#include "stdafx.h"
#include "ImportTable.h"
#include "Exceptions.h"
#include "Utils.h"

#include <algorithm>
#include <bitset>

#define NUM_BIT sizeof(PVOID) * 8

namespace pe_parse
{
    ImportTable::ImportTable(std::istream & in, DWORD vaTableOffset, const std::vector<IMAGE_SECTION_HEADER>& sections)
    {
        // Find section, which contain import table
        if (vaTableOffset == 0)
        {
            return;
        }

        const auto& ownerSection = std::find_if(sections.begin(), sections.end(), 
            [vaTableOffset](const IMAGE_SECTION_HEADER& section)
        {
            return section.VirtualAddress <= vaTableOffset && section.VirtualAddress + section.Misc.VirtualSize > vaTableOffset;
        });

        THROW_IF(ownerSection == sections.end(), "Can't find owner section of import table");

        // Calculate offset of import table in raw data
        DWORD rawTableOffset = GetRawOffset(vaTableOffset, *ownerSection);

        // Fill first import descriptor structure
        IMAGE_IMPORT_DESCRIPTOR importTableIt;
        size_t descriptorsCount = 0;
        ReadValueByOffset(in, rawTableOffset, importTableIt);
        
        // Iterate all import tables
        while (importTableIt.Characteristics != 0)
        {
            ModuleInfo moduleInfo;
            ReadStringByOffset(in, GetRawOffset(importTableIt.Name, *ownerSection), moduleInfo.Name);          

            DWORD vaThunkOffset = importTableIt.OriginalFirstThunk != 0 ? importTableIt.OriginalFirstThunk : importTableIt.FirstThunk;
            auto rawThunkOffset = GetRawOffset(vaThunkOffset, *ownerSection);

            IMAGE_THUNK_DATA thunkIt = { 0 };
            size_t thunkCount = 0;
            ReadValueByOffset(in, rawThunkOffset, thunkIt);

            while (thunkIt.u1.AddressOfData != 0 && thunkIt.u1.ForwarderString != 0 && thunkIt.u1.Function != 0 && thunkIt.u1.Ordinal != 0)
            {
                //
                // Check how function is imported
                // If highest bit is set, then function imported by ordinal
                // Otherwise it imported by function name
                //
                auto bitCheck = *reinterpret_cast<ULONGLONG*>(&thunkIt);
                std::bitset<NUM_BIT> bits(bitCheck);

                if (bits.test(NUM_BIT - 1))
                {
                    moduleInfo.FunctionOrdinals.push_back(LOWORD(bitCheck));
                }
                else
                {
                    FuncInfo funcInfo;
                    auto rawFuncInfo = GetRawOffset(thunkIt.u1.AddressOfData, *ownerSection);

                    // Read Hint and Name from IMAGE_IMPORT_BY_NAME
                    ReadValueByOffset(in, rawFuncInfo, funcInfo.Hint);
                    ReadStringByOffset(in, in.tellg(), funcInfo.Name);

                    moduleInfo.Functions.push_back(funcInfo);
                }

                ++thunkCount;
                ReadValueByOffset(in, rawThunkOffset + thunkCount * sizeof(thunkIt), thunkIt);
            }

            moduleInfo.Descriptor = importTableIt;
            m_import.push_back(moduleInfo);
            ++descriptorsCount;
            ReadValueByOffset(in, rawTableOffset + descriptorsCount * sizeof(importTableIt), importTableIt);
        }
    }

    void ImportTable::Accept(IVisitor & visitor)
    {
        visitor.HandleImportTable(*this);
    }

    const std::vector<ImportTable::ModuleInfo>& ImportTable::GetImportTable()
    {
        return m_import;
    }
}
