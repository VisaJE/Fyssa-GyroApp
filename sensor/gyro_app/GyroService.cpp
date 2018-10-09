#include "GyroService.h"
#include "QuickMafs.h"
#include "app-resources/resources.h"
#include "common/core/debug.h"
#include "meas_acc/resources.h"
#include "meas_gyro/resources.h"
#include "whiteboard/builtinTypes/UnknownStructure.h"
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

#define CALIBRATION_TIME 1000

const char* const GyroService::LAUNCHABLE_NAME = "GyroService";

#define DEGREES_PER_PI 57.2957795130

using namespace gyrospinner;

const char* GYRO_PATH = "/meas/gyro/";
const char* ACC_PATH = "/meas/acc/";

static const whiteboard::ExecutionContextId sExecutionContextId =
    WB_RES::LOCAL::FYSSA_GYRO::EXECUTION_CONTEXT;

static const whiteboard::LocalResourceId sProviderResources[] = {
    WB_RES::LOCAL::FYSSA_GYRO::LID,
    WB_RES::LOCAL::FYSSA_GYRO_FYSSAGYROCONFIG::LID,
    WB_RES::LOCAL::FYSSA_IMU::LID,
    WB_RES::LOCAL::FYSSA_IMU_FYSSAACCCONFIG::LID,
};


GyroService::GyroService()
    : ResourceClient(WBDEBUG_NAME(__FUNCTION__), sExecutionContextId),
      ResourceProvider(WBDEBUG_NAME(__FUNCTION__), sExecutionContextId),
      LaunchableModule(LAUNCHABLE_NAME, sExecutionContextId),
      isRunning(false),
      sampleRate(208),
      minAngleSquared(0.001*0.001),
      accSampleRate(208),
      minAccSquared(0.001)
{

    mTimer = whiteboard::ID_INVALID_TIMER;
    mCalibTimer = whiteboard::ID_INVALID_TIMER;
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
        DEBUGLOG("D/SENSOR/Resetting.");

        shutdownCounter = 0;
        reset();
        if (isRunning) calibrate();
        asyncPut(WB_RES::LOCAL::UI_IND_VISUAL::ID, AsyncRequestOptions::Empty,(uint16_t) 1);
        WB_RES::HeadingValue res;
        res.frontx = startHeadingX.i;
        res.fronty = startHeadingX.j;
        res.frontz = startHeadingX.k;
        res.topx = zeroAngularX;
        res.topy = zeroAngularY;
        res.topz = zeroAngularZ;
        returnResult(request, whiteboard::HTTP_CODE_OK,
             ResponseOptions::Empty, res);
        
    }

    break;
    case WB_RES::LOCAL::FYSSA_IMU::ID:
    {
        DEBUGLOG("D/SENSOR/Fyssa_Imu get");
        if (!isRunning)
        {
            returnResult(request, whiteboard::HTTP_CODE_SERVICE_UNAVAILABLE);
            break;
        }
        WB_RES::PositionValue res;
        res.x = xSpeed;
        res.y = ySpeed;
        res.z = zSpeed;
        reset();
        if (isRunning) calibrate();
        asyncPut(WB_RES::LOCAL::UI_IND_VISUAL::ID, AsyncRequestOptions::Empty,(uint16_t) 1);
        returnResult(request, whiteboard::HTTP_CODE_OK,
            ResponseOptions::Empty, res);
        break;
    }

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
    case WB_RES::LOCAL::FYSSA_IMU_FYSSAACCCONFIG::ID:
    {
        bool wasRunning = isRunning;
        if (wasRunning) stopRunning();
        // Parse and gather the specified settings
        auto config = WB_RES::LOCAL::FYSSA_IMU_FYSSAACCCONFIG::PUT::ParameterListRef(parameters).getFyssaAccConfig();
        int i = 0;
        while (accSampleRate != (uint32_t) config.rate && i++ < 8) {
            if (SAMPLE_RATES[i] == (uint32_t)config.rate) {
                accSampleRate = (uint32_t)config.rate;
            }
        }

        if (accSampleRate != (uint32_t) config.rate) {
            DEBUGLOG("D/SENSOR/Updating sample rate failed:");
            returnResult(request, whiteboard::HTTP_CODE_BAD_REQUEST);
        }
        else
        {
            minAccSquared = ((float)config.threshold) * ((float)config.threshold);
        }
        filterWithGyro = (bool)config.filter;
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
    imuSubscription = false;
    startSequence(request);
    break;
    case WB_RES::LOCAL::FYSSA_IMU::ID:
    imuSubscription = true;
    startSequence(request);
    break;
    default:
        DEBUGLOG("D/SENSOR/Shouldn't happen!");
        return returnResult(request, whiteboard::HTTP_CODE_BAD_REQUEST);
        //return ResourceProvider::onSubscribe(request, parameters);
        break;
    }
}

