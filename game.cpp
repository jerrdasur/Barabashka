#include "game.h"
#include "time.h"
#include <SDL/SDL_draw.h>
#include <stdio.h>

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) //отображение поверхности
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void Game :: initialize()
{
    this->fnt = TTF_OpenFont("UbuntuMono-RI.ttf", 25);
    this->text_color.r=0;
    this->text_color.g=255;
    this->text_color.b=0;
    this->obj[0].name[0]="src/objects/1.png";//комната
    this->obj[0].name[1]="src/objects/1.png";
    this->obj[1].name[0]="src/objects/2.png";//дверь сверху
    this->obj[1].name[1]="src/objects/2.png";
    this->obj[2].name[0]="src/objects/3.png";//дверь сбоку
    this->obj[2].name[1]="src/objects/3.png";
    this->obj[3].name[0]="src/objects/4.png";//окно
    this->obj[3].name[1]="src/objects/4.png";
    this->obj[4].name[0]="src/objects/5_1.png";//тумба
    this->obj[4].name[1]="src/objects/5_2.png";
    this->obj[5].name[0]="src/objects/6_1.png";//стол
    this->obj[5].name[1]="src/objects/6_2.png";
    this->obj[6].name[0]="src/objects/7_1.png";//стул
    this->obj[6].name[1]="src/objects/7_2.png";
    this->obj[7].name[0]="src/objects/8_1.png";//маленькая тумба
    this->obj[7].name[1]="src/objects/8_2.png";
    this->obj[8].name[0]="src/objects/9_1.png";//холодос
    this->obj[8].name[1]="src/objects/9_2.png";
    for(int i=0;i<9;i++)
        this->obj[i].init();
    this->an[0].names[0]="src/objects/10_1.png"; //плитка
    this->an[0].names[1]="src/objects/10_2.png";
    this->an[0].names[2]="src/objects/10_3.png";
    this->an[0].names[3]="src/objects/10_4.png";
    this->an[0].names[4]="src/objects/10_5.png";
    this->an[1].names[0]="src/objects/11_1.png"; //раковина
    this->an[1].names[1]="src/objects/11_2.png";
    this->an[1].names[2]="src/objects/11_3.png";
    this->an[1].names[3]="src/objects/11_4.png";
    this->an[1].names[4]="src/objects/11_5.png";
    this->an[0].init();
    this->an[1].init();
    //Левый вариант отрисовки героя
    this->hero_of_barabashka.name[3]="src/hero/left/0.png";
    this->hero_of_barabashka.name[4]="src/hero/left/1.png";
    this->hero_of_barabashka.name[5]="src/hero/left/2.png";
    //Правый вариант отрисовки
    this->hero_of_barabashka.name[6]="src/hero/right/0.png";
    this->hero_of_barabashka.name[7]="src/hero/right/1.png";
    this->hero_of_barabashka.name[8]="src/hero/right/2.png";
    //Верхний вариант отрисовки
    this->hero_of_barabashka.name[9]="src/hero/top/0.png";
    this->hero_of_barabashka.name[10]="src/hero/top/1.png";
    this->hero_of_barabashka.name[11]="src/hero/top/2.png";
    //нижний вариант отрисовки
    this->hero_of_barabashka.name[0]="src/hero/bottom/0.png";
    this->hero_of_barabashka.name[1]="src/hero/bottom/1.png";
    this->hero_of_barabashka.name[2]="src/hero/bottom/2.png";
    this->hero_of_barabashka.init();
}

