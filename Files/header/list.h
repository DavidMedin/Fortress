#pragma once
#include "Obj.h"
namespace list {
	void UniqueCpyStr(Obj** src, Obj** dst);
	template <typename T> T* AddNode(T*& target) {
		T* tmpnt = new T();

		if (target != nullptr) {
			tmpnt->next = target;
		}
		target = tmpnt;
		return tmpnt;
	}
	template <typename T> T* DeleteNode(T*& tarList, T*& target) {
		T* tmpnt = target;
		if (tarList == target && target->next != nullptr) {
			tarList = (T*)target->next;
		}
		else if (tarList == target && target->next == nullptr) {
			tarList = nullptr;
		}
		else {
			T* inc = tarList;
			while (inc->next != target) {
				inc = (T*)inc->next;
			}
			if (target->next == nullptr) {
				inc->next = nullptr;
			}
			else {
				inc->next = target->next;
			}
		}
		delete target;
		return target;
	}
}