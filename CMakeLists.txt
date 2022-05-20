cmake_minimum_required(VERSION 3.22)
project(Library_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Library_project main.cpp Journal.cpp Journal.h String.cpp String.h LibraryItem.h LibraryItem.cpp Admin.h Article.h Book.h Reader.h User.h Vector.h Genre.h Date.cpp Date.h Library.cpp Article.cpp)
