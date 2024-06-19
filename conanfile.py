from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

import os
from os.path import join

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy
from conan.tools.scm import Git


class CommsEqmSoftwareConan(ConanFile):
    name = "comms-eqm-software"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": False, "ecss-services/*:ecss_config_file_path": os.path.abspath("inc/Platform/")}

    requires = (
        "etl/20.37.2",
        "logger/1.0",
        "ecss-services/1.1",
        # "ccsds-telemetry-packets/1.0",
        # "comms-component-drivers/1.0",
    )
    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "inc/*", "lib/*"
    generators = "CMakeDeps", "CMakeToolchain"

    def source(self):
        git = Git(self)
        git.clone(url="git@github.com:PeakSat/comms-component-drivers.git", target=join(str(self.source_folder), "lib/atsam-component-drivers"))
        git.clone(url="git@github.com:PeakSat/ccsds-space-data-link-protocols.git", target=join(str(self.source_folder), "lib/ccsds-telemetry-packets"))

def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def requirements(self):
        self.requires("etl/20.37.2")
        self.requires("logger/1.0")
        self.requires("ecss-services/1.1")
        # self.requires("comms-component-drivers/1.0")
        # self.requires("ccsds-telemetry-packets/1.0")
