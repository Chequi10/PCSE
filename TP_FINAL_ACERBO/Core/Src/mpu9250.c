
#include "mpu9250.h"

static uint8_t mag_sensibilidad[3]={0};
VALIDACION_CONFIG inicializacion;

//Declaracion de las funciones, antes definidas en el mpu9250.h

VALIDACION_CONFIG modulo_inicializacion()
{

	//Inicializacion del puerto I2C
	configuracion_i2c();
	uint8_t buffer;
	uint8_t sensibilidad[3] = {0};

	write_i2c_b(MPU_ADDRES,PWR_MGMNT_1,INIT_BYTE_107); //Se configura el registro POWER MANAGEMENT 1,  0b00000001 se configura el PLL
	read_i2c(MPU_ADDRES,PWR_MGMNT_1,&buffer,1); //Validar que se escribió correctamente

	if (buffer == INIT_BYTE_107)
	{
		inicializacion.CLOCK = true;
	}
	else
	{
		inicializacion.CLOCK = false;
	}


	write_i2c_b(MPU_ADDRES, ACCEL_CONFIG, INIT_BYTE_28); //Se configura el registro de escala de aceleracion ACCEL_CONFIG con 0b00001000 +-4g
	read_i2c(MPU_ADDRES,ACCEL_CONFIG,&buffer,1); //Validar que se escribió correctamente

	if (buffer == INIT_BYTE_28)
	{
		inicializacion.ACELEROMETRO = true;
	}
	else
	{

		inicializacion.ACELEROMETRO = false;
	}

	write_i2c_b(MPU_ADDRES, GYRO_CONFIG, INIT_BYTE_27); //Se configura el registro de escala de giroscopo GYRO_CONFIG con 0b00001000 +500dps
	read_i2c(MPU_ADDRES,GYRO_CONFIG,&buffer,1); //Validar que se escribió correctamente

	if (buffer == INIT_BYTE_27)
	{

		inicializacion.GIROSCOPO = true;
	}
	else
	{
		inicializacion.GIROSCOPO = false;
	}


	write_i2c_b(MPU_ADDRES,ACCEL_CONFIG_FILTER, INIT_BYTE_29); //Se configura el filtro del acelerómetro
	read_i2c(MPU_ADDRES,ACCEL_CONFIG_FILTER,&buffer,1); //Validar que se escribió correctamente

	if (buffer == INIT_BYTE_29)
	{
		inicializacion.FILTRO_ACEL = true;

	}
	else
	{
		inicializacion.FILTRO_ACEL = false;

	}


	write_i2c_b(MPU_ADDRES,GYRO_CONFIG_FILTER, INIT_BYTE_26); //Se configura el filtro del giroscopo
	read_i2c(MPU_ADDRES,GYRO_CONFIG_FILTER,&buffer,1); //Validar que se escribió correctamente

	if (buffer == INIT_BYTE_26)
	{
		inicializacion.FILTRO_GIRO = true;

	}
	else
	{
		inicializacion.FILTRO_GIRO = false;
	}



	write_i2c_b(MPU_ADDRES, CTRL_MASTER_I2C, INIT_BYTE_106); // Deshabilita el Master Mode del bus I2C
	read_i2c(MPU_ADDRES,CTRL_MASTER_I2C,&buffer,1); ////Validar que se escribió correctamente

	if (buffer == INIT_BYTE_106)
	{
		inicializacion.CONTROL = true;

	}
	else
	{
		inicializacion.CONTROL = false;

	}


	write_i2c_b(MPU_ADDRES, BYPASS_CONFIG_I2C, INIT_BYTE_55); //Se desahbilita el modo Bypass y deshabilita la comunicación por interrupciones
	read_i2c(MPU_ADDRES,BYPASS_CONFIG_I2C,&buffer,1); ///Validar que se escribió correctamente

	if (buffer == INIT_BYTE_55)
	{
		inicializacion.BYPASS = true;

	}
	else
	{
		inicializacion.BYPASS = false;

	}


	write_i2c_b(MAG_ID, MAG_CTRL_CONFIG, MAG_FUSE_MODE); //Se configura el magnetómetro en modo FUSE para poder leerlo
	HAL_Delay(1000);
	read_i2c(MAG_ID,MAG_CTRL_CONFIG,&buffer,1); ///Validar que se escribió correctamente

	if (buffer == MAG_FUSE_MODE)
	{

		inicializacion.MAGNETOMETRO_ENE = true;

	}
	else
	{
		inicializacion.MAGNETOMETRO_ENE = false;

	}


	read_i2c(MAG_ID, MAG_ASAXYZ, sensibilidad, 3); //Se leen los parámetrosde sensibilidad del magnetómetro

	mag_sensibilidad[0] = (sensibilidad[0]-128)*0.5/128+1;
	mag_sensibilidad[1] = (sensibilidad[1]-128)*0.5/128+1;
	mag_sensibilidad[2] = (sensibilidad[2]-128)*0.5/128+1;


	write_i2c_b(MAG_ID, MAG_CTRL_CONFIG, MAG_PWR_DWN_MODE);
	HAL_Delay(1000);
	read_i2c(MAG_ID, MAG_CTRL_CONFIG, &buffer,1);

	if (buffer == MAG_PWR_DWN_MODE)
	{
		inicializacion.SENSIBILIDAD_MAG = true;

	}
	else
	{
		inicializacion.SENSIBILIDAD_MAG = false;

	}


	write_i2c_b(MAG_ID, MAG_CTRL_CONFIG, MAG_CONT2_MODE); //Configura el magnetómetro para medición continua
	HAL_Delay(1000);
	read_i2c(MAG_ID,MAG_CTRL_CONFIG,&buffer,1); ////Validar que se escribió correctamente

	if (buffer == MAG_CONT2_MODE)
	{
		inicializacion.MAGNETOMETRO_SET = true;

	}
	else
	{
		inicializacion.MAGNETOMETRO_SET = false;

	}


	read_i2c(MPU_ADDRES, WHO_AM_I, &buffer,1); //Valida la dirección del registro

	if (buffer == 0x71)
	{
		inicializacion.QUIEN_SOY = true;

	}
	else
	{
		inicializacion.QUIEN_SOY = false;

	}
	return inicializacion;
}


