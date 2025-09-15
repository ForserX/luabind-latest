set(LUABIND_SRC_FILES)

# Files import
file(GLOB LUABIND_SOURCE_ALL_FILES CONFIGURE_DEPENDS
    "src/*.*"
)
file(GLOB_RECURSE LUABIND_INCL_ALL_FILES CONFIGURE_DEPENDS
    "include/*.*"
)

source_group("src" FILES ${LUABIND_SOURCE_ALL_FILES})
source_group("include" FILES ${LUABIND_INCL_ALL_FILES})

# Apply list
list(APPEND LUABIND_SRC_FILES ${LUABIND_SOURCE_ALL_FILES})
list(APPEND LUABIND_SRC_FILES ${LUABIND_INCL_ALL_FILES})

add_library(luabind SHARED ${LUABIND_SRC_FILES})
target_include_directories(luabind PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories(luabind PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_compile_definitions(luabind PRIVATE LUABIND_BUILDING)
target_compile_definitions(luabind PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:LUABIND_NO_EXCEPTIONS>")
target_compile_definitions(luabind PUBLIC "$<$<CONFIG:RELEASE>:LUABIND_NO_EXCEPTIONS>")

if (LUABIND_USE_EXTERNAL_LUA)
    target_link_libraries(luabind PUBLIC libluajit)
else()
    target_link_libraries(luabind PUBLIC Lua::Lua)
endif()

set_target_properties(luabind PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
