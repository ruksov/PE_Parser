#pragma once
#include "IElement.h"

namespace pe_parse
{
    class NtHeader : public IElement
    {
    public:
        NtHeader(std::istream& in, LONG ntOffset);

        void Accept(IVisitor& visitor) override;

        const IMAGE_NT_HEADERS& GetNtHeader();
        ULONG GetSectionTableOffset();
        USHORT GetNumberOfSections();
        IMAGE_DATA_DIRECTORY GetDataDirectory(size_t index);

    private:
        IMAGE_NT_HEADERS m_ntHeader;
        ULONG m_sectionTableOffset;
    };
}


