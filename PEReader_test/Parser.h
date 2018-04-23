#pragma once
#include "DosHeader.h"
#include "NtHeader.h"
#include "SectionTable.h"
#include "ImportTable.h"
#include "ExportTable.h"

namespace pe_parse
{
    class Parser
    {
    public:
        explicit Parser(std::istream& in);
        void Show(IVisitor& visitor);

    private:
        DosHeader m_dosHeader;
        NtHeader m_ntHeader;
        SectionTable m_sectionTable;
        ImportTable m_importTable;
        ExportTable m_exportTable;
        std::vector<std::reference_wrapper<IElement>> m_elements;
    };
}


