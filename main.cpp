#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "game.h"


int main ( int argc, char** argv )
{
    int i=0;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    TTF_Init();
    atexit(SDL_Quit);
    SDL_Surface *screen = SDL_SetVideoMode(850, 594, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption( "Барабашка", NULL );
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
    //установка цвета, который будет игнорироваться наложении поверхностей
    SDL_SetColorKey(screen, SDL_SRCCOLORKEY | SDL_RLEACCEL, 0xFFFFFF); 
    Game game;
    Text txt;
    txt.init();
    game.initialize(); //загрузка изображений, установка флагов в исходное положение, задание начальных 			    //координат
    game.load_res(); //чтение результатов из файла
    game.show_menu(screen); //переход к меню
    while(game.flag) //начало игрового цикла
    {
        game.load_rect();
        game.events();
        game.loop();
        if(game.ren)
        {
            game.render(screen, game.hero_of_barabashka.p);
            txt.draw(screen);
            SDL_Flip(screen);
        }
        if(!game.flag) //в случае проигрыша
        {
            game.EOG(screen);
        }
        if(game.menu) //если пользователь решил выйти в меню
            game.show_menu(screen);
    }
    game.save_res(); //запись лучших результатов в файл
    game.destruct(); //очистка загруженных поверхностей
    txt.destruct(); 
    SDL_Quit();
    TTF_Quit();
    printf("Exited cleanly\n");
    return 0;
}
