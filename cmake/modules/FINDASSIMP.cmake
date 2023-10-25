# - Try to find Assimp
# Once done, this will define
#
# ASSIMP_FOUND - system has Assimp
# ASSIMP_INCLUDE_DIR - the Assimp include directories
# ASSIMP_LIBRARIES - link these to use Assimp

FIND_PATH( ASSIMP_INCLUDE_DIR assimp/mesh.h
      /usr/include
      /usr/local/include
      /opt/local/include
      ${CMAKE_SOURCE_DIR}/include)

FIND_LIBRARY( ASSIMP_LIBRARY assimp
      /usr/lib64
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      ${CMAKE_SOURCE_DIR}/lib)

IF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)
set( ASSIMP_FOUND TRUE)
set( ASSIMP_LIBRARIES ${ASSIMP_LIBRARY})
ENDIF(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY)

IF(ASSIMP_FOUND)
IF(NOT ASSIMP_FIND_QUIETLY)
MESSAGE(STATUS "Found ASSIMP: ${ASSIMP_LIBRARY}")
ENDIF(NOT ASSIMP_FIND_QUIETLY)
ELSE(ASSIMP_FOUND)
IF(ASSIMP_FIND_QUIETLY)
MESSAGE(FATAL_ERROR "Could not find libAssimp")
ENDIF(ASSIMP_FIND_QUIETLY)
ENDIF(ASSIMP_FOUND)
