#pragma once
#include "Obj.h"
namespace list {
	template <typename T> T* AddNode(T*& target) {
		T* tmpnt;
		try {
			tmpnt = new T();
		}
		catch (const std::exception e) {
			tmpnt = new T;
		}

		if (target != nullptr) {
			tmpnt->next = target;
		}
		target = tmpnt;
		return tmpnt;
	}
	template <typename T> T* DeleteNode(T** tarList, T** target) {
		T** tmpnt = *target;
		// finish pointer pointers, then use tmpnt to 'tag' the target to delete
		if (tarList == *target && target->next != nullptr) {
			T* test = (T*)target->next;
			tarList = (T*)target->next;
			printf(" ");
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