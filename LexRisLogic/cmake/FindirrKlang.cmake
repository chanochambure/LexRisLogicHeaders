# - Find irrKlang
# Find the irrKlang libraries
#
#  This module defines the following variables:
#     IRRKLANG_FOUND       - True if IRRKLANG_INCLUDE_DIR & IRRKLANG_LIBRARY
#                            are found
#     IRRKLANG_LIBRARIES   - Set when IRRKLANG_LIBRARY is found
#     IRRKLANG_INCLUDE_DIRS- Set when IRRKLANG_INCLUDE_DIR is found
#
#     IRRKLANG_INCLUDE_DIR - where to find irrklang.h, etc.
#     IRRKLANG_LIBRARY     - the irrklang library
#

#=============================================================================
#=============================================================================

FIND_PATH(IRRKLANG_INCLUDE_DIR NAMES irrKlang.h
          DOC "irrKlang include directory"
)

FIND_LIBRARY(IRRKLANG_LIBRARY NAMES IrrKlang
          DOC "The irrKlang library"
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(irrKlang DEFAULT_MSG IRRKLANG_LIBRARY IRRKLANG_INCLUDE_DIR)

if(IRRKLANG_FOUND)
  SET( IRRKLANG_LIBRARIES ${IRRKLANG_LIBRARY})
  SET( IRRKLANG_INCLUDE_DIRS ${IRRKLANG_INCLUDE_DIR} )
endif()

MARK_AS_ADVANCED(IRRKLANG_INCLUDE_DIR IRRKLANG_LIBRARY)