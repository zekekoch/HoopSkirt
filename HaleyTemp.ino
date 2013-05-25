#include "FastSPI_LED2.h"
#include "Animation.h"
#include "Segment.h"


//const int ledCount = 185;
const byte ledCount = 255;
const int strandCount = 7;
const int animationCount = 7;

//#define PIN 11
#define PIN 19

enum SegmentEnum
{
    RingTopBackCenter,
    RingTopBackRightInner,
    RingTopBackRightOuter,

    RingTopLeft,
    RingTopFrontLeftOuter,
    RingTopFrontLeftInner,

    RingTopFrontRightInner,
    RingTopFrontRightOuter,
    RingTopRight,

    RingTopBackLeftOuter,
    RingTopBackLeftInner,
    
    RingMiddleBackCenter,
    RingMiddleBackRightInner,
    RingMiddleBackRightOuter,
    
    RingMiddleLeft,
    RingMiddleFrontLeftInner,
    
    RingMiddleFrontRightInner,
    RingMiddleRight,
    
    RingMiddleBackLeftOuter,
    RingMiddleBackLeftInner,
   
    RingBottomBackCenter,
    RingBottomBackRightInner,
    RingBottomLeft,
    RingBottomRight,
    RingBottomBackLeftInner,
    
    VTopBackCenter,
    VTopRight,
    VTopLeft,

    VMiddleBackCenter,
    VMiddleBackLeftLower,
    VMiddleBackLeftMiddle,
    VMiddleBackLeftUpper,

    VMiddleFrontRightMiddle,
    VMiddleFrontLeftMiddle,
    
    VMiddleBackRightUpper,
    VMiddleBackRightMiddle,
    VMiddleBackRightLower,
    
    VBottomBackRightLower,
    VBottomBackRightMiddle,
    VBottomBackRightTop,
    VBottomFrontLeftMiddle,
    VBottomFrontLeftLower,
    
    VBottomFrontRightLower,
    VBottomFrontRightMiddle,
    VBottomBackLeftTop,
    VBottomBackLeftMiddle,
    VBottomBackLeftLower,
};

