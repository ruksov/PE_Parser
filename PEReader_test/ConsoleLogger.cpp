#include "stdafx.h"
#include "ConsoleLogger.h"
#include "DosHeader.h"
#include "NtHeader.h"
#include "SectionTable.h"
#include "ImportTable.h"
#include "ExportTable.h"

namespace viewers
{
    ConsoleLogger::~ConsoleLogger()
    {
        std::cout << m_divider;
    }

    void ConsoleLogger::HandleDosHeader(pe_parse::DosHeader & dosHeader)
    {
        auto& header = dosHeader.GetDosHeader();

        std::cout << m_divider << "Dos header:";

        std::cout << "\n\n\tMagic number: " << std::hex << header.e_magic;
        std::cout << "\n\tBytes on last page of file: " << std::hex << header.e_cblp;
        std::cout << "\n\tPages in file: " << std::hex << header.e_cp;
        std::cout << "\n\tRelocations: " << std::hex << header.e_crlc;
        std::cout << "\n\tSize of header in paragraphs: " << std::hex << header.e_cparhdr;
        std::cout << "\n\tMinimum extra paragraphs needed: " << std::hex << header.e_minalloc;
        std::cout << "\n\tMaximum extra paragraphs needed: " << std::hex << header.e_maxalloc;
        std::cout << "\n\tInitial(relative) SS value: " << std::hex << header.e_ss;
        std::cout << "\n\tInitial SP value: " << std::hex << header.e_sp;
        std::cout << "\n\tChecksum: " << std::hex << header.e_csum;
        std::cout << "\n\tInitial IP value: " << std::hex << header.e_ip;
        std::cout << "\n\tInitial(relative) CS value: " << std::hex << header.e_cs;
        std::cout << "\n\tFile address of relocation table: " << std::hex << header.e_lfarlc;
        std::cout << "\n\tOverlay number: " << std::hex << header.e_ovno;
        std::cout << "\n\tOEM identifier(for e_oeminfo): " << std::hex << header.e_oemid;
        std::cout << "\n\tOEM information; e_oemid specific: " << std::hex << header.e_oeminfo;
        std::cout << "\n\tFile address of new exe header: " << std::hex << header.e_lfanew;
    }

