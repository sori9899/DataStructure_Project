/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);                                                                          // main함수에서 선언한 headNode* 형 변수 headnode의 주솟값을 받아 직접 변경하므로 이중포인터를 매개변수로 받음

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);                                                                             // initialize를 통해 headnode에 할당된 공간의 주솟값을 받기때문에 싱글포인터를 매개변수로 받음

int insertNode(headNode* h, int key);                                                                  // 오름차순으로 data를 넣는 함수
int insertLast(headNode* h, int key);                                                                  // 마지막에 data를 넣는 함수
int insertFirst(headNode* h, int key);                                                                 // 맨 앞에 data를 넣는 함수
int deleteNode(headNode* h, int key);                                                                  // 사용자가 입력한 수와 같은 수를 찾아 삭제하고 없으면 오류를 발생시키는 함수
int deleteLast(headNode* h);                                                                           // 마지막 노드를 삭제하는 함수
int deleteFirst(headNode* h);                                                                          // 첫번째 노드를 삭제하는 함수
int invertList(headNode* h);                                                                           // 리스트를 뒤집는 함수

void printList(headNode* h);                                                                           // 리스트를 출력하는 함수


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;                                                                         // 리스트의 시작

	printf("2019038068 김성욱\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {                                                                         // main함수에서 선언한 headNode* 형 변수 headnode의 주솟값을 받아 직접 변경하므로 이중포인터를 매개변수로 받음

	if ((*h != NULL)) {                                                                                // 기존 노드가 있을 경우 초기화
		freeList((*h));
	}

	*h = (headNode *)malloc(sizeof(headNode));                                                         // headNode만큼 동적할당뒤, NULL로 초기화
	(*h)->first = NULL;

	if ((*h) == NULL) {                                                                                // 동적할당이 되지 않았을 경우 오류 발생
		printf("Fail to mallocation\n");
		return -1;
	}
	return 1;
}

int freeList(headNode* h) {                                                                            // initialize를 통해 headnode에 할당된 공간의 주솟값을 받기때문에 싱글포인터를 매개변수로 받음
	if (h == NULL) {                                                                                   // 할당된 리스트가 존제하지 않을 경우 오류 메시지 발생
		printf("List is Empty\n");
		return -1;
	}
	listNode* p = h->first;

	listNode* previous = NULL;
	while (p != NULL) {                                                                                // p가 NULL인 경우 중지
		previous = p;
		p = p->rlink;
		if (p != NULL) {                                                                               // 여기서 종료하지 않는 이유는, previous를 free하기 전에 그 다음 노드의 llink를 NULL로 만들어 줘야 하는데
			p->llink = NULL;                                                                           // 여기서 종료하게 되면 그렇지 못함으로 이렇게 코드가 짜여짐
		}
		previous->rlink = NULL;
		previous->llink = NULL;
		free(previous);
	}
	free(h);
	return 0;
}

