cmake_minimum_required(VERSION 2.8.12)
project(fast_corpus)

add_subdirectory(pybind11)
pybind11_add_module(fast_corpus src/main.cpp)
