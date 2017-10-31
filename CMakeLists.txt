cmake_minimum_required(VERSION 2.8)

project(itransition-task)

# c++11
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")

file(GLOB SOURCES
	main.cpp
    HTTPDownloader.h
    HTTPDownloader.cpp
    HTMLParser.h
    HTMLParser.cpp
    Adler32Generator.h
    Adler32Generator.cpp
    TextColor.hpp
)
add_executable(itransition-task ${SOURCES})

# zlib include-link:
# sudo apt-get install zlib1g-dev
find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    target_link_libraries(itransition-task ${ZLIB_LIBRARIES})
endif(ZLIB_FOUND)

# curl lib include-link:
# sudo apt-get install libcurl4-gnutls-dev
set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED)
if(CURL_FOUND)
	include_directories(${CURL_INCLUDE_DIR})
	target_link_libraries(itransition-task ${CURL_LIBRARIES})
endif(CURL_FOUND)

# gumbo html5 parcer lib include-link:
# sudo apt-get install libgumbo-dev
set(GUMBO_LIBRARY "-lgumbo")
# linux find_package error - use ./cmake/*.cmake files instead
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
find_package(Gumbo REQUIRED)
if(Gumbo_FOUND)
	include_directories(${Gumbo_INCLUDE_DIRS})
	target_link_libraries(itransition-task ${Gumbo_LIBRARY})
endif(Gumbo_FOUND)

# cppnet lib include-link:
# sudo apt-get install libcppnetlib-dev
# sudo apt-get install libboost-test-dev
find_package(cppnetlib REQUIRED)
if(cppnetlib_FOUND)
    include_directories (${CPPNETLIB_INCLUDE_DIRS})
    target_link_libraries (itransition-task ${CPPNETLIB_LIBRARIES})
endif(cppnetlib_FOUND)