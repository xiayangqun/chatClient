//
//  Tools.cpp
//  chatDemo
//
//  Created by xiayangqun on 16/6/18.
//
//

#include "Tools.h"

std::string  Tools::timeSince1970ToTimeString(time_t timeSince1970)
{
    struct tm *p;
    p=gmtime(&timeSince1970);
    char s[80];
    strftime(s, 80, "%Y-%m-%d %H:%M:%S :", p);
    
    return std::string(s);
}
