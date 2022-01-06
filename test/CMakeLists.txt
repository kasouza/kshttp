# Unit tests
add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain kshttp)
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

# This executable basically uses the library, right now it is manual but maybe a
# python script can be used to automate it
add_executable(integration_test integration_test.cpp)
target_link_libraries(integration_test kshttp)
target_include_directories(integration_test PRIVATE ${PROJECT_SOURCE_DIR}/include)

include(Catch)
catch_discover_tests(tests)