#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


//-----------------------------< LƯU Ý >-------------------------------
// 1 là tường
// 0 là đường đi có điểm
// 2 là đường đi trống
// 3 red ghost
//---------------------------------------------------------------------

//khởi tạo cửa sổ
const int step = 3;
const int TILE_SIZE = 23;
const int MAP_WIDTH = 25;
const int MAP_HEIGHT = 25;
const int SCREEN_WIDTH = TILE_SIZE* MAP_WIDTH + 100 ;
const int SCREEN_HEIGHT = TILE_SIZE* MAP_HEIGHT;
const std::string Font = "ArialCE.ttf";
const int fontSize = 20;
const int symbolRed = 1;
const int symbolBlue = 2;
const int symbolPink = 3;
const int symbolGreen = 4;


/* ----------------------------<MA TRẬN QR>--------------------------------------
{1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0},
{0, 0, 1, 1, 1, 0, 0, 0,0 , 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0},
{1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0},
{0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
{0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0},
{0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
{1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
{0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0},
{1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1},
{0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
{1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0},
{1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0},
{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0},
{1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0},
{1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0},
{1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0,0 , 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1},
*/

//-----------------------<HÀM LẤY MA TRẬN TỪ FILE.TXT>----------------------------------------

void readMatrix(const std::string& filename, int a[][MAP_WIDTH], int numRows, int numCols) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cout << "Failed to open file." << std::endl;
        return;
    }

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            infile >> a[i][j];
        }
    }
    infile.close();
}
//-------------------------------------------------------------------------------------

bool move_left(int size_pixel, int x, int y,int w, int step, int boolen[MAP_HEIGHT][MAP_WIDTH]) {
    // Kiểm tra tất cả các ô bên trái của nhân vật main
    for (int i = y; i <= (y+w); i++) {
        if (boolen[i/size_pixel][(x - step)/size_pixel] == 1) {
            return false;
        }
    }
    return true;
}

bool move_right(int size_pixel, int x, int y,int h, int step, int boolen[MAP_HEIGHT][MAP_WIDTH]) {
    // Kiểm tra tất cả các ô bên phai của nhân vật main
    for (int i = y; i <= (y+h); i++) {
        if (boolen[i/size_pixel][(x + h+ step)/size_pixel] == 1) {
            return false;
        }
    }
    return true;
}

bool move_up(int size_pixel, int x, int y,int h, int step, int boolen[MAP_HEIGHT][MAP_WIDTH]) {
    // Kiểm tra tất cả các ô bên tren của nhân vật main
    for (int i = x; i <= (x+h); i++) {
        if (boolen[(y-step)/size_pixel ][(i)/size_pixel] == 1) {
            return false;
        }
    }
    return true;
}

bool move_down(int size_pixel, int x, int y,int h,int w, int step, int boolen[MAP_HEIGHT][MAP_WIDTH]) {
    // Kiểm tra tất cả các ô bên duoi của nhân vật main
    for (int i = x ; i <= x + h ; i++) {
        if (boolen[(y + w + step)/size_pixel][(i)/size_pixel] == 1) {
            return false;
        }
    }
    return true;
}

void pointed(int boolen[MAP_HEIGHT][MAP_WIDTH] ,int x ,int y, int &score) {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            if (boolen[j][i] == 0) { // Nếu là điểm point
                int pointPosX = i * 23; // Tính tọa độ pixel x của điểm
                int pointPosY = j * 23; // Tính tọa độ pixel y của điểm
                int pointCenterX = pointPosX + 23 / 2; // Tính tâm của điểm theo trục x
                int pointCenterY = pointPosY + 23 / 2; // Tính tâm của điểm theo trục y

                // Kiểm tra va chạm giữa nhân vật main và điểm point
                if (x < pointCenterX + 11 && x + 17 > pointCenterX - 11 &&
                   y < pointCenterY + 11 &&  y + 17 > pointCenterY - 11) {
                    // Nếu tâm của điểm point nằm bên trong ảnh main thì in ảnh pointed.png thay vì ảnh point.png
                    if (x + 8 > pointPosX && x + 8 < pointPosX + 23 &&
                        y + 8 > pointPosY && y + 8 < pointPosY + 23) {
                        score++;
                        boolen[j][i] = 2 ;
                    }
                }
            }
        }
    }
}

