#include "FastSPI_LED2.h"
#include "constants.h"
#include "Segment.h"
#include "Animation.h"
#include "Strand.h"
#include "Segment.h"
#include "AnimationFrame.h"

const int ledCount = 128;
const int strandCount = 7;

//CHSV c = CHSV(214,255,255);
CHSV c = CHSV(214,255,255);

AnimationFrame frames[] =
{

    AnimationFrame(0, AllOff, BitHSVFadeAnimation, c),
    AnimationFrame(0, segments[RingTopBackRightInner] |segments[RingTopBackLeftInner] , BitHSVFadeAnimation,c),
    AnimationFrame(1250, segments[VMiddleBackLeftMiddle] |segments[VMiddleBackRightMiddle] | segments[VMiddleBackLeftLower] | segments[VMiddleBackRightLower], BitHSVFadeAnimation,c),

    
    AnimationFrame(0, AllOff, BitHSVFadeAnimation, c),
    AnimationFrame(2333, segments[VTopLeft] | segments[VTopRight], BitHSVFadeAnimation,c),


    AnimationFrame(0, AllOff, BitHSVFadeAnimation, c),
    AnimationFrame(0, segments[RingTopBackRightInner] |segments[RingTopBackLeftInner] , BitHSVFadeAnimation,c),
    AnimationFrame(3417, segments[VMiddleBackLeftMiddle] |segments[VMiddleBackRightMiddle] | segments[VMiddleBackLeftLower] | segments[VMiddleBackRightLower], BitHSVFadeAnimation,c),

    AnimationFrame(0, AllOff, BitHSVFadeAnimation, c),
    AnimationFrame(4500, segments[VTopLeft] | segments[VTopRight], BitHSVFadeAnimation,c),

    AnimationFrame(0, AllOff, BitHSVFadeAnimation, c),
    AnimationFrame(0, segments[RingTopBackRightInner] |segments[RingTopBackLeftInner] , BitHSVFadeAnimation,c),
    AnimationFrame(5625, segments[VMiddleBackLeftMiddle] |segments[VMiddleBackRightMiddle] | segments[VMiddleBackLeftLower] | segments[VMiddleBackRightLower], BitHSVFadeAnimation,c),
    
    AnimationFrame(0, AllOff, BitHSVFadeAnimation, c),
    AnimationFrame(6708, segments[VTopLeft] | segments[VTopRight], BitHSVFadeAnimation,c),
    
    AnimationFrame(0, AllOff, BitHSVFadeAnimation, c),
    AnimationFrame(7792, segments[VTopLeft] |segments[VTopRight] , BitHSVFadeAnimation,c),

    AnimationFrame(0, AllOn, BitHSVFadeAnimation, c),
    AnimationFrame(8875, segments[VMiddleBackLeftUpper] |segments[VMiddleBackRightUpper] , BitHSVFadeAnimation,c),

    AnimationFrame(9950, AllOn, BitHSVFadeAnimation,c),

};

const constexpr int frameCount = sizeof(frames) / sizeof(frames[0]);



// this is wasteful because I'm creating a square array and many
// of my strands are much shorter than ledCount, but this makes it easier for
// me to initialize and for now I have the space to spare.
// TODO: change this to a ragged array.
//struct CRGB leds[strandCount][ledCount];
struct CRGB leds[strandCount][ledCount];

Animation anims[] =
{
    Animation(12, leds[RingTop], ledCount),
    Animation(9, leds[RingMiddle], ledCount),
    Animation(6, leds[RingBottom], ledCount),
    Animation(3, leds[VTop], ledCount),
    Animation(13, leds[VMiddle], ledCount),
    Animation(16, leds[VBottom], ledCount),
    Animation(19, leds[Vertical], ledCount)
};
const constexpr int animationCount = sizeof(anims) / sizeof(anims[0]);


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int lastInputLed = 0;

long currentTime;
int currentFrame = 0;

long showRGBCounter = 0;
long timeSpentInShowRGB = 0;


void setup()
{
    delay(1000);
    
    // For safety (to prevent too high of a power draw), the test case defaults to
   	// setting brightness to 25% brightness
    LEDS.setBrightness(255);
    
   	LEDS.addLeds<WS2811,12>(leds[0], ledCount);
   	LEDS.addLeds<WS2811,9>(leds[1], ledCount);
   	LEDS.addLeds<WS2811,6>(leds[2], ledCount);
   	LEDS.addLeds<WS2811,3>(leds[3], ledCount);
   	LEDS.addLeds<WS2811,13>(leds[4], ledCount);
   	LEDS.addLeds<WS2811,16>(leds[5], ledCount);
   	LEDS.addLeds<WS2811,19>(leds[6], ledCount);


	Serial.begin(38400);

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

bool doAnimation = true;

void loop()
{
    if (Serial.available())
    {
        Serial.print (sizeof(frames));Serial.print(" ");Serial.print(sizeof(frames[0]));Serial.println();
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
    if (doAnimation == true && ((millis()) > currentSequenceStartTime + sequenceInterval))
    {
        Serial.print(millis() - currentSequenceStartTime);Serial.print("ms: ");Serial.print(currentStep);Serial.print(":");Serial.println(sequenceInterval);
        AnimationFrame f = frames[currentStep];
        Serial.println(f.toString());
        //if (0 == currentStep)
        //    currentSequenceStartTime = millis();
        
        sequenceInterval = f.timeCode;
        StrandEnum s = f.segment.strand;
        
        
        Serial.print("segment ");Serial.print("|");Serial.print(s);Serial.println();
        
        if (AllStrands == s)
        {
            Serial.println("setting all");
            
            // todo: right now I'm assuming that each strand it only playing one animation
            for (int i = 0;i < strandCount;i++)
            {
                anims[i].bitFade(f.segment, 16, 1);
                anims[i].setColor(255,255,255);
            }
                
        } else
        {
            switch(f.animation)
            {
                case BitFadeAnimation:
                    anims[s].bitFade(f.segment, 16, 1);
                    anims[s].setColor(64,0,64);
                    break;
                case BitHSVFadeAnimation:
                    anims[s].bitHSVFade(f.segment, f.hsvColor, 1);
                    break;
                case NoAnimation:
                    anims[s].clear();
                    break;
            }
        }
        currentStep++;
        if (currentStep > frameCount)
        {
            Serial.println("done with a loop");
            currentStep = 0;
            currentSequenceStartTime = millis();
            sequenceInterval = 0;
            //doAnimation = false;
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

long lastLedUpdateTime = 0;
void updateLeds()
{
    //long tempTime = millis();
    //Serial.print("updateLeds ");Serial.print(millis() - lastLedUpdateTime);
    //lastLedUpdateTime = millis();
    LEDS.show();
    //tempTime = millis();
    //Serial.print(" updatedLeds ");Serial.print(tempTime - lastLedUpdateTime);Serial.println();
    //lastLedUpdateTime = millis();
    
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