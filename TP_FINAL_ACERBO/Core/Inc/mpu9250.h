#ifndef INC_MPU9250_H_
#define INC_MPU9250_H_

// Includes
#include"port.h"

	// Definción de MACROS

	// MACROS De los registros para el acelerómetro y el giroscopo
	#define MPU_ADDRES            0x68 //0b1101000
	#define GYRO_CONFIG_FILTER    26   //0x1A
	#define GYRO_CONFIG           27   //0x1B
	#define ACCEL_CONFIG          28
	#define ACCEL_CONFIG_FILTER   29   //0x1D
	#define BYPASS_CONFIG_I2C     55   //0x37
    #define ACCEL_X_High          59   //Bits más significativos del acelerómetro
	#define CTRL_MASTER_I2C       106  //0x6A
    #define PWR_MGMNT_1           107  //0x6B
	#define WHO_AM_I              117

	//MACROS de Seteos de bits para los registros de Accel y Gyro

	#define INIT_BYTE_26    0b00000101
    #define INIT_BYTE_27    0b00001000
    #define INIT_BYTE_28    0b00001000
	#define INIT_BYTE_29    0b00000101
    #define INIT_BYTE_104   0b00000111
    #define INIT_BYTE_106   0b00000001
	#define INIT_BYTE_107   0b00000001   //0b00000001
    #define INIT_BYTE_55    0b00000000

	// MACROS De los registros para el Magnetómetro
	#define MAG_ID               0x00 //id is: 0x48
	#define MAG_CTRL_CONFIG      10   //0x0A
	#define MAG_ASAXYZ           16   //0x10
	#define MAG_READ_REG         2    //0x02
	#define MAG_OVERFLOW         0x9

    //MACROS de Seteos de bits para los registros del Magnetómetro
	#define MAG_PWR_DWN_MODE     0b00000000 //Power-down mode
	#define MAG_FUSE_MODE        0b00011111 //fuse mode
	#define MAG_CONT2_MODE       0b00010110 //CONTINUOUS mode 2 en 16 bits
	#define MAG_DATA_READY       0x01
	#define MAG_HXL_TO_HZH_REG   0x03
	#define MAG_MASK             0x01

	// Declaracion de estructuras para simplificar la lectura de los datos del Modulo

	typedef struct {
		bool_t CLOCK;
		bool_t ACELEROMETRO;
		bool_t GIROSCOPO;
		bool_t FILTRO_ACEL;
		bool_t FILTRO_GIRO;
		bool_t CONTROL;
		bool_t BYPASS;
		bool_t MAGNETOMETRO_ENE;
		bool_t SENSIBILIDAD_MAG;
		bool_t MAGNETOMETRO_SET;
		bool_t QUIEN_SOY;
	}VALIDACION_CONFIG;

	typedef struct {
		float xACELEROMETRO;
		float yACELEROMETRO;
		float zACELEROMETRO;
		float TEMPERATURA;
		float xGIROSCOPO;
		float yGIROSCOPO;
		float zGIROSCOPO;
		float xMAGNETOMETRO;
		float yMAGNETOMETRO;
		float zMAGNETOMETRO;
	}DATOS;

	// Declaración de los prototipos de las Funciones
	VALIDACION_CONFIG modulo_inicializacion();
	DATOS modulo_datos();

#endif
