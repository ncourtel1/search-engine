cmake_minimum_required(VERSION 3.31)
project(search-engine)

# Définit le standard C++
set(CMAKE_CXX_STANDARD 23)

# Ajoute les fichiers sources
set(SOURCES
    src/main.cpp
    src/Indexer.cpp
    src/Searcher.cpp
)

# Ajoute les fichiers d'en-tête
include_directories(include)

# Crée l'exécutable
add_executable(SearchEngine ${SOURCES})