void Game::events()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type==SDL_QUIT)
    {
        this->flag=false;
    }
    if(event.type==SDL_KEYDOWN)
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                this->menu=true;
                return;

            case SDLK_SPACE:
                this->check();
                break;
        }
    if(SDL_GetTicks())
    {
        this->ren=true;
        Uint8 *keystates = SDL_GetKeyState( NULL );
        if(keystates[SDLK_UP])
        {
            this->hero_of_barabashka.pos=9;
            this->hero_of_barabashka.dest.y--;
            if(!this->check_collission())
                this->hero_of_barabashka.dest.y++;
            else
                this->hero_of_barabashka.flag=true;
        }
        else if(keystates[SDLK_LEFT])
        {
            this->hero_of_barabashka.pos=3;
            this->hero_of_barabashka.dest.x--;
            if(!this->check_collission())
                this->hero_of_barabashka.dest.x++;
            else
                this->hero_of_barabashka.flag=true;
        }
        else if(keystates[SDLK_RIGHT])
        {
            this->hero_of_barabashka.pos=6;
            this->hero_of_barabashka.dest.x++;
            if(!this->check_collission())
                this->hero_of_barabashka.dest.x--;
            else
                this->hero_of_barabashka.flag=true;
        }
        else if(keystates[SDLK_DOWN])
        {
            this->hero_of_barabashka.pos=0;
            this->hero_of_barabashka.dest.y++;
            if(!this->check_collission())
                this->hero_of_barabashka.dest.y--;
            else
                this->hero_of_barabashka.flag=true;
        }
        else
            this->hero_of_barabashka.flag=false;
    }
}

void Game::loop()
{
    char c;
    if(this->ren)
    {
        this->timer++;
        int stime;
        long ltime;
        ltime = time(NULL);
        stime = (unsigned) ltime/2;
        srand(stime);
        if(this->timer%n==0)
        {
            if(count1==10 && n>1)
                count1=0, n--;
            c=rand()%11;
            if(c<9)
                count1++, this->obj[c].flag=true;
            else if(c==9)
                count1++, this->an[0].flag=true;
            else
                count1++, this->an[1].flag=true;
        }
    }
    c=0;
    for(int i=1;i<9;i++)
    {
        c=1;
        if(this->obj[i].flag==false)
            {c=0; break;}
    }
    if(this->an[0].flag && this->an[1].flag)
        ;
    else
        c=0;
    if(c)
        {this->flag=false; change_res();}
}

void Game::load_res()
{
    FILE *fp;
    if(fp=fopen("results", "rb"))
    {
        for(int i=0; i<10;i++)
        {
            if(fread(this->m[i], sizeof(char), 11, fp))
                fread(&(this->t[i]), sizeof(int), 1, fp);
            else
            {
                memset(this->m[i], 0, 11);
                t[i]=0;
            }
        }
        fclose(fp);
    }
}

void Game::change_res()
{
    for(int i=0;i<10;i++)
    {
        if(timer>t[i])
        {
            for(int j=0;j<11;j++)
                m[i][j]=name[j];
            t[i]=timer;
            return;
        }
    }
}

void Game::show_res(SDL_Surface *screen)
{
    dest.x=0; dest.y=0;
    dest.w=850; dest.h=594;
    SDL_FillRect(screen, &dest, 0xFFFFFF);
    this->dest.x = 10; this->dest.y =10;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"10 лучших результатов:");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
    for(int i=0;i<10;i++)
    {
        if(t[i]==0) //если у нас нечего выводить, то и не выводим ничего
            break;
        dest.y+=30;
        memset(this->txtbuf,0,100);
        sprintf(this->txtbuf,"|%10s|%10d|", m[i], t[i]/10);
        text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
        if(text_surface)
        {
            SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
            SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
        }
    }
    SDL_Flip(screen);
    SDL_Event event;
    while(SDL_WaitEvent(&event))
        if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE)
            return;
}

void Game::save_res()
{
    FILE *fp;
    if(fp=fopen("results", "wb"))
    {
        for(int i=0;i<10;i++)
        {
            fwrite(m[i], sizeof(char), 11, fp);
            fwrite(&t[i], sizeof(int), 1, fp);
        }
        fclose(fp);
    }
}

