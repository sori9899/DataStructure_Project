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
 /* �ʿ��� ������� �߰� */

typedef struct Node {                             // listNode�� ��Ī���� ������ �ִ� struct Node ����ü
	int key;
	struct Node* llink;                           // ���� ���� ���
	struct Node* rlink;                           // ������ ��带 ����Ų��
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);                     // ó�� head ��带 �����ϴ� �ڵ�, Ȥ �̹� ������ ����Ǿ� ���� ��� ��ü�ϰ� �ٽ� ��� ����
int freeList(listNode* h);                        // ��带 ��ü�ϴ� �ڵ�
int insertLast(listNode* h, int key);             // �������� ��� ����
int deleteLast(listNode* h);                      // ������ ��带 ����
int insertFirst(listNode* h, int key);            // ó�� ��� ����
int deleteFirst(listNode* h);                     // ó�� ��� ����
int invertList(listNode* h);                      // ����Ʈ �������� ����� �ڵ�

int insertNode(listNode* h, int key);             // data�� ���� ������������  ��� �����ϴ� �ڵ�
int deleteNode(listNode* h, int key);             // ����ڰ� �Է��� data�� ���� ���� ã�� �����ϴ� ���, ������ ���� �߻�

void printList(listNode* h);                      // ����Ʈ�� ����ϴ� �Լ�



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;
	printf("2019308068 �輺��\n");
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


