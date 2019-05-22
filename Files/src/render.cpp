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

	}
		
}


void RenderWindow() {
	
	Obj* mapTexList = targetMap->texList;
	if (mapTexList != nullptr) {
		do {
			do {
				if (texLoadQueue == nullptr) {
					list::AddNode<Obj>(&texLoadQueue);
					texLoadQueue->texName = mapTexList->texName;
				}
				if (texLoadQueue->texName == mapTexList->texName) {
					break;
				}
				texLoadQueue = texLoadQueue->next;
			} while (texLoadQueue != nullptr);
			if (texLoadQueue == nullptr) {
				list::AddNode<Obj>(&texLoadQueue);
				texLoadQueue->texName = mapTexList->texName;
				texLoadQueue = texLoadQueue->next;
			}
			mapTexList = mapTexList->next;
		} while (mapTexList != nullptr);
	}
	
	do {
		Obj* tileItr = targetMap->roomList->tileList;
		do {
			if (texLoadQueue->texName == tileItr->texName) {
				int w, h;
				SDL_GetWindowSize(window, &w, &h);
				SDL_Rect* tmpRect = new SDL_Rect();
				tmpRect->x = offX;
				tmpRect->y = offY;
				tmpRect->w = w;
				tmpRect->h = h;
				if (collision::DoubleBoxCollision(&tileItr->rect, tmpRect)) {
					Texture* loadItr = loadedTextures;
					if (loadItr != nullptr) {
						do {
							if (loadItr->texName == texLoadQueue->texName) {
								break;
							}
							loadItr = loadItr->next;
						} while (loadItr != nullptr);
						if (loadItr == nullptr) {
							list::AddNode<Texture>(&loadedTextures);
							loadedTextures->texName = texLoadQueue->texName;
							loadedTextures->tex = ImgLoad(texLoadQueue->texName.c_str());
							list::DeleteNode(&texLoadQueue, &texLoadQueue);
						}
					}
					else {
						list::AddNode<Texture>(&loadedTextures);
						loadedTextures->texName = texLoadQueue->texName;
						loadedTextures->tex = ImgLoad(texLoadQueue->texName.c_str());
						list::DeleteNode(&texLoadQueue, &texLoadQueue);
					}
					break;
				}
			}
			tileItr = tileItr->next;
		} while (tileItr != nullptr);
		if (texLoadQueue != nullptr && tileItr == nullptr) {
			list::DeleteNode(&texLoadQueue, &texLoadQueue);
		}
	} while (texLoadQueue != nullptr);


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
	SDL_RenderClear(renderer);

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

		tmpRect.w = (int)ceil(float(tileItr->rect.w) * scale);
		tmpRect.h = (int)ceil(float(tileItr->rect.h) * scale);
		tmpRect.x = (int)floor(float(tileItr->rect.x - offX) * scale + (scrW / 2));
		tmpRect.y = (int)floor(float(tileItr->rect.y - offY) * scale + (scrH / 2));

		// next make a relative coord system and move the camera
		// then add scaling of camera
		// test multiple rooms
		if (tmpTex == nullptr) {
			printf("tmpTex is null\n");
		}
		SDL_RenderCopy(renderer, tmpTex, NULL, &tmpRect);
		tileItr = (Tile*)tileItr->next;
	} while (tileItr != nullptr);
	SDL_RenderPresent(renderer);
}
