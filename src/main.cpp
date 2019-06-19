#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
#include <vector>
#include <iostream>
#include "dictionary.h"

namespace py = pybind11;
PYBIND11_MAKE_OPAQUE(std::vector<unsigned int>);
PYBIND11_MAKE_OPAQUE(std::vector<std::vector<unsigned int>>);

std::tuple<std::vector<std::vector<size_t>>, std::vector<std::string>>
process(const std::string& corpus_file) {
    Dictionary dictionary(corpus_file);
    return std::make_tuple(dictionary.get_data(), dictionary.get_vocab());
}

std::vector<unsigned int>& get() {
    auto *v = new std::vector<unsigned int>();
    for (int i=0; i<100000000; i++) {
        v->emplace_back(i);
    }
    std::cout << "done\n";
    return *v;
}

std::vector<std::vector<unsigned int>>& get2() {
    auto *v = new std::vector<std::vector<unsigned int>>();
    for (int i=0; i<1000000; i++) {
        auto u = std::vector<unsigned int>();
        for (int j=0; j<100; j++) {
            u.emplace_back(j);
        }
        v->emplace_back(u);
    }
    std::cout << "done\n";
    return *v;
}
    

PYBIND11_MODULE(fast_corpus, m) {
py::bind_vector<std::vector<unsigned int>>(m, "VectorInt", py::buffer_protocol());
py::class_<std::vector<std::vector<unsigned int>>>(m, "VectorVectorInt")
    .def(py::init<>());
m.def("process", &process);
m.def("get", &get);
m.def("get2", &get2);

#ifdef VERSION_INFO
m.attr("__version__") = VERSION_INFO;
#else
m.attr("__version__") = "dev";
#endif
}
