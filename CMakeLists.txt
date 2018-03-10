cmake_minimum_required(VERSION 3.9)
project(C__primer)

#set(CMAKE_VERBOSE_MAKEFILE ON)

set(Boost_INCLUDE_DIR G:/Tools/boostForGcc/boost_1_66_0)
set(BOOST_ROOT G:/Tools/boostForGcc/boost_1_66_0)
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    message("Found boost")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
message(${CMAKE_CXX_FLAGS_RELEASE})
#SET(GCC_COVERAGE_COMPILE_FLAGS -lboost_system-mt)
#SET(GCC_COVERAGE_LINK_FLAGS    )
#SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

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
        C++primer/Account.cpp
        C++primer/Account.h
        C++primer/Debug.cpp
        C++primer/Debug.h
#        C++primer/FileAnalysis.cpp
#        C++primer/FileAnalysis.h
        C++primer/IO_error.cpp
        C++primer/IO_error.h
        C++primer/QueryResult.h
        C++primer/QueryResult.cpp
        C++primer/TextQuery.cpp
        C++primer/TextQuery.h
        C++primer/Blob.h
        C++primer/Folder.h
        C++primer/Folder.cpp
        C++primer/Message.h
        C++primer/Message.cpp
        C++primer/StrVec.cpp
        C++primer/StrVec.h
        C++primer/Quote.h
        C++primer/Quote.cpp
        C++primer/DiscountQuote.cpp
        C++primer/DiscountQuote.h
        C++primer/BulkQuote.h
        C++primer/BulkQuote.cpp
        C++primer/BulkQuoteWithLimit.cpp
        C++primer/BulkQuoteWithLimit.h
        "Note/Dynamic Memory.cpp"
        "Note/Defining Abstract Data Types.cpp" C++primer/BlobPtr.h)
target_link_libraries (C__primer ${Boost_LIBRARIES})