#include "images.h"
#include <SDL/SDL_draw.h>

Uint32 GetPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch(bpp) {
    case 1:
        return *p;
        break;
    case 2:
        return *(Uint16 *)p;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;
    case 4:
        return *(Uint32 *)p;
        break;
    default:
        return 0;
    }
}

SDL_Surface *load_image( std::string filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF );
        SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey);
        SDL_FreeSurface( loadedImage );
    }
    return optimizedImage;
}

void Anim::init()
{
    for(int i=0;i<5;i++)
        this->img[i]=load_image(this->names[i]);
}

Anim::~Anim()
{
    for(int i=0;i<5;i++)
        SDL_FreeSurface(this->img[i]);
}

void Objects::init()
{
    this->img[0]=load_image(this->name[0]);
    this->img[1]=load_image(this->name[1]);
}

Objects::~Objects()
{
    for(int i=0;i<2;i++)
        SDL_FreeSurface(this->img[i]);
}

void hero::init()
{
    for(int i=0;i<12;i++)
    {
        if(i<3)
        {
            this->img_b[i]=load_image(this->name[i]);
        }
        else if(i<6)
        {
            this->img_l[i-3]=load_image(this->name[i]);
        }
        else if(i<9)
        {
            this->img_r[i-6]=load_image(this->name[i]);
        }
        else
        {
            this->img_t[i-9]=load_image(this->name[i]);
        }
    }
    this->dest.x=400;
    this->dest.y=250;
    this->dest.w=this->img_b[0]->w;
    this->dest.h=this->img_b[0]->h;
}

hero::~hero()
{
    for(int i=0;i<12;i++)
    {
        if(i<3)
        {
            SDL_FreeSurface(this->img_b[i]);
        }
        else if(i<6)
        {
            SDL_FreeSurface(this->img_l[i-3]);
        }
        else if(i<9)
        {
            SDL_FreeSurface(this->img_r[i-6]);
        }
        else
        {
            SDL_FreeSurface(this->img_t[i-9]);
        }
    }
}
