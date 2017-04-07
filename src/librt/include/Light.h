//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Light.h
// A light object
//------------------------------------------------------------------------------



#ifndef __LIGHT_H__
#define __LIGHT_H__



#include <string>
#include "STVector3.h"
#include "RGBR_f.h"



class Light
{


public:
                                    Light                               (STVector3 position, RGBR_f color, std::string id = "");
                                    ~Light                              (void);

    
    void                            SetPosition                         (STVector3 position);
    STVector3                       GetPosition                         (void);

    void                            SetColor                            (RGBR_f color);
    RGBR_f                          GetColor                            (void);


private:

    // parameters
    STVector3                       m_position;

    RGBR_f                          m_color;

    std::string                     m_id;

};


#endif //__LIGHT_H__

