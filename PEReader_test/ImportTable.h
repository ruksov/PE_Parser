#pragma once
#include "IElement.h"

namespace pe_parse
{
    class ImportTable : public IElement
    {
    public:
        struct FuncInfo
        {
            WORD Hint;
            std::string Name;
        };

        struct ModuleInfo
        {
            IMAGE_IMPORT_DESCRIPTOR Descriptor = { 0 };
            std::string Name;
            std::vector<FuncInfo> Functions;
            std::vector<WORD> FunctionOrdinals;
        };

    public:
        ImportTable(std::istream& in, DWORD vaTableOffset, const std::vector<IMAGE_SECTION_HEADER>& sections);
        void Accept(IVisitor& visitor) override;

        const std::vector<ModuleInfo>& GetImportTable();

    private:
        std::vector<ModuleInfo> m_import;
    };
}