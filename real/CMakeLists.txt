add_benchmark(sorting)
add_benchmark(gmp)
add_benchmark(numerical_recipes)
add_benchmark(libmatheval)
add_benchmark(diction)
add_benchmark(units)

# HACK: Disable optimizing this benchmark when using old Clang because Clang 3.4.2
# hangs when trying to optimize this benchmark.
if (ENABLE_TARGET_UNITS_METER_FT)
  if ("${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
    if (${CMAKE_C_COMPILER_VERSION} VERSION_LESS "3.5")
      set(TARGET_TO_NOT_OPTIMIZE units_meter_ft.x86_64)
      message(WARNING "Detected you using Clang ${CMAKE_C_COMPILER_VERSION}."
        "Disabling optimizations for ${TARGET_TO_NOT_OPTIMIZE} to avoid compiler hang")
      target_compile_options(${TARGET_TO_NOT_OPTIMIZE} PRIVATE -O0)
    endif()
  endif()
endif()
