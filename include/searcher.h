#include <iostream>
#include <unordered_map>

std::vector<std::string> SearchWord(const std::unordered_map<std::string, std::unordered_map<std::string, int>>& dataBase, const std::string& word);
const std::string UserInterface();
void displayFileContent(const std::vector<std::string>& files);