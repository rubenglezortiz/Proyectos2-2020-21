
#include "SDL.h"
#include "SDL_image.h"

#include <iostream>

using namespace std;

using uint = unsigned int;

void firstTest() {
	const int WIN_WIDTH = 800;
	const int WIN_HEIGHT = 600;
	bool exit = false;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const uint winWidth = 800;
	const uint winHeight = 600;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("My first test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	SDL_Texture* texture; // Variable para la textura
	string filename = "background1.png"; // Nombre del fichero con la imagen .bmp
	//SDL_Surface* surface = SDL_LoadBMP(filename.c_str()); // Solo para bmps
	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface); // Se borra la estructura auxiliar
	// Textura lista para ser usada

	SDL_Texture* texture2; // Variable para la textura
	string filename2 = "dog.png"; // Nombre del fichero con la imagen .bmp
	//SDL_Surface* surface = SDL_LoadBMP(filename.c_str()); // Solo para bmps
	surface = IMG_Load(filename2.c_str());
	texture2 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface); // Se borra la estructura auxiliar

	int textW, textH; // Para saber el tamaño de la textura
	SDL_QueryTexture(texture2, nullptr, nullptr, &textW, &textH);
	SDL_Rect srcRect, destRect;
	srcRect.w = textW / 6; srcRect.h = textH / 1; // Tamaño frame textura 6 imagenes en 1 fila
	//uint cellW = WIN_WIDTH / 8; uint cellH = WIN_HEIGHT / 8;
	destRect.w = 100; destRect.h = 100; // Tamaño px salida
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.x = 0; destRect.y = WIN_WIDTH / 2; // pos izq

	SDL_Texture* texture3; // Variable para la textura
	string filename3 = "helicopter.png"; // Nombre del fichero con la imagen .bmp
	//SDL_Surface* surface = SDL_LoadBMP(filename.c_str()); // Solo para bmps
	surface = IMG_Load(filename3.c_str());
	texture3 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface); // Se borra la estructura auxiliar

	int textW2, textH2; // Para saber el tamaño de la textura
	SDL_QueryTexture(texture3, nullptr, nullptr, &textW2, &textH2);
	SDL_Rect srcRect2, destRect2;
	srcRect2.w = textW2 / 5; srcRect2.h = textH2 / 1; // Tamaño frame textura 6 imagenes en 1 fila
	//uint cellW = WIN_WIDTH / 8; uint cellH = WIN_HEIGHT / 8;
	destRect2.w = 50; destRect2.h = 50; // Tamaño px salida
	srcRect2.x = 0;
	srcRect2.y = 0;
	destRect2.x = WIN_WIDTH - destRect2.w; destRect2.y = 0; // pos izq


	/*if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderCopy(renderer, texture2, &srcRect, &destRect);
		SDL_RenderPresent(renderer);
		SDL_Delay(5000);
	}*/

	uint32_t startTime, frameTime;
	//startTime = SDL_GetTicks();
	SDL_Event event;
	const int FRAME_RATE = 50;
	int vel_Dog = 10;
	int vel_Hel = 10;
	bool dog = false;
	bool hel = false;

	while (!exit) { // Bucle del juego
		startTime = SDL_GetTicks();
		while (SDL_PollEvent(&event) && !exit)
		{
			if (event.type == SDL_QUIT)
				exit = true;
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_d) {
					if (dog)
						dog = false;
					else
						dog = true;
				}
				if (event.key.keysym.sym == SDLK_h) {
					if (hel)
						hel = false;
					else
						hel = true;
				}
				if (event.key.keysym.sym == SDLK_s) {
					vel_Dog += 5;
				}
				if (event.key.keysym.sym == SDLK_f) {
					if (vel_Dog - 5 >= 0)
						vel_Dog -= 5;
				}
				if (event.key.keysym.sym == SDLK_j) {
					vel_Hel += 5;
				}
				if (event.key.keysym.sym == SDLK_g) {
					if (vel_Hel - 5 >= 0)
						vel_Hel -= 5;
				}
			}
		}

		/*if (destRect.x != 800) {
			SDL_Delay(50);
			destRect.x += 10;
		}

		else
			destRect.x = 0;*/

			//frameTime = SDL_GetTicks() - startTime; // Tiempo desde última actualización
			//if (frameTime >= FRAME_RATE) {
		if (dog) {
			if (destRect.x <= WIN_WIDTH)
				destRect.x += vel_Dog;
			else
				destRect.x = 0;
			if (srcRect.x != 5 * (textW / 6))	//srcRect.x = textFrameW * int(((SDL_GetTicks() / TIME_PER_FRAME) % 6));
				srcRect.x = (textW / 6) * int((SDL_GetTicks() / FRAME_RATE) % 6);
			else
				srcRect.x = 0;
		}
		if (hel) {
			if (destRect2.x >= -destRect2.w)
				destRect2.x -= vel_Hel;
			else
				destRect2.x = WIN_WIDTH;

			if (srcRect2.x != 4 * (textW2 / 5))
				srcRect2.x = (textW2 / 5) * int((SDL_GetTicks() / FRAME_RATE) % 5);
			else
				srcRect2.x = 0;
		}

		//startTime = SDL_GetTicks();
	//	}
			// Renderiza todos los objetos del juego
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderCopy(renderer, texture2, &srcRect, &destRect);
		SDL_RenderCopy(renderer, texture3, &srcRect2, &destRect2);
		SDL_RenderPresent(renderer);
		frameTime = SDL_GetTicks() - startTime; // Tiempo de la iteración
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime); // Suspende por el tiempo restante
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}



int main(int argc, char* argv[]) {
	firstTest();
	
	return 0;
}