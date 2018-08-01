#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdint.h>

void matrix()
{
uint8_t red[8] = {0x3C, 0x3C, 0xDB, 0xE7, 0xE7, 0xDB, 0x3C, 0x3C};
uint8_t green[8] = {0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00};
uint8_t blue[8] = {0xC3, 0xC3, 0x00, 0x00, 0x00, 0x00, 0xC3, 0xC3};
wiringPiSetup();
wiringPiSPISetup(0,500000);
uint8_t data[4];
int i = 0;
int k = 0;
for(k=0;k<100;k++){
 for ( i = 0; i<8 ; i++)
  {
   data[0] = ~red[i];
   data[1] = ~green[i];
   data[2] = ~blue[i];
   data[3] = (1 << i);
   wiringPiSPIDataRW(0,data,sizeof data);
   delay(1);
    }
  }
}
void matrix2()
{
uint8_t red[8] ={0xC0, 0xC0, 0x30, 0x30, 0x0C, 0x0C, 0x03, 0x03}; 
uint8_t green[8] = {0x03, 0x03, 0x0C, 0x0C, 0x30, 0x30, 0xC0, 0xC0}; 
uint8_t blue[8] = {0x3C, 0x3C, 0xC3, 0xC3, 0xC3, 0xC3, 0x3C, 0x3C}; 
wiringPiSetup();
wiringPiSPISetup(0,500000);
uint8_t data[4];
int i = 0;
int k = 0;
for(k=0;k<100;k++){
 for ( i = 0; i<8 ; i++)
  {
   data[0] = ~red[i];
   data[1] = ~green[i];
   data[2] = ~blue[i];
   data[3] = (1 << i);
   wiringPiSPIDataRW(0,data,sizeof data);
   delay(1);
    }
  }
}

void matrix3()
{
uint8_t red[8] = {0x00, 0x66, 0x66, 0x18, 0xDB, 0x42, 0x3C, 0x18};
uint8_t green[8] = {0x00, 0x42, 0x00, 0x18, 0xDB, 0x5A, 0x24, 0x00};
uint8_t blue[8] = {0x00, 0x66, 0x66, 0x18, 0xDB, 0x42, 0x7E, 0x66};
wiringPiSetup();
wiringPiSPISetup(0,500000);
uint8_t data[4];
int i = 0;
int k = 0;
for(k=0;k<100;k++){
 for ( i = 0; i<8 ; i++)
  {
   data[0] = ~red[i];
   data[1] = ~green[i];
   data[2] = ~blue[i];
   data[3] = (1 << i);
   wiringPiSPIDataRW(0,data,sizeof data);
   delay(1);
    }
  }
}

void matrix4()
{
uint8_t red[8] = {0x18, 0x24, 0x7E, 0xDB, 0x7E, 0x7E, 0x5A, 0x7E};
uint8_t green[8] = {0x18, 0x24, 0x7E, 0xDB, 0x24, 0x24, 0x5A, 0x7E};
uint8_t blue[8] = {0x00, 0x3C, 0x42, 0xDB, 0x24, 0x00, 0x5A, 0x24};
wiringPiSetup();
wiringPiSPISetup(0,500000);
uint8_t data[4];
int i = 0;
int k = 0;
for(k=0;k<100;k++){
 for ( i = 0; i<8 ; i++)
  {
   data[0] = ~red[i];
   data[1] = ~green[i];
   data[2] = ~blue[i];
   data[3] = (1 << i);
   wiringPiSPIDataRW(0,data,sizeof data);
   delay(1);
    }
  }
}

void main() 
{
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, ADS1115 I2C address is 0x48(72)
	ioctl(file, I2C_SLAVE, 0x48);

	// Select configuration register(0x01)
	// AINP = AIN0 and AINN = AIN1, +/- 2.048V
	// Continuous conversion mode, 128 SPS(0x84, 0x83)
	while (1){
	char config[3] = {0};
	config[0] = 0x01;
	config[1] = 0xD4;
	config[2] = 0x84;
	write(file, config, 3);
	sleep(1);

	char reg1[1] = {0x00};
	write(file, reg1, 1);
	char data[2]={0};
	if(read(file, data, 2) != 2){
	printf("Error: Input/Output Error \n");
		}
	else{
	int raw_adc = (data[0] * 256 + data[1]);
	if (raw_adc > 32767) {
		raw_adc -=65535;
		}
	printf("X-aixes: %d\n", raw_adc);
	if( raw_adc < 200 ){
	 matrix();
	}	
	elif( raw_adc > 32000) {
	 matrix2(); 
	 }
	};

	char config2[3] = {0};
	config2[0] = 0x01;
	config2[1] = 0xE4;
	config2[2] = 0x84;
	write(file, config2, 3);
	sleep(1);

	char reg2[2] = {0x00};
	write(file, reg2, 2);
	char data2[2]={0};
	if(read(file, data2, 2) != 2){
	printf("Error: Input/Output Error \n");
	}
	else{
	int raw_adc2 = (data2[0] * 256 + data2[1]);
	if (raw_adc2 > 32767){
	raw_adc2 -=65535;
	}
	printf("Y-aixes: %d\n", raw_adc2);
        if( raw_adc2 > 32000 ){
	 matrix3();
	}
	elif( raw_adc2 < 200){
	 matrix4(); 
	}
	}
	printf("---------------------------------------------------------------------\n");
	};
};
}
