# Note that this script can accept some limited command-line arguments, run
# `julia build_tarballs.jl --help` to see a usage message.
using BinaryBuilder, Pkg

name = "JcVoronoi"
version = v"0.0.1"

# Collection of sources required to complete build
sources = [
    GitSource("https://github.com/AtsushiSakai/JcVoronoiBuilder.jl.git", "84580b249c1fbfe6abf2c2adbc79ae8370688870")
]

# Bash recipe for building across all platforms
script = raw"""
cd $WORKSPACE/srcdir
cd JcVoronoiBuilder.jl/jcvoronoi/
mkdir build
cd build/
cmake -DCMAKE_INSTALL_PREFIX=$prefix -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TARGET_TOOLCHAIN} -DCMAKE_BUILD_TYPE=Release ../
make
make install
"""

# These are the platforms we will build for by default, unless further
# platforms are passed in on the command line
platforms = supported_platforms()

# The products that we will ensure are always built
products = [
    LibraryProduct("libjcvoronoi", :JcVoronoi)
]

# Dependencies that must be installed before this package can be built
dependencies = Dependency[
]

# Build the tarballs, and possibly a `build.jl` as well.
build_tarballs(ARGS, name, version, sources, script, platforms, products, dependencies)
