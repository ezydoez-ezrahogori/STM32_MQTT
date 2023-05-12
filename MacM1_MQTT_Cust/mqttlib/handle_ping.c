
#include "config.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#ifdef WITH_BROKER
#  include "mosquitto_broker_internal.h"
#endif

#include "mosquitto.h"
#include "logging_mosq.h"
#include "memory_mosq.h"
#include "messages_mosq.h"
#include "mqtt_protocol.h"
#include "net_mosq.h"
#include "packet_mosq.h"
#include "read_handle.h"
#include "send_mosq.h"
#include "util_mosq.h"

int handle__pingreq(struct mosquitto *mosq)
{
	assert(mosq);

	if(mosquitto__get_state(mosq) != mosq_cs_active){
		return MOSQ_ERR_PROTOCOL;
	}

#ifdef WITH_BROKER
	log__printf(NULL, MOSQ_LOG_DEBUG, "Received PINGREQ from %s", mosq->id);
#else
	log__printf(mosq, MOSQ_LOG_DEBUG, "Client %s received PINGREQ", mosq->id);
#endif
	return send__pingresp(mosq);
}

int handle__pingresp(struct mosquitto *mosq)
{
	assert(mosq);

	if(mosquitto__get_state(mosq) != mosq_cs_active){
		return MOSQ_ERR_PROTOCOL;
	}

	mosq->ping_t = 0; /* No longer waiting for a PINGRESP. */
#ifdef WITH_BROKER
	log__printf(NULL, MOSQ_LOG_DEBUG, "Received PINGRESP from %s", mosq->id);
#else
	log__printf(mosq, MOSQ_LOG_DEBUG, "Client %s received PINGRESP", mosq->id);
#endif
	return MOSQ_ERR_SUCCESS;
}

