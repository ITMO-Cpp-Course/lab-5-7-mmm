# Source files
set(SOURCES
    documentbuilder.cpp
    invertedindex.cpp
)

set(HEADERS
    document.hpp
    documentbuilder.hpp
    invertedindex.hpp
)

add_library(search_index STATIC ${SOURCES} ${HEADERS})

target_include_directories(search_index
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(search_index PRIVATE -Wall -Wextra -Wpedantic)