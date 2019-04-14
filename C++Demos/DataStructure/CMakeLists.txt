cmake_minimum_required(VERSION 3.13)
project(DataStructure)

FILE(GLOB OrderList ${PROJECT_SOURCE_DIR}/OrderList/*.*)
FILE(GLOB LinkList ${PROJECT_SOURCE_DIR}/LinkList/*.*)
FILE(GLOB queue ${PROJECT_SOURCE_DIR}/stack&queue/*.*)
FILE(GLOB string ${PROJECT_SOURCE_DIR}/string/*.*)
FILE(GLOB array ${PROJECT_SOURCE_DIR}/Array/*.*)
FILE(GLOB tree ${PROJECT_SOURCE_DIR}/tree/*.*)
FILE(GLOB graph ${PROJECT_SOURCE_DIR}/Graph/*.*)
FILE(GLOB Search ${PROJECT_SOURCE_DIR}/Search/*.*)
FILE(GLOB Sort ${PROJECT_SOURCE_DIR}/Sort/*.*)


set(CMAKE_CXX_STANDARD 11)

add_executable(DataStructure main.cpp ${OrderList} ${LinkList} ${queue} ${string} ${array} ${tree} ${graph} ${Search} ${Sort})