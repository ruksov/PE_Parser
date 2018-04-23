#pragma once
#include "IVisitor.h"

namespace viewers
{
    class ConsoleLogger :
        public pe_parse::IVisitor
    {
    public:
        ~ConsoleLogger();

        void HandleDosHeader(pe_parse::DosHeader& dosHeader) override;
        void HandleNtHeader(pe_parse::NtHeader& ntHeader) override;
        void HandleSectionTable(pe_parse::SectionTable& sectionTable) override;
        void HandleImportTable(pe_parse::ImportTable& importTable) override;
        void HandleExportTable(pe_parse::ExportTable& exportTable) override;

    private:
        std::string m_divider = "\n\n___________________________________________________________________\n\n\n";
    };
}