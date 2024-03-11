from conan import ConanFile
from conan.tools.cmake import CMake

class ImguiOpencvDemo(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "boost/1.76.0"

    generators = "CMakeToolchain"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
       