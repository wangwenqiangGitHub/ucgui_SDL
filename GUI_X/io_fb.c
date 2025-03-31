#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/mman.h>
#include <linux/fb.h>

#if defined(USE_SDL)
#include <SDL.h>

static SDL_Surface *screen = NULL;
#endif

int fb_getkey(void)
{
#if defined(USE_SDL)
    SDL_Event event = { 0 };

    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            return event.key.keysym.sym;
        }
    }
#endif

    return 0;
}

int fb_init(void)
{
#if defined(USE_SDL)
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE);
#endif

    return 0;
}

void fb_deinit(void)
{
#if defined(USE_SDL)
    SDL_Quit();
#endif
}

void fb_flip(void)
{
#if defined(USE_SDL)
    SDL_Flip(screen);
#endif
}

int fb_setpixel(int width, int height, int x, int y, unsigned short color)
{
    if ((x > width) || (y > height)) {
        return -1;
    }

#if defined(USE_SDL)
    unsigned short *dst = ((unsigned short *)screen->pixels + y * width + x);
    *dst = color;
#endif

    return 0;
}

unsigned short fb_readpixel(int width, int height, int x, int y)
{
    if ((x > width) || (y > height)) {
        return -1;
    }

#if defined(USE_SDL)
    unsigned short *dst = ((unsigned short *)screen->pixels + y * width + x);
    return *dst;
#endif

    return 0;
}