void Game::render(SDL_Surface *screen, bool &p)
{
    this->ren=false;
    apply_surface(0,0,this->obj[0].img[0], screen);
    if(this->obj[1].flag)
        apply_surface(163, 50, this->obj[1].img[0], screen);
    if(this->obj[2].flag)
        apply_surface(531,161, this->obj[2].img[0], screen);
    if(this->obj[3].flag)
        apply_surface(56,166, this->obj[3].img[0],screen);
    if(this->obj[4].flag)
        apply_surface(324,84, this->obj[4].img[1],screen);
    else
        apply_surface(324,84, this->obj[4].img[0], screen);
    if(this->obj[5].flag)
        apply_surface(230,240, this->obj[5].img[1], screen);
    else
        apply_surface(230,240, this->obj[5].img[0], screen);
    if(this->obj[6].flag)
        apply_surface(170,270, this->obj[6].img[1], screen);
    else
        apply_surface(170,270, this->obj[6].img[0], screen);

    if(this->an[1].i>4)
        this->an[1].i=1;
    else if(this->timer%50==0)
        this->an[1].i++;
    if(this->an[1].flag)
        apply_surface(532,270, this->an[1].img[this->an[1].i%5], screen);
    else
        apply_surface(532,270, this->an[1].img[0], screen);

    if(this->obj[7].flag)
        apply_surface(436,430, this->obj[7].img[1], screen);
    else
        apply_surface(436,430, this->obj[7].img[0], screen);

    if(this->an[0].i>4)
        this->an[0].i=1;
    else if(this->timer%50==0)
        this->an[0].i++;
    if(this->an[0].flag)
        apply_surface(280,441, this->an[0].img[this->an[0].i%5], screen);
    else
        apply_surface(280,441, this->an[0].img[0],screen);

    if(this->obj[8].flag)
        apply_surface(208,377, this->obj[8].img[1],screen);
    else
        apply_surface(208,421, this->obj[8].img[0],screen);

    if(this->timer%50==0)
        p=!p;
    if(this->hero_of_barabashka.pos==9) //движение вверх
    {
        if(this->hero_of_barabashka.flag && p)
           apply_surface(this->hero_of_barabashka.dest.x,
                         this->hero_of_barabashka.dest.y,
                         this->hero_of_barabashka.img_t[1],
                         screen);
        else if(this->hero_of_barabashka.flag)
           apply_surface(this->hero_of_barabashka.dest.x,
                         this->hero_of_barabashka.dest.y,
                         this->hero_of_barabashka.img_t[2],
                         screen);
        else
            apply_surface(this->hero_of_barabashka.dest.x,
                          this->hero_of_barabashka.dest.y,
                          this->hero_of_barabashka.img_t[0],
                          screen);
    }
    if(this->hero_of_barabashka.pos==3) //движение влево
    {
        if(this->hero_of_barabashka.flag && p)
           apply_surface(this->hero_of_barabashka.dest.x,
                          this->hero_of_barabashka.dest.y,
                          this->hero_of_barabashka.img_l[1],
                          screen);
        else if(this->hero_of_barabashka.flag)
           apply_surface(this->hero_of_barabashka.dest.x,
                         this->hero_of_barabashka.dest.y,
                         this->hero_of_barabashka.img_l[2],
                         screen);
        else
            apply_surface(this->hero_of_barabashka.dest.x,
                          this->hero_of_barabashka.dest.y,
                          this->hero_of_barabashka.img_l[0],
                          screen);
    }
    if(this->hero_of_barabashka.pos==6) //движение направо
    {
        if(this->hero_of_barabashka.flag && p)
            apply_surface(this->hero_of_barabashka.dest.x,
                          this->hero_of_barabashka.dest.y,
                          this->hero_of_barabashka.img_r[1],
                          screen);
        else if(this->hero_of_barabashka.flag)
           apply_surface(this->hero_of_barabashka.dest.x,
                         this->hero_of_barabashka.dest.y,
                         this->hero_of_barabashka.img_r[2],
                         screen);
        else
            apply_surface(this->hero_of_barabashka.dest.x,
                          this->hero_of_barabashka.dest.y,
                          this->hero_of_barabashka.img_r[0],
                          screen);
    }
    if(this->hero_of_barabashka.pos==0) //движение вниз
    {
        if(this->hero_of_barabashka.flag && p)
            apply_surface(this->hero_of_barabashka.dest.x,
                          this->hero_of_barabashka.dest.y,
                          this->hero_of_barabashka.img_b[1],
                          screen);
        else if(this->hero_of_barabashka.flag)
           apply_surface(this->hero_of_barabashka.dest.x,
                         this->hero_of_barabashka.dest.y,
                         this->hero_of_barabashka.img_b[2],
                         screen);
        else
            apply_surface(this->hero_of_barabashka.dest.x,
                          this->hero_of_barabashka.dest.y,
                          this->hero_of_barabashka.img_b[0],
                          screen);
    }
    this->dest.x = 10; this->dest.y =10;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"Время: %d", this->timer/100);
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
}

