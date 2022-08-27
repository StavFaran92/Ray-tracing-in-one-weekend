cmake_minimum_required(VERSION 3.21.2)

project(ray-tracing-in-one-weekend VERSION 1.0)

add_executable(${PROJECT_NAME} 
	main.cpp 
	ImageUtils.cpp 
	ImageUtils.h 
	Ray.cpp. 
	Ray.h 
	Color.h 
	Color.cpp 
	Hittable.h 
	Sphere.h 
	Sphere.cpp
	HittableList.h
	HittableList.cpp
	Constants.h)

target_include_directories(${PROJECT_NAME} PUBLIC extern/stb)
target_include_directories(${PROJECT_NAME} PUBLIC extern/glm)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

add_subdirectory(extern)