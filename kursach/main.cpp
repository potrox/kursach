#include <iostream>
#include <vector>
#include <conio.h>
#include <SDL.h>
#include <WINDOWS.h>

using namespace std;

const int Width = GetSystemMetrics(SM_CXSCREEN);
const int Height = GetSystemMetrics(SM_CYSCREEN); 


SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

SDL_Renderer* ren = NULL;
SDL_Texture* close = NULL;
SDL_Texture* map1 = NULL;
SDL_Texture* map2 = NULL;
SDL_Texture* red = NULL;
SDL_Texture* green = NULL;
SDL_Texture* blue = NULL;
SDL_Texture* yellow = NULL;

int init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Could not init SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Game of Memory", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        Width, Height,
        SDL_WINDOW_ALLOW_HIGHDPI);

    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    surface = SDL_GetWindowSurface(window);

    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);



    return 0;
}

int load()
{
    SDL_Surface* temp_surface = NULL;

    temp_surface = SDL_LoadBMP("./Texture/exit.bmp");
    close = SDL_CreateTextureFromSurface(ren, temp_surface);

    if (close == NULL) {
        return 1;
    }

    temp_surface = SDL_LoadBMP("./Texture/f1.bmp");
    map1 = SDL_CreateTextureFromSurface(ren, temp_surface);

    if (map1 == NULL) {
        return 1;
    }

    temp_surface = SDL_LoadBMP("./Texture/f2.bmp");
    map2 = SDL_CreateTextureFromSurface(ren, temp_surface);

    if (map2 == NULL) {
        return 1;
    }

    temp_surface = SDL_LoadBMP("./Texture/red.bmp");
    red = SDL_CreateTextureFromSurface(ren, temp_surface);

    if (red == NULL) {
        return 1;
    }

    temp_surface = SDL_LoadBMP("./Texture/green.bmp");
    green = SDL_CreateTextureFromSurface(ren, temp_surface);

    if (green == NULL) {
        return 1;
    }

    temp_surface = SDL_LoadBMP("./Texture/blue.bmp");
    blue = SDL_CreateTextureFromSurface(ren, temp_surface);

    if (blue == NULL) {
        return 1;
    }

    temp_surface = SDL_LoadBMP("./Texture/yellow.bmp");
    yellow = SDL_CreateTextureFromSurface(ren, temp_surface);

    if (yellow == NULL) {
        return 1;
    }

    return 0;
}

void draw()
{
    srand(time(NULL));
    SDL_Rect coord{};
    coord.x = 0;
    coord.y = 0;
    coord.w = Width;
    coord.h = Width;
    SDL_RenderCopy(ren, map2, NULL, &coord);
    coord.x = Width/5;
    coord.y = Height/1.2;
    coord.w = 64;
    coord.h = 64;
    SDL_RenderCopy(ren, red, NULL, &coord);
    coord.x = Width / 2.5;
    coord.y = Height / 1.2;
    coord.w = 64;
    coord.h = 64;
    SDL_RenderCopy(ren, green, NULL, &coord);
    coord.x = Width / 1.67;
    coord.y = Height / 1.2;
    coord.w = 64;
    coord.h = 64;
    SDL_RenderCopy(ren, blue, NULL, &coord);
    coord.x = Width / 1.25;
    coord.y = Height / 1.2;
    coord.w = 64;
    coord.h = 64;
    SDL_RenderCopy(ren, yellow, NULL, &coord);
    coord.x = Width - 128;
    coord.y = Height / 10;
    coord.w = 64;
    coord.h = 64;
    SDL_RenderCopy(ren, close, NULL, &coord);
}

void quit() {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(ren);
    ren = NULL;

    SDL_DestroyTexture(red);
    red = NULL;

    SDL_Quit();
}

void status(bool& console_status)
{
    if (console_status == false)
    {
        console_status = true;
    }
    else
    {
        console_status = false;
    }

    ShowWindow(GetConsoleWindow(), console_status);
}


