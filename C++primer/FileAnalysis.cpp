#include "stdafx.h"
#include "FileAnalysis.h"
#include <fstream>
#include <iomanip>
#include <exception>
#include "IO_error.h"
#include <boost/filesystem.hpp>
using namespace std;

const std::string FileAnalysis::NOT_EXIST = " not exist";

auto FileAnalysis::analysisFile(const std::string & filePath)
{
    ifstream file(filePath);
    if (!file)
        throw IO_error("can't open file " + filePath);

    char input = 0;
    FileData data;
    while (input = file.get(), file)
    {
        ++data.chars;
        //cout << input;
        if (input == '\n')
            ++data.lines;
        else if (input == ' ')
            ++data.words;
    }
    cout << "In file ";
    cout << setw(40) << boost::filesystem::path(filePath).filename().string();
    printf("%6d lines %8d words %10d chars\n", data.lines, data.words, data.chars);
    return data;
}

int FileAnalysis::analysisDirectory(const std::string & directoryPath)
{
    using namespace boost::filesystem;
    if (is_directory(directoryPath))
    {
        for (auto &iter : directory_iterator(directoryPath))
        {
            if (iter.path().string().find("git") != string::npos) continue;
            if (is_directory(iter))
                analysisDirectory(iter.path().string());
            else
            {
                if (iter.path().string().find(".java") != -1)
                    analysisFile(iter.path().string());
            }
        }
    }
    return 1;
} 