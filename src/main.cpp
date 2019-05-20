#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include "dictionary.h"

std::tuple<std::vector<std::vector<size_t>>, std::vector<std::string>>
process(const std::string& corpus_file) {
    Dictionary dictionary(corpus_file);
    return std::make_tuple(dictionary.get_data(), dictionary.get_vocab());
}

namespace py = pybind11;

PYBIND11_MODULE(fast_corpus, m) {
m.def("process", &process);

#ifdef VERSION_INFO
m.attr("__version__") = VERSION_INFO;
#else
m.attr("__version__") = "dev";
#endif
}
