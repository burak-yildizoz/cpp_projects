cmake_minimum_required(VERSION 2.8.3)
project(RSA)

add_compile_options(-std=c++11)
add_compile_options(-O2)
add_compile_options(-Wall)

include_directories("include")
set(SOURCES "src/BigInt.cpp" "src/Prime.cpp")

add_executable(factorization main/factorization.cpp ${SOURCES})
target_link_libraries(factorization)

add_executable(RSA main/RSA.cpp ${SOURCES})
target_link_libraries(RSA)
