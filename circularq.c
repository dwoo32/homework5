#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //MAX_QUEUE_SIZE 4로 정의

typedef char element;//char타입 element선언
typedef struct //구조체 정의
{//구조체 멤버정의
	element queue[MAX_QUEUE_SIZE];//배열 queue[MAX_QUEUE_SIZE]로 선언
	int front, rear;//int형 변수 front, rear 선언
}QueueType;


QueueType *createQueue();//반환값이 QueueType에 저장될 큐생성 함수 선언
int freeQueue(QueueType *cQ);//메모리 해제하는 freeQueue 함수 선언
int isEmpty(QueueType *cQ);//큐가 비었는지 확인하는 함수 선언
int isFull(QueueType *cQ);//큐가 가득 찼는 지 확인하는 함수 선언
void enQueue(QueueType *cQ, element item);//큐에 데이터 입력받는 enQueue함수 선언
void deQueue(QueueType *cQ, element* item);//큐에 저장된 데이터 삭제하는 deQueue함수 선언
void printQ(QueueType *cQ);//큐 출력하는 함수 선언
void debugQ(QueueType *cQ);//현재 큐의 상태를 보여주는 함수 선언
element getElement();//배열의 요소를 입력받는 함수 선언


int main(void)
{
    
	QueueType *cQ = createQueue();//구조체QueueType의 *cQ에 createQueue함수의 반환값 할당
	element data;//data를 문자형배열의 요소 element 선언

	char command;//char형 변수 command 선언

	do{//메뉴 출력
        
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//입력받은 값 저장할 변수command 선언

		switch(command) {
		case 'i': case 'I'://i 대소문자 입력받았을 때
			data = getElement();//data에 getElement함수 리턴값 할당
			enQueue(cQ, data);//enQueue 함수 호출
			break;
		case 'd': case 'D'://d 대소문자 입력받았을 때
			deQueue(cQ,&data);//deQueue 함수 호출
			break;
		case 'p': case 'P'://p 대소문자 입력받았을 때
			printQ(cQ);//printQ함수 호출
			break;
		case 'b': case 'B'://b 대소문자 입력받았을 때
			debugQ(cQ);//debugQ함수 호출
			break;
		case 'q': case 'Q'://q 대소문자 입력받았을 때
			break;//종료
		default://case에 없는 문자를 입력받았을 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q 대소문자 입력받기 전까지 반복
    printf("[----- [Kimdongwoo] [2020039058] -----]\n");


	return 1;
}

QueueType *createQueue()//createQueue함수 정의
{
	QueueType *cQ;//*cQ를 QueueType으로 선언
	cQ = (QueueType *)malloc(sizeof(QueueType));//cQ에 QueueType의 크기만큼 동적메모리 할당
	cQ->front = 0;//cQ의 front 0으로 초기화
	cQ->rear = 0;//cQ의 rear 0으로 초기화
	return cQ;//cQ반환
}

int freeQueue(QueueType *cQ)//int형 freeQueue 함수 정의
{
    if(cQ == NULL) return 1;//cQ가 비어있을 때 1리턴
    free(cQ);//cQ에 할당되어있던 메모리 해제
    return 1;//1 리턴
}

element getElement()//getElement 함수 정의
{
	element item;//item을 element로 선언
	printf("Input element = ");
	scanf(" %c", &item);//입력받은 값 item에 할당
	return item;//item 리턴
}


int isEmpty(QueueType *cQ)//int형 isEmpty 함수 정의
{
	if (cQ->front == cQ->rear){//만약 cQ의 front와 rear가 같다면
		printf("Circular Queue is empty!");//원형큐가 비었음을 출력
		return 1;
	}
	else return 0;//아닌 경우라면 0 반환
}

int isFull(QueueType *cQ)//int형 isFull함수 정의
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {//cQ의 rear를 1증가시킨 값이 cQ의 front와 같다면
		printf(" Circular Queue is full!");//원형큐가 꽉 차있음을 출력
		return 1;
	}
	else return 0;//아닌 경우라면 0 반환
}

void enQueue(QueueType *cQ, element item)//cQ에 데이터 입력받는 함수 정의
{
	if(isFull(cQ)) return;//isFull 함수에서 1이 반환되면 리턴
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;//rear++
		cQ->queue[cQ->rear] = item;//증가된 rear에 item 할당
	}
}

void deQueue(QueueType *cQ, element *item)//cQ에 저장된 데이터를 삭제하는 함수 정의
{
	if(isEmpty(cQ)) return;//isEmpty 함수에서 1이 반환되면 리턴
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;//front++
		*item = cQ->queue[cQ->front];//item의 주소가 가르키는 곳에 cQ의 front 값을 할당
		return;
	}
}


void printQ(QueueType *cQ)//cQ를 출력하는 함수 정의
{
	int i, first, last;//int형 변수 i,first,last 선언

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;//first 증가
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;//last 증가

	printf("Circular Queue : [");//원형 큐 출력

	i = first;//i에 first 할당
	while(i != last){//i가 last가 아닐 동안
		printf("%3c", cQ->queue[i]);//queue[i] 출력
		i = (i+1)%MAX_QUEUE_SIZE;//i++

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)//cQ의 현재상태 출력해주는 함수
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)//i=0, i가 MAX_QUEUE_SIZE보다 작을 때까지 반복
	{
		if(i == cQ->front) {//i가 cQ의 front와 같다면
			printf("  [%d] = front\n", i);//i값 출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front,rear의 위치 출력
}



