cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME mercator)
project(${PROJECT_NAME})

find_package(Eigen3 REQUIRED)
find_package(Ceres REQUIRED)
find_package(Boost
  COMPONENTS
  program_options
  system
  REQUIRED
)

find_package(OpenMP QUIET)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    add_definitions("-DOPENMP_ENABLED")
endif()

include(sources.cmake)

include_directories(
    src
    ${EIGEN3_INCLUDE_DIRS}
    ${CERES_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
  ${CERES_LIBRARIES}
  ${Boost_LIBRARIES}
)
