# - Find Allegro5.2
# Find the Allegro5.2 libraries
#
#  This module defines the following variables:
#     ALLEGRO5.2_FOUND     - True if ALLEGRO_INCLUDE_DIR & ALLEGRO_LIBRARY
#                            are found
#     ALLEGRO_INCLUDE_DIRS - Set when ALLEGRO_INCLUDE_DIR is found
#
#     ALLEGRO_INCLUDE_DIR  - where to find allegro5/allegro5.h, etc.
#

#=============================================================================
#=============================================================================

FIND_PATH(ALLEGRO_INCLUDE_DIR NAMES allegro5/allegro5.h
          DOC "Allegro5.2 include directory"
)

FIND_LIBRARY(ALLEGRO_LIBRARY NAMES allegro
          DOC "The Allegro5.2 library"
)

		FIND_LIBRARY(ALLEGRO_LIBRARY_ACODEC NAMES allegro_acodec
		          DOC "The Allegro5.2 library Acodec"
		)

		FIND_LIBRARY(ALLEGRO_LIBRARY_AUDIO NAMES allegro_audio
		          DOC "The Allegro5.2 library Audio"
		)

		FIND_LIBRARY(ALLEGRO_LIBRARY_COLOR NAMES allegro_color
		          DOC "The Allegro5.2 library Color"
		)

		FIND_LIBRARY(ALLEGRO_LIBRARY_DIALOG NAMES allegro_dialog
		          DOC "The Allegro5.2 library Dialog"
		)

		FIND_LIBRARY(ALLEGRO_LIBRARY_FONT NAMES allegro_font
		          DOC "The Allegro5.2 library Font"
		)

		FIND_LIBRARY(ALLEGRO_LIBRARY_IMAGE NAMES allegro_image
		          DOC "The Allegro5.2 library Image"
		)

		FIND_LIBRARY(ALLEGRO_LIBRARY_MAIN NAMES allegro_main
		          DOC "The Allegro5.2 library Main"
		)

		FIND_LIBRARY(ALLEGRO_LIBRARY_MEMFILE NAMES allegro_memfile
		          DOC "The Allegro5.2 library MemFile"
		)

		FIND_LIBRARY(ALLEGRO_LIBRARY_PHYSFS NAMES allegro_physfs
		          DOC "The Allegro5.2 library PhysFS"
		)

		FIND_LIBRARY(ALLEGRO_LIBRARY_PRIMITIVES NAMES allegro_primitives
		          DOC "The Allegro5.2 library Primitives"
		)

		FIND_LIBRARY(ALLEGRO_LIBRARY_TTF NAMES allegro_ttf
		          DOC "The Allegro5.2 library TTF"
		)

		FIND_LIBRARY(ALLEGRO_LIBRARY_VIDEO NAMES allegro_video
		          DOC "The Allegro5.2 library video"
		)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Allegro5.2 DEFAULT_MSG ALLEGRO_LIBRARY
														 ALLEGRO_LIBRARY_ACODEC
														 ALLEGRO_LIBRARY_AUDIO
														 ALLEGRO_LIBRARY_COLOR
														 ALLEGRO_LIBRARY_DIALOG
														 ALLEGRO_LIBRARY_FONT
														 ALLEGRO_LIBRARY_IMAGE
														 ALLEGRO_LIBRARY_MAIN
														 ALLEGRO_LIBRARY_MEMFILE
														 ALLEGRO_LIBRARY_PHYSFS
														 ALLEGRO_LIBRARY_PRIMITIVES
														 ALLEGRO_LIBRARY_TTF
														 ALLEGRO_LIBRARY_VIDEO
									ALLEGRO_INCLUDE_DIR)

if(ALLEGRO5.2_FOUND)
  SET( ALLEGRO_INCLUDE_DIRS ${ALLEGRO_INCLUDE_DIR} )
endif()

MARK_AS_ADVANCED(ALLEGRO_INCLUDE_DIR
				ALLEGRO_LIBRARY
				ALLEGRO_LIBRARY_ACODEC
				ALLEGRO_LIBRARY_AUDIO
				ALLEGRO_LIBRARY_COLOR
				ALLEGRO_LIBRARY_DIALOG
				ALLEGRO_LIBRARY_FONT
				ALLEGRO_LIBRARY_IMAGE
				ALLEGRO_LIBRARY_MAIN
				ALLEGRO_LIBRARY_MEMFILE
				ALLEGRO_LIBRARY_PHYSFS
				ALLEGRO_LIBRARY_PRIMITIVES
				ALLEGRO_LIBRARY_TTF
				ALLEGRO_LIBRARY_VIDEO
				)