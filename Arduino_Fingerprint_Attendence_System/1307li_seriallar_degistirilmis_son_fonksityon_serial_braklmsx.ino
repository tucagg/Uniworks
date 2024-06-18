//1307li_seriallar_degistirilmis_son_fonksityon_serial_braklms
//3 kere okudu 1. yanlis 2 ve 3 dogru. sadece 3 kere okuyor
//delaylerle birlikte iyi calisiyor.

#include <RTClib.h>

#include <LiquidCrystal_I2C.h>

#include<EEPROM.h>

#include <SoftwareSerial.h>

#include <Wire.h>

#include "Adafruit_Fingerprint.h"

RTC_DS1307 rtc;

SoftwareSerial fingerPrint(8, 7);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);

uint8_t id;

#define enroll 14

#define del 15

#define up 16

#define down 17

#define indFinger 10

#define buzzer 9

#define match 5

#define records 5  // 5 for 5 user

LiquidCrystal_I2C lcd(0x27,16,2);

int user1,user2,user3,user4,user5;
DateTime now;



void setup()

{

    delay(1000);
    lcd.init();
    lcd.backlight();

    Serial.begin(9600);

    pinMode(enroll, INPUT_PULLUP);

    pinMode(up, INPUT_PULLUP);

    pinMode(down, INPUT_PULLUP);

    pinMode(del, INPUT_PULLUP);

    pinMode(match, INPUT_PULLUP);

    pinMode(buzzer, OUTPUT);

    pinMode(indFinger, OUTPUT);

    digitalWrite(buzzer, LOW);

    if(digitalRead(enroll) == 0)

    {

      digitalWrite(buzzer, HIGH);

      delay(500);

      digitalWrite(buzzer, LOW);

      lcd.clear();

      lcd.print("Please wait");

      lcd.setCursor(0,1);

      lcd.print("Downloading Data");
      for(int i=0;i<records;i++)

      {

              digitalWrite(buzzer, HIGH);

      delay(500);

      digitalWrite(buzzer, LOW);

        Serial.print("         User ID");

        Serial.print(i+1);

        Serial.print("                   ");

      }

      Serial.println();

      int eepIndex=0;

      for(int i=0;i<30;i++)

      {

        if(i+1<10)

        Serial.print('0');

        Serial.print(i+1);

        Serial.print("          ");

        eepIndex=(i*7);

        download(eepIndex);

        eepIndex=(i*7)+210;

        download(eepIndex);

        eepIndex=(i*7)+420;

        download(eepIndex);

        eepIndex=(i*7)+630;

        download(eepIndex);

      //  eepIndex=(i*7)+840;   // 5th user

      //  download(eepIndex);

        Serial.println();

      }

    }

    if(digitalRead(del) == 0)

    {

      lcd.clear();

      lcd.print("Please Wait");

      lcd.setCursor(0,1);

      lcd.print("Reseting.....");

      for(int i=1000;i<1005;i++)

      EEPROM.write(i,0);

      for(int i=0;i<841;i++)

      EEPROM.write(i, 0xff);

      lcd.clear();

      lcd.print("System Reset");

      delay(1000);

    }


    

    lcd.clear();
    /*
    //lcd.print("Bengisu Duru");
    lcd.setCursor(0,1);
    lcd.print("Goksu");
    delay(2000);
    lcd.clear();

    lcd.print("Bekir Sadık");
    lcd.setCursor(0,1);
    lcd.print("Altunkaya");
    delay(2000);
    lcd.clear();

    lcd.print("Cagri");
    lcd.setCursor(0,1);
    lcd.print("Ozcanli");
    delay(2000);
    lcd.clear();

    lcd.print("Emircan");
    lcd.setCursor(0,1);
    lcd.print("Badur");
    delay(2000);
    lcd.clear();

    lcd.print("Fatma Aleyna");
    lcd.setCursor(0,1);
    lcd.print("Corapci");
    delay(2000);
    lcd.clear();

    lcd.print("Nisanur");
    lcd.setCursor(0,1);
    lcd.print("Kara");
    delay(2000);
    lcd.clear();

    lcd.print("Omer Faruk");
    lcd.setCursor(0,1);
    lcd.print("Oruc");
    delay(2000);
    lcd.clear();

    lcd.print("Sertan Batur");
    lcd.setCursor(0,1);
    lcd.print("Esitgen");
    delay(2000);
    lcd.clear();

    lcd.print("Tugce");
    lcd.setCursor(0,1);
    lcd.print("Polat");
    delay(2000);
    lcd.clear();*/

    lcd.print("   Attendance   ");

    lcd.setCursor(0,1);

    lcd.print("     System     ");

    delay(2000);

    lcd.clear();

    lcd.print("Group 16");

    lcd.setCursor(0,1);

    lcd.print("Arduino Project");

    delay(2000);

          digitalWrite(buzzer, HIGH);

      delay(500);

      digitalWrite(buzzer, LOW);

  for(int i=1000;i<1000+records;i++)

  {

    if(EEPROM.read(i) == 0xff)

        EEPROM.write(i,0);

   }


    finger.begin(57600);

    Serial.begin(9600);

    lcd.clear();

    lcd.print("Finding Module");

    lcd.setCursor(0,1);

    delay(1000);

    if (finger.verifyPassword())

    {
      lcd.clear();

      lcd.print("Found Module ");

      delay(1000);

    }

    else

    {
    lcd.clear();

    lcd.print("module not Found");

    lcd.setCursor(0,1);

    lcd.print("Check Connections");

    while (1);

    }

    if (! rtc.isrunning())

    {


    // following line sets the RTC to the date & time this sketch was compiled

       //rtc.adjust(DateTime(2023,1,17,7,0,0));

    // This line sets the RTC with an explicit date & time, for example to set

    // January 21, 2014 at 3am you would call:

    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

    }

lcd.setCursor(0,0);

 lcd.print("Press Match to ");

 lcd.setCursor(0,1);

 lcd.print("Start System");

 delay(2000);


 user1=EEPROM.read(1000);

  user2=EEPROM.read(1001);

   user3=EEPROM.read(1002); 

   user4=EEPROM.read(1003);

    user5=EEPROM.read(1004);

    lcd.clear();

    digitalWrite(indFinger, HIGH);

    

}


