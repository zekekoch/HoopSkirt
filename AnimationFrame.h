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

class AnimationFrame
{
public:
    SegmentEnum segment;
    long timeCode;
    AnimationType animation;
    int color;
    
public:
    AnimationFrame(long time, SegmentEnum s, AnimationType anim, int c)
    {
        timeCode = time;
        segment = s;
        animation = anim;
        color = c;
    }

};

#endif
