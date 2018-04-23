// PEReader_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ConsoleLogger.h"
#include "Exceptions.h"
#include "Parser.h"

bool PrepareFileStream(std::ifstream& fin)
{
    std::cout << "Input file name -> ";
    std::string input;
    std::getline(std::cin, input);

    std::ifstream file(input, std::ios::binary);

    try
    {
        THROW_IF(!file.is_open(), "Invalid path to file: " << input);
        file.exceptions(std::ifstream::failbit);
        fin = std::move(file);
        return true;
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << '\n';
        return false;
    }
}

void Parse(std::istream& in)
{
    try
    {
        pe_parse::Parser parser(in);

        viewers::ConsoleLogger logger;
        parser.Show(logger);
    }
    catch (std::exception& ex)
    {
        std::cout << "\nInvalid PE file.\n" << ex.what() << '\n';
    }
}

int main()
{
    std::ifstream fin;
    if (!PrepareFileStream(fin))
    {
        return -1;
    }

    Parse(fin);
    return 0;
}

