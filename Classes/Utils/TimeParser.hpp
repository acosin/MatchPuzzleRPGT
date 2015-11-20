//
//  TimeParser.h
//  MatchPuzzleRPGT
//

#pragma once

#include <time.h>
#include <string>

class TimeParser
{
public:
    static struct tm StringToTM(const std::string &str)
    {
        struct tm tm0;
        int i = sscanf(str.c_str(), "%d/%d/%d %d:%d:%d" ,
                       &(tm0.tm_year),
                       &(tm0.tm_mon),
                       &(tm0.tm_mday),
                       &(tm0.tm_hour),
                       &(tm0.tm_min),
                       &(tm0.tm_sec),
                       &(tm0.tm_wday),
                       &(tm0.tm_yday));
        
        tm0.tm_year -= 1900;
        tm0.tm_mon --;
        tm0.tm_isdst=-1;
        
        return tm0;
    }
    
    static std::string TMToString(const struct tm &tm0)
    {
        char buff[20];
        sprintf (buff, "%d/%d/%d %d:%d:%d",
                 tm0.tm_year,
                 tm0.tm_mon,
                 tm0.tm_mday,
                 tm0.tm_hour,
                 tm0.tm_min,
                 tm0.tm_sec);
        return string(buff);
    }
};