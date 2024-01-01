add_subdirectory(Command)
add_subdirectory(Hook)
add_subdirectory(SDK)
add_subdirectory(Module)
add_subdirectory(Event)

target_sources(client PRIVATE "System.cpp")
