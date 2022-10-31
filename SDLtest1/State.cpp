#include "stdafx.h"
#include "State.h"

State::State(const char* lua_state_file)
{
	this->L = luaL_newstate();
	luaL_openlibs(this->L);

	int error = luaL_dofile(this->L, lua_state_file);
	if (error) {
		std::cout << "LUA::ERROR::STATE::CONSTRUCTOR::" << lua_tostring(this->L, -1) << '\n';
		lua_pop(this->L, lua_gettop(this->L));
		throw("CPP:;ERROR::STATE::Could not open file %s", lua_state_file);
	}
}

State::~State()
{
	lua_close(this->L);
}

void State::update()
{
	lua_getglobal(this->L, "Update");
	int error = lua_pcall(this->L, 0, 0, 0);
	if (error) {
		std::cout << "LUA::ERROR::STATE::UPDATE::" << lua_tostring(this->L, -1) << '\n';
		lua_pop(this->L, lua_gettop(this->L));
		throw("CPP:;ERROR::STATE::UPDATE::Cannot call Update function");
	}
}

void State::render()
{
	lua_getglobal(this->L, "Render");
	int error = lua_pcall(this->L, 0, 0, 0);
	if (error) {
		std::cout << "LUA::ERROR::STATE::RENDER::" << lua_tostring(this->L, -1) << '\n';
		lua_pop(this->L, lua_gettop(this->L));
		throw("CPP:;ERROR::STATE::RENDER::Cannot call Render function");
	}
}
