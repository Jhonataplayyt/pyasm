# Kstool for Keystone assembler engine.
# By Nguyen Anh Quynh, 2016

cmake_minimum_required(VERSION 2.8)

project(kstool)

include_directories("../include")

include_directories("./")

add_executable(kstool kstool.cpp getopt.cpp)

target_link_libraries(kstool keystone)

install(TARGETS kstool DESTINATION bin)
