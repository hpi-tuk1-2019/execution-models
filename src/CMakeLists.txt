file (GLOB_RECURSE SRCS . *.cpp)

if (WIN32)
    add_definitions("-fopt-info-vec /Qvec-report:2")
endif (WIN32)

if (UNIX)
    add_definitions("-fopt-info-vec -O2")
endif (UNIX)

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