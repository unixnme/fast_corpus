cmake_minimum_required(VERSION 2.8.12)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O0 -g")

project(fast_corpus)

add_subdirectory(pybind11)
pybind11_add_module(fast_corpus src/main.cpp)

add_library(vocab src/vocab.cpp)
add_executable(corpus src/vocab.cpp src/corpus.cpp src/dictionary.cpp src/dictionary.h)
add_executable(dictionary src/dictionary.cpp)