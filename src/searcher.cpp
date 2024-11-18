#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "../include/indexer.h"

// Function to prompt the user for a search term or phrase
const std::string UserInterface() {
    int attempts = 0;  // Limit user input attempts
    std::string searchStr;

    while (attempts <= 3) {
        std::cout << "Enter a phrase/word to find: ";
        std::getline(std::cin, searchStr);  // Read the full line, including spaces

        searchStr = cleanPhrase(searchStr);  // Clean the phrase

        if (!searchStr.empty()) {  // Validate input
            return searchStr;
        }

        std::cerr << "Invalid input. Please enter a valid word or phrase.\n";
        attempts++;
    }

    std::cerr << "Too many invalid attempts. Exiting...\n";
    exit(EXIT_FAILURE);  // Exit the program if attempts are exceeded
}

// Function to search for a string in multiple files and return matching line numbers
std::unordered_map<std::string, std::vector<int>> SearchStr(const std::vector<std::string>& files, const std::string& str) {
   std::string searchStr = str;  // Copy the search term
   std::transform(searchStr.begin(), searchStr.end(), searchStr.begin(), ::tolower);  // Convert to lowercase

   std::unordered_map<std::string, std::vector<int>> fileAndLines;  // Map for results

   std::cout << "Searching for the phrase: \"" << searchStr << "\"...\n";

   for (const std::string& fileName : files) {
      std::ifstream file(fileName);  // Open the file
      if (!file.is_open()) {  // Handle file errors
         std::cerr << "Error: Could not open file " << fileName << '\n';
         continue;
      }

      std::string line;
      int lineNumber = 1;  // Track line numbers

      while (std::getline(file, line)) {  // Read each line
         std::string lowerLine = line;  
         std::transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(), ::tolower);  // Convert line to lowercase

         if (lowerLine.find(searchStr) != std::string::npos) {  // Check for the search string
               fileAndLines[fileName].push_back(lineNumber);  // Store line number
         }

         lineNumber++;  // Increment line number
      }

      file.close();  // Close the file
   }

   // Display results to the user
   if (!fileAndLines.empty()) {
      for (const auto& [fileName, lineNumbers] : fileAndLines) {
         std::cout << "String \"" << searchStr << "\" found in file: " << fileName << '\n';
         std::cout << "At line number(s): ";
         for (size_t i = 0; i < lineNumbers.size(); ++i) {
               std::cout << lineNumbers[i];
               if (i != lineNumbers.size() - 1) {
                  std::cout << ", ";  // Format output
               }
         }
         std::cout << '\n';
      }
   } else {
      std::cout << "The string \"" << searchStr << "\" was not found in any file.\n";
   }
   return fileAndLines;
}

// Function to display specific lines in files if the user requests it
void DisplayLineContent(std::unordered_map<std::string, std::vector<int>> fileAndLines){
   std::string response;

   for (const auto& [fileName, lineNumbers] : fileAndLines) {
      for (int lineNumber : lineNumbers) {
         std::cout << "Would you like to see the content of line " << lineNumber << " in the file \"" << fileName << "\"? (Yes or No): ";
         std::cin >> response;

         std::transform(response.begin(), response.end(), response.begin(), ::tolower);  // Normalize user input

         if (response == "y" || response == "yes") {
            std::ifstream file(fileName);  // Open the file
            if (!file.is_open()) {  // Handle file errors
               std::cerr << "Error: Could not open file \"" << fileName << "\".\n";
               continue;
            }

            std::string line;
            int currentLineNumber = 1;

            while (std::getline(file, line)) {  // Read each line
               if (currentLineNumber == lineNumber) {  // Display the specific line
                  std::cout << "Content of line " << lineNumber << ": " << line << "\n";
                  break;
               }
               currentLineNumber++;
            }

            file.close();  // Close the file
         } else {
            std::cout << "Skipping line " << lineNumber << " in file \"" << fileName << "\".\n";
         }
      }
   }
}

// Function to display the entire content of a file if requested by the user
void displayFileContent(const std::string& file) {
   std::string fileDisplayResponse;
   std::string line;

   std::cout << "Would you like to see the content of the files " << file << "? (Yes/No): ";
   std::cin >> fileDisplayResponse;

   for (auto& c : fileDisplayResponse) c = std::tolower(c);  // Normalize user input

   if (fileDisplayResponse == "y" || fileDisplayResponse == "yes") {
      std::cout << "\nContent in file: " << file << '\n';
      std::ifstream fileName(file);
      if (!fileName.is_open()) {  // Handle file errors
         std::cerr << "Error: Could not open file " << file << '\n';
         return;
      }
      while (std::getline(fileName, line)) {  // Display each line
         std::cout << line << '\n';
      }
   } else if (fileDisplayResponse != "n" && fileDisplayResponse != "no") {
      std::cerr << "Invalid input. Please type Yes or No.\n";
      displayFileContent(file);  // Retry on invalid input
   }
   return;
}

// Function to prompt the user for their next action
bool AskForAction() {
   std::string response;
   std::cout << "\nWhat would you like to do?\n";
   std::cout << "1 - Stay\n" << "2 - Quit\n";
   std::cout << "Enter your choice (1-2): ";
   std::cin >> response;

   if (response == "1") {  // Stay in the program
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return true; 
   } else if (response == "2") {  // Exit the program
      std::cout << "Goodbye!\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return false;
   } else {  // Retry on invalid input
      std::cout << "Please enter a valid choice (1-2)\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return AskForAction();
   }
}