#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {//Node 구조체 선언
	int key;//int형 변수 key선언
	struct Node* link;//Node 구조체의 포인터 link 선언
} listNode;//typedef를 통해 listNode 구조체 정의

typedef struct Head {//Head 구조체 선언
	struct Node* first;//Head 구조체의 포인터 first 선언
} headNode;//typedef를 통해 headNode 구조체 정의


/* 함수 리스트 */
headNode* initialize(headNode* h);/*headNode 포인터를 매개인자로 받아 연결리스트의 헤드 노드를 초기화하고, 
                                   초기화된 헤드 노드를 가리키는 포인터를 반환하는 initialize함수*/
int freeList(headNode* h);//headNode 포인터를 매개인자로 받는 int형 함수 freeList

int insertFirst(headNode* h, int key);//headNode 포인터와 int형 변수 key를 매개인자로 받는 int형 함수 insertFirst
int insertNode(headNode* h, int key);//headNode 포인터와 int형 변수 key를 매개인자로 받는 int형 함수 insertNode
int insertLast(headNode* h, int key);//headNode 포인터와 int형 변수 key를 매개인자로 받는 int형 함수 insertLast

int deleteFirst(headNode* h);//headNode 포인터를 매개인자로 받는 int형 함수 deleteFirst
int deleteNode(headNode* h, int key);//headNode 포인터와 int형 변수 key를 매개인자로 받는 int형 함수 deleteNode
int deleteLast(headNode* h);//headNode 포인터를 매개인자로 받는 int형 함수 deleteLast
int invertList(headNode* h);//headNode 포인터를 매개인자로 받는 int형 함수 invertList

void printList(headNode* h);//headNode 포인터를 매개인자로 받는 함수 printList

int main()
{
	char command;//char형 변수 command 선언
	int key;//int형 변수 key 선언
	headNode* headnode=NULL;//headNode 포인터 headnode 선언 후 null로 초기화

	do{//menu 출력
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf("-------------------[Kimdongwoo] [2020039058]--------------------\n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");//command 입력을 받기 위한 출력
		scanf(" %c", &command);//입력받은 키 command에 저장

		switch(command) {//command에 따른 switch 조건문
		case 'z': case 'Z'://z 대소문자 입력 받았을 때
			headnode = initialize(headnode);//headnode에 초기화한 headnode값 할당
			break;
		case 'p': case 'P'://p 대소문자 입력 받았을 때
			printList(headnode);//headnode를 매개인자로 받는 printList함수 출력
			break;
		case 'i': case 'I'://i 대소문자 입력받았을 때
			printf("Your Key = ");//key입력을 위한 출력
			scanf("%d", &key);//입력받은 값 key변수에 할당
			insertNode(headnode, key);//headnode와 입력받은 key값을 매개인수로 inserNode 함수 실행
			break;
		case 'd': case 'D'://d 대소문자 입력받았을 때
			printf("Your Key = ");//key입력을 위한 출력
			scanf("%d", &key);//입력받은 값 key변수에 할당
			deleteNode(headnode, key);//headnode와 입력받은 key값을 매개인수로 deleteNOde함수 실행
			break;
		case 'n': case 'N'://n 대소문자 입력받았을 때
			printf("Your Key = ");//key입력을 위한 출력
			scanf("%d", &key);//입력받은 값 key변수에 할당
			insertLast(headnode, key);//headnode와 입력받은 key값을 매개인수로 insertLast함수 실행
			break;
		case 'e': case 'E':// e 대소문자 입력받았을 때
			deleteLast(headnode);//headenode를 매개인자로 deleteLast 함수 실행
			break;
		case 'f': case 'F':// f 대소문자 입력받았을 때
			printf("Your Key = ");//key입력을 위한 출력
			scanf("%d", &key);//입력받은 값 key변수에 할당
			insertFirst(headnode, key);//headnode와 key를 매개인수로 insertFirst함수 실행
			break;
		case 't': case 'T'://t 대소문자 입력받았을 때
			deleteFirst(headnode);//headnode를 매개인자로 deleteFirst 함수 실행
			break;
		case 'r': case 'R'://r 대소문자 입력받았을 때
			invertList(headnode);//headnode를 매개인자로 invertList 함수 실행
			break;
		case 'q': case 'Q':// q 대소문자 입력받았을 때
			freeList(headnode);//headnode를 매개인자로 freeList 함수 실행
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q가 입력되지 않은 동안 반복

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)//headNode h가 NULL이 아니면
		freeList(h);//할당된 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));//headNode의 크기만큼 temp에 저장
	temp->first = NULL;//temp의 first에 NULL 저장
	return temp;//temp 리턴
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;//listNode의 포인터 p선언 후 h를 통해 first 노드를 p에 할당

	listNode* prev = NULL;//listNode의 포인터 prev 선언 후 NULL값 할당
	while(p != NULL) {//p가 NULL이 아닐동안
		prev = p;//prev에 p값 할당
		p = p->link;//p의 link를 p에 할당
		free(prev);//할당된 prev 메모리 해제
	}
	free(h);//할당된 h 메모리 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//listNode의 크기 만큼 listNode의 포인터 node에 메모리 할당
	node->key = key;//node의 key에 key 할당
	node->link = NULL;//node의 link에 NULL 값 할당

	if (h->first == NULL)//h의 first가 NULL이라면
	{
		h->first = node;//h의 first에 node 할당
		return 0;
	}

	listNode* n = h->first;//listNode의 포인터 n에 h의 first 값 할당
	listNode* trail = h->first;//listNode의 포인터 trail에 h의 first 값 할당

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {//n이 NULL이 아닐동안
		if(n->key >= key) {//n의 key가 key보다 크거나 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {//n이 h의 first와 같다면
				h->first = node;//h의 first에 node값 할당
				node->link = n;//node의 link에 n값 할당
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;//node의 link에 n값 할당
				trail->link = node;//trail의 link에 node 값 할당
			}
			return 0;
		}

		trail = n;//trail에 n값 할당
		n = n->link;//n에 n의 link값 할당
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;//trail의 link에 node 삽입
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//listNode의 크기만큼 listNode의 포인터 node에 메모리 할당
	node->key = key;//node의 key에 key값 할당
	node->link = NULL;//node의 link에 NULL값 할당

	if (h->first == NULL)//h의 first가 NULL이라면
	{
		h->first = node;//h의 first에 node 값 할당
		return 0;
	}

	listNode* n = h->first;//listNode의 포인터 n에 h의 first 값 할당
	while(n->link != NULL) {//
		n = n->link;
	}
	n->link = node;
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;
	free(n);

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;
	free(n);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

