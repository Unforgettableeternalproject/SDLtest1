#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#define HEIGHT 600
#define WIDTH 600

int main(int argc, char* argv[])
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    luaL_loadfile(L, "hello.lua");
    if (lua_pcall(L, 0, 0, 0)) {
        cout << lua_tostring(L, -1) << endl;
    }


    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        HEIGHT, WIDTH, 0);

    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

    // creates a surface to load an image into the main memory
    SDL_Surface* surface;

    // please provide a path for your image
    surface = IMG_Load("imgs/rika.jpg");

    // loads image to our graphics hardware memory.
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

    // clears main-memory
    SDL_FreeSurface(surface);

    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;

    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box.
    dest.w /= 6;
    dest.h /= 6;

    // sets initial x-position of object
    dest.x = (HEIGHT - dest.w) / 2;

    // sets initial y-position of object
    dest.y = (WIDTH - dest.h) / 2;

    // controls animation loop
    int close = 0;

    int vx = 30, vy = 30;


    // animation loop
    while (!close) {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;

            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_Q:
                    close = 1;
                    break;

                default:
                    break;
                }
            }
        }

        // right boundary
        if (dest.x + dest.w > WIDTH)
        {
            dest.x = WIDTH - dest.w;
            vx = -vx;
        }
            

        // left boundary
        if (dest.x < 0)
        {
            dest.x = 0;
            vx = -vx;
        }

        // bottom boundary
        if (dest.y + dest.h > HEIGHT)
        {
            dest.y = HEIGHT - dest.h;
            vy = -vy;
        }

        // upper boundary
        if (dest.y < 0)
        {
            dest.y = 0;
            vy = -vy;
        }

        dest.x += vx;
        dest.y += vy;

        // clears the screen
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, tex, NULL, &dest);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    // destroy texture
    SDL_DestroyTexture(tex);

    // destroy renderer
    SDL_DestroyRenderer(rend);

    // destroy window
    SDL_DestroyWindow(win);

    // close SDL
    SDL_Quit();

    return 0;
}