include(FetchContent)

cmake_minimum_required (VERSION 3.15)

add_library(client SHARED "Load.cpp" "client/CommandManager.cpp" "client/CommandManager.h" "client/commands/Command.h" "client/commands/PingCommand.h" "client/commands/PingCommand.cpp" "client/commands/HiCommand.cpp" "client/commands/HiCommand.h" "Utils/Mem.cpp")

set_property(TARGET client PROPERTY CXX_STANDARD 23)

FetchContent_Declare(
    libhat
    GIT_REPOSITORY https://github.com/BasedInc/libhat.git
    GIT_TAG 224fd84f37bb5ebcfb65d45db9af438ee68bac59
)
FetchContent_GetProperties(libhat)
if(NOT libhat_POPULATED)
    FetchContent_Populate(libhat)
    message("${libhat_SOURCE_DIR}")
    message("${libhat_BINARY_DIR}")
    add_subdirectory(${libhat_SOURCE_DIR} ${libhat_BINARY_DIR})
endif()




add_subdirectory(Include)
add_subdirectory(client)
add_subdirectory(Utils)

target_link_libraries(client PRIVATE minhook libhat)