bool die(int boolen[MAP_HEIGHT][MAP_WIDTH] ,int x ,int y) {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            if (boolen[j][i] == 3 ||boolen[j][i] == 4 || boolen[j][i] == 5 || boolen[j][i] == 6 ) { // Nếu là điểm point
                int pointPosX = i * 23; // Tính tọa độ pixel x của điểm
                int pointPosY = j * 23; // Tính tọa độ pixel y của điểm
                int pointCenterX = pointPosX + 23 / 2; // Tính tâm của điểm theo trục x
                int pointCenterY = pointPosY + 23 / 2; // Tính tâm của điểm theo trục y
                // Kiểm tra va chạm giữa nhân vật main và điểm point
                if (x < pointCenterX + 11 && x + 17 > pointCenterX - 11 &&
                   y < pointCenterY + 11 &&  y + 17 > pointCenterY - 11) {
                    // Nếu tâm của điểm point nằm bên trong ảnh main thì in ảnh pointed.png thay vì ảnh point.png
                    if (x + 8 > pointPosX && x + 8 < pointPosX + 23 &&
                        y + 8 > pointPosY && y + 8 < pointPosY + 23) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void enemyRedMove(int boolen[MAP_HEIGHT][MAP_WIDTH], int symbol){
    int r = 0;
    int c = 0;
    int a, b;
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            if (boolen[j][i] == 3) {
                r = j;
                c = i;
            }
        }
    }
    do {
        a = r - symbol + rand() % (2* symbol + 1);
        b = c - symbol + rand() % (2* symbol + 1);
    } while ( a < 0 || a >= MAP_HEIGHT || b < 0 || b >= MAP_WIDTH || (a == r && b == c) || boolen[a][b] == 1 || boolen[a][b] == 4 || boolen[a][b] == 5 ||boolen[a][b] == 6 );
    boolen[r][c] = 0;
    boolen[a][b] = 3;
}

void enemyBlueMove(int boolen[MAP_HEIGHT][MAP_WIDTH], int symbol){
    int r = 0;
    int c = 0;
    int a, b;
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            if (boolen[j][i] == 4) {
                r = j;
                c = i;
            }
        }
    }
    do {
        a = r - symbol + rand() % (2* symbol + 1);
        b = c - symbol + rand() % (2* symbol + 1);
    } while ( a < 0 || a >= MAP_HEIGHT || b < 0 || b >= MAP_WIDTH || (a == r && b == c) || boolen[a][b] == 1|| boolen[a][b] == 3 || boolen[a][b] == 5 ||boolen[a][b] == 6 );
    boolen[r][c] = 0;
    boolen[a][b] = 4;
}

void enemyPinkMove(int boolen[MAP_HEIGHT][MAP_WIDTH], int symbol){
    int r = 0;
    int c = 0;
    int a, b;
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            if (boolen[j][i] == 5) {
                r = j;
                c = i;
            }
        }
    }
    do {
        a = r - symbol + rand() % (2* symbol + 1);
        b = c - symbol + rand() % (2* symbol + 1);
    } while ( a < 0 || a >= MAP_HEIGHT || b < 0 || b >= MAP_WIDTH || (a == r && b == c) || boolen[a][b] == 1 || boolen[a][b] == 3 || boolen[a][b] == 4 ||boolen[a][b] == 6 );
    boolen[r][c] = 0;
    boolen[a][b] = 5;
}

