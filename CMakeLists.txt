cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME raytracer)
set(SOURCE_DIR src)
set(LIBRARIES_DIR libs)

set(SOURCE ${SOURCE_DIR}/main.cpp)

project(${PROJECT_NAME})

include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

include_directories(include)

###############################################################################
### DEPENDENCIES ##############################################################
###############################################################################

###############################################################################
### TESTING ###################################################################
###############################################################################

###############################################################################
### PROJECT ###################################################################
###############################################################################

add_executable(${PROJECT_NAME} ${SOURCE})

foreach(LIBRARY ${LIBRARIES})
	add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})