from conan import ConanFile
from conan.tools.cmake import CMake

class ImguiOpencvDemo(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    #requires = "nlohmann_json/3.11.3"

    generators = "CMakeToolchain"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
       