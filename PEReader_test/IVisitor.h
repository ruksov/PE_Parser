#pragma once

namespace pe_parse
{
    class DosHeader;
    class NtHeader;
    class SectionTable;
    class ImportTable;
    class ExportTable;

    struct IVisitor
    {
        virtual ~IVisitor() = default;

        virtual void HandleDosHeader(DosHeader&) = 0;
        virtual void HandleNtHeader(NtHeader&) = 0;
        virtual void HandleSectionTable(SectionTable&) = 0;
        virtual void HandleImportTable(ImportTable&) = 0;
        virtual void HandleExportTable(ExportTable&) = 0;
    };
}