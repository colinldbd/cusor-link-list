//the implement of a linklist stored by cursor
//this structure can avoid the error in some language that don't support pointer
//cursor is a replacement of the pointer
#include <iostream>

#define CursorSpace 100
#define ElementType int

using namespace std;

typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

void InitializeCursorList(void);
List MakeEmpty(List L);
int isEmpty(List L);
int isLast(List L, Position P);
void Insert(List L, Position P, ElementType X);
void Delete(List L, ElementType X);
Position Find(List L, ElementType X);
Position FindPrevious(List L, ElementType X);
void DeleteList(List L);

struct Node {
	ElementType X;
	Position Next;
};

struct Node CursorList[CursorSpace];

int isEmpty(List L) {
	return CursorList[L].Next == 0;
}

int isLast(List L, Position P) {
	return CursorList[P].Next == 0;
}

void InitializeCursorList(void) {
	int i = 0;
	for (i = 0; i < CursorSpace; i++) {
		CursorList[i].Next = i + 1;
	}
	CursorList[CursorSpace - 1].Next = 0;
}

Position CursorAlloc() {
	Position P;
	P = CursorList[0].Next;
	CursorList[0].Next = CursorList[P].Next;
	CursorList[P].Next = 0;
	return P;
}

void CursorFree(Position P) {
	CursorList[P].Next = CursorList[0].Next;
	CursorList[0].Next = P;
}

Position Find(List L, ElementType X) {
	Position P = CursorList[L].Next;
	while (CursorList[P].X != X && P) {
		P = CursorList[P].Next;
	}
	if (P == 0) {
		return false;
	}
	return P;
}

Position FindPrevious(List L, ElementType X) {
	Position P = L;
	Position tmp = CursorList[P].Next;
	while (CursorList[tmp].X != X && tmp) {
		tmp = CursorList[tmp].Next;
		P = CursorList[P].Next;
	}
	return P;
}

void Delete(List L, ElementType X) {
	Position P = FindPrevious(L, X);
	Position tmp = CursorList[P].Next;
	CursorList[P].Next = CursorList[tmp].Next;
}

void Insert(List L, Position P, ElementType X) {
	Position tmp;
	tmp = CursorAlloc();
	CursorList[tmp].X = X;
	CursorList[tmp].Next = CursorList[P].Next;
	CursorList[P].Next = tmp;
}

void DeleteList(List L) {
	Position P = CursorList[L].Next;
	Position tmp = P;
	while (tmp != 0) {
		P = CursorList[P].Next;
		CursorFree(tmp);
		if (P == 0) {
			break;
		}
		tmp = P;
	}
	CursorList[L].Next = 0;
}

void Print(List L) {
	Position P = CursorList[L].Next;
	while (P != 0) {
		printf("%d ", CursorList[P].X);
		P = CursorList[P].Next;
	}

	printf("\n");
}

int main(int argc, const char * argv[])
{

	printf("start ...\n");
	InitializeCursorList();
	List L = CursorAlloc();
	Insert(L, L, 1);
	Insert(L, L, 3);
	Insert(L, L, 5);
	Insert(L, L, 4);
	Print(L);
	Position P = FindPrevious(L, 3);
	printf("%d\n", P);
	Delete(L, 3);
	Print(L);
	DeleteList(L);
	Print(L);
	getchar();
	return 0;
}
