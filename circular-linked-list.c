/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {                             // listNode를 별칭으로 가지고 있는 struct Node 구조체
	int key;
	struct Node* llink;                           // 각각 왼쪽 노드
	struct Node* rlink;                           // 오른쪽 노드를 가리킨다
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);                     // 처음 head 노드를 생성하는 코드, 혹 이미 노드들이 연결되어 있을 경우 해체하고 다시 노드 생성
int freeList(listNode* h);                        // 노드를 해체하는 코드
int insertLast(listNode* h, int key);             // 마지막에 노드 삽입
int deleteLast(listNode* h);                      // 마지막 노드를 삭제
int insertFirst(listNode* h, int key);            // 처음 노드 삽입
int deleteFirst(listNode* h);                     // 처음 노드 삭제
int invertList(listNode* h);                      // 리스트 역순으로 만드는 코드

int insertNode(listNode* h, int key);             // data의 값을 오름차순으로  노드 삽입하는 코드
int deleteNode(listNode* h, int key);             // 사용자가 입력한 data와 같은 값을 찾아 삭제하는 노드, 없으면 오류 발생

void printList(listNode* h);                      // 리스트를 출력하는 함수



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;
	printf("2019308068 김성욱\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {    // 처음 head 노드를 생성하는 코드, 혹 이미 노드들이 연결되어 있을 경우 해체하고 다시 노드 생성

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);             // 존제하는 노드의 헤체 진행

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {    // 노드를 해체하는 코드
	if (h == NULL) {
		printf("Empty List\n");
		return 0;
	}

	while (h->llink != h) {
		deleteFirst(h);     // 노드의 헤체가 앞에서 부터 순서대로 이루어 짐으로 deletFirst호출
	}
	free(h);

	return 1;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {                                   // 마지막에 노드 삽입
	if (h == NULL) {                                                     // initialize가 되지 않은 상태, 즉 head가 NULL인 상태이므로
		printf("initialize first\n");                                    // 오류 발생
		return 0;
	}
	if (h->llink == h) {                                                 // 리스트가 비었다는 뜻임으로 맨 앞에 노드 추가와 같은 경우
		insertFirst(h, key);
		return 1;
	}
	listNode* temp = (listNode*)malloc(sizeof(listNode));                // 리스트의 맨 뒤에 노드를 삽입하는 경우
	temp->key = key;
	temp->llink = h->llink;                                              // 새롭게 연결할 노드의 rlink, llink를 연결한 후
	temp->rlink = h;
	h->llink->rlink = temp;                                              // 기존의 노드의 앞뒤의 rlink, llink를 삽입할 노드와 연결
	h->llink = temp;
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {                                            // 마지막 노드를 삭제
	if (h == NULL || h->llink == h) {                                      // 리스트가 비여있는 경우이므로 오류 발생
		printf("Empty List\n");
		return 0;
	}

	if (h->rlink->rlink == h) {                                          // 노드가 하나 존제한다면, 첫번째 노드를 해제하는 것과 같으므로
		deleteFirst(h);                                                  // deleteFirst 호출
		return 1;
	}
	listNode* temp = h->llink;                                           // h->llink가 마지막 노드이므로 이의 주솟값을 temp에 주고
	temp->llink->rlink = temp->rlink;                                    // 해제를 하기전, 기존 노드와의 연결을 해제
	h->llink = temp->llink;
	temp->rlink = temp;                                                  // temp와 기존 노드간 연결 해제
	temp->llink = temp;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {                                   // 처음 노드 삽입
	if (h == NULL) {                                                      // initialize가 되지 않은 상태, 즉 head가 NULL인 상태이므로
		printf("initialize first\n");                                     // 오류 발생
		return 0;
	}
	listNode *temp = (listNode *)malloc(sizeof(listNode));
	temp->key = key;
	temp->llink = h;
	if (h->llink == h) {                                                  // head에 노드가 하나도 없는 경우
		h->llink = temp;                                                  // h->llink의 값을 temp으로 해주는 유일한 경우이다
	}
	else {                                                                // 그렇지 않은 경우
		h->rlink->llink = temp;                                           // 맨 앞에 있던 노드의 llink에 temp연결
	}
	temp->rlink = h->rlink;                                               // temp->rlink에는 기존에 맨 앞에 있던 노드 연결
	h->rlink = temp;                                                      // h->rlink에 새로 삽입할 노드 연결
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {                       // 처음 노드 삭제
	if (h == NULL || h->llink == h) {                // 리스트가 비여있는 경우이므로 오류 발생
		printf("Empty List\n");
		return 0;
	}

	listNode * temp = h->rlink;
	h->rlink = temp->rlink;                          // head와 temp 다음 노드간연결
	if (temp->rlink == h) {                          // 이경우 노드가 한개만 존제하는 것이므로
		h->llink = temp->llink;                      // 헤드에 temp->link 즉, head의 주소값 전달
	}
	else {                                           // 노드가 2개 이상일 경우
		temp->rlink->llink = temp->llink;            // 다음 노드에 head를 연결해 head와 temp와의 연결 해제
	}
	temp->rlink = temp;
	temp->llink = temp;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {                       // 리스트 역순으로 만드는 코드
	if (h == NULL || h->llink == h) {               // 리스트가 비여있는 경우이므로 오류 발생
		printf("Empty List\n");
		return 0;
	}

	listNode *temp = h->rlink;
	listNode *tail = NULL;
	listNode *middle = NULL;
	while (temp != h) {                             // circular_linked_list이므로 temp==h일때가 리스트를 한바퀴 돌았을 때다
		tail = middle;
		middle = temp;
		temp = temp->rlink;                         // 밑에서  middle->rlink를 변경하게 되면 temp->rlink도 같이 변경 됨으로 미리 temp를 다음 노드로 이동
		if (tail != NULL) {                        // tail이 NULL이 아닐경우, middle과 tail간의 연결을 구현하는 코드
			tail->llink = middle;
			middle->rlink = tail;
		}
		if (middle->llink == h) {                   // middle->llink==h 일때는 리스트의 처음이므로,
			middle->rlink = h;                      // 미리 middle->rlilnk에 head의 주솟값을 전달( 맨 처음 노드가 맨 뒤로 가기 때문(rlink기준) )
		}
	}
	h->llink = h->rlink;                            // revers된 리스트와 head간의 연결을 구현한 코드
	h->rlink = middle;
	middle->llink = h;
	return 1;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {            // data의 값을 오름차순으로  노드 삽입하는 코드
	if (h == NULL) {                              // initialize가 되지 않은 상태, 즉 head가 NULL인 상태이므로
		printf("initialize first\n");             // 오류 발생
		return 0;
	}
	listNode *node = h->rlink;
	listNode *previous = NULL;
	listNode *temp = NULL;
	while (node->key < key && node != h) {       // key값이 들어갈 위치 찾기
		previous = node;
		node = node->rlink;
	}
	if (previous == NULL) {                       // 맨 앞에 들어갈 경우
		insertFirst(h, key);
		return 1;
	}
	if (node == h) {                              // 맨 뒤에 들어갈 경우
		insertLast(h, key);
		return 1;
	}
	temp = (listNode*)malloc(sizeof(listNode));   // 중간에 들어갈 경우
	temp->key = key;
	previous->rlink = temp;                       // 리스트의 앞뒤를 연결
	node->llink = temp;
	temp->llink = previous;
	temp->rlink = node;

	return 1;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {                  // 사용자가 입력한 data와 같은 값을 찾아 삭제하는 노드, 없으면 오류 발생
	if (h == NULL || h->llink == h) {                   // 리스트가 비여있는 경우이므로 오류 발생
		printf("Empty List\n");
		return 0;
	}

	listNode*node = h->rlink;
	listNode*previous = NULL;
	while (node->key != key && node != h) {              // 리스트를 한바퀴를 돌며 key값과 data값이 같은 노드 탐색
		previous = node;
		node = node->rlink;
	}
	if (previous == NULL) {                              // 첫번째 노드에서 종료된 경우이므로, 첫번째 노드 삭제와 동일
		deleteFirst(h);
		return 1;
	}
	if (node == h) {                                     // 이경우, 조건에 맡는 key값을 찾지 못한것이므로, 즉 key값이 리스트에 존제하지 않는 경우
		printf("%d is not Exist\n", key);
		return 0;
	}
	previous->rlink = node->rlink;                       // 조건에 맞는 노드를 기준으로 이전노드와 다음노드 연결
	node->rlink->llink = previous;
	node->rlink = node;                                  // 조건에 맞는 노드의 앞뒤 연결 해체
	node->llink = node;
	printf("Delet %d\n", key);
	free(node);
	return 1;
}

