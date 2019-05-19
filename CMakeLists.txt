cmake_minimum_required(VERSION 2.8.12)
set (CMAKE_CXX_STANDARD 11)

project(fast_corpus)

add_subdirectory(pybind11)
pybind11_add_module(fast_corpus src/main.cpp)

add_executable(vocab src/vocab.cpp)
