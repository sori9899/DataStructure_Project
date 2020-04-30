/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node { 
	int key;                      // key값을 저장할 변수
	struct Node* link;            // 다음 노드를 가리키는 구조체 포인터 변수( 구조체의 주소를 저장하므로 단일 포인터 사용 ) 
} listNode;                       // struct Node 의 별칭으로 listNode를 사용

typedef struct Head {
	struct Node* first;           // 리스트의 시작을 가리키는 구조체 포인터 변수( 구조체의 주소를 저장하므로 단일 포인터 사용 ) 
}headNode;                        // struct Head 의 별칭으로 headNode를 사용


/* 함수 리스트 */
headNode* initialize(headNode* h);  
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;   // 연결 리스트의 head

	printf("2019038068 김성욱\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	if (h == NULL) {                                            // 할당된 리스트가 존제하지 않을 경우 오류 메시지 발생 
		printf("List is Empty\n");
		return -1;
	}
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	if (h == NULL) {
		printf("initialize List first\n");
		return -1;
	}
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	if (h == NULL) {
		printf("initialize List first\n");
		return -1;
	}
	listNode* node = (listNode*)malloc(sizeof(listNode));                               // node에 동적할당( listNode만큼을 )
	listNode*previous = NULL;                                                           // temp가 가리키는 공간의 이전 공간을 가리킬 변수
	listNode* temp = h->first;                                                          // head를 직접 움직이면 기존의 리스트가 날라감으로, 이를 temp로 넘겨 temp가 대신 이동
	node->key = key;                          
	if (temp == NULL) {
		insertFirst(h, key);
	}
	else { 
		while (temp != NULL && temp->key < key) {                                       // 사용자가 입력한 key값이 들어갈 위치를 찾는 조건
			previous = temp;                                                            // temp->first가 가리키는 공간의 주솟값을 넘겨준다
			temp = temp->link;                                                          // temp->first는 temp->first가 가리키는 다음 공간으로 이동
		} 
		if (previous == NULL) {
			insertFirst(h, key);
			return 0;
		}

		node->link = temp;                                                              // node->link에 temp->first를 삽입에 뒤의 리스트들을 연결
		previous->link = node;                                                          // previous->link에 node를 연결함으로써 temp->first가 가리키는 노드 이전 노드들과의 연결
	}
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	if (h == NULL) {
		printf("initialize List first\n");
		return -1;
	}
	listNode* node = (listNode*)malloc(sizeof(listNode));                               // node에 동적할당( listNode만큼을 )
	listNode* temp = h->first;                                                          // head를 직접 움직이면 기존의 리스트가 날라감으로, 이를 temp로 넘겨 temp가 대신 이동
	node->key = key;
	if (temp == NULL) {                                                                 // temp==NULL일 경우 리스트가 비어있는 경우이므로insertFirst 실행
		insertFirst(h, key);
	}
	else {
		while (temp->link != NULL) {                                                    // 마지막일 조건 : temp->first->link가 NULL을 가리키고 있을 경우 그 다음 노드가 없는 것이므로 마지막이다
			temp = temp->link;                                                          // temp->first가 가리키는 노드를 다음 노드로 변경
		}
		node->link = temp->link;                                                        // node->link에 temp->first를 삽입에 뒤의 리스트들을 연결( 여기서는 node->link를 NULL로 변경하기 위해 사용 )
		temp->link = node;                                                              // temp->first->link에 node를 삽입해 이전 리스트들을 연결
	}
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if (h == NULL || h->first == NULL) {                                                // 할당된 리스트가 존제하지 않을 경우 오류 메시지 발생 
		printf("List is Empty\n");
		return -1;
	}
	listNode* temp = h->first;                                                          // temp에 첫번째 리스트의 노드의 주솟값을 넘겨준다
	h->first = temp->link;                                                              // h->first에 temp->link가 가리키는 다음 노드의 주솟값을 넣어 head와의 연결을 끊고 
	temp->link = NULL;                                                                  // temp->link를 NULL로 변환해 첫번째 노드와의 연결을 완전히 해체
	printf("Delet %d\n", temp->key);
	free(temp);                                                                         // 첫번쨰 노드를 free로 해체
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	int sw=0;
	if ( h == NULL || h->first == NULL) {                                               // 할당된 리스트가 존제하지 않을 경우 오류 메시지 발생 
		printf("List is Empty\n");
		return -1;
	}
	listNode* temp = h->first;                                                          // temp에 첫번째 리스트의 노드의 주솟값을 넘겨준다
	listNode* previous = NULL;                                                          // temp가 가리키는 공간의 이전 공간을 가리킬 변수
	while (temp != NULL) {
		if (temp->key == key) {                                                         // 연결리스트에 key와 동일한 값이 없는 경우도 temp=NULL이 됨으로 sw를 1로 변경해 이 경우를 분리
			sw = 1;
			break;
		}
		previous = temp;                                                                // previous는 temp가 가리키는 노드의 바로 전 노드르 가리키게 한다
		temp = temp->link;                                                              // temp를 다음 노드로 움직이는 코드
	}
	if (previous == NULL) {                                                             // previous가 NULL인 경우는 첫번째 노드에 key 값이 있는 경우
		deleteFirst(h);                                                                 // 첫번째 노드 삭제
		return 0;
	}
	if (temp == NULL && sw==1) {                                                        //temp==NULL이고 sw==1인 경운 key값이 연결리스트의 끝에 있는 경우
		deleteLast(h);                                                                  // 마지막 노드 삭제
		return 0;
	}
	else if (sw == 0) {                                                                 // sw==0인 경우는 key값이 존제하지 않는 경우
		printf("%d isn't Esixt\n", key);                                                // Erorr 메세지 출력
		return -1;
	}
	previous->link = temp->link;                                                        // 이전 노드의 link에 temp가 가리키고 있는 노드를 연결
	temp->link = NULL;                                                                  // temp->link를 NULL로 바꾸어 temp와의 앞뒤의 연결을 끊는 코드
	printf("Delet %d\n", temp->key);
	free(temp);
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if (h == NULL || h->first == NULL) {                                                // 할당된 리스트가 존제하지 않을 경우 오류 메시지 발생 
		printf("List is Empty\n");
		return -1;
	}
	listNode *temp = h->first;                       
	listNode *node = NULL;
	while (temp->link != NULL) {                                                       // temp->link가 NULL인 경우가 마지막 노드
		node = temp;                                                                   // temp가 가리키는 노드의 이전 노드를 가리키는 구조체 포인터 변수
		temp = temp->link;                                                             // temp는 다음 노드로 이동
	}
	node->link = NULL;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if (h == NULL || h->first == NULL) {                                               // 할당된 리스트가 존제하지 않을 경우 오류 메시지 발생 
		printf("List is Empty\n");
		return -1;
	}
	listNode *temp = h->first;                         
	listNode *middle = NULL;               
	listNode *trail = NULL; 
	while (temp != NULL) {                                                             // 리스트의 끝에 갈때까지 반복
		trail = middle;				                                                   // middle에 있는 값을 trail로 이동
		middle = temp;                                                                 // temp가 가리키는 곳을 middle또한 가리키게 하는 코드
		temp= temp->link;                                                              // temp는 다음 노드로 이동
		middle->link = trail;                                                          // middle->link에는 trail을 연결해 역순으로 만들도록 구현
	}
	h->first = middle;
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
