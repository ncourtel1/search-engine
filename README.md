# **Search Engine Project**

## **Overview**
This is a basic **Search Engine** project written in C++. The goal of this project is to create a program capable of indexing text files and performing efficient searches on their content. It allows users to search for phrases or words in a collection of text files. The program indexes files from a specified directory, processes their contents, and allows users to search for phrases. It displays the results with line numbers and optionally shows line or file content. The project is designed for learning and demonstrating key skills in C++ development, including file handling, data structures, and algorithms.

## Features
- **File indexing:** Automatically scans a directory to retrieve file names.
- **Word cleaning:** Removes unwanted characters and normalizes text to lowercase for consistent searching.
- **Phrase search:** Searches multiple files for a phrase and identifies the line numbers where it occurs.
- **Interactive display:** Allows users to view specific lines or entire files based on the search results.
- **Interactive loop:** Users can perform multiple searches before quitting.

---

## How It Works
1. **Indexing Files:**
   - The program scans a specified directory (`../data`) to retrieve all text files.
   - It processes each file, cleaning and counting the occurrences of words.

2. **Search Interface:**
   - The user inputs a phrase to search for.
   - The program performs a case-insensitive search across all indexed files.

3. **Displaying Results:**
   - The program shows the files and line numbers where the phrase is found.
   - Users can choose to view specific lines or the entire file content.

4. **Interactive Flow:**
   - Users can continue searching or exit the program via an interactive menu.

---

## **Project Structure**
The project is organized as follows:
``` bash
search-engine/
├── build/                # Directory for compiled binaries and object files
│
├── data/                 # Text files to be indexed and searched
│    ├── file1.txt        # Example text file to test the search engine
│    ├── file2.txt        # Another example text file
│
├── include/              # Header files containing function declarations and interfaces
│    ├── indexer.h        # Logic for file indexing (declarations of functions for parsing and cleaning files)
│    ├── searcher.h       # Logic for handling user queries (declarations for searching and displaying results)
│
├── src/                  # Source files containing implementation
│    ├── main.cpp         # Entry point for the program (handles user interactions and overall control flow)
│    ├── indexer.cpp      # Implementation of file indexing (parsing, cleaning, and counting words)
│    ├── searcher.cpp     # Implementation of search functionality (searching text and displaying results)
│
├── CMakeLists.txt        # CMake build configuration file (defines how the project is compiled)
│
```
---

## **Requirements**
To run and build this project, you need the following tools installed on your system:
- **C++ Compiler** (e.g., GCC, Clang, or MSVC) supporting C++17 or later
- **CMake** (version 3.10 or higher)
- A terminal or IDE (e.g., Visual Studio Code, CLion)

---

## **Getting Started**
Follow these steps to build and run the project:

### **1. Clone the Repository**
```bash
git clone https://github.com/ncourtel1/search-engine.git
cd search-engine
```

### **2. Build the Project**
Go in the build directory and run make to compile the project:
```bash
cd build
make
```

### **3. Run the Program**
After compilation, you can run the program:
```bash
./SearchEngine
```

### **4. Add Text Files to Index**
Place any .txt files you want to index in the data/ directory. The program will automatically process them.

## **Usage**
The program has a simple command-line interface. You can:

1.	**Index Files**: The program scans all text files in the data/ folder and builds an index.
2.	**Enter a word or phrase**, and the program will provide:
      - The files where the word or phrase appears.
      - The specific lines in each file where the word or phrase is found.
      - The option to view the content of those lines.
      - The option to view the content of the entire files.
3. **Choose an Action**:
      - **Stay**: Continue searching.
      - **Quit**: Exit the program.

## **License**

This project is licensed under the MIT License. Feel free to use, modify, and distribute it as you like.

## **Contact**

If you have any questions or suggestions, feel free to reach out:

   - Email: courtel.nattan19@gmail.com
   - GitHub: ncourtel1