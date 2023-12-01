cmake_minimum_required (VERSION 3.15)

add_library(client SHARED "Load.cpp" "client/CommandManager.cpp" "client/CommandManager.h" "client/commands/Command.h" "client/commands/PingCommand.h" "client/commands/PingCommand.cpp" "client/commands/HiCommand.cpp" "client/commands/HiCommand.h")

set_property(TARGET client PROPERTY CXX_STANDARD 17)

add_subdirectory(Include)
add_subdirectory(client)

target_link_libraries(client PRIVATE minhook)