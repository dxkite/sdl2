				// 第五课
	// 触屏事
#include "SDL2/SDL.h"
	// 包含字体扩展库
#include "SDL2/SDL_ttf.h"
#include "DXErr.h"
	using namespace DXkite;
#include<string>
// 使用std::string
using std::string;

// 根目录/mnt/sdcard/
string Root = "/mnt/sdcard/";
// 字体路径
string Fonts = "/system/fonts/DroidSansFallback.ttf";
DXErr f;

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
	int i = 0;
	double Tx = 0.0, Ty = 0.0;
	char str[80];
	char str2[80];
	float Tdx = 0.0, Tdy = 0.0, p = 0.0;
	char str3[80];
	char str4[80];
	SDL_Event event;
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			// event.type: 
			// SDL_FINGERDOWN 
			// SDL_FINGERUP
			// SDL_FINGERMOTION
		/*	if (event.type == SDL_FINGERUP)
			{
				Tx = 0.0;
				Ty = 0.0;
			}*/
			Tx = event.tfinger.x;
			Ty = event.tfinger.y;
			Tdx = event.tfinger.dx;
			Tdy = event.tfinger.dy;
            p=event.tfinger.pressure;
		}
		sprintf(str, "[x:%.3f][y:%.3f]", Tx, Ty);
		f << str << Endl;
		BiltTexture(0, 0, Text(str, 40, Render, Fonts, 255, 255), Render);
		sprintf(str3, "[dx:%.3f][dy:%.3f]", Tdx, Tdy);
		f << str3 << Endl;
		BiltTexture(0, 200, Text(str, 40, Render, Fonts, 255, 255), Render);
		sprintf(str4, "%.3f",p);
		f << str4 << Endl << Endl;
		BiltTexture(0, 250, Text(str4, 40, Render, Fonts, 255, 255), Render);
		BiltTexture(0, 50, Text("触点", 30, Render, Fonts, 0, 255), Render);
		int TWx = Tx * 480;
		int TWy = Ty * 800;
		sprintf(str2, "[x:%03d][y:%03d]", TWx, TWy);
		BiltTexture(0, 100, Text(str2, 40, Render, Fonts, 0, 255, 255),
					Render);
		// 刷新(不刷新，等着黑屏)
		SDL_RenderPresent(Render);
		SDL_Delay(10);
	}
	DestroyAll();

	SDL_Quit();
}