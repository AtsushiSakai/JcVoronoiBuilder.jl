project(jcvoronoi)

cmake_minimum_required(VERSION 3.1)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_library(jcvoronoi SHARED jcvoronoi.c)

set_property(TARGET jcvoronoi PROPERTY C_STANDARD 99) # jc_voronoi needs C99 mode

install(TARGETS
  jcvoronoi
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib
RUNTIME DESTINATION bin)
