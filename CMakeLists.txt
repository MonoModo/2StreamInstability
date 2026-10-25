cmake_minimum_required(VERSION 3.20)

project(2StreamInstability LANGUAGES CXX)

include(FetchContent)

if(NOT EMSCRIPTEN)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(glfw)

    find_package(OpenGL REQUIRED)
endif()

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
file(GLOB APP_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rendering/shaders")
set(VERTEX_SHADER_FILE "${SHADER_DIR}/default.vs.glsl")
set(FRAGMENT_SHADER_FILE "${SHADER_DIR}/default.fs.glsl")
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    "${VERTEX_SHADER_FILE}"
    "${FRAGMENT_SHADER_FILE}"
)
file(READ "${VERTEX_SHADER_FILE}" VERTEX_SHADER_HEX HEX)
file(READ "${FRAGMENT_SHADER_FILE}" FRAGMENT_SHADER_HEX HEX)
string(REGEX REPLACE "([0-9a-fA-F][0-9a-fA-F])" "0x\\1," VERTEX_SHADER_BYTES "${VERTEX_SHADER_HEX}")
string(REGEX REPLACE "([0-9a-fA-F][0-9a-fA-F])" "0x\\1," FRAGMENT_SHADER_BYTES "${FRAGMENT_SHADER_HEX}")
set(GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${GENERATED_INCLUDE_DIR}")
file(WRITE "${GENERATED_INCLUDE_DIR}/embedded_shaders.h"
    "#pragma once\nnamespace EmbeddedShaders {\n"
    "static const unsigned char DefaultVertex[] = { ${VERTEX_SHADER_BYTES} 0x00 };\n"
    "static const unsigned char DefaultFragment[] = { ${FRAGMENT_SHADER_BYTES} 0x00 };\n"
    "}\n"
)

add_executable(example_glfw_opengl3
    ${APP_SOURCES}
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_compile_features(example_glfw_opengl3 PRIVATE cxx_std_17)
target_include_directories(example_glfw_opengl3 PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/enums
    ${GENERATED_INCLUDE_DIR}
)
if(EMSCRIPTEN)
    target_compile_definitions(example_glfw_opengl3 PRIVATE IMGUI_IMPL_OPENGL_ES3 GLFW_INCLUDE_ES3)
    target_compile_options(example_glfw_opengl3 PRIVATE -sUSE_GLFW=3 -sUSE_WEBGL2=1 -sFULL_ES3=1)
    target_link_options(example_glfw_opengl3 PRIVATE
        -sUSE_GLFW=3
        -sUSE_WEBGL2=1
        -sFULL_ES3=1
        -sALLOW_MEMORY_GROWTH=1
    )
    set_target_properties(example_glfw_opengl3 PROPERTIES SUFFIX ".html")
else()
    target_link_libraries(example_glfw_opengl3 PRIVATE glfw OpenGL::GL)
endif()