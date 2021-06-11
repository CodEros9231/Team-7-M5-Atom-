/*
    Description: 
    Use ATOM Socket to monitor the socket power, press the middle button of ATOM to switch the socket power on and off.
    Connect to the AP hotspot of the device and access 192.168.4.1 to wirelessly control the socket power and view the power voltage, current and power information.
*/

#include "M5Atom.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "index.h"

const char* ssid = "Team7";
const char* password = "assignment2";

int minute, ActivePower = 0;
float Current = 0;

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", html);
}

#define RXD 22
#define RELAY 23


bool RelayFlag = false;

//FOR TIMER 1
int hourTimer1 = 0;
int minuteTimer1 = 0;
int secondTimer1 = 0;
double totalTime1 = 0;
double fracTime1 = 0;
bool initiateDisplay1 = true;
bool timerSet1 = false;
bool timeSelect = false;
bool snoozeTimer1 = true;

unsigned long currentMillisCount1 = 0, previousMillisCount1 = 0;
unsigned long currentMillisCount2 = 0, previousMillisCount2 = 0;

//FOR TIMER 2
int hourTimer2 = 0;
int minuteTimer2 = 0;
int secondTimer2 = 0;
double totalTime2 = 0;
double fracTime2 = 0;
bool initiateDisplay2 = true;
bool timerSet2 = false;
bool timeSelect2 = false;
bool snoozeTimer2 = true;


String DataCreate() {
    String RelayState = (RelayFlag)?"on":"off";
    String Data = String(hourTimer1)+"#"+String(minuteTimer1)+"#"+String(secondTimer1)+"#"+String(hourTimer2)+"#"+String(minuteTimer2)+"#"+String(secondTimer2);
    return Data;
}

extern const unsigned char image_hour[77];
extern const unsigned char image_hourB[122];
extern const unsigned char image_secondB[122];
extern const unsigned char image_minute[77];
extern const unsigned char image_minuteB[122];
extern const unsigned char image_confirm[77];
extern const unsigned char image_num1W[77];
extern const unsigned char image_num2W[77];
extern const unsigned char image_num3W[77];
extern const unsigned char image_num4W[77];
extern const unsigned char image_num5W[77];
//Links all LED data for each number and symbol
extern const unsigned char image_num0B[122];
extern const unsigned char image_num1B[122];
extern const unsigned char image_num2B[122];
extern const unsigned char image_num3B[122];
extern const unsigned char image_num4B[122];
extern const unsigned char image_num5B[122];
extern const unsigned char image_num6B[122];
extern const unsigned char image_num7B[122];
extern const unsigned char image_num8B[122];
extern const unsigned char image_num9B[122];

bool IMU6886Flag = false;
bool atomState = false;
bool modeState = false;
int optionsCTR = 0;
int unitCTR = 0;

double start, finished, elapsed;
double pitch, roll;
unsigned long intervalTime = 0;
bool resetInterval = false;


bool hourloop = false;
bool minuteloop = false;
bool secondloop = false;

int interval=1000,x_1=1;
int y_1=1,x2=0,y2=4,x3=4;
unsigned long previousMillis = millis(),currentMillis;
int patternarray[16]={1,0,5,10,15,20,21,22,23,24,19,14,9,4,3,2};
bool newTime1 = false, newTime2 = false;

//double currentTime, lastUpdateTime, elapsed;
unsigned long currentTime=0;

void delayInterval(int num)
{ 
  currentTime=millis();
  while(millis()<(currentTime+num))
   {
      //do nothing
   }
}

