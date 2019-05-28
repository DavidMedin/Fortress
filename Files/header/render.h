#pragma once
#include "data.h"


void AddToLoaded(string path);
int VirtToReal(int in, bool width);
int RealToVirt(int in, bool width);
int VirtualSize(int size);
void RenderWindow();