project(Lab3)

cmake_minimum_required(VERSION 3.10)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(
        .
)

add_executable(
        main
        main.cpp
)

add_executable(
        writebuf
        Semaphore.cpp
        write.cpp
)

add_executable(
        readbuf
        Semaphore.cpp
        read.cpp
)