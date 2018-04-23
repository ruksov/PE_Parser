#include "stdafx.h"
#include "ExportTable.h"
#include "Utils.h"
#include "Exceptions.h"

namespace pe_parse
{
    ExportTable::ExportTable(std::istream & in, DWORD vaTableOffset, const std::vector<IMAGE_SECTION_HEADER>& sections)
    {
        if (vaTableOffset == 0)
        {
            return;
        }

        // Find owner section for calculating raw offset
        auto ownerSection = std::find_if(sections.begin(), sections.end(), 
            [vaTableOffset](const IMAGE_SECTION_HEADER& section)
        {
            return section.VirtualAddress <= vaTableOffset && vaTableOffset < section.VirtualAddress + section.Misc.VirtualSize;
        });

        THROW_IF(ownerSection == sections.end(), "Couldn't find owner section for export table");

        // Read Export Table Header
        ReadValueByOffset(in, GetRawOffset(vaTableOffset, *ownerSection), m_header);

        // Create bool array for checking function ordinals
        std::vector<bool> setFunctions(m_header.NumberOfFunctions);
        std::fill(setFunctions.begin(), setFunctions.end(), false);

        for (WORD i = 0; i < m_header.NumberOfNames; ++i)
        {
            FuncInfo funcInfo;
            funcInfo.IndexOfName = i;

            // Read RVA of function name
            DWORD nameRva = 0;
            ReadValueByOffset(in, GetRawOffset(m_header.AddressOfNames, *ownerSection) + i * sizeof(nameRva), nameRva);

            // Convert name RVA to RAW pointer
            // And read name
            ReadStringByOffset(in, GetRawOffset(nameRva, *ownerSection), funcInfo.Name);

            // Get ordinal from ordinal table
            ReadValueByOffset(in, GetRawOffset(m_header.AddressOfNameOrdinals, *ownerSection) + i * sizeof(funcInfo.Ordinal), funcInfo.Ordinal);

            // Get RVA from Address of Functions array
            ReadValueByOffset(in, GetRawOffset(m_header.AddressOfFunctions, *ownerSection) + funcInfo.Ordinal * sizeof(funcInfo.Rva), funcInfo.Rva);
            funcInfo.Ordinal += static_cast<WORD>(m_header.Base);

            // Check is RVA of function in .rdata section
            if (ownerSection->VirtualAddress <= funcInfo.Rva && funcInfo.Rva < ownerSection->VirtualAddress + ownerSection->Misc.VirtualSize)
            {
                // PE file use forwarding to export function
                ReadStringByOffset(in, GetRawOffset(funcInfo.Rva, *ownerSection), funcInfo.ForwardNameOpt);
            }

            setFunctions[i] = true;

            m_functions.push_back(funcInfo);
        }

        if (m_header.NumberOfFunctions != m_header.NumberOfNames)
        {
            for (size_t i = 0; i < setFunctions.size(); ++i)
            {
                if (setFunctions[i] == false)
                {
                    // Function exported by ordinal
                    FuncInfo funcInfo;
                    ReadValueByOffset(in, GetRawOffset(m_header.AddressOfFunctions, *ownerSection) + i * sizeof(DWORD), funcInfo.Rva);
                    funcInfo.Ordinal = static_cast<WORD>(i + m_header.Base);
                    m_functions.push_back(funcInfo);
                }
            }
        }
    }
    IMAGE_EXPORT_DIRECTORY & ExportTable::GetHeader()
    {
        return m_header;
    }
    std::vector<ExportTable::FuncInfo>& ExportTable::GetFunctions()
    {
        return m_functions;
    }

    void ExportTable::Accept(IVisitor & visitor)
    {
        visitor.HandleExportTable(*this);
    }
}
