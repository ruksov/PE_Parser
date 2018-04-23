#include "stdafx.h"
#include "NtHeader.h"
#include "Utils.h"
#include "Exceptions.h"

namespace pe_parse
{
    NtHeader::NtHeader(std::istream & in, LONG ntOffset)
    {
        // Read Nt Header
        ReadValueByOffset(in, ntOffset, m_ntHeader);
        THROW_IF(m_ntHeader.Signature != IMAGE_NT_SIGNATURE, "Failed to match NT signature.");

        // Check is PE must running on x86 machine
        THROW_IF(m_ntHeader.FileHeader.Machine == IMAGE_FILE_MACHINE_I386, "Parser can parse only x64 PE files.");

        // Calculate section table offset
        m_sectionTableOffset = ntOffset + offsetof(IMAGE_NT_HEADERS, OptionalHeader) + m_ntHeader.FileHeader.SizeOfOptionalHeader;
    }

    void NtHeader::Accept(IVisitor & visitor)
    {
        visitor.HandleNtHeader(*this);
    }

    const IMAGE_NT_HEADERS & NtHeader::GetNtHeader()
    {
        return m_ntHeader;
    }

    ULONG NtHeader::GetSectionTableOffset()
    {
        return m_sectionTableOffset;
    }

    USHORT NtHeader::GetNumberOfSections()
    {
        return m_ntHeader.FileHeader.NumberOfSections;
    }

    IMAGE_DATA_DIRECTORY NtHeader::GetDataDirectory(size_t index)
    {
        THROW_IF(index >= IMAGE_NUMBEROF_DIRECTORY_ENTRIES, "Wrong index for Data Directory, GetDataDirectory() index=" << index);
        return m_ntHeader.OptionalHeader.DataDirectory[index];
    }
}