cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)

project(spawn-fcgi)
set(PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(PACKAGE_VERSION 1.6.3)

set(CMAKE_MAN_DIR "share/man" CACHE STRING "Install location for man pages (relative to prefix).")
mark_as_advanced(CMAKE_MAN_DIR)

# Set Default build type to RelWithDebInfo
if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(CMAKE_BUILD_TYPE STREQUAL "")

add_subdirectory(src)

install(FILES spawn-fcgi.1 DESTINATION ${CMAKE_MAN_DIR}/man1)
