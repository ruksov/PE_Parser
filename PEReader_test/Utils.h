#pragma once

template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
T GetRawOffset(T vaOffset, const IMAGE_SECTION_HEADER& section)
{
    return section.PointerToRawData + (vaOffset - section.VirtualAddress);
}

void ReadStringByOffset(std::istream& in, size_t offset, std::string& value);

template<typename T>
void ReadValueByOffset(std::istream& in, size_t offset, T& value)
{
    in.seekg(offset);
    in.read(reinterpret_cast<PCHAR>(&value), sizeof(value));
}