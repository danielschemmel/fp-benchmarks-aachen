add_benchmark(atof)
add_benchmark(halve)
add_benchmark(inf)
add_benchmark(member)
add_benchmark(simple)
add_benchmark(simple2)
add_benchmark(sqr)

add_benchmark(ld-add)
add_benchmark(ld-overwrite)
add_benchmark(ld-unnormal)


# HACK: Disable optimizing this benchmark when using Clang because it
# incorrectly constant folds this benchmark.
# This bug was reported at https://llvm.org/bugs/show_bug.cgi?id=31294 .
if (ENABLE_TARGET_LD-UNNORMAL_DEFAULT)
  if ("${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
    set(TARGET_TO_NOT_OPTIMIZE ld-unnormal_default.x86_64)
    message(WARNING "Detected you using Clang ${CMAKE_C_COMPILER_VERSION}."
      "Disabling optimizations for ${TARGET_TO_NOT_OPTIMIZE} to avoid miscompilation")
    target_compile_options(${TARGET_TO_NOT_OPTIMIZE} PRIVATE -O0)
  endif()
endif()


add_benchmark(mod)
add_benchmark(nan)
