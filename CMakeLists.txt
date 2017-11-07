cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

set(PROJECT itransition-task)

project(${PROJECT}
        VERSION 1.5.0)

# c++11
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")

file(GLOB SOURCES
    src/*.h
    src/*.cpp
    src/*.hpp
)
add_executable(${PROJECT} ${SOURCES})

# add EasyGumbo subproject directory
add_subdirectory(EasyGumbo)
# EasyGumbo link lib
target_link_libraries(${PROJECT} EasyGumbo)
# include EasyGumbo source files location
include_directories(EasyGumbo/src)

# add EasyCurl subproject directory
add_subdirectory(EasyCurl)
# EasyCurl link lib
target_link_libraries(${PROJECT} EasyCurl)
# include EasyCurl source files location
include_directories(EasyCurl/src)

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

# libsoup lib include-link:
# sudo apt-get install libsoup2.4-dev libglib2.0-dev
find_package(LibSoup REQUIRED)
if(LIBSOUP_FOUND)
    include_directories (${LIBSOUP_INCLUDE_DIRS})
    target_link_libraries (${PROJECT} ${LIBSOUP_LIBRARIES})
endif(LIBSOUP_FOUND)

# libgtk2.0 lib include-link:
# sudo apt-get install libgtk2.0-dev
find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK2 REQUIRED gtk+-2.0)
if(GTK2_FOUND)
	include_directories (${GTK2_INCLUDE_DIRS})
	target_link_libraries (${PROJECT} ${GTK2_LIBRARIES})
endif(GTK2_FOUND)