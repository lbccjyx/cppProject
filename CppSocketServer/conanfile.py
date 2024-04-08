from conan import ConanFile
from conan.tools.cmake import CMake

class ImguiOpencvDemo(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    generators = "CMakeToolchain"
    def configure(self):
        self.settings.compiler.cppstd = "23"

    def requirements(self):
        self.requires("nlohmann_json/3.11.3")
        self.requires("boost/1.76.0")
        
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def build_requirements(self):
        self.tool_requires("cmake/3.25.3")
