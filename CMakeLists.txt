cmake_minimum_required(VERSION 3.16)

project(imgGen)

add_executable(imgGen imgGen.cpp)

install(TARGETS imgGen)

enable_testing()
add_test(NAME imgGen COMMAND imgGen)


IF (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_link_libraries(imgGen -static)
ENDIF()