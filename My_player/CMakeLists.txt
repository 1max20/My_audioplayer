cmake_minimum_required(VERSION 3.10)

project(My_player VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Multimedia)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

qt_standard_project_setup()

qt_add_executable(MyPlayer
    main.cpp
    mainwindow.cpp
    clickslider.cpp
    mainwindow.h
    clickslider.h
    mainwindow.ui
    resources.qrc
    ${WIN32_ICON}
)

# Иконка только для Windows
if(WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/Main_icon.rc")
    list(APPEND PROJECT_SOURCES ${APP_ICON_RESOURCE_WINDOWS})
endif()

target_link_libraries(MyPlayer PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
)

set_target_properties(MyPlayer PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

