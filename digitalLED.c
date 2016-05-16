#include <wiringPi.h>
#include <stdio.h>

#define DIGITAL_A 0
#define DIGITAL_B 1
#define DIGITAL_C 2
#define DIGITAL_D 3
#define DIGITAL_E 4
#define DIGITAL_F 5
#define DIGITAL_G 6
#define DIGITAL_DP 21
#define DIGITAL_SEG1 22
#define DIGITAL_SEG2 23
#define DIGITAL_SEG3 24
#define DIGITAL_SEG4 25

void init_digitalled(void)
{
  digitalWrite(DIGITAL_A,LOW);
  digitalWrite(DIGITAL_B,LOW);
  digitalWrite(DIGITAL_C,LOW);
  digitalWrite(DIGITAL_D,LOW);
  digitalWrite(DIGITAL_E,LOW);
  digitalWrite(DIGITAL_F,LOW);
  digitalWrite(DIGITAL_G,LOW);
  digitalWrite(DIGITAL_DP,LOW);
  digitalWrite(DIGITAL_SEG1,HIGH);
  digitalWrite(DIGITAL_SEG2,HIGH);
  digitalWrite(DIGITAL_SEG3,HIGH);
  digitalWrite(DIGITAL_SEG4,HIGH);
}

/*
int mynumber = 0;

void add_by_self()
{
  for (mynumber = 0; mynumber <= 1000; mynumber++)
  {
      printf("add by myself: %d\n", mynumber);
  };
}
*/

void LED_ALL_OFF(void)
{
 delay(3);
 digitalWrite(DIGITAL_SEG1,HIGH);
 digitalWrite(DIGITAL_SEG2,HIGH);
 digitalWrite(DIGITAL_SEG3,HIGH);
 digitalWrite(DIGITAL_SEG4,HIGH);
}

const char lednumber[10]=
{
	0xfc, //0
	0x60, //1
	0xda, //2
	0xf0, //3
	0x66, //4
	0xb6, //5
	0xfe, //6
	0xe0, //7
	0xff, //8
	0xf6  //9
};

void light_led(int x)
{
  digitalWrite(DIGITAL_A, (lednumber[x] & 0x80));
  digitalWrite(DIGITAL_B, (lednumber[x] & 0x40));
  digitalWrite(DIGITAL_C, (lednumber[x] & 0x20));
  digitalWrite(DIGITAL_D, (lednumber[x] & 0x10));
  digitalWrite(DIGITAL_E, (lednumber[x] & 0x08));
  digitalWrite(DIGITAL_F, (lednumber[x] & 0x04));
  digitalWrite(DIGITAL_G, (lednumber[x] & 0x02));
  digitalWrite(DIGITAL_DP, (lednumber[x] & 0x01));
}

void display_led(int number)
{
  number=number%10000;
  printf("number is %d",number);

  int led1,led2,led3,led4;
  if(number/1000)
  {
  led1 = number/1000;
  number = number%1000;
  }
  else if(number/100)
  {
  led2 = number/100;
  number = number%100;
  }
  else if(number/10)
  {
  led3 = number/10;
  number = number%10;
  }
  else if(number/1)
  {
  led4 = number/1;
  number = number%1;
  }

  printf("led1=%d",led1);
  printf("led2=%d",led2);
  printf("led3=%d",led3);
  printf("led4=%d",led4);
  delay(2000);
  light_led(led1);
  digitalWrite(DIGITAL_SEG1,LOW);
  delay(2);
  digitalWrite(DIGITAL_SEG1,HIGH);
  light_led(led2);
  digitalWrite(DIGITAL_SEG2,LOW);
  delay(2);
  digitalWrite(DIGITAL_SEG2,HIGH);

  light_led(led3);
  digitalWrite(DIGITAL_SEG3,LOW);
  delay(2);
  digitalWrite(DIGITAL_SEG3,HIGH);

  light_led(led4);
  digitalWrite(DIGITAL_SEG4,LOW);
  delay(2);
  digitalWrite(DIGITAL_SEG4,HIGH);
}

int main(void)
{
  wiringPiSetup();
  pinMode(DIGITAL_A,OUTPUT);
  pinMode(DIGITAL_B,OUTPUT);
  pinMode(DIGITAL_C,OUTPUT);
  pinMode(DIGITAL_D,OUTPUT);
  pinMode(DIGITAL_E,OUTPUT);
  pinMode(DIGITAL_F,OUTPUT);
  pinMode(DIGITAL_G,OUTPUT);
  pinMode(DIGITAL_DP,OUTPUT);
  pinMode(DIGITAL_SEG1,OUTPUT);
  pinMode(DIGITAL_SEG2,OUTPUT);
  pinMode(DIGITAL_SEG3,OUTPUT);
  pinMode(DIGITAL_SEG4,OUTPUT);
  init_digitalled();
  for(;;)
  {
  printf("number is 123");
  display_led(2016);
  delay(3);
  }
}

