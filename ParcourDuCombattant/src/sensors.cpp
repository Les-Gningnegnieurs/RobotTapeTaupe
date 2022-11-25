#include "sensors.h"

int getSensorProximity(int id) {
    if ((id < 0) || (id > 3)) {
        #ifdef SENSOR_DEBUG_PRINT
            SERIAL_PRINTF("Invalid ID when calling getSensorProximity()\n");
        #endif
        return;
    }
    #ifdef SENSOR_DEBUG_PRINT
        SERIAL_PRINTF("Valeur lue du capteur %i est %i\n", id, ROBUS_ReadIR(id));
    #endif
    return ROBUS_ReadIR(id);
}