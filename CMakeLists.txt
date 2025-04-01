cmake_minimum_required(VERSION 3.16)

project(VideoSharing VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

add_subdirectory(recorder)
include_directories(recorder)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(VideoSharing
    main.cpp
)

qt_add_qml_module(VideoSharing
    URI VideoSharing
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES devicesenumerationmodel.h devicesenumerationmodel.cpp
        SOURCES pimpl.h
        SOURCES frameprovider.h frameprovider.cpp
        SOURCES pixmapimage.h pixmapimage.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(VideoSharing PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.VideoSharing
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(VideoSharing
    PRIVATE Qt6::Quick recorder
)

include(GNUInstallDirs)
install(TARGETS VideoSharing
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