bool Game::check_collission()
{
    int leftA, leftB, rightA, rightB, topA, topB, botA, botB;
    leftA=this->hero_of_barabashka.dest.x;
    rightA=leftA+this->hero_of_barabashka.dest.w;
    topA=this->hero_of_barabashka.dest.y;
    botA=topA+this->hero_of_barabashka.dest.h;
    for(int i=0;i<11;i++)
    {
        leftB=this->mas[i].x;  rightB=leftB+this->mas[i].w;
        topB=this->mas[i].y;  botB=topB+this->mas[i].h;
        if(botA>=topB && botA<=botB)
            if(leftA>=leftB && leftA<=rightB || rightA<=rightB && rightA>=leftB) //если у нас хотя бы один из нижних
                return false;
        if(topA>=topB && topA<=botB)
            if(leftA>=leftB && leftA<=rightB || rightA<=rightB && rightA>=leftB)//или верхних углов героя пересекает
                return false;							 //границу объекта
    }
    if(this->hero_of_barabashka.dest.x<70)//пересечение стенок комнаты
        return false;
    else if(this->hero_of_barabashka.dest.y<80)
        return false;
    else if(this->hero_of_barabashka.dest.x+this->hero_of_barabashka.dest.w>590)
        return false;
    else if(this->hero_of_barabashka.dest.y+this->hero_of_barabashka.dest.h>520)
        return false;
    else
        return true;
}

void Game::load_rect()
{
    if(this->obj[1].flag) //т.к. при отрисовке объекты в разном положении могут иметь разные координаты и 			       //размеры проверяем его положение
    {
        this->mas[0].x=163;  this->mas[0].y=50;
        this->mas[0].h=this->obj[1].img[0]->h;  this->mas[0].w=this->obj[1].img[0]->w;
    }
    else
    {
        this->mas[0].x=0;  this->mas[0].y=0;
        this->mas[0].h=0;  this->mas[0].w=0;
    }

    if(this->obj[2].flag)
    {
        this->mas[1].x=531;  this->mas[1].y=161;
        this->mas[1].h=this->obj[2].img[0]->h;  this->mas[1].w=this->obj[2].img[0]->w;
    }
    else
    {
        this->mas[1].x=0;  this->mas[1].y=0;
        this->mas[1].h=0;  this->mas[1].w=0;
    }

    if(this->obj[3].flag)
    {
        this->mas[2].x=56;  this->mas[2].y=166;
        this->mas[2].h=this->obj[3].img[0]->h;  this->mas[2].w=this->obj[3].img[0]->w;
    }
    else
    {
        this->mas[2].x=0;  this->mas[2].y=0;
        this->mas[2].h=0;  this->mas[2].w=0;
    }

    this->mas[3].x=324;  this->mas[3].y=84;
    if(this->obj[4].flag)
        this->mas[3].h=this->obj[4].img[1]->h;
    else
        this->mas[3].h=this->obj[4].img[0]->h;
    this->mas[3].w=this->obj[4].img[0]->w;

    this->mas[4].x=230;  this->mas[4].y=240;
    this->mas[4].h=this->obj[5].img[0]->h; this->mas[4].w=this->obj[5].img[0]->w;

    this->mas[5].x=170;  this->mas[5].y=270;
    this->mas[5].h=this->obj[6].img[0]->h;  this->mas[5].w=this->obj[6].img[0]->w;

    this->mas[6].x=436;  this->mas[6].y=430;
    this->mas[6].h=this->obj[7].img[0]->h;  this->mas[6].w=this->obj[7].img[0]->w;

    this->mas[7].x=208;
    if(this->obj[8].flag)
    {
        this->mas[7].y=421;
        this->mas[7].h=this->obj[8].img[1]->h;
    }
    else
    {
        this->mas[7].y=377;
        this->mas[7].h=this->obj[8].img[0]->h;
    }
    this->mas[7].w=this->obj[8].img[0]->w;

    this->mas[8].x=280;  this->mas[8].y=441;
    this->mas[8].h=this->an[0].img[0]->h;  this->mas[8].w=this->an[0].img[0]->w;

    this->mas[9].x=532;  this->mas[9].y=270;
    this->mas[9].h=this->an[1].img[0]->h;  this->mas[9].w=this->an[1].img[0]->w;
}

