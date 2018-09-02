#include "GyroService.h"
#include "QuickMafs.h"
#include "app-resources/resources.h"
#include "common/core/debug.h"
#include "meas_acc/resources.h"
#include "meas_gyro/resources.h"
#include "whiteboard/builtinTypes/UnknownStructure.h"
#include "whiteboard/integration/bsp/shared/debug.h"
#include "component_max3000x/resources.h"
#include "system_mode/resources.h"
#include "ui_ind/resources.h"
#include <float.h>
#include <math.h>
#include <string>

#define ASSERT WB_DEBUG_ASSERT

// Time between wake-up and going to power-off mode
#define AVAILABILITY_TIME 180000


// Time between turn on AFE wake circuit to power off
// (must be LED_BLINKING_PERIOD multiple)
#define WAKE_PREPARATION_TIME 6000

// LED blinking period in adertsing mode
#define LED_BLINKING_PERIOD 6000

const char* const GyroService::LAUNCHABLE_NAME = "GyroService";

#define DEGREES_PER_PI = 57.2957795130


const char* GYRO_PATH = "/meas/gyro/";

static const whiteboard::ExecutionContextId sExecutionContextId =
    WB_RES::LOCAL::FYSSA_GYRO::EXECUTION_CONTEXT;

static const whiteboard::LocalResourceId sProviderResources[] = {
    WB_RES::LOCAL::FYSSA_GYRO::LID,
    WB_RES::LOCAL::FYSSA_GYRO_FYSSAGYROCONFIG::LID,
};


GyroService::GyroService()
    : ResourceClient(WBDEBUG_NAME(__FUNCTION__), sExecutionContextId),
      ResourceProvider(WBDEBUG_NAME(__FUNCTION__), sExecutionContextId),
      LaunchableModule(LAUNCHABLE_NAME, sExecutionContextId),
      isRunning(false),
      sampleRate(208),
      minAngleSquared(0.001)
{

    mTimer = whiteboard::ID_INVALID_TIMER;
    // Reset max acceleration members
    reset();

}

GyroService::~GyroService()
{
}

bool GyroService::initModule()
{
    if (registerProviderResources(sProviderResources) != whiteboard::HTTP_CODE_OK)
    {
        return false;
    }


    mModuleState = WB_RES::ModuleStateValues::INITIALIZED;
    return true;
}

void GyroService::deinitModule()
{
    unregisterProviderResources(sProviderResources);
    mModuleState = WB_RES::ModuleStateValues::UNINITIALIZED;
}

/** @see whiteboard::ILaunchableModule::startModule */
bool GyroService::startModule()
{
    shutdownCounter = 0;
    mModuleState = WB_RES::ModuleStateValues::STARTED;
    mTimer = whiteboard::ResourceProvider::startTimer((size_t) LED_BLINKING_PERIOD, true);
    return true;
}

void GyroService::stopModule() 
{
    whiteboard::ResourceProvider::stopTimer(mTimer);
    mModuleState = WB_RES::ModuleStateValues::STOPPED;
    mTimer = whiteboard::ID_INVALID_TIMER;
    stopRunning();
}


void GyroService::onGetRequest(const whiteboard::Request& request,
                                      const whiteboard::ParameterList& parameters)
{
    

    if (mModuleState != WB_RES::ModuleStateValues::STARTED)
    {
        return returnResult(request, wb::HTTP_CODE_SERVICE_UNAVAILABLE);
    }

    switch (request.getResourceConstId())
    {
    case WB_RES::LOCAL::FYSSA_GYRO::ID:
    {
        DEBUGLOG("D/SENSOR/Rotating and resetting.");
        currentHeadingX = gyrospinner::QuickMafs::rotate({1.0, 0.0, 0.0}, totalRotation);
        currentHeadingY = gyrospinner::QuickMafs::rotate({0.0, 1.0, 0.0}, totalRotation);
        shutdownCounter = 0;
        reset();
        calibrateGyro();
        WB_RES::HeadingValue res;
        res.frontx = currentHeadingX.i;
        res.fronty = currentHeadingX.j;
        res.frontz = currentHeadingX.k;
        res.topx = zeroAngularX;
        res.topy = zeroAngularY;
        res.topz = zeroAngularZ;
        returnResult(request, whiteboard::HTTP_CODE_OK,
             ResponseOptions::Empty, res);
        
    }

    break;

    default:
        // Return error
        return returnResult(request, whiteboard::HTTP_CODE_NOT_IMPLEMENTED);
    }
}


