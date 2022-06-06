cmake_minimum_required(VERSION 3.10.3)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_HOME_DIRECTORY}/cmake/concrete/modules)

include(Concrete)

project(${CONCRETE_PROJECT_DEFAULT_PARAMETER})

concrete_project(
    SimpleRayTracing
    VERSION         1 0 0 0
    DESCRIPTION     "simple ray tracing"
    HOMEPAGE_URL    ""
    LANGUAGES       CXX

    CONFIGURATION_TYPES  Debug Release

    ROOT_DIR            ${CMAKE_HOME_DIRECTORY}/
    BINARY_OUTPUT_DIR   ${CMAKE_HOME_DIRECTORY}/bin
    LIBRARY_OUTPUT_DIR  ${CMAKE_HOME_DIRECTORY}/lib
    WITH_COMPILER_TARGET_POSTFIX
)

concrete_set_global_properties(
    PROPERTIES 
        USE_FOLDERS  ON
        PREDEFINED_TARGETS_FOLDER "CMakeTargets"
)

set(SRC_DIR ${CONCRETE_PROJECT_ROOT_DIRECTORY}src)

concrete_source_directory_analyse(
    SRT ${SRC_DIR} 
    EXT h hpp cpp
)

concrete_sources_list(
    SRT_APP_SOURCES
        SOURCES 
            ${SRT_APP_SOURCES}
        SOURCES_FOLDER
            "App"        
        MSVC_SOURCES
            ${SRC_DIR}/SimpleRayTracing.rc
)

concrete_sources_list(
    SRT_COMMON_SOURCES
        SOURCES 
            ${SRT_COMMON_SOURCES}
        SOURCES_FOLDER
            "Common"
)

concrete_sources_list(
    SRT_MATH_SOURCES
        SOURCES 
            ${SRT_MATH_SOURCES}
        SOURCES_FOLDER
            "Math"
)

concrete_sources_list(
    SRT_RENDER_SOURCES
        SOURCES 
            ${SRT_RENDER_SOURCES}
        SOURCES_FOLDER
            "Render"
)

concrete_target(
    SimpleRayTracing "Execute"

    SOURCES
        ${SRT_APP_SOURCES}
        ${SRT_COMMON_SOURCES}
        ${SRT_MATH_SOURCES}
        ${SRT_RENDER_SOURCES}

    INCLUDE_DIRECTORIES
        PRIVATE 
            ${SRC_DIR}/App 
            ${SRC_DIR}/Common 
            ${SRC_DIR}/Geometry 
            ${SRC_DIR}/Math 
            ${SRC_DIR}/Render

    COMPILE_DEFINITIONS
            PUBLIC $<$<CXX_COMPILER_ID:MSVC>:UNICODE> $<$<CXX_COMPILER_ID:MSVC>:_UNICODE>    
)

concrete_set_vs_startup_project(SimpleRayTracing)