cmake_minimum_required(VERSION 2.8.1)
project(im2model_slices_engine)
set(RDKAFKA_MIN_VERSION 0x00090400)
set (CMAKE_CXX_STANDARD 11)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")


# Build output checks
option(CPPKAFKA_CMAKE_VERBOSE "Generate verbose output." ON)
option(CPPKAFKA_BUILD_SHARED "Build cppkafka as a shared library." ON)
option(CPPKAFKA_BOOST_STATIC_LIBS "Link with Boost static libraries." ON)
option(CPPKAFKA_BOOST_USE_MULTITHREADED "Use Boost multithreaded libraries." ON)
option(CPPKAFKA_RDKAFKA_STATIC_LIB "Link with Rdkafka static library." ON)

# Disable output from find_package macro
if (NOT CPPKAFKA_CMAKE_VERBOSE)
  set(FIND_PACKAGE_QUIET QUIET)
endif()


# Look for Boost (just need boost.optional headers here)
find_package(Boost REQUIRED )
find_package(RdKafka REQUIRED )

if(CPPKAFKA_BUILD_SHARED)
  message(STATUS "Build will generate a shared library. "
    "Use CPPKAFKA_BUILD_SHARED=0 to perform a static build")
  set(CPPKAFKA_LIBRARY_TYPE SHARED)
else()
  message(STATUS "Build will generate a static library.")
  set(CPPKAFKA_LIBRARY_TYPE STATIC)
  add_definitions("-DCPPKAFKA_STATIC=1")
endif()

if (CPPKAFKA_RDKAFKA_STATIC_LIB)
  add_definitions("-DLIBRDKAFKA_STATICLIB")
endif()

if (Boost_FOUND)
  find_package(Boost COMPONENTS program_options ${FIND_PACKAGE_QUIET})
  set(Boost_USE_STATIC_LIBS ${CPPKAFKA_BOOST_STATIC_LIBS})
  set(Boost_USE_MULTITHREADED ${CPPKAFKA_BOOST_USE_MULTITHREADED})
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
  if (CPPKAFKA_CMAKE_VERBOSE)
    message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost library dir: ${Boost_LIBRARY_DIRS}")
    message(STATUS "Boost use static libs: ${Boost_USE_STATIC_LIBS}")
    message(STATUS "Boost is multi-threaded: ${CPPKAFKA_BOOST_USE_MULTITHREADED}")
    message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
  endif()
endif()


add_subdirectory(src)

