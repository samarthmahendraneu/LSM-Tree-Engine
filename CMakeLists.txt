cmake_minimum_required(VERSION 3.20)
project(LSMTreeEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lsm_engine
        main.cpp
        main.cpp
        core/types/Entry.cpp
        core/types/Entry.h
        core/types/value_type.h
        core/types/internal_key.cpp
        core/types/internal_key.h
        core/types/internal_key_comparator.h
        core/memtable/MemTable.cpp
        core/memtable/MemTable.h
        core/wal/Wal.cpp
        core/wal/Wal.h
        core/db/DB.cpp
        core/db/DB.h
)
