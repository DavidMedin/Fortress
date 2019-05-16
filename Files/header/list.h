#pragma once
#include "Data.h"



namespace list {
	void UniqueCpyStr(Obj* src, Obj* dst);
	template <typename T> T* AddNode(T*& target);
	template <typename T> T* DeleteNode(T*& tarList, T*& target);
}