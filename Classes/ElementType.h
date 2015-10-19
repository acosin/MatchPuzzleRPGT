//
//  ElementType.h
//  MatchPuzzleRPGT
//
//

#ifndef ElementType_h
#define ElementType_h

#include <stdio.h>

enum class ElementType {
    RED,
    BLUE,
    YELLOW,
    GREEN,
    
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
};


#endif /* ElementType_h */
