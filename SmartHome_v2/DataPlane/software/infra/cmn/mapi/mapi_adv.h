/*******************************************************************************
    Description : MAPI library (Advanced configurations)

    This is the 2nd stage of the MAPI library where advanced configurations are
    provided to the user to control the behavior of the traffic. This is an
    optional stage and the user can skip this stage. 

    This stage demands more memory and processing power as the user can configure
    the policies for each MAPI ID. But it provides more control over the traffic
    and security. Enable only the required policies to save memory and processing
    power.

    It is recommneded to call this function in a separate thread/task to avoid slowing 
    down the 1st staqe, though it is not mandatory. In case if run as a separate
    thread/task, a buffer will be allocated between the 1st and 2nd stage to store the packets
    received. So it consumes little more memory, than directly running in the same context 
    of 1st stage.

*******************************************************************************/
#ifndef INCLUDE_MAPI_ADV_LIB_H__
#define INCLUDE_MAPI_ADV_LIB_H__

#include "mapi_internal.h"

typedef void (*mapi_adv_config_cb)(char *buffer, uint32_t buflen);

/**
 * @brief Structure to define security policies for a MAPI ID.
 *
 * This structure allows you to configure various security and filtering
 * options to control which packets the MAPI library will accept.
 */
typedef struct  {
    struct {
        uint8_t policy_enable : 1; /**< If set, enables the security policy for this MAPI ID. */
        uint8_t allow_all : 1; /**< If set, allows all packets to be accepted. */
        uint8_t deny_all : 1; /**< If set, denies all packets to be accepted. */
        uint8_t reserved : 5; /**< Reserved for future use. */
    } global_policy; /**< Global security policy. */
    uint16_t num_allowed_src_port_ranges; /**< The number of allowed source port ranges. */
    uint16_t **allowed_src_port_ranges;    /**< An array of source port ranges (each range is an array of 2 uint16_t: {start_port, end_port}). */
    uint16_t num_allowed_src_uids;         /**< The number of allowed source UIDs. */
    uint16_t *allowed_src_uids;           /**< An array of allowed source UIDs. */
    uint16_t num_allowed_msg_codes;        /**< The number of allowed message codes. */
    uint32_t *allowed_msg_codes;          /**< An array of allowed message codes. */
    uint32_t max_allowed_msg_size;         /**< The maximum allowed size of incoming messages. */
    // uint32_t max_packets_per_second; //For rate limiting, could be added later
} MAPI_USER_FILTERING_POLICY;

/**
 * @brief Structure to define traffic shaping policies for a MAPI ID.
 *
 * This structure allows you to configure various traffic shaping and QoS
 * options to control the rate at which packets are sent and received.
 */
typedef struct {
    struct {
        uint8_t policy_enable : 1; /**< If set, enables the traffic shaping policy for this MAPI ID. */
        uint8_t traffic_stop : 1; /**< If set, stops the traffic for this MAPI ID. */
        uint8_t traffic_start : 1; /**< If set, starts the traffic for this MAPI ID. */
        uint8_t reserved : 5; /**< Reserved for future use. */
    } global_policy; /**< Global traffic shaping policy. */
    uint32_t max_packets_per_second; /**< The maximum number of packets per second that can be sent or received. */
    uint32_t max_packet_size;        /**< The maximum size of packets that can be sent or received. */
    uint32_t max_packet_burst;       /**< The maximum number of packets that can be sent or received in a burst. */
} MAPI_USER_TRAFFIC_SHAPING_POLICY;

/**
 * @brief Structure to define security policies for a MAPI ID.
 * 
 * This structure allows you to configure various security
 * options to control which packets the MAPI library will accept.
 */
typedef struct {
    struct {
        uint8_t policy_enable : 1; /**< If set, enables the security policy for this MAPI ID. */
        uint8_t allow_all : 1; /**< If set, allows all packets to be accepted. */
        uint8_t deny_all : 1; /**< If set, denies all packets to be accepted. */
        uint8_t reserved : 5; /**< Reserved for future use. */
    } global_policy; /**< Global security policy. */    
    uint32_t secret_token; /**< The secret token to be used for secure communication. */
} MAPI_USER_SECURITY_POLICY;


/**
 * @brief Structure to define filters for monitoring packets.
 */
typedef struct {
    uint32_t dst_ip;          /**< Filter by destination IP address. */
    uint32_t src_ip;          /**< Filter by source IP address. */
    uint16_t dst_port;        /**< Filter by destination port. */
    uint16_t src_port;        /**< Filter by source port. */
    uint16_t dst_uid;         /**< Filter by destination UID. */
    uint16_t src_uid;         /**< Filter by source UID. */
    uint32_t messageCode;     /**< Filter by message code. */
    uint32_t max_payload_size; /**< Filter by maximum payload size. */
} MAPI_MONITORING_FILTERS;

