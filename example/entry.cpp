#include <iostream>
#include <luabind/luabind.hpp>
#include <luabind/iterator_pair_policy.hpp>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

std::map<unsigned long long, float> TestMap =
{
	{51151, 12.f},
	{2312512515, 0.8f}
};

std::map<unsigned long long, float> GetTestMap()
{
	return TestMap;
}


static void* luabind_allocator(luabind::memory_allocation_function_parameter const, void const* const pointer, size_t const size)
{
	if (!size)
	{
		void* non_const_pointer = const_cast<void*>(pointer);
		free(non_const_pointer);
		return	(0);
	}

	if (!pointer)
	{
		return malloc(size);
	}

	void* non_const_pointer = const_cast<void*>(pointer);
	return realloc(non_const_pointer, size);
}

int main()
{
	luabind::allocator = &luabind_allocator;
	luabind::allocator_parameter = 0;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    luabind::open(L);

#ifdef LUA_DEBUG
    std::cout << "LUA_DEBUG enabled\n";
#endif

#ifdef LUABIND_NO_RTTI
    std::cout << "LUABIND_NO_RTTI enabled\n";
#endif

    // пример привязки функции
    luabind::module(L)
    [
        luabind::def("hello", &GetTestMap, luabind::return_stl_pair_iterator)
    ];

	luaL_dostring
	(
		L,
		R"(
			for k, v in hello() do
			    print("Key:", k, "Value:", v)
			end
		)"
	);

    lua_close(L);
    return 0;
}
