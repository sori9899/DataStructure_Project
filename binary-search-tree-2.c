/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */
// right노드부터 탐색하는 방식으로 코드를 작성하였습니다
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

	printf("2019038068 김성욱");
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

// 노드를 초기화 하는 함수
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


// 재귀적 방식으로 inorder 탐색
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
 // 반복적 방식으로 inordor 탐색
void iterativeInorder(Node* node)
{
	for (;;) {
		// 무한반복
		for (; node; node = node->left) {
			// node의 왼쪽부터 탐색해야 함으로 일단 왼쪽부터 탐색
			push(node);
			// stack에 node의 주소 저장
		}
		node = pop();
		// 왼쪽에 대한 탐색이 다 끝났으면 pop()

		if (node == NULL) break;
		// 만약 top이 -1인경우 NULL을 반환하며, 이는 곧 스택이 비었다는 뜻이므로 종료

		printf(" [%d] ", node->key);
		// node의 data 값 출력
		node = node->right;
		// node의 오른쪽으로 이동
	}
}

/**
 * textbook: p 225
 */
 // 반복적 방식으로 ㅇ노드의 래밸순 출력
void levelOrder(Node* ptr)
{
	front = 0;
	rear = 0;
	// 원형 큐에선 front가 가리키는 값을 공백으로 두어 이를 이용해
	// 가득찬 상태와 비어있는 상태를 구분함으로 0으로 초기화
	enQueue(ptr);
	// 초기값을 삽입후
	for (;;) {
		ptr = deQueue(ptr);
		// stack에 있는 값을 가져온다
		if (!ptr) break;
		// 그값이 NULL이 아니라면
		printf(" [%d] ", ptr->key);
		// 출력후 자식노드 삽입
		if (ptr->left != NULL) {
			enQueue(ptr->left);
		}
		if (ptr->right != NULL) {
			enQueue(ptr->right);
		}
	}
}

// 노드를 삽입하는 함수
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

// 노드를 삭제하는 함수
int deleteNode(Node* head, int key)
{
	Node *temp = head->left;
	Node *temp2 = NULL;
	Node *previous = head;
	for (;;) {
		if (temp == NULL || temp->key == key) {
			// 반복하며 검사, temp가 NULL인 경우 temp->key값을 검사하면 오류가 발생함으로 temp==NULL부터 검사
			// OR의 특성상 둘중 하나라도 참이면 참으로 해석하기 때문에 앞의 조건이 참일경우 뒤를 검사하지 않는 방식 이용
			break;
		}
		previous = temp;
		// 나중에 temp와의 연결을 끊기 위해 previous에 이동하기 건 temp의 위치 저장
		if (temp->key > key) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}

	if (temp == NULL) {
		// 찾고자 하는 key값이 없는 경우
		printf(" [%d] is not found", key);
		return -1;
	}
	else {
		if (temp->left == NULL && temp->right == NULL) {
			// key값이 있는 노드에 자식노드가 없는 경우
			if (previous->left == temp) {
				// temp에 해당하는 노드를 찾아 연결 끊어주기
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
				// key값이 있는 노드에 자식노드가 있고, 그 자식노등의 rigth자식이 있는 경우
				previous = NULL;
				// 기존의 previous는 temp2 이전의 노드를 가리키고 있으므로 초기화
				temp = temp->right;
				for (; temp->left; previous = temp, temp = temp->left);
				//temp의 left값중 가장 작은 값을 찾아서 이동
				temp2->key = temp->key;
				// key값 이동
				if (previous != NULL) {
					//temp에 left노드가 존재할 경우
					previous->left = temp->right;
				}
				else {
					// temp에 left 노드가 존제하지 않을 경우
					temp2->right = temp->right;
				}
				temp->right = NULL;
				free(temp);
				return 0;
			}
			else {
				// key값이 있는 노드에 자식노드가 있고, 그 자식노등의 left자식만 있는 경우
				temp2 = temp;
				previous = NULL;
				// 기존의 previous는 temp2 이전의 노드를 가리키고 있으므로 초기화
				temp = temp->left;
				for (; temp->right; previous = temp, temp = temp->right);
				//temp의 right값중 가장 작은 큰값을 찾아서 이동
				temp2->key = temp->key;
				// key값 이동
				if (previous != NULL) {
					//temp에 right노드가 존재할 경우
					previous->right = temp->left;
				}
				else {
					// temp에 right 노드가 존제하지 않을 경우
					temp2->left = temp->left;
				}
				temp->left = NULL;
				free(temp);
				return 0;
			}
		}
	}
}

// 재귀적 방식으로 노드를 해체하는 함수
void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

// 노드를 해체하는 함수
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


// stack을 사용하기 위한 함수들입니다
// stack에 있는 값을 반환하는 함수
Node* pop()
{
	Node* temp = NULL;
	if (top != -1) {
		temp = stack[top--];
		stack[top + 1] = NULL;
	}
	return temp;
}

// stack에 값을 집어넣는 함수
void push(Node* aNode)
{
	if (top + 1 != MAX_STACK_SIZE)
		stack[++top] = aNode;
	else
		printf("Stack Overflow!!");
}


// 큐를 구현하기 위한 함수들입니다
// 큐에 있는 값을 반환하는 함수
Node* deQueue()
{
	Node* temp = NULL;
	if (front != rear) {
		// 큐가 비어있지 않다면 삭제
		front = (front + 1) % MAX_QUEUE_SIZE;
		temp = queue[front];
		queue[front] = NULL;
	}
	return temp;
}

// 큐에 값을 집어넣는 함수
void enQueue(Node* aNode)
{
	if (front != rear + 1) {
		// 큐가 다 차지 않았다면 삽입
		rear = (rear + 1) % MAX_QUEUE_SIZE;
		queue[rear] = aNode;
	}
	else {
		printf("Queue is full");
	}
}