/**
 * @brief Structure to define monitoring destination information.
 * Basiacally where to send the monitoring data.
 * If callback is provided, the data will be sent to the callback function. (local application)
 * For remote sending, make sure to set the callback function to NULL.
 */
typedef struct {
    uint32_t dst_ip;          /**< Destination IP address. */
    uint16_t dst_port;        /**< Destination port. */
    uint16_t dst_uid;         /**< Destination UID. */
    mapi_adv_config_cb rcv_cb;   /**< Callback function to receive the monitoring data. */
} MAPI_MONITORING_DEST_INFO;

/**
 * @brief Structure to define monitoring policies for a MAPI ID.
 *
 * This structure allows you to configure various monitoring
 * options to control the monitoring of packets sent and received.
 */
typedef struct {
    struct {
        uint8_t policy_enable : 1;          /**< If set, enables the monitoring policy for this MAPI ID. */
        uint8_t telemetry_enable : 1;       /**< If set, enables the telemetry monitoring for this MAPI ID. */
        uint8_t packet_capture_enable : 1;  /**< If set, enables the packet capture monitoring for this MAPI ID. */
        uint8_t monitor_all : 1;            /**< If set, monitors all packets sent and received. */
        uint8_t monitor_errors : 1;         /**< If set, monitors only error packets and dropped packets. */
        uint8_t reserved : 3;               /**< Reserved for future use. */
    } global_policy;                        /**< Global monitoring policy. */
    struct {
         MAPI_MONITORING_FILTERS *filters; /**< Filters for telemetry. */
         uint32_t export_frequency_mins;        /**< The frequency at which monitoring data is exported. This is in minutes */
         MAPI_MONITORING_DEST_INFO *dest_info; /**< Destination information for monitoring data. */
    } telemetry_policy; /**< Telemetry monitoring policy. */
    struct {
        uint8_t capture_header : 1; /**< If set, captures only the header of the packet. */
        uint8_t capture_all : 1; /**< If set, captures the entire packet. */
        MAPI_MONITORING_FILTERS *filters;     /**< Filters for packet capture. */
        uint16_t max_monitoring_time_sec;         /**< The maximum time for monitoring. This is in seconds */
        uint32_t max_monitoring_size;   /**< The maximum size of the monitoring buffer. */
        MAPI_MONITORING_DEST_INFO *dest_info; /**< Destination information for monitoring data. */
    } packet_capture_policy; /**< Packet capture monitoring policy. */
} MAPI_USER_MONITORING_POLICY;

typedef struct {
    MAPI_USER_FILTERING_POLICY *filtering_policy; /**< A pointer to filtering policy for this MAPI ID. */
    MAPI_USER_TRAFFIC_SHAPING_POLICY *traffic_shaping_policy; /**< A pointer to traffic shaping/qos policy for this MAPI ID. */
    MAPI_USER_SECURITY_POLICY *security_policy; /**< A pointer to security policy for this MAPI ID. */    
    MAPI_USER_MONITORING_POLICY *monitoring_policy; /**< A pointer to monitoring policy for this MAPI ID. */
} MAPI_USER_ADVANCED_CONFIG;

/*******************************************************************************/
/*                      Public functions                                       */
/*******************************************************************************/
/**
 * @brief Updates the advanced communication policy for a MAPI ID.
 *
 * This function allows you to dynamically change any or all of the 
 * advanced settings (filtering, traffic shaping, security, monitoring)
 * for an existing MAPI ID. 
 *
 * To change a specific setting, modify the corresponding member(s)
 * in the MAPI_USER_ADVANCED_CONFIG struct. Members that are not modified
 * will retain their current values.
 *
 * @param mid The MAPI ID.
 * @param new_policy A pointer to a MAPI_USER_ADVANCED_CONFIG struct 
 *                   containing the new settings.
 * @return MAPI_LIB_SUCCESS on success, an error code otherwise.
 */
MAPI_LIB_ERR mapi_update_comms_policy(mapiID mid, MAPI_USER_ADVANCED_CONFIG *new_policy);

/*******************************************************************************/
/*                      Private functions                                       */
/*******************************************************************************/
MAPI_USER_ADVANCED_CONFIG *__mapi_create_adv_config(mapiID mid, MAPI_USER_ADVANCED_CONFIG *user_config);
MAPI_USER_ADVANCED_CONFIG *__mapi_get_adv_config(mapiID mid);
void __mapi_delete_adv_config(mapiID mid);


#endif /* INCLUDE_MAPI_ADV_LIB_H__  */