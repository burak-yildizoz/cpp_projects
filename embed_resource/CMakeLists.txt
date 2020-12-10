project(test)
cmake_minimum_required(VERSION 2.8)

include(embed_resource.txt)
embed_resource("res/test.txt" "include/test.h" "TEST")

include_directories("include")

add_executable(main main.cpp)
target_link_libraries(main)
