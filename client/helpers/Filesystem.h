#pragma once

#include "cpp-sdk/ICore.h"

namespace js
{
    bool DoesFileExist(alt::IResource* resource, const std::string& path)
    {
        alt::IPackage* package = resource->GetPackage();
        if(!package) return false;
        return package->FileExists(path);
    }

    std::optional<std::string> ReadFile(alt::IResource* resource, const std::string& path)
    {
        alt::IPackage* package = resource->GetPackage();
        if(!DoesFileExist(resource, path)) return std::nullopt;
        alt::IPackage::File* file = package->OpenFile(path);
        if(file == nullptr) return std::nullopt;
        size_t fileSize = package->GetFileSize(file);
        std::string content(fileSize, '\0');
        package->ReadFile(file, content.data(), fileSize);
        package->CloseFile(file);
        return content;
    }
}  // namespace js
