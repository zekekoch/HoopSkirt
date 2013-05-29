//
//  AnimationFrame.h
//  
//
//  Created by Zeke Koch on 5/25/13.
//
//

#ifndef _AnimationFrame_h
#define _AnimationFrame_h

#include "Animation.h"
#include "Segment.h"

//enum SegmentEnum;
static Segment segments[49] =
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
    Segment(RingTopBackCenter,      "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingTopBackRightInner,  "11111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingTopBackRightOuter,  "00000000111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingTopLeft,            "00000000000000011111111111111111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingTopFrontLeftOuter,  "00000000000000000000000000000000000011111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingTopFrontLeftInner,  "00000000000000000000000000000000000000000001111100000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingTopFrontRightInner, "00000000000000000000000000000000000000000000000111111000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingTopFrontRightOuter, "00000000000000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingTopRight,           "00000000000000000000000000000000000000000000000000000000000011111111111111111111000000000000000000000000000000000000000000000000"),
    Segment(RingTopBackLeftOuter,   "00000000000000000000000000000000000000000000000000000000000000000000000000000001111111110000000000000000000000000000000000000000"),
    Segment(RingTopBackLeftInner,   "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111111000000000000000000000000000000000"),
    
    /*** Ring Middle ***/
    Segment(RingMiddleBackCenter,       "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingMiddleBackRightInner,   "11111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingMiddleBackRightOuter,   "00001111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingMiddleLeft,             "00000000000001111111111111111111111111111111100000000000000000000000000000000000000000000000000000000"),
    Segment(RingMiddleFrontLeftInner,   "00000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000000000"),
    Segment(RingMiddleFrontRightInner,  "00000000000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000"),
    Segment(RingMiddleRight,            "00000000000000000000000000000000000000000000000000000000011111111111111111111111111111111000000000000"),
    Segment(RingMiddleBackLeftOuter,    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111110000"),
    Segment(RingMiddleBackLeftInner,    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111"),
    
    /*** Ring Bottom ***/
    Segment(RingBottomBackCenter,       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingBottomBackRightInner,   "1111111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(RingBottomLeft,             "0000000000111111111111111111111111111111111111111111100000000000000000000000000000000000000000000000000000"),
    Segment(RingBottomRight,            "0000000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111110000000000"),
    Segment(RingBottomBackLeftInner,    "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111111"),
    
    /*** VTop ***/
    // V Top (Center, Left, Right)
    Segment(VTopBackCenter,             "000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(VTopRight,                  "111111111111111111111111111111111111111110000000000000000000000000000000000000000"),
    Segment(VTopLeft,                   "000000000000000000000000000000000000000001111111111111111111111111111111111111111"),
    
    /*** VMiddle ***/
    Segment(VMiddleBackCenter,          "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(VMiddleBackLeftLower,       "1111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(VMiddleBackLeftMiddle,      "0000000111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(VMiddleBackLeftUpper,       "0000000000000011111111111111111111111111111111111000000000000000000000000000000000000000000000000000000000000000"),
    Segment(VMiddleFrontRightMiddle,    "0000000000000000000000000000000000000000000000000111111100000000000000000000000000000000000000000000000000000000"),
    Segment(VMiddleFrontLeftMiddle,     "0000000000000000000000000000000000000000000000000000000011111110000000000000000000000000000000000000000000000000"),
    Segment(VMiddleBackRightUpper,      "0000000000000000000000000000000000000000000000000000000000000001111111111111111111111111111111111110000000000000"),
    Segment(VMiddleBackRightMiddle,     "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111000000"),
    Segment(VMiddleBackRightLower,      "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111"),
    
    /*** V Bottom ***/
    Segment(VBottomBackCenter,          "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(VBottomBackRightLower,      "1111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(VBottomBackRightMiddle,     "0000011111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(VBottomBackRightTop,        "0000000000001111111111111111111111100000000000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(VBottomFrontLeftMiddle,     "0000000000000000000000000000000000111111110000000000000000000000000000000000000000000000000000000000000000000000"),
    Segment(VBottomFrontLeftLower,      "0000000000000000000000000000000000000000001111111110000000000000000000000000000000000000000000000000000000000000"),
    Segment(VBottomFrontRightLower,     "0000000000000000000000000000000000000000000000000001111111100000000000000000000000000000000000000000000000000000"),
    Segment(VBottomFrontRightMiddle,    "0000000000000000000000000000000000000000000000000000000000011111111000000000000000000000000000000000000000000000"),
    Segment(VBottomBackLeftTop,         "0000000000000000000000000000000000000000000000000000000000000000000111111111111111111111100000000000000000000000"),
    Segment(VBottomBackLeftMiddle,      "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111100000000000000000"),
    Segment(VBottomBackLeftLower,       "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111111111111111"),
    
    //TODO: add the vertical strand to this
};

class AnimationFrame
{
private:
    
public:
    Segment segment;
    long timeCode;
    AnimationType animation;
    int color;
    
public:

    AnimationFrame(long time, SegmentEnum s, AnimationType anim, int c)
    {
        timeCode = time;
        segment = segments[s];
        animation = anim;
        color = c;
    }

    AnimationFrame(long time, Segment s, AnimationType anim, int c)
    {
        timeCode = time;
        segment = s;
        animation = anim;
        color = c;
    }
    
};

#endif