void GyroService::startSequence(const whiteboard::Request& request)
{
        DEBUGLOG("D/SENSOR/Subscription for orientation");
        if(startRunning(mRemoteRequestId) == whiteboard::HTTP_CODE_OK) {

            return returnResult(request, whiteboard::HTTP_CODE_OK);
        }
        else returnResult(request, whiteboard::HTTP_CODE_SERVICE_UNAVAILABLE);
}

void GyroService::onUnsubscribe(const whiteboard::Request& request,
                                       const whiteboard::ParameterList& parameters)
{
    DEBUGLOG("D/SENSOR/GyroService::onUnsubscribe()");

    switch (request.getResourceConstId())
    {
    case WB_RES::LOCAL::FYSSA_GYRO::ID:
    case WB_RES::LOCAL::FYSSA_IMU::ID:
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

    wb::Result result = getResource((const char*) buff, mMeasGyroResourceId);
    if (!wb::RETURN_OKC(result))
    {
        return result;
    }
    result = asyncSubscribe(mMeasGyroResourceId, AsyncRequestOptions(&remoteRequestId, 0, true));

    char buff2[20];
    snprintf(buff2, sizeof(buff2), "%s%d", ACC_PATH, accSampleRate);

    wb::Result result2 = getResource((const char*) buff2, mMeasAccResourceId);
    if (!wb::RETURN_OKC(result))
    {
        return result;
    }
    result2 = asyncSubscribe(mMeasAccResourceId, AsyncRequestOptions(&remoteRequestId, 0, true));

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
    wb::Result result2 = asyncUnsubscribe(mMeasGyroResourceId, NULL);
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
        onGyroData(resourceId, value, parameters);
        break;
    }
    case WB_RES::LOCAL::MEAS_ACC_SAMPLERATE::ID:
    {
        onAccData(resourceId, value, parameters);
        break;
    }
    
    }
}

void GyroService::onGyroData(whiteboard::ResourceId resourceId, const whiteboard::Value& value,
                                          const whiteboard::ParameterList& parameters)
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
            zeroAngularX = zeroAngularX*3/4 + gyroValue.mX/4;
            zeroAngularY = zeroAngularY*3/4 + gyroValue.mY/4;
            zeroAngularZ = zeroAngularZ*3/4 + gyroValue.mZ/4;
            }
        return;
    }

    for (size_t i = 0; i < arrayData.size(); i++)
    {
        whiteboard::FloatVector3D gyroValue = arrayData[i];
        gyrospinner::Vector axis;
        axis.i = (gyroValue.mX - zeroAngularX)/(sampleRate*DEGREES_PER_PI);
        axis.j = (gyroValue.mY - zeroAngularY)/(sampleRate*DEGREES_PER_PI);
        axis.k = (gyroValue.mZ - zeroAngularZ)/(sampleRate*DEGREES_PER_PI);
        float angle = QuickMafs::normalize(&axis);
        if (angle*angle > minAngleSquared) {
            isTurning = true;
            totalRotation = gyrospinner::QuickMafs::product(gyrospinner::QuickMafs::constructRotator(axis, -angle), totalRotation); 
        } else isTurning = false;

        if (!imuSubscription)
        {
            if (upCounter >= (int)sampleRate/4) 
            {
                //DEBUGLOG("D/SENSOR/OnNotify():angle x 1000: %u", (uint32_t)(angle*1000));
                gyrospinner::Vector headingX = QuickMafs::rotate(startHeadingX, totalRotation);
                gyrospinner::Vector headingZ = QuickMafs::rotate(startHeadingZ, totalRotation);
                QuickMafs::normalize(&headingX);
                QuickMafs::normalize(&headingZ);
                upCounter = 0;
                WB_RES::HeadingValue res;
                res.frontx = headingX.i;
                res.fronty = headingX.j;
                res.frontz = headingX.k;
                res.topx = headingZ.i;
                res.topy = headingZ.j;
                res.topz = headingZ.k;
                updateResource(WB_RES::LOCAL::FYSSA_GYRO(),
                    ResponseOptions::Empty, res);
            } else ++upCounter;
        }
    }
}

