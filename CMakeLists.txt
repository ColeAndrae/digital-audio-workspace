cmake_minimum_required(VERSION 3.10)
project(DAW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

add_executable(DAW main.cpp)

target_link_libraries(DAW SFML::Graphics SFML::Window SFML::System SFML::Audio)
