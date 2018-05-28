#ifndef MODEL_H
#define MODEL_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Env_t Env;

/* **************************************************************** */

#ifdef __ANDROID__
#define PRINT(STR, ...) do { SDL_Log(STR, ##__VA_ARGS__);  } while(0)
#define ERROR(STR, ...) do { SDL_Log(STR, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)
#else
#define PRINT(STR, ...) do { printf(STR, ##__VA_ARGS__); } while(0)
#define ERROR(STR, ...) do { fprintf(stderr, STR, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)
#endif

/* **************************************************************** */

#define APP_NAME "Tarot Graphic"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480
#define DELAY 50

/* **************************************************************** */

Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]);

void render(SDL_Window* win, SDL_Renderer* ren, Env * env);
void render_new_game(SDL_Window* win, SDL_Renderer* ren, Env * env); 
void render_ask_num(SDL_Window* win, SDL_Renderer* ren, Env * env);
void render_ask_name(SDL_Window* win, SDL_Renderer* ren, Env * env);
void render_team(SDL_Window* win, SDL_Renderer* ren, Env * env);
void render_points(SDL_Window* win, SDL_Renderer* ren, Env * env);

bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);
bool process_new_game (SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);
bool process_ask_num (SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e); 
bool process_ask_name (SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);
bool process_team(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);
bool process_points(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e);

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env);

#endif