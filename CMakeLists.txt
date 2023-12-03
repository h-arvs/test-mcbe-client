cmake_minimum_required(VERSION 3.18)
project(Test)

include(FetchContent)

add_library(client SHARED "Load.cpp")

set_property(TARGET client PROPERTY CXX_STANDARD 23)

FetchContent_Declare(
    libhat
    GIT_REPOSITORY https://github.com/BasedInc/libhat.git
    GIT_TAG 224fd84f37bb5ebcfb65d45db9af438ee68bac59
)
FetchContent_MakeAvailable(libhat)

# LIBHAT LI BAT LIBHAT LIBAHAT MOREE LIBJHAT
add_subdirectory(Include)
add_subdirectory(Client)
add_subdirectory(Utils)

target_link_libraries(client PRIVATE minhook libhat)

set_property(
    # any target that is compiled (has source files) likely needs to be here
    TARGET client libhat
    PROPERTY MSVC_RUNTIME_LIBRARY
    # Use /MT (statically-linked runtime library)
    MultiThreaded
)
