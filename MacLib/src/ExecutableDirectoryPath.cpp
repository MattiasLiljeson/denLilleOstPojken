//
//  ExecutableDirectoryPath.cpp
//  Mac OS X
//
//  Created by Jesper on 2/26/13.
//
//

#include "ExecutableDirectoryPath.h"
#include <sstream>
#include <iostream>
#include "CoreFoundation/CoreFoundation.h"

std::string addExecutableDirectoryPath(const char* path)
{
    CFURLRef bundleURL = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    char bundle_path[PATH_MAX];
    CFURLGetFileSystemRepresentation(bundleURL, TRUE, (UInt8 *)bundle_path, PATH_MAX);
    CFRelease(bundleURL);

    std::stringstream stream;
    stream << bundle_path << "/Contents/MacOS/" << path;
    return stream.str();
}
