#include<stdio.h>
#include<stdlib.h> // 동적할당을 위한 코드
#define MAX_VERTEX 20

typedef struct Vertex {
	int num;                      // vertex number
	struct Vertex* link;          // link to a next adjacent vertex
}Vertex;

typedef struct VertexHead {
	Vertex* head;                 // linked list of all adjacent vertices
}VertexHead;

typedef struct Graph {
	VertexHead* vlist;            // list of all vertices : vlist[MAX_VERTEX]
}Graph;

void createGraph(VertexHead **vlist);               // empty graph creation   // 그래프 초기 연결인 Graph에 malloc으로 배열 할당
void destroyGraph(VertexHead **vlist); // 만들어져 있는 그래프 해체
void insertVertex(int vertex_num); // 만들어진 그래프에 vertex 추가 ( 존제하는, 단 vertex는 양의 정수로 순차적으로 증가 )
void deleteVertex(int vertex_num, VertexHead *vlist); // 만들어진 vertex를 삭제하며 그에 연결된 링크기 있다면 헤제
void insertEdge(int vertex_num, int edge_num, VertexHead *vlist);   // 만들어진 vertex에 연결된 vertex를 linked list로 연결
void deleteEdge(int vertex_num, int edge_num, VertexHead *vlist);   // 만들어진 vertex에 연결된 vertex의 linked list를 삭제하는 함수
void depthFS(int vertex_num, VertexHead* vlist);   // 깊이 우선 탐색
void breadthFS(int vertex_num, VertexHead* vlist);   // 너비 우선 탐색
void printGraph(VertexHead *vlist);   // 만들어진 Graph를 출력하는 함수

/* 따로 구현하는 것들 */
void printTitle();  // 실행 가능한 명령어 목록 출력
void CheckGraph(VertexHead *vlist);  // vertex, edge 에 삭제가 일어났을때, 그래프가 온전한지 판단해 주는 함수
void swap(int *a, int *b);  // data를 교환해 주는 함수
void inputData(int *a, char* str);    // data의 값을 입력받는 함수
int Error_ck(int vertex_num, int edge_num, VertexHead* vlist);  // 각각의 Error를 검사하고 그에 맞는 에러 메시지를 출력하는 함수

// Graph가 온전한지 확인하기 위해 쓰는 자료구조
int stack[MAX_VERTEX];
int top = -1;

void pop();           // stack에서 data를 뺴는 함수 ( 후입선출 )
void push(int node);  // stack에 data를 넎는 함수
int get();            // stack에서 현재 top이 가리키는 data를 반환하는 함수

// 너비우선 탐색 구현할때 사용할 자료구조
int queue[MAX_VERTEX];
int front = 0;
int rear = 0;

int deQueue();              // 큐에서 data를 빼는함수 ( 선입선출 )
void enQueue(int aNode);    // 큐에 data를 넣는 함수

int exist_vertex[MAX_VERTEX] = { 0, };  // 각각의 vertex에 대해 존제 여부
int visit_vertex[MAX_VERTEX] = { 0, };  // 존제하는 vertex에 대해 방문 여부

