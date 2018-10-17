#include <SoftwareSerial.h>
#include <Servo.h>


#define MOTOR_PIN    9
#define PWR_UP    7
#define STATE_PIN 10


Servo myservo;

String inputString = "";
boolean stringComplete = false;
boolean ledState=0;
boolean soundPlaying=false;

String s;

String pass="";

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(STATE_PIN, INPUT);
  pinMode(PWR_UP, OUTPUT);

  if(!digitalRead(STATE_PIN))
  {
    digitalWrite(PWR_UP, LOW);
    delay(100);
    digitalWrite(PWR_UP, HIGH);
    delay(2000);
    digitalWrite(PWR_UP, LOW);
    delay(5000);
  }

  
Serial.begin(115200);
myservo.attach(MOTOR_PIN);

inputString.reserve(200);

Serial.println("AT");
delay(500);
Serial.println("AT+QTONEDET=4,1,3,3,65536");
delay(500);
Serial.println("AT+QTONEDET=1");
delay(500);
Serial.println("AT+QSFR=7");
delay(500);
Serial.println("AT+QTDMOD=1,0");
delay(500);

digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{

}

void serialEvent() {

  
  
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {

      if(inputString.indexOf("RING")>-1)
      {
        Serial.println("ATA");
        delay(500);
        soundPlaying=true;
        Serial.println("AT+QPRESBG=1,2,6,7,1");
        pass="";
      }
      else if(inputString.indexOf("+QPRESBG:")>-1)
      {
        digitalWrite(LED_BUILTIN, LOW);
        soundPlaying=false;
      }
      else if(inputString.indexOf("+QTONEDET:")>-1)
      {
        digitalWrite(LED_BUILTIN, HIGH);
        if(!soundPlaying)
        {
          if(inputString.indexOf("49")>-1)
          {
           
             pass+="1";
          }
          else if(inputString.indexOf("50")>-1)
          {
             pass+="2";
          }
          else if(inputString.indexOf("51")>-1)
          {
             pass+="3";
          }
          else if(inputString.indexOf("52")>-1)
          {
             pass+="4";
          }
          else if(inputString.indexOf("53")>-1)
          {
             pass+="5";
          }
          else if(inputString.indexOf("54")>-1)
          {
             pass+="6";
          }
          else if(inputString.indexOf("55")>-1)
          {
             pass+="7";
          }
          else if(inputString.indexOf("35")>-1)
          {
             
             if(pass=="3214")
             {
                Serial.println("AT+QPRESBG=1,1,6,7,1");
                myservo.write(30);
                delay(500);
                myservo.write(120);
                delay(500);
                myservo.write(30);
             }
             else
             {
              Serial.println("AT+QPRESBG=1,3,6,7,1");
             }
             pass="";
          }
        }
      }

      inputString="";
    }
  }
}