void GyroService::onPutRequest(const whiteboard::Request& request,
                                      const whiteboard::ParameterList& parameters)
{
    DEBUGLOG("D/SENSOR/onPutRequest(). Requedt id: %d. Our config id: %d.", request.getResourceConstId(), WB_RES::LOCAL::FYSSA_GYRO_FYSSAGYROCONFIG::ID);

    if (mModuleState != WB_RES::ModuleStateValues::STARTED)
    {
        return returnResult(request, wb::HTTP_CODE_SERVICE_UNAVAILABLE);
    }

    switch (request.getResourceConstId())
    {
    case WB_RES::LOCAL::FYSSA_GYRO_FYSSAGYROCONFIG::ID:
    {
        
        bool wasRunning = isRunning;
        if (wasRunning) stopRunning();
        // Parse and gather the specified settings
        auto config = WB_RES::LOCAL::FYSSA_GYRO_FYSSAGYROCONFIG::PUT::ParameterListRef(parameters).getFyssaGyroConfig();
        int i = 0;
        while (sampleRate != (uint32_t) config.rate && i++ < 8) {
            if (SAMPLE_RATES[i] == (uint32_t)config.rate) {
                sampleRate = (uint32_t)config.rate;
            }
        }

        if (sampleRate != (uint32_t) config.rate) {
            DEBUGLOG("D/SENSOR/Updating sample rate failed:");
            returnResult(request, whiteboard::HTTP_CODE_BAD_REQUEST);
        }
        else
        {
            minAngleSquared = ((float)config.threshold) * ((float)config.threshold);
        }
        
        if (wasRunning) startRunning(mRemoteRequestId);
        returnResult(request, whiteboard::HTTP_CODE_OK);
        break;
    }
  default:
        // Return error
        return returnResult(request, whiteboard::HTTP_CODE_NOT_IMPLEMENTED);
    }
}


void GyroService::onSubscribe(const whiteboard::Request& request,
                                     const whiteboard::ParameterList& parameters)
{
    DEBUGLOG("D/SENSOR/GyroService::onSubscribe()");
    
    switch (request.getResourceConstId())
    {
    case WB_RES::LOCAL::FYSSA_GYRO::ID:
    {
        DEBUGLOG("D/SENSOR/Subscription for orientation");
        if(startRunning(mRemoteRequestId) == whiteboard::HTTP_CODE_OK) {

            return returnResult(request, whiteboard::HTTP_CODE_OK);
        }
        else returnResult(request, whiteboard::HTTP_CODE_SERVICE_UNAVAILABLE);
       
        break;
    }
    default:
        DEBUGLOG("D/SENSOR/Shouldn't happen!");
        return returnResult(request, whiteboard::HTTP_CODE_BAD_REQUEST);
        //return ResourceProvider::onSubscribe(request, parameters);
        break;
    }
}


void GyroService::onUnsubscribe(const whiteboard::Request& request,
                                       const whiteboard::ParameterList& parameters)
{
    DEBUGLOG("D/SENSOR/GyroService::onUnsubscribe()");

    switch (request.getResourceConstId())
    {
    case WB_RES::LOCAL::FYSSA_GYRO::ID:
        returnResult(request, wb::HTTP_CODE_OK);
        stopRunning();
        break;

    default:
        DEBUGLOG("D/SENSOR/Shouldnt happen!");
        return returnResult(request, whiteboard::HTTP_CODE_BAD_REQUEST);
        //ResourceProvider::onUnsubscribe(request, parameters);
        break;
    }
}




whiteboard::Result GyroService::startRunning(whiteboard::RequestId& remoteRequestId)
{
    if (isRunning)
    {
        return whiteboard::HTTP_CODE_OK;
    }

    DEBUGLOG("D/SENSOR/GyroService::startRunning().");
    char buff[20];
    snprintf(buff, sizeof(buff), "%s%d", GYRO_PATH, sampleRate);

    wb::Result result = getResource((const char*) buff, mMeasAccResourceId);
    if (!wb::RETURN_OKC(result))
    {
        return result;
    }
    result = asyncSubscribe(mMeasAccResourceId, AsyncRequestOptions(&remoteRequestId, 0, true));

    isRunning = true;

    return whiteboard::HTTP_CODE_OK;
}


whiteboard::Result GyroService::stopRunning()
{
    if (!isRunning)
    {
        return whiteboard::HTTP_CODE_OK;
    }

    DEBUGLOG("D/SENSOR/GyroService::stopRunning()");

    // Unsubscribe the LinearAcceleration resource, when unsubscribe is done, we get callback
    wb::Result result = asyncUnsubscribe(mMeasAccResourceId, NULL);
    if (!wb::RETURN_OKC(result))
    {
        DEBUGLOG("D/SENSOR/asyncUnsubscribe threw error: %u", result);
    }
    isRunning = false;
    return whiteboard::HTTP_CODE_OK;
}


