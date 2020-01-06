cmake_minimum_required(VERSION 3.2)
project(vdtjson)

enable_testing()

set(CMAKE_CXX_STANDARD 17)

# recursively include all source files
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.cpp)
if(WIN32 OR UNIX OR APPLE)
	file(GLOB_RECURSE DESKTOP_SOURCE_FILES ${PROJECT_SOURCE_DIR}/platform/desktop/*.h ${PROJECT_SOURCE_DIR}/platform/desktop/*.cpp)
	list(APPEND PROJECT_SOURCE_FILES ${DESKTOP_SOURCE_FILES})
endif()

foreach(_source IN ITEMS ${PROJECT_SOURCE_FILES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${PROJECT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

add_library(
    ${PROJECT_NAME} 
	STATIC
	${PROJECT_SOURCE_FILES}
)