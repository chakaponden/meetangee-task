cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

set(PROJECT itransition-task)

project(${PROJECT}
        VERSION 1.0.0)

# c++11
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")

file(GLOB SOURCES
	main.cpp
    ICurlEasyDownloader.h
    DownloaderParallel.h
    DownloaderParallel.cpp
    DownloaderString.h
    DownloaderString.cpp
    DownloaderFile.h
    DownloaderFile.cpp
    HTMLParser.h
    HTMLParser.cpp
    Adler32Generator.h
    Adler32Generator.cpp
    TextColor.hpp
)
add_executable(${PROJECT} ${SOURCES})

# name target executable with version
# set_target_properties(${PROJECT} PROPERTIES OUTPUT_NAME ${PROJECT}-${PROJECT_VERSION})

# zlib include-link:
# sudo apt-get install zlib1g-dev
find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    target_link_libraries(${PROJECT} ${ZLIB_LIBRARIES})
endif(ZLIB_FOUND)

# curl lib include-link:
# sudo apt-get install libcurl4-gnutls-dev
set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED)
if(CURL_FOUND)
	include_directories(${CURL_INCLUDE_DIR})
	target_link_libraries(${PROJECT} ${CURL_LIBRARIES})
endif(CURL_FOUND)

# gumbo html5 parcer lib include-link:
# sudo apt-get install libgumbo-dev
set(GUMBO_LIBRARY "-lgumbo")
# linux find_package error - use ./cmake/*.cmake files instead
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
find_package(Gumbo REQUIRED)
if(Gumbo_FOUND)
	include_directories(${Gumbo_INCLUDE_DIRS})
	target_link_libraries(${PROJECT} ${Gumbo_LIBRARY})
endif(Gumbo_FOUND)

# cppnet lib include-link:
# sudo apt-get install libcppnetlib-dev
# sudo apt-get install libboost-test-dev
find_package(cppnetlib REQUIRED)
if(cppnetlib_FOUND)
    include_directories (${CPPNETLIB_INCLUDE_DIRS})
    target_link_libraries (${PROJECT} ${CPPNETLIB_LIBRARIES})
endif(cppnetlib_FOUND)