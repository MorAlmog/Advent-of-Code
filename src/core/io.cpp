#include <stdexcept>
#include <iostream>
#include <filesystem>
#include "core/io.h"

namespace io {

    std::ostream& console() {
        return std::cout;
    }
    FileOutput::FileOutput(const std::string& path, std::ios::openmode mode) {
        std::filesystem::create_directories("outputs");
        output_stream.open(std::filesystem::path("outputs") / path, mode);
        if (!output_stream) {
            throw std::runtime_error("Failed to open output file: " + path);
        }
    }

    std::ostream& FileOutput::out() {
        return output_stream;
    }

}