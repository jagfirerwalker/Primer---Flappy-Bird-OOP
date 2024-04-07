cmake_minimum_required(VERSION 3.0.0)
project(Primer - Flappy Bird VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(Primer - Flappy Bird main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
