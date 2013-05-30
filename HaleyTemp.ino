#include "FastSPI_LED2.h"
#include "Segment.h"
#include "Animation.h"
#include "AnimationFrame.h"

const byte ledCount = 128;
const int strandCount = 7;
const int animationCount = 7;

const int frameCount = 44;

AnimationFrame frames[frameCount] =
{

    AnimationFrame(1250, RingTopBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, segments[RingTopBackRightInner] |segments[RingTopBackLeftInner] , BitFadeAnimation,55),
    AnimationFrame(0, segments[RingMiddleBackLeftInner] |segments[RingMiddleBackRightInner] , BitFadeAnimation,55),
    AnimationFrame(0, segments[VMiddleBackLeftMiddle] |segments[VMiddleBackRightMiddle] | segments[VMiddleBackLeftLower] | segments[VMiddleBackRightLower], BitFadeAnimation,55),

    
    AnimationFrame(2333, RingTopBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, segments[VBottomBackRightLower] |segments[VBottomBackLeftLower] | segments[VBottomBackLeftMiddle] | segments[VBottomBackRightMiddle], BitFadeAnimation,55),


    AnimationFrame(3417, RingTopBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, segments[RingTopBackRightInner] |segments[RingTopBackLeftInner] , BitFadeAnimation,55),
    AnimationFrame(0, segments[RingMiddleBackLeftInner] |segments[RingMiddleBackRightInner] , BitFadeAnimation,55),
    AnimationFrame(0, segments[VMiddleBackLeftMiddle] |segments[VMiddleBackRightMiddle] | segments[VMiddleBackLeftLower] | segments[VMiddleBackRightLower], BitFadeAnimation,55),

    AnimationFrame(4500, RingTopBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, segments[VBottomBackRightLower] |segments[VBottomBackLeftLower] | segments[VBottomBackLeftMiddle] | segments[VBottomBackRightMiddle], BitFadeAnimation,55),

    AnimationFrame(5625, RingTopBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, segments[RingTopBackRightInner] |segments[RingTopBackLeftInner] , BitFadeAnimation,55),
    AnimationFrame(0, segments[RingMiddleBackLeftInner] |segments[RingMiddleBackRightInner] , BitFadeAnimation,55),
    AnimationFrame(0, segments[VMiddleBackLeftMiddle] |segments[VMiddleBackRightMiddle] | segments[VMiddleBackLeftLower] | segments[VMiddleBackRightLower], BitFadeAnimation,55),
    
    AnimationFrame(6708, RingTopBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, segments[VBottomBackRightLower] |segments[VBottomBackLeftLower] | segments[VBottomBackLeftMiddle] | segments[VBottomBackRightMiddle], BitFadeAnimation,55),
    
    AnimationFrame(7792, RingTopBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, segments[VTopLeft] |segments[VTopRight] , BitFadeAnimation,55),

    AnimationFrame(8875, RingTopBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, segments[VMiddleBackLeftUpper] |segments[VMiddleBackRightUpper] , BitFadeAnimation,55),

    AnimationFrame(9950, RingTopBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackCenter, BitFadeAnimation, 55),

    AnimationFrame(11083, RingTopBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingMiddleBackCenter, BitFadeAnimation, 55),
    AnimationFrame(0, RingBottomBackCenter, BitFadeAnimation, 55),
};

// this is wasteful because I'm creating a square array and many
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
WS2811Controller800Mhz<12> LED1;    //RingTop
WS2811Controller800Mhz<9> LED2;     //RingMiddle
WS2811Controller800Mhz<6> LED3;     //RingMiddle
WS2811Controller800Mhz<3> LED4;     //VTop
WS2811Controller800Mhz<13> LED5;    //VMiddle
WS2811Controller800Mhz<16> LED6;    //VBottom
WS2811Controller800Mhz<19> LED7;    //Vertical

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int lastInputLed = 0;

long currentTime;
int currentFrame = 0;

long showRGBCounter = 0;
long timeSpentInShowRGB = 0;


void setup()
{
	Serial.begin(38400);
	LED1.init();
	LED2.init();
	LED3.init();
	LED4.init();
	LED5.init();
	LED6.init();
	LED7.init();
    
    currentTime = millis();
    
	pinMode(A0, INPUT);
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

int currentStep = 0;
int nextStepInSequence = 0;

long currentSequenceStartTime = 0;
long nextSequenceStartTime = 0;
long sequenceInterval = 0;

bool doAnimation = false;

void loop()
{
    if (Serial.available())
    {
        /*
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
        */
        
        // flush the serial buffer
        while(Serial.available())
              Serial.read();
        Serial.println("restarting");
        currentStep = 0;
        currentSequenceStartTime = millis();
        sequenceInterval = 0;
        doAnimation = true;
        
    }
    
    // if the current time is after the start of the next sequence
    // then I need to play all of the sequences that have the same time
    if (doAnimation == true && ((millis()*4) > currentSequenceStartTime + sequenceInterval))
    {
        Serial.print(millis() - currentSequenceStartTime);Serial.print("ms: ");Serial.print(currentStep);Serial.print(":");Serial.println(sequenceInterval);
        AnimationFrame f = frames[currentStep];

        //if (0 == currentStep)
        //    currentSequenceStartTime = millis();
        
        sequenceInterval = f.timeCode;
        Strand s = f.segment.strand;
        
        switch(f.animation)
        {
            case BitFadeAnimation:
                anims[s].bitFade(f.segment, 16, 1);
                anims[s].setColor(64,0,64);
                break;
            case NoAnimation:
                anims[s].clear();
                break;
        }
        
        currentStep++;
        if (currentStep > frameCount)
        {
            Serial.println("done with a loop");
            currentStep = 0;
            currentSequenceStartTime = millis();
            sequenceInterval = 0;
            doAnimation = false;
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
    updateLeds();
}


void updateLeds()
{
	LED1.showRGB((byte*)leds[0], ledCount);
	LED2.showRGB((byte*)leds[1], ledCount);
	LED3.showRGB((byte*)leds[2], ledCount);
	LED4.showRGB((byte*)leds[3], ledCount);
	LED5.showRGB((byte*)leds[4], ledCount);
	LED6.showRGB((byte*)leds[5], ledCount);
	LED7.showRGB((byte*)leds[6], ledCount);
    
    // showRGB pauses the timer that delay uses so this is to compensate
    //timeSpentInShowRGB += strandCount * (ledCount * 3 * 1.25)/1000;
    //Serial.print("time spent in showrgb ");Serial.println(timeSpentInShowRGB);
    
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