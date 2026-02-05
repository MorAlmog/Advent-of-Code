#pragma once
#include <string>
#include <fstream>
#include <ostream>

namespace io {

    std::ostream& console();

    class FileOutput {
        std::ofstream output_stream;
    public:
        explicit FileOutput(const std::string& path, std::ios::openmode mode = std::ios::trunc);
        ~FileOutput() = default;
        std::ostream& out();

        FileOutput(const FileOutput&) = delete;
        FileOutput& operator=(const FileOutput&) = delete;

    };
    
}

