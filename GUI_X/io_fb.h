#include <sys/types.h>

#if defined(UIDBG)
#define SCREEN_W 640
#define SCREEN_H 480
#endif

int            fb_init(void);
void           fb_deinit(void);
int            fb_setpixel(int width, int height, int x, int y, unsigned short color);
unsigned short fb_readpixel(int width, int height, int x, int y);
void           fb_flip(void);
int            fb_getkey(void);
void*          fb_getbuffer(void);