void Game::check()
{
    int i=this->space(); //если мы рядом с каким-то перевёрнутым объектом
		      //то возвращаем его в исходное положение
    if(i>-1)
        this->ren=true;
    if(i<8 && i>-1)
        this->obj[i+1].flag=false;
    else if(i==8)
        this->an[0].flag=false;
    else if(i==9)
        this->an[1].flag=false;
}

int Game::space()
{
    int leftA, leftB, rightA, rightB, topA, topB, botA, botB;
    leftA=this->hero_of_barabashka.dest.x;
    rightA=leftA+this->hero_of_barabashka.dest.w;
    topA=this->hero_of_barabashka.dest.y;
    botA=topA+this->hero_of_barabashka.dest.h;
    for(int i=0;i<10;i++)
    {
        leftB=this->mas[i].x-15;  rightB=leftB+this->mas[i].w+30; 
        topB=this->mas[i].y-15;  botB=topB+this->mas[i].h+30;	 
        if(botA>=topB && botA<=botB && this->obj[i+1].flag)
        {
            if(leftA>=leftB && leftA<=rightB || rightA<=rightB && rightA>=leftB)//аналог check_collission()
                return i;
        }
        else if(topA>=topB && topA<=botB && this->obj[i+1].flag)
        {
            if(leftA>=leftB && leftA<=rightB || rightA<=rightB && rightA>=leftB)
                return i;
        }
       
    }
    return -1;
}

void Game::EOG(SDL_Surface *screen)
{
    apply_surface(0, 0, this->obj[0].img[0], screen);
    this->dest.x = 240; this->dest.y =220;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"Игра окончена!");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
    this->dest.x=150; this->dest.y=this->dest.y+30;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"Для выхода нажмите 'Пробел'");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
    SDL_Flip(screen);

    bool flag=true;
    SDL_Event event;
    while(flag)
    {
        SDL_WaitEvent(&event);
        if(event.type== SDL_KEYDOWN)
            if(event.key.keysym.sym== SDLK_SPACE)
            {
                flag=false;
                this->flag=false;
                menu=true;
            }
    }

}

void Text::init()
{
    this->fnt = TTF_OpenFont("UbuntuMono-RI.ttf", 15);
    this->text_color.r=100;
    this->text_color.g=255;
    this->text_color.b=100;
}

void Text::draw(SDL_Surface *screen) //отрисовка необходимой вспомогательной информации
				      //для игрового цикла
{
    this->dest.x = 630; this->dest.y =10;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"Движение осуществляется");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
    this->dest.y =this->dest.y+20;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"с помощью стрелочек");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
    this->dest.y =this->dest.y+20;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"Для закрытия объекта или");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
    this->dest.y =this->dest.y+20;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"возврата его в исходное");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
    this->dest.y =this->dest.y+20;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"состояние. Нажмите 'Пробел'.");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
}

