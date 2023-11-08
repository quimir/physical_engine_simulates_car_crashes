cmake_minimum_required(VERSION 3.5)

project(physical_engine_simulates_car_crashes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools OpenGL OpenGLWidgets)

set(TS_FILES physical_engine_simulates_car_crashes_zh_CN.ts)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        include/src_include/mainwindow.h
        src/mainwindow.ui
        ${TS_FILES}
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

if(WIN32)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif(WIN32)

link_directories(${CMAKE_SOURCE_DIR}/lib)

#find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

if(WIN32)
      set(LIBS assimp)
      add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(physical_engine_simulates_car_crashes
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        include/src_include/mainentrybutton.h src/mainentrybutton.cpp
        include/src_include/settingwindow.h src/settingwindow.cpp
        include/src_include/filewirtesystem.h src/filewirtesystem.cpp
        include/src_include/filepathsystem.h src/filepathsystem.cpp
        include/src_include/filereadsystem.h src/filereadsystem.cpp
        include/src_include/settingbutton.h src/settingbutton.cpp
        include/src_include/shader.h src/shader.cpp
        include/src_include/geometricalias.h
        include/src_include/firstpersoncamera.h src/firstpersoncamera.cpp
        include/src_include/mesh.h src/mesh.cpp
        include/src_include/modelattribute.h
        include/src_include/model.h src/model.cpp
        include/src_include/assimp_qt_coversion.h
        include/src_include/startwindow.h src/startwindow.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET physical_engine_simulates_car_crashes APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(physical_engine_simulates_car_crashes SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(physical_engine_simulates_car_crashes
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

target_link_libraries(physical_engine_simulates_car_crashes PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
    ${LIBS}
    assimp
)

set_target_properties(physical_engine_simulates_car_crashes PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS physical_engine_simulates_car_crashes
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(physical_engine_simulates_car_crashes)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
