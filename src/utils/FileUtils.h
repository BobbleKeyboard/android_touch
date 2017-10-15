//
// Created by kunaldawn on 15/10/17.
//

#ifndef PROJECT_FILEUTILS_H
#define PROJECT_FILEUTILS_H

#include <string>
#include <vector>
#include <dirent.h>

namespace android_touch {
    class FileUtils {
    public:
        /**
         * Get list of all directories in given path
         *
         * @param path Base path
         * @returns Vector of directory names in given path
         */
        static std::vector<std::string> getDirs(std::string path) {
            std::vector<std::string> list;
            DIR *dir = opendir(path.c_str());
            struct dirent *entry = readdir(dir);

            while (entry != NULL) {
                if (entry->d_type == DT_DIR) {
                    std::string dirName = std::string(entry->d_name);
                    if (dirName.find(".") == std::string::npos) {
                        list.push_back(dirName);
                    }
                }
                entry = readdir(dir);
            }
            closedir(dir);

            return list;
        }

        /**
         * Get list of all files in given path
         *
         * @param path Base path
         * @param isApplyFilter Boolean value to indicate if filter needs to be applied
         * @param Filter that needs to be applied if enabled
         * @returns Vector of file names in given path
         */
        static std::vector<std::string> getFiles(std::string path, bool isApplyFilter, std::string filter) {
            std::vector<std::string> list;
            DIR *dir = opendir(path.c_str());
            struct dirent *entry = readdir(dir);

            while (entry != NULL) {
                if (entry->d_type != DT_DIR) {
                    std::string fileName = std::string(entry->d_name);
                    if (isApplyFilter) {
                        if (fileName.find(filter) != std::string::npos) {
                            list.push_back(fileName);
                        }
                    } else {
                        list.push_back(fileName);
                    }
                }
                entry = readdir(dir);
            }
            closedir(dir);

            return list;
        }
    };
}

#endif //PROJECT_FILEUTILS_H
