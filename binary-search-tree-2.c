/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */
// right������ Ž���ϴ� ������� �ڵ带 �ۼ��Ͽ����ϴ�
#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */




int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("2019038068 �輺��");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

// ��带 �ʱ�ȭ �ϴ� �Լ�
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}


// ����� ������� inorder Ž��
void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
 // �ݺ��� ������� inordor Ž��
void iterativeInorder(Node* node)
{
	for (;;) {
		// ���ѹݺ�
		for (; node; node = node->left) {
			// node�� ���ʺ��� Ž���ؾ� ������ �ϴ� ���ʺ��� Ž��
			push(node);
			// stack�� node�� �ּ� ����
		}
		node = pop();
		// ���ʿ� ���� Ž���� �� �������� pop()

		if (node == NULL) break;
		// ���� top�� -1�ΰ�� NULL�� ��ȯ�ϸ�, �̴� �� ������ ����ٴ� ���̹Ƿ� ����

		printf(" [%d] ", node->key);
		// node�� data �� ���
		node = node->right;
		// node�� ���������� �̵�
	}
}

/**
 * textbook: p 225
 */
 // �ݺ��� ������� ������� ����� ���
void levelOrder(Node* ptr)
{
	front = 0;
	rear = 0;
	// ���� ť���� front�� ����Ű�� ���� �������� �ξ� �̸� �̿���
	// ������ ���¿� ����ִ� ���¸� ���������� 0���� �ʱ�ȭ
	enQueue(ptr);
	// �ʱⰪ�� ������
	for (;;) {
		ptr = deQueue(ptr);
		// stack�� �ִ� ���� �����´�
		if (!ptr) break;
		// �װ��� NULL�� �ƴ϶��
		printf(" [%d] ", ptr->key);
		// ����� �ڽĳ�� ����
		if (ptr->left != NULL) {
			enQueue(ptr->left);
		}
		if (ptr->right != NULL) {
			enQueue(ptr->right);
		}
	}
}

// ��带 �����ϴ� �Լ�
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

// ��带 �����ϴ� �Լ�
int deleteNode(Node* head, int key)
{
	Node *temp = head->left;
	Node *temp2 = NULL;
	Node *previous = head;
	for (;;) {
		if (temp == NULL || temp->key == key) {
			// �ݺ��ϸ� �˻�, temp�� NULL�� ��� temp->key���� �˻��ϸ� ������ �߻������� temp==NULL���� �˻�
			// OR�� Ư���� ���� �ϳ��� ���̸� ������ �ؼ��ϱ� ������ ���� ������ ���ϰ�� �ڸ� �˻����� �ʴ� ��� �̿�
			break;
		}
		previous = temp;
		// ���߿� temp���� ������ ���� ���� previous�� �̵��ϱ� �� temp�� ��ġ ����
		if (temp->key > key) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}

	if (temp == NULL) {
		// ã���� �ϴ� key���� ���� ���
		printf(" [%d] is not found", key);
		return -1;
	}
	else {
		if (temp->left == NULL && temp->right == NULL) {
			// key���� �ִ� ��忡 �ڽĳ�尡 ���� ���
			if (previous->left == temp) {
				// temp�� �ش��ϴ� ��带 ã�� ���� �����ֱ�
				previous->left = NULL;
			}
			else {
				previous->right = NULL;
			}
			free(temp);
			return 0;
		}
		else {
			temp2 = temp;
			if (temp->right != NULL) {
				// key���� �ִ� ��忡 �ڽĳ�尡 �ְ�, �� �ڽĳ���� rigth�ڽ��� �ִ� ���
				previous = NULL;
				// ������ previous�� temp2 ������ ��带 ����Ű�� �����Ƿ� �ʱ�ȭ
				temp = temp->right;
				for (; temp->left; previous = temp, temp = temp->left);
				//temp�� left���� ���� ���� ���� ã�Ƽ� �̵�
				temp2->key = temp->key;
				// key�� �̵�
				if (previous != NULL) {
					//temp�� left��尡 ������ ���
					previous->left = temp->right;
				}
				else {
					// temp�� left ��尡 �������� ���� ���
					temp2->right = temp->right;
				}
				temp->right = NULL;
				free(temp);
				return 0;
			}
			else {
				// key���� �ִ� ��忡 �ڽĳ�尡 �ְ�, �� �ڽĳ���� left�ڽĸ� �ִ� ���
				temp2 = temp;
				previous = NULL;
				// ������ previous�� temp2 ������ ��带 ����Ű�� �����Ƿ� �ʱ�ȭ
				temp = temp->left;
				for (; temp->right; previous = temp, temp = temp->right);
				//temp�� right���� ���� ���� ū���� ã�Ƽ� �̵�
				temp2->key = temp->key;
				// key�� �̵�
				if (previous != NULL) {
					//temp�� right��尡 ������ ���
					previous->right = temp->left;
				}
				else {
					// temp�� right ��尡 �������� ���� ���
					temp2->left = temp->left;
				}
				temp->left = NULL;
				free(temp);
				return 0;
			}
		}
	}
}

// ����� ������� ��带 ��ü�ϴ� �Լ�
void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

// ��带 ��ü�ϴ� �Լ�
int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}


// stack�� ����ϱ� ���� �Լ����Դϴ�
// stack�� �ִ� ���� ��ȯ�ϴ� �Լ�
Node* pop()
{
	Node* temp = NULL;
	if (top != -1) {
		temp = stack[top--];
		stack[top + 1] = NULL;
	}
	return temp;
}

// stack�� ���� ����ִ� �Լ�
void push(Node* aNode)
{
	if (top + 1 != MAX_STACK_SIZE)
		stack[++top] = aNode;
	else
		printf("Stack Overflow!!");
}


// ť�� �����ϱ� ���� �Լ����Դϴ�
// ť�� �ִ� ���� ��ȯ�ϴ� �Լ�
Node* deQueue()
{
	Node* temp = NULL;
	if (front != rear) {
		// ť�� ������� �ʴٸ� ����
		front = (front + 1) % MAX_QUEUE_SIZE;
		temp = queue[front];
		queue[front] = NULL;
	}
	return temp;
}

// ť�� ���� ����ִ� �Լ�
void enQueue(Node* aNode)
{
	if (front != rear + 1) {
		// ť�� �� ���� �ʾҴٸ� ����
		rear = (rear + 1) % MAX_QUEUE_SIZE;
		queue[rear] = aNode;
	}
	else {
		printf("Queue is full");
	}
}