void loop()

{
    
    now = rtc.now();

    lcd.setCursor(0,0);

    lcd.print("Time->");

    lcd.print(now.hour(), DEC);

    lcd.print(':');

    lcd.print(now.minute(), DEC);

    lcd.print(':');

    lcd.print(now.second(), DEC);

    lcd.print("    ");

    lcd.setCursor(0,1);

    lcd.print("Date->");

    lcd.print(now.day(), DEC);

    lcd.print('/');

    lcd.print(now.month(), DEC);

    lcd.print('/');

    lcd.print(now.year(), DEC);

    lcd.print("     ");

    delay(500);

    int result=getFingerprintIDez();

    if(result>0)

    {

              digitalWrite(indFinger, LOW);

              digitalWrite(buzzer, HIGH);

              delay(100);

              digitalWrite(buzzer, LOW);

              lcd.clear();

              lcd.print("ID:");

              lcd.print(result);
              
            

              lcd.setCursor(0,1);
              if (result == 1){
                lcd.clear();
                lcd.print("Tugce");
                Serial.println("Tugce Polat");
               }
              if (result == 2){
                lcd.clear();
                lcd.print("Bengisu");
                Serial.println("Bengisu Duru Goksu");
              }
              if (result == 3){
                lcd.clear();
                lcd.print("BSA");
                Serial.println("Bekir Sadik Altunkaya");
              }
              if (result == 4){
                lcd.clear();
                lcd.print("Emircan");
                Serial.println("Emircan Badur");
              }
              if (result == 5){
                lcd.clear();
                lcd.print("Nisanur");
                Serial.println("Nisanur Kara");
              }

              lcd.print("Please Wait....");

              delay(1000);

              attendance(result);

              lcd.clear();

              lcd.print("Attendance ");

              lcd.setCursor(0,1);

              lcd.print("Registered");

              delay(1000);

        digitalWrite(indFinger, HIGH);

        return;

 }

 checkKeys();

 delay(300);

}


//     dmyyhms - 7 bytes

void attendance(int id)

