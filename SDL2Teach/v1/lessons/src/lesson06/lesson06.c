// 第六课
// 键盘输入
#include "SDL2/SDL.h"
// 包含字体扩展库
#include "SDL2/SDL_ttf.h"
#include<string>
// 使用std::string
using std::string;

// 根目录/mnt/sdcard/
string Root = "/mnt/sdcard/";
// 字体路径
string Fonts = "/system/fonts/DroidSansFallback.ttf";

	// 窗口
SDL_Window *Window = NULL;
// 渲染器
SDL_Renderer *Render = NULL;
// 画笔
SDL_Texture *fonts = NULL;


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

SDL_Texture *Text(std::string Fonts, int FontSize, SDL_Renderer * Render,
				  std::string FontsPath, int r = 0, int g = 0, int b =
				  0, int a = 0)
{
	// 初始化字体
	TTF_Init();
	TTF_Font *font = NULL;
	font = TTF_OpenFont(FontsPath.c_str(), FontSize);
	/* 
	 *结构体原型
	 SDL_Color
	 {
	 Uint8 r,g,b,a;
	 };
	 */
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	SDL_Surface *temp = NULL;
	/* 
	   函数原型： extern DECLSPEC SDL_Surface * SDLCALL
	   TTF_RenderUTF8_Blended(TTF_Font *font,const char *text, SDL_Color fg); */
	temp = TTF_RenderUTF8_Blended(font, Fonts.c_str(), color);
	fonts = SDL_CreateTextureFromSurface(Render, temp);
	SDL_FreeSurface(temp);
	TTF_CloseFont(font);
	if (fonts != NULL)
		return fonts;
}


int BiltTexture(int x, int y, SDL_Texture * Draw_Texture,
				SDL_Renderer * Draw_Render)
{
	// 不支持缩放了～～～
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


int DestroyAll()
{
	// 释放
	SDL_DestroyTexture(fonts);
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
	SDL_Event event;
	std::string T;
	while (true)
	{
		SDL_RenderClear(Render);
		while (SDL_PollEvent(&event))
		{
			/* if(event->key.keysym.scancode !=
			   SDL_GetScancodeFromKey(event->key.keysym.sym)) printf("Physical 
			   %s key acting as %s key",
			   SDL_GetScancodeName(event->key.keysym.scancode),
			   SDL_GetKeyName(event->key.keysym.sym)); */
			Window = SDL_GetKeyboardFocus();
			SDL_StartTextInput();
			if (event.type == SDL_KEYDOWN)
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					{
						BiltTexture(0, 0,
									Text("SDLK_UP", 40, Render, Fonts, 255,
										 255), Render);
						break;
					}
				case SDLK_DOWN:
					{
						BiltTexture(0, 0,
									Text("SDLK_DOWN", 40, Render, Fonts, 255,
										 255), Render);
						break;
					}
				case SDLK_LEFT:
					{

						BiltTexture(0, 0,
									Text("SDLK_LEFT", 40, Render, Fonts, 255,
										 255), Render);
						break;
					}
				case SDLK_RIGHT:
					{
						BiltTexture(0, 0,
									Text("SDLK_RIGHT", 40, Render, Fonts, 255,
										 255), Render);
						break;

					}
				}
			{
				T = SDL_GetKeyName(event.key.keysym.sym);
				BiltTexture(0, 100,
							Text(T, 40, Render, Fonts, 255, 255), Render);
				std::string Tc =
					SDL_GetScancodeName(event.key.keysym.scancode);
				BiltTexture(0, 200,
							Text(Tc, 40, Render, Fonts, 255, 255), Render);
				if (T == "A")
					BiltTexture(0, 0,
								Text("你按下了A键", 40, Render, Fonts, 255,
									 255), Render);
			}

			SDL_RenderPresent(Render);
			SDL_Delay(10);
		}

	}
	DestroyAll();

	SDL_Quit();
}