cmake_minimum_required(VERSION 3.23)
project(ToDo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

file(GLOB SOURCES CONFIGURE_DEPENDS "source/*.cpp")

add_executable(todo ${SOURCES} ${HEADERS})

target_include_directories(todo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers)
