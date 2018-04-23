#pragma once
#include "IElement.h"

namespace pe_parse
{
    class ExportTable : public IElement
    {
    public:
        struct FuncInfo
        {
            WORD IndexOfName = 0;
            std::string Name;
            std::string ForwardNameOpt;
            WORD Ordinal = 0;
            DWORD Rva;
        };

    public:
        ExportTable(std::istream& in, DWORD vaTableOffset, const std::vector<IMAGE_SECTION_HEADER>& sections);

        IMAGE_EXPORT_DIRECTORY& GetHeader();
        std::vector<FuncInfo>& GetFunctions();

        void Accept(IVisitor& visitor) override;

    private:
        IMAGE_EXPORT_DIRECTORY m_header;
        std::vector<FuncInfo> m_functions;
    };
}


