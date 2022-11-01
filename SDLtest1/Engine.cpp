#include "stdafx.h"
#include "Engine.h"


void Engine::initStates()
{
	this->test = 400;
	this->pushState("Game_State_Lua.lua");
}

void Engine::registerCppFunctions(lua_State* L)
{
	lua_pushcfunction(L, luaTest);
	lua_setglobal(L, "cpp_luaTest");

	lua_pushcfunction(L, cpp_createWindow);
	lua_setglobal(L, "cpp_createWindow");
}

Engine::Engine()
{
	this->initStates();
}

Engine::~Engine()
{
	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

void Engine::pushState(const char* lua_state_file)
{
	this->states.push(new State("Game_State_Lua.lua"));

	lua_pushlightuserdata(this->states.top()->getLuaState(), this);

	lua_setglobal(this->states.top()->getLuaState(), LUA_ENGINE_ACCESSOR);

	this->registerCppFunctions(this->states.top()->getLuaState());

	this->states.top()->loadFile();

	this->states.top()->initialize();
}

void Engine::pollEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT:

				SDL_DestroyWindow(this->window);
				exit(0);
				break;

			default:
				break;
		}
	}
}

void Engine::update()
{
	this->pollEvent();
	this->states.top()->update();
}

void Engine::render()
{
	this->states.top()->render();
}

void Engine::run()
{
	//Main game loop
	while (!this->states.empty()) {
		this->update();
		this->render();
	}
}

//LUA FUNCTIONS
int Engine::luaTest(lua_State* L)
{
	lua_getglobal(L, LUA_ENGINE_ACCESSOR);
	Engine* engine = static_cast<Engine*>(lua_touserdata(L, -1));

	std::cout << "HELLO FROM CPP" << engine->test << '\n';
	return 0;
}

int Engine::cpp_createWindow(lua_State* L)
{
	lua_getglobal(L, LUA_ENGINE_ACCESSOR);
	Engine* engine = static_cast<Engine*>(lua_touserdata(L, -1));

	const std::string title = lua_tostring(L, 1);
	const unsigned win_x = lua_tonumber(L, 2);
	const unsigned win_y = lua_tonumber(L, 3);
	const unsigned win_w = lua_tonumber(L, 4);
	const unsigned win_h = lua_tonumber(L, 5);

	engine->window = SDL_CreateWindow(title.c_str(), win_x, win_y, win_w, win_h, 0);

	return 0;
}
