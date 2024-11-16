# **Search Engine Project**

## **Overview**
This is a basic **Search Engine** project written in C++. The goal of this project is to create a program capable of indexing text files and performing efficient searches on their content. The project is designed for learning and demonstrating key skills in C++ development, including file handling, data structures, and algorithms.

## **Features**
- **File Indexing**: Automatically scans and indexes words from multiple files.
- **Search Functionality**: Allows users to search for words and returns relevant files with occurrence counts.
- **Performance Optimization**: Uses efficient data structures (e.g., hash tables or trees) to speed up search queries.
- **Customizable**: Designed for easy expansion to include additional features like phrase searching or Boolean queries.

---

## **Project Structure**
The project is organized as follows:
search-engine/
├── CMakeLists.txt        # CMake configuration file
├── build/                # Directory for compiled files (generated during build)
├── include/              # Header files
│    ├── indexer.h        # Logic for file indexing
│    ├── searcher.h       # Logic for handling user queries
├── src/                  # Source files
│    ├── main.cpp         # Entry point for the program
│    ├── indexer.cpp      # Implementation of indexing
│    ├── searcher.cpp     # Implementation of search functionality
├── data/                 # Text files to be indexed
│    ├── file1.txt
│    ├── file2.txt
├── tests/                # Unit tests for the project
│    ├── test_indexer.cpp # Tests for indexing functionality
│    ├── test_searcher.cpp# Tests for search functionality
├── README.md             # Project documentation
└── .gitignore            # Git ignore file

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
git clone https://github.com/your-username/SearchEngine.git
cd SearchEngine
```

### **2. Build the Project**
Create a build directory and run CMake to configure and compile the project:
```bash
mkdir build
cd build
cmake ..
make
```

### **3. Run the Program**
After compilation, you can run the program:
```bash
./search-engine
```

### **4. Add Text Files to Index**
Place any .txt files you want to index in the data/ directory. The program will automatically process them.

## **Usage**
The program has a simple command-line interface. You can:

1.	Index Files: The program scans all text files in the data/ folder and builds an index.
2.	Search for Words: Enter a word, and the program will return:
      - Files where the word appears.
      - The number of occurrences in each file
3.	Quit: Exit the program.

## **Future Enhancements**

Planned improvements for the project include:

   - Phrase Searching: Allow users to search for multi-word phrases.
   - Boolean Queries: Support for queries like “word1 AND word2” or “word1 OR word2”.
   - Ranking Results: Sort search results based on relevance or frequency.
   - Web Interface: Add a simple GUI or web-based interface for easier use.

## **License**

This project is licensed under the MIT License. Feel free to use, modify, and distribute it as you like.

## **Contact**

If you have any questions or suggestions, feel free to reach out:

   - Email: courtel.nattan19@gmail.com
   - GitHub: ncourtel1