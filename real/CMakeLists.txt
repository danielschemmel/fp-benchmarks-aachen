add_benchmark(sorting)
add_subdirectory(gmp)
add_benchmark(numerical_recipes)
add_benchmark(libmatheval)
add_benchmark(diction)
add_benchmark(units)

# HACK: Disable optimizing this benchmark when using old Clang because Clang 3.4.2
# hangs when trying to optimize this benchmark.
if ("${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
  if (${CMAKE_C_COMPILER_VERSION} VERSION_LESS "3.5")
    if (ENABLE_TARGET_UNITS_METER_FT)
      set(TARGET_TO_NOT_OPTIMIZE units_meter_ft.x86_64)
      message(WARNING "Detected you using Clang ${CMAKE_C_COMPILER_VERSION}."
        "Disabling optimizations for ${TARGET_TO_NOT_OPTIMIZE} to avoid compiler hang")
      target_compile_options(${TARGET_TO_NOT_OPTIMIZE} PRIVATE -O0)
    endif()
    if (ENABLE_TARGET_UNITS_METER_FT_NON_KLEE)
      set(TARGET_TO_NOT_OPTIMIZE units_meter_ft_non_klee.x86_64)
      message(WARNING "Detected you using Clang ${CMAKE_C_COMPILER_VERSION}."
        "Disabling optimizations for ${TARGET_TO_NOT_OPTIMIZE} to avoid compiler hang")
      target_compile_options(${TARGET_TO_NOT_OPTIMIZE} PRIVATE -O0)
    endif()
  endif()
endif()
