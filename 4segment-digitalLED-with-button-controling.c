#include <wiringPi.h>
#include <stdio.h>

/* Define some parameters for GPIO pins */
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
#define BUTTONA 27
#define BUTTONB 26

int x;
int i;

const char lednumber[10]=
{
        0xfc, //0
        0x60, //1
        0xda, //2
        0xf2, //3
        0x66, //4
        0xb6, //5
        0xbe, //6
        0xe0, //7
        0xfe, //8
        0xf6  //9
};

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

void display_led(int num)
{
  int number = num;
  int led1 = 0;
  int led2 = 0;
  int led3 = 0;
  int led4 = 0;

  led4 = number%10;
  led3 = number/10%10;
  led2 = number/100%10;
  led1 = number/1000%10;

  light_led(led1);
  digitalWrite(DIGITAL_SEG1,LOW);
  delay(1);
  digitalWrite(DIGITAL_SEG1,HIGH);

  light_led(led2);
  digitalWrite(DIGITAL_SEG2,LOW);
  delay(1);
  digitalWrite(DIGITAL_SEG2,HIGH);

  light_led(led3);
  digitalWrite(DIGITAL_SEG3,LOW);
  delay(1);
  digitalWrite(DIGITAL_SEG3,HIGH);

  light_led(led4);
  digitalWrite(DIGITAL_SEG4,LOW);
  delay(1);
  digitalWrite(DIGITAL_SEG4,HIGH);
}

void init_all(void)
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
  pinMode(BUTTONA,INPUT);
  pinMode(BUTTONB,INPUT);
}

int main()
{
  init_all();
  init_digitalled();
  for(;;)
  {
       display_led(i);
    if(digitalRead(BUTTONA) == 0 || digitalRead(BUTTONB) == 0)
    {
       for(x=0;x<=20;x++)
       {
       display_led(i);
       };

       if(digitalRead(BUTTONA) == 0)
       {
          printf("BottonA is pressed! and you press %d times\n", i++);
       };

       if(digitalRead(BUTTONB) == 0)
       {
         if (i>0)
          {
             printf("ButtonB was pressed, and you have been pressed %d times\n", i--);
          };
       };
    };
  };
}


