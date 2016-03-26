#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "head.h"
using namespace DXkite;
#include<string>

	// 创建窗口 
SDL_Window *Window = NULL;
	// 创建渲染器 
SDL_Renderer *Render = NULL;

std::string RootFile = "/mnt/sdcard/SDL2教程/lessons/src/lesson05/";


class Botton
{
  private:
	SDL_Surface * Pic = NULL;
	SDL_Texture *Tex = NULL;
	SDL_Renderer *Render_ = NULL;
	std::string Path;
	int x, y;
	int wh, ww;
  public:
	Botton(std::string Path, SDL_Renderer * Render_);
	bool Is_Click();
	int Set(int X, int Y);
	int SetWinSize(SDL_Window * win);
};

Botton::Botton(std::string Path, SDL_Renderer * Render_)
{
	Tex = LoadTexture(Path,Render_);
	x = 0;
	y = 0;
	ww = 0;
	wh = 0;
	// SDL_GetWindowSize(win, &ww, &wh);

}

bool Botton::Is_Click()
{
	BiltTexture(x,y,Tex,Render_);
		int w = 0, h = 0;
		SDL_QueryTexture(Tex, NULL, NULL, &w, &h);
	int Tx = 0;
	int Ty = 0;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		Tx = event.tfinger.x * ww;
		Ty = event.tfinger.y * wh;
		if ((Tx >= x) && (Tx <= (x + w)) && (Ty >= y) && (Ty <= y + h))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int Botton::SetWinSize(SDL_Window * win)
{
	SDL_GetWindowSize(win, &ww, &wh);
	if ((wh != 0) && (ww != 0))
		return 0;
	return -1;
}

int Init()
{
	/* 参数说明 *标题,位置信息(x,y,w,h),窗体模式标记 */
	Window =
		SDL_CreateWindow("SDL2 第四课 DXkite", 0, 0, 480, 600,
						 SDL_WINDOW_FULLSCREEN);

	/* 参数说明 *窗体,渲染器索引(-1为默认),模式标记 */
	Render = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	if ((Render == NULL) || (Window == NULL))
		return -1;
	return 0;
}

int DestroyAll()
{
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
		Botton star(RootFile+"star.png",Render);
		star.Is_Click();
		SDL_Delay(10000);
return 0;
}