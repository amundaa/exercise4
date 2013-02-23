# Name of our project
PROJECT(Summing)

# Tell cmake which version we require - 2.6 is enough for us
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# We use the C language
ENABLE_LANGUAGE(C)

# We want C99
INCLUDE(CheckCCompilerFlag)
CHECK_C_COMPILER_FLAG("-std=c99" HAVE_C99)

OPTION(USE_OPENMP "Use OpenMP?" ON)

IF (HAVE_C99)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
ELSE(HAVE_C99)
  MESSAGE(WARNING "C99 support not available, program may fail to compile!")
ENDIF(HAVE_C99)

IF(USE_OPENMP)
  FIND_PACKAGE(OpenMP)
ENDIF(USE_OPENMP)

# Add a library with common sources
ADD_LIBRARY(common common.c)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")

# Send the include directories to the compiler
INCLUDE_DIRECTORIES(${INCLUDES})

# Add a program consisting of these sources
ADD_EXECUTABLE(main main.c)
TARGET_LINK_LIBRARIES(main m)
TARGET_LINK_LIBRARIES(main common)