int initialize(listNode** h) {    // ó�� head ��带 �����ϴ� �ڵ�, Ȥ �̹� ������ ����Ǿ� ���� ��� ��ü�ϰ� �ٽ� ��� ����

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (*h != NULL)
		freeList(*h);             // �����ϴ� ����� ��ü ����

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h) {    // ��带 ��ü�ϴ� �ڵ�
	if (h == NULL) {
		printf("Empty List\n");
		return 0;
	}

	while (h->llink != h) {
		deleteFirst(h);     // ����� ��ü�� �տ��� ���� ������� �̷�� ������ deletFirstȣ��
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {                                   // �������� ��� ����
	if (h == NULL) {                                                     // initialize�� ���� ���� ����, �� head�� NULL�� �����̹Ƿ�
		printf("initialize first\n");                                    // ���� �߻�
		return 0;
	}
	if (h->llink == h) {                                                 // ����Ʈ�� ����ٴ� �������� �� �տ� ��� �߰��� ���� ���
		insertFirst(h, key);
		return 1;
	}
	listNode* temp = (listNode*)malloc(sizeof(listNode));                // ����Ʈ�� �� �ڿ� ��带 �����ϴ� ���
	temp->key = key;
	temp->llink = h->llink;                                              // ���Ӱ� ������ ����� rlink, llink�� ������ ��
	temp->rlink = h;
	h->llink->rlink = temp;                                              // ������ ����� �յ��� rlink, llink�� ������ ���� ����
	h->llink = temp;
	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {                                            // ������ ��带 ����
	if (h == NULL || h->llink == h) {                                      // ����Ʈ�� ���ִ� ����̹Ƿ� ���� �߻�
		printf("Empty List\n");
		return 0;
	}

	if (h->rlink->rlink == h) {                                          // ��尡 �ϳ� �����Ѵٸ�, ù��° ��带 �����ϴ� �Ͱ� �����Ƿ�
		deleteFirst(h);                                                  // deleteFirst ȣ��
		return 1;
	}
	listNode* temp = h->llink;                                           // h->llink�� ������ ����̹Ƿ� ���� �ּڰ��� temp�� �ְ�
	temp->llink->rlink = temp->rlink;                                    // ������ �ϱ���, ���� ������ ������ ����
	h->llink = temp->llink;
	temp->rlink = temp;                                                  // temp�� ���� ��尣 ���� ����
	temp->llink = temp;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {                                   // ó�� ��� ����
	if (h == NULL) {                                                      // initialize�� ���� ���� ����, �� head�� NULL�� �����̹Ƿ�
		printf("initialize first\n");                                     // ���� �߻�
		return 0;
	}
	listNode *temp = (listNode *)malloc(sizeof(listNode));
	temp->key = key;
	temp->llink = h;
	if (h->llink == h) {                                                  // head�� ��尡 �ϳ��� ���� ���
		h->llink = temp;                                                  // h->llink�� ���� temp���� ���ִ� ������ ����̴�
	}
	else {                                                                // �׷��� ���� ���
		h->rlink->llink = temp;                                           // �� �տ� �ִ� ����� llink�� temp����
	}
	temp->rlink = h->rlink;                                               // temp->rlink���� ������ �� �տ� �ִ� ��� ����
	h->rlink = temp;                                                      // h->rlink�� ���� ������ ��� ����
	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {                       // ó�� ��� ����
	if (h == NULL || h->llink == h) {                // ����Ʈ�� ���ִ� ����̹Ƿ� ���� �߻�
		printf("Empty List\n");
		return 0;
	}

	listNode * temp = h->rlink;
	h->rlink = temp->rlink;                          // head�� temp ���� ��尣����
	if (temp->rlink == h) {                          // �̰�� ��尡 �Ѱ��� �����ϴ� ���̹Ƿ�
		h->llink = temp->llink;                      // ��忡 temp->link ��, head�� �ּҰ� ����
	}
	else {                                           // ��尡 2�� �̻��� ���
		temp->rlink->llink = temp->llink;            // ���� ��忡 head�� ������ head�� temp���� ���� ����
	}
	temp->rlink = temp;
	temp->llink = temp;
	printf("Delet %d\n", temp->key);
	free(temp);
	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {                       // ����Ʈ �������� ����� �ڵ�
	if (h == NULL || h->llink == h) {               // ����Ʈ�� ���ִ� ����̹Ƿ� ���� �߻�
		printf("Empty List\n");
		return 0;
	}

	listNode *temp = h->rlink;
	listNode *tail = NULL;
	listNode *middle = NULL;
	while (temp != h) {                             // circular_linked_list�̹Ƿ� temp==h�϶��� ����Ʈ�� �ѹ��� ������ ����
		tail = middle;
		middle = temp;
		temp = temp->rlink;                         // �ؿ���  middle->rlink�� �����ϰ� �Ǹ� temp->rlink�� ���� ���� ������ �̸� temp�� ���� ���� �̵�
		if (tail != NULL) {                        // tail�� NULL�� �ƴҰ��, middle�� tail���� ������ �����ϴ� �ڵ�
			tail->llink = middle;
			middle->rlink = tail;
		}
		if (middle->llink == h) {                   // middle->llink==h �϶��� ����Ʈ�� ó���̹Ƿ�,
			middle->rlink = h;                      // �̸� middle->rlilnk�� head�� �ּڰ��� ����( �� ó�� ��尡 �� �ڷ� ���� ����(rlink����) )
		}
	}
	h->llink = h->rlink;                            // revers�� ����Ʈ�� head���� ������ ������ �ڵ�
	h->rlink = middle;
	middle->llink = h;
	return 1;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {            // data�� ���� ������������  ��� �����ϴ� �ڵ�
	if (h == NULL) {                              // initialize�� ���� ���� ����, �� head�� NULL�� �����̹Ƿ�
		printf("initialize first\n");             // ���� �߻�
		return 0;
	}
	listNode *node = h->rlink;
	listNode *previous = NULL;
	listNode *temp = NULL;
	while (node->key < key && node != h) {       // key���� �� ��ġ ã��
		previous = node;
		node = node->rlink;
	}
	if (previous == NULL) {                       // �� �տ� �� ���
		insertFirst(h, key);
		return 1;
	}
	if (node == h) {                              // �� �ڿ� �� ���
		insertLast(h, key);
		return 1;
	}
	temp = (listNode*)malloc(sizeof(listNode));   // �߰��� �� ���
	temp->key = key;
	previous->rlink = temp;                       // ����Ʈ�� �յڸ� ����
	node->llink = temp;
	temp->llink = previous;
	temp->rlink = node;

	return 1;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {                  // ����ڰ� �Է��� data�� ���� ���� ã�� �����ϴ� ���, ������ ���� �߻�
	if (h == NULL || h->llink == h) {                   // ����Ʈ�� ���ִ� ����̹Ƿ� ���� �߻�
		printf("Empty List\n");
		return 0;
	}

	listNode*node = h->rlink;
	listNode*previous = NULL;
	while (node->key != key && node != h) {              // ����Ʈ�� �ѹ����� ���� key���� data���� ���� ��� Ž��
		previous = node;
		node = node->rlink;
	}
	if (previous == NULL) {                              // ù��° ��忡�� ����� ����̹Ƿ�, ù��° ��� ������ ����
		deleteFirst(h);
		return 1;
	}
	if (node == h) {                                     // �̰��, ���ǿ� �ô� key���� ã�� ���Ѱ��̹Ƿ�, �� key���� ����Ʈ�� �������� �ʴ� ���
		printf("%d is not Exist\n", key);
		return 0;
	}
	previous->rlink = node->rlink;                       // ���ǿ� �´� ��带 �������� �������� ������� ����
	node->rlink->llink = previous;
	node->rlink = node;                                  // ���ǿ� �´� ����� �յ� ���� ��ü
	node->llink = node;
	printf("Delet %d\n", key);
	free(node);
	return 1;
}

