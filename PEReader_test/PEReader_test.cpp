// PEReader_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::cout << "Input file name -> ";
    std::string input;
    std::getline(std::cin, input);

    std::ifstream file(input, std::ios::binary);
    file.exceptions(std::ifstream::failbit);
    if (!file.is_open())
    {
        std::cout << "Invalid path to file\n";
        return -1;
    }

    bool isPeFile = false;

    try {

        WORD dosSign = 0;
        file.seekg(0);
        file.read(reinterpret_cast<PCHAR>(&dosSign), sizeof(dosSign));

        if (dosSign == IMAGE_DOS_SIGNATURE)
        {
            file.seekg(offsetof(IMAGE_DOS_HEADER, e_lfanew));
            LONG peOffset = 0;
            file.read(reinterpret_cast<PCHAR>(&peOffset), sizeof(peOffset));

            file.seekg(peOffset);
            DWORD ntSign = 0;
            file.read(reinterpret_cast<PCHAR>(&ntSign), sizeof(ntSign));
            isPeFile = ntSign == IMAGE_NT_SIGNATURE;
        }
    }
    catch (std::ios_base::failure& fail)
    {
        // nothing
    }

    std::cout << (isPeFile ? "Valid" : "Invalid") << " PE file\n";
    return 0;
}

