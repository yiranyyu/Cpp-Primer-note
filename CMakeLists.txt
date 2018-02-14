cmake_minimum_required(VERSION 3.9)
project(C__primer)

set(CMAKE_CXX_STANDARD 11)

add_executable(C__primer
        C++primer/C++primer.cpp
        C++primer/Chapter2_Sample.cpp
        C++primer/Person.cpp
        C++primer/Person.h
        C++primer/Sales_data.cpp
        C++primer/Sales_data.h
        C++primer/Sales_item.cpp
        C++primer/Sales_item.h
        C++primer/Screen.cpp
        C++primer/Screen.h
        C++primer/SolutionChapter1.cpp
        C++primer/SolutionChapter2.cpp
        C++primer/stdafx.cpp
        C++primer/stdafx.h
        C++primer/targetver.h
        C++primer/Tools.cpp
        C++primer/Tools.h
        C++primer/Window_mgr.cpp
        C++primer/Window_mgr.h
        "Note/Defining Abstract Data Types.cpp")
