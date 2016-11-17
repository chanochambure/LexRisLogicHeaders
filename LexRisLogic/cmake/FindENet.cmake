# - Find ENet
# Find the ENet libraries
#
#  This module defines the following variables:
#     ENET_FOUND           - True if ENET_INCLUDE_DIR & ENET_LIBRARY
#                            are found
#     ENET_LIBRARIES       - Set when ENET_LIBRARY is found
#     ENET_INCLUDE_DIRS    - Set when ENET_INCLUDE_DIR is found
#
#     ENET_INCLUDE_DIR     - where to find enet.h, etc.
#     ENET_LIBRARY         - the enet library
#

#=============================================================================
#=============================================================================

FIND_PATH(ENET_INCLUDE_DIR NAMES enet/enet.h
          DOC "ENet include directory"
)

FIND_LIBRARY(ENET_LIBRARY NAMES enet
          DOC "The ENet library"
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ENET DEFAULT_MSG ENET_LIBRARY ENET_INCLUDE_DIR)

if(ENET_FOUND)
  SET( ENET_LIBRARIES ${ENET_LIBRARY} )
  SET( ENET_INCLUDE_DIRS ${ENET_INCLUDE_DIR} )
endif()

MARK_AS_ADVANCED(ENET_INCLUDE_DIR ENET_LIBRARY)