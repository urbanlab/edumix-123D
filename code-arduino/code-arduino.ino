
#include <SoftwareSerial.h>
#include <MP3Player_KT403A.h>
#include <ChainableLED.h>
#define NUM_LEDS  3
#define PROXI_A A0
#define PROXI_B A1

#define VOID 0
#define WELCOME 1
#define MUSIC 2
#define BYE 3

// Note: You must define a SoftwareSerial class object that the name must be mp3,
//       but you can change the pin number according to the actual situation.
SoftwareSerial mp3(2, 3);
ChainableLED leds(6, 7, NUM_LEDS);
float hue = 0.0;
boolean up = true;
int State = VOID;

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(PROXI_A, INPUT);
  pinMode(PROXI_B, INPUT);
  leds.init();
  mp3.begin(9600);
  Serial.begin(115200);
  delay(100);
  SelectPlayerDevice(0x02);       // Select SD card as the player device.
  SetVolume(0x1E);                // Set the volume, the range is 0x00 to 0x1E.
  //SpecifyMusicPlay(1);
  digitalWrite(13, LOW);
  leds.setColorRGB(0, 0, 0, 0);
  State = VOID;
  Serial.println("Void");
}

void AnimLeds()
{
  if (!digitalRead(PROXI_A) && !digitalRead(PROXI_B) )
  {
    State = BYE;
    Serial.println("Bye");
  }

  if (State != BYE)
  {
    for (byte i = 0; i < NUM_LEDS; i++)
      leds.setColorHSB(i, hue, 1.0, 0.5);

    delay(100);

    if (up)
      hue += 0.025;
    else
      hue -= 0.025;

    if (hue >= 1.0 && up)
      up = false;
    else if (hue <= 0.0 && !up)
      up = true;
  }
  if (!digitalRead(PROXI_A) && !digitalRead(PROXI_B) )
  {
    State = BYE;
    Serial.println("Bye");
  }
}

void loop()
{

  //if(digitalRead(PROXI_A) ) Serial.println("PROXI_A");
  //if(digitalRead(PROXI_B) ) Serial.println("PROXI_B");

  switch (State)
  {
    case VOID:
      leds.setColorRGB(0, 0, 0, 0);
      leds.setColorRGB(1, 0, 0, 0);
      leds.setColorRGB(2, 0, 0, 0);
      digitalWrite(13, LOW);
      if ( digitalRead(PROXI_A) || digitalRead(PROXI_B) )
      {
        State = WELCOME;
        Serial.println("Welcome");

      }
      break;

    case WELCOME:
      leds.setColorRGB(0, 0, 0, 128);
      leds.setColorRGB(1, 0, 0, 128);
      leds.setColorRGB(2, 0, 0, 128);
      delay(1000);
      leds.init();
      SpecifyMusicPlay(1);
      digitalWrite(13, LOW);
      delay(9000);
      digitalWrite(13, HIGH);
      for (int i = 0; i < 100; i++)
      {
        AnimLeds();
      }
      leds.init();
      digitalWrite(13, HIGH);
      State = MUSIC;
      Serial.println("Music");

      break;

    case MUSIC:
      if (!digitalRead(PROXI_A) && !digitalRead(PROXI_B) )
      {
        State = BYE;
        Serial.println("Bye");
      }
      break;

    case BYE:

      leds.setColorRGB(0, 0, 0, 128);
      leds.setColorRGB(1, 0, 0, 128);
      leds.setColorRGB(2, 0, 0, 128);
      delay(1000);
      leds.init();
      SpecifyMusicPlay(2);
      digitalWrite(13, LOW);
      delay(7000);
      State = VOID;
      Serial.println("Void");
      break;
  }


  /*
    char recvChar = 0;
    while(Serial.available())
    {
      recvChar = Serial.read();
    }
    Serial.print("Send: ");
    Serial.println( recvChar );


    switch (recvChar)
    {
      case '1':
          leds.setColorRGB(0, 0, 0,128);
          leds.setColorRGB(1, 0, 0,128);
          leds.setColorRGB(2, 0, 0,128);
          delay(1000);
          leds.init();
          SpecifyMusicPlay(1);
          digitalWrite(13, LOW);
          delay(9000);
          digitalWrite(13, HIGH);
          for (int i=0; i<50; i++)
          {
             AnimLeds();
          }
          leds.init();
          digitalWrite(13, HIGH);
          Serial.println("Specify the music index to play");

          break;
      case '2':
          PlayPause();
          digitalWrite(13, HIGH);

          Serial.println("Pause the MP3 player");
          break;
      case '3':
          PlayResume();
          digitalWrite(13, HIGH);

          Serial.println("Resume the MP3 player");
          break;
      case '4':
          PlayNext();
          Serial.println("Play the next song");
          break;
      case '5':
          PlayPrevious();
          Serial.println("Play the previous song");
          break;
      case '6':
          PlayLoop();
          Serial.println("Play loop for all the songs");
          break;
      case '7':
          IncreaseVolume();
          Serial.println("Increase volume");
          break;
      case '8':
          DecreaseVolume();
          Serial.println("Decrease volume");
          break;
      default:
          break;
    }

    delay(1000);

    printReturnedData();
  */
}
