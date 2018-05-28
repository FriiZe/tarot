#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "TI.h"

int main(int argc, char * argv[]){
    /* initialize SDL2 and some extensions */
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        ERROR("Error: SDL_Init VIDEO (%s)", SDL_GetError());
    if(IMG_Init(IMG_INIT_PNG & IMG_INIT_PNG) != IMG_INIT_PNG)
        ERROR("Error: IMG_Init PNG (%s)", SDL_GetError());
    if(TTF_Init() != 0)
        ERROR("Error: TTF_Init (%s)", SDL_GetError());

    /* create window and renderer */
    SDL_Window * win = SDL_CreateWindow(
        APP_NAME,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if(!win)
        ERROR("Error: SDL_CreateWindow (%s)", SDL_GetError());
    SDL_Renderer * ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!ren)
        ERROR("Error: SDL_CreateRenderer (%s)", SDL_GetError());



    /* initialize your environment */
    Env * env = init(win, ren, argc, argv);
    /* main render loop */
    SDL_Event e;
    bool quit = false;


    while (!quit)
    {
        /* manage events */
        while (SDL_PollEvent(&e))
        {
        /* process events */
        quit = process(win, ren, env, &e);
        if(quit) break;
        }

        SDL_RenderClear(ren);
        render(win, ren, env);
        SDL_RenderPresent(ren);
        SDL_Delay(DELAY);
    }


    /* clean the environment */
    clean(win, ren, env);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}