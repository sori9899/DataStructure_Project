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
 /* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
		 singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);                                                                          // main�Լ����� ������ headNode* �� ���� headnode�� �ּڰ��� �޾� ���� �����ϹǷ� ���������͸� �Ű������� ����

/* note: freeList�� �̱������͸� �Ű������� ����
		- initialize�� �� �ٸ��� ���� �Ұ�
		 - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h);                                                                             // initialize�� ���� headnode�� �Ҵ�� ������ �ּڰ��� �ޱ⶧���� �̱������͸� �Ű������� ����

int insertNode(headNode* h, int key);                                                                  // ������������ data�� �ִ� �Լ�
int insertLast(headNode* h, int key);                                                                  // �������� data�� �ִ� �Լ�
int insertFirst(headNode* h, int key);                                                                 // �� �տ� data�� �ִ� �Լ�
int deleteNode(headNode* h, int key);                                                                  // ����ڰ� �Է��� ���� ���� ���� ã�� �����ϰ� ������ ������ �߻���Ű�� �Լ�
int deleteLast(headNode* h);                                                                           // ������ ��带 �����ϴ� �Լ�
int deleteFirst(headNode* h);                                                                          // ù��° ��带 �����ϴ� �Լ�
int invertList(headNode* h);                                                                           // ����Ʈ�� ������ �Լ�

void printList(headNode* h);                                                                           // ����Ʈ�� ����ϴ� �Լ�


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;                                                                         // ����Ʈ�� ����

	printf("2019038068 �輺��\n");

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


int initialize(headNode** h) {                                                                         // main�Լ����� ������ headNode* �� ���� headnode�� �ּڰ��� �޾� ���� �����ϹǷ� ���������͸� �Ű������� ����

	if ((*h != NULL)) {                                                                                // ���� ��尡 ���� ��� �ʱ�ȭ
		freeList((*h));
	}

	*h = (headNode *)malloc(sizeof(headNode));                                                         // headNode��ŭ �����Ҵ��, NULL�� �ʱ�ȭ
	(*h)->first = NULL;

	if ((*h) == NULL) {                                                                                // �����Ҵ��� ���� �ʾ��� ��� ���� �߻�
		printf("Fail to mallocation\n");
		return -1;
	}
	return 1;
}

int freeList(headNode* h) {                                                                            // initialize�� ���� headnode�� �Ҵ�� ������ �ּڰ��� �ޱ⶧���� �̱������͸� �Ű������� ����
	if (h == NULL) {                                                                                   // �Ҵ�� ����Ʈ�� �������� ���� ��� ���� �޽��� �߻�
		printf("List is Empty\n");
		return -1;
	}
	listNode* p = h->first;

	listNode* previous = NULL;
	while (p != NULL) {                                                                                // p�� NULL�� ��� ����
		previous = p;
		p = p->rlink;
		if (p != NULL) {                                                                               // ���⼭ �������� �ʴ� ������, previous�� free�ϱ� ���� �� ���� ����� llink�� NULL�� ����� ��� �ϴµ�
			p->llink = NULL;                                                                           // ���⼭ �����ϰ� �Ǹ� �׷��� �������� �̷��� �ڵ尡 ¥����
		}
		previous->rlink = NULL;
		previous->llink = NULL;
		free(previous);
	}
	free(h);
	return 0;
}

void printList(headNode* h) {                                                                          // ����Ʈ�� ����ϴ� �Լ�
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {                                                                                   // ����Ʈ�� NULL�� ���, ����
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {                                                                 // �������� data�� �ִ� �Լ�
	if (h == NULL) {                                                                                   // h=NULL�ϰ�� ����, ����Ʈ�� ����ų head�� ��� ���� �߻�
		printf("initialize first\n");
		return -1;
	}
	listNode* temp = h->first;
	if (temp == NULL) {                                                                                // ���� ����Ʈ�� �������� ������� �� �տ� �־�� ������ insertFirstȣ��
		insertFirst(h, key);
		return 0;
	}
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	while (temp->rlink != NULL) {                                                                      // ������ ������ �̵�
		temp = temp->rlink;
	}
	node->llink = temp;                                                                                // �������� ��� ����
	temp->rlink = node;

	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {                                                                          // ������ ��带 �����ϴ� �Լ�
	if (h == NULL || h->first == NULL) {                                                               // ����Ʈ�� ����ִ� ����̹Ƿ� ���� �߻�
		printf("List is Empty\n");
		return -1;
	}
	listNode* temp = h->first;
	listNode* previous = NULL;

	while (temp->rlink != NULL) {                                                                      // ������ ������ �̵�
		previous = temp;
		temp = temp->rlink;
	}
	if (previous == NULL) {                                                                            // previous�� NULL�̸� ù��° ��� == ������ ����̹Ƿ�
		deleteFirst(h);                                                                                // deletFirst ȣ��
		return 0;
	}
	temp->llink = NULL;                                                                                // ����Ʈ�� �ٸ� ��尡 �����ϰ� temp�� �� ����Ʈ�� �������� ����Ű�� ���
	previous->rlink = NULL;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {                                                                // �� �տ� data�� �ִ� �Լ�
	if (h == NULL) {                                                                                   // h=NULL�ϰ�� ����, ����Ʈ�� ����ų head�� ��� ���� �߻�
		printf("initialize first\n");
		return -1;
	}
	listNode * temp = (listNode *)malloc(sizeof(listNode));
	temp->key = key;
	temp->llink = NULL;
	temp->rlink = h->first;
	if (h->first != NULL) {                                                                            // ���� ��带 ������ ��ġ�� �� ó���� ���
		h->first->llink = temp;                                                                        // h->rlink->llink�� �������� �����Ƿ� ���� ����
	}
	h->first = temp;                                                                                   // �ٲ� ��带 �ٽ� head���� ����
	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {                                                                         // ù��° ��带 �����ϴ� �Լ�
	if (h == NULL || h->first == NULL) {                                                               // ����Ʈ�� ����ִ� ����̹Ƿ� ���� �߻�
		printf("List is Empty\n");
		return -1;
	}
	listNode * temp = h->first;
	if (temp->rlink != NULL) {                                                                         // ���� ��尡 �Ѱ��� �ִ°��
		temp->rlink->llink = NULL;                                                                     // temp->rlink->llink�� �������� �����Ƿ�  ���� ����
	}
	h->first = temp->rlink;                                                                            // head���� �� ���� ����� �ּڰ� ����, (NULL�� ��� NULL ����)
	temp->rlink = NULL;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {                                                                          // ����Ʈ�� ������ �Լ�
	if (h == NULL || h->first == NULL) {                                                               // ����Ʈ�� ����ִ� ����̹Ƿ� ���� �߻�
		printf("List is Empty\n");
		return -1;
	}
	listNode * temp = h->first;
	listNode * tail = NULL;
	listNode * middle = NULL;

	while (temp != NULL) {                                                                             // temp�� NULL�� �ɶ����� �ݺ�
		tail = middle;
		middle = temp;
		temp = temp->rlink;
		middle->rlink = tail;                                                                          // middle->rlink�� tail����
		if (tail != NULL) {                                                                            // tail�� NULL�� �ƴ� ���
			tail->llink = middle;                                                                      // tail->link�� middle�� ���� -> ��, NULL�� �ƴҰ�� �յڷ� ������ �ְ� �ִ�
		}
		middle->llink = NULL;                                                                          // �⺻������ middle�� �׻� �� �տ� ������ llink�� NULL�� ����
	}
	h->first = middle;
	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {                                                                 // ������������ data�� �ִ� �Լ�
	if (h == NULL) {                                                                                   // h=NULL�ϰ�� ����, ����Ʈ�� ����ų head�� ��� ���� �߻�
		printf("initialize first\n");
		return -1;
	}
	listNode* temp = h->first;
	listNode* previous = NULL;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	while (temp != NULL && temp->key < key) {                                                            // temp�� ����Ű�� ��尡 NULL�� �ƴϰ� �� ����� key���� ����ڰ� �Է��� ������ ���� ���
		previous = temp;
		temp = temp->rlink;
	}
	if (previous == NULL) {                                                                            // ������ ��ġ�� �� ���� ���
		insertFirst(h, key);
		return 0;
	}
	else if (temp == NULL) {                                                                           // ������ ��ġ�� �� ���� ���
		insertLast(h, key);
		return 0;
	}
	temp->llink = node;                                                                                // ������ ��ġ�� �߰��� ���
	node->rlink = temp;
	node->llink = previous;
	previous->rlink = node;

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {                                                                 // ����ڰ� �Է��� ���� ���� ���� ã�� �����ϰ� ������ ������ �߻���Ű�� �Լ�
	if (h == NULL || h->first == NULL) {                                                               // ����Ʈ�� ����ִ� ����̹Ƿ� ���� �߻�
		printf("List is Empty\n");
		return -1;
	}
	listNode* temp = h->first;
	listNode* previous = NULL;

	while (temp != NULL && temp->key != key) {                                                         // tmep�� NULL�� �ƴϸ� key���� tmep�� key���� ������������ �ݺ�
		previous = temp;
		temp = temp->rlink;
	}
	if (temp == NULL) {                                                                                // key���� ������ data�� �������� �ʴ� ��� ���� �߻�
		printf("%d is not exist\n", key);
		return 0;
	}
	if (previous == NULL) {                                                                            // �� ���� ��带 �����ϴ� ���
		deleteFirst(h);
		return 0;
	}
	if (temp->rlink == NULL) {                                                                         // �� ���� ��带 �����ϴ� ���
		deleteLast(h);
		return 0;
	}
	previous->rlink = temp->rlink;                                                                     // �߰��� �ִ� ��帣 �����ϴ� ���
	temp->rlink->llink = previous;
	temp->rlink = NULL;
	temp->llink = NULL;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 1;
}



