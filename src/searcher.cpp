#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "../include/indexer.h"

// Function to search for a word in the database
std::vector<std::string> SearchWord(const std::unordered_map<std::string, std::unordered_map<std::string, int>>& dataBase, const std::string& word) {
   bool wordFound = false;  // Flag to track if the word was found
   std::vector<std::string> fileFoundPath;

   std::cout << "Searching for the word: \"" << word << "\"...\n";

   for (const auto& [fileName, occurrenceMap] : dataBase) {
      auto it = occurrenceMap.find(word);  // Use map's find function for faster lookup
      if (it != occurrenceMap.end()) {    // If the word is found in the file
         wordFound = true;
         std::cout << "File: " << fileName << " -> Occurrences: " << it->second << '\n';
         fileFoundPath.push_back(fileName);
      }
   }

   if (!wordFound) {  // If the word was not found in any file
      std::cout << "The word \"" << word << "\" was not found in any file.\n";
   }
   return fileFoundPath;
}

// Function to interact with the user
const std::string UserInterface() {
   int attempts = 0;  // Counter to track the number of invalid attempts

   // Loop to allow the user to input a valid word, with a maximum of 3 attempts
   while (attempts <= 3) {
      std::string word;
      std::cout << "What word would you like to find?: ";  // Prompt the user to enter a word
      std::cin >> word;  // Read the user's input

      word = cleanWord(word);  // Clean the word to remove unwanted characters

      if (!word.empty()) {
         return word;  // If the word is valid, return it
      }

      // If the input is invalid, notify the user and increment the attempt counter
      std::cerr << "Invalid input. Please enter a valid word.\n";
      attempts++;
   }

   // If the user exceeds the maximum number of invalid attempts, exit the program
   std::cerr << "Too many invalid attempts. Exiting...\n";
   exit(EXIT_FAILURE);  // Terminate the program with an error status
}

// Function to display the content of files
void displayFileContent(const std::vector<std::string>& files) {
   std::string fileDisplayResponse;
   std::string line;

   std::cout << "Would you like to see the content of the files? (Yes/No): ";
   std::cin >> fileDisplayResponse;

   // Convert response to lowercase for easier comparison
   for (auto& c : fileDisplayResponse) c = std::tolower(c);

   if (fileDisplayResponse == "y" || fileDisplayResponse == "yes") {
      for (const std::string& file : files) {
         std::cout << "\nContent in file: " << file << '\n';

         std::ifstream fileName(file);
         if (!fileName.is_open()) {
               std::cerr << "Error: Could not open file " << file << '\n';
               continue;  // Skip to the next file
         }

         while (std::getline(fileName, line)) {
               std::cout << line << '\n';
         }
      }
   } else if (fileDisplayResponse != "n" && fileDisplayResponse != "no") {
      std::cerr << "Invalid input. Please type Yes or No.\n";
      displayFileContent(files);  // Ask again for a valid response
   }
}

// Function to search for a string in multiple files
std::unordered_map<std::string, std::vector<int>> SearchStr(const std::vector<std::string>& files, const std::string& str) {
   // Convert the search string to lowercase
   std::string searchStr = str;
   std::transform(searchStr.begin(), searchStr.end(), searchStr.begin(), ::tolower);

   // Map to store files and their corresponding line numbers where the string is found
   std::unordered_map<std::string, std::vector<int>> fileAndLines;

   std::cout << "Searching for the phrase: \"" << searchStr << "\"...\n";

   // Iterate through each file
   for (const std::string& fileName : files) {
      std::ifstream file(fileName); // Open the file
      if (!file.is_open()) { // Check if the file is successfully opened
         std::cerr << "Error: Could not open file " << fileName << '\n';
         continue; // Skip to the next file if there's an error
      }

      std::string line;
      int lineNumber = 1; // Track the current line number

      // Read each line from the file
      while (std::getline(file, line)) {
         // Convert the line to lowercase for case-insensitive search
         std::string lowerLine = line;
         std::transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(), ::tolower);

         // Check if the search string exists in the current line
         if (lowerLine.find(searchStr) != std::string::npos) {
               fileAndLines[fileName].push_back(lineNumber); // Store the line number in the map
         }

         lineNumber++; // Move to the next line
      }

      file.close(); // Close the file after reading
   }

   // Display the search results
   if (!fileAndLines.empty()) {
      for (const auto& [fileName, lineNumbers] : fileAndLines) {
         std::cout << "String \"" << searchStr << "\" found in file: " << fileName << '\n';
         std::cout << "At line number(s): ";
         for (size_t i = 0; i < lineNumbers.size(); ++i) {
               std::cout << lineNumbers[i];
               if (i != lineNumbers.size() - 1) {
                  std::cout << ", "; // Add a comma between line numbers, except for the last one
               }
         }
         std::cout << '\n';
      }
   } else {
      std::cout << "The string \"" << searchStr << "\" was not found in any file.\n";
   }

}

// void DisplayLineContent(std::unordered_map<std::string, std::vector<int>> fileAndLines){
//    std::string response;

//    for (const auto& [fileName, lineNumbers] : fileAndLines) {
//       std::cout << "Would you like to see the content of the line " << lineNumbers << " in the file " << fileName << " ?";
//       std::cout << "(Yes or No)? ";
//       std::cin >> response;
//       for (auto& c : response) c = std::tolower(c);

//       if (response == "y" || response == "yes"){

//       }
      
//    }
// }