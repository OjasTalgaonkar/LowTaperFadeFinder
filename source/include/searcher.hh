#ifndef SEARCHER_HH
#define SEARCHER_HH

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace fs = std::filesystem;

namespace searcher {

enum class FileType { TEXT, BINARY };

// Function to determine file type
FileType getFileType(const std::string &filename);

// Function to search for specific words in a file
void search(const std::string &inputFile);

bool checker();

}  // namespace searcher

#endif  // SEARCHER_H
