#include "stdafx.h"
#include "SectionTable.h"

namespace pe_parse
{
    SectionTable::SectionTable(std::istream & inFile, DWORD sectionOffset, WORD sectionNumber)
        : m_sections(sectionNumber)
    {
        if (m_sections.empty())
        {
            return;
        }

        inFile.seekg(sectionOffset);
        inFile.read(reinterpret_cast<PCHAR>(&m_sections[0]), m_sections.size() * sizeof(IMAGE_SECTION_HEADER));
    }

    void SectionTable::Accept(IVisitor & visitor)
    {
        visitor.HandleSectionTable(*this);
    }

    const std::vector<IMAGE_SECTION_HEADER>& SectionTable::GetSections()
    {
        return m_sections;
    }
}

