if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/crillab-easyjni-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package crillab-easyjni)

install(
    DIRECTORY
    include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT crillab-easyjni_Development
)

install(
    TARGETS crillab-easyjni_crillab-easyjni
    EXPORT crillab-easyjniTargets
    RUNTIME #
    COMPONENT crillab-easyjni_Runtime
    LIBRARY #
    COMPONENT crillab-easyjni_Runtime
    NAMELINK_COMPONENT crillab-easyjni_Development
    ARCHIVE #
    COMPONENT crillab-easyjni_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

if (VCPKG_TARGET_TRIPLET)
# Allow package maintainers to freely override the path for the configs
set(
    crillab-easyjni_INSTALL_CMAKEDIR "${CMAKE_INSTALL_PREFIX}/share/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
else ()
set(
    crillab-easyjni_INSTALL_CMAKEDIR "${CMAKE_INSTALL_INCLUDEDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
endif ()
mark_as_advanced(crillab-easyjni_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${crillab-easyjni_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT crillab-easyjni_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${crillab-easyjni_INSTALL_CMAKEDIR}"
    COMPONENT crillab-easyjni_Development
)

install(
    EXPORT crillab-easyjniTargets
    NAMESPACE crillab-easyjni::
    DESTINATION "${crillab-easyjni_INSTALL_CMAKEDIR}"
    COMPONENT crillab-easyjni_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
