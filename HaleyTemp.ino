#include "FastSPI_LED2.h"
#include "Animation.h"
#include "Segment.h"
#include "AnimationFrame.h"

const byte ledCount = 128;
const int strandCount = 7;
const int animationCount = 7;

Segment segments[49] =
{
    /*** Ring Top ***/
    /*
    Segment(RingTopBackCenter,      0b00000000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(RingTopBackRightInner,  0b11111111000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(RingTopBackRightOuter,  0b00000000111111100000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(RingTopLeft,            0b00000000000000011111111111111111,0b11110000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(RingTopFrontLeftOuter,  0b00000000000000000000000000000000,0b00001111111000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(RingTopFrontLeftInner,  0b00000000000000000000000000000000,0b00000000000111110000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(RingTopFrontRightInner, 0b00000000000000000000000000000000,0b00000000000000011111100000000000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(RingTopFrontRightOuter, 0b00000000000000000000000000000000,0b00000000000000000000011111110000,0b00000000000000000000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(RingTopRight,           0b00000000000000000000000000000000,0b00000000000000000000000000001111,0b11111111111111110000000000000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(RingTopBackLeftOuter,   0b00000000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000011111111100000000,0b00000000000000000000000000000000,95, RingTop),
    Segment(RingTopBackLeftInner,   0b00000000000000000000000000000000,0b00000000000000000000000000000000,0b00000000000000000000000111111110,0b00000000000000000000000000000000,95, RingTop),
    */
    Segment(RingTopBackCenter,      "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", RingTop),
    Segment(RingTopBackRightInner,  "11111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", RingTop),
    Segment(RingTopBackRightOuter,  "00000000111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", RingTop),
    Segment(RingTopLeft,            "00000000000000011111111111111111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", RingTop),
    Segment(RingTopFrontLeftOuter,  "00000000000000000000000000000000000011111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000", RingTop),
    Segment(RingTopFrontLeftInner,  "00000000000000000000000000000000000000000001111100000000000000000000000000000000000000000000000000000000000000000000000000000000", RingTop),
    Segment(RingTopFrontRightInner, "00000000000000000000000000000000000000000000000111111000000000000000000000000000000000000000000000000000000000000000000000000000", RingTop),
    Segment(RingTopFrontRightOuter, "00000000000000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000000000000000000000000000", RingTop),
    Segment(RingTopRight,           "00000000000000000000000000000000000000000000000000000000000011111111111111111111000000000000000000000000000000000000000000000000", RingTop),
    Segment(RingTopBackLeftOuter,   "00000000000000000000000000000000000000000000000000000000000000000000000000000001111111110000000000000000000000000000000000000000", RingTop),
    Segment(RingTopBackLeftInner,   "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111111000000000000000000000000000000000", RingTop),

    /*** Ring Middle ***/
    Segment(RingMiddleBackCenter,       "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", RingMiddle),
    Segment(RingMiddleBackRightInner,   "11111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", RingMiddle),
    Segment(RingMiddleBackRightOuter,   "00001111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", RingMiddle),
    Segment(RingMiddleLeft,             "00000000000001111111111111111111111111111111100000000000000000000000000000000000000000000000000000000", RingMiddle),
    Segment(RingMiddleFrontLeftInner,   "00000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000000000", RingMiddle),
    Segment(RingMiddleFrontRightInner,  "00000000000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000", RingMiddle),
    Segment(RingMiddleRight,            "00000000000000000000000000000000000000000000000000000000011111111111111111111111111111111000000000000", RingMiddle),
    Segment(RingMiddleBackLeftOuter,    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111110000", RingMiddle),
    Segment(RingMiddleBackLeftInner,    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111", RingMiddle),

    /*** Ring Bottom ***/
    Segment(RingBottomBackCenter,       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", RingBottom),
    Segment(RingBottomBackRightInner,   "1111111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", RingBottom),
    Segment(RingBottomLeft,             "0000000000111111111111111111111111111111111111111111100000000000000000000000000000000000000000000000000000", RingBottom),
    Segment(RingBottomRight,            "0000000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111110000000000", RingBottom),
    Segment(RingBottomBackLeftInner,    "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111111", RingBottom),
        
    /*** VTop ***/
    // V Top (Center, Left, Right)
    Segment(VTopBackCenter,             "000000000000000000000000000000000000000000000000000000000000000000000000000000000", VTop),
    Segment(VTopRight,                  "111111111111111111111111111111111111111110000000000000000000000000000000000000000", VTop),
    Segment(VTopLeft,                   "000000000000000000000000000000000000000001111111111111111111111111111111111111111", VTop),
    
    /*** VMiddle ***/
    Segment(VMiddleBackCenter,          "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", VMiddle),
    Segment(VMiddleBackLeftLower,       "1111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", VMiddle),
    Segment(VMiddleBackLeftMiddle,      "0000000111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", VMiddle),
    Segment(VMiddleBackLeftUpper,       "0000000000000011111111111111111111111111111111111000000000000000000000000000000000000000000000000000000000000000", VMiddle),
    Segment(VMiddleFrontRightMiddle,    "0000000000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000000000000000", VMiddle),
    Segment(VMiddleFrontLeftMiddle,     "0000000000000000000000000000000000000000000000000000000011111110000000000000000000000000000000000000000000000000", VMiddle),
    Segment(VMiddleBackRightUpper,      "0000000000000000000000000000000000000000000000000000000000000001111111111111111111111111111111111110000000000000", VMiddle),
    Segment(VMiddleBackRightMiddle,     "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111000000", VMiddle),
    Segment(VMiddleBackRightLower,      "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111", VMiddle),

    /*** V Bottom ***/
    Segment(VBottomBackCenter,          "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", VBottom),
    Segment(VBottomBackRightLower,      "1111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", VBottom),
    Segment(VBottomBackRightMiddle,     "0000011111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", VBottom),
    Segment(VBottomBackRightTop,        "0000000000001111111111111111111111100000000000000000000000000000000000000000000000000000000000000000000000000000", VBottom),
    Segment(VBottomFrontLeftMiddle,     "0000000000000000000000000000000000111111110000000000000000000000000000000000000000000000000000000000000000000000", VBottom),
    Segment(VBottomFrontLeftLower,      "0000000000000000000000000000000000000000001111111110000000000000000000000000000000000000000000000000000000000000", VBottom),
    Segment(VBottomFrontRightLower,     "0000000000000000000000000000000000000000000000000001111111100000000000000000000000000000000000000000000000000000", VBottom),
    Segment(VBottomFrontRightMiddle,    "0000000000000000000000000000000000000000000000000000000000011111111000000000000000000000000000000000000000000000", VBottom),
    Segment(VBottomBackLeftTop,         "0000000000000000000000000000000000000000000000000000000000000000000111111111111111111111100000000000000000000000", VBottom),
    Segment(VBottomBackLeftMiddle,      "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111100000000000000000", VBottom),
    Segment(VBottomBackLeftLower,       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111111111111111", VBottom),
    
    //TODO: add the vertical strand to this
};

const int FrameCount = 53;
AnimationFrame frames[FrameCount] =
{

    AnimationFrame(0, RingTopBackRightInner, BitFadeAnimation, 55),
    AnimationFrame(0, RingTopBackRightOuter, BitFadeAnimation, 55),
    AnimationFrame(0, RingTopLeft, BitFadeAnimation, 55),
    AnimationFrame(0, RingTopFrontLeftOuter, BitFadeAnimation, 55),
    AnimationFrame(0, RingTopFrontLeftInner, BitFadeAnimation, 55),
    AnimationFrame(0, RingTopFrontRightInner, BitFadeAnimation, 55),
    AnimationFrame(0, RingTopFrontRightOuter, BitFadeAnimation, 55),
    AnimationFrame(0, RingTopRight, BitFadeAnimation, 55),
    AnimationFrame(0, RingTopBackLeftOuter, BitFadeAnimation, 55),
    AnimationFrame(0, RingTopBackLeftInner, BitFadeAnimation, 55),
    AnimationFrame(0, RingTopBackCenter, BitFadeAnimation, 55),
    
    AnimationFrame(1000, RingMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackRightInner, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackRightOuter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleLeft, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleFrontLeftInner, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleFrontRightInner, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleFrontRightInner, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleRight, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackLeftOuter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackLeftInner, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackCenter, BitFadeAnimation, 55),
    
    AnimationFrame(1500, RingBottomBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackRightInner, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomLeft, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomRight, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackLeftInner, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackCenter, BitFadeAnimation, 55),
    
    AnimationFrame(2000, VTopBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, VTopRight, BitFadeAnimation, 55),
    AnimationFrame(0, VTopLeft, BitFadeAnimation, 55),
    AnimationFrame(0, VTopBackCenter, BitFadeAnimation, 55),
    
    AnimationFrame(3000, VMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, VMiddleBackLeftLower, BitFadeAnimation, 55),
    AnimationFrame(0, VMiddleBackLeftMiddle, BitFadeAnimation, 55),
    AnimationFrame(0, VMiddleBackLeftUpper, BitFadeAnimation, 55),
    AnimationFrame(0, VMiddleFrontRightMiddle, BitFadeAnimation, 55),
    AnimationFrame(0, VMiddleFrontLeftMiddle, BitFadeAnimation, 55),
    AnimationFrame(0, VMiddleBackRightUpper, BitFadeAnimation, 55),
    AnimationFrame(0, VMiddleBackRightMiddle, BitFadeAnimation, 55),
    AnimationFrame(0, VMiddleBackRightLower, BitFadeAnimation, 55),
    AnimationFrame(0, VMiddleBackCenter, BitFadeAnimation, 55),
    
    AnimationFrame(4000, VBottomBackRightLower, BitFadeAnimation, 55),
    AnimationFrame(0, VBottomBackRightMiddle, BitFadeAnimation, 55),
    AnimationFrame(0, VBottomBackRightTop, BitFadeAnimation, 55),
    AnimationFrame(0, VBottomFrontLeftMiddle, BitFadeAnimation, 55),
    AnimationFrame(0, VBottomFrontLeftLower, BitFadeAnimation, 55),
    AnimationFrame(0, VBottomFrontRightLower, BitFadeAnimation, 55),
    AnimationFrame(0, VBottomFrontRightMiddle, BitFadeAnimation, 55),
    AnimationFrame(0, VBottomBackLeftTop, BitFadeAnimation, 55),
    AnimationFrame(0, VBottomBackLeftMiddle, BitFadeAnimation, 55),
    AnimationFrame(0, VBottomBackLeftLower, BitFadeAnimation, 55),
    AnimationFrame(0, VBottomBackCenter, BitFadeAnimation, 55),
    
    
    
};

// this is incredibly wasteful because I'm creating a square array and many
// of my strands are much shorter than ledCount, but this makes it easier for
// me to initialize and for now I have the space to spare.
// TODO: change this to a ragged array.
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

long currentTime;
int currentFrame = 0;

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
    
    currentTime = millis();
    
    // run the memory test function and print the results to the serial port
    //int result = memoryTest();
    //Serial.print("Memory test results: ");
    //Serial.print(result,DEC);
    //Serial.print(" bytes free");
    
	pinMode(A0, INPUT);

    /*
    
    anims[VBottom].bitFade(segments[VBottomBackLeftLower] | segments[VBottomBackLeftLower], 16,1);
    anims[VBottom].setColor(0,2,0);
    */
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

int currentSequence = 0;
int nextStepInSequence = 0;

long currentSequenceStartTime = 0;
long nextSequenceStartTime = 0;

long sequenceInterval = 10;


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
    
    // if the current time is after the start of the next sequence
    // then I need to play all of the sequences that have the same time
    if (millis() > currentSequenceStartTime + sequenceInterval)
    {
        AnimationFrame f = frames[currentSequence];

        if (0 == currentSequence)
            currentSequenceStartTime = millis();
        
        sequenceInterval = f.timeCode;
        
        Strand s = segments[f.segment].strand;
        switch(f.animation)
        {
            case BitFadeAnimation:
            //    anims[s].clear();
                anims[s].bitFade(segments[f.segment], 16, 1);
                anims[s].setColor(4,4,0);
                break;
            case NoAnimation:
            //    anims[s].clear();
                break;
        }
        
        currentSequence++;
        if (FrameCount < currentSequence)
        {
            currentSequence = 0;
        }
    }
    
    
    for(int i = 0;i<animationCount;i++)
    {
        anims[i].play();
    }
    
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