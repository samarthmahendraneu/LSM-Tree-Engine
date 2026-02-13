cmake_minimum_required(VERSION 3.20)
project(LSMTreeEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lsm_engine
        main.cpp
        main.cpp
        core/Entry.cpp
        core/Entry.h
        core/value_type.h
        core/internal_key.cpp
        core/internal_key.h
        core/internal_key_comparator.h
)
