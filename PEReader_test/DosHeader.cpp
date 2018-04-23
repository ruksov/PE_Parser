#include "stdafx.h"
#include "DosHeader.h"
#include "Exceptions.h"

namespace pe_parse
{
    DosHeader::DosHeader(std::istream & inFile)
    {
        inFile.seekg(0);
        inFile.read(reinterpret_cast<PCHAR>(&m_dosHeader), sizeof(IMAGE_DOS_HEADER));
        THROW_IF(m_dosHeader.e_magic != IMAGE_DOS_SIGNATURE, "Failed to match DOS signature.");
    }

    void DosHeader::Accept(IVisitor & visitor)
    {
        visitor.HandleDosHeader(*this);
    }

    const IMAGE_DOS_HEADER& DosHeader::GetDosHeader()
    {
        return m_dosHeader;
    }

    LONG DosHeader::GetNtOffset()
    {
        return m_dosHeader.e_lfanew;
    }
}
