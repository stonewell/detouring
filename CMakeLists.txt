CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

CMAKE_POLICY(
    SET CMP0048 NEW
    )

PROJECT (detouring
	VERSION 1.0.0
	LANGUAGES C CXX
)

INCLUDE(ExternalProject)

IF(APPLE)
  SET(CMAKE_MACOSX_RPATH 1)
  SET(CMAKE_PREFIX_PATH /usr/local)
ENDIF()

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "DEBUG")
  #SET(CMAKE_BUILD_TYPE "RELEASE")
  #SET(CMAKE_BUILD_TYPE "RELWITHDEBINFO")
  #SET(CMAKE_BUILD_TYPE "MINSIZEREL")
ENDIF()

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(warnings "-Wall -Wextra -Werror")
  set(no_undefined "-Wl,--no-undefined")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(warnings "-Wall -Wextra -Werror -Wno-inconsistent-missing-override")
  set(no_undefined "-Wl,-undefined,error")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
    set(no_undefined "")
endif()

SET(CXX_STANDARD_REQUIRED OFF)
SET(CXX_EXTENSION NO)

if (NOT CONFIGURED_ONCE)
    set(CMAKE_C_FLAGS "-fPIC ${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_CXX_FLAGS "-fPIC ${warnings} -std=c++14"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_LINK_FLAGS "${no_undefined}"
        CACHE STRING "Flags used by the linker during all build types." FORCE)
endif()

SET(HDE_SRC
hde/include/hde64.h
hde/include/table64.h
hde/include/hde32.h
hde/include/table32.h
hde/src/hde32.c
hde/src/hde64.c
hde/src/hde.c
)

SET(MINIHOOK_SRC
minhook/include/minhook.h
minhook/src/architecture.h
minhook/src/buffer.c
minhook/src/trampoline.h
minhook/src/buffer.h
minhook/src/trampoline.c
minhook/src/hook.c
)

SET(DETOURING_SRC
detours.h
classproxy.hpp
hde.h
hook.hpp
hook.cpp
vfnhook.h
helpers.cpp helpers.hpp
Platform.hpp
)

ADD_LIBRARY(detouring STATIC
    ${DETOURING_SRC}
    ${HDE_SRC}
    ${MINIHOOK_SRC}
)

TARGET_INCLUDE_DIRECTORIES(detouring PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

ADD_SUBDIRECTORY(test)