Segment segments[47] =
{
    /*** Ring Top ***/
    // Ring Top (Center, Right Inner, Right Outer)
    Segment(0b00000000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(0b11111111000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(0b00000000111111100000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),

    // Ring Top (Left Side, Left Outer, Left Inner)
    Segment(0b00000000000000011111111111111111,0b11110000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(0b00000000000000000000000000000000,0b00001111111000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment("00000000000000000000000000000000000000000001111100000000000000000000000000000000000000000000000"),

    // Ring Top (Right Inner, Right Outer, Right Side)
    Segment("00000000000000000000000000000000000000000000000111111000000000000000000000000000000000000000000"),
    Segment("00000000000000000000000000000000000000000000000000000111111100000000000000000000000000000000000"),
    Segment("00000000000000000000000000000000000000000000000000000000000011111111111111111111000000000000000"),

    // Ring Top (Left Outer, Left Inner)
    Segment("00000000000000000000000000000000000000000000000000000000000000000000000000000001111111110000000"),
    Segment("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111111"),

    /*** Ring Middle ***/
    // Ring Middle (Center, Right Inner, Right Outer)
    Segment("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("11111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("00001111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),

    // Ring Middle (Left Side, Left Inner)
    Segment("00000000000001111111111111111111111111111111100000000000000000000000000000000000000000000000000000000"),
    Segment("00000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000000000"),

    // Ring Middle (Right Inner, Right Side)
    Segment("00000000000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000"),
    Segment("00000000000000000000000000000000000000000000000000000000011111111111111111111111111111111000000000000"),

    // Ring Middle (Left Outer, Left Inner)
    Segment("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111110000"),
    Segment("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111"),

    /*** Ring Bottom ***/
    // Ring Bottom (Center, Right Inner, Left)
    Segment("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("1111111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("0000000000111111111111111111111111111111111111111111100000000000000000000000000000000000000000000000000000"),
    
    // Ring Bottom (Left Side, Left Inner)
    Segment("0000000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111110000000000"),
    Segment("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111111"),
        
    /*** VTop ***/
    // V Top (Center, Left, Right)
    Segment("000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("111111111111111111111111111111111111111110000000000000000000000000000000000000000"),
    Segment("000000000000000000000000000000000000000001111111111111111111111111111111111111111"),
    
    
    /*** VMiddle ***/
    // V Middle  (Center, Back Left Lower, Back Left Middle, Back Left Upper)
    Segment("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("1111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("0000000111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("0000000000000011111111111111111111111111111111111000000000000000000000000000000000000000000000000000000000000000"),

    // V Middle (Front Right Middle, Front Left Middle)
    Segment("0000000000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000000000000000"),
    Segment("0000000000000000000000000000000000000000000000000000000011111110000000000000000000000000000000000000000000000000"),
    
    // V Middle (Back Right Upper, Back Right Middle, Back Right Lower)
    Segment("0000000000000000000000000000000000000000000000000000000000000001111111111111111111111111111111111110000000000000"),
    Segment("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111000000"),
    Segment("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111"),

    /*** V Bottom ***/
    // V Bottom  (VBottomBackRightLower, VBottomBackRightMiddle, VBottomBackRightTop, VBottomFrontLeftMiddle, VBottomFrontLeftLower)
    
    Segment("1111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("0000011111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("0000000000001111111111111111111111100000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("0000000000000000000000000000000000111111110000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment("0000000000000000000000000000000000000000001111111110000000000000000000000000000000000000000000000000000000000000"),

    // VBottomFrontRightLower, VBottomFrontRightMiddle, VBottomBackLeftTop, VBottomBackLeftMiddle, VBottomBackLeftLower,
    Segment("0000000000000000000000000000000000000000000000000001111111100000000000000000000000000000000000000000000000000000"),
    Segment("0000000000000000000000000000000000000000000000000000000000011111111000000000000000000000000000000000000000000000"),
    Segment("0000000000000000000000000000000000000000000000000000000000000000000111111111111111111111100000000000000000000000"),
    Segment("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111100000000000000000"),
    Segment("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111111111111111"),

    
};

Animation::CRGB leds[strandCount][ledCount];
Animation anims[animationCount] =
{
    Animation(leds[RingTop], ledCount),
    Animation(leds[RingMiddle], ledCount),
    Animation(leds[RingBottom], ledCount),
    Animation(leds[VTop], ledCount),
    Animation(leds[VMiddle], ledCount),
    Animation(leds[VBottom], ledCount),
    Animation(leds[Vertical], ledCount)
};

// Setup/define the Led controller with data pin 11, clock pin 13, and latch pin 10
// this will trigger use of the hardware SPI support on the arduino uno
//LPD8806Controller<11, 13, 10> LED;
WS2811Controller800Mhz<12> LED1;
WS2811Controller800Mhz<9> LED2;
WS2811Controller800Mhz<6> LED3;
WS2811Controller800Mhz<3> LED4;
WS2811Controller800Mhz<13> LED5;
WS2811Controller800Mhz<16> LED6;
WS2811Controller800Mhz<19> LED7;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int lastInputLed = 0;

// array of animations

// top v - center 35, front left 50-70, front right 0-20
// bottom v - center 70, left 137-165, right 70-99
// top ring - front center 222, front left 199-222, front right 222-245
// middle ring - front center 307, front left 281-307, front right 307-331
// bottom ring - front center 396, front left 369-396, front right 396-421

void setup()
{
	Serial.begin(9600);
	LED1.init();
	LED2.init();
	LED3.init();
	LED4.init();
	LED5.init();
	LED6.init();
	LED7.init();
    
    // run the memory test function and print the results to the serial port
    //int result = memoryTest();
    //Serial.print("Memory test results: ");
    //Serial.print(result,DEC);
    //Serial.print(" bytes free");
    
	pinMode(A0, INPUT);
    

    anims[0].solid(0,95,16, 1);
    anims[0].setColor(2,0,0); // 16 for real

    anims[1].solid(0,101,16, 1);
    anims[1].setColor(0,2,0); // 16 for real

    anims[2].solid(0,115,16, 1);
    anims[2].setColor(0,0,2); // 16 for real
    anims[3].solid(0,115,16, 1);
    anims[3].setColor(2,2,0); // 16 for real
    anims[4].solid(0,115,16, 1);
    anims[4].setColor(2,0,2); // 16 for real
    anims[5].solid(0,115,16, 1);
    anims[5].setColor(2,2,0); // 16 for real
    anims[6].solid(0,115,16, 1);
    anims[6].setColor(4,2,0); // 16 for real
    
    anims[VBottom].bitFade(segments[VBottomBackLeftLower] | segments[VBottomBackLeftLower], 16,1);
    anims[VBottom].setColor(0,2,0);
    
}

int getLedFromSerial() {
    // if there's any serial available, read it:
    while (Serial.available() > 0) {
        Serial.println("in Get LED");
        // look for the next valid integer in the incoming serial stream:
        int iLed = Serial.parseInt();
        Serial.println(iLed);
        // look for the newline. That's the end of your
        // sentence:
        if (Serial.read() == ',') {
            iLed = constrain(iLed, 0, ledCount);
            Serial.print("led ");
            Serial.println(iLed);
            
            return iLed;
        }
    }
}

int xAccel;
void loop()
{
    if (Serial.available())
    {
        lastInputLed = getLedFromSerial();
        
        //
        Serial.print("byte: ");Serial.print(sizeof(byte));Serial.println();
        Serial.print("long: ");Serial.print(sizeof(long));Serial.println();
        Serial.print("int: ");Serial.print(sizeof(int));Serial.println();
        Serial.print("double: ");Serial.print(sizeof(double));Serial.println();
        Serial.print("long long: ");Serial.print(sizeof(long long));Serial.println();
        
        Serial.println(segments[2].length);
        Serial.println(segments[2].toString());
        Serial.println(segments[8].toString());
        Segment s =segments[2] | segments[8];
        Serial.println(s.toString());

    }

    //Serial.println("Hello World");
    //Serial.println(sizeof(leds));
    
    xAccel = analogRead(14)-655;
    //Serial.print("accel x=");
    //Serial.println(xAccel);
	int delayTime = 50;
    anims[0].clear();
    for(int i = 0;i<animationCount;i++)
    {
        anims[i].setAccel(xAccel);
        anims[i].play();
    }
    /*	for(int i = 0;i<=20;i++)
     {
     leds[i].r = 0;
     leds[i].g = 0;
     leds[i].b = 255;
     }
     */
    
    if(lastInputLed > 0)
    {
        for(int i = 0; i<7;i++)
        {
            leds[i][lastInputLed].r=15;
            leds[i][lastInputLed].g=15;
            leds[i][lastInputLed].b=15;
        }
    }
	
	LED1.showRGB((byte*)leds[0], 115);
	LED2.showRGB((byte*)leds[1], 115);
	LED3.showRGB((byte*)leds[2], 115);
	LED4.showRGB((byte*)leds[3], 115);
	LED5.showRGB((byte*)leds[4], 115);
	LED6.showRGB((byte*)leds[5], 115);
	LED7.showRGB((byte*)leds[6], 115);
	
	// delay(delayTime);
}

/*
 void looped() {
 if (Serial.available())
 {
 lastInputLed = getLedFromSerial();
 }
 
 int delayTime = 75;
 // upper v
 clearLeds();
 race(0, 255, 50,70);
 race(0, 255, 0, 20);
 FastSPI_LED.show();
 delay(delayTime);
 
 clearLeds();
 //lower v
 setRange(0, 128, 137,167);
 setRange(0, 128, 70, 99);
 FastSPI_LED.show();
 
 delay(delayTime);
 clearLeds();
 FastSPI_LED.show();
 delay(delayTime);
 
 //bottom ring
 setRange(0, 255, 369,396);
 setRange(0, 255, 396, 421);
 FastSPI_LED.show();
 delay(delayTime);
 
 clearLeds();
 //middle ring
 setRange(0, 255, 281,307);
 setRange(0, 255, 307, 331);
 FastSPI_LED.show();
 delay(delayTime);
 
 clearLeds();
 //upper ring
 setRange(0, 255, 199,222);
 setRange(0, 128, 222, 245);
 FastSPI_LED.show();
 delay(delayTime);
 
 //  leds[lastInputLed].r = 255;
 //  leds[lastInputLed].g = 0;
 //  leds[lastInputLed].b = 0;
 
 FastSPI_LED.show();
 }
 
 void playFrame()
 {
 // check time
 // clear leds
 clearLeds();
 // loop over the list of animations
 for (int i = 0;i<animationCount;i++)
 {
 //    animations[i]
 }
 // show the leds
 // delay until the next frame
 }
 
 
 
 int getLedFromSerial() {
 // if there's any serial available, read it:
 while (Serial.available() > 0) {
 
 // look for the next valid integer in the incoming serial stream:
 int iLed = Serial.parseInt();
 // look for the newline. That's the end of your
 // sentence:
 if (Serial.read() == '\n') {
 // constrain the values to 0 - 255 and invert
 // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
 iLed = constrain(iLed, 0, ledCount);
 Serial.print("led ");
 Serial.println(iLed);
 
 return iLed;
 }
 }
 }
 
 void colorFromAccelerormeter()
 {
 byte x = analogRead(A0);
 
 clearLeds();
 for (int i = 0;i < ledCount;i++)
 {
 if (x > 128)
 leds[i].r = x;
 else
 leds[i].b = x;
 }
 }
 
 void race(byte color, byte intensity, int first, int last)
 {
 for(int i = first;i< last;i++)
 {
 leds[i].r = intensity;
 }
 }
 
 void setRange(byte color, byte intensity, int first, int last)
 {
 for (int i = first; i < last;i++)
 {
 switch(color)
 {
 case 0:
 leds[i].r = intensity;
 break;
 case 1:
 leds[i].g = intensity;
 break;
 case 2:
 leds[i].b = intensity;
 break;
 }
 }
 
 }
 
 
 void progress() {
 for (int frame = 0;frame < ledCount;frame++)
 {
 clearLeds();
 for(int i = frame; i < ledCount; i++ )
 {
 leds[i].r = 255;
 leds[i].g = 0;
 leds[i].b = 0;
 }
 FastSPI_LED.show();
 delay(5);
 }
 }
 */