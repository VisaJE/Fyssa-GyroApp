#pragma once

#include "QuickMafs.h"

#include <whiteboard/LaunchableModule.h>
#include <whiteboard/ResourceClient.h>
#include <whiteboard/ResourceProvider.h>
#include <whiteboard/containers/RequestMap.h>

#include "wb-resources/resources.h"
#include <string>

class GyroService FINAL : private whiteboard::ResourceClient,
                                         private whiteboard::ResourceProvider,
                                         public whiteboard::LaunchableModule

{
public:
    /** Name of this class. Used in StartupProvider list. */
    static const char* const LAUNCHABLE_NAME;
    GyroService();
    ~GyroService();

private:
    /** @see whiteboard::ILaunchableModule::initModule */
    virtual bool initModule() OVERRIDE;

    /** @see whiteboard::ILaunchableModule::deinitModule */
    virtual void deinitModule() OVERRIDE;

    /** @see whiteboard::ILaunchableModule::startModule */
    virtual bool startModule() OVERRIDE;

    /** @see whiteboard::ILaunchableModule::stopModule */
    virtual void stopModule() OVERRIDE;

    /**
    *   GET POST and DELETE request handlers.
    *
    *   @param requestId ID of the request
    *   @param clientId ID of the client that should receive the result
    *   @param resourceId ID of the associated resource
    *   @param parameters List of parameters for the request
    *   @return Result of the operation
    */
    virtual void onGetRequest(const whiteboard::Request& request,
                              const whiteboard::ParameterList& parameters) OVERRIDE;


    virtual void onPutRequest(const whiteboard::Request& request,
                              const whiteboard::ParameterList& parameters) OVERRIDE;

    /**
    *	Subscribe notification callback.
    *
    *	@param request Request information
    *	@param parameters List of parameters
    */
    virtual void onSubscribe(const whiteboard::Request& request,
                             const whiteboard::ParameterList& parameters) OVERRIDE;

    /**
    *	Unsubscribe notification callback.
    *
    *	@param request Request information
    *	@param parameters List of parameters
    */
    virtual void onUnsubscribe(const whiteboard::Request& request,
                               const whiteboard::ParameterList& parameters) OVERRIDE;

    /**
    *  Whiteboard disconnect notification handler.
    *
    *  This can be used for example to cleanup possible subscription related information of clients from
    *  the remote whiteboard.
    *
    *  @param whiteboardId ID of the whiteboard that has been disconnected.
    *
    *  @see whiteboard::ResourceProvider::onSubscribe
    *  @see whiteboard::ResourceProvider::onUnsubscribe
    */
    virtual void onRemoteWhiteboardDisconnected(whiteboard::WhiteboardId whiteboardId) OVERRIDE;

    /**
    * Local client 'disconnect' notification handler.
    *
    *  This can be used for example to cleanup possible subscription related information of the client.
    *
    *  @see whiteboard::ResourceProvider::onSubscribe
    *  @see whiteboard::ResourceProvider::onUnsubscribe
    */
    virtual void onClientUnavailable(whiteboard::ClientId clientId) OVERRIDE;

    /**
    *	Callback for resource notifications.
    *   Note that this function will not be called for notifications that are
    *   of types WB_RESOURCE_NOTIFICATION_TYPE_INSERT or WB_RESOURCE_NOTIFICATION_TYPE_DELETE,
    *   just for notifications that are of type WB_RESOURCE_NOTIFICATION_TYPE_UPDATE.
    *
    *	@param resourceId Resource id associated with the update
    *	@param rValue Current value of the resource
    */
    virtual void onNotify(whiteboard::ResourceId resourceId, const whiteboard::Value& value,
                          const whiteboard::ParameterList& parameters);


protected:
    /**
    *	Timer callback.
    *
    *	@param timerId Id of timer that triggered
    */
    virtual void onTimer(whiteboard::TimerId timerId) OVERRIDE;

private:
    whiteboard::Result startRunning(whiteboard::RequestId& remoteRequestId);
    whiteboard::Result stopRunning();

    void reset();

    whiteboard::RequestId mRemoteRequestId;
    whiteboard::ResourceId	mMeasAccResourceId;
    whiteboard::ResourceId	mMeasGyroResourceId;

    bool isRunning;
    void calibrate();

    // Stuff for the gyro

    void onGyroData(whiteboard::ResourceId resourceId, const whiteboard::Value& value,
                                          const whiteboard::ParameterList& parameters);
    float minAngleSquared;
    uint32_t sampleRate;
    
    bool isCalibrating = false;
    bool isTurning = false;
    bool memoryBit;
    float zeroAngularX = 0;
    float zeroAngularY = 0;
    float zeroAngularZ = 0;

    

    const uint32_t SAMPLE_RATES[8] =  {13, 26, 52, 104, 208, 416, 833, 1666};
    int upCounter = 0;



    gyrospinner::Vector startHeadingX = {1.0, 0.0, 0.0}; 
    gyrospinner::Vector startHeadingY = {0.0, 1.0, 0.0};
    gyrospinner::Vector crossProduct(gyrospinner::Vector a, gyrospinner::Vector b);

    gyrospinner::Quaternion totalRotation = {1.0, {0.0, 0.0, 0.0}};
    
    bool orientate = false;

    // True if imu is subscribed and gyro is not (by the mobile client)
    bool imuSubscription = false;
    // Stuff for accelerometer
    void onAccData(whiteboard::ResourceId resourceId, const whiteboard::Value& value,
                                          const whiteboard::ParameterList& parameters);
    
    float xSpeed = 0;
    float ySpeed = 0;
    float zSpeed = 0;
    float minAccSquared;
    float g = 9.81;
    uint32_t accSampleRate;
    float position[3] = {0.0, 0.0, 0.0};
    
    bool filterWithGyro = true;

    whiteboard::TimerId mTimer;
    whiteboard::TimerId mCalibTimer;
    uint32_t shutdownCounter;
};