/*
 *  librt.cpp
 *  librt
 *
 *  Created by XiaoxiZheng on 1/25/17.
 *  Copyright © 2017 XiaoxiZheng. All rights reserved.
 *
 */

#include <iostream>
#include "librt.hpp"
#include "librtPriv.hpp"

void librt::HelloWorld(const char * s)
{
    librtPriv *theObj = new librtPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void librtPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

