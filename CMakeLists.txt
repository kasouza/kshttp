cmake_minimum_required(VERSION 3.0.0)
project(kshttp VERSION 0.1.0)

# include(CTest)
# enable_testing()

set(SOURCES main.cpp
    Request.cpp
    Response.cpp
    Server.cpp
)

# Prepend all the source filenames with /src/
list(TRANSFORM SOURCES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/src/)

add_executable(kshttp ${SOURCES})
target_include_directories(kshttp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
