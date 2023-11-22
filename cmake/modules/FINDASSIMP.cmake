# - Try to find Assimp
# Once done, this will define
# Assimp for MinGW uses version 5.2.0, while MinGW uses version 11.2.0 64-bit, statically compiled and use Debug made
#
# ASSIMP_FOUND - system has Assimp
# ASSIMP_INCLUDE_DIR - the Assimp include directories
# ASSIMP_LIBRARIES - link these to use Assimp

FIND_PATH(ASSIMP_INCLUDE_DIR assimp/mesh.h
      /usr/include
      /usr/local/include
      ${CMAKE_SOURCE_DIR}/include
)

if(MSVC)
      FIND_LIBRARY(ASSIMP_LIBRARY assimp
            /usr/lib64
            /usr/lib
            /usr/local/lib
            ${CMAKE_SOURCE_DIR}/lib
      )

IF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
SET( ASSIMP_FOUND TRUE )
SET( ASSIMP_LIBRARIES ${ASSIMP_LIBRARY} )
ENDIF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)

elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
      if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            # On MinGW, the library is likely to be named libassimpd.dll.a
            FIND_LIBRARY(ASSIMP_LIBRARIES_DEBUG assimpd
                  PATHS ${CMAKE_SOURCE_DIR}/lib)
            # On MinGW, the library is likely to be named libzlibstaticd.a
            FIND_LIBRARY(ZLIB_LIBRARY_DEBUG zlibstaticd
                  PATHS ${CMAKE_SOURCE_DIR}/lib)
            IF(ASSIMP_LIBRARIES_DEBUG AND ZLIB_LIBRARY_DEBUG AND ASSIMP_INCLUDE_DIR)
            SET(ASSIMP_FOUND TRUE)
            SET(ASSIMP_LIBRARIES
                  debug ${ASSIMP_LIBRARIES_DEBUG} ${ZLIB_LIBRARY_DEBUG}
                  optimized ${ASSIMP_LIBRARIES_RELEASE})
            ENDIF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
            ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Release")
            FIND_LIBRARY(ASSIMP_LIBRARIES_RELEASE assimp
                  PATHS ${CMAKE_SOURCE_DIR}/lib)
            IF(ASSIMP_LIBRARIES_RELEASE AND ASSIMP_INCLUDE_DIR)
            SET(ASSIMP_FOUND TRUE)
            SET(ASSIMP_LIBRARIES
                  release ${ASSIMP_LIBRARIES_RELEASE})
            ENDIF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
            ENDIF()
      endif()

      IF(ASSIMP_FOUND)
      IF(NOT ASSIMP_FIND_QUIETLY)
      MESSAGE(STATUS "Found ASSIMP: ${ASSIMP_LIBRARIES}")
      ENDIF(NOT ASSIMP_FIND_QUIETLY)
      ELSE(ASSIMP_FOUND)
      IF(ASSIMP_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find ASSIMP")
      ENDIF(ASSIMP_FIND_REQUIRED)
      ENDIF(ASSIMP_FOUND)
