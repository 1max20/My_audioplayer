cmake_minimum_required(VERSION 3.16)

# Define the project name and version, and specify that it uses C++
project(My_player VERSION 0.1 LANGUAGES CXX)

# Enable automatic handling of UI, MOC, and resource files
set(CMAKE_AUTOUIC ON)  # Automatically process .ui files
set(CMAKE_AUTOMOC ON)  # Automatically run MOC on header files
set(CMAKE_AUTORCC ON)  # Automatically handle resource files

# Set the C++ standard to C++17 and require it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required Qt packages (support for both Qt5 and Qt6)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Multimedia)

# Include the current source directory for header file lookups
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# List of source files for the project
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    clickslider.cpp
    mainwindow.h
    clickslider.h
    mainwindow.ui
    resources.qrc
)

# Windows-specific settings for application icon
if(WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/Main_icon.rc")
    list(APPEND PROJECT_SOURCES ${APP_ICON_RESOURCE_WINDOWS})
endif()

# Create the executable target for the project
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(My_player
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(My_player
        ${PROJECT_SOURCES}
    )
endif()

# Link the necessary Qt libraries to the target
target_link_libraries(My_player PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
)

# Set properties for the target executable
set_target_properties(My_player PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Define a preprocessor macro to disable deprecated APIs before a certain version
target_compile_definitions(My_player PRIVATE QT_DISABLE_DEPRECATED_BEFORE=0x060000)

# Installation rules for the target
include(GNUInstallDirs)
install(TARGETS My_player
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalization step for Qt6 projects to complete the executable setup
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(My_player)
endif()
