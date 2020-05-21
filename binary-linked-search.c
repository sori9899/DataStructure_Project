/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);                                                            // head를 생성

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */                 // 중위순회
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */                // 선위순회
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */               // 후위순회
int insert(Node* head, int key);  /* insert a node to the tree */                       // 노드삽입, 같은 같이 있을 경우 무시
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */        // key값에 해당하는 노드의 자식노드가 없으면 삭제, 아닐경우 오류출력
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */           // 제귀적 방식으로 key값과 동일한 data 값이 있는 노드를 찾아 주소를 반환
Node* searchIterative(Node* head, int key);  /* search the node for the key */          // 반복적 방식으로 key값과 동일한 data 값이 있는 노드를 찾아 주소를 반환
int freeBST(Node* head); /* free all memories allocated to the tree */                  // 노드를 해제하는 함수

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("2019038068 김성욱");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {               // head를 생성

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)                         // 이전 노드가 있을경우
		freeBST(*h);                        // 헤제해 준다

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)            // 중위순회
{
	if (ptr != NULL) {                      // NULL일 경우 무시
		inorderTraversal(ptr->left);        // inorder이므로 왼쪽 노드부터 탐색
		printf("%d ", ptr->key);            // 해당 노드의 data값 출력
		inorderTraversal(ptr->right);       // 그 다음 오른쪽 노드 탐색
	}
}

void preorderTraversal(Node* ptr)           // 선위순회
{
	if (ptr != NULL) {                      // NULL일 경우 무시
		printf("%d ", ptr->key);            // preorder이므로 해당 노드의 data값 부터 출력
		preorderTraversal(ptr->left);       // 왼쪽 노드 탐색 후
		preorderTraversal(ptr->right);      // 오른쪽 노드 탐색
	}
}

void postorderTraversal(Node* ptr)          // 후위순회
{
	if (ptr != NULL) {                      // NULL일 경우 무시
		postorderTraversal(ptr->left);      // postorder이므로 왼쪽 노드부터 탐색
		postorderTraversal(ptr->right);     // 오른쪽 노드 탐색
		printf("%d ", ptr->key);            // 해당 노드의 data값 출력
	}
}


int insert(Node* head, int key)             // 노드삽입, 같은 같이 있을 경우 무시
{
	Node *node = head;
	Node *temp = NULL;
	if (head == NULL) {                     // head가 NULL일 경우 오류 발생
		printf("initializeBST first\n");
		return -1;
	}
	temp = (Node *)malloc(sizeof(Node));      // 노드 생성

	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;
	if (node->left == NULL) {
		node->left = temp;
	}
	else {
		node = node->left;                  // 처음 head->left에 트리의 루트가 있으므로 이동
		while (1) {
			if (node->key == key) {         // 같은 값이 있을 경우 무시
				return 0;
			}
			else if (node->key < key) {    // node-> key보다 key값이 클경우
				if (node->right == NULL) {  // node->right가 비어있다면
					node->right = temp;     // 노드 연결
					return 0;
				}
				else
					node = node->right;     // 아닐경우 node->right로 이동
			}
			else {                         // node-> key보다 key값이 작을 경우
				if (node->left == NULL) {   // node->right가 비어있다면
					node->left = temp;      // 노드 연결
					return 0;
				}
				else
					node = node->left;      // 아닐경우 node->left로 이동
			}
		}
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)     // key값에 해당하는 노드의 자식노드가 없으면 삭제, 아닐경우 오류출력
{
	Node* node = head;
	Node* previous = NULL;

	while (1) {
		if (node == NULL || node->key == key) {  // node가 NULL 혹은 key값과 node->key가 같을 경우 반복 중지
			break;
		}
		previous = node;                         // 삭제할 노드와의 연결을 끊기 위해 이전 노드의 주소 저장
		if (node->key <= key && node != head) {  // key값이 클경우 right으로 이동 & head 가 아닐경우
			node = node->right;
		}
		else
			node = node->left;
	}

	if (node == NULL) {                          // key값과 같은 값을 가진 노드가 존제하지 않는 경우
		printf("%d is not Found\n", key);
		return -1;
	}
	else if (node->left != node->right) {        // 이 조건을 만족하는 경우는 둘다 NULL일때 이므로
		printf("%d is Not LeafNode\n", node->key); // left와 right의 값이 다를 경우 자식이 존제하는 경우이므로 오류
		return -1;
	}
	else {
		printf("Delet %d", node->key);           // key값과 동일한 data가 저장된 Node를 정상적으로 찾았을 경우
		if (previous->left == node) {            // 이전 노드와의 연결을 해체하는 부분
			previous->left = NULL;
		}
		else {
			previous->right = NULL;
		}
		free(node);
		return 0;
	}
}

Node* searchRecursive(Node* ptr, int key)        // 제귀적 방식으로 key값과 동일한 data 값이 있는 노드를 찾아 주소를 반환
{
	Node* temp = NULL;
	if (ptr == NULL || ptr->key == key) {        // NULL or node의 data값이 key값과 같을 경우
		return ptr;                              // 제귀 종료
	}
	if (ptr->key > key)                          // node의 data와 key 값을 비교해 이동할 위치 결정
		temp = searchRecursive(ptr->left, key);  // 제귀함수 호출
	else
		temp = searchRecursive(ptr->right, key); // 제귀함수 호출

	if (temp != NULL) {                          // 노드의 위치를 찾았다면 값을 반환
		return temp;
	}

	return NULL;
}

Node* searchIterative(Node* head, int key)       // 반복적 방식으로 key값과 동일한 data 값이 있는 노드를 찾아 주소를 반환
{
	Node* node = head->left;
	while (1) {
		if (node == NULL || node->key == key) {  // NULL or node의 data값이 key값과 같을 경우
			return node;                         // 반복종료
		}
		if (node->key <= key) {                  // node가 움직일 위치 결정
			node = node->right;
		}
		else
			node = node->left;
	}
}


int freeBST(Node* head)                          // 노드를 해제하는 함수
{
	if (head != NULL) {                          // head가 NULL이 아닐 경우
		freeBST(head->left);                     // 먼저 left로 이동
		if (head->right != head)                  // head가 아닐경우
			freeBST(head->right);                // right로 이동
		free(head);                              // head 해체
	}
	head = NULL;
	return 0;
}
