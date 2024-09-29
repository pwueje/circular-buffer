# Copyright 2024 Philipp Jeske
# SPDX-License-Identifier: MIT

set(component ${PROJECT_NAME}-test)

find_package(GTest)

if (NOT GTest-FOUND)
    include(FetchContent)
    FetchContent_Declare(
      googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.15.2
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(${component})

target_link_libraries(${component} PRIVATE GTest::gtest GTest::gtest_main pjexx::circularbuffer)
target_add_common_build_properties(${component})
target_enable_clang_tidy(${component})
target_enable_coverage(${component})

include(GoogleTest)
gtest_discover_tests(${component})

target_sources(${component} PRIVATE
    "tst_circularbuffer.cpp"
    "tst_position.cpp"
)
target_generate_coverage_report(${component})