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

#include <SDL.h>

static SDL_Surface *screen = NULL;

int fb_init(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE); 
    return 0;
}

void fb_deinit(void)
{
    SDL_Quit(); 
}

void fb_flip(void)
{
    SDL_Flip(screen);
}

int fb_setpixel(int width, int height, int x, int y, unsigned short color)
{
    if ((x > width) || (y > height)) {
        return -1;
    }

    unsigned short *dst = ((unsigned short *)screen->pixels + y * width + x);
    *dst = color;
    return 0;
}

unsigned short fb_readpixel(int width, int height, int x, int y)
{
    if ((x > width) || (y > height)) {
        return -1;
    }

    unsigned short *dst = ((unsigned short *)screen->pixels + y * width + x);
    return *dst;
}

