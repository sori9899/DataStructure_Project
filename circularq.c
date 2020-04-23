/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;                                                         // char���� ��Ī�� element�� ����
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();                                                     // �����Ҵ����ִ� �Լ�
int isEmpty(QueueType *cQ);                                                   // ���� ť�� ����ִ��� Ȯ���� �ִ� �Լ�
int isFull(QueueType *cQ);                                                    // ���� ť�� ���ִ��� Ȯ���� �ִ� �Լ�
void enQueue(QueueType *cQ, element item);                                    // ���� ť�� data�� �������ִ� �Լ�
void deQueue(QueueType *cQ, element* item);                                   // ���� ť�� �ִ� data�� �����ϴ� �Լ�( ���� �� data���� ���� )
void printQ(QueueType *cQ);                                                   // ���� ť�� ���ִ� data�� ������ִ� �Լ�
void debugQ(QueueType *cQ);                                                   // ���� ť���� front, rear�� ��ġ��, �� �ε��� �� data�� Ȯ���� �ִ� �Լ�
int FreeQ(QueueType *cQ);                                                     // ���� ť�� �����Ҵ��� �����ϴ� �Լ�
void MakeNULL(QueueType *cQ);                                                 // ���α׷� ����� ���� ť�� debugQ�� �ҽ� data���� ?�� ��µǾ� �̸� �ʱ�ȭ �ϴ� �Լ�

element getElement();                                                         // ���� ť�� ������ data�� �Է¹޴� �Լ�


int main(void)
{
	QueueType *cQ = createQueue();                                            // cQ���� �����Ҵ��� ���� ���� ť�� ������ �ش�  
	element data;
	MakeNULL(cQ);
	char command;
	printf("2019038068 �輺��\n");
	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);                                               // ������ ��ɾ �Է¹޴´�

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


QueueType *createQueue()                                                      // �����Ҵ����ִ� �Լ�                                
{
	QueueType *cQ=NULL;        
	cQ = (QueueType *)malloc(sizeof(QueueType));                              // �����Ҵ� 
	cQ->front = 0;                                                            // front�� �ʱ�ȭ
	cQ->rear = 0;                                                             // rear�� �ʱ�ȭ 
	return cQ;
}

element getElement()                                                          // ���� ť�� ������ data�� �Է¹޴� �Լ�
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)                                                    // ���� ť�� ����ִ��� Ȯ���� �ִ� �Լ�
{
	if (cQ->rear == cQ->front) {                                              // ����ִ� ���� : rear�� ���� front�� ���� ���� ���
		return 1;
	}
	return 0;
}

/* complete the function */
int isFull(QueueType *cQ)                                                     // ���� ť�� ���ִ��� Ȯ���� �ִ� �Լ�
{
	int r = (cQ->rear + 1) % MAX_QUEUE_SIZE;                                  // rear�� ���� ��ġ�ϴ� �ε��� +1 % MAX_QUEUE_SIZE�� �������� �δ콺 ����
	if (r == cQ->front) {                                                     // front�� �ε��� ���� ���ٸ� ����ť�� �� ���ִٴ� ���� �ǹ��Ѵ�, ���� ���ִ� ���� : rear +1 == front�� ���
		return 1;
	}
	return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)                                     // ���� ť�� data�� �������ִ� �Լ�  
{
	if (!(isFull(cQ))) {                                                      // ���� ť�� �� ���ִ��� �˻�
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;                           // rear�� ���� +1�Ѵ��� MAX_QUEUE_SIZE�� ������ ���� �ε����� �̵�
		cQ->queue[cQ->rear] = item;                                           // rear�� ����Ű�� ��ġ�� data ����
	}
	else {
		printf("CircularQ is Already Full\n");                                // ���� ť�� ��á�� ��� Error �޽��� ���
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)                                    // ���� ť�� �ִ� data�� �����ϴ� �Լ�( ���� �� data���� ���� )
{
	if (!(isEmpty(cQ))) {                                                     // ���� ť�� ����ִ��� �˻�
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;                         // front�� ���� +1�Ѵ��� MAX_QUEUE_SIZE�� ������ ���� �ε����� �̵�
		*item = cQ->queue[cQ->front];                                         // item�� front�� ����Ű�� ���� data �ֱ�
		printf("Delete %c\n", *item);                                         
		cQ->queue[cQ->front] = NULL;                                          // front�� ����Ű�� ���� NULL�� �ʱ�ȭ, ���� data�� ������ �� �����Ƿ�, NULL�� �ʱ�ȭ�Ѵ�
	}
	else {
		printf("CircularQ is Already Empty\n");                               // ���� ť�� ������� ��� Erro �޽��� ��� 
	}
}


void printQ(QueueType *cQ)                                                    // ���� ť�� ���ִ� data�� ������ִ� �Լ�
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;                                 // �����ϴ� data�� �� ������ ���� ���� data�� ��ġ�� ����Ų��
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;                                   // ����ť�� ���κ�, �� ���� ť���� data�� �� á�ٴ� ���� �Ǵ��ϱ� ���� data�� ü���� �ʴ� ������ ��ġ�� ��Ÿ����, ��, ������ data�� �ε��� ��ġ +1�� ����Ų��

	printf("Circular Queue : [");

	i = first;
	while (i != last) {                                                       // first : ���� ���� �� data�� �ε���, last : ���� ���߿� �� data�� �ε��� +1 
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;                                         // ���� �ε����� i�� �̵�

	}
	printf(" ]\n");
}

  
void debugQ(QueueType *cQ)                                                    // ���� ť���� front, rear�� ��ġ��, �� �ε��� �� data�� Ȯ���� �ִ� �Լ�
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)                                  // 0���� MAX_QUEUE_SIZE���� �ݺ�
	{
		if (i == cQ->front) {                                                 // �ε����� ���� front�� ���� ���ٸ� 
			printf("  [%d] = front\n", i);                                    // front ���( ���� ť�� Ư���� ����ִ� ���¿� ������ ���¸� �����ϱ� ���� �Ѱ��� ������ ����Ѽ� �ۿ� �����Ƿ� ���� )
			continue;                   
		} 
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

int FreeQ(QueueType *cQ) {                                                    // ���� ť�� �����Ҵ��� �����ϴ� �Լ�
	if (cQ == NULL) {                                                         // cQ�� NULL�� ��� ������ ������ �����Ƿ� ���� �޽��� ���
		return 0;
	}
	free(cQ);                                                                 // cQ�� �����Ҵ�� ������ free�� ���� ����
	return 1;
}

void MakeNULL(QueueType *cQ) {                                                // ���α׷� ����� ���� ť�� debugQ�� �ҽ� data���� ?�� ��µǾ� �̸� �ʱ�ȭ �ϴ� �Լ�
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		cQ->queue[i] = NULL;                                                  // �ʱ��� ��� index�� ���� NULL�� �ʱ�ȭ
	}
}