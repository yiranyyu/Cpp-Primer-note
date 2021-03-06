#pragma once
#include <string>
#include <iosfwd>
class FileAnalysis
{
public:
    struct FileData
    {
        size_t lines = 0;
        size_t words = 0;
        size_t chars = 0;
    };
private:
    constexpr static int EXIST      = 0;
    constexpr static int EXECUTABLE = 1;
    constexpr static int WRITEABLE  = 2;
    constexpr static int READABLE   = 4;
    const static std::string NOT_EXIST;
public:
    FileAnalysis() = delete;
    ~FileAnalysis() = delete;

    static FileAnalysis::FileData analysisFile(const std::string &filePath);
    static int analysisDirectory(const std::string &directoryPath);
};