// This callback is called when the resource we have subscribed notifies us
void GyroService::onNotify(whiteboard::ResourceId resourceId, const whiteboard::Value& value,
                                          const whiteboard::ParameterList& parameters)
{
    // Confirm that it is the correct resource
    switch (resourceId.getConstId())
    {
    case WB_RES::LOCAL::MEAS_GYRO_SAMPLERATE::ID:
    {
        const WB_RES::GyroData& turnRateValue =
            value.convertTo<const WB_RES::GyroData&>();

        if (turnRateValue.arrayGyro.size() <= 0)
        {
            // No value, do nothing...
            return;
        }

        const whiteboard::Array<whiteboard::FloatVector3D>& arrayData = turnRateValue.arrayGyro;
        uint32_t relativeTime = turnRateValue.timestamp;

        if (isCalibrating)
        {

            for (size_t i = 0; i < arrayData.size(); i++)
            {
                whiteboard::FloatVector3D gyroValue = arrayData[i];
                zeroAngularX = (zeroAngularX + gyroValue.mX)/2;
                zeroAngularY = (zeroAngularY + gyroValue.mY)/2;
                zeroAngularZ = (zeroAngularZ + gyroValue.mZ)/2;
            }
        isCalibrating = false;
        return;
        }


        for (size_t i = 0; i < arrayData.size(); i++)
        {
            whiteboard::FloatVector3D gyroValue = arrayData[i];
            gyrospinner::Vector axis;
            axis.i = (gyroValue.mX - zeroAngularX)/(sampleRate*DEGREES_PER_PI);
            axis.j = (gyroValue.mY - zeroAngularY)/(sampleRate*DEGREES_PER_PI);
            axis.k = (gyroValue.mZ - zeroAngularZ)/(sampleRate*DEGREES_PER_PI);
            float angle = gyrospinner::QuickMafs::normalize(&axis);
            if (angle*angle > minAngleSquared) {
                totalRotation = gyrospinner::QuickMafs::product(gyrospinner::QuickMafs::constructRotator(axis, angle), totalRotation); 
            }

            if (upCounter >= (int)sampleRate/4) 
            {
                DEBUGLOG("D/SENSOR/OnNotify():angle: %u", (uint32_t)(angle*1000));
                currentHeadingX = gyrospinner::QuickMafs::rotate({1.0, 0.0, 0.0}, totalRotation);
                currentHeadingY = gyrospinner::QuickMafs::rotate({0.0, 1.0, 0.0}, totalRotation);
                gyrospinner::QuickMafs::normalize(&currentHeadingX);
                gyrospinner::QuickMafs::normalize(&currentHeadingY);
                upCounter = 0;
                WB_RES::HeadingValue res;
                res.frontx = currentHeadingX.i;
                res.fronty = currentHeadingX.j;
                res.frontz = currentHeadingX.k;
                // TEMP PUSH FOR TURN AXIS INFO
                res.topx = axis.i;
                res.topy = axis.j;
                res.topz = axis.k;
                /*res.topx = currentHeadingY.i;
                res.topy = currentHeadingY.j;
                res.topz = currentHeadingY.k;*/
                updateResource(WB_RES::LOCAL::FYSSA_GYRO(),
                     ResponseOptions::Empty, res);
            } else ++upCounter;
        }
    }
    break;
    }
}

void GyroService::onTimer(whiteboard::TimerId timerId)
{
    if (timerId != mTimer)
    {
        return;
    }
    if (!isRunning) shutdownCounter = shutdownCounter + LED_BLINKING_PERIOD;
    else shutdownCounter = 0;
    if (shutdownCounter >= AVAILABILITY_TIME) 
    {
            // Prepare AFE to wake-up mode
        asyncPut(WB_RES::LOCAL::COMPONENT_MAX3000X_WAKEUP::ID,
                 AsyncRequestOptions(NULL, 0, true), (uint8_t)1);


        // Make PUT request to enter power off mode
        asyncPut(WB_RES::LOCAL::SYSTEM_MODE::ID,
                 AsyncRequestOptions(NULL, 0, true), // Force async
                 (uint8_t)1U);                       // WB_RES::SystemMode::FULLPOWEROFF
    }
    else
    {
    // Make PUT request to trigger led blink
    asyncPut(WB_RES::LOCAL::UI_IND_VISUAL::ID, AsyncRequestOptions::Empty,(uint16_t) 2);
    }


}

void GyroService::reset()
{
    currentHeadingX = {1.0, 0.0, 0.0};
    currentHeadingY = {0.0, 1.0, 0.0};
    totalRotation = {1.0, {0.0, 0.0, 0.0}};
    shutdownCounter = 0;
    
}

void GyroService::calibrateGyro()
{
    if (isRunning) isCalibrating = true;
}

void GyroService::onRemoteWhiteboardDisconnected(whiteboard::WhiteboardId whiteboardId)
{
    DEBUGLOG("D/SENSOR/GyroService::onRemoteWhiteboardDisconnected()");
    stopRunning();
}

void GyroService::onClientUnavailable(whiteboard::ClientId clientId)
{
    DEBUGLOG("D/SENSOR/GyroService::onClientUnavailable()");
    stopRunning();
}

gyrospinner::Vector GyroService::currentHeadingZ() 
{
return {currentHeadingX.j*currentHeadingY.k-currentHeadingX.j*currentHeadingY.k, currentHeadingX.k*currentHeadingY.i - currentHeadingY.k * currentHeadingX.i, currentHeadingX.i*currentHeadingY.j - currentHeadingX.j*currentHeadingY.i};
}

