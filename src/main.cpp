#include <iostream>
#include <vector>
#include <unordered_map>
#include "../include/indexer.h"
#include "../include/searcher.h"

int main() {
   // Retrieve the list of file names in the "../data" directory
   const std::vector<std::string> fileName = getFileName("../data"); 
   std::unordered_map<std::string, std::unordered_map<std::string, int>> occurrenceByFileMap;

   // Process each file to create a map of word occurrences
   for (const std::string& file : fileName) {
      occurrenceByFileMap[file] = processFile(file); // Count word occurrences for each file
   }
   
   // Welcome message for the user
   std::cout << "WELCOME to my own Search Engine!!!\n";
   
   // Main program loop to allow multiple searches
   do {
      std::string phraseToFind = UserInterface(); // Prompt user for a search phrase
      std::unordered_map<std::string, std::vector<int>> fileAndLines = SearchStr(fileName, phraseToFind); // Search files for the phrase
      DisplayLineContent(fileAndLines); // Display line content if the user requests it
      
      // Optionally display full file content based on user input
      for (const auto& [file, line] : fileAndLines) {
         displayFileContent(file);
      }
   } while (AskForAction()); // Continue until the user decides to quit
   
   return 0; // Program exits successfully
}