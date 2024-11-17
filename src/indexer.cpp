#include <iostream>          // For input/output operations (e.g., std::cout)
#include <fstream>           // For file handling (e.g., reading files with std::ifstream)
#include <filesystem>        // For working with the file system (e.g., iterating over directories)
#include <vector>            // For using std::vector to store file paths
#include <unordered_map>     // For using std::unordered_map to store word occurrences
#include <cctype>            // For std::isalnum and std::tolower

namespace fs = std::filesystem;  // Shorten the namespace for easier usage

// Function to clean a word: removes non-alphanumeric characters and converts to lowercase
const std::string cleanWord(const std::string& wordToClean) {
    std::string newCleanWord;
    for (char c : wordToClean) {
        if (std::isalnum(c)) {                // Check if the character is alphanumeric
            newCleanWord += std::tolower(c);  // Convert to lowercase and add it
        }
    }
    return newCleanWord;  // Return the cleaned word
}

// Function to get a list of file names in a specified directory
const std::vector<std::string> getFileName(const std::string& directoryPath) {
    std::vector<std::string> listFile;  // Vector to store file paths

    try {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            listFile.push_back(entry.path());  // Add each file path to the vector
        }
    } catch (const fs::filesystem_error& e) {  // Catch exceptions related to filesystem errors
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    if (listFile.empty()) {  // Warn if no files were found
        std::cerr << "Error: No files found in directory " << directoryPath << std::endl;
    }

    return listFile;  // Return the list of file paths
}

// Function to process a single file
std::unordered_map<std::string, int> processFile(const std::string& filePath) {
    std::unordered_map<std::string, int> occurrenceMap;  // Map to store word counts
    std::string word;                                   // Temporary variable to hold each word

    std::ifstream myReadFile(filePath);  // Open the file
    if (!myReadFile.is_open()) {  // Check if the file was successfully opened
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return std::unordered_map<std::string, int>();
    }

    while (myReadFile >> word) {  // Read words from the file
        std::string clean = cleanWord(word);  // Clean the word
        if (!clean.empty()) {                 // Ignore empty words after cleaning
            occurrenceMap[clean]++;           // Increment the count for the cleaned word
        }
    }

   //Print word occurrences for debugging/output purposes
   std::cout << "Occurrences in file: " << filePath << std::endl;
   for (const auto& [key, value] : occurrenceMap) {  // Structured binding to iterate through the map
      std::cout << key << ": " << value << std::endl;
   }
    return occurrenceMap;
}