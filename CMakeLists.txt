cmake_minimum_required(VERSION 3.8)
project(marvin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

# xml stuff
find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})
add_definitions(-DLIBXML2_STATICLIB)

# downloads work with curl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
add_definitions(-DCURL_STATICLIB)

# boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.58.0 COMPONENTS log log_setup system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# local headers
include_directories(include)

set(sources
        include/types.h
        include/news_sources.h
        include/utils.h
        src/feeds.cpp include/feeds.h
        src/download.cpp include/download.h
        src/library.cpp include/library.h
)

# our library
add_library(marvin ${sources})
target_link_libraries(marvin ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES} ${CURL_LIBRARIES})

# our test executable
add_definitions(-DCATCH_CONFIG_RUNNER)
add_definitions(-DCATCH_CONFIG_MAIN)
add_executable(marvin_tests ${sources} test/marvin_tests.cpp)
target_link_libraries(marvin_tests ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES} ${CURL_LIBRARIES})
