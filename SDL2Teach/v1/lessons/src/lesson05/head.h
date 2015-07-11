#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include<string>
#ifndef __COMMON_H__
#define __COMMON_H__
namespace DXkite
{
	SDL_Surface *SetColorKey(SDL_Surface * f, int r, int g, int b)
	{
		// 声明定义一个32位无符号颜色
		// (Usigned int 32->Uint32)
		Uint32 colorkey = SDL_MapRGB(f->format, 0, 0xFF, 0xFF);
		  SDL_SetColorKey(f, SDL_TRUE, colorkey);
		  return f;
	}
	int ClipBiltTexture(int x, int y, SDL_Texture * Draw_Texture,
						SDL_Rect Clip, SDL_Renderer * Draw_Render)
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
	int SpinZoomBiltTexture(int x, int y, SDL_Texture * Draw_Texture,
							SDL_Renderer * Draw_Render,
							bool zoom = false, float extent =
							1.0, double angle = 0.0, int cx = -1, int cy = -1)
	{
		SDL_Rect Draw_Render_Rect;
		Draw_Render_Rect.x = x;
		Draw_Render_Rect.y = y;

		int w = 0, h = 0;
		SDL_QueryTexture(Draw_Texture, NULL, NULL, &w, &h);
		if (extent < 0)
		{
			extent = 1.0;
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

		   extern DECLSPEC int SDLCALL SDL_RenderCopyEx(SDL_Renderer *
		   renderer, SDL_Texture * texture, const SDL_Rect * srcrect, const
		   SDL_Rect * dstrect, const double angle, const SDL_Point *center,
		   const SDL_RendererFlip flip); */
		if ((cx != -1) && (cy != -1))

		{
			SDL_Point center;
			center.x = cx;
			center.y = cy;
			SDL_RenderCopyEx(Draw_Render, Draw_Texture, NULL,
							 &Draw_Render_Rect,
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
							 &Draw_Render_Rect, angle, NULL,
							 SDL_FLIP_HORIZONTAL);
		}

	}
SDL_Texture *LoadTexture(std::string filename,
										  SDL_Renderer * Render_temp,
										  bool Color_Key = false, int r =
										  0, int g = 0, int b = 0)
{
	// 创建临时表面
	SDL_Surface *Surface_temp = NULL;
	// 创建临时画笔
	SDL_Texture *Texture_temp = NULL;
	// 加载
	Surface_temp = IMG_Load(filename.c_str());
	// IMG_SavePNG(Surface_temp, "/mnt/sdcard/template.bmp");
	// 设置透明色
	Uint32 colorkey = SDL_MapRGB(Surface_temp->format, r, g, b);
	SDL_SetColorKey(Surface_temp, Color_Key, colorkey);
	// 生成画笔
	Texture_temp = SDL_CreateTextureFromSurface(Render_temp, Surface_temp);
	// 释放内存
	SDL_FreeSurface(Surface_temp);
	// 返回表面
	return Texture_temp;
}


}
#endif	/* Common.h */