DATOS modulo_datos()
{
	uint8_t ACEL_Y_GIRO_DATA[14] = {0};
	int16_t DATA[10]={0};
	DATOS datos;
	uint8_t MAG_STATUS = 0; //estado de los datos en el magnetómetro 0 = normal ; 1 = data is rEady
	uint8_t MAG_DATA[7] = {0};

	read_i2c(MPU_ADDRES, ACCEL_X_High, ACEL_Y_GIRO_DATA, 14);

	DATA[0] = (ACEL_Y_GIRO_DATA[0]<<8)|(ACEL_Y_GIRO_DATA[1]); //acc_x
	DATA[1] = (ACEL_Y_GIRO_DATA[2]<<8)|(ACEL_Y_GIRO_DATA[3]); //acc_y
	DATA[2] = (ACEL_Y_GIRO_DATA[4]<<8)|(ACEL_Y_GIRO_DATA[5]); //acc_z
	DATA[3] = (ACEL_Y_GIRO_DATA[6]<<8)|(ACEL_Y_GIRO_DATA[7]); //temperature
	DATA[4] = (ACEL_Y_GIRO_DATA[8]<<8)|(ACEL_Y_GIRO_DATA[9]); //gyro_x
	DATA[5] = (ACEL_Y_GIRO_DATA[10]<<8)|(ACEL_Y_GIRO_DATA[11]); //gyro_y
	DATA[6] = (ACEL_Y_GIRO_DATA[12]<<8)|(ACEL_Y_GIRO_DATA[13]); //gyro_z

	read_i2c(MAG_ID, MAG_READ_REG, &MAG_STATUS, 1);

	if ((MAG_STATUS & MAG_MASK ) == MAG_DATA_READY)
	{
		read_i2c(MAG_ID, MAG_HXL_TO_HZH_REG, MAG_DATA,7);

		if (!(MAG_DATA[6] & MAG_OVERFLOW))
		{
			DATA[7] = (MAG_DATA[0] | (MAG_DATA[1]<<8));
			DATA[8] = (MAG_DATA[2] | (MAG_DATA[3]<<8));
			DATA[9] = (MAG_DATA[4] | (MAG_DATA[5]<<8));
		}
	}

	datos.xACELEROMETRO  = (float)DATA[0];
	datos.yACELEROMETRO  = (float)DATA[1];
	datos.zACELEROMETRO  = (float)DATA[2];
	datos.TEMPERATURA     = (float)DATA[3];
	datos.xGIROSCOPO = (float)DATA[4];
	datos.yGIROSCOPO = (float)DATA[5];
	datos.zGIROSCOPO = (float)DATA[6];
	datos.xMAGNETOMETRO  = (float)DATA[7];
	datos.yMAGNETOMETRO  = (float)DATA[8];
	datos.zMAGNETOMETRO  = (float)DATA[9];

	return datos;
}


