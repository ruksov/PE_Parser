#pragma once
#include "IElement.h"

namespace pe_parse
{
    class DosHeader
        : public IElement
    {
    public:
        explicit DosHeader(std::istream& inFile);

        void Accept(IVisitor& visitor) override;
        const IMAGE_DOS_HEADER& GetDosHeader();
        LONG GetNtOffset();

    private:
        IMAGE_DOS_HEADER m_dosHeader = { 0 };
    };
}


