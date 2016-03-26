/*************************\
*SDL2基础教程
*第三课 
*DXKite编写
*2014-5-11
\*************************/
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include<string>
	// 创建窗口 
SDL_Window *win = NULL;
	// 创建渲染器 
SDL_Renderer *renderer = NULL;
	// 创建绘画表面 
SDL_Texture *pic = NULL;
SDL_Surface *picSur = NULL;
SDL_Texture *background = NULL;
std::string RootFile = "/mnt/sdcard/SDL2教程/lessons/src/lesson03/";

int Init()
{

	/* 使用SDL前先初始化 */
	if (!SDL_Init(SDL_INIT_EVERYTHING))
		return -1;
	if (!IMG_Init(IMG_INIT_PNG))
		return -1;
	/* 设置窗口 */
	win = SDL_CreateWindow("加载图片", 0, 0, 480, 800, 0);
	/* 设置渲染器 */
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	return 0;
}

int Destroy()
{
	/* 销毁绘画表面 */
	SDL_DestroyTexture(pic);
	/* 销毁渲染器 */
	SDL_DestroyRenderer(renderer);
	/* 销毁窗口 */
	SDL_DestroyWindow(win);
	/* 释放表面 */
	SDL_FreeSurface(picSur);
	/* 退出 */
	SDL_Quit();
	IMG_Quit();
}

int BiltTexture(int x, int y, SDL_Texture * Draw_Texture,
				SDL_Renderer * Draw_Render)
{
	SDL_Rect Draw_Render_Rect;
	Draw_Render_Rect.x = x;
	Draw_Render_Rect.y = y;
	int w = 0, h = 0;
	SDL_QueryTexture(Draw_Texture, NULL, NULL, &w, &h);
	Draw_Render_Rect.w = w;
	Draw_Render_Rect.h = h;
	// 本部分函数可变性极强。
	// 有兴趣的同学可以自行更改
	SDL_RenderCopy(Draw_Render, Draw_Texture, NULL, &Draw_Render_Rect);
}
// 去背景色
SDL_Surface *SetColorKey(SDL_Surface * f, int r, int g, int b)
{
	// 声明定义一个32位无符号颜色
	// (Usigned int 32->Uint32)
	Uint32 colorkey = SDL_MapRGB(f->format, 0, 0xFF, 0xFF);
	SDL_SetColorKey(f, SDL_TRUE, colorkey);
	return f;
}

int LoadSrc(std::string RP)
{
	picSur = IMG_Load((RP + "dots.png").c_str());
	picSur = SetColorKey(picSur, 0, 0xff, 0xff);
	pic = SDL_CreateTextureFromSurface(renderer, picSur);
	background =
		SDL_CreateTextureFromSurface(renderer,
									 IMG_Load((RP +
											   "background.png").c_str()));
	if ((pic == NULL) || (background == NULL))
		return -1;
	return 0;
}


// 切割图片
int ClipBiltTexture(int x, int y, SDL_Texture * Draw_Texture, SDL_Rect Clip,
					SDL_Renderer * Draw_Render)
{
	SDL_Rect Draw_Render_Rect;
	Draw_Render_Rect.x = x;
	Draw_Render_Rect.y = y;
	int w = 0, h = 0;
	SDL_QueryTexture(Draw_Texture, NULL, NULL, &w, &h);
	Draw_Render_Rect.w = Clip.w;
	Draw_Render_Rect.h = Clip.h;
	// 本部分函数可变性极强。
	// 有兴趣的同学可以自行更改
	SDL_RenderCopy(Draw_Render, Draw_Texture, &Clip, &Draw_Render_Rect);
}

// 旋转函数

int SpinZoomBiltTexture(int x, int y, SDL_Texture * Draw_Texture,
					SDL_Renderer * Draw_Render,
				bool zoom = false, float extent = 1.0, double angle = 0.0, int cx =
					-1, int cy = -1)
{
	SDL_Rect Draw_Render_Rect;
	Draw_Render_Rect.x = x;
	Draw_Render_Rect.y = y;

	int w = 0, h = 0;
	SDL_QueryTexture(Draw_Texture, NULL, NULL, &w, &h);
		if (extent < 0)
	{	extent =1.0;
	}
	if (zoom)
	{
		Draw_Render_Rect.w = w * extent;
		Draw_Render_Rect.h = h * extent;
	}
	else
	{
		Draw_Render_Rect.w = w;
		Draw_Render_Rect.h = h;
	}
	/* 函数原型

	   extern DECLSPEC int SDLCALL SDL_RenderCopyEx(SDL_Renderer * renderer,
	   SDL_Texture * texture, const SDL_Rect * srcrect, const SDL_Rect *
	   dstrect, const double angle, const SDL_Point *center, const
	   SDL_RendererFlip flip); */
	if ((cx != -1) && (cy != -1))

	{
		SDL_Point center;
		center.x = cx;
		center.y= cy;
		SDL_RenderCopyEx(Draw_Render, Draw_Texture, NULL, &Draw_Render_Rect,
						 // 旋转角度
						 angle,
						 // 旋转中心
						 &center,
						 // 旋转方式
						 // SDL_FLIP_HORIZONTAL 水平旋转
						 // SDL_FLIP_VERTICAL 垂直翻转
						 // SDL_FLIP_NONE 无
						 SDL_FLIP_NONE);
	}
	else
	{
		SDL_RenderCopyEx(Draw_Render, Draw_Texture, NULL,
						 &Draw_Render_Rect, angle, NULL, SDL_FLIP_HORIZONTAL);
	}

}

int main(int argc, char *argv[])
{

	if ((Init() != 0) || (LoadSrc(RootFile) != 0))
		return -1;
	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.w = 100;
	clip.h = 100;
	double i=0.0;
	while (true)
	{
		i+=1.0;
		SDL_RenderClear(renderer);
		BiltTexture(0, 0, background, renderer);
	//	BiltTexture(100, 200, pic, renderer);
	//	ClipBiltTexture(100,100, pic, clip, renderer);
	SpinZoomBiltTexture(300, 100, pic, renderer,1,0.5,i, 0,0);
		SDL_RenderPresent(renderer);
		/* 暂停2000毫秒 */
		SDL_Delay(20);
	}
	Destroy();
	return 0;
}