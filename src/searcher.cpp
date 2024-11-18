#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "../include/indexer.h"

const std::string UserInterface() {
    int attempts = 0;
    std::string searchStr;

    while (attempts <= 3) {
        std::cout << "Enter a phrase/word to find: ";
        std::getline(std::cin, searchStr);  // Lire toute la ligne, y compris les espaces

        searchStr = cleanPhrase(searchStr);  // Nettoyer la phrase

        if (!searchStr.empty()) {
            return searchStr;
        }

        std::cerr << "Invalid input. Please enter a valid word or phrase.\n";
        attempts++;
    }

    std::cerr << "Too many invalid attempts. Exiting...\n";
    exit(EXIT_FAILURE);
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
   return fileAndLines;
}

void DisplayLineContent(std::unordered_map<std::string, std::vector<int>> fileAndLines){
   std::string response;

      for (const auto& [fileName, lineNumbers] : fileAndLines) {
         for (int lineNumber : lineNumbers) {
            // Ask the user if they want to see the content of a specific line
            std::cout << "Would you like to see the content of line " << lineNumber << " in the file \"" << fileName << "\"? (Yes or No): ";
            std::cin >> response;

            // Convert response to lowercase for comparison
            std::transform(response.begin(), response.end(), response.begin(), ::tolower);

            if (response == "y" || response == "yes") {
                  // Open the file to read the specific line
                  std::ifstream file(fileName);
                  if (!file.is_open()) {
                     std::cerr << "Error: Could not open file \"" << fileName << "\".\n";
                     continue;
                  }

                  std::string line;
                  int currentLineNumber = 1;

                  // Read the file line by line to find the requested line
                  while (std::getline(file, line)) {
                     if (currentLineNumber == lineNumber) {
                        std::cout << "Content of line " << lineNumber << ": " << line << "\n";
                        break; // Exit the loop once the line is found
                     }
                     currentLineNumber++;
                  }

                  file.close();
            } else {
                  std::cout << "Skipping line " << lineNumber << " in file \"" << fileName << "\".\n";
            }
         }
      }
}

// Function to display the content of files
void displayFileContent(const std::string& file) {
   std::string fileDisplayResponse;
   std::string line;

   std::cout << "Would you like to see the content of the files " << file << "? (Yes/No): ";
   std::cin >> fileDisplayResponse;

   // Convert response to lowercase for easier comparison
   for (auto& c : fileDisplayResponse) c = std::tolower(c);

   if (fileDisplayResponse == "y" || fileDisplayResponse == "yes") {
         std::cout << "\nContent in file: " << file << '\n';
         std::ifstream fileName(file);
         if (!fileName.is_open()) {
               std::cerr << "Error: Could not open file " << file << '\n';
               return;
         }
         while (std::getline(fileName, line)) {
               std::cout << line << '\n';
         }
      } else if (fileDisplayResponse != "n" && fileDisplayResponse != "no") {
      std::cerr << "Invalid input. Please type Yes or No.\n";
      displayFileContent(file);  // Ask again for a valid response
   }
   return;
}

bool AskForAction() {
   std::string response;
   std::cout << "\nWhat would you like to do?\n";
   std::cout << "1 - Stay\n" << "2 - Quit\n";
   std::cout << "Enter your choice (1-2): ";
   std::cin >> response;

   if (response == "1") {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return true; 
   } else if (response == "2") {
      std::cout << "Goodbye!\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return false;
   } else {
      std::cout << "Please enter a valid choice (1-2)\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return AskForAction();
   }
}