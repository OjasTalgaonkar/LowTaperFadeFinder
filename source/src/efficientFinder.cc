#include <cmath>
#include <filesystem>
#include <iostream>

#include "../include/searcher.hh"
#include "../include/threadPool.hh"

namespace fs = std::filesystem;

int processFile(const fs::path &filePath, ThreadPool &pool) {
    try {
        if (!fs::exists(filePath))
            return 0;  // Stop early if found
        std::string        pathString = filePath.string();
        searcher::FileType type       = searcher::getFileType(pathString);

        if (type == searcher::FileType::TEXT) {
            searcher::search(pathString);
            if (searcher::checker()) {
                std::cout << "merry rizzmas\n";
                pool.stopPool();  // Stop the thread pool immediately
                return 5;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error processing " << filePath.string() << ": " << e.what() << std::endl;
    }
    return 0;
}

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

    ThreadPool pool(std::pow(std::thread::hardware_concurrency(), 2));

    fs::recursive_directory_iterator it(root, fs::directory_options::skip_permission_denied), end;
    while (it != end) {
        try {
            fs::path currentPath = it->path();

            // Skip symlinks and system directories
            if (fs::is_symlink(currentPath) ||
                currentPath.string().find("Documents and Settings") != std::string::npos) {
                it.disable_recursion_pending();
                ++it;
                continue;
            }

            if (searcher::checker())
                break;  // Stop adding tasks if condition met

            pool.enqueue([currentPath, &pool] { processFile(currentPath, pool); });

        } catch (const std::exception &e) {
            std::cerr << "Skipping " << it->path().string() << ": " << e.what() << std::endl;
        }
        ++it;
    }

    return 0;
}
