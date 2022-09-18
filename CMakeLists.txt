cmake_minimum_required(VERSION 3.0.0)
project(sortview VERSION 0.1.0)

include(CTest)
enable_testing()

add_compile_options(
  /std:c++17
)

add_library(raylib::raylib SHARED IMPORTED)
set_target_properties(
  raylib::raylib
  PROPERTIES
  IMPORTED_IMPLIB "${PROJECT_SOURCE_DIR}/lib/raylib.lib"
  IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/lib/raylib.dll"
  IMPORTED_IMPLIB "${PROJECT_SOURCE_DIR}/lib/raylibdll.lib"
  IMPORTED_NO_SONAME "TRUE"
  INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/lib"
)

add_executable(sortview
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
        "${PROJECT_SOURCE_DIR}/src/msort.cpp"
        "${PROJECT_SOURCE_DIR}/src/sortview.cpp"
        "${PROJECT_SOURCE_DIR}/src/qsort.cpp"
        "${PROJECT_SOURCE_DIR}/src/insort.cpp"
        "${PROJECT_SOURCE_DIR}/src/selsort.cpp"
        "${PROJECT_SOURCE_DIR}/src/state.cpp"
        "${PROJECT_SOURCE_DIR}/src/menu.cpp"
)
target_link_libraries(sortview PRIVATE raylib::raylib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