void Game::show_menu(SDL_Surface *screen)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load("src/objects/menu.jpg");
    if(!player)
        input_name(screen);
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF );
        SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey);
        SDL_FreeSurface( loadedImage );
    }
    SDL_Event event;
    char i=0;
    while(SDL_WaitEvent(&event))
    {
        apply_surface(0,0, optimizedImage, screen);
        dest.x=100; dest.y=80;
        dest.w=300; dest.h=30;
        memset(this->txtbuf,0,100);
        sprintf(this->txtbuf,"Новая игра");
        if(i==0)
            SDL_FillRect(screen, &dest, 0x0000FF);
        else
            SDL_FillRect(screen, &dest, 0xFFFFFF);
        text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
        if(text_surface)
        {
            SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
            SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
        }
        if(timer/1000)//значение таймера дано в тиках, проверяем на секунды для определения
		 //ведётся ли у нас игра или есть ли сохранения
        {
            dest.y+=60;
            dest.w=300; dest.h=30;
            memset(this->txtbuf,0,100);
            sprintf(this->txtbuf,"Продолжить игру");
            if(i==1)
                SDL_FillRect(screen, &dest, 0x0000FF);
            else
                SDL_FillRect(screen, &dest, 0xFFFFFF);
            text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
            if(text_surface)
            {
                SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
                SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
            }
            dest.y+=60;
            dest.w=300; dest.h=30;
            memset(this->txtbuf,0,100);
            sprintf(this->txtbuf,"Сохранить игру");
            if(i==2)
                SDL_FillRect(screen, &dest, 0x0000FF);
            else
                SDL_FillRect(screen, &dest, 0xFFFFFF);
            text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
            if(text_surface)
            {
                SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
                SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
            }
        }
        dest.y+=60;
        dest.w=300; dest.h=30;
        memset(this->txtbuf,0,100);
        sprintf(this->txtbuf,"Правила игры");
        if(i==3)
            SDL_FillRect(screen, &dest, 0x0000FF);
        else
            SDL_FillRect(screen, &dest, 0xFFFFFF);
        text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
        if(text_surface)
        {
            SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
            SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
        }
        dest.y+=60;
        dest.w=300; dest.h=30;
        memset(this->txtbuf,0,100);
        sprintf(this->txtbuf,"Смена игрока");
        if(i==4)
            SDL_FillRect(screen, &dest, 0x0000FF);
        else
            SDL_FillRect(screen, &dest, 0xFFFFFF);
        text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
        if(text_surface)
        {
            SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
            SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
        }
        dest.y+=60;
        dest.w=300; dest.h=30;
        memset(this->txtbuf,0,100);
        sprintf(this->txtbuf,"Результаты");
        if(i==5)
            SDL_FillRect(screen, &dest, 0x0000FF);
        else
            SDL_FillRect(screen, &dest, 0xFFFFFF);
        text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
        if(text_surface)
        {
            SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
            SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
        }
        dest.y+=60;
        dest.w=300; dest.h=30;
        memset(this->txtbuf,0,100);
        sprintf(this->txtbuf,"Выход");
        if(i==6)
            SDL_FillRect(screen, &dest, 0x0000FF);
        else
            SDL_FillRect(screen, &dest, 0xFFFFFF);
        text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
        if(text_surface)
        {
            SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
            SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
        }
        if(event.type==SDL_QUIT)
        {flag=false; return;}
        if(event.type==SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_DOWN:
                    if(i==0 && timer/10==0)
                        i+=2;
                    if(i<6)
                        i++;
                    else
                        i=0;
                    break;
                case SDLK_RETURN:
                    if(i==0)
                        {flag=true; this->start(); menu=false; return;}
                    else if(i==3)
                        show_help(screen);
                    else if(i==2)
                        {
                            apply_surface(0,0,optimizedImage,screen);
                            dest.x=100; dest.y=100;
                            text_surface = TTF_RenderUTF8_Solid(this->fnt, "Игра успешно сохранена!", this->text_color);
                            if(text_surface)
                            {
                                SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
                                SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
                            }
                            save_game();
                            SDL_Flip(screen);
                            SDL_Delay(2000);
                        }
                    else if(i==4)
                    {
                        input_name(screen);
                    }
                    else if(i==5)
                    {
                        show_res(screen);
                    }
                    else if(i==1)
                        {menu=false; return;}
                    else
                        {flag=false; return;}
                    break;
                case SDLK_UP:
                    if(i==3 && timer/10==0)
                        i-=2;
                    if(i>0)
                        i--;
                    else
                        i=6;
                    break;
            }
        }
        dest.x=10; dest.y=560;
        dest.w=300; dest.h=30;
        memset(this->txtbuf,0,100);
        sprintf(this->txtbuf,"Пензин Кирилл гр. И532");
        text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
        if(text_surface)
        {
            SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
            SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
        }
        SDL_Flip(screen);
    }
    SDL_FreeSurface(optimizedImage);
}

