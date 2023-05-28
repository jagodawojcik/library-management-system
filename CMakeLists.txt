cmake_minimum_required(VERSION 3.22)

project(library-management-system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17")


set(src
    src/main.cpp
    src/book.h
    src/book.cpp
    src/catalogue.h
    src/catalogue.cpp
    src/entry_classified.h
    src/entry.h
    src/entry.cpp
    src/film.h
    src/film.cpp
    src/music_album.h
    src/music_album.cpp
)

add_executable(library-management-system ${src})
