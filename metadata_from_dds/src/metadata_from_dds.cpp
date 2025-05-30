#include <iostream>
#include <codecvt>
#include <locale>
#include <string>
#include <DirectXTex.h>

void PrintDDSMetadata(const std::string& filename) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wideName = converter.from_bytes(filename);

    DirectX::TexMetadata metadata;
    HRESULT hr = DirectX::GetMetadataFromDDSFile(wideName.c_str(), DirectX::DDS_FLAGS_NONE, metadata);

    if (FAILED(hr)) {
        std::cerr << "Error reading metadata from DDS file: " << filename << std::endl;
        return;
    }

    std::cout << "file: " << filename << std::endl;
    std::cout << "width: " << metadata.width << std::endl;
    std::cout << "height: " << metadata.height << std::endl;
    std::cout << "format: " << metadata.format << std::endl;
    std::cout << "mipLevels: " << metadata.mipLevels << std::endl;
    std::cout << "arraySize: " << metadata.arraySize << std::endl;
    std::cout << "texture type: " << (metadata.dimension == DirectX::TEX_DIMENSION_TEXTURE1D ? "1D" :
                                      metadata.dimension == DirectX::TEX_DIMENSION_TEXTURE2D ? "2D" :
                                      metadata.dimension == DirectX::TEX_DIMENSION_TEXTURE3D ? "3D" : "Unknown") << std::endl;
}

int main() {
    std::string filename;

    std::cout << "Enter DDS filename: ";
    std::getline(std::cin, filename);

    PrintDDSMetadata(filename);

    return 0;
}
