set(component "circularbuffer")

add_library(${component})
add_library(pjexx::${component} ALIAS ${component})

target_include_directories(matrix INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include/
)

target_compile_features(matrix INTERFACE cxx_std_20)