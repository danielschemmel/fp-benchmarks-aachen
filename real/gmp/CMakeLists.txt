###############################################################################
# Build GNU multiple precision library (gmp) and make available as a target to
# link against.
###############################################################################
include(ExternalProject)

if (("${CMAKE_VERSION}" VERSION_EQUAL "3.4") OR ("${CMAKE_VERSION}" VERSION_GREATER "3.4"))
  set(EXTERNAL_PROJECT_USE_TERMINAL_ARGS
    USES_TERMINAL_CONFIGURE 1
    USES_TERMINAL_BUILD 1
    USES_TERMINAL_INSTALL 1
  )
else()
  set(EXTERNAL_PROJECT_USE_TERMINAL_ARGS "")
endif()

# Unfortunately `BUILD_ALWAYS` only seems to be supported with the version of ExternalProject
# that shipped with CMake >= 3.1. Should we just avoid using this option? We don't really
# need it unless we are patching gsl itself and need to rebuild.
if (("${CMAKE_VERSION}" VERSION_EQUAL "3.1") OR ("${CMAKE_VERSION}" VERSION_GREATER "3.1"))
  option(GMP_ALWAYS_REBUILD "Always try to rebuild GMP" ON)
  if (GMP_ALWAYS_REBUILD)
    set(EXTERNAL_PROJECT_BUILD_ALWAYS_ARG BUILD_ALWAYS 1)
  else()
    set(EXTERNAL_PROJECT_BUILD_ALWAYS_ARG BUILD_ALWAYS 0)
  endif()
else()
  set(EXTERNAL_PROJECT_BUILD_ALWAYS_ARG "")
  message(WARNING "The GNU multiple precision Library will not be automatically re-built. Try deleting the stamp files in BuildAndInstallGMP-stamp to trigger a rebuild")
endif()

set(GMP_AVAILABLE TRUE)
# Add a target to build and do a fake install of GSL
set(GMP_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gmp_install")
set(GMP_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/gmp_build")

if (DEFINED CMAKE_CONFIGURATION_TYPES)
  # FIXME: We can't set BINARY_DIR to use $<CONFIG> (it doesn't get expanded)
  # so we won't get separate builds for different build types. It's not worth
  # fixing this now so just don't support multi-configuration generators.
  message(FATAL_ERROR "Multi-configuration generators not supported")
endif()

string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_UPPER)
set(GMP_CFLAGS "${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}")
set(GMP_CXXFLAGS "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER}}")
# Generate a script to invoke the configure script so we can pass environment variables.
set(AUTOGEN_MESSAGE "Automatically generated. DO NOT EDIT!")
set(configure_script "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/gmp-6.1.1/configure")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/configure-wrapper.sh.in" "${CMAKE_CURRENT_BINARY_DIR}/configure-wrapper.sh" @ONLY)
unset(AUTOGEN_MESSAGE)
unset(configure_script)

ExternalProject_Add(BuildAndInstallGMP
  # Configure Step
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/gmp-6.1.1" # Do we need this?
  CONFIGURE_COMMAND sh "${CMAKE_CURRENT_BINARY_DIR}/configure-wrapper.sh"
  # Build step
  BINARY_DIR "${GMP_BUILD_DIR}"
  ${EXTERNAL_PROJECT_BUILD_ALWAYS_ARG}
  ${EXTERNAL_PROJECT_HAS_BYPRODUCTS_ARGS}
  BUILD_COMMAND
    make -j${EXTERNAL_PROJECT_JOBS} && make -j${EXTERNAL_PROJECT_JOBS} install
  ${EXTERNAL_PROJECT_USE_TERMINAL_ARGS}
)

set(GMP_INCLUDE_DIR "${GMP_INSTALL_PREFIX}/include")

# Import the built libraries.
#
# Note the choice of a static library here is very important
# as it means when building with wllvm that the extracted
# bitcode file will contain the code from the static library.
add_library(gmp_lib STATIC IMPORTED)
set_target_properties(gmp_lib PROPERTIES
  IMPORTED_LOCATION "${GMP_INSTALL_PREFIX}/lib/libgmp.a"
)
set(GMP_LIBS gmp_lib)
## Try to make sure that when targets link against these imported libraries
## That build and install is always done first.
add_dependencies(gmp_lib BuildAndInstallGMP)


###############################################################################
# Add benchmarks
###############################################################################
add_cmake_dependency_handler(gmp_dependency_handler.py)
# FIXME: These really should be split
add_benchmark(benchmarks)
