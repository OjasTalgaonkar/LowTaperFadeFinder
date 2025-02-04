#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main() {
  std::ifstream file("input.txt");
  if (!file.is_open()) {
    std::cerr << "Failed to open input file." << std::endl;
    return 1;
  }

  std::map<std::string, bool> wordMap = {
      {"low", false},
      {"taper", false},
      {"fade", false},
      {"massive", false},
  };
  std::string line;
  std::string word;
  while (std::getline(file, line)) {
    for (char c : line) {
      if (c == ' ') {
        if (word == "low" || word == "Low") {
          wordMap["low"] = true;
          std::cout << "found low \n";
        } else if (word == "taper" || word == "Taper") {
          wordMap["taper"] = true;
          std::cout << "found taper \n";
        } else if (word == "fade" || word == "Fade") {
          wordMap["fade"] = true;
          std::cout << "found fade \n";
        } else if (word == "massive" || word == "Massive") {
          wordMap["massive"] = true;
        }
        word = "";
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
    word = ""; // Reset word
  }

  if (wordMap["low"] && wordMap["taper"] && wordMap["fade"]) {
    std::cout << "All conditions met. You are officially a massive brainrot "
                 "enjoyer, but you know what else is massive?"
              << "\n";
    std::cout << "LLLLLLLLOOOOOOOOWWWWWW  T A P E R  F A D E" << "\n";
  } else if (wordMap["massive"]) {
    std::cout << "Low taper fade wasnt found, but we did find massive"
                 " and you know what else is massive?"
              << "\n";
    std::cout << "LLLLLLLLOOOOOOOOWWWWWW  T A P E R  F A D E" << "\n";
  }
}