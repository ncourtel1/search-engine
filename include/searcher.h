#include <iostream>
#include <unordered_map>

const std::string UserInterface();
std::unordered_map<std::string, std::vector<int>> SearchStr(const std::vector<std::string>& files, const std::string& str);
void DisplayLineContent(std::unordered_map<std::string, std::vector<int>> fileAndLines);
void displayFileContent(const std::string& file);