{

  int user=0,eepLoc=0;

  if(id == 1)

  {

    eepLoc=0;

    user=user1++;

  }

  else if(id == 2)

  {

    eepLoc=210;

    user=user2++;

  }

  else if(id == 3)

  {

    eepLoc=420;

    user=user3++;

  }

  else if(id == 4)

  {

    eepLoc=630;

    user=user4++;

  }

  /*else if(id == 5)   // fifth user

  {

    eepLoc=840;

    user=user5++;

  }*/

  else 

  return;

  

    int eepIndex=(user*7)+eepLoc;

    EEPROM.write(eepIndex++, now.hour());

    EEPROM.write(eepIndex++, now.minute());

    EEPROM.write(eepIndex++, now.second());

    EEPROM.write(eepIndex++, now.day());

    EEPROM.write(eepIndex++, now.month());

    EEPROM.write(eepIndex++, now.year()>>8 );

    EEPROM.write(eepIndex++, now.year());


    EEPROM.write(1000,user1);

    EEPROM.write(1001,user2);

    EEPROM.write(1002,user3);

    EEPROM.write(1003,user4);

  //  EEPROM.write(4,user5);   // figth user

}


void checkKeys()

{

   if(digitalRead(enroll) == 0)

   {

    lcd.clear();

    lcd.print("Please Wait");

    delay(1000);

    while(digitalRead(enroll) == 0);

    Enroll();

   }


   else if(digitalRead(del) == 0)

   {

    lcd.clear();

    lcd.print("Please Wait");

    delay(1000);

    delet();

   }

}


void Enroll()

{

   int count=1;

   lcd.clear();

   lcd.print("Enter Finger ID:");

   while(1)

   {

    lcd.setCursor(0,1);

     lcd.print(count);

     if(digitalRead(up) == 0)

     {

       count++;

       if(count>records)

       count=1;

       delay(500);

     }


     else if(digitalRead(down) == 0)

     {

       count--;

       if(count<1)

       count=records;

       delay(500);

     }

     else if(digitalRead(del) == 0)

     {

          id=count;

          getFingerprintEnroll();

          for(int i=0;i<records;i++)

          {

            if(EEPROM.read(i) != 0xff)

            {

              EEPROM.write(i, id);

              break;

            }

          }

          return;

     }


       else if(digitalRead(enroll) == 0)

     {

          return;

     }

 }

}


void delet()

{

   int count=1;

   lcd.clear();

   lcd.print("Enter Finger ID");


   while(1)

   {

    lcd.setCursor(0,1);

     lcd.print(count);

     if(digitalRead(up) == 0)

     {

       count++;

       if(count>records)

       count=1;

       delay(500);

     }


     else if(digitalRead(down) == 0)

     {

       count--;

       if(count<1)

       count=records;

       delay(500);

     }

     else if(digitalRead(del) == 0)

     {

          id=count;

          deleteFingerprint(id);

          for(int i=0;i<records;i++)

          {

            if(EEPROM.read(i) == id)

            {

              EEPROM.write(i, 0xff);

              break;

            }

          }

          return;

     }


       else if(digitalRead(enroll) == 0)

     {

          return;

     }

 }

}


uint8_t getFingerprintEnroll()

