#include "stdafx.h"
#include "FileMapper.h"
#include "Exceptions.h"


FileMapper::FileMapper()
    : m_file(NULL)
    , m_fileMapping(NULL)
    , m_fileBase(nullptr)
{

}

FileMapper::~FileMapper()
{
    UnmapViewOfFile(m_fileBase);
    CloseHandle(m_fileMapping);
    CloseHandle(m_file);
}

void FileMapper::Init(const std::wstring & filename)
{
    m_file = CreateFile(filename.data(), GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    THROW_IF(!m_file, "Couldn't open file with CreateFile()");

    m_fileMapping = CreateFileMapping(m_file, NULL, PAGE_READONLY, 0, 0, NULL);
    THROW_IF(!m_fileMapping, "Couldn't open file mapping with CreteFileMapping()");

    m_fileBase = MapViewOfFile(m_fileMapping, FILE_MAP_READ, 0, 0, 0);
    THROW_IF(!m_fileBase, "Couldn't map view of file with MapViewOfFile()");
}

PVOID FileMapper::GetFileBase()
{
    return m_fileBase;
}
