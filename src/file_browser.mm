#import "file_browser.h"
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include <vector>
#include <string>

bool isAudioFile(NSString *filePath) {
    NSString *extension = [filePath pathExtension].lowercaseString;
    return [extension isEqualToString:@"mp3"] || 
           [extension isEqualToString:@"wav"] || 
           [extension isEqualToString:@"flac"];
}

std::vector<std::string> openFolderDialog() {
    std::vector<std::string> audioFiles;

    @autoreleasepool {
        // Create an NSOpenPanel instance
        NSOpenPanel *panel = [NSOpenPanel openPanel];
        
        // Configure the panel for directory selection
        [panel setCanChooseFiles:NO];
        [panel setCanChooseDirectories:YES];
        [panel setAllowsMultipleSelection:NO];

        // Show the panel and check if the user selected a folder
        if ([panel runModal] == NSModalResponseOK) {
            // Get the selected folder's URL
            NSURL *folderURL = [panel URL];
            NSString *folderPath = [folderURL path];

            // Use NSFileManager to retrieve file contents
            NSFileManager *fileManager = [NSFileManager defaultManager];
            NSError *error = nil;
            NSArray *contents = [fileManager contentsOfDirectoryAtPath:folderPath error:&error];

            if (error) {
                NSLog(@"Error reading directory contents: %@", error.localizedDescription);
                return audioFiles; // Return empty if there's an error
            }

            // Sort the contents alphabetically
            NSArray *sortedContents = [contents sortedArrayUsingSelector:@selector(localizedStandardCompare:)];

            // Iterate over sorted contents and filter audio files
            for (NSString *fileName in sortedContents) {
                NSString *filePath = [folderPath stringByAppendingPathComponent:fileName];

                // Check if the file has a valid audio extension
                if (isAudioFile(filePath)) {
                    audioFiles.push_back(std::string([filePath UTF8String]));
                }
            }
        }
    }

    return audioFiles;
}