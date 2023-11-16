cmake_minimum_required(VERSION 3.5)

project(physical_engine_simulates_car_crashes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Define supported build types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: Debug Release" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Add a flag bit to store the target name
set(QT_TARGET_NAME physical_engine_simulates_car_crashes)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools OpenGL OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools OpenGL OpenGLWidgets)

set(TS_FILES physical_engine_simulates_car_crashes_zh_CN.ts)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

link_directories(${CMAKE_SOURCE_DIR}/lib)

#find the required packages
find_package(PhysX REQUIRED)
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

set(LIBS assimp)

set(SHADER_FILES
      src/shader/text.vert
      src/shader/text.frag)

set(PROJECT_SOURCES
      src/main.cpp
      src/mainwindow.cpp
      include/src_include/mainwindow.h
      src/mainwindow.ui
      ${TS_FILES}
      ${SHADER_FILES}
)

#Add shader to separate Shader Files
source_group("Shader Files" FILES ${SHADER_FILES})

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
            include/src_include/animdata.h
            include/src_include/bone.h src/bone.cpp
            include/src_include/animator.h src/animator.cpp
            include/src_include/animation.h src/animation.cpp
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
      ${LIBS}
      Qt${QT_VERSION_MAJOR}::Widgets
      Qt${QT_VERSION_MAJOR}::OpenGL
      Qt${QT_VERSION_MAJOR}::OpenGLWidgets
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
