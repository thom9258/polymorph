from conan import ConanFile
from conan.tools.files import copy

# https://docs.conan.io/2/tutorial/creating_packages/create_your_first_package.html

# build polymorph package:
#   conan create . 

# install polymorph in a project:
#   conan install . --output-folder=build --build=missing
#   cd build
#   cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
#   cmake --build .

class conantestRecipe(ConanFile):
    name = "polymorph"
    version = "1.1"
    package_type = "library"
    license = "<Put the package license here>"
    author = "Thomas Alexgaard Jensen"
    url = "https://github.com/thom9258/polymorph/"
    description = "A tiny, easy to use functional piping library."
    topics = ("functional", "piping", "readability")

    no_copy_source = True
    exports_sources = "polymorph/*"
    package_type = "header-library"

    def package(self):
        # This will also copy the "include" folder
        print(">> Source dir where exports_sources go: " + self.source_folder)
        print(">> Package dir: " + self.package_folder)
        
        # copy here takes the stuff exported from the exports_sources above
        # and puts it into a include/polymorph/ dir
        #copy(self, "*.hpp", self.source_folder, self.package_folder + "/include")

        #copies are relative to source folder, this is where exports_sources go
        
        source_dir = self.source_folder + "/polymorph"
        include_dir = self.package_folder + "/include/polymorph"
        headers = [
            "polymorph.hpp",       
            "assign.hpp",
            "detail.hpp",
            "enumerate.hpp",
            "filter.hpp",
            "fold.hpp",
            "fuse.hpp",
            "pipe.hpp",
            "stream.hpp",
            "take.hpp",
            "tee.hpp",
            "transform.hpp",
            "utils.hpp"]
        
        for header in headers:
            copy(self, header, source_dir, include_dir)
            print(">> copied " + header + " from " + source_dir + " to " + include_dir)

    def package_info(self):
        # For header-only packages, libdirs and bindirs are not used
        # so it's recommended to set those as empty.
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []

