#pragma once
class FileMapper
{
public:
    explicit FileMapper();
    ~FileMapper();

    void Init(const std::wstring& filename);
    PVOID GetFileBase();

private:
    HANDLE m_file;
    HANDLE m_fileMapping;
    PVOID m_fileBase;
};

