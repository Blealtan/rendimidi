cmake_minimum_required(VERSION 3.5)
project(rendimidi)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if (CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

include_directories("${CMAKE_SOURCE_DIR}/include")

set(SOURCE_FILES src/rendimidi.cpp)
add_library(rendimidi ${SOURCE_FILES})

set(OGRE_SDK "${CMAKE_SOURCE_DIR}/ogre_sdk" CACHE STRING "Set where your Ogre SDK places. Leave empty if installed to system directories in *nix." FORCE)
find_package(OGRE REQUIRED)
include_directories(${OGRE_INCLUDE_DIRS})
target_link_libraries(rendimidi ${OGRE_LIBRARIES})

set(EXAMPLE_SOURCE_FILES example/main.cpp)
add_executable(rendimidi_example ${EXAMPLE_SOURCE_FILES})
target_link_libraries(rendimidi_example rendimidi)

if (WIN32)
    add_custom_command(TARGET rendimidi_example POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "$<$<CONFIG:Debug>:${OGRE_BINARY_DBG}>$<$<CONFIG:Release>:${OGRE_BINARY_REL}>"
                    "$<TARGET_FILE_DIR:rendimidi_example>")
    add_custom_command(TARGET rendimidi_example POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "$<$<CONFIG:Debug>:${OGRE_Plugin_ParticleFX_DBG}>$<$<CONFIG:Release>:${OGRE_Plugin_ParticleFX_REL}>"
                    "$<TARGET_FILE_DIR:rendimidi_example>")
    add_custom_command(TARGET rendimidi_example POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "$<$<CONFIG:Debug>:${OGRE_RenderSystem_GL3Plus_DBG}>$<$<CONFIG:Release>:${OGRE_RenderSystem_GL3Plus_REL}>"
                    "$<TARGET_FILE_DIR:rendimidi_example>")
    add_custom_command(TARGET rendimidi_example POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "$<$<CONFIG:Debug>:${OGRE_RenderSystem_Direct3D11_DBG}>$<$<CONFIG:Release>:${OGRE_RenderSystem_Direct3D11_REL}>"
                    "$<TARGET_FILE_DIR:rendimidi_example>")
endif()
