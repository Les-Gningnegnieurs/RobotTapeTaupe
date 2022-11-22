#include "sensors.h"

int getSensorProximity(int id) {
    if ((id < 0) || (id > 3)) {
        #ifdef SENSOR_DEBUG_PRINT
            SERIAL_PRINTF("Invalid ID when calling getSensorProximity()");
        #endif
        return;
    }
    SERIAL_PRINTF("Valeur lue du capteur %i est %i", id, ROBUS_ReadIR(id))
    return ROBUS_ReadIR(id);
}