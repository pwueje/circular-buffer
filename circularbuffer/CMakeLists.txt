set(component "circularbuffer")

add_library(${component} INTERFACE)
add_library(pjexx::${component} ALIAS ${component})

target_include_directories(${component} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include/
)

target_compile_features(${component} INTERFACE cxx_std_20)

AddClangTidy(${component})

add_subdirectory(include/pjexx)