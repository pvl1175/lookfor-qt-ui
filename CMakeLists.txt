cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(demo)

if (MSVC)
    add_definitions(-DNOMINMAX)
endif()

add_definitions(-DUSE_STD_THREAD)
if (MSVC)
  option(BUILD_COMPILER "" OFF)
endif(MSVC)
option(WITH_BOOST_STATIC "" ON)
option(BUILD_TESTING "" OFF)
option(BUILD_TUTORIALS "" OFF)
option(BUILD_EXAMPLES "" OFF)
option(BUILD_PYTHON "" OFF)
option(WITH_SHARED_LIB "" OFF)
option(WITH_STATIC_LIB "" ON)
option(WITH_C_GLIB "" OFF)
option(WITH_JAVA "" OFF)
option(WITH_PYTHON "" OFF)
option(WITH_QT4 "" OFF)
option(WITH_QT5 "" OFF)
option(WITH_ZLIB "" OFF)
option(WITH_STDTHREADS "" ON)
option(WITH_LIBEVENT "" OFF)
option(WITH_OPENSSL "" OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(thrift)

find_package(Boost 1.70 REQUIRED)
include_directories("./thrift/lib/cpp/src")

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(helloworld_SRCS
	./api/lookfor9_constants.h
	./api/lookfor9_types.h
	./api/Api.h
	./api/lookfor9_constants.cpp
	./api/lookfor9_types.cpp
	./api/Api.cpp
    mainwindow.ui
    mainwindow.cpp
    main.cpp
    client.h
    client.cpp
)

add_executable(demo WIN32 ${helloworld_SRCS})

target_link_libraries(demo ${Boost_LIBRARIES})
target_link_libraries(demo Qt5::Widgets)
target_link_libraries(demo thrift_static)
