cmake_minimum_required(VERSION 3.10.2)

project(Kanzaki)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(code ${SOURCES} )

target_link_libraries(code PRIVATE -lcurl -lstdc++fs)
