project(Lab2)

add_executable(lab2.1
        2.1_mutex.cpp)

target_link_libraries(lab2.1
        -lpthread)

add_executable(lab2.2
        2.2_sync.cpp)

target_link_libraries(lab2.2
        -lpthread)
