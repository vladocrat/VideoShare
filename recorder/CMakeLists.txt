cmake_minimum_required(VERSION 3.16)

set(CMAKE_AUTOMOC ON)

include(ffmpeg_setup.cmake)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui)

add_library(recorder STATIC
    recorder.h recorder.cpp
    processenumerator.h processenumerator.cpp
    process.h process.cpp
    settings.h settings.cpp
    pimpl.h
    frameworker.h frameworker.cpp
    recordingdevice.h recordingdevice.cpp
    recordingdevicefactory.h recordingdevicefactory.cpp
    streamoptions.h streamoptions.cpp
)

target_link_libraries(recorder PRIVATE
    Qt6::Core
    Qt6::Gui)

foreach(lib ${FFMPEG_LIBRARIES})
    message(STATUS ${FFMPEG_LIB_DIR}/${lib}.lib)
    target_link_libraries(recorder PRIVATE ${FFMPEG_LIB_DIR}/${lib}.lib)
endforeach()