void printList(headNode* h) {                                                                          // 리스트를 출력하는 함수
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {                                                                                   // 리스트가 NULL일 경우, 오류
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {                                                                 // 마지막에 data를 넣는 함수
	if (h == NULL) {                                                                                   // h=NULL일경우 오류, 리스트를 가리킬 head가 없어서 오류 발생
		printf("initialize first\n");
		return -1;
	}
	listNode* temp = h->first;
	if (temp == NULL) {                                                                                // 기존 리스트가 존제하지 않을경우 맨 앞에 넣어야 함으로 insertFirst호출
		insertFirst(h, key);
		return 0;
	}
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	while (temp->rlink != NULL) {                                                                      // 마지막 노드까지 이동
		temp = temp->rlink;
	}
	node->llink = temp;                                                                                // 마지막에 노드 삽입
	temp->rlink = node;

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {                                                                          // 마지막 노드를 삭제하는 함수
	if (h == NULL || h->first == NULL) {                                                               // 리스트가 비어있는 경우이므로 오류 발생
		printf("List is Empty\n");
		return -1;
	}
	listNode* temp = h->first;
	listNode* previous = NULL;

	while (temp->rlink != NULL) {                                                                      // 마지막 노드까지 이동
		previous = temp;
		temp = temp->rlink;
	}
	if (previous == NULL) {                                                                            // previous가 NULL이면 첫번째 노드 == 마지막 노드이므로
		deleteFirst(h);                                                                                // deletFirst 호출
		return 0;
	}
	temp->llink = NULL;                                                                                // 리스트에 다른 노드가 존제하고 temp가 그 리스트의 마지막을 가리키는 경우
	previous->rlink = NULL;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {                                                                // 맨 앞에 data를 넣는 함수
	if (h == NULL) {                                                                                   // h=NULL일경우 오류, 리스트를 가리킬 head가 없어서 오류 발생
		printf("initialize first\n");
		return -1;
	}
	listNode * temp = (listNode *)malloc(sizeof(listNode));
	temp->key = key;
	temp->llink = NULL;
	temp->rlink = h->first;
	if (h->first != NULL) {                                                                            // 만약 노드를 삽입할 위치가 맨 처음인 경우
		h->first->llink = temp;                                                                        // h->rlink->llink는 존제하지 않으므로 실행 안함
	}
	h->first = temp;                                                                                   // 바뀐 노드를 다시 head에다 연결
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {                                                                         // 첫번째 노드를 삭제하는 함수
	if (h == NULL || h->first == NULL) {                                                               // 리스트가 비어있는 경우이므로 오류 발생
		printf("List is Empty\n");
		return -1;
	}
	listNode * temp = h->first;
	if (temp->rlink != NULL) {                                                                         // 만약 노드가 한개만 있는경우
		temp->rlink->llink = NULL;                                                                     // temp->rlink->llink가 존제하지 않으므로  실행 안함
	}
	h->first = temp->rlink;                                                                            // head에는 그 다음 노드의 주솟값 전달, (NULL일 경우 NULL 전달)
	temp->rlink = NULL;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {                                                                          // 리스트를 뒤집는 함수
	if (h == NULL || h->first == NULL) {                                                               // 리스트가 비어있는 경우이므로 오류 발생
		printf("List is Empty\n");
		return -1;
	}
	listNode * temp = h->first;
	listNode * tail = NULL;
	listNode * middle = NULL;

	while (temp != NULL) {                                                                             // temp가 NULL이 될때까지 반복
		tail = middle;
		middle = temp;
		temp = temp->rlink;
		middle->rlink = tail;                                                                          // middle->rlink에 tail연결
		if (tail != NULL) {                                                                            // tail이 NULL이 아닐 경우
			tail->llink = middle;                                                                      // tail->link를 middle과 연결 -> 즉, NULL이 아닐경우 앞뒤로 연결해 주고 있다
		}
		middle->llink = NULL;                                                                          // 기본적으로 middle은 항상 맨 앞에 들어감으로 llink를 NULL로 변경
	}
	h->first = middle;
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {                                                                 // 오름차순으로 data를 넣는 함수
	if (h == NULL) {                                                                                   // h=NULL일경우 오류, 리스트를 가리킬 head가 없어서 오류 발생
		printf("initialize first\n");
		return -1;
	}
	listNode* temp = h->first;
	listNode* previous = NULL;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	while (temp != NULL && temp->key < key) {                                                            // temp가 가리키는 노드가 NULL이 아니고 그 노드의 key값이 사용자가 입력한 값보다 작을 경우
		previous = temp;
		temp = temp->rlink;
	}
	if (previous == NULL) {                                                                            // 삽입할 위치가 맨 앞인 경우
		insertFirst(h, key);
		return 0;
	}
	else if (temp == NULL) {                                                                           // 삽입할 위치가 맨 뒤인 경우
		insertLast(h, key);
		return 0;
	}
	temp->llink = node;                                                                                // 삽입할 위치가 중간인 경우
	node->rlink = temp;
	node->llink = previous;
	previous->rlink = node;

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {                                                                 // 사용자가 입력한 수와 같은 수를 찾아 삭제하고 없으면 오류를 발생시키는 함수
	if (h == NULL || h->first == NULL) {                                                               // 리스트가 비어있는 경우이므로 오류 발생
		printf("List is Empty\n");
		return -1;
	}
	listNode* temp = h->first;
	listNode* previous = NULL;

	while (temp != NULL && temp->key != key) {                                                         // tmep가 NULL이 아니며 key값이 tmep의 key값과 같아질때까지 반복
		previous = temp;
		temp = temp->rlink;
	}
	if (temp == NULL) {                                                                                // key값과 동일한 data가 존재하지 않는 경우 오류 발생
		printf("%d is not exist\n", key);
		return 0;
	}
	if (previous == NULL) {                                                                            // 맨 앞의 노드를 삭제하는 경우
		deleteFirst(h);
		return 0;
	}
	if (temp->rlink == NULL) {                                                                         // 맨 뒤의 노드를 삭제하는 경우
		deleteLast(h);
		return 0;
	}
	previous->rlink = temp->rlink;                                                                     // 중간에 있는 노드르 삭제하는 경우
	temp->rlink->llink = previous;
	temp->rlink = NULL;
	temp->llink = NULL;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 1;
}



