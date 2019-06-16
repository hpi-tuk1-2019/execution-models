file (GLOB_RECURSE SRCS . *.cpp)

option(VECTORIZE OFF)
if (VECTORIZE)
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
      add_definitions("/O2 /Qvec-report:2")
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
      add_definitions("-march=core-avx2 -O3
 -vec -qopt-report-stdout -qopt-report-phase=vec")
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
      add_definitions("-Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize -march=native -O3 -ftree-vectorize")
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
      add_definitions("-fopt-info-vec -march=native -O3")
  endif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
else ()
# There is no supported way in the Microsoft C++ Compiler to turn off auto-vectorization using compilation flags. This has to be done on the specific loops with a pragma flag.
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
      add_definitions("-O3")
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
      add_definitions("-march=core-avx2 -O3
 -no-vec -qopt-report-stdout -qopt-report-phase=vec")
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
      add_definitions("-O3 -march=native -fno-tree-vectorize")
  endif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
endif (VECTORIZE)

add_library(${PROJECT_NAME}
    ${SRCS}
)

add_executable(Main
    Main.cpp
)

target_link_libraries(Main
    # Add libraries here
    ${PROJECT_NAME}
    ${EXTERNAL_LIBRARIES}
)
