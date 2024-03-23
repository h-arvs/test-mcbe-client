cmake_minimum_required(VERSION 3.27)
project(Test)

include(FetchContent)

add_library(client SHARED "Load.cpp")

set_property(TARGET client PROPERTY CXX_STANDARD 23)
set_property(TARGET client PROPERTY CXX_STANDARD_REQUIRED ON)

# download(packagename github repo git tag)
function(download NAME REPO TAG)
    FetchContent_Declare(
        ${NAME}
        GIT_REPOSITORY ${REPO}
        GIT_TAG ${TAG} 
    )
    FetchContent_MakeAvailable(${NAME})
endfunction()

download(libhat https://github.com/BasedInc/libhat.git 82de2e6f19d3a5c0123d32ef6a5059034312df7b)
download(minhook https://github.com/TsudaKageyu/minhook.git f5485b8454544c2f034c78f8f127c1d03dea3636)
download(entt https://github.com/skypjack/entt.git fedcb920ce0068c35ffbc66fd4e84864e6ef71ef)
download(magic_enum https://github.com/Neargye/magic_enum 414fb654d36620f7b899f782f2743e43122325f6)

add_compile_definitions(ENTT_SPARSE_PAGE=2048)
add_compile_definitions(ENTT_PACKED_PAGE=128)

# LIBHAT LI BAT LIBHAT LIBAHAT MOREE LIBJHAT more libhat :))
add_subdirectory(Client)
add_subdirectory(Utils)
add_subdirectory(Include)

target_link_libraries(client PRIVATE minhook libhat EnTT magic_enum)

set_property(
    # any target that is compiled (has source files) likely needs to be here
    TARGET client libhat
    PROPERTY MSVC_RUNTIME_LIBRARY
    # Use /MT (statically-linked runtime library)
    MultiThreaded
)
