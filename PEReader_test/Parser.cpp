#include "stdafx.h"
#include "Parser.h"
#include "ImportTable.h"

namespace pe_parse
{
    Parser::Parser(std::istream & in)
        : m_dosHeader(in)
        , m_ntHeader(in, m_dosHeader.GetNtOffset())
        , m_sectionTable(in, m_ntHeader.GetSectionTableOffset(), m_ntHeader.GetNumberOfSections())
        , m_importTable(in, m_ntHeader.GetDataDirectory(IMAGE_DIRECTORY_ENTRY_IMPORT).VirtualAddress, m_sectionTable.GetSections())
        , m_exportTable(in, m_ntHeader.GetDataDirectory(IMAGE_DIRECTORY_ENTRY_EXPORT).VirtualAddress, m_sectionTable.GetSections())
    {
        m_elements.push_back(m_dosHeader);
        m_elements.push_back(m_ntHeader);
        m_elements.push_back(m_sectionTable);
        m_elements.push_back(m_importTable);
        m_elements.push_back(m_exportTable);
    }

    void Parser::Show(IVisitor & visitor)
    {
        for (auto& el : m_elements)
        {
            el.get().Accept(visitor);
        }
    }
}
