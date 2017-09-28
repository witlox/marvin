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

# souces
set(sources
        include/types.h
        src/utils.cpp include/utils.h
        src/smiley.cpp include/smiley.h
        src/emoji.cpp include/emoji.h
        src/lexicon.cpp include/lexicon.h
        src/download.cpp include/download.h
        src/feeds.cpp include/feeds.h
        src/sentiment.cpp include/sentiment.h
        src/library.cpp include/library.h
        src/tensorflow.cpp include/tensorflow.h
)

# our library
add_library(marvin ${sources})
target_link_libraries(marvin ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES} ${CURL_LIBRARIES})

# our test executable
add_definitions(-DCATCH_CONFIG_RUNNER)
add_definitions(-DCATCH_CONFIG_MAIN)
add_executable(marvin_tests test/marvin_tests.cpp test/tensorflow_inception_graph.pb test/imagenet_comp_graph_label_strings.txt)
target_link_libraries(marvin_tests marvin)
