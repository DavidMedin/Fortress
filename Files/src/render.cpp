#include "../header/render.h"
void RenderWindow() {
	// fetching and adding the unique textures and putting them into the correct texture lsit
	Obj* texItr = targetMap->texList;
	do {
		Texture* mapLoadItr = mapLoadTexes;
		if (mapLoadTexes != nullptr) {
			do {
				if (mapLoadTexes->texName->texName == texItr->texName) {
					break;
				}
				mapLoadItr = mapLoadItr->next;
			} while (mapLoadItr != nullptr);
		}
		if (mapLoadItr == nullptr) {
			list::AddNode<Texture>(mapLoadTexes);
			mapLoadTexes->texName = new Obj();
			mapLoadTexes->texName->texName = texItr->texName;
			mapLoadTexes->tex = ImgLoad(texItr->texName.c_str());
		}

		texItr = texItr->next;
	} while (texItr != nullptr);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
	SDL_RenderClear(renderer);

	//map rendering
	// w / roomW * ScreenWidth
	SDL_Rect tmpRect;

	Tile * tileItr = targetRoom->tileList;
	do {
		SDL_Texture* tmpTex = nullptr;
		Texture* texLoop = mapLoadTexes;
		do {
			if (texLoop->texName->texName == tileItr->texName) {
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