void Game::start()
{
    for(int i=0;i<9;i++)
        obj[i].flag=false;
    an[0].flag=false; an[0].i=0;
    an[1].flag=false; an[1].i=0;
    hero_of_barabashka.dest.x=400;
    hero_of_barabashka.dest.y=250;
    hero_of_barabashka.flag=false;
    hero_of_barabashka.p=false;
    hero_of_barabashka.pos=0;
    timer=0;
 }

void OutSymbolFntColorXY(SDL_Surface *screen, TTF_Font *fnt,
  SDL_Color clr, Sint16 x, Sint16 y, char symbolcode)
{ /* Такая реализация корректно работает только с символами,
    код которых в utf8 задается 1 байтом. То есть, только
    символами ASCII, имеющими код от 0 до 127. Этого достаточно
    для записи вещественных чисел. */
  SDL_Rect dest; dest.x = x; dest.y = y;
  char s[2]; s[0]=symbolcode; s[1]='\0';
  SDL_Surface *TextSurface = TTF_RenderUTF8_Solid(fnt, s, clr);
  SDL_BlitSurface(TextSurface, NULL, screen, &dest);
  SDL_FreeSurface(TextSurface); // Освобождаем поверхность
  /* Обновляем только измененный участок целевой поверхности:*/
  SDL_UpdateRect(screen,dest.x,dest.y,dest.w,dest.h);
}


  void  input_string(SDL_Surface *who_draw, TTF_Font *fnt,
  SDL_Color color, Sint16 x1, Sint16 y1,
  Sint16 x2, Sint16 y2, char *name)
{
  char s[11];
  /* Все символы в нем делаем нулевыми */
  memset(s,0,11);
  /* количество и положение различных символов в буфере */
  int _kol=-1;
  /* Координаты рабочей области */
  Sint16 wrk_x1=x1, x=wrk_x1, wrk_y1=y1, y=wrk_y1;
  SDL_Event event;
  SDL_EnableUNICODE(SDL_ENABLE);
  while ( SDL_WaitEvent(&event) )
  {
    if (event.type == SDL_KEYDOWN){ /*Если нажата клавиша...*/
      if(_kol<11)
      {/*При соблюдении условий смотрим, не буква ли нажата...*/
        if(event.key.keysym.unicode>= 'A' && event.key.keysym.unicode<='Z' ||
           event.key.keysym.unicode>= 'a' && event.key.keysym.unicode<='z')
        {
          char digitsym;
          digitsym=event.key.keysym.unicode;
          OutSymbolFntColorXY(who_draw, fnt, color, x,y, digitsym);
          x+=18; s[++_kol]=digitsym;
        }
      }
      if ((event.key.keysym.sym==SDLK_BACKSPACE)&&(x!=x1))
      {
        // Смещаемся на 30 пикселей влево (одно "знакоместо")
        x-=18;
        // Затираем знакоместо белым цветом
        Draw_FillRect(who_draw,x,y,18,30,0xFFFFFF);
        // Обновляем экран
        SDL_UpdateRect(who_draw,0,0, 850, 594);
        _kol=_kol-1; /* Уменьшаем число символов */
        continue; /*Продолжаем ожидание событий */
      }
      if (event.key.keysym.sym==SDLK_RETURN && _kol!=-1)
      { /* Завершение ввода */
        s[_kol+1]='\0';
        for(int i=0;i<11;i++)
            name[i]=s[i];
        SDL_EnableUNICODE(SDL_DISABLE);
        return;
      }
    } /* Конец обработки события SDL_KEYDOWN */
  } /* Конец цикла обработки событий */
  SDL_EnableUNICODE(SDL_DISABLE);
  return;
}

