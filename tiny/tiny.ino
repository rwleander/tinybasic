//  beep after 5, 10, 15, 20, 25 or 30 seconds

#include <M5StickC.h>

//  settings

#define MIN_TIME 5
#define MAX_TIME 30

int t = 15;
int tone = 440;

//  sound setup variables

const int servo_pin = 26;
int ledChannel = 0;
int freq = 50;
int resolution = 10;
extern const unsigned char m5stack_startup_music[];

//  function prototypes

void playTime();
void addTime();
void playTone(int t);


//--------------------
//  arduino functions

//  setup

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(0, 30, 4);
  M5.Lcd.println("Timer");
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(servo_pin, ledChannel);
  ledcWrite(ledChannel, 256);//0°
  ledcWriteTone(ledChannel, 0);
}

//  loop look for button press

void loop() {
	
	if (M5.BtnB.read() == 1) {
    addTime();
  }

  if (M5.BtnA.read() == 1) {
    playTime();
  }

  m5.update();
}

//-------------------
//  sound functions

//  play the time sequence

void playTime()
{
	  playTone(200);
	  delay (t * 1000);
	  playTone(200);
}
    
	//  increment time
  
  void addTime()
  {
	    t += MIN_TIME;
		if (t > MAX_TIME)
		{
			  t = MIN_TIME;
		}
		
		int n = t / MIN_TIME;
		for (int i = 0; i < n; i++)
		{
			  playTone(200);
			  delay(250);
		}			
  }
  
//  play a tone

void playTone(int t) {
  ledcWriteTone(ledChannel, tone);
  delay(t);
  ledcWriteTone(ledChannel, 0);  
}
