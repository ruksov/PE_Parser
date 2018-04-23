#include "stdafx.h"
#include "Utils.h"

void ReadStringByOffset(std::istream& in, size_t offset, std::string & value)
{
    in.seekg(offset);
    char c = '\0';
    in >> c;
    
    while (c != '\0')
    {
        value.push_back(c);
        in >> c;
    }
}