//displays the unit in the tens place
void displayTime(int timer)
{
          int Tens = 0;
          int Ones = 0;
          //determine number in the tens place
            Tens = (timer / 10) % 10;
            Ones = timer - (Tens * 10);


            //display number in the tens place
            switch(Tens)
            {
              case 0:
              {
                  //if less than 10, display nothing
                  break;
              }

              case 1: //display 1
              {
                  M5.dis.animation((uint8_t *)image_num1B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 2: //display 2
              {
                  M5.dis.animation((uint8_t *)image_num2B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 3: //display 3
              {
                  M5.dis.animation((uint8_t *)image_num3B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 4: //display 4
              {
                  M5.dis.animation((uint8_t *)image_num4B, 150, LED_DisPlay::kMoveLeft, 20);
                 
                  break;
              }
              case 5: //display 5
              {
                  M5.dis.animation((uint8_t *)image_num5B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 6: //display 6
              {
                  M5.dis.animation((uint8_t *)image_num6B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 7: //display 7
              {
                  M5.dis.animation((uint8_t *)image_num7B, 150, LED_DisPlay::kMoveLeft, 20);
                
                  break;
              }
              case 8: //display 8
              {
                  M5.dis.animation((uint8_t *)image_num8B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 9: //display 9
              {
                  M5.dis.animation((uint8_t *)image_num9B, 150, LED_DisPlay::kMoveLeft, 20);
                 
                  break;
              }
            }
            delayInterval(700);
            M5.update();

            switch(Ones)
            {
              case 0: //display 0
              {
                  M5.dis.animation((uint8_t *)image_num0B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
      
              case 1: //display 1
              {
                  M5.dis.animation((uint8_t *)image_num1B, 150, LED_DisPlay::kMoveLeft, 20);
                 
                  break;
              }
              case 2: //display 2
              {
                  M5.dis.animation((uint8_t *)image_num2B, 150, LED_DisPlay::kMoveLeft, 20);
                 
                  break;
              }
              case 3: //display 3
              {
                  M5.dis.animation((uint8_t *)image_num3B, 150, LED_DisPlay::kMoveLeft, 20);
               
                  break;
              }
              case 4: //display 4
              {
                  M5.dis.animation((uint8_t *)image_num4B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 5: //display 5
              {
                  M5.dis.animation((uint8_t *)image_num5B, 150, LED_DisPlay::kMoveLeft, 20);
                 
                  break;
              }
              case 6: //display 6
              {
                  M5.dis.animation((uint8_t *)image_num6B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 7: //display 7
              {
                  M5.dis.animation((uint8_t *)image_num7B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
              case 8: //display 8
              {
                  M5.dis.animation((uint8_t *)image_num8B, 150, LED_DisPlay::kMoveLeft, 20);
                
                  break;
              }
              case 9: //display 9
              {
                  M5.dis.animation((uint8_t *)image_num9B, 150, LED_DisPlay::kMoveLeft, 20);
                  
                  break;
              }
            }
            delayInterval(700);
            M5.update();
              
}

void countdown(int &seconds, int &minutes, int &hours, bool &snoozeTimer)
{

    if(seconds >= 0) //for every second
    {
      seconds--;
    }

    if(seconds < 0 && minutes == 0 && hours > 0) //for every hour
    {
      hours--;
      minutes = 59;
      seconds = 59;
    }
    
    if(seconds < 0 && minutes > 0) //for every minute
    {
      minutes--;
      seconds = 59;
    }

    
    else if(seconds == 0 && minutes == 0 && hours == 0) //when the timer reaches 0
    {
      snoozeTimer = false;
    }  
}

void initiateClockDisplay1(CRGB color)
{
  //------initial display of square lights------------
  for (int x=0;x<5;x=x+4)
  {
    for (int y=0;y<5;y++)
    {
        M5.dis.drawpix(x,y,color);
    } 
  }
  for (int y=0;y<5;y=y+4)
    {
    for (int x=0;x<5;x++)
    {
      M5.dis.drawpix(x,y,color);
      } 
    }
}

int noOfpastIntervals1=0,noOfpastIntervals2=0,TimerNumber;
unsigned long Timestamp1 = 0, Timestamp2 = 0, interval1, interval2;
unsigned long previousMillis1=millis(),currentMillis1,previousMillis2=millis(),currentMillis2;

void displayClock1(int timernumber, int noOfpastIntervals)
{ 
      if (timernumber==1)
      {
      for (int i=0;i<noOfpastIntervals;i++)
      {
        M5.dis.drawpix(patternarray[i],0x000000);
        }
      }
      if (timernumber==2)
      {
           for (int i=0;i<noOfpastIntervals;i++)
      {
        M5.dis.drawpix(patternarray[i],0x000000);
        }
      }
}

int timerIndex = 1;

void setup(){
    M5.begin(true, false, true);
    M5.IMU.Init();
    WiFi.softAP(ssid, password);
    Serial.print("AP SSID: ");
    Serial.println(ssid);
    Serial.print("AP PASSWORD: ");
    Serial.println(password);
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());  //IP address assigned to your ESP
    server.on("/", handleRoot);

    server.on("/sendData", []() {
        RelayFlag = true;

        if(server.arg("timer").toInt() == 1){
          // start timer 1
          
          timerSet1 = true;
          modeState = false;
          initiateDisplay1 = true;

          hourTimer1 = server.arg("hours").toInt();
          minuteTimer1 = server.arg("mins").toInt();
          secondTimer1 = server.arg("seconds").toInt();
          
          //calculate the total times and intervals for the clock display
          totalTime1 = (hourTimer1 * 3600) + (minuteTimer1 * 60) + secondTimer1;
          fracTime1 = (totalTime1 / 15) * 1000;
          
        }
        
        if(server.arg("timer").toInt() == 2){
          // start timer 1
          
          timerSet2 = true;
          modeState = false;
          initiateDisplay2 = true;

          hourTimer2 = server.arg("hours").toInt();
          minuteTimer2 = server.arg("mins").toInt();
          secondTimer2 = server.arg("seconds").toInt();
          
          //calculate the total times and intervals for the clock display
          totalTime2 = (hourTimer2 * 3600) + (minuteTimer2 * 60) + secondTimer2;
          fracTime2 = (totalTime2 / 15) * 1000;
          
        }
        Serial.print("Timer: ");
        Serial.print(server.arg("timer"));
        
        Serial.print(" Hours: ");
        Serial.print(server.arg("hours"));

        Serial.print(" Minutes: ");
        Serial.print(server.arg("mins"));
        
        Serial.print(" Seconds: ");
        Serial.println(server.arg("seconds"));

        // start timerIndex
        timerIndex++;
        server.send(200, "text/plain", DataCreate());
    });

    server.on("/off", []() {
        RelayFlag = false;
        server.send(200, "text/plain", DataCreate());
    });

    server.on("/data", []() {
        server.send(200, "text/plain", DataCreate());
    });

    server.begin();
    Serial.println("HTTP server started");
}

void loop(){

server.handleClient();

M5.IMU.getAttitude(&pitch, &roll); //Start recording pitch and roll values

  if(roll > -10 && roll < 0 && pitch > roll && pitch < 0) //if face up
  {
    atomState = true;
    delayInterval(300);
  }

  if(M5.Btn.wasPressed()) //button pressed
  {
    atomState = true;
  }

  //print states of functions
//  Serial.printf("%d,%i,%d\n", atomState, optionsCTR, modeState);

  while(atomState == true)
  {

    if(timerSet1 == true) //when timer 1 is counting down
      {
        if(snoozeTimer1 == true)
        {
        
        currentMillisCount1 = millis();
        if(currentMillisCount1 - previousMillisCount1 >= 970) //1 second timer
        {
            countdown(secondTimer1, minuteTimer1, hourTimer1, snoozeTimer1); //countdown
            previousMillisCount1 = currentMillisCount1;
        }
//        Serial.printf("%i:%i:%i\n", hourTimer1, minuteTimer1, secondTimer1);
        Timestamp1=millis(); //record the current time
        currentMillis1=millis();
            if (currentMillis1-previousMillis1>=fracTime1) 
            {noOfpastIntervals1++;
              previousMillis1=currentMillis1;
              }
        }

        if(snoozeTimer1 == false)
         {
            M5.dis.clear();
            M5.update();
            currentMillisCount1 = millis();
            if(currentMillisCount1 - previousMillisCount1 >= 500) //1 second timer
            {
                M5.dis.fillpix(0xff0000);
                M5.update();
//                previousMillis1=currentMillis1;
            }

            if(currentMillisCount1 - previousMillisCount1 >= 1000) //1 second timer
            {
                M5.dis.clear();
                M5.update();
                previousMillis1=currentMillis1;
            }

            if(M5.Btn.wasPressed())
            {
              snoozeTimer1 = true;
              timerSet1 = false;
              modeState = false;
            }
          
         }
      }

      if(timerSet2 == true) //when timer 1 is counting down
      {
        currentMillisCount2 = millis();
        if(currentMillisCount2 - previousMillisCount2 >= 970) //1 second timer
        {
            countdown(secondTimer2, minuteTimer2, hourTimer2, snoozeTimer2); //countdown
            previousMillisCount2 = currentMillisCount2;
        }
        Timestamp2=millis(); //record the current time
        currentMillis2=millis();
            if (currentMillis2-previousMillis2>=fracTime2) 
            {noOfpastIntervals2++;
              previousMillis2=currentMillis2;
              }
      }
      
      //get current pitch and roll
      M5.IMU.getAttitude(&pitch, &roll);
      double val = sqrt(pitch * pitch + roll * roll);

      if(modeState == false)
      {
//          delayInterval(300);
          if(pitch < -10)
          {
            optionsCTR++;
            if (optionsCTR >= 3) //if counter exceeds number of states
            {
               optionsCTR = 0; //reset counter
            }
            delayInterval(300); //so that no other values are read
          }
        
          else if(pitch > 10)
          {
            optionsCTR--;
            if (optionsCTR <= -1) //if counter exceeds number of states
            {
               optionsCTR = 2; //reset counter
            }
            delayInterval(300); //so that no other values are read
          }
      }
     
      switch(optionsCTR)
      {
        case 0: //Timer 1
        {
          if(modeState == false)
          {
            M5.dis.displaybuff((uint8_t *)image_num2W, 0, 0);
            M5.update();
  
            if(M5.Btn.wasPressed())
            {
              modeState = true;
              TimerNumber = 2;
            } 
          }

          if(modeState == true)
          {
            if(timerSet2 == false) //if the timer is not set
            {

              if(timeSelect2 == false) //if a unit of time isnt selected
              {

                if(pitch < -10)
                {
                  unitCTR++;
                  if (unitCTR >= 4) //if counter exceeds number of states
                  {
                     unitCTR = 0; //reset counter
                  }
                  delayInterval(300);
                }
              
                else if(pitch > 10)
                {
                  unitCTR--;
                  if (unitCTR <= -1) //if counter exceeds number of states
                  {
                     unitCTR = 3; //reset counter
                  }
                  delayInterval(300);
                }
              }

              switch(unitCTR)
              {
                case 0: //hour
                {
                  delayInterval(300);
                  if(hourloop == false)
                  {
                      M5.dis.displaybuff((uint8_t *)image_hour, 0, 0);
                      M5.update();

                      if(M5.Btn.wasPressed())
                      {
                        hourloop = true;
                      }
                  }

                  else if(hourloop == true)
                  {
                    timeSelect = true;
                      //get current pitch and roll
                      M5.IMU.getAttitude(&pitch, &roll); 
                        if(pitch < -10)
                        {
                          hourTimer2++;
                        }
                      
                        else if(pitch > 10)
                        {
                          if(hourTimer2 >= 0)
                          {
                            hourTimer2--;
                          }
                        }

                        displayTime(hourTimer2);
                        M5.dis.animation((uint8_t *)image_hourB, 150, LED_DisPlay::kMoveLeft, 12);
                        M5.update();
                        if(val >= 35 && val <= 50)
                        {
                          hourloop = false;
                          timeSelect2 = false;
                        } 
                    }
                    break;
                 }

                 case 1: //minute
                 {
                  if(minuteloop == false)
                  {
                      M5.dis.displaybuff((uint8_t *)image_minute, 0, 0);
                      M5.update();

                      if(M5.Btn.wasPressed())
                      {
                        minuteloop = true;
                      }
                  }

                  else if(minuteloop == true)
                  {
                      delayInterval(300);
                      timeSelect2 = true;
                      //get current pitch and roll
                      M5.IMU.getAttitude(&pitch, &roll); 
                        if(pitch < -10)
                        {
                          minuteTimer2++;
                        }
                      
                        else if(pitch > 10)
                        {
                          if(hourTimer2 >= 0)
                          {
                            minuteTimer2--;
                          }
                        }

                        displayTime(minuteTimer2);
                        M5.dis.animation((uint8_t *)image_minuteB, 150, LED_DisPlay::kMoveLeft, 8);
                        M5.update();
                        if(val >= 35 && val <= 50)
                        {
                          minuteloop = false;
                          timeSelect2 = false;
                        } 
                    }
                    break;
                 }

                 case 2: //seconds
                 {
                  if(secondloop == false)
                  {
                      M5.dis.displaybuff((uint8_t *)image_num5W, 0, 0);
                      M5.update();

                      if(M5.Btn.wasPressed())
                      {
                        secondloop = true;
                      }
                  }

                  else if(secondloop == true)
                  {
                      delayInterval(300);
                      timeSelect2 = true;
                      //get current pitch and roll
                      M5.IMU.getAttitude(&pitch, &roll); 
                        if(pitch < -10)
                        {
                         secondTimer2++;
                        }
                      
                        else if(pitch > 10)
                        {
                          if(secondTimer2 >= 0)
                          {
                            secondTimer2--;
                          }
                        }

                        displayTime(secondTimer2);
                        M5.dis.animation((uint8_t *)image_secondB, 150, LED_DisPlay::kMoveLeft, 12);
                        M5.update();
                        if(val >= 35 && val <= 50)
                        {
                          secondloop = false;
                          timeSelect2 = false;
                        } 
                    }
                    break;
                 }

                 case 3: //confirm
                 {
                      M5.dis.displaybuff((uint8_t *)image_confirm, 0, 0);
                      M5.update();

                      if(M5.Btn.wasPressed())
                      {
                        timerSet2 = true;
                        modeState = false;
                        initiateDisplay2 = true;

                        //calculate the total times and intervals for the clock display
                        totalTime2 = (hourTimer2 * 3600) + (minuteTimer2 * 60) + secondTimer2;
                        fracTime2 = (totalTime2 / 15) * 1000;
                      }
                      break;
                  }
                }


                 
              }
             
              else if (timerSet2 == true)
              {
                if(initiateDisplay2 == true)
                {
                  M5.dis.clear();
                  initiateClockDisplay1(0x008000);
                  M5.update();
                  initiateDisplay2 = false;
                }

                if(initiateDisplay2 == false)
                {
                  displayClock1(TimerNumber, noOfpastIntervals2);
                  M5.update();
                  if(M5.Btn.wasPressed())
                    {
                      modeState = false;
                      initiateDisplay2 = true;
                      M5.update();
                    } 
                }
              }
            
          }

          break;
          
        }
    
        case 1: //Timer 2
        {
          
          if(modeState == false)
          {
            M5.dis.displaybuff((uint8_t *)image_num1W, 0, 0);
            M5.update();
  
            if(M5.Btn.wasPressed())
            {
              modeState = true;
//              timerView1 = true;
              TimerNumber = 1;
            } 
          }

          if(modeState == true)
          {
//            Serial.printf("%d\n", timerSet1);
//            delayInterval(300);
            if(timerSet1 == false) //if the timer is not set
            {

              if(timeSelect == false) //if a unit of time isnt selected
              {

                if(pitch < -10)
                {
                  unitCTR++;
                  if (unitCTR >= 4) //if counter exceeds number of states
                  {
                     unitCTR = 0; //reset counter
                  }
                  delayInterval(300);
                }
              
                else if(pitch > 10)
                {
                  unitCTR--;
                  if (unitCTR <= -1) //if counter exceeds number of states
                  {
                     unitCTR = 3; //reset counter
                  }
                  delayInterval(300);
                }
              }

              switch(unitCTR)
              {
                case 0: //hour
                {
                  delayInterval(300);
                  if(hourloop == false)
                  {
                      M5.dis.displaybuff((uint8_t *)image_hour, 0, 0);
                      M5.update();

                      if(M5.Btn.wasPressed())
                      {
                        hourloop = true;
                      }
                  }

                  else if(hourloop == true)
                  {
                    timeSelect = true;
                      //get current pitch and roll
                      M5.IMU.getAttitude(&pitch, &roll); 
                        if(pitch < -10)
                        {
                          hourTimer1++;
                        }
                      
                        else if(pitch > 10)
                        {
                          if(hourTimer1 >= 0)
                          {
                            hourTimer1--;
                          }
                        }

                        displayTime(hourTimer1);
                        M5.dis.animation((uint8_t *)image_hourB, 150, LED_DisPlay::kMoveLeft, 12);
                        M5.update();
                        if(val >= 35 && val <= 50)
                        {
                          hourloop = false;
                          timeSelect = false;
                        } 
                    }
                    break;
                 }

                 case 1: //minute
                 {
                  if(minuteloop == false)
                  {
                      M5.dis.displaybuff((uint8_t *)image_minute, 0, 0);
                      M5.update();

                      if(M5.Btn.wasPressed())
                      {
                        minuteloop = true;
                      }
                  }

                  else if(minuteloop == true)
                  {
                      delayInterval(300);
                      timeSelect = true;
                      //get current pitch and roll
                      M5.IMU.getAttitude(&pitch, &roll); 
                        if(pitch < -10)
                        {
                          minuteTimer1++;
                        }
                      
                        else if(pitch > 10)
                        {
                          if(hourTimer1 >= 0)
                          {
                            minuteTimer1--;
                          }
                        }

                        displayTime(minuteTimer1);
                        M5.dis.animation((uint8_t *)image_minuteB, 150, LED_DisPlay::kMoveLeft, 8);
                        M5.update();
                        if(val >= 35 && val <= 50)
                        {
                          minuteloop = false;
                          timeSelect = false;
                        } 
                    }
                    break;
                 }

                 case 2: //seconds
                 {
                  if(secondloop == false)
                  {
                      M5.dis.displaybuff((uint8_t *)image_num5W, 0, 0);
                      M5.update();

                      if(M5.Btn.wasPressed())
                      {
                        secondloop = true;
                      }
                  }

                  else if(secondloop == true)
                  {
                      delayInterval(300);
                      timeSelect = true;
                      //get current pitch and roll
                      M5.IMU.getAttitude(&pitch, &roll); 
                        if(pitch < -10)
                        {
                         secondTimer1++;
                        }
                      
                        else if(pitch > 10)
                        {
                          if(secondTimer1 >= 0)
                          {
                            secondTimer1--;
                          }
                        }

                        displayTime(secondTimer1);
                        M5.dis.animation((uint8_t *)image_secondB, 150, LED_DisPlay::kMoveLeft, 12);
                        M5.update();
                        if(val >= 35 && val <= 50)
                        {
                          secondloop = false;
                          timeSelect = false;
                        } 
                    }
                    break;
                 }

                 case 3: //confirm
                 {
                      M5.dis.displaybuff((uint8_t *)image_confirm, 0, 0);
                      M5.update();

                      if(M5.Btn.wasPressed())
                      {
                        timerSet1 = true;
                        modeState = false;
                        initiateDisplay1 = true;

                        //calculate the total times and intervals for the clock display
                        totalTime1 = (hourTimer1 * 3600) + (minuteTimer1 * 60) + secondTimer1;
                        fracTime1 = (totalTime1 / 15) * 1000;
                      }
                      break;
                  }
                }


                 
              }
             
              else if (timerSet1 == true)
              {
                if(initiateDisplay1 == true)
                {
                  M5.dis.clear();
                  initiateClockDisplay1(0xff0000);
                  M5.update();
                  initiateDisplay1 = false;
                }

                if(initiateDisplay1 == false)
                {
                  displayClock1(TimerNumber, noOfpastIntervals1);
                  M5.update();
                  if(M5.Btn.wasPressed())
                    {
                      modeState = false;
                      initiateDisplay1 = true;
                      M5.update();
                    } 
                }
              }
            
          }

          break;
           
        }

//        case 2: //Reset
//        {
//
//          if(modeState == false)
//          {
//            M5.dis.displaybuff((uint8_t *)image_num3W, 0, 0);
//            M5.update();
//  
//            if(M5.Btn.wasPressed())
//            {
//              modeState = true;
//            }
//          }
//
//          if(modeState == true)
//          
//           { 
//           }
//           
//
//
//           break;
//           
//        
//        
//      }
      }

//    if(roll > 15 && roll > pitch) //HAD TO BE REMOVED BC OF LACK OF DELAY
//    {
//      modeState = false;
//      atomState = false;
//      M5.dis.clear();
//      M5.update();
//      delayInterval(500);
//  
//    }

    break;
    
  }


//    M5.dis.clear();
//    M5.update();
//    delayInterval(500);
  

    
}