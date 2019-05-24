#include "../header/render.h"

void AddToLoaded(string path) {
	Texture* texItr = loadedTextures;
	if (texItr != nullptr) {
		do {
			if (texItr->texName == path) {
				break;
			}
			texItr = texItr->next;
		} while (texItr != nullptr);
		if (texItr == nullptr) {
			list::AddNode<Texture>(&loadedTextures);
			loadedTextures->texName = path;
		}
	}
	else {
		list::AddNode<Texture>(&loadedTextures);
		loadedTextures->texName = path;
		printf(" ");
	}
}


void RenderWindow() {
	//add map tilelist to loadedtexture
	Obj* texItr = targetMap->texList;
	do {
		AddToLoaded(texItr->texName);
		texItr = texItr->next;
	} while (texItr != nullptr);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
	SDL_RenderClear(renderer);

	// if the loaded tex isn't used, trash it, otherwise check if it loaded, if not, load
	Texture* loadedItr = loadedTextures;
	if (loadedItr == nullptr) {
		printf("loadedTextures is nullptr!\n");
	}
	else {
		do {
			Tile* tileItr = targetMap->roomList->tileList;
			if (tileItr != nullptr) {
				do 
				{
					if (tileItr == nullptr) printf("problem");
					if (tileItr->texName == loadedItr->texName) {
						SDL_Rect tmprect;
						int w, h;
						SDL_GetWindowSize(window, &w, &h);
						tmprect.w = (int)((float)w / scale);
						tmprect.h = (int)((float)h / scale);
						tmprect.x = offX;
						tmprect.y = offY;
						printf("%d\n", tmprect.x);
						SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
						SDL_RenderDrawLine(renderer, tmprect.x, tmprect.y, tmprect.x + (int)((float)tmprect.w / scale), tmprect.y);
						SDL_RenderDrawLine(renderer, (int)(float)tmprect.w / scale, tmprect.y, (int)(float)tmprect.w / scale, tmprect.y + tmprect.h);
						SDL_RenderDrawLine(renderer, (int)(float)tmprect.w / scale, tmprect.y + tmprect.h, tmprect.x, tmprect.y + tmprect.h);
						SDL_RenderDrawLine(renderer, tmprect.x, tmprect.y, tmprect.x, tmprect.y);

						if (collision::DoubleBoxCollision(&tmprect, &tileItr->rect)) {
							if (loadedItr->tex == nullptr) {
								loadedItr->tex = ImgLoad(loadedItr->texName.c_str());
							}
							break;
						}
					}
					tileItr = (Tile*)tileItr->next;
				} while (tileItr != nullptr);
			}
			if (tileItr == nullptr) {
				Texture* tmpObj = loadedItr->next;
				list::DeleteNode<Texture>(&loadedTextures, &loadedItr);
				loadedItr = tmpObj;
			}else loadedItr = loadedItr->next;
		} while (loadedItr != nullptr);
	}
	
	





	//map rendering
	// w / roomW * ScreenWidth
	SDL_Rect tmpRect;

	Tile * tileItr = targetRoom->tileList;
	do {
		SDL_Texture* tmpTex = nullptr;
		Texture* texLoop = loadedTextures;
		do {
			if (texLoop->texName == tileItr->texName) {
				tmpTex = texLoop->tex;
				break;
			}
			texLoop = texLoop->next;
		} while (texLoop != nullptr);
		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		tmpRect = tileItr->rect;




		/*static bool lazy = false;
		if (lazy == false) {
			int targetLength = targetRoom->width > targetRoom->height ? targetRoom->width : targetRoom->height;
			scale = float((targetRoom->width == targetLength ? w : h)) / float(targetLength);
			lazy = true;
		}*/

		// screen width / w
		//tmpRect.w *= WIDTH / roomItr->width;
		//tmpRect.h *= HEIGHT / roomItr->height;
		int scrW, scrH;
		SDL_GetWindowSize(window, &scrW, &scrH);



		//int w, h;
		//////SDL_GetWindowSize(window, &w, &h);
		//printf("%f\n", offX + w / scale);
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//SDL_RenderDrawLine(renderer, offX, offY, offX + w / scale, offY);
		//SDL_RenderDrawLine(renderer, offX + w / scale, offY, offX + w / scale, offY + h / scale);
		//SDL_RenderDrawLine(renderer, offX + w / scale, offY + h / scale, offX, offY + h / scale);
		//SDL_RenderDrawLine(renderer, offX, offY + h / scale, offX, offY);
		//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		tmpRect.w = (int)ceil(float(tileItr->rect.w) * scale);
		tmpRect.h = (int)ceil(float(tileItr->rect.h) * scale);
		tmpRect.x = (int)floor(float(tileItr->rect.x - offX) * scale + (scrW / 2));
		tmpRect.y = (int)floor(float(tileItr->rect.y - offY) * scale + (scrH / 2));

		// next make a relative coord system and move the camera
		// then add scaling of camera
		// test multiple rooms
		if (tmpTex == nullptr) {
			//printf("tmpTex is null\n");
		}
		SDL_RenderCopy(renderer, tmpTex, NULL, &tmpRect);
		tileItr = (Tile*)tileItr->next;
	} while (tileItr != nullptr);
	SDL_RenderPresent(renderer);
}