{

  int p = -1;

  lcd.clear();

  lcd.print("finger ID:");

  lcd.print(id);

  lcd.setCursor(0,1);

  lcd.print("Place Finger");

  delay(2000);

  while (p != FINGERPRINT_OK)

  {

    p = finger.getImage();

    switch (p)

    {

    case FINGERPRINT_OK:

      //Serial.println("Image taken");

      lcd.clear();

      lcd.print("Image taken");

      break;

    case FINGERPRINT_NOFINGER:
      lcd.clear();

      lcd.print("No Finger");

      break;

    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();

      lcd.print("Comm Error");

      break;

    case FINGERPRINT_IMAGEFAIL:

      lcd.clear();

      lcd.print("Imaging Error");

      break;

    default:

       lcd.clear();

      lcd.print("Unknown Error");

      break;

    }

  }


  // OK success!


  p = finger.image2Tz(1);

  switch (p) {

    case FINGERPRINT_OK:

      lcd.clear();

      lcd.print("Image converted");

      break;

    case FINGERPRINT_IMAGEMESS:

       lcd.clear();

       lcd.print("Image too messy");

      return p;

    case FINGERPRINT_PACKETRECIEVEERR:

            lcd.clear();

      lcd.print("Comm Error");

      return p;

    case FINGERPRINT_FEATUREFAIL:

            lcd.clear();

      lcd.print("Feature Not Found");

      return p;

    case FINGERPRINT_INVALIDIMAGE:


                  lcd.clear();

      lcd.print("Feature Not Found");

      return p;

    default:

                  lcd.clear();

      lcd.print("Unknown Error");

      return p;

  }


  lcd.clear();

  lcd.print("Remove Finger");

  delay(2000);

  p = 0;

  while (p != FINGERPRINT_NOFINGER) {

    p = finger.getImage();

  }

  Serial.print("ID "); Serial.println(id);

  p = -1;

   lcd.clear();

      lcd.print("Place Finger");

      lcd.setCursor(0,1);

      lcd.print("   Again");

  while (p != FINGERPRINT_OK) {

    p = finger.getImage();

    switch (p) {

    case FINGERPRINT_OK:

      break;

    case FINGERPRINT_NOFINGER:


      break;

    case FINGERPRINT_PACKETRECIEVEERR:

      break;

    case FINGERPRINT_IMAGEFAIL:

      break;

    default:

      return;

    }

  }


  // OK success!


  p = finger.image2Tz(2);

  switch (p) {

    case FINGERPRINT_OK:

      break;

    case FINGERPRINT_IMAGEMESS:

      return p;

    case FINGERPRINT_PACKETRECIEVEERR:

      return p;

    case FINGERPRINT_FEATUREFAIL:

      return p;

    case FINGERPRINT_INVALIDIMAGE:

      return p;

    default:

      return p;

  }


  // OK converted!

  //Serial.print("Creating model for #");  Serial.println(id);


  p = finger.createModel();

  if (p == FINGERPRINT_OK) {

  //Serial.println("Prints matched!");

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {


    return p;

  } else if (p == FINGERPRINT_ENROLLMISMATCH) {

    return p;

  } else {


    return p;

  }


  Serial.print("ID "); Serial.println(id);

  p = finger.storeModel(id);

  if (p == FINGERPRINT_OK) {


    lcd.clear();

    lcd.print("Stored!");

    delay(2000);
    


  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {


    return p;

  } else if (p == FINGERPRINT_BADLOCATION) {

    return p;

  } else if (p == FINGERPRINT_FLASHERR) {


    return p;

  }

  else {

    return p;

  }

}


int getFingerprintIDez()

{

  uint8_t p = finger.getImage();


  if (p != FINGERPRINT_OK)

  return -1;


  p = finger.image2Tz();

  if (p != FINGERPRINT_OK)

  return -1;


  p = finger.fingerFastSearch();

  if (p != FINGERPRINT_OK)

  {

   lcd.clear();

   lcd.print("Finger Not Found");

   lcd.setCursor(0,1);

   lcd.print("Try Later");

   delay(2000);

  return -1;

  }

  // found a match!


  return finger.fingerID;

}


uint8_t deleteFingerprint(uint8_t id)

{

  uint8_t p = -1;

  lcd.clear();

  lcd.print("Please wait");

  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK)

  {

    lcd.clear();

    lcd.print("Finger Deleted");

    lcd.setCursor(0,1);

    lcd.print("Successfully");

    delay(1000);

  }


  else

  {


    lcd.clear();

    lcd.print("Something Wrong");

    lcd.setCursor(0,1);

    lcd.print("Try Again Later");

    delay(2000);

    return p;

  }

}


void download(int eepIndex)

{

            

            if(EEPROM.read(eepIndex) != 0xff)

            {

              Serial.print("T->");

              if(EEPROM.read(eepIndex)<10)

              Serial.print('0');

              Serial.print(EEPROM.read(eepIndex++));

              Serial.print(':');  

              if(EEPROM.read(eepIndex)<10)

              Serial.print('0');

              Serial.print(EEPROM.read(eepIndex++));

              Serial.print(':'); 

              if(EEPROM.read(eepIndex)<10)

              Serial.print('0');

              Serial.print(EEPROM.read(eepIndex++));

              Serial.print("   D->");

              if(EEPROM.read(eepIndex)<10)

              Serial.print('0');

              Serial.print(EEPROM.read(eepIndex++));

              Serial.print('/');

              if(EEPROM.read(eepIndex)<10)

              Serial.print('0');           

              Serial.print(EEPROM.read(eepIndex++));

              Serial.print('/');            

              Serial.print(EEPROM.read(eepIndex++)<<8 | EEPROM.read(eepIndex++));

            }

            else

            {

               Serial.print("---------------------------");

            }


            Serial.print("         ");

}