    void ConsoleLogger::HandleNtHeader(pe_parse::NtHeader & ntHeader)
    {
        auto& header = ntHeader.GetNtHeader();

        std::cout << m_divider << "Nt header:";

        std::cout << "\n\n\tFile header:";
        auto& fileHeader = header.FileHeader;

        std::cout << "\n\n\t\tMachine: " << std::hex << fileHeader.Machine;
        std::cout << "\n\t\tNumberOfSections: " << std::hex << fileHeader.NumberOfSections;
        std::cout << "\n\t\tTimeDateStamp: " << std::hex << fileHeader.TimeDateStamp;
        std::cout << "\n\t\tPointerToSymbolTable: " << std::hex << fileHeader.PointerToSymbolTable;
        std::cout << "\n\t\tNumberOfSymbols: " << std::hex << fileHeader.NumberOfSymbols;
        std::cout << "\n\t\tSizeOfOptionalHeader: " << std::hex << fileHeader.SizeOfOptionalHeader;
        std::cout << "\n\t\tCharacteristics: " << std::hex << fileHeader.Characteristics;

        std::cout << "\n\n\tOptional Header:";
        auto& optHeader = header.OptionalHeader;

        std::cout<<"\n\n\t\tMagic: "                          <<std::hex << optHeader.Magic;
        std::cout<<"\n\t\tMajorLinkerVersion: "             <<std::hex << static_cast<short>(optHeader.MajorLinkerVersion);
        std::cout<<"\n\t\tMinorLinkerVersion: "             <<std::hex << static_cast<short>(optHeader.MinorLinkerVersion);
        std::cout<<"\n\t\tSizeOfCode: "                     <<std::hex << optHeader.SizeOfCode;
        std::cout<<"\n\t\tSizeOfInitializedData: "          <<std::hex << optHeader.SizeOfInitializedData;
        std::cout<<"\n\t\tSizeOfUninitializedData: "        <<std::hex << optHeader.SizeOfUninitializedData;
        std::cout<<"\n\t\tAddressOfEntryPoint: "            <<std::hex << optHeader.AddressOfEntryPoint;
        std::cout<<"\n\t\tBaseOfCode: "                     <<std::hex << optHeader.BaseOfCode;
        std::cout<<"\n\t\tImageBase: "                      <<std::hex << optHeader.ImageBase;
        std::cout<<"\n\t\tSectionAlignment: "               <<std::hex << optHeader.SectionAlignment;
        std::cout<<"\n\t\tFileAlignment: "                  <<std::hex << optHeader.FileAlignment;
        std::cout<<"\n\t\tMajorOperatingSystemVersion: "    <<std::hex << optHeader.MajorOperatingSystemVersion;
        std::cout<<"\n\t\tMinorOperatingSystemVersion: "    <<std::hex << optHeader.MinorOperatingSystemVersion;
        std::cout<<"\n\t\tMajorImageVersion: "              <<std::hex << optHeader.MajorImageVersion;
        std::cout<<"\n\t\tMinorImageVersion: "              <<std::hex << optHeader.MinorImageVersion;
        std::cout<<"\n\t\tMajorSubsystemVersion: "          <<std::hex << optHeader.MajorSubsystemVersion;
        std::cout<<"\n\t\tMinorSubsystemVersion: "          <<std::hex << optHeader.MinorSubsystemVersion;
        std::cout<<"\n\t\tWin32VersionValue: "              <<std::hex << optHeader.Win32VersionValue;
        std::cout<<"\n\t\tSizeOfImage: "                    <<std::hex << optHeader.SizeOfImage;
        std::cout<<"\n\t\tSizeOfHeaders: "                  <<std::hex << optHeader.SizeOfHeaders;
        std::cout<<"\n\t\tCheckSum: "                       <<std::hex << optHeader.CheckSum;
        std::cout<<"\n\t\tSubsystem: "                      <<std::hex << optHeader.Subsystem;
        std::cout<<"\n\t\tDllCharacteristics: "             <<std::hex << optHeader.DllCharacteristics;
        std::cout<<"\n\t\tSizeOfStackReserve: "             <<std::hex << optHeader.SizeOfStackReserve;
        std::cout<<"\n\t\tSizeOfStackCommit: "              <<std::hex << optHeader.SizeOfStackCommit;
        std::cout<<"\n\t\tSizeOfHeapReserve: "              <<std::hex << optHeader.SizeOfHeapReserve;
        std::cout<<"\n\t\tSizeOfHeapCommit: "               <<std::hex << optHeader.SizeOfHeapCommit;
        std::cout<<"\n\t\tLoaderFlags: "                    <<std::hex << optHeader.LoaderFlags;
        std::cout<<"\n\t\tNumberOfRvaAndSizes: "            <<std::hex << optHeader.NumberOfRvaAndSizes;

        std::cout << "\n\n\tData Directories:\n";
        for (size_t i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; ++i)
        {
            std::cout << "\n\t\t" << i + 1 << ") Virtial Address: 0x" << std::hex << optHeader.DataDirectory[i].VirtualAddress;
            std::cout << "\n\t\tSize: " << std::hex << optHeader.DataDirectory[i].Size;
        }
    }

    void ConsoleLogger::HandleSectionTable(pe_parse::SectionTable & sectionTable)
    {
        auto& sections = sectionTable.GetSections();

        std::cout << m_divider << "Section table:";

        size_t i = 0;
        for (const auto& section : sections)
        {
            std::cout << "\n\n\tSection header " << ++i;

            std::cout << "\n\n\t\tName: " << section.Name;
            std::cout << "\n\t\tPhysicalAddress: 0x" << std::hex << section.Misc.PhysicalAddress;
            std::cout << "\n\t\tVirtualSize: " << section.Misc.VirtualSize;
            std::cout << "\n\t\tVirtualAddress: 0x" << std::hex << section.VirtualAddress;
            std::cout << "\n\t\tSizeOfRawData: " << section.SizeOfRawData;
            std::cout << "\n\t\tPointerToRawData: 0x" << std::hex << section.PointerToRawData;
            std::cout << "\n\t\tPointerToRelocations: 0x" << std::hex << section.PointerToRelocations;
            std::cout << "\n\t\tPointerToLinenumbers: 0x" << std::hex << section.PointerToLinenumbers;
            std::cout << "\n\t\tNumberOfRelocations: " << section.NumberOfRelocations;
            std::cout << "\n\t\tNumberOfLinenumbers: " << section.NumberOfLinenumbers;
            std::cout << "\n\t\tCharacteris: " << std::hex << section.Characteristics;
        }
    }

