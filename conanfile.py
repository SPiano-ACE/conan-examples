from conan import ConanFile


class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("boost/1.86.0")
        self.requires("qt/6.7.3")

    def configure(self):
        self.options["qt"].shared = True # Qt 使用动态库
        self.options["qt"].qtcharts = True # 启用 Qt Charts