int main(void) {
	Graph start;
	int vertex_num, edge_num;
	start.vlist = NULL;

	char command;
	printf("=====================[ 2019038068 김성욱 ]====================\n");
	do {
		printTitle();
		scanf(" %c", &command);

		switch (command)
		{
		case 'g':case 'G':
			createGraph(&start.vlist);
			break;
		case 'd':case 'D':
			destroyGraph(&start.vlist);
			break;
		case 'v':case 'V':
			if (start.vlist == NULL) {                        // vlist에 동적할당이 되지 않았을 경우 오류 발생
				printf("[ Error : creatGraph first ]\n");
			}
			else {
				inputData(&vertex_num, "Insert Vertex = ");
				insertVertex(vertex_num);
			}
			break;
		case 'r':case 'R':
			inputData(&vertex_num, "Delete Vertex = ");
			deleteVertex(vertex_num, start.vlist);
			break;
		case 'e':case 'E':
			inputData(&vertex_num, "Chose Vertex = ");
			inputData(&edge_num, "insert Edge = ");;
			insertEdge(vertex_num, edge_num, start.vlist);
			break;
		case 't':case 'T':
			inputData(&vertex_num, "Chose Vertex = ");
			inputData(&edge_num, "Delete Edge = ");
			deleteEdge(vertex_num, edge_num, start.vlist);
			break;
		case 'h':case 'H':
			inputData(&vertex_num, "Chose Start Vertex = ");
			depthFS(vertex_num, start.vlist);
			break;
		case 'b':case 'B':
			inputData(&vertex_num, "Chose Start Vertex = ");
			breadthFS(vertex_num, start.vlist);
			break;
		case 'p':case 'P':
			printGraph(start.vlist);
			break;
		case 'q':case 'Q':
			destroyGraph(&start.vlist);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');
	return 0;
}

void inputData(int *a, char* str) {   // 정수형 data값을 입력받는 함수
	printf("%s", str);
	scanf(" %d", &(*a));
}

void printTitle() {  // 실행 가능한 명령어 목록 출력
	printf("\n=============================================================\n");
	printf(" 1. createGraph  :  g                  2. destroyGraph  :  d  \n");
	printf(" 3. insertVertex :  v                  4. deleteVertex  :  r  \n");
	printf(" 5. insertEdge   :  e                  6. deleteEdge    :  t  \n");
	printf(" 7. depthFS      :  h                  8. breadFS       :  b  \n");
	printf(" 9. printGrapth  :  p                 10. Qite          :  q  \n");
	printf("=============================================================\n");
	printf("Command =");
}

void createGraph(VertexHead **vlist) {                                                                 // 그래프 초기 연결인 Graph에 malloc으로 배열 할당
	if ((*vlist)) {
		destroyGraph(&(*vlist));
	}
	(*vlist) = (VertexHead *)malloc(sizeof(VertexHead) * MAX_VERTEX);                                  // 동적할당( 초기 MAX_VERTEX의 수만큼 )
	printf("vlist : %p\n", &(*vlist));
	for (int i = 0; i < MAX_VERTEX; i++) {
		(*vlist)[i].head = NULL;
		printf("vlist[%2d] : %p   vlist[%2d].head = %p\n", i, &(*vlist)[i], i, (*vlist)[i].head);     // 동적할당 & 초기화가 제대로 됬는지 확인하는 코드 나중에 삭제?
	}
}

void destroyGraph(VertexHead **vlist) {                                                                // 만들어져 있는 그래프 해체dd -> 즉 최악의 경우 O( MAX_VERTEX의 제곱)d
	Vertex *temp = NULL;
	Vertex *previous = NULL;
	if (*vlist == NULL) {                        // vlist에 동적할당이 되지 않았을 경우 오류 발생
		printf("[ Error : creatGraph first ]\n");
		return;
	}
	for (int i = 0; i < MAX_VERTEX; i++) {       // 아래의 과정을 모든 노드가 반복 , O(MAX_VERTEX)
		temp = (*vlist)[i].head;                 // i+1 번째 vertex에 연결되 있는 vertex들을 삭제하기 위해 temp로 주솟값 복사
		while (temp) {                           // temp가 NULL이 아닐떄 까지 반복 , O(MAX_VERTEX)
			previous = temp;                     // temp가 가리키는 공간을 previous로 이동 후
			temp = temp->link;                   // temp를 다음 노드로 이동
			previous->link = NULL;               // 다음 노드와의 연결을 해체한 후
			free(previous);                      // previous가 가리키는 노드 해제
		}
		previous = NULL;                         // 초기화
		(*vlist)[i].head = NULL;                 // 연결된 linked list를 해체한 후 head가 가리키는 값을 NULL로 변경
		exist_vertex[i] = 0;                     // i+1 번째 vertex에 대해 종료
	}
	free((*vlist));
	(*vlist) = NULL;
}

void insertVertex(int vertex_num) {               // 만들어진 그래프에 vertex 추가 ( 존제하는, 단 vertex는 양의 정수로 순차적으로 증가 )
	if (!(0 < vertex_num && vertex_num <= 20)) {
		printf("[ Error : Wrong input ]\n");
	}
	if (!exist_vertex[vertex_num - 1]) exist_vertex[vertex_num - 1] = 1;         // vertex의 number가 양의 정수부터 순차적으로 시작됨으로 i번째 index를 i+1번째 vertex로 생각
	else printf("[ Error : Vertex Already Exist ]\n");
}

void deleteVertex(int vertex_num, VertexHead *vlist) {     // 만들어진 vertex를 삭제하며 그에 연결된 링크기 있다면 헤제
	Vertex *temp = NULL;
	Vertex *previous = NULL;
	Vertex *vertex = NULL;
	int find_vertex;
	if (Error_ck(vertex_num, vertex_num, vlist)) {  // 오류가 있는 지 확인하는 함수 오류가 있을 경우 1이 return되어 종료, 아닐 경우 0이 리턴되어 계속 실행
		return;
	}

	while (1) {
		temp = vlist[vertex_num - 1].head;                 // 계속해서 처음 노드가 바뀌므로 ( 밑에서 호출하는 deleteEdge로 인해 )
		if (temp == NULL) break;                           // 모든 linked list를 삭제했을 경우 NULL이 나옴으로 이때 반복 종료
		deleteEdge(vertex_num, temp->num, vlist);          // deleteVertex는 deleteEdge를 linked list의 수 만큼 반복한 것이므로 deleteEdeg 호충
	}
	vlist[vertex_num - 1].head = NULL;                     // 연결되있는 주솟값을 NULL로 바꿈
	exist_vertex[vertex_num - 1] = 0;                      // 존제여부를 존제하지 않음으로 바꿈
}

void swap(int *a, int *b) {                                // a와 b의 값을 바꿔주는 함수
	int temp = *a;
	*a = *b;
	*b = temp;
}

void insertEdge(int vertex_num, int edge_num, VertexHead *vlist) {				// 만들어진 vertex에 연결된 vertex를 linked list로 연결
	Vertex* temp = NULL;
	Vertex* node = NULL;

	if (Error_ck(vertex_num, edge_num, vlist)) {                              // 오류가 있는 지 확인하는 함수 오류가 있을 경우 1이 return되어 종료, 아닐 경우 0이 리턴되어 계속 실행
		return;
	}
	if (edge_num == vertex_num) {
		printf("[ Error : %d can't have %d ]\n", vertex_num, edge_num);
		return;
	}
	for (int i = 0; i < 2; i++) {												// vertex_num에 edge_num을 연결하고, edge_num에 vertex_num을 연결해야 하는데 이는 서로 코드가 같으므로 2번 반복
		temp = (Vertex *)malloc(sizeof(Vertex));
		temp->link = NULL;
		temp->num = edge_num;
		if (vlist[vertex_num - 1].head == NULL) {								// 연결된 노드가 없다면( 기존에 )
			vlist[vertex_num - 1].head = temp;									// head에 temp를 바로 연결
		}
		else {
			node = vlist[vertex_num - 1].head;									// 기존에 노드가 있을 경우 head의 값을 받아
			for (; node->link && node->num != edge_num; node = node->link) {};  // 끝으로 이동, 혹 중간에 같은 값이 있을 경우도 중지
			if (node->num != edge_num)                                          // node의 link가 NULL이여서 나온건지, node의 num이 같아서 나온건지 모름으로, 이를 확인하는 코드
				node->link = temp;                                              // 연결
		}
		swap(&vertex_num, &edge_num);                                           // vertex_num과 edge_num의 위치를 바꿔주는 코드
	}
}

void deleteEdge(int vertex_num, int edge_num, VertexHead *vlist) {      // 만들어진 vertex에 연결된 vertex의 linked list를 삭제하는 함수
	Vertex* temp = NULL;
	Vertex* node = NULL;

	if (Error_ck(vertex_num, edge_num, vlist)) {                        // 오류가 있는 지 확인하는 함수 오류가 있을 경우 1이 return되어 종료, 아닐 경우 0이 리턴되어 계속 실행
		return;
	}
	if (edge_num == vertex_num) {
		printf("[ Error : %d can't have %d ]\n", vertex_num, edge_num);
		return;
	}

	for (int i = 0; i < 2; i++) {                                       // insertEdge와 같은 이유이기 떄문에 2번 반복( vertex_num, edge_num에 서로 각각 연결해 줘야 한다 )
		temp = vlist[vertex_num - 1].head;                              // vertex_num이 가지고 있는 head의 값을 temp로 이동
		if (!temp) {
			printf("[ Error : No Edge ]\n");
			return;
		}
		while (temp && temp->num != edge_num) {                                 // 삭제를 해야 함으로 이를 찾을때 까지 이동( 반복 )
			node = temp;                                                // 찾는 노드가 중간에 있을 경우 앞뒤의 연결을 끊어줘야 함으로 사용
			temp = temp->link;                                          // 다음 노드의 값으로 이동
		}
		if (temp == NULL) {                                             // tmpe == NULL일 경우, 찾는 노드가 없는 것이므로
			printf("[ Error : %d Edge Doesn't Exist ]\n", edge_num);    // 오류 발생
			return;
		}
		if (node == NULL) {                                             // node == NULL일 경우, 첫번째 노드를 삭제하는 경우 이므로
			vlist[vertex_num - 1].head = temp->link;                    // head에 다음노드 연결
		}
		else {
			node->link = temp->link;                                    // 중간일 경우
		}
		temp->link = NULL;
		free(temp);
		node = NULL;
		swap(&vertex_num, &edge_num);
	}
}

void printGraph(VertexHead *vlist) {                          // 만들어진 Graph를 출력하는 함수
	Vertex* temp = NULL;
	if (vlist == NULL) {                                      // vlist에 동적할당이 되지 않았을 경우 오류 발생
		printf("[ Error : creatGraph first ]\n");
		return;
	}
	for (int i = 0; i < MAX_VERTEX; i++) {                    // 0~19까지 반복
		if (exist_vertex[i] == 1) {                           // vertex가 존제할 경우
			printf("[ Vertex %d ]", i + 1);                   // vertex의 해당 번호( 즉 인덱스 )를 출력하고
			printf(" [ Linked Vertex ] ");                    // 이에 연결되있는 linked list들을 출력한다
			temp = vlist[i].head;                             // temp에 head값 할당
			while (temp) {                                    // temp가 NULL 이 될때 까지 반복
				printf(" %d ", temp->num);                    // temp의 num을 출력
				temp = temp->link;                            // 다음 노드로 이동
			}
			printf("\n");
		}
	}
}

void CheckGraph(VertexHead *vlist) {                             // 온전한 그래프인지 ( 분리된 부분이 없는지 ) 확인하는 함수
	int vertex[MAX_VERTEX] = { 0, }, j = -1;
	for (int i = 0; i < MAX_VERTEX; i++) {
		if (visit_vertex[i] == 0 && exist_vertex[i] == 1) {      // 탐색을 하며 바꿨던 visiting flag를 다시 전부 0으로 바꾸는 작업
			vertex[++j] = i + 1;                                 // 이와 동시에 vertex가 존제하는데 visiting가 0일경우 방문이 안된 경우임으로, ( 즉, 연결이 되지 않은 경우 )  그 값을 저장
			//deleteVertex(i + 1, vlist);                      // 연결이 끊어진 vertex의 삭제( 교수님께서 연결이 끊어진 경우에도 그래프를 놔두라고 하셨서 일단 주석처리 해놨습니다. 주석을 해체하시면 그래프연결이 끊어 졌을시 이를 해체합니다.
		}
		visit_vertex[i] = 0;                                     // visiting vertex를 다시 0으로 초기화
	}

	if (j != -1) {                                               // j의 값이 연결되지 않은 vertex의 수임으로
		printf("\n===============[ error : graph disconnected ]================\n");
		printf("[ vertex num ]");
		for (int h = 0; h <= j; h++) {                               // 0~j까지 반복하면서 출력
			printf(" %2d", vertex[h]);
		}
		puts("");
		//printf("=============[ being delete disconnected graph ]=============\n");
	}
}

void depthFS(int vertex_num, VertexHead* vlist) {  // 깊이 우선 탐색
	if (Error_ck(vertex_num, vertex_num, vlist)) {  // 오류가 있는 지 확인하는 함수 오류가 있을 경우 1이 return되어 종료, 아닐 경우 0이 리턴되어 계속 실행
		return;
	}
	printf(" [ %d ] ", vertex_num);                // 초기 시작값 출력 ( 각각의 vertex는 배열의 인덱스를 사용함으로 )
	Vertex* temp = NULL;
	push(vertex_num);                              // 시작 vertex_num을 stack에 집어 넣는다
	visit_vertex[vertex_num - 1] = 1;              // 또한 해당 vertex에 대한

	while (top != -1) {
		temp = vlist[get()].head;                  // stack의 top이 현제 가리키고 있는 위치의 num값에 해당하는 vertex에 연결된 vlist[num-1].head의 값을 받는다
		while (temp) {                             // temp에 연결된 linked list 탐색
			if (!visit_vertex[temp->num - 1]) {    // linked list에 연결되있는 노드가 방문 되지 않았다면
				printf(" [ %d ] ", temp->num);     // 이의 vertex num을 출력하고
				push(temp->num);                   // vertex_num을 stack에 집어넣는다
				visit_vertex[temp->num - 1] = 1;   // 또한 이 vertex에 대해 방문했다고 표시한다
				break;
			}
			temp = temp->link;                     // 방문을 한 경우 다음 노드로 이동
		}
		if (temp == NULL) pop();                   // temp가 NULL일 경우, stack에서 값을 뺴낸다 ( 이를 top이 -1, 즉 stack 안에 값이 없을때 까지 반복 )
	}
	CheckGraph(vlist);                             // 연결되지 않은 vertex가 있는지 확인해 보는 함수
}

void pop() {                     // stack에 값을 뺴는 함수
	stack[top--] = NULL;         // top의 위치를 NULL로 바꾼다음 1만큼 줄인다
}

void push(int node) {           // stack에 값을 넣는 함수
	stack[++top] = node;         // top의 값을 1만큼 증가시킨 후 이자리에 node를 삽입
}

int get() {                      // 현제 top이 가리키는 위치의 num의 값을 리턴
	return stack[top] - 1;
}

void breadthFS(int vertex_num, VertexHead* vlist) {                    // 너비 우선 탐색
	int v_num;
	Vertex *temp = NULL;
	if (Error_ck(vertex_num, vertex_num, vlist)) {  // 오류가 있는 지 확인하는 함수 오류가 있을 경우 1이 return되어 종료, 아닐 경우 0이 리턴되어 계속 실행
		return;
	}
	enQueue(vertex_num);                                               // 큐에 vertex_num을 넣는다
	for (;;) {                                                         // 무한 반복
		v_num = deQueue();                                             // 큐에 있는 값을 받는다
		if (v_num == MAX_VERTEX + 1) break;                            // 이때 값이 MAX_VERTEX +1이라면 종료 ( 큐에 더이상 값이 없는 경우 이다 )
		printf(" [ %d ] ", v_num);
		temp = vlist[v_num - 1].head;                                  // 그리고 이에 해당하는 linked list의 시작 값을 받는다
		while (temp) {                                                 // temp가 NULL이 되기 전까지
			if (!visit_vertex[temp->num - 1]) enQueue(temp->num);         // 방문하지 않았다면 큐에 값을 삽입
			temp = temp->link;                                         // temp를 다음 노드로 이동
		}
	}                                                                  // 깊이 우선 탐색이므로 시작 vertex를 기점으로 연결되있는 vertex중 방문하지 않은 노드를 모두 큐에 넣은뒤, 선입선출이라는 큐의 특성을 사용해 가장 앞부분을 빼서 뒷부분에 해당 vertex에서 접근할 수 있는 노드( 방문하지 않는 )를 넣는 식으로 작동한다
	CheckGraph(vlist);                                                 // 연결되지 않은 vertex가 있는지 확인해 보는 함수
}

int deQueue() {                         // 큐에서 값을 빼눈 함수
	int temp;
	if (front == rear) {                // front와 rear가 같을 경우 큐가 다 비어있는 경우 임으로
		return MAX_VERTEX + 1;          // MAX_VERTEX+1의 값을 리턴
	}
	front = ++front % MAX_VERTEX;       // front의 값을 1만큼 증가 ( 원형 큐 임으로 MAX_VERTEX로 나누어 표시한다 )
	temp = queue[front];                // front가 가리키는 곳에 있는 data를 temp로 옮기고
	queue[front] = NULL;                // 초기화 시킨다
	return temp;                        // temp를 리턴한다
}

void enQueue(int aNode) {               // 큐에 값을 넣는 함수
	rear = ++rear % MAX_VERTEX;         // rear의 값을 1만큼 증가시킨다 ( 원형 큐 임으로 MAX_VERTEX로 나누어 표시한다 )
	queue[rear] = aNode;                // rear가 가리키는 곳에 data 삽입
	visit_vertex[aNode - 1] = 1;        // 저장한 data 즉, 해당 vertex에 대한 visiting flag를 1로 바꾼다 ( 방문했다고 바꾼다 )
}

int Error_ck(int vertex_num, int edge_num, VertexHead* vlist) {
	if (vlist == NULL) {																// vlist에 동적할당이 되지 않았을 경우 오류 발생
		printf("[ Error : creatGraph first ]\n");
		return 1;
	}

	if (!(0 < vertex_num && vertex_num <= 20) || !(0 < edge_num && edge_num <= 20)) {	// 정해놓은 vertex의 범위를 벗어나면 error
		printf("[ Error : Wrong input ]\n");
		return 1;
	}

	if (exist_vertex[vertex_num - 1] == 0) {											// 해당 vertex가 존제하지 않을 시 오류
		printf("[ Error : %d Vertex Doesn't Exist ]\n", vertex_num);
		return 1;
	}

	if (edge_num != 0 && exist_vertex[edge_num - 1] == 0) {												// 해당 vertex가 존제하지 않을 시 오류
		printf("[ Error : %d Vertex Doesn't Exist ]\n", edge_num);
		return 1;
	}
	return 0;
}