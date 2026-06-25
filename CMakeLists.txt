cmake_minimum_required(VERSION 3.14...3.28)
project(076cpputils LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "静的リンク" FORCE)

set(DB_NAME "test.db" CACHE STRING "データベースのパス" FORCE)

option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)
add_subdirectory(deps/glfw)
add_subdirectory(deps/sqlite)

add_library(076cpputils)

file(GLOB_RECURSE CPPUTILS_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")
file(GLOB_RECURSE CPPUTILS_INC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh")

target_sources(076cpputils PRIVATE "${CPPUTILS_SRC}")
target_include_directories(076cpputils PUBLIC include)

	if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  set(DB_NAME "test.db" CACHE STRING "データベースのパス" FORCE)
  set(PRODUCTION_BUILD OFF CACHE BOOL "リリース版？" FORCE)
  target_compile_definitions(076cpputils PRIVATE
    DB_NAME="test.db"
    DB_RELATIVE_TO_EXE
  )
else()
  set(PRODUCTION_BUILD ON CACHE BOOL "リリース版？" FORCE)
  if(WIN32)
    set(DB_NAME "$ENV{LOCALAPPDATA}/076Studio/Test/data/test.db" CACHE STRING "データベースのパス" FORCE)
  elseif(UNIX)
    set(DB_NAME "$ENV{HOME}/.local/share/Test/test.db" CACHE STRING "データベースのパス" FORCE)
  else()
    set(DB_NAME "test.db" CACHE STRING "データベースのパス" FORCE)
  endif()
  target_compile_definitions(076cpputils PRIVATE PRODUCTION_BUILD DB_NAME="${DB_NAME}")
endif()

target_link_libraries(076cpputils PRIVATE
  glfw
  sqlite3
)
