
#ifndef SMGSS_H
#define SMGSS_H

/*********
 Includes
 *********/

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 \defgroup overAir Over-the-air Messages
 <BR>
 This header file defines the over-the-air messages between the collector
 and the sensor applications.
 <BR>
 Each field in these message are formatted low byte first, so a 16 bit field
 with a value of 0x1516 will be sent as 0x16, 0x15.
 <BR>
 The first byte of each message (data portion) contains the command ID (@ref
 Smsgs_cmdIds).
 <BR>
  @{
 */

/*********
 Constants and definitions
 *********/
  
/*! Sensor Message Extended Address Length */
#define SMGS_SENSOR_EXTADDR_LEN 8

/*! Config Request message length (over-the-air length) */
#define SMSGS_CONFIG_REQUEST_MSG_LENGTH 23
/*! Config Response message length (over-the-air length) */
#define SMSGS_CONFIG_RESPONSE_MSG_LENGTH 28
/*! Length of the bikeParkingState portion of the Smsgs_configRspMsg_t  */
#define SMSGS_CONFIG_BIKEPARKING_LEN 4

/*! Tracking Request message length (over-the-air length) */
#define SMSGS_TRACKING_REQUEST_MSG_LENGTH 1
/*! Tracking Response message length (over-the-air length) */
#define SMSGS_TRACKING_RESPONSE_MSG_LENGTH 1

/*! Length of a sensor data message with no configured data fields */
#define SMSGS_BASIC_SENSOR_LEN (7 + SMGS_SENSOR_EXTADDR_LEN)
/*! Length of the tempSensor portion of the sensor data message */
#define SMSGS_SENSOR_TEMP_LEN 4
/*! Length of the lightSensor portion of the sensor data message */
#define SMSGS_SENSOR_LIGHT_LEN 2
/*! Length of the humiditySensor portion of the sensor data message */
#define SMSGS_SENSOR_HUMIDITY_LEN 4
/*! Length of the messageStatistics portion of the sensor data message */
#define SMSGS_SENSOR_MSG_STATS_LEN 40
/*! Length of the configSettings portion of the sensor data message */
#define SMSGS_SENSOR_CONFIG_SETTINGS_LEN 8

/*! Toggle Led Request message length (over-the-air length) */
#define SMSGS_TOGGLE_LED_REQUEST_MSG_LEN 1
/*! Toggle Led Request message length (over-the-air length) */
#define SMSGS_TOGGLE_LED_RESPONSE_MSG_LEN 2

/*! Toggle Ble Request message length (over-the-air length) */
#define SMSGS_TOGGLE_BLE_REQUEST_MSG_LEN 1
/*! Toggle Ble Request message length (over-the-air length) */
#define SMSGS_TOGGLE_BLE_RESPONSE_MSG_LEN 2

/*! Change Ble URL Request message length (over-the-air length) */
#define SMSGS_CHANGE_BLE_URL_REQUEST_MSG_LEN 11
/*! Change Ble URL Response message length (over-the-air length) */
#define SMSGS_CHANGE_BLE_URL_RESPONSE_MSG_LEN 11

/*! Parking State message length (over-the-air length) */
#define SMSGS_PARKING_STATE_MSG_LEN 1
/*! Bike Select message length (over-the-air length) */
#define SMSGS_BIKE_SELECT_MSG_LEN 2
/*! Parking State message length (over-the-air length) */
#define SMSGS_PARKING_STATE_RSP_MSG_LEN 5




/*!
 Message IDs for Sensor data messages.  When sent over-the-air in a message,
 this field is one byte.
 */
 typedef enum
 {
    /*! Configuration message, sent from the collector to the sensor */
    Smsgs_cmdIds_configReq = 1,
    /*! Configuration Response message, sent from the sensor to the collector */
    Smsgs_cmdIds_configRsp = 2,

    /*! Tracking request message, sent from the the collector to the sensor */
    Smsgs_cmdIds_trackingReq = 3,
     /*! Tracking response message, sent from the sensor to the collector */
    Smsgs_cmdIds_trackingRsp = 4,

    /*! Sensor data message, sent from the sensor to the collector */
    Smsgs_cmdIds_sensorData = 5,

    /*! Toggle LED message, sent from the collector to the sensor */
    Smsgs_cmdIds_toggleLedReq = 6,
    /*! Toggle LED response msg, sent from the sensor to the collector */
    Smsgs_cmdIds_toggleLedRsp = 7,

    /*! Change URL request message, sent from the collector to the sensor */
    Smsgs_cmIds_changeBleUrl = 8,
    /*! Change URL response message, sent from the sensor to the collector */
    Smsgs_cmIds_changeBleUrlRsp = 9,

    /*! Bike parking state message, sent from the sensor to the collector*/
    Smsgs_cmIds_bikeParkingState = 10,
    /*! Bike Select message, sent from the sensor to the collector*/
    Smsgs_cmIds_bikeSelect = 11,
    /*! Bike parking state, sent from the sensor to the collector*/
    Smsgs_cmIds_bikeParkingStateRsp = 12,

 } Smsgs_cmdIds_t;

/*!
 Frame Control field states what data fields are included in reported
 sensor data, each value is a bit mask value so that they can be combined
 (OR'd together) in a control field.
 When sent over-the-air in a message this field is 2 bytes.
 */
typedef enum
{
    /*! Temperature Sensor */
    Smsgs_dataFields_tempSensor = 0x0001,
    /*! Message Statistics */
    Smsgs_dataFields_msgStats = 0x0002,
    /*! Config Settings */
    Smsgs_dataFields_configSettings = 0x0004,

} Smsgs_dataFields_t;

/*!
 Status values for the over-the-air messages
 */
typedef enum
{
    /*! Success */
    Smsgs_statusValues_success = 0,
    /*! Message was invalid and ignored */
    Smsgs_statusValues_invalid = 1,
    /*!
     Config message was received but only some frame control fields
     can be sent or the reportingInterval or pollingInterval fail
     range checks.
     */
    Smsgs_statusValues_partialSuccess = 2,
} Smsgs_statusValues_t;

/*!
 Type of nodes
 */
typedef enum
{
    Smsgs_typeNode_simpleNode = 0x01,
    Smsgs_typeNode_parkingBike = 0x02,
    //add new type
} Smsgs_typeNode_t;




/*********
 Structures - Building blocks for the over-the-air sensor messages
 *********/

/*!
 Configuration Request message: sent from controller to the sensor.
 */
typedef struct _Smsgs_configreqmsg_t
{
    /*! Command ID - 1 byte */
    Smsgs_cmdIds_t cmdId;
    /*! Reporting Interval */
    uint32_t reportingInterval;
    /*! Polling Interval */
    uint32_t pollingInterval;
    /*! Time now */
    uint32_t timeNow;
    /*! URL BLE  */
    uint8_t url[10];
} Smsgs_configReqMsg_t;

/*!
 Configuration Response message: sent from the sensor to the collector
 in response to the Configuration Request message.
 */
typedef struct _Smsgs_configrspmsg_t
{
    /*! Command ID - 1 byte */
    Smsgs_cmdIds_t cmdId;
    /*! Response Status - 2 bytes */
    Smsgs_statusValues_t status;
    /*! Type Node - 1 byte*/
    Smsgs_typeNode_t type;
    /*! Frame Control field - 2 bytes - bit mask of Smsgs_dataFields */
    uint16_t frameControl;
    /*! Reporting Interval - 4 bytes */
    uint32_t reportingInterval;
    /*! Polling Interval - 4 bytes */
    uint32_t pollingInterval;
    /*! Time now */
    uint32_t timeNow;
    /*! URL BLE  */
    uint8_t url[10];
    /*! BikeParking State - only if type is Smsgs_typeNode_parkingBike*/
    uint32_t bikeParkingState;
} Smsgs_configRspMsg_t;

/*!
 Tracking Request message: sent from controller to the sensor.
 */
typedef struct _Smsgs_trackingreqmsg_t
{
    /*! Command ID - 1 byte */
    Smsgs_cmdIds_t cmdId;
} Smsgs_trackingReqMsg_t;

/*!
 Tracking Response message: sent from the sensor to the collector
 in response to the Tracking Request message.
 */
typedef struct _Smsgs_trackingrspmsg_t
{
    /*! Command ID - 1 byte */
    Smsgs_cmdIds_t cmdId;
} Smsgs_trackingRspMsg_t;

/*!
 Toggle LED Request message: sent from controller to the sensor.
 */
typedef struct _Smsgs_toggleledreqmsg_t
{
    /*! Command ID - 1 byte */
    Smsgs_cmdIds_t cmdId;
} Smsgs_toggleLedReqMsg_t;

/*!
 Toggle LED Response message: sent from the sensor to the collector
 in response to the Toggle LED Request message.
 */
typedef struct _Smsgs_toggleledrspmsg_t
{
    /*! Command ID - 1 byte */
    Smsgs_cmdIds_t cmdId;
    /*! LED State - 0 is off, 1 is on - 1 byte */
    uint8_t ledState;
} Smsgs_toggleLedRspMsg_t;


/*!
 Temp Sensor Field
 */
typedef struct _Smsgs_tempsensorfield_t
{
    /*!
     Ambience Chip Temperature - each value represents a 0.01 C
     degree, so a value of 2475 represents 24.75 C.
     */
    int16_t ambienceTemp;
    /*!
     Object Temperature - each value represents a 0.01 C
     degree, so a value of 2475 represents 24.75 C.
     */
    int16_t objectTemp;
} Smsgs_tempSensorField_t;

/*!
 Message Statistics Field
 */
typedef struct _Smsgs_msgstatsfield_t
{
    /*! total number of join attempts (associate request sent) */
    uint16_t joinAttempts;
    /*! total number of join attempts failed */
    uint16_t joinFails;
    /*! total number of sensor data messages attempted. */
    uint16_t msgsAttempted;
    /*! total number of sensor data messages sent. */
    uint16_t msgsSent;
    /*! total number of tracking requests received */
    uint16_t trackingRequests;
    /*! total number of tracking response attempted */
    uint16_t trackingResponseAttempts;
    /*! total number of tracking response success */
    uint16_t trackingResponseSent;
    /*! total number of config requests received */
    uint16_t configRequests;
    /*! total number of config response attempted */
    uint16_t configResponseAttempts;
    /*! total number of config response success */
    uint16_t configResponseSent;
    /*!
     Total number of Channel Access Failures.  These are indicated in MAC data
     confirms for MAC data requests.
     */
    uint16_t channelAccessFailures;
    /*!
     Total number of MAC ACK failures. These are indicated in MAC data
     confirms for MAC data requests.
     */
    uint16_t macAckFailures;
    /*!
     Total number of MAC data request failures, other than channel access
     failure or MAC ACK failures.
     */
    uint16_t otherDataRequestFailures;
    /*! Total number of sync loss failures received for sleepy devices. */
    uint16_t syncLossIndications;
    /*! Total number of RX Decrypt failures. */
    uint16_t rxDecryptFailures;
    /*! Total number of TX Encrypt failures. */
    uint16_t txEncryptFailures;
    /*! Total number of resets. */
    uint16_t resetCount;
    /*!
     Assert reason for the last reset -  0 - no reason, 2 - HAL/ICALL,
     3 - MAC, 4 - TIRTOS
     */
    uint16_t lastResetReason;
    /*! Amount of time taken for node to join */
    uint16_t joinTime;
    /*! Delay between sending a packet and receiving an ack */
    uint16_t interimDelay;
} Smsgs_msgStatsField_t;

/*!
 Message Statistics Field
 */
typedef struct _Smsgs_configsettingsfield_t
{
    /*!
     Reporting Interval - in millseconds, how often to report, 0
     means reporting is off
     */
    uint32_t reportingInterval;
    /*!
     Polling Interval - in millseconds (32 bits) - If the sensor device is
     a sleep device, this states how often the device polls its parent for
     data. This field is 0 if the device doesn't sleep.
     */
    uint32_t pollingInterval;
} Smsgs_configSettingsField_t;

/*!
 Sensor Data message: sent from the sensor to the collector
 */
typedef struct _Smsgs_sensormsg_t
{
    /*! Command ID */
    Smsgs_cmdIds_t cmdId;
    /*! Extended Address */
    uint8_t extAddress[SMGS_SENSOR_EXTADDR_LEN];
    /*! Frame Control field - bit mask of Smsgs_dataFields */
    uint16_t frameControl;
    /*! Battery field */
    uint32_t battery;
    /*!
     Temp Sensor field - valid only if Smsgs_dataFields_tempSensor
     is set in frameControl.
     */
    Smsgs_tempSensorField_t tempSensor;
    /*!
     Message Statistics field - valid only if Smsgs_dataFields_msgStats
     is set in frameControl.
     */
    Smsgs_msgStatsField_t msgStats;
    /*!
     Configuration Settings field - valid only if
     Smsgs_dataFields_configSettings is set in frameControl.
     */
    Smsgs_configSettingsField_t configSettings;

} Smsgs_sensorMsg_t;



/*********
 Structures - Building blocks for the change url(over-the-air sensor messages)
 *********/

/*!
 Change URL message: sent from the collector to the sensor
 */
typedef struct _Smsgs_changebleurl_t
{
    /*! Command ID - 1 byte */
    Smsgs_cmdIds_t cmdId;
    /*! New URL - 10 bytes */
    uint8_t url[10];
} Smsgs_changeBleUrl_t;

/*!
 Change URL Response message: sent from the collector to the sensor
 */
typedef struct _Smsgs_changebleurlrsp_t
{
    /*! Command ID - 1 byte */
    Smsgs_cmdIds_t cmdId;
    /*! New URL - 10 bytes */
    uint8_t url[10];
} Smsgs_changeBleUrlRsp_t;



/*********
 Structures - Building blocks for the bikeParking control (over-the-air sensor messages)
 *********/


/*!
  Bike Parking State request message: sent from the collector to the sensor
 */
typedef struct _Smsgs_bikeparkingstatereq_t
{
    /*! Command ID - 1 byte */
    Smsgs_cmdIds_t cmdId;
} Smsgs_bikeParkingStateReqMsg_t;

/*!
 Bike Select request message: sent from the collector to the sensor
 */
typedef struct _Smsgs_bikeselectedreq_t
{
    /*! Command ID - 1 byte */
    Smsgs_cmdIds_t cmdId;
    /*! Bike Number - 1 byte*/
    uint8_t bikeNumber;
} Smsgs_bikeSelectReqMsg_t;

/*!
 Bike parking State or Bike select response message: sent from the sensor to the collector
 */
typedef struct _Smsgs_parkingstatersp_t
{
    /*! Command ID - 1 byte */
    Smsgs_cmdIds_t cmdId;
    /*! Bike Parking State - each bit represents a bike - 4 bytes*/
    uint32_t parkingState;
} Smsgs_parkingStateRspMsg_t;

/*
 * @}
*/

#ifdef __cplusplus
}
#endif

#endif /* SMGSS_H */

