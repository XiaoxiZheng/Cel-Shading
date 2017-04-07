// ---------------------------------------------------------------
// Corey Toler-Franklin
// RGBR_f.cpp
// Color data
// 10 February 2006
// Copyright 
// RGBR_f.cpp
//-----------------------------------------------------------------

#include "RGBR_f.h"


RGBR_f::RGBR_f (void)
    : r		(0),
      g		(0),
      b		(0),
      a	    (0)
{
}

RGBR_f::RGBR_f(float red, float green, float blue, float alpha)
    : r       (red),
      g       (green),
      b       (blue),
      a       (alpha)
{
}

RGBR_f::~RGBR_f(void)
{
}
