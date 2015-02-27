#ifndef IMAGES_H
#define IMAGES_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <string>

using namespace std;

class images
{
    public:
        bool flag=false;
};

class Anim: public images
{
    public:
        string names[5];
        unsigned char i;
        void init();
        ~Anim();
        SDL_Surface *img[5];
};

class Objects: public images
{
    public:
        string name[2];
        void init();
        ~Objects();
        SDL_Surface *img[2];
};

class hero: public images
{
    public:
        bool p=false;
        SDL_Rect dest;
        char pos=0;
        string name[12];
        void init();
        ~hero();
        SDL_Surface *img_l[3];
        SDL_Surface *img_r[3];
        SDL_Surface *img_t[3];
        SDL_Surface *img_b[3];
};
#endif // IMAGES_H
