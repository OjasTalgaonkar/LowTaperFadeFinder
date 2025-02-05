#include <filesystem>
#include <iostream>

#include "../include/searcher.hh"

namespace fs = std::filesystem;

int main() {
    std::string root;

#ifdef _WIN32
    root = "C:\\";
#elif __APPLE__ || __linux__ || __unix__
    root = "/";
#else
    std::cerr << "Unsupported OS" << std::endl;
    return 1;
#endif

    try {
        for (const auto &entry : fs::recursive_directory_iterator(
                 root, fs::directory_options::skip_permission_denied)) {
            std::string        filePath = entry.path().string();
            searcher::FileType type     = searcher::getFileType(filePath);
            searcher::search(filePath);
        }
    } catch (const std::exception &e) { std::cerr << "Error: " << e.what() << std::endl; }
}