    void ConsoleLogger::HandleImportTable(pe_parse::ImportTable & importTable)
    {
        auto& importModules = importTable.GetImportTable();
        
        std::cout << std::dec << m_divider << "Import table:";

        if (importModules.empty())
        {
            std::cout << " Empry";
            return;
        }

        for (const auto& module : importModules)
        {
            std::cout << "\n\n\tImport module: " << module.Name;

            std::cout << "\n\n\t\tNameVa: 0x" << std::hex << module.Descriptor.Name;
            std::cout << "\n\t\tCharacteristics: " << module.Descriptor.Characteristics;
            std::cout << "\n\t\tOriginalFirstThunk: 0x" << module.Descriptor.OriginalFirstThunk;
            std::cout << "\n\t\tTimeDataStamp: " << module.Descriptor.TimeDateStamp;
            std::cout << "\n\t\tForwarderChain: " << module.Descriptor.ForwarderChain;
            std::cout << "\n\t\tFirstThunk: 0x" << module.Descriptor.FirstThunk;

            std::cout << "\n\t\tFunctions: ";
            size_t fc = 0;
            for (const auto& func : module.Functions)
            {
                std::cout << "\n\t\t\t" << std::dec << ++fc << ") Hint: " << std::hex << func.Hint;
                std::cout << "\n\t\t\tName: " << func.Name;
            }

            std::cout << "\n\t\tFunction ords: ";
            if (module.FunctionOrdinals.empty())
            {
                std::cout << "Empty";
                break;
            }

            fc = 0;
            for (const auto& ords : module.FunctionOrdinals)
            {
                std::cout << "\n\t\t\t" << std::dec << ++fc << ") Ordinal: " << std::hex << ords;
            }
        }
    }

    void ConsoleLogger::HandleExportTable(pe_parse::ExportTable & exportTable)
    {
        auto& exportHeader = exportTable.GetHeader();
        auto& functions = exportTable.GetFunctions();

        std::cout << m_divider << "Export table:";

        if (functions.empty())
        {
            std::cout << " Empty";
            return;
        }

        std::cout << "\n\tCharacteristics: " << std::hex << exportHeader.Characteristics;
        std::cout << "\n\tTimeDateStamp: " << std::hex << exportHeader.TimeDateStamp;
        std::cout << "\n\tMajorVersion: " << std::hex << exportHeader.MajorVersion;
        std::cout << "\n\tMinorVersion: " << std::hex << exportHeader.MinorVersion;
        std::cout << "\n\tName RVA: 0x" << std::hex << exportHeader.Name;
        std::cout << "\n\tBase: " << exportHeader.Base;
        std::cout << "\n\tNumberOfFunctions: " << std::dec << exportHeader.NumberOfFunctions;
        std::cout << "\n\tNumberOfNames: " << std::dec << exportHeader.NumberOfNames;
        std::cout << "\n\tAddressOfFunctions: 0x" << std::hex << exportHeader.AddressOfFunctions;
        std::cout << "\n\tAddressOfNames: 0x" << std::hex << exportHeader.AddressOfNames;
        std::cout << "\n\tAddressOfNameOrdinals: 0x" << std::hex << exportHeader.AddressOfNameOrdinals;

        std::cout << "\n\n\t Export functions:";

        size_t i = 0;
        for (const auto& func : functions)
        {
            std::cout << "\n\t\t" << std::dec << ++i << ") ";
            if (func.Name.empty())
            {
                std::cout << "Export by ordinal:";
            }
            else
            {
                std::cout << "Export by name:";
                std::cout << "\n\t\t\tName: " << func.Name << (func.ForwardNameOpt.empty() ? "" : " (forwarding export " + func.ForwardNameOpt + ")");
                std::cout << "\n\t\t\tName index: " << std::hex << func.IndexOfName;
            }
            std::cout << "\n\t\t\tOrdinal: " << std::hex << func.Ordinal;
            std::cout << "\n\t\t\tRVA: 0x" << std::hex << func.Rva;
        }
    }
}