void enemyGreenMove(int boolen[MAP_HEIGHT][MAP_WIDTH], int symbol){
    int r = 0;
    int c = 0;
    int a, b;
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            if (boolen[j][i] == 6) {
                r = j;
                c = i;
            }
        }
    }
    do {
        a = r - symbol + rand() % (2* symbol + 1);
        b = c - symbol + rand() % (2* symbol + 1);
    } while ( a < 0 || a >= MAP_HEIGHT || b < 0 || b >= MAP_WIDTH || (a == r && b == c) || boolen[a][b] == 1 || boolen[a][b] == 3 || boolen[a][b] == 4 ||boolen[a][b] == 5 );
    boolen[r][c] = 0;
    boolen[a][b] = 6;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int bando[MAP_HEIGHT][MAP_WIDTH];
    readMatrix("matrix.txt", bando, MAP_WIDTH, MAP_HEIGHT);

    /*{
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 3, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    */
    char tieptuc = 'y';
    while (tieptuc == 'y') {
        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();

        //tạo cửa sổ
        SDL_Window* window = SDL_CreateWindow("Nguyen Quang Tuan_22028209",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              SCREEN_WIDTH, SCREEN_HEIGHT,
                                              SDL_WINDOW_SHOWN);

        //tạo renderer
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        //tạo ảnh mở đầu
        SDL_Surface* imageSurface = IMG_Load("image/Welcome.png");
        SDL_Texture* textureWelcome = SDL_CreateTextureFromSurface(renderer, imageSurface);
        SDL_FreeSurface(imageSurface);
        SDL_RenderCopy(renderer, textureWelcome, NULL, NULL);

        // Tải ảnh kết thúc
        SDL_Surface* overSurface = IMG_Load("image/over.png");
        SDL_Texture* textureOver = SDL_CreateTextureFromSurface(renderer, overSurface);
        SDL_FreeSurface(overSurface);

        //bấm phím bất kỳ để vào game
        bool quit = false;
        bool temp = false;
        while (!temp) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT){
                    temp = true;
                    quit = true;

                } else if (event.type == SDL_KEYDOWN)
                    {
                        SDL_DestroyTexture(textureWelcome);
                        temp = true;
                    }
            }

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, textureWelcome, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
        SDL_DestroyTexture(textureWelcome);

        // Texture
        int score = 0;
        SDL_Texture* wall = IMG_LoadTexture(renderer, "image/wall.png");
        SDL_Texture* path = IMG_LoadTexture(renderer, "image/path.png");
        SDL_Texture* path01 = IMG_LoadTexture(renderer, "image/path01.png");
        SDL_Texture* red = IMG_LoadTexture(renderer, "image/red.png");
        SDL_Texture* blue = IMG_LoadTexture(renderer, "image/blue.png");
        SDL_Texture* pink = IMG_LoadTexture(renderer, "image/pink.png");
        SDL_Texture* green = IMG_LoadTexture(renderer, "image/green.png");
        // Tải ảnh main.bmp
        SDL_Surface* main_surface = IMG_Load("image/main.png");
        SDL_Texture* main_texture = SDL_CreateTextureFromSurface(renderer, main_surface);


        // Khởi tạo kích thước và vị trí ban đầu của ảnh main
        SDL_Rect main_rect;
        main_rect.w = main_surface->w;
        main_rect.h = main_surface->h;
        main_rect.x = 12 * TILE_SIZE; //SCREEN_WIDTH / 2 - main_surface->w / 2 ;
        main_rect.y = 12 * TILE_SIZE; //SCREEN_HEIGHT / 2 - main_surface->h / 2;

        //==============================<BẢNG ĐIỂM>===============================
        TTF_Font* font = TTF_OpenFont(Font.c_str(), fontSize );
        if (!font) {
            std::cout << "Failed to load font: " << TTF_GetError() << '\n';
            return 1;
        }
        SDL_Rect scoreRect;
        SDL_Color color = { 255, 255, 255 };
        std::string scoreString = "Score: " + std::to_string(score);
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreString.c_str(), color);
        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_FreeSurface(scoreSurface);
        SDL_QueryTexture(scoreTexture, nullptr, nullptr, &scoreRect.w, &scoreRect.h);
        scoreRect.x = SCREEN_WIDTH - scoreRect.w - 10;
        scoreRect.y = 10;


        //==============================<GAME LOGIC>================================

        int countLeft = 0;
        int countRight = 0;
        int countUp = 0;
        int countDown = 0;

        // Xử lý sự kiện

        while (!quit){
            SDL_Event e;
            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                    quit = true;
                }
                else if (e.type == SDL_KEYDOWN){
                    switch (e.key.keysym.sym){
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_LEFT:
                            countLeft += 1;
                            if (countLeft % 6 == 5) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainLeft2.png"); // Chuyển lại về main.png
                            } else if (countLeft % 6 == 0) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainLeft2.png"); // Chuyển lại về main.png
                                countLeft = 0;
                            }
                             else if (countLeft % 6 == 3 || countLeft % 6 == 4) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainLeft1.png"); // Chuyển lại về main.png
                            }
                              else if (countLeft % 6 == 1 || countLeft % 6 == 2){
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/main.png"); // Chuyển sang main1.png
                            }

            //=========<XỬ LÝ MAIN DI CHUYỂN >================
                            SDL_DestroyTexture(main_texture);
                            main_texture = SDL_CreateTextureFromSurface(renderer, main_surface);
                            if(move_left(TILE_SIZE, main_rect.x, main_rect.y, main_rect.w, step, bando)) {
                                main_rect.x = (main_rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
                                pointed(bando, main_rect.x , main_rect.y, score);
                                enemyRedMove(bando, symbolRed);
                                enemyBlueMove(bando, symbolBlue );
                                enemyPinkMove(bando, symbolPink);
                                enemyGreenMove(bando, symbolGreen);
                                if(die(bando, main_rect.x , main_rect.y) == true ) {
                                    SDL_Delay(500);
                                    SDL_RenderCopy(renderer, textureOver, NULL, NULL);
                                    SDL_RenderPresent(renderer);
                                    SDL_DestroyTexture(textureOver);
                                    SDL_Delay(2000);
                                    quit = true;
                                }
                            }
                            break;
            //==================================================
                        case SDLK_RIGHT:
                            countRight += 1;
                            if (countRight % 6 == 5) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainRight2.png"); // Chuyển lại về main.png
                            }else if (countRight % 6 == 0) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainRight2.png"); // Chuyển lại về main.png
                                countRight = 0;
                            }
                            else if (countRight % 6 == 3 ||  countRight % 6 == 4) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainRight1.png"); // Chuyển lại về main.png
                            } else if ( countRight % 6 == 1 || countRight % 6 == 2 ){
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/main.png"); // Chuyển sang main1.png
                            }
                            SDL_DestroyTexture(main_texture);
                            main_texture = SDL_CreateTextureFromSurface(renderer, main_surface);
                            if(move_right(TILE_SIZE, main_rect.x, main_rect.y, main_rect.h, step, bando)) {
                                main_rect.x = (main_rect.x + step + SCREEN_WIDTH) % SCREEN_WIDTH;
                                //-----------------------------------------------------------------
                                pointed(bando, main_rect.x , main_rect.y, score);
                                enemyRedMove(bando, symbolRed);
                                enemyBlueMove(bando, symbolBlue );
                                enemyPinkMove(bando, symbolPink);
                                enemyGreenMove(bando, symbolGreen);
                                if(die(bando, main_rect.x , main_rect.y) == true ) {
                                    SDL_Delay(500);
                                    SDL_RenderCopy(renderer, textureOver, NULL, NULL);
                                    SDL_RenderPresent(renderer);
                                    SDL_DestroyTexture(textureOver);
                                    SDL_Delay(2000);
                                    quit = true;
                                }
                                //-----------------------------------------------------------------
                            }
                            break;
                        case SDLK_UP:
                            countUp += 1;
                            if (countUp % 6 == 5) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainUp2.png"); // Chuyển lại về main.png
                            }
                            if (countUp % 6 == 0) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainUp2.png"); // Chuyển lại về main.png
                                countUp = 0;
                            }   else if (countUp % 6 == 3 || countUp == 4) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainUp1.png"); // Chuyển lại về main.png
                            } else if(countUp % 6 == 1 || countUp % 6 == 2 ) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/main.png"); // Chuyển sang main1.png
                                //countUp = 0;
                            }
                            SDL_DestroyTexture(main_texture);
                            main_texture = SDL_CreateTextureFromSurface(renderer, main_surface);
                            if (move_up(TILE_SIZE, main_rect.x, main_rect.y, main_rect.h, step, bando)) {
                                main_rect.y = (main_rect.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
                                //-----------------------------------------------------------------
                                pointed(bando, main_rect.x , main_rect.y, score);
                                enemyRedMove(bando, symbolRed);
                                enemyBlueMove(bando, symbolBlue );
                                enemyPinkMove(bando, symbolPink);
                                enemyGreenMove(bando, symbolGreen);
                                if(die(bando, main_rect.x , main_rect.y) == true ) {
                                    SDL_Delay(500);
                                    SDL_RenderCopy(renderer, textureOver, NULL, NULL);
                                    SDL_RenderPresent(renderer);
                                    SDL_DestroyTexture(textureOver);
                                    SDL_Delay(2000);
                                    quit = true;
                                }
                                //-----------------------------------------------------------------
                            }
                            break;
                        case SDLK_DOWN:
                            countDown += 1;
                            if (countDown % 6 == 5 ) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainDown2.png"); // Chuyển lại về main.png
                            }
                            else if (countDown % 6 == 0 ) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainDown2.png"); // Chuyển lại về main.png
                                countDown = 0;
                            }
                            else if (countDown % 6 == 3 || countDown % 6 == 4 ) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/mainDown1.png"); // Chuyển lại về main.png
                            }else if (countDown % 6 == 1 || countDown % 6 == 2 ) {
                                SDL_FreeSurface(main_surface);
                                main_surface = IMG_Load("image/main.png"); // Chuyển sang main1.png
                            }
                            SDL_DestroyTexture(main_texture);
                            main_texture = SDL_CreateTextureFromSurface(renderer, main_surface);
                            if (move_down(TILE_SIZE, main_rect.x, main_rect.y, main_rect.h,main_rect.w, step, bando)) {
                                main_rect.y = (main_rect.y + step) % SCREEN_HEIGHT;
                                pointed(bando, main_rect.x , main_rect.y,score);
                                enemyRedMove(bando, symbolRed);
                                enemyBlueMove(bando, symbolBlue );
                                enemyPinkMove(bando, symbolPink);
                                enemyGreenMove(bando, symbolGreen);
                                if(die(bando, main_rect.x , main_rect.y) == true ) {
                                    SDL_Delay(500);
                                    SDL_RenderCopy(renderer, textureOver, NULL, NULL);
                                    SDL_RenderPresent(renderer);
                                    SDL_DestroyTexture(textureOver);
                                    SDL_Delay(2000);
                                    quit = true;
                                }
                            }
                            break;
                    }
                }
            }
            SDL_RenderClear(renderer);
            //===============================< Vẽ map lên màn hình >===============================
            for (int i = 0; i < MAP_HEIGHT; i++) {
                for (int j = 0; j < MAP_WIDTH; j++) {
                    SDL_Rect rect = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                    if (bando[i][j] == 0) {
                        SDL_RenderCopy(renderer, path, NULL, &rect);
                    } else if (bando[i][j] == 1) {
                        SDL_RenderCopy(renderer, wall, NULL, &rect);
                    } else if (bando[i][j] == 2) {
                        SDL_RenderCopy(renderer, path01, NULL, &rect);
                    } else if (bando[i][j] == 3) {
                        SDL_RenderCopy(renderer, red, NULL, &rect);
                    } else if (bando[i][j] == 4) {
                        SDL_RenderCopy(renderer, blue, NULL, &rect);
                    } else if (bando[i][j] == 5) {
                        SDL_RenderCopy(renderer, pink, NULL, &rect);
                    } else if (bando[i][j] == 6) {
                        SDL_RenderCopy(renderer, green, NULL, &rect);
                    }
                }
            }
            //======================<HIỂN THỊ SAU KHI DI CHUYỂN>===============================

            // Hiển thị lại ảnh main đã được di chuyển
            SDL_RenderCopy(renderer, main_texture, NULL, &main_rect);
            // Hiển thị bảng điểm
            scoreString = "Score: " + std::to_string(score);
            scoreSurface = TTF_RenderText_Solid(font, scoreString.c_str(), color);
            scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
            SDL_FreeSurface(scoreSurface);
            SDL_QueryTexture(scoreTexture, nullptr, nullptr, &scoreRect.w, &scoreRect.h);
            scoreRect.x = SCREEN_WIDTH - scoreRect.w - 10;
            SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);

            // Cập nhật lại màn hình
            SDL_RenderPresent(renderer);
        }

        //==================================<GIẢI PHÓNG>=======================================
        SDL_DestroyTexture(main_texture);
        SDL_DestroyTexture(scoreTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        // Đóng SDL2, SDL2_image và SDL2_ttf
        IMG_Quit();
        SDL_Quit();
        TTF_Quit();
        std::cout << "Continue ??? <y/n> " << std::endl;
        do {
            std::cout << "Your answer: ";
            std::cin >> tieptuc;
        } while(tieptuc != 'y' && tieptuc != 'n' );
        if (tieptuc == 'n')
        return 0;
    }
}

