cmake_minimum_required(VERSION 2.8.12)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O3 -g")

project(fast_corpus)

add_subdirectory(pybind11)
pybind11_add_module(fast_corpus src/main.cpp src/dictionary.cpp)

add_library(vocab src/vocab.cpp)
add_library(corpus src/vocab.cpp src/corpus.cpp)
add_library(dictionary src/dictionary.cpp)
