/*
  Software serial multple serial test

  Receives from the hardware serial, sends to software serial.
  Receives from software serial, sends to hardware serial.

  The circuit:
   RX is digital pin 10 (connect to TX of other device)
   TX is digital pin 11 (connect to RX of other device)

  Note:
  Not all pins on the Mega and Mega 2560 support change interrupts,
  so only the following can be used for RX:
  10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

  Not all pins on the Leonardo support change interrupts,
  so only the following can be used for RX:
  8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

  created back in the mists of time
  modified 25 May 2012
  by Tom Igoe
  based on Mikal Hart's example

  This example code is in the public domain.

*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // RX, TX
int soundsensor = A0;
int redpin = 5;
int bluepin = 9;
int greenpin = 6;


//int colorr=0;
//int redd=0,greenn=0,bluee=0;

int color = 0;                                  // color value defines which color is selected
int red = 1, blue = 2, pink = 3, green = 4, cyan = 5;

//int light[10][3]={{255,0,0},{150,150,0},{0,255,0},{0,255,100},{0,100,255},{0,0,255},{100,100,100},{200,200,200},{100,0,200},{255,0,100}};

void setup() {
  pinMode(soundsensor, INPUT);
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}
int x = 0;
void loop() { // run over and over

  while (mySerial.available()) 
  {
    x = mySerial.read() - '0';

    Serial.println(x);

        if (x == 1)
        {
          rgb(cyan);
        }


        if (x == 2)
        {

          color++;
          rgb(color);
              if (color == 7)
                color = 1;

          fade();
    }

      if (x == 3)
      {
         color++;
        rgb(color);
        delay(3000);
            if (color == 6)
              color = 1;
      }

      if (x == 4)
      {
        color = 1;
        rgb(color);
      }
  
    

      if (x == 5)
      {
         rgb(6);
      }
  

       else  if (x == 6)
      {   
         digitalWrite(greenpin, LOW);
         digitalWrite(redpin, LOW);
         digitalWrite(bluepin, LOW);

         color = 0;
      }

  }

  if (x == 2)
  {
    fade();
  }


  if (x == 4)
  {
    color++;
    rgb(color);
    delay(2000);
    if (color == 6)
      color = 1;
  }

}


void fade()
{

  for (int i = 200; i > 0; i--)
  {
    if (mySerial.available())
      break;

    if (color == red)
      analogWrite(redpin, i);

    else if (color == green)
      analogWrite(greenpin, i);

    else if (color == blue)
      analogWrite(bluepin, i );

    else if (color == pink)
    {
      analogWrite(redpin, i );
      analogWrite(bluepin, i * 0.3);
    }
    else if (color == cyan)
    {
      analogWrite(greenpin, i);
      analogWrite(bluepin, i);
    }

      
   else if (color == 6)
  {
    analogWrite(greenpin, i * 0.2);
    analogWrite(redpin, i);
  }

    for (int j = 0; j < 15; j++)
    {
      delay(1);
      if (mySerial.available())
        break;
    }
  }

  for (int i = 0; i < 200; i++)
  {
    if (mySerial.available())
      break;

    if (color == red)
      analogWrite(redpin, i);

    else if (color == green)
      analogWrite(greenpin, i);

    else if (color == blue)
      analogWrite(bluepin, i );

    else if (color == pink)
    {
      analogWrite(redpin, i );
      analogWrite(bluepin, i * 0.8);
    }
    else if (color == cyan)
    {
      analogWrite(greenpin, i * 0.5);
      analogWrite(bluepin, i);
    }

   else if (color == 6)
  {
    analogWrite(greenpin, i * 0.2);
    analogWrite(redpin, i);
  }

    for (int j = 0; j < 15; j++)
    {
      if (mySerial.available())
        break;

      delay(1);
    }
  }


}


void rgb(int color)
{
  digitalWrite(greenpin, LOW);
  digitalWrite(redpin, LOW);
  digitalWrite(bluepin, LOW);

  if (color == red)
    digitalWrite(redpin, HIGH);

  else if (color == blue)
    analogWrite(bluepin, 150 );

  else if (color == pink)
  {
    digitalWrite(redpin, HIGH );
    analogWrite(bluepin, 30);
  }

  else if (color == green)
    digitalWrite(greenpin, HIGH);

  else if (color == cyan)
  {
    analogWrite(greenpin, 255);
    analogWrite(bluepin, 50);
  }
  else if (color == 6)
  {
    analogWrite(greenpin, 50);
    analogWrite(redpin, 255);
  }
}



