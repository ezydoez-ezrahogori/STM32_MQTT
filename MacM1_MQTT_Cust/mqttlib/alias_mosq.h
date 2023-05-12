

#ifndef ALIAS_MOSQ_H
#define ALIAS_MOSQ_H

#include "mosquitto_internal.h"

int alias__add(struct mosquitto *mosq, const char *topic, uint16_t alias);
int alias__find(struct mosquitto *mosq, char **topic, uint16_t alias);
void alias__free_all(struct mosquitto *mosq);

#endif
