project(okular-mupdf)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
cmake_minimum_required(VERSION 2.8.12)

find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENJPEG2 REQUIRED libopenjp2)
pkg_check_modules(OPENSSL REQUIRED openssl)

find_package(ECM 5.19.0 CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

#TODO: find libmupdf with cmake
find_package(Okular5 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Freetype REQUIRED)
find_package(jbig2dec REQUIRED)
find_package(JPEG REQUIRED)

find_package(KF5 REQUIRED COMPONENTS
    CoreAddons
    I18n
    )

set(okularGenerator_mupdf_SRCS
  document.cpp
  page.cpp
  generator_mupdf.cpp
  synctex/synctex_parser.c
  synctex/synctex_parser_utils.c
)

kcoreaddons_add_plugin(okularGenerator_mupdf
    JSON "libokularGenerator_mupdf.json"
    INSTALL_NAMESPACE "okular/generators"
    SOURCES ${okularGenerator_mupdf_SRCS}
    )

target_link_libraries(okularGenerator_mupdf
    Okular::Core
    KF5::I18n
    mupdf mupdfthird
    harfbuzz
    ${ZLIB_LIBRARIES} ${FREETYPE_LIBRARIES} ${JBIG2DEC_LIBRARIES}
    ${JPEG_LIBRARIES} ${OPENJPEG2_LIBRARIES}
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
