set(executable "circularbuffer-example-01")

add_executable(${executable} main.cpp)

target_link_libraries(${executable}
    PRIVATE
        pjexx::circularbuffer
)
target_add_common_build_properties(${executable})
target_enable_clang_tidy(${executable})

target_compile_features(${executable} PRIVATE cxx_std_20)
