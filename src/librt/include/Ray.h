//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Ray.h 
// A Ray - origin and direction
//------------------------------------------------------------------------------------------------


#ifndef _RAY_H
#define _RAY_H

#include "STVector3.h"




class Ray {

public:

                                        Ray                         (void);
                                        ~Ray                        (void);

    STVector3                           Origin                      (void);
    STVector3                           Direction                   (void); 
    void                                SetOrigin                   (STVector3 point);
    void                                SetDirection                (STVector3 point);

private:

    STVector3                           m_origin;
    STVector3                           m_direction;
};


#endif //_RAY_H