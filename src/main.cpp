#include <iostream>
#include <vector>
#include <unordered_map>
#include "../include/indexer.h"
#include "../include/searcher.h"

int main() {
   // Get a list of all file names in the "../data" directory
   const std::vector<std::string> fileName = getFileName("../data"); 
   std::unordered_map<std::string, std::unordered_map<std::string, int>> occurrenceByFileMap;

   // Iterate through each file name and process it
   for (const std::string& file : fileName) {
      occurrenceByFileMap[file] = processFile(file); // Add the map for the file
   }

   // Debug: Print all word occurrences for each file
   for (const auto& [file, wordMap] : occurrenceByFileMap) {
      std::cout << "Occurrences in file: " << file << std::endl;
      for (const auto& [word, count] : wordMap) {
         std::cout << "  " << word << ": " << count << std::endl;
      }
      std::cout << std::endl;
   }

   std::string phraseToFind = UserInterface();
   std::unordered_map<std::string, std::vector<int>> fileAndLines = SearchStr(fileName, phraseToFind);
   DisplayLineContent(fileAndLines);
   for (const auto& [file, line] : fileAndLines){
      displayFileContent(file);
   }
   return 0; // Indicate successful execution
}