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
	}
}
int VirtToReal(int in, bool width) {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return (int)floor(float(in - (width ? offX : offY)) * scale + ((width ? w : h) / 2)); // virtual to real
}
int RealToVirt(int in, bool width) {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return (int)(((float)in + floor((float)(width ? offX : offY) * scale - ((width ? w : h) / 2))) / scale);
}
int VirtualSize(int size) {
	return (int)ceil(float(size) * scale);
}
void RenderWindow() {
	//add map tilelist to loadedtexture
	Obj* texItr = targetMap->texList;
	if (texItr != nullptr) {
		do {
			AddToLoaded(texItr->texName);
			texItr = texItr->next;
		} while (texItr != nullptr);
	}
	

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
			Actor* actorItr = targetMap->actorList;
			if (tileItr != nullptr) {
				do 
				{
					if (tileItr->texName == loadedItr->texName) {
						if (tileItr->IsInView()) {
							if (loadedItr->tex == nullptr) {
								loadedItr->tex = ImgLoad(loadedItr->texName.c_str());
							}
							goto jump;
						}
					}
					tileItr = (Tile*)tileItr->next;
				} while (tileItr != nullptr);
			}
			if (actorItr != nullptr) {
				do {
					if (actorItr->texName == loadedItr->texName && actorItr->IsInView()) {
						if (loadedItr->tex == nullptr) {
							loadedItr->tex = ImgLoad(loadedItr->texName.c_str());
						}
						break;
					}
				actorItr = (Actor*)actorItr->next;
				} while (actorItr != nullptr);
			}
			jump:;
			if (tileItr == nullptr && actorItr == nullptr) {
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
		if (texLoop != nullptr) {
			do {
				if (tileItr->IsInView()) {
					if (texLoop->texName == tileItr->texName) {
						tmpTex = texLoop->tex;
						break;
					}
				}
				texLoop = texLoop->next;
			} while (texLoop != nullptr);
			int w, h;
			SDL_GetWindowSize(window, &w, &h);
			tmpRect = tileItr->rect;
		}
		else {
			//printf("no textures to load\n");
			SDL_RenderPresent(renderer);
			return;
		}
		int scrW, scrH;
		SDL_GetWindowSize(window, &scrW, &scrH);
		tmpRect.w = VirtualSize(tileItr->rect.w);
		tmpRect.h = VirtualSize(tileItr->rect.h);
		tmpRect.x = VirtToReal(tileItr->rect.x, 1);
		tmpRect.y = VirtToReal(tileItr->rect.y, 0);
		// next make a relative coord system and move the camera
		// then add scaling of camera
		// test multiple rooms
		if (tmpTex == nullptr) {
			//printf("tmpTex is null\n");
		}
		SDL_RenderCopy(renderer, tmpTex, NULL, &tmpRect);
		tileItr = (Tile*)tileItr->next;
	} while (tileItr != nullptr);
	Actor* actorItr = targetMap->actorList;
	if (actorItr != nullptr) {
		do {
			Texture* texItr = loadedTextures;
			if (texItr != nullptr) {
				do {
					if (actorItr->IsInView() && texItr->texName == actorItr->texName) {
						break;
					}
					texItr = texItr->next;
				} while (texItr != nullptr);
				if (texItr == nullptr) {
					printf("LoadedTextures didn't contain the required texture for the actor\n");
				}else {
					SDL_Rect tmpRect;
					tmpRect.w = VirtualSize(actorItr->rect.w);
					tmpRect.h = VirtualSize(actorItr->rect.h);
					tmpRect.x = VirtToReal(actorItr->rect.x, 1);
					tmpRect.y = VirtToReal(actorItr->rect.y, 0);
					SDL_RenderCopy(renderer, texItr->tex, NULL, &tmpRect);
				}
			}
			else {
				printf("loadedTexture is empty\n");
				SDL_RenderPresent(renderer);
				return;
			}
			actorItr = (Actor*)actorItr->next;
		} while (actorItr != nullptr);
	}
	

	SDL_RenderPresent(renderer);
}
