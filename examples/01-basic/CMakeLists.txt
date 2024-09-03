set(executable "circularbuffer-example-01")

add_executable(${executable} main.cpp)

target_link_libraries(${executable}
    PRIVATE
        build_properties
        pjexx::circularbuffer
)