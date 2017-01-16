#useful defines:

# -DCMAKE_GENERATOR_PLATFORM=x64 or =x86



cmake_minimum_required (VERSION 3.4)
project (my_cool_project)

# The version number.
set (my_cool_project_VERSION_MAJOR 0)
set (my_cool_project_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 11)


if (WIN32)
	# disable autolinking in boost
	add_definitions( -DBOOST_ALL_DYN_LINK )
	add_definitions( -DBOOST_ALL_NO_LIB )
	set(Boost_USE_MULTITHREADED 	ON)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
endif()


# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/my_cool_project_config.h.in"
#  "${PROJECT_BINARY_DIR}/my_cool_project_config.h"
#  )

include_directories (include)

set(MY_COOL_PROJECT_HEADERS
	include/my_cool_library/other1.hpp
	include/my_cool_library/other2.hpp
	)


set(MY_COOL_LIBRARY_SOURCES
	src/my_cool_library/other1.cpp
	src/my_cool_library/other2.cpp
	)

set(MY_COOL_PROGRAM_HEADERS
	include/my_cool_program/header.hpp
	)

set(MY_COOL_PROGRAM_SOURCES
	src/my_cool_program/main.cpp
	)

include(GenerateExportHeader)


set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#include_directories("${PROJECT_BINARY_DIR}")

add_library(my_cool_library SHARED ${MY_COOL_LIBRARY_HEADERS} ${MY_COOL_LIBRARY_SOURCES})
add_executable(my_cool_program ${MY_COOL_PROGRAM_HEADERS}  ${MY_COOL_PROGRAM_SOURCES})
target_link_libraries(my_cool_program my_cool_library)


generate_export_header(my_cool_library
    BASE_NAME my_cool_library
    EXPORT_MACRO_NAME MY_COOL_LIBRARY_EXPORTS
    EXPORT_FILE_NAME my_cool_library_exports.h
    STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)

target_include_directories(my_cool_library PUBLIC ${CMAKE_BINARY_DIR})
target_include_directories(my_cool_program PUBLIC ${CMAKE_BINARY_DIR})

install(
		TARGETS my_cool_library my_cool_program
		ARCHIVE DESTINATION "lib"
		LIBRARY DESTINATION "lib"
		RUNTIME DESTINATION "bin")


install(
		FILES ${MY_COOL_PROJECT_HEADERS}
		DESTINATION "include/my_cool_library")


enable_testing()
#Setup CMake to run tests



#Prep for compiling against boost
find_package(Boost REQUIRED
			COMPONENTS
				unit_test_framework )

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS} ${CMAKE_BINARY_DIR}/lib)


set(MY_COOL_TEST_SOURCES
	test/my_cool_test.cpp)

add_executable(my_cool_test ${MY_COOL_TEST_SOURCES})
target_link_libraries(my_cool_test ${Boost_LIBRARIES} my_cool_library)


add_test(NAME my_cool_test
		COMMAND ${CMAKE_BINARY_DIR}/bin/my_cool_test)
