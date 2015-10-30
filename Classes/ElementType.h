//
//  ElementType.h
//  MatchPuzzleRPGT
//
//

#ifndef ElementType_h
#define ElementType_h

#include <stdio.h>

enum class ElementType {
    RED = 0,
    BLUE,
    YELLOW,
    GREEN, // = count - 1
    
    count
};

class ElementTypeUtils
{
public:
    static std::string getResourceFilename(ElementType type)
    {
        char name[100] = {0};
        //TODO: may change image resource path here!
        sprintf(name, "element_%d.png", (int)type);
        return std::string(name);
    }
    
    //too dirty
    static std::string toString(ElementType type)
    {
        switch (type) {
            case ElementType::RED:     return "RED";
            case ElementType::BLUE:    return "BLUE";
            case ElementType::YELLOW:  return "YELLOW";
            case ElementType::GREEN:   return "GREEN";
            default:                   return NULL;
        }
    }
};


#endif /* ElementType_h */
