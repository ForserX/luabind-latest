cmake_minimum_required(VERSION 3.16)
project(luabind-latest CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(LUABIND_USE_EXTERNAL_LUA "Use external luajit-ixray from GitHub" ON)
option(LUABIND_TESTAPP "Add test application" ON)
option(LUABIND_NO_RTTI "Disable RTTI usage in luabind" OFF)
option(LUABIND_DEBUG_SCRIPTS "Enable Lua debug scripts" OFF)
option(LUABIND_NO_RTTI "Disable RTTI usage in luabind" OFF)

set(FOLDER_3RD FOLDER "3rd Party")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (LUABIND_TESTAPP)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()

if (LUABIND_USE_EXTERNAL_LUA)
    include(FetchContent)
    FetchContent_Declare(
        luajit
        GIT_REPOSITORY https://github.com/ixray-team/luajit-ixray.git
        GIT_TAG        default
    )
    FetchContent_MakeAvailable(luajit)
    set(LUA_INCLUDE_DIR ${luajit_SOURCE_DIR}/src)
    set(LUA_LIB luajit)
    
    set_target_properties(gendef PROPERTIES ${FOLDER_3RD})
    set_target_properties(dynasm PROPERTIES ${FOLDER_3RD})
    set_target_properties(buildvm PROPERTIES ${FOLDER_3RD})
    set_target_properties(libluajit PROPERTIES ${FOLDER_3RD})
    set_target_properties(minilua PROPERTIES ${FOLDER_3RD})
else()
    find_package(Lua REQUIRED)
    set(LUA_INCLUDE_DIR ${LUA_INCLUDE_DIR})
    set(LUA_LIB Lua::Lua)
endif()

add_subdirectory(luabind)

if (LUABIND_TESTAPP)
    add_subdirectory(example)
endif()

if (LUABIND_DEBUG_SCRIPTS)
    add_compile_definitions(LUA_DEBUG)
endif()

if (LUABIND_NO_RTTI)
    add_compile_definitions(LUABIND_NO_RTTI)
endif()