void GyroService::onAccData(whiteboard::ResourceId resourceId, const whiteboard::Value& value,
                                          const whiteboard::ParameterList& parameters)
{
    const WB_RES::AccData& accValues =
                value.convertTo<const WB_RES::AccData&>();

    if (accValues.arrayAcc.size() <= 0)
    {
        // No value, do nothing...
        return;
    }

    const whiteboard::Array<whiteboard::FloatVector3D>& arrayData = accValues.arrayAcc;
    uint32_t relativeTime = accValues.timestamp;
    if (orientate) 
    {
        whiteboard::FloatVector3D accValue = arrayData[0];

        startHeadingZ.i = startHeadingZ.i*3/4 + accValue.mX/4;
        startHeadingZ.j = startHeadingZ.j*3/4 + accValue.mY/4;
        startHeadingZ.k = startHeadingZ.k*3/4 + accValue.mZ/4;
        // Rest will be done once the calibration is done at onTimer();
        return;
    }
    for (size_t i = 0; i < arrayData.size(); i++)
    {
        whiteboard::FloatVector3D accValue = arrayData[i];
        gyrospinner::Vector acc = {accValue.mX, accValue.mY, accValue.mZ};
        if (isTurning || !filterWithGyro)
        {
            gyrospinner::Vector headingX = QuickMafs::rotate(startHeadingX, totalRotation);
            gyrospinner::Vector headingZ = QuickMafs::rotate(startHeadingZ, totalRotation);
            gyrospinner::Vector yVec = QuickMafs::crossProduct(headingZ, headingX);

            float zS = QuickMafs::dotProduct(acc, headingZ) - g;
            zSpeed += (zS*zS > minAccSquared) ? zS / accSampleRate : 0.0;
            float xS = QuickMafs::dotProduct(acc, headingX);
            xSpeed += xS*xS > minAccSquared ? xS / accSampleRate : 0.0;
            float yS = QuickMafs::dotProduct(acc, yVec);
            ySpeed += yS*yS > minAccSquared ? yS / accSampleRate : 0.0;
        } else if (filterWithGyro)
        {
            zSpeed = 0.0;
            xSpeed = 0.0;
            ySpeed = 0.0;
        }
        position[0] += xSpeed/accSampleRate;
        position[1] += ySpeed/accSampleRate;
        position[2] += zSpeed/accSampleRate;
        if (imuSubscription) {
            if (upCounter >= accSampleRate/4) {
                DEBUGLOG("D/SENSOR/onAccData updating position resource. Current speed %u %u %u", (uint32_t)abs((int) xSpeed), (uint32_t)abs((int) ySpeed), (uint32_t)abs((int) zSpeed));
                upCounter = 0;
                WB_RES::PositionValue res;
                res.x = position[0];
                res.y = position[1];
                res.z = position[2];
                updateResource(WB_RES::LOCAL::FYSSA_IMU(),
                        ResponseOptions::Empty, res);
            }
            else upCounter++;
        }
    }
}

void GyroService::onTimer(whiteboard::TimerId timerId)
{
    if (timerId == mTimer)
    {
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
    else if (timerId == mCalibTimer) {
        
        float x = startHeadingZ.i;
        float y = startHeadingZ.j;
        float z = startHeadingZ.k;
        QuickMafs::normalize(&startHeadingZ);
        isCalibrating = false;
        orientate = false;
        g = sqrt(x*x + y*y + z*z);
        asyncPut(WB_RES::LOCAL::UI_IND_VISUAL::ID, AsyncRequestOptions::Empty,(uint16_t) 0);
        if (x*x > 0.001)
        {
            startHeadingX.j = 1.0;
            startHeadingX.k = 0.0;
            startHeadingX.i = -y*startHeadingX.j/x;
            QuickMafs::normalize(&startHeadingX);

        } else
        {
            startHeadingX.i = 0.0;
            startHeadingX.k = 1.0;
            startHeadingX.j = -z*startHeadingX.k/y;
            QuickMafs::normalize(&startHeadingX);
        }
        DEBUGLOG("D/SENSOR/ Imu calibrated with acc data %u, %u, %u. Gravity g: %u", (uint32_t)abs((int)(x*100)), (uint32_t)abs((int)(y*100)),
            (uint32_t)abs((int)(z*100)), (uint32_t)abs((int)(g*100)));
    }


}

void GyroService::reset()
{
    startHeadingX = {1.0, 0.0, 0.0};
    startHeadingZ = {0.0, 0.0, 1.0};
    totalRotation = {1.0, {0.0, 0.0, 0.0}};
    shutdownCounter = 0;
    xSpeed = 0;
    ySpeed = 0;
    zSpeed = 0;
    for (int i = 0; i < 3; i++) position[i] = 0.0;
}

void GyroService::calibrate()
{
    isCalibrating = true;
    orientate = true;
    mCalibTimer =  whiteboard::ResourceProvider::startTimer((size_t) CALIBRATION_TIME, false);
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


