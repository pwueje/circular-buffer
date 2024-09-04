set(component ${PROJECT_NAME}-test)

find_package(GTest REQUIRED)

add_executable(${component})

target_link_libraries(${component} PRIVATE GTest::gtest GTest::gtest_main pjexx::circularbuffer)

include(GoogleTest)
gtest_discover_tests(${component})

target_sources(${component} PRIVATE
    "tst_position.cpp"
)