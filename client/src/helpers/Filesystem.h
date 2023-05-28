#pragma once

#include "cpp-sdk/ICore.h"

namespace js
{
    static bool DoesFileExist(alt::IPackage* package, const std::string& path)
    {
        if(!package) return false;
        return package->FileExists(path);
    }

    static std::vector<uint8_t> ReadFile(alt::IPackage* package, const std::string& path)
    {
        if(!DoesFileExist(package, path)) return {};
        alt::IPackage::File* file = package->OpenFile(path);
        if(file == nullptr) return {};
        size_t fileSize = package->GetFileSize(file);
        std::vector<uint8_t> content(fileSize);
        package->ReadFile(file, content.data(), fileSize);
        package->CloseFile(file);
        return content;
    }
}  // namespace js