int main(int argc, char* argv[])
{
    SDL_Rect coord{};
    coord.x = (Width - 256) / 2;
    coord.y = (Height - 256) / 2;
    coord.w = 256;
    coord.h = 256;
    vector <int> color;
    vector <int> color_check(100);
    srand(time(NULL));
    int g = 1, x, y, i, j, flag = 1, t = 0;
    bool console_status = false, exit = false;
    ShowWindow(GetConsoleWindow(), console_status);

    color.push_back(0);
    for (int z = 0; z < color_check.size(); z++)
    {
        color_check[z] = 0;
    }

    init();
    load();

    SDL_Event windowEvent;

    i = 0;
    SDL_RenderClear(ren);
    SDL_RenderPresent(ren);

    while (!exit)
    {
        while (SDL_PollEvent(&windowEvent))
        {
            draw();
            switch (windowEvent.type)
            {
            case SDL_QUIT:
            {
                exit = true;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                if (windowEvent.button.button = SDL_BUTTON_LEFT)
                {
                    cout << "\n" << "x = " << windowEvent.button.x << "\n" << "y = " << windowEvent.button.y;
                    x = windowEvent.button.x;
                    y = windowEvent.button.y;
                    if ((x >= Width - 128) and (x <= Width - 64) and y >= Height / 10 and (y <= Height / 10 + 64))
                    {
                        exit = true;
                    }
                    if ((x >= Width / 5 and y >= Height / 1.2) and ((x <= Width / 5 + 64) and (y <= Height / 1.2 + 64)))
                    {
                        if (color[i] == 0)
                        {
                            i++;
                            SDL_RenderCopy(ren, red, NULL, &coord);
                            SDL_RenderPresent(ren);
                            SDL_Delay(1000);
                            if (i == color.size())
                            {
                                color.push_back(rand() % 4);
                                i = 0;
                                flag = 1;
                                SDL_RenderClear(ren);
                                draw();
                                SDL_RenderPresent(ren);
                                SDL_Delay(2000);
                            }
                        }
                        else if (color[i] == 1 or color[i] == 2 or color[i] == 3)
                        {
                            exit = true;
                        }
                    }
                    if ((x >= Width / 2.5 and y >= Height / 1.2) and ((x <= Width / 2.5 + 64) and (y <= Height / 1.2 + 64)))
                    {
                        if (color[i] == 1)
                        {
                            i++;
                            SDL_RenderCopy(ren, green, NULL, &coord);
                            SDL_RenderPresent(ren);
                            SDL_Delay(1000);
                            if (i == color.size())
                            {
                                color.push_back(rand() % 4);
                                i = 0;
                                flag = 1;
                                SDL_RenderClear(ren);
                                draw();
                                SDL_RenderPresent(ren);
                                SDL_Delay(2000);
                            }
                        }
                        else if (color[i] == 0 or color[i] == 1 or color[i] == 3)
                        {
                            exit = true;
                        }
                    }
                    if ((x >= Width / 1.67 and y >= Height / 1.2) and ((x <= Width / 1.67 + 64) and (y <= Height / 1.2 + 64)))
                    {
                        if (color[i] == 2)
                        {
                            i++;
                            SDL_RenderCopy(ren, blue, NULL, &coord);
                            SDL_RenderPresent(ren);
                            SDL_Delay(1000);
                            if (i == color.size())
                            {
                                color.push_back(rand() % 4);
                                i = 0;
                                flag = 1;
                                SDL_RenderClear(ren);
                                draw();
                                SDL_RenderPresent(ren);
                                SDL_Delay(2000);
                            }
                        }
                        else if (color[i] == 0 or color[i] == 1 or color[i] == 3)
                        {
                            exit = true;
                        }
                    }
                    if ((x >= Width / 1.25 and y >= Height / 1.2) and ((x <= Width / 1.25 + 64) and (y <= Height / 1.2 + 64)))
                    {
                        if (color[i] == 3)
                        {
                            i++;
                            SDL_RenderCopy(ren, yellow, NULL, &coord);
                            SDL_RenderPresent(ren);
                            SDL_Delay(1000);
                            if (i == color.size())
                            {
                                color.push_back(rand() % 4);
                                i = 0;
                                flag = 1;
                                SDL_RenderClear(ren);
                                draw();
                                SDL_RenderPresent(ren);
                                SDL_Delay(2000);
                            }
                        }
                        else if (color[i] == 0 or color[i] == 1 or color[i] == 2)
                        {
                            exit = true;
                        }
                    }
                }
                break;
            }
            }
            if (flag == 1)
            {
                for (j = 0; j < color.size(); j++)
                {
                    if (color[j] == 0)
                    {
                        SDL_RenderCopy(ren, red, NULL, &coord);
                        SDL_RenderPresent(ren);
                        SDL_Delay(1000);
                    }
                    if (color[j] == 1)
                    {
                        SDL_RenderCopy(ren, green, NULL, &coord);
                        SDL_RenderPresent(ren);
                        SDL_Delay(1000);
                    }
                    if (color[j] == 2)
                    {
                        SDL_RenderCopy(ren, blue, NULL, &coord);
                        SDL_RenderPresent(ren);
                        SDL_Delay(1000);
                    }
                    if (color[j] == 3)
                    {
                        SDL_RenderCopy(ren, yellow, NULL, &coord);
                        SDL_RenderPresent(ren);
                        SDL_Delay(1000);
                    }
                    SDL_RenderClear(ren);
                    draw();
                    SDL_RenderPresent(ren);
                    t = time(NULL);
                }
            }
            flag = 0;
        }
    }

    quit();

    return 0;
}