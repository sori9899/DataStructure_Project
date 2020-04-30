/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* �ʿ��� ������� �߰� */

typedef struct Node { 
	int key;                      // key���� ������ ����
	struct Node* link;            // ���� ��带 ����Ű�� ����ü ������ ����( ����ü�� �ּҸ� �����ϹǷ� ���� ������ ��� ) 
} listNode;                       // struct Node �� ��Ī���� listNode�� ���

typedef struct Head {
	struct Node* first;           // ����Ʈ�� ������ ����Ű�� ����ü ������ ����( ����ü�� �ּҸ� �����ϹǷ� ���� ������ ��� ) 
}headNode;                        // struct Head �� ��Ī���� headNode�� ���


/* �Լ� ����Ʈ */
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
	headNode* headnode = NULL;   // ���� ����Ʈ�� head

	printf("2019038068 �輺��\n");

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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	if (h == NULL) {                                            // �Ҵ�� ����Ʈ�� �������� ���� ��� ���� �޽��� �߻� 
		printf("List is Empty\n");
		return -1;
	}
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
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
 * list ó���� key�� ���� ����ϳ��� �߰�
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


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	if (h == NULL) {
		printf("initialize List first\n");
		return -1;
	}
	listNode* node = (listNode*)malloc(sizeof(listNode));                               // node�� �����Ҵ�( listNode��ŭ�� )
	listNode*previous = NULL;                                                           // temp�� ����Ű�� ������ ���� ������ ����ų ����
	listNode* temp = h->first;                                                          // head�� ���� �����̸� ������ ����Ʈ�� ��������, �̸� temp�� �Ѱ� temp�� ��� �̵�
	node->key = key;                          
	if (temp == NULL) {
		insertFirst(h, key);
	}
	else { 
		while (temp != NULL && temp->key < key) {                                       // ����ڰ� �Է��� key���� �� ��ġ�� ã�� ����
			previous = temp;                                                            // temp->first�� ����Ű�� ������ �ּڰ��� �Ѱ��ش�
			temp = temp->link;                                                          // temp->first�� temp->first�� ����Ű�� ���� �������� �̵�
		} 
		if (previous == NULL) {
			insertFirst(h, key);
			return 0;
		}

		node->link = temp;                                                              // node->link�� temp->first�� ���Կ� ���� ����Ʈ���� ����
		previous->link = node;                                                          // previous->link�� node�� ���������ν� temp->first�� ����Ű�� ��� ���� ������� ����
	}
	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	if (h == NULL) {
		printf("initialize List first\n");
		return -1;
	}
	listNode* node = (listNode*)malloc(sizeof(listNode));                               // node�� �����Ҵ�( listNode��ŭ�� )
	listNode* temp = h->first;                                                          // head�� ���� �����̸� ������ ����Ʈ�� ��������, �̸� temp�� �Ѱ� temp�� ��� �̵�
	node->key = key;
	if (temp == NULL) {                                                                 // temp==NULL�� ��� ����Ʈ�� ����ִ� ����̹Ƿ�insertFirst ����
		insertFirst(h, key);
	}
	else {
		while (temp->link != NULL) {                                                    // �������� ���� : temp->first->link�� NULL�� ����Ű�� ���� ��� �� ���� ��尡 ���� ���̹Ƿ� �������̴�
			temp = temp->link;                                                          // temp->first�� ����Ű�� ��带 ���� ���� ����
		}
		node->link = temp->link;                                                        // node->link�� temp->first�� ���Կ� ���� ����Ʈ���� ����( ���⼭�� node->link�� NULL�� �����ϱ� ���� ��� )
		temp->link = node;                                                              // temp->first->link�� node�� ������ ���� ����Ʈ���� ����
	}
	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	if (h == NULL || h->first == NULL) {                                                // �Ҵ�� ����Ʈ�� �������� ���� ��� ���� �޽��� �߻� 
		printf("List is Empty\n");
		return -1;
	}
	listNode* temp = h->first;                                                          // temp�� ù��° ����Ʈ�� ����� �ּڰ��� �Ѱ��ش�
	h->first = temp->link;                                                              // h->first�� temp->link�� ����Ű�� ���� ����� �ּڰ��� �־� head���� ������ ���� 
	temp->link = NULL;                                                                  // temp->link�� NULL�� ��ȯ�� ù��° ������ ������ ������ ��ü
	printf("Delet %d\n", temp->key);
	free(temp);                                                                         // ù���� ��带 free�� ��ü
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	int sw=0;
	if ( h == NULL || h->first == NULL) {                                               // �Ҵ�� ����Ʈ�� �������� ���� ��� ���� �޽��� �߻� 
		printf("List is Empty\n");
		return -1;
	}
	listNode* temp = h->first;                                                          // temp�� ù��° ����Ʈ�� ����� �ּڰ��� �Ѱ��ش�
	listNode* previous = NULL;                                                          // temp�� ����Ű�� ������ ���� ������ ����ų ����
	while (temp != NULL) {
		if (temp->key == key) {                                                         // ���Ḯ��Ʈ�� key�� ������ ���� ���� ��쵵 temp=NULL�� ������ sw�� 1�� ������ �� ��츦 �и�
			sw = 1;
			break;
		}
		previous = temp;                                                                // previous�� temp�� ����Ű�� ����� �ٷ� �� ��帣 ����Ű�� �Ѵ�
		temp = temp->link;                                                              // temp�� ���� ���� �����̴� �ڵ�
	}
	if (previous == NULL) {                                                             // previous�� NULL�� ���� ù��° ��忡 key ���� �ִ� ���
		deleteFirst(h);                                                                 // ù��° ��� ����
		return 0;
	}
	if (temp == NULL && sw==1) {                                                        //temp==NULL�̰� sw==1�� ��� key���� ���Ḯ��Ʈ�� ���� �ִ� ���
		deleteLast(h);                                                                  // ������ ��� ����
		return 0;
	}
	else if (sw == 0) {                                                                 // sw==0�� ���� key���� �������� �ʴ� ���
		printf("%d isn't Esixt\n", key);                                                // Erorr �޼��� ���
		return -1;
	}
	previous->link = temp->link;                                                        // ���� ����� link�� temp�� ����Ű�� �ִ� ��带 ����
	temp->link = NULL;                                                                  // temp->link�� NULL�� �ٲپ� temp���� �յ��� ������ ���� �ڵ�
	printf("Delet %d\n", temp->key);
	free(temp);
	return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	if (h == NULL || h->first == NULL) {                                                // �Ҵ�� ����Ʈ�� �������� ���� ��� ���� �޽��� �߻� 
		printf("List is Empty\n");
		return -1;
	}
	listNode *temp = h->first;                       
	listNode *node = NULL;
	while (temp->link != NULL) {                                                       // temp->link�� NULL�� ��찡 ������ ���
		node = temp;                                                                   // temp�� ����Ű�� ����� ���� ��带 ����Ű�� ����ü ������ ����
		temp = temp->link;                                                             // temp�� ���� ���� �̵�
	}
	node->link = NULL;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	if (h == NULL || h->first == NULL) {                                               // �Ҵ�� ����Ʈ�� �������� ���� ��� ���� �޽��� �߻� 
		printf("List is Empty\n");
		return -1;
	}
	listNode *temp = h->first;                         
	listNode *middle = NULL;               
	listNode *trail = NULL; 
	while (temp != NULL) {                                                             // ����Ʈ�� ���� �������� �ݺ�
		trail = middle;				                                                   // middle�� �ִ� ���� trail�� �̵�
		middle = temp;                                                                 // temp�� ����Ű�� ���� middle���� ����Ű�� �ϴ� �ڵ�
		temp= temp->link;                                                              // temp�� ���� ���� �̵�
		middle->link = trail;                                                          // middle->link���� trail�� ������ �������� ���鵵�� ����
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
