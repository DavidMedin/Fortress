#include "../header/render.h"

void RenderWindow() {
	
	Obj* mapTileItr = targetMap->roomList->tileList;
	do {
		Obj* queue = texLoadQueue;
		do {
			if (texLoadQueue == nullptr) {
				list::AddNode<Obj>(texLoadQueue);
				texLoadQueue->texName = mapTileItr->texName;
				break;
			}
			if (mapTileItr->texName == queue->texName) {
				break;
			}
			queue = queue->next;
		} while (queue != nullptr);
		if (queue == nullptr) {
			list::AddNode<Obj>(texLoadQueue);
			texLoadQueue->texName = mapTileItr->texName;
		}
		mapTileItr = mapTileItr->next;
	} while (mapTileItr != nullptr);

	bool used;
	Obj* texItr = texLoadQueue;
	do {
		used = false;
		Obj* mapTileItr = targetMap->roomList->tileList;
		do {
			if (mapTileItr->texName == texItr->texName) {
				SDL_Point tmpPoint = { mapTileItr->rect.x,mapTileItr->rect.y };
				int w, h;
				SDL_GetWindowSize(window, &w, &h);
				SDL_Rect tmpRect = { offX,offY,w,h };
				printf("%s, %s\n", collision::BoxPointCollision(&tmpRect, &tmpPoint) ? "True" : "False",mapTileItr->texName.c_str());
				if (collision::BoxPointCollision(&tmpRect, &tmpPoint)) {
					used = true;
					break;
				}
			}
			
			mapTileItr = mapTileItr->next;
		} while (mapTileItr != nullptr);
		if (used == true) {
			//list::AddNode<Texture>(loadedTextures);
			Texture* test = new Texture();
			loadedTextures->tex = ImgLoad(texItr->texName.c_str());
			loadedTextures->texName = texItr->texName;
		}
		Obj* next = texItr->next;
		list::DeleteNode(texLoadQueue, texItr);
		texItr = next;
	} while (texItr != nullptr);



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




		static bool lazy = false;
		if (lazy == false) {
			int targetLength = targetRoom->width > targetRoom->height ? targetRoom->width : targetRoom->height;
			scale = float((targetRoom->width == targetLength ? w : h)) / float(targetLength);
			lazy = true;
		}

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
