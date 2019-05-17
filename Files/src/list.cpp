#include "../header/list.h"

 void list::UniqueCpyStr(Obj** src, Obj** dst) {
	Obj* srcItr = *src;
	do {
		Obj** dstItr = dst;
		do {
			if (*dstItr == nullptr) {
				list::AddNode<Obj>(*dstItr);
				(*dst)->texName = (*src)->texName;
				break;
			}
			if (srcItr->texName == (*dstItr)->texName) {
				break;
			}
			*dstItr = (*dstItr)->next;
		} while (dstItr != nullptr);
		if (dstItr == nullptr) {
			list::AddNode<Obj>(*dstItr);
			(*dst)->texName = (*src)->texName;
		}

		srcItr = srcItr->next;
	} while (srcItr != nullptr);
}
//template <typename T> T* list::AddNode(T*& target) {
//	T* tmpnt = new T();
//
//	if (target != nullptr) {
//		tmpnt->next = target;
//	}
//	target = tmpnt;
//	return tmpnt;
//}
//template <typename T> T* list::DeleteNode(T*& tarList, T*& target) {
//	T* tmpnt = target;
//	if (tarList == target && target->next != nullptr) {
//		tarList = (T*)target->next;
//	}
//	else if (tarList == target && target->next == nullptr) {
//		tarList = nullptr;
//	}
//	else {
//		T* inc = tarList;
//		while (inc->next != target) {
//			inc = (T*)inc->next;
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