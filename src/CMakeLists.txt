file (GLOB_RECURSE SRCS . *.cpp)

option(VECTORIZE OFF)

if (VECTORIZE)
  if (WIN32)
      add_definitions("-fopt-info-vec /Qvec-report:2")
  elseif (APPLE)
      add_definitions("-Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize -march=native -O3 -ftree-vectorize")
  elseif (UNIX)
      add_definitions("-fopt-info-vec -march=native -O3 -ftree-vectorize")
  endif (WIN32)
else ()
  if (APPLE)
      add_definitions("-O3")
  elseif (UNIX)
      add_definitions("-O3")
  endif (APPLE)
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
