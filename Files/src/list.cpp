#include "../header/list.h"

//template <class T> T* list::AddNode(T*& target) {
//	
//	T* tmpnt = new T();
//
//	if (target != nullptr) {
//		tmpnt->next = target;
//	}
//	target = tmpnt;
//	return tmpnt;
//}

//template <class T> T* list::DeleteNode(T* &tarList,T* &target) {
//	T* tmpnt = target;
//	if (tarList == target && target->next != nullptr) {
//		tarList = target->next;
//	}
//	else if (tarList == target && target->next == nullptr) {
//		tarList = nullptr;
//	}
//	else {
//		T* inc = tarList;
//		while (inc->next != target) {
//			inc = inc->next;
//		}
//		if (target->next == nullptr) {
//			inc->next = nullptr;
//		}
//		else {
//			inc->next = target->next;
//		}
//	}
//	delete target;
//	return target;
//}