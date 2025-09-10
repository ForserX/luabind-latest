add_executable(test_app entry.cpp)
target_include_directories(test_app PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(test_app PRIVATE luabind)