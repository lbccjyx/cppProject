from conan import ConanFile
from conan.tools.cmake import CMake

class ImguiOpencvDemo(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def configure(self):
        self.settings.compiler.cppstd = "23"
        self.settings.compiler.runtime_type = "Debug"

    def requirements(self):
        self.requires("nlohmann_json/3.11.3")
        self.requires("boost/1.83.0")
        self.requires("websocketpp/0.8.2")
        self.requires("sfml/2.6.1")
        
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def build_requirements(self):
        self.tool_requires("cmake/3.27.4")
