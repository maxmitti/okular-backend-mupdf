include(FindPackageHandleStandardArgs)

find_path(MuPDF_INCLUDE_DIR
    NAMES mupdf/pdf.h
)

find_library(MuPDF_LIBRARY
    NAMES mupdf
    )
find_library(MuPDF_THIRD_LIBRARY
    NAMES mupdf-third
    )

find_package_handle_standard_args(MuPDF
    FOUND_VAR
        MuPDF_FOUND
    REQUIRED_VARS
        MuPDF_INCLUDE_DIR
        MuPDF_LIBRARY
        MuPDF_THIRD_LIBRARY
        )

if(MuPDF_FOUND AND NOT TARGET MuPDF::MuPDF)
    add_library(MuPDF::MuPDF UNKNOWN IMPORTED)
    set_target_properties(MuPDF::MuPDF PROPERTIES
        IMPORTED_LOCATION "${MuPDF_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${MuPDF_INCLUDE_DIR}")
endif()

mark_as_advanced(MuPDF_LIBRARY MuPDF_THIRD_LIBRARY MuPDF_INCLUDE_DIR)

if(MuPDF_FOUND)
    set(MuPDF_LIBRARIES ${MuPDF_LIBRARY} ${MuPDF_THIRD_LIBRARY})
    set(MuPDF_INCLUDE_DIRS ${MuPDF_INCLUDE_DIR})
endif()
