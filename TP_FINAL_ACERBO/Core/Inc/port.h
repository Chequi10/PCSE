#ifndef INC_PORT_H_
#define INC_PORT_H_

#include "stm32f4xx_hal.h"
#include "stdbool.h"

// MACROS para ser utilizados en la funciones del puerto

#define DIR_MAESTRO	        				0x68F
#define PUERTO_I2C	                   		I2C1
#define TAMANO_BUFFER(buffer)  				(sizeof(buffer)/sizeof(*(buffer)))
#define TAMANO_BUFFER_TX                      (TAMANO_BUFFER(buffer_tx) - 1)
#define TAMANO_BUFFER_RX                      TAMANO_BUFFER_TX

// Declaracion de un typedef para una mejor simplificacion de las lecturas de los datos del modulo

typedef bool bool_t;

// Declaraciones de los prototipos de las funciones del puerto

bool_t configuracion_i2c(void);
bool_t read_i2c(uint8_t i2c_addres, uint8_t reg_addres, uint8_t *buffer_rx, uint8_t buffer_rx_size);
bool_t write_i2c(uint8_t i2c_add, uint8_t *buffer_rx, uint16_t buffer_tx_size);
bool_t write_i2c_b(uint8_t I2c_add, uint8_t reg_addres, uint8_t reg_content);


#endif
