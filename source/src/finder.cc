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
        fs::recursive_directory_iterator it(root, fs::directory_options::skip_permission_denied),
            end;
        while (it != end) {
            try {
                fs::path currentPath = it->path();

                // Skip junction points and system directories
                if (fs::is_symlink(currentPath) ||
                    currentPath.string().find("Documents and Settings") != std::string::npos) {
                    it.disable_recursion_pending();
                    ++it;
                    continue;
                }

                if (!fs::exists(currentPath)) {
                    ++it;
                    continue;
                }

                std::string        filePath = currentPath.string();
                searcher::FileType type     = searcher::getFileType(filePath);
                if (type == searcher::FileType::TEXT) {
                    searcher::search(filePath);
                    if (searcher::checker()) {
                        std::cout << "merry rizzmas";
                        break;
                    }
                }
            } catch (const std::exception &e) {
                std::cerr << "Skipping " << it->path().string() << ": " << e.what() << std::endl;
            }
            ++it;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error iterating filesystem: " << e.what() << std::endl;
    }
}
