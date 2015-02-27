#ifndef GAME_H
#define GAME_H
#include "images.h"

struct Game
{
        TTF_Font *fnt;
        /* Для вывода текстов */
        SDL_Color text_color;
        SDL_Rect dest;
        SDL_Surface *text_surface = NULL;
        char txtbuf[100];

        void destruct();
        bool flag=false; //идёт ли у нас игра?
        bool ren=true; //А таки ви действительно хотите  шо-то отрисовать?
        bool menu=true; //выход в меню
        bool player=false; //было ли введено имя игрока
        int timer=0, n=10, count1=0; //таймер, коэффициент времени открытия барабашкой объектов
			            //счётчик открытых элементов
        void initialize();
        void start(); //установка параметров в исходное положение
        void save_game(); 
        void load_game();
        void save_res();
        void load_res();
        void change_res();
        void show_menu(SDL_Surface *screen);
        void input_name(SDL_Surface *screen);
        void show_help(SDL_Surface *screen);
        void show_res(SDL_Surface *screen);
        void events(); //обработка событий
        void loop(); //изменение параметров игрового цикла
        void load_rect(); //загрузка координат всех объектов
        int space();  //проверка при нажатии «Пробела». А есть ли у нас рядом перевёрнутый объект?
        void check();
        void render(SDL_Surface *screen, bool &p);
        void EOG(SDL_Surface *screen);
        bool check_collission(); //проверка на столкновение с объектом
        char m[10][11]; //хранение имён 10 лучших игроков
        int t[10]; //их время
        Objects obj[9];
        SDL_Rect mas[10]; //координаты всех игровых объектов
        Anim an[2];
        char name[10];
        hero hero_of_barabashka;
};

struct Text
{
    TTF_Font *fnt;
    /* Для вывода текстов */
    SDL_Color text_color;
    SDL_Rect dest;
    SDL_Surface *text_surface = NULL;
    char txtbuf[100];

    void init();
    void draw(SDL_Surface *screen);
    void destruct();
};

#endif // GAME_H
