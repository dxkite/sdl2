/*************************\
*SDL2基础教程
*第二课
*DXKite编写
*2014-5-11
\*************************/
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

int main(int argc, char *argv[])
{
/* 创建窗口 */
SDL_Window *win = NULL;
/* 创建渲染器 */
SDL_Renderer *renderer = NULL;
/* 创建绘画表面 */
SDL_Texture *HelloTex = NULL;
/* 创建加载表面 */
SDL_Surface *Surface = NULL;
/* 使用SDL前先初始化 */ SDL_Init(SDL_INIT_EVERYTHING);
IMG_Init(IMG_INIT_PNG); 
/* 设置窗口 */ 
win = SDL_CreateWindow("加载图片", 0, 0, 480, 800, 0);
/* 设置渲染器 */
renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
/* 加载图片 */
/*图片必须为bmp格式*/
Surface = IMG_Load("/mnt/sdcard/source/background.png");
/* 从表面创建画图表面 */
HelloTex = SDL_CreateTextureFromSurface(renderer, Surface);
/* 释放表面 */
SDL_FreeSurface(Surface);
/* 清理渲染器 */
SDL_RenderClear(renderer);
/* 复制绘图后的表面至渲染器 */
SDL_RenderCopy(renderer, HelloTex, NULL, NULL);
SDL_RenderPresent(renderer);
/* 暂停2000毫秒 */
SDL_Delay(2000);
/* 销毁绘画表面 */ SDL_DestroyTexture(HelloTex);
/* 销毁渲染器 */ SDL_DestroyRenderer(renderer);
/*销毁窗口*/
SDL_DestroyWindow(win);
/*退出*/
SDL_Quit();
IMG_Quit();
return 0;
}