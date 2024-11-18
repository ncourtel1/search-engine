#include <iostream>          // For input/output operations
#include <fstream>           // For file handling
#include <filesystem>        // To manage directories and files
#include <vector>            // For dynamic arrays
#include <unordered_map>     // For efficient word-count storage
#include <cctype>            // For character manipulation (e.g., std::tolower)

namespace fs = std::filesystem;  // Short alias for the filesystem namespace

// Function to clean a phrase by removing unwanted characters and converting to lowercase
const std::string cleanPhrase(const std::string& phraseToClean) {
    std::string newCleanPhrase;

    for (char c : phraseToClean) {
        // Keep only alphanumeric characters and spaces
        if (std::isalnum(c) || c == ' ') { 
            newCleanPhrase += std::tolower(c);  // Convert to lowercase and append
        }
    }

    return newCleanPhrase;  // Return the cleaned phrase
}

// Function to retrieve file names from a directory
const std::vector<std::string> getFileName(const std::string& directoryPath) {
   std::vector<std::string> listFile;  // Vector to store file paths

   try {
      // Iterate through the directory and store file paths
      for (const auto& entry : fs::directory_iterator(directoryPath)) {
         listFile.push_back(entry.path());  // Append each file path to the vector
      }
   } catch (const fs::filesystem_error& e) {  // Handle errors related to the filesystem
      std::cerr << "Filesystem error: " << e.what() << std::endl;
   }

   if (listFile.empty()) {  // Notify if no files are found
      std::cerr << "Error: No files found in directory " << directoryPath << std::endl;
   }

   return listFile;  // Return the list of file names
}

// Function to process a file and count the occurrence of each word
std::unordered_map<std::string, int> processFile(const std::string& filePath) {
   std::unordered_map<std::string, int> occurrenceMap;  // Map to store word counts
   std::string word;  // Temporary variable for reading words

   std::ifstream myReadFile(filePath);  // Open the file for reading
   if (!myReadFile.is_open()) {  // Handle errors if the file cannot be opened
      std::cerr << "Error: Could not open file " << filePath << std::endl;
      return std::unordered_map<std::string, int>();
   }

   // Read each word from the file
   while (myReadFile >> word) {  
      std::string clean = cleanPhrase(word);  // Clean the word before processing
      if (!clean.empty()) {  // Ignore empty strings
         occurrenceMap[clean]++;  // Increment the word count
      }
   }
   return occurrenceMap;  // Return the map of word counts
}