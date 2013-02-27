//
//  ExecutableDirectoryPath.h
//
//  Created by Jesper on 2/26/13.
//
//

#ifndef ExecutableDirectoryPath_h
#define ExecutableDirectoryPath_h

#include <string>

#if __APPLE__ && __MACH__

std::string addExecutableDirectoryPath(const char* path);

#else

#define addExecutableDirectoryPath(path) std::string(path)

#endif

#endif
