set(component ${PROJECT_NAME}-test)

find_package(GTest REQUIRED)

add_executable(${component})

target_link_libraries(${component} PRIVATE GTest::gtest GTest::gtest_main pjexx::circularbuffer)
target_add_common_build_properties(${component})
target_enable_clang_tidy(${component})
target_enable_coverage(${component})

include(GoogleTest)
gtest_discover_tests(${component})

target_sources(${component} PRIVATE
    "tst_position.cpp"
)
target_generate_coverage_report(${component})