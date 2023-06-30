cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    crillab-easyjni
    VERSION 0.1.0
    DESCRIPTION "Invoking Java code from C++ made easy"
    HOMEPAGE_URL "https://github.com/crillab/easyjni"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# Configuring the use of JNI.
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# ---- Declare library ----

file(GLOB_RECURSE HEADERS
        ${PROJECT_SOURCE_DIR}/include/**.h
        )

file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/source/**.cpp
        )

add_library(
    crillab-easyjni_crillab-easyjni
    ${HEADERS} ${SOURCES}
)
add_library(crillab-easyjni::crillab-easyjni ALIAS crillab-easyjni_crillab-easyjni)
target_link_libraries(crillab-easyjni_crillab-easyjni ${JNI_LIBRARIES})

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(crillab-easyjni_crillab-easyjni PUBLIC CRILLAB_EASYJNI_STATIC_DEFINE)
endif()

set_target_properties(
    crillab-easyjni_crillab-easyjni PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME crillab-easyjni
    OUTPUT_NAME crillab-easyjni
)

target_include_directories(
    crillab-easyjni_crillab-easyjni ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    crillab-easyjni_crillab-easyjni SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(crillab-easyjni_crillab-easyjni PUBLIC cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT crillab-easyjni_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of crillab-easyjni"
  )
endif()

include(cmake/dev-mode.cmake)

# Adding the executable (for demonstration purposes) to the build targets.
# It is only built on UNIX systems because of the use of getopt().
if (UNIX)
    add_executable(crillab-easyjni-demo example/main.cpp)
    target_link_libraries(crillab-easyjni-demo crillab-easyjni_crillab-easyjni)
endif (UNIX)