void Game::show_help(SDL_Surface *screen)
{
    dest.x=0; dest.y=0;
    dest.w=850; dest.h=594;
    SDL_FillRect(screen, &dest, 0xFFFFFF);
    this->dest.x = 10; this->dest.y =10;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"Движение осуществляется с помощью стрелочек");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
    this->dest.y+=35;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"Возврат объекта в исходное состояние по нажатию клавиши 'Пробел'");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
    this->dest.y+=35;
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"Игра заканчивается, когда все объекты открыты или перевёрнуты.");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
    SDL_Flip(screen);
    SDL_Event event;
    while(SDL_WaitEvent(&event))
    {
        if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE)
            return;
    }
}

void Game::destruct()
{
    TTF_CloseFont(this->fnt);
}

void Game::save_game()
{
    FILE *fp;
    if(fp=fopen(name, "w"))
    {
        for(int i=0;i<9;i++)
            fwrite(&(this->obj[i].flag), sizeof(bool),1,fp);
        fwrite(&(this->an[0].flag), sizeof(bool), 1, fp);
        fwrite(&(this->an[0].i), sizeof(char), 1, fp);
        fwrite(&(this->an[1].flag), sizeof(bool), 1, fp);
        fwrite(&(this->an[1].i), sizeof(char), 1, fp);
        fwrite(&(this->count1), sizeof(int), 1 , fp);
        fwrite(&(this->flag), sizeof(bool), 1, fp);
        fwrite(&(this->hero_of_barabashka.flag), sizeof(bool), 1, fp);
        fwrite(&(this->hero_of_barabashka.p), sizeof(bool), 1, fp);
        fwrite(&(this->hero_of_barabashka.pos), sizeof(char), 1, fp);
        fwrite(&(this->n), sizeof(int), 1, fp);
        fwrite(&(this->timer), sizeof(int), 1, fp);
        fclose(fp);
    }
}

void Game::load_game()
{
    FILE *fp;
    printf("1\n");
    if(fp=fopen(name, "r"))
    {
        for(int i=0;i<9;i++)
            fread(&(this->obj[i].flag), sizeof(bool),1,fp);
        fread(&(this->an[0].flag), sizeof(bool), 1, fp);
        fread(&(this->an[0].i), sizeof(char), 1, fp);
        fread(&(this->an[1].flag), sizeof(bool), 1, fp);
        fread(&(this->an[1].i), sizeof(char), 1, fp);
        fread(&(this->count1), sizeof(int), 1 , fp);
        fread(&(this->flag), sizeof(bool), 1, fp);
        fread(&(this->hero_of_barabashka.flag), sizeof(bool), 1, fp);
        fread(&(this->hero_of_barabashka.p), sizeof(bool), 1, fp);
        fread(&(this->hero_of_barabashka.pos), sizeof(char), 1, fp);
        fread(&(this->n), sizeof(int), 1, fp);
        fread(&(this->timer), sizeof(int), 1, fp);
        fclose(fp);
    }
    else
        start();
}

void Text::destruct()
{
    TTF_CloseFont(this->fnt);
}

void Game::input_name(SDL_Surface *screen)
{
    dest.x=0; dest.y=0;
    dest.w=screen->w; dest.h=screen->h;
    SDL_FillRect(screen, &dest, 0xFFFFFF);
    memset(this->txtbuf,0,100);
    sprintf(this->txtbuf,"Введите имя игрока:");
    text_surface = TTF_RenderUTF8_Solid(this->fnt, this->txtbuf, this->text_color);
    if(text_surface)
    {
        SDL_BlitSurface(this->text_surface, NULL, screen, &(this->dest));
        SDL_FreeSurface(this->text_surface); this->text_surface = NULL;
    }
    dest.y+=30;
    memset(name, 0, 10);
    SDL_Color color;
    color.b=0; color.g=0; color.r=0;
    SDL_Flip(screen);
    input_string(screen, fnt, color, dest.x, dest.y, dest.w, dest.h, name);
    load_game();
    player=true;
}
