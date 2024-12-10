#ifndef FILE_BROWSER_H
#define FILE_BROWSER_H

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

#include <vector>
#include <string>

// Use a forward declaration for non-Objective-C contexts
#ifndef __OBJC__
class NSString;
#endif

bool isAudioFile(NSString* filePath);
std::vector<std::string> openFolderDialog();

#endif // FILE_BROWSER_H