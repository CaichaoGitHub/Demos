cmake_minimum_required(VERSION 3.13)
project(DataStructure)

FILE(GLOB OrderList ${PROJECT_SOURCE_DIR}/OrderList/*.*)
FILE(GLOB LinkList ${PROJECT_SOURCE_DIR}/LinkList/*.*)

set(CMAKE_CXX_STANDARD 11)

add_executable(DataStructure main.cpp ${OrderList} ${LinkList})