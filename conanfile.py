from conan import ConanFile
from conan.tools.cmake import cmake_layout

class MatrixConanFile(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    
    def build_requirements(self):
        self.test_requires("gtest/1.15.0")
        
    def layout(self):
        cmake_layout(self)