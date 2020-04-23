/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;                                                         // char형의 별칭을 element라 선언
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();                                                     // 동적할당해주는 함수
int isEmpty(QueueType *cQ);                                                   // 원형 큐가 비어있는지 확인해 주는 함수
int isFull(QueueType *cQ);                                                    // 원형 큐가 차있는지 확인해 주는 함수
void enQueue(QueueType *cQ, element item);                                    // 원형 큐에 data를 삽입해주는 함수
void deQueue(QueueType *cQ, element* item);                                   // 원형 큐에 있는 data를 삭제하는 함수( 먼저 들어간 data부터 삭제 )
void printQ(QueueType *cQ);                                                   // 원형 큐에 들어가있는 data를 출력해주는 함수
void debugQ(QueueType *cQ);                                                   // 원형 큐에서 front, rear의 위치와, 각 인덱스 별 data를 확인해 주는 함수
int FreeQ(QueueType *cQ);                                                     // 원형 큐의 동적할당을 해제하는 함수
void MakeNULL(QueueType *cQ);                                                 // 프로그램 실행시 원형 큐에 debugQ를 할시 data값에 ?가 출력되어 이를 초기화 하는 함수

element getElement();                                                         // 원형 큐에 삽입할 data를 입력받는 함수


int main(void)
{
	QueueType *cQ = createQueue();                                            // cQ에다 동적할당을 통해 원형 큐를 생성해 준다  
	element data;
	MakeNULL(cQ);
	char command;
	printf("2019038068 김성욱\n");
	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);                                               // 실행할 명령어를 입력받는다

		switch (command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			if (!FreeQ(cQ)) {
				printf("Error : demallocation was filled");
			}
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue()                                                      // 동적할당해주는 함수                                
{
	QueueType *cQ=NULL;        
	cQ = (QueueType *)malloc(sizeof(QueueType));                              // 동적할당 
	cQ->front = 0;                                                            // front값 초기화
	cQ->rear = 0;                                                             // rear값 초기화 
	return cQ;
}

element getElement()                                                          // 원형 큐에 삽입할 data를 입력받는 함수
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)                                                    // 원형 큐가 비어있는지 확인해 주는 함수
{
	if (cQ->rear == cQ->front) {                                              // 비어있는 조건 : rear의 값과 front의 값이 같을 경우
		return 1;
	}
	return 0;
}

/* complete the function */
int isFull(QueueType *cQ)                                                     // 원형 큐가 차있는지 확인해 주는 함수
{
	int r = (cQ->rear + 1) % MAX_QUEUE_SIZE;                                  // rear가 현재 위치하는 인덱스 +1 % MAX_QUEUE_SIZE를 했을때의 인댁스 값이
	if (r == cQ->front) {                                                     // front의 인덱스 값과 같다면 원형큐가 다 차있다는 것을 의미한다, 가득 차있는 조건 : rear +1 == front인 경우
		return 1;
	}
	return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)                                     // 원형 큐에 data를 삽입해주는 함수  
{
	if (!(isFull(cQ))) {                                                      // 원형 큐가 다 차있는지 검사
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;                           // rear의 값를 +1한다음 MAX_QUEUE_SIZE로 나누어 다음 인덱스로 이동
		cQ->queue[cQ->rear] = item;                                           // rear가 가리키는 위치에 data 삽입
	}
	else {
		printf("CircularQ is Already Full\n");                                // 원형 큐가 꽉찼을 경우 Error 메시지 출력
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)                                    // 원형 큐에 있는 data를 삭제하는 함수( 먼저 들어간 data부터 삭제 )
{
	if (!(isEmpty(cQ))) {                                                     // 원형 큐가 비어있는지 검사
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;                         // front의 값을 +1한다음 MAX_QUEUE_SIZE로 나누어 다음 인덱스로 이동
		*item = cQ->queue[cQ->front];                                         // item에 front가 가리키는 곳의 data 넣기
		printf("Delete %c\n", *item);                                         
		cQ->queue[cQ->front] = NULL;                                          // front가 가리키는 곳을 NULL로 초기화, 실제 data를 삭제할 수 없으므로, NULL로 초기화한다
	}
	else {
		printf("CircularQ is Already Empty\n");                               // 원형 큐가 비어있을 경우 Erro 메시지 출력 
	}
}


void printQ(QueueType *cQ)                                                    // 원형 큐에 들어가있는 data를 출력해주는 함수
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;                                 // 존제하는 data중 들어간 순서가 가장 빠른 data의 위치를 가리킨다
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;                                   // 원형큐의 끝부분, 즉 원형 큐에서 data가 다 찼다는 것을 판단하기 위해 data를 체우지 않는 공간의 위치를 나타낸다, 즉, 마지막 data의 인덱스 위치 +1을 가리킨다

	printf("Circular Queue : [");

	i = first;
	while (i != last) {                                                       // first : 가장 먼저 들어간 data의 인덱스, last : 가장 나중에 들어간 data의 인덱스 +1 
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;                                         // 다음 인덱스로 i값 이동

	}
	printf(" ]\n");
}

  
void debugQ(QueueType *cQ)                                                    // 원형 큐에서 front, rear의 위치와, 각 인덱스 별 data를 확인해 주는 함수
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)                                  // 0부터 MAX_QUEUE_SIZE까지 반복
	{
		if (i == cQ->front) {                                                 // 인덱스의 값이 front의 값과 같다면 
			printf("  [%d] = front\n", i);                                    // front 출력( 원형 큐의 특성상 비어있는 상태와 가득찬 상태를 구분하기 위해 한개의 공간을 비워둘수 밖에 없으므로 가능 )
			continue;                   
		} 
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

int FreeQ(QueueType *cQ) {                                                    // 원형 큐의 동적할당을 해제하는 함수
	if (cQ == NULL) {                                                         // cQ가 NULL일 경우 해제할 공간이 없으므로 오류 메시지 출력
		return 0;
	}
	free(cQ);                                                                 // cQ에 동적할당된 공간을 free를 통해 해제
	return 1;
}

void MakeNULL(QueueType *cQ) {                                                // 프로그램 실행시 원형 큐에 debugQ를 할시 data값에 ?가 출력되어 이를 초기화 하는 함수
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		cQ->queue[i] = NULL;                                                  // 초기의 모든 index의 값을 NULL로 초기화
	}
}