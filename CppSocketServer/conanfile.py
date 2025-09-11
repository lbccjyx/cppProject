from conan import ConanFile
from conan.tools.cmake import CMake

class ImguiOpencvDemo(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    options = {
        "shared": [True, False],
    }
    default_options = {
        "shared": True,  # 使用动态库
        "*:shared": True,  # 所有依赖使用动态库
    }

    def configure(self):
        self.settings.compiler.cppstd = "23"
        self.settings.compiler.runtime_type = "Debug"

    def requirements(self):
        # 使用 nlohmann_json 库
        self.requires("nlohmann_json/3.12.0", override=True)
        self.requires("boost/1.83.0", override=True)
        self.requires("websocketpp/0.8.2", override=True)
        
        
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def build_requirements(self):
        self.tool_requires("cmake/3.27.4")
