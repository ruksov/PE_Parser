#pragma once
#include "IElement.h"

#include <vector>
#include <fstream>

namespace pe_parse
{
    class SectionTable :
        public IElement
    {
    public:
        SectionTable(std::istream& inFile, DWORD sectionOffSet, WORD sectionNumber);

        void Accept(IVisitor& visitor) override;
        const std::vector<IMAGE_SECTION_HEADER>& GetSections();

    private:
        std::vector<IMAGE_SECTION_HEADER> m_sections;
    };
}