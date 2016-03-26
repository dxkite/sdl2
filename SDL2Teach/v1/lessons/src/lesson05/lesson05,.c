// 触屏事件
/* DXkite SDL2教程第五课
 * 本课教学 触屏事件 
 * 2014-5-31
 * 编译器：C4droid/g++/c++11
 * 函数查询入口
 Google翻译版:http://translate.googleusercontent.com/translate_c?depth=1&ie=UTF8&nv=1&rurl=translate.google.com&sl=auto&tl=zh-CN&u=http://wiki.libsdl.org/FrontPage&usg=ALkJrhh9G_mTkBBfX17kq2QRkH0LwCVu-g 
 *英文版:http://wiki.libsdl.org/FrontPage  建议对照来看 */
#include "SDL2/SDL.h"
// 包含字体扩展库
#include "SDL2/SDL_ttf.h"
#include<string>
// 使用std::string
using std::string;
const int FontSize = 60;
// 根目录/mnt/sdcard/
string Root = "/mnt/sdcard/";
// 字体路径
string Fonts = "/system/fonts/DroidSansFallback.ttf";
SDL_Event event;
// 窗口
SDL_Window *Window = NULL;
// 渲染器
SDL_Renderer *Render = NULL;
int Init()
{
/* 参数说明 *标题,位置信息(x,y,w,h),窗体模式标记 */
Window =
SDL_CreateWindow("SDL2 第五课 DXkite", 0, 0, 480, 600,
 SDL_WINDOW_FULLSCREEN);
/* 参数说明 *窗体,渲染器索引(-1为默认),模式标记 */
Render = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
if ((Render == NULL) || (Window == NULL))
return -1;
return 0;
}
int BiltTexture(int x, int y, SDL_Texture * Draw_Texture,
SDL_Renderer * Draw_Render)
{
SDL_Rect Draw_Render_Rect;
Draw_Render_Rect.x = x;
Draw_Render_Rect.y = y;
/* 
 *查询函数
 *int SDL_QueryTexture(SDL_Texture* texture,Uint32* format, int* access,int* w,int* h)
 */
int w = 0, h = 0;
SDL_QueryTexture(Draw_Texture, NULL, NULL, &w, &h);
Draw_Render_Rect.w = w;
Draw_Render_Rect.h = h;
// 本部分函数可变性极强。
// 有兴趣的同学可以自行更改
SDL_RenderCopy(Draw_Render, Draw_Texture, NULL, &Draw_Render_Rect);
}
int ShowText(int x, int y, const char *str, int r = 0, int g =
 0, int b = 0, int a = 0)
{
// 初始化字体
TTF_Init();
TTF_Font *font = NULL;
SDL_Texture *fonts = NULL;
font = TTF_OpenFont(Fonts.c_str(), FontSize);
SDL_Color color;
color.r = r;
color.g = g;
color.b = b;
color.a = a;
SDL_Surface *temp = NULL;
temp = TTF_RenderUTF8_Blended(font, str, color);
fonts = SDL_CreateTextureFromSurface(Render, temp);
SDL_FreeSurface(temp);
TTF_CloseFont(font);
BiltTexture(x, y, fonts, Render);
SDL_DestroyTexture(fonts);
if (fonts == NULL)
return -1;
return 0;
}
int DestroyAll()
{
// 释放
SDL_DestroyRenderer(Render);
SDL_DestroyWindow(Window);
}
int main(int argc, char *argv[])
{
// 初始化SDL2(为了省事初始化了全部)
SDL_Init(SDL_INIT_EVERYTHING);
// 初始化
if (Init() == -1)
// 初始化失败退出SDL
SDL_Quit();
int i = 0;
double Tx = 0.0, Ty = 0.0;
char str[80];
while (true)
{
while (SDL_PollEvent(&event))
{
// event.type: 
// SDL_FINGERDOWN 
// SDL_FINGERUP
// SDL_FINGERMOTION
if (event.type == SDL_FINGERUP)
{
Tx = 0.0;
Ty = 0.0;
}
Tx = event.tfinger.x;
Ty = event.tfinger.y;
}
sprintf(str, "[x:%.3f][y:%.3f]", Tx, Ty);
// str="app";
ShowText(0, 0, str, 0, 200);
// 刷新(不刷新，等着黑屏)
SDL_RenderPresent(Render);
SDL_Delay(10);
}
DestroyAll();
SDL_Quit();
}