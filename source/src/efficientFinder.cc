#include <atomic>
#include <filesystem>
#include <iostream>

#include "../include/searcher.hh"
#include "../include/threadPool.hh"

namespace fs                  = std::filesystem;
std::atomic<bool> foundTarget = false;  // Global flag to stop work

int processFile(const fs::path &filePath, ThreadPool &pool) {
    try {
        if (!fs::exists(filePath) || foundTarget)
            return 0;

        // std::cout << "Processing: " << filePath << std::endl;

        std::string        pathString = filePath.string();
        searcher::FileType type       = searcher::getFileType(pathString);

        if (type == searcher::FileType::TEXT) {
            searcher::search(pathString);
            if (searcher::checker(pathString)) {
                std::cout << "merry rizzmas\n";
                foundTarget = true;
                pool.stopPool();
                return 5;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error processing " << filePath.string() << ": " << e.what() << "\n";
    }

    // std::cout << "Finished: " << filePath << std::endl;
    return 0;
}

int main() {
    std::string root;

#ifdef _WIN32
    root = "C:\\";
#elif __APPLE__ || __linux__ || __unix__
    root = "/";
#else
    std::cerr << "Unsupported OS" << "\n";
    return 1;
#endif

    ThreadPool pool(std::thread::hardware_concurrency());

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

            if (foundTarget)
                break;  // Stop adding tasks if condition met

            pool.enqueue([currentPath, &pool] { processFile(currentPath, pool); });

        } catch (const std::exception &e) {
            std::cerr << "Skipping " << it->path().string() << ": " << e.what() << "\n";
        }
        ++it;
    }

    while (pool.activeTasks > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
