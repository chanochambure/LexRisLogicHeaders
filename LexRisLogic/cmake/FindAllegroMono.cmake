# - Find AllegroMono
# Find the Allegro Monolith 5.2 libraries
#
#  This module defines the following variables:
#     ALLEGROMONO_FOUND     - True if ALLEGRO_INCLUDE_DIR & ALLEGRO_LIBRARY
#                            are found
#     ALLEGRO_LIBRARIES    - Set when ALLEGRO_LIBRARY is found
#     ALLEGRO_INCLUDE_DIRS - Set when ALLEGRO_INCLUDE_DIR is found
#
#     ALLEGRO_INCLUDE_DIR  - where to find allegro5/allegro5.h, etc.
#     ALLEGRO_LIBRARY      - the allegro monolith library
#

#=============================================================================
#=============================================================================

FIND_PATH(ALLEGRO_INCLUDE_DIR NAMES allegro5/allegro5.h
          DOC "Allegro Monolith 5.2 include directory"
)

FIND_LIBRARY(ALLEGRO_LIBRARY NAMES allegro_monolith
          DOC "The Allegro Monolith 5.2 library"
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(AllegroMono DEFAULT_MSG ALLEGRO_LIBRARY ALLEGRO_INCLUDE_DIR)

if(ALLEGROMONO_FOUND)
  SET( ALLEGRO_LIBRARIES ${ALLEGRO_LIBRARY} )
  SET( ALLEGRO_INCLUDE_DIRS ${ALLEGRO_INCLUDE_DIR} )
else(ALLEGROMONO_FOUND)
	SET( ALLEGRO_MONO_FOUND OFF)
endif()

MARK_AS_ADVANCED(ALLEGRO_INCLUDE_DIR ALLEGRO_LIBRARY)