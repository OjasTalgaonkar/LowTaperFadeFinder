#include "../include/searcher.hh"

namespace searcher {

// Define a static word map
static std::map<std::string, bool> wordMap = {
    {"low", false},
    {"taper", false},
    {"fade", false},
    {"massive", false},
};

// Determine file type based on the extension
FileType getFileType(const std::string &filename) {
    std::string ext = fs::path(filename).extension().string();

    if (ext == ".exe" || ext == ".dll" || ext == ".bin" || ext == ".zip" || ext == ".tar" ||
        ext == ".gz" || ext == ".rar" || ext == ".7z" || ext == ".png" || ext == ".jpg" ||
        ext == ".jpeg" || ext == ".gif" || ext == ".mp3" || ext == ".mp4" || ext == ".pdf" ||
        ext == ".doc" || ext == ".xls") {
        return FileType::BINARY;
    }

    return FileType::TEXT;
}

// Function to search for words in a file
void search(const std::string &inputFile) {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        // std::cerr << "Failed to open input file: " << inputFile << std::endl;
        // return;
    }

    std::string line, word;
    while (std::getline(file, line)) {
        for (char c : line) {
            if (c == ' ') {
                if (word == "low" || word == "Low") {
                    wordMap["low"] = true;
                    std::cout << "Found low in " << inputFile << "\n";
                } else if (word == "taper" || word == "Taper") {
                    wordMap["taper"] = true;
                    std::cout << "Found taper in " << inputFile << "\n";
                } else if (word == "fade" || word == "Fade") {
                    wordMap["fade"] = true;
                    std::cout << "Found fade in " << inputFile << "\n";
                } else if (word == "massive" || word == "Massive") {
                    wordMap["massive"] = true;
                }
                word.clear();
            } else {
                word += c;
            }
        }
    }

    if (!word.empty()) {
        if (word == "low" || word == "Low") {
            wordMap["low"] = true;
        } else if (word == "taper" || word == "Taper") {
            wordMap["taper"] = true;
        } else if (word == "fade" || word == "Fade") {
            wordMap["fade"] = true;
        } else if (word == "massive" || word == "Massive") {
            wordMap["massive"] = true;
        }
    }

    if (wordMap["massive"]) {
        wordMap["massive"] = false;
        std::cout << "Low taper fade wasn't found, but we did find massive, "
                     "and you know what else is massive?\n";
        std::cout << "LLLLLLLLOOOOOOOOWWWWWW  T A P E R  F A D E\n";
    }
}

bool checker() {
    if (wordMap["low"] && wordMap["taper"] && wordMap["fade"]) {
        std::cout << "All conditions met. You are officially a massive brainrot enjoyer, "
                     "but you know what else is massive?\n";
        std::cout << "LLLLLLLLOOOOOOOOWWWWWW  T A P E R  F A D E\n";
        wordMap["low"] = wordMap["taper"] = wordMap["fade"] = false;
        std::exit(0);

        return true;
    }
    return false;
}

}  // namespace searcher
