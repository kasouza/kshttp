cmake_minimum_required(VERSION 3.0.0)

set(SOURCES
    Request.cpp
    Response.cpp
    Server.cpp
)

add_library(kshttp STATIC ${SOURCES})
target_include_directories(kshttp PRIVATE ${PROJECT_SOURCE_DIR}/include/)
target_compile_features(kshttp PRIVATE cxx_std_17)
