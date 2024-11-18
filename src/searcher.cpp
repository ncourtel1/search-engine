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