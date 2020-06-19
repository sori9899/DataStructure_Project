#include<stdio.h>
#include<stdlib.h> // �����Ҵ��� ���� �ڵ�
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

void createGraph(VertexHead **vlist);               // empty graph creation   // �׷��� �ʱ� ������ Graph�� malloc���� �迭 �Ҵ�
void destroyGraph(VertexHead **vlist); // ������� �ִ� �׷��� ��ü
void insertVertex(int vertex_num); // ������� �׷����� vertex �߰� ( �����ϴ�, �� vertex�� ���� ������ ���������� ���� )
void deleteVertex(int vertex_num, VertexHead *vlist); // ������� vertex�� �����ϸ� �׿� ����� ��ũ�� �ִٸ� ����
void insertEdge(int vertex_num, int edge_num, VertexHead *vlist);   // ������� vertex�� ����� vertex�� linked list�� ����
void deleteEdge(int vertex_num, int edge_num, VertexHead *vlist);   // ������� vertex�� ����� vertex�� linked list�� �����ϴ� �Լ�
void depthFS(int vertex_num, VertexHead* vlist);   // ���� �켱 Ž��
void breadthFS(int vertex_num, VertexHead* vlist);   // �ʺ� �켱 Ž��
void printGraph(VertexHead *vlist);   // ������� Graph�� ����ϴ� �Լ�

/* ���� �����ϴ� �͵� */
void printTitle();  // ���� ������ ��ɾ� ��� ���
void CheckGraph(VertexHead *vlist);  // vertex, edge �� ������ �Ͼ����, �׷����� �������� �Ǵ��� �ִ� �Լ�
void swap(int *a, int *b);  // data�� ��ȯ�� �ִ� �Լ�
void inputData(int *a, char* str);    // data�� ���� �Է¹޴� �Լ�
int Error_ck(int vertex_num, int edge_num, VertexHead* vlist);  // ������ Error�� �˻��ϰ� �׿� �´� ���� �޽����� ����ϴ� �Լ�

// Graph�� �������� Ȯ���ϱ� ���� ���� �ڷᱸ��
int stack[MAX_VERTEX];
int top = -1;

void pop();           // stack���� data�� ���� �Լ� ( ���Լ��� )
void push(int node);  // stack�� data�� ���� �Լ�
int get();            // stack���� ���� top�� ����Ű�� data�� ��ȯ�ϴ� �Լ�

// �ʺ�켱 Ž�� �����Ҷ� ����� �ڷᱸ��
int queue[MAX_VERTEX];
int front = 0;
int rear = 0;

int deQueue();              // ť���� data�� �����Լ� ( ���Լ��� )
void enQueue(int aNode);    // ť�� data�� �ִ� �Լ�

int exist_vertex[MAX_VERTEX] = { 0, };  // ������ vertex�� ���� ���� ����
int visit_vertex[MAX_VERTEX] = { 0, };  // �����ϴ� vertex�� ���� �湮 ����

int main(void) {
	Graph start;
	int vertex_num, edge_num;
	start.vlist = NULL;

	char command;
	printf("=====================[ 2019038068 �輺�� ]====================\n");
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
			if (start.vlist == NULL) {                        // vlist�� �����Ҵ��� ���� �ʾ��� ��� ���� �߻�
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

void inputData(int *a, char* str) {   // ������ data���� �Է¹޴� �Լ�
	printf("%s", str);
	scanf(" %d", &(*a));
}

void printTitle() {  // ���� ������ ��ɾ� ��� ���
	printf("\n=============================================================\n");
	printf(" 1. createGraph  :  g                  2. destroyGraph  :  d  \n");
	printf(" 3. insertVertex :  v                  4. deleteVertex  :  r  \n");
	printf(" 5. insertEdge   :  e                  6. deleteEdge    :  t  \n");
	printf(" 7. depthFS      :  h                  8. breadFS       :  b  \n");
	printf(" 9. printGrapth  :  p                 10. Qite          :  q  \n");
	printf("=============================================================\n");
	printf("Command =");
}

void createGraph(VertexHead **vlist) {                                                                 // �׷��� �ʱ� ������ Graph�� malloc���� �迭 �Ҵ�
	if ((*vlist)) {
		destroyGraph(&(*vlist));
	}
	(*vlist) = (VertexHead *)malloc(sizeof(VertexHead) * MAX_VERTEX);                                  // �����Ҵ�( �ʱ� MAX_VERTEX�� ����ŭ )
	printf("vlist : %p\n", &(*vlist));
	for (int i = 0; i < MAX_VERTEX; i++) {
		(*vlist)[i].head = NULL;
		printf("vlist[%2d] : %p   vlist[%2d].head = %p\n", i, &(*vlist)[i], i, (*vlist)[i].head);     // �����Ҵ� & �ʱ�ȭ�� ����� ����� Ȯ���ϴ� �ڵ� ���߿� ����?
	}
}

void destroyGraph(VertexHead **vlist) {                                                                // ������� �ִ� �׷��� ��üdd -> �� �־��� ��� O( MAX_VERTEX�� ����)d
	Vertex *temp = NULL;
	Vertex *previous = NULL;
	if (*vlist == NULL) {                        // vlist�� �����Ҵ��� ���� �ʾ��� ��� ���� �߻�
		printf("[ Error : creatGraph first ]\n");
		return;
	}
	for (int i = 0; i < MAX_VERTEX; i++) {       // �Ʒ��� ������ ��� ��尡 �ݺ� , O(MAX_VERTEX)
		temp = (*vlist)[i].head;                 // i+1 ��° vertex�� ����� �ִ� vertex���� �����ϱ� ���� temp�� �ּڰ� ����
		while (temp) {                           // temp�� NULL�� �ƴҋ� ���� �ݺ� , O(MAX_VERTEX)
			previous = temp;                     // temp�� ����Ű�� ������ previous�� �̵� ��
			temp = temp->link;                   // temp�� ���� ���� �̵�
			previous->link = NULL;               // ���� ������ ������ ��ü�� ��
			free(previous);                      // previous�� ����Ű�� ��� ����
		}
		previous = NULL;                         // �ʱ�ȭ
		(*vlist)[i].head = NULL;                 // ����� linked list�� ��ü�� �� head�� ����Ű�� ���� NULL�� ����
		exist_vertex[i] = 0;                     // i+1 ��° vertex�� ���� ����
	}
	free((*vlist));
	(*vlist) = NULL;
}

void insertVertex(int vertex_num) {               // ������� �׷����� vertex �߰� ( �����ϴ�, �� vertex�� ���� ������ ���������� ���� )
	if (!(0 < vertex_num && vertex_num <= 20)) {
		printf("[ Error : Wrong input ]\n");
	}
	if (!exist_vertex[vertex_num - 1]) exist_vertex[vertex_num - 1] = 1;         // vertex�� number�� ���� �������� ���������� ���۵����� i��° index�� i+1��° vertex�� ����
	else printf("[ Error : Vertex Already Exist ]\n");
}

void deleteVertex(int vertex_num, VertexHead *vlist) {     // ������� vertex�� �����ϸ� �׿� ����� ��ũ�� �ִٸ� ����
	Vertex *temp = NULL;
	Vertex *previous = NULL;
	Vertex *vertex = NULL;
	int find_vertex;
	if (Error_ck(vertex_num, vertex_num, vlist)) {  // ������ �ִ� �� Ȯ���ϴ� �Լ� ������ ���� ��� 1�� return�Ǿ� ����, �ƴ� ��� 0�� ���ϵǾ� ��� ����
		return;
	}

	while (1) {
		temp = vlist[vertex_num - 1].head;                 // ����ؼ� ó�� ��尡 �ٲ�Ƿ� ( �ؿ��� ȣ���ϴ� deleteEdge�� ���� )
		if (temp == NULL) break;                           // ��� linked list�� �������� ��� NULL�� �������� �̶� �ݺ� ����
		deleteEdge(vertex_num, temp->num, vlist);          // deleteVertex�� deleteEdge�� linked list�� �� ��ŭ �ݺ��� ���̹Ƿ� deleteEdeg ȣ��
	}
	vlist[vertex_num - 1].head = NULL;                     // ������ִ� �ּڰ��� NULL�� �ٲ�
	exist_vertex[vertex_num - 1] = 0;                      // �������θ� �������� �������� �ٲ�
}

void swap(int *a, int *b) {                                // a�� b�� ���� �ٲ��ִ� �Լ�
	int temp = *a;
	*a = *b;
	*b = temp;
}

void insertEdge(int vertex_num, int edge_num, VertexHead *vlist) {				// ������� vertex�� ����� vertex�� linked list�� ����
	Vertex* temp = NULL;
	Vertex* node = NULL;

	if (Error_ck(vertex_num, edge_num, vlist)) {                              // ������ �ִ� �� Ȯ���ϴ� �Լ� ������ ���� ��� 1�� return�Ǿ� ����, �ƴ� ��� 0�� ���ϵǾ� ��� ����
		return;
	}
	if (edge_num == vertex_num) {
		printf("[ Error : %d can't have %d ]\n", vertex_num, edge_num);
		return;
	}
	for (int i = 0; i < 2; i++) {												// vertex_num�� edge_num�� �����ϰ�, edge_num�� vertex_num�� �����ؾ� �ϴµ� �̴� ���� �ڵ尡 �����Ƿ� 2�� �ݺ�
		temp = (Vertex *)malloc(sizeof(Vertex));
		temp->link = NULL;
		temp->num = edge_num;
		if (vlist[vertex_num - 1].head == NULL) {								// ����� ��尡 ���ٸ�( ������ )
			vlist[vertex_num - 1].head = temp;									// head�� temp�� �ٷ� ����
		}
		else {
			node = vlist[vertex_num - 1].head;									// ������ ��尡 ���� ��� head�� ���� �޾�
			for (; node->link && node->num != edge_num; node = node->link) {};  // ������ �̵�, Ȥ �߰��� ���� ���� ���� ��쵵 ����
			if (node->num != edge_num)                                          // node�� link�� NULL�̿��� ���°���, node�� num�� ���Ƽ� ���°��� ������, �̸� Ȯ���ϴ� �ڵ�
				node->link = temp;                                              // ����
		}
		swap(&vertex_num, &edge_num);                                           // vertex_num�� edge_num�� ��ġ�� �ٲ��ִ� �ڵ�
	}
}

void deleteEdge(int vertex_num, int edge_num, VertexHead *vlist) {      // ������� vertex�� ����� vertex�� linked list�� �����ϴ� �Լ�
	Vertex* temp = NULL;
	Vertex* node = NULL;

	if (Error_ck(vertex_num, edge_num, vlist)) {                        // ������ �ִ� �� Ȯ���ϴ� �Լ� ������ ���� ��� 1�� return�Ǿ� ����, �ƴ� ��� 0�� ���ϵǾ� ��� ����
		return;
	}
	if (edge_num == vertex_num) {
		printf("[ Error : %d can't have %d ]\n", vertex_num, edge_num);
		return;
	}

	for (int i = 0; i < 2; i++) {                                       // insertEdge�� ���� �����̱� ������ 2�� �ݺ�( vertex_num, edge_num�� ���� ���� ������ ��� �Ѵ� )
		temp = vlist[vertex_num - 1].head;                              // vertex_num�� ������ �ִ� head�� ���� temp�� �̵�
		if (!temp) {
			printf("[ Error : No Edge ]\n");
			return;
		}
		while (temp && temp->num != edge_num) {                                 // ������ �ؾ� ������ �̸� ã���� ���� �̵�( �ݺ� )
			node = temp;                                                // ã�� ��尡 �߰��� ���� ��� �յ��� ������ ������� ������ ���
			temp = temp->link;                                          // ���� ����� ������ �̵�
		}
		if (temp == NULL) {                                             // tmpe == NULL�� ���, ã�� ��尡 ���� ���̹Ƿ�
			printf("[ Error : %d Edge Doesn't Exist ]\n", edge_num);    // ���� �߻�
			return;
		}
		if (node == NULL) {                                             // node == NULL�� ���, ù��° ��带 �����ϴ� ��� �̹Ƿ�
			vlist[vertex_num - 1].head = temp->link;                    // head�� ������� ����
		}
		else {
			node->link = temp->link;                                    // �߰��� ���
		}
		temp->link = NULL;
		free(temp);
		node = NULL;
		swap(&vertex_num, &edge_num);
	}
}

void printGraph(VertexHead *vlist) {                          // ������� Graph�� ����ϴ� �Լ�
	Vertex* temp = NULL;
	if (vlist == NULL) {                                      // vlist�� �����Ҵ��� ���� �ʾ��� ��� ���� �߻�
		printf("[ Error : creatGraph first ]\n");
		return;
	}
	for (int i = 0; i < MAX_VERTEX; i++) {                    // 0~19���� �ݺ�
		if (exist_vertex[i] == 1) {                           // vertex�� ������ ���
			printf("[ Vertex %d ]", i + 1);                   // vertex�� �ش� ��ȣ( �� �ε��� )�� ����ϰ�
			printf(" [ Linked Vertex ] ");                    // �̿� ������ִ� linked list���� ����Ѵ�
			temp = vlist[i].head;                             // temp�� head�� �Ҵ�
			while (temp) {                                    // temp�� NULL �� �ɶ� ���� �ݺ�
				printf(" %d ", temp->num);                    // temp�� num�� ���
				temp = temp->link;                            // ���� ���� �̵�
			}
			printf("\n");
		}
	}
}

void CheckGraph(VertexHead *vlist) {                             // ������ �׷������� ( �и��� �κ��� ������ ) Ȯ���ϴ� �Լ�
	int vertex[MAX_VERTEX] = { 0, }, j = -1;
	for (int i = 0; i < MAX_VERTEX; i++) {
		if (visit_vertex[i] == 0 && exist_vertex[i] == 1) {      // Ž���� �ϸ� �ٲ�� visiting flag�� �ٽ� ���� 0���� �ٲٴ� �۾�
			vertex[++j] = i + 1;                                 // �̿� ���ÿ� vertex�� �����ϴµ� visiting�� 0�ϰ�� �湮�� �ȵ� ���������, ( ��, ������ ���� ���� ��� )  �� ���� ����
			//deleteVertex(i + 1, vlist);                      // ������ ������ vertex�� ����( �����Բ��� ������ ������ ��쿡�� �׷����� ���ζ�� �ϼ̼� �ϴ� �ּ�ó�� �س����ϴ�. �ּ��� ��ü�Ͻø� �׷��������� ���� ������ �̸� ��ü�մϴ�.
		}
		visit_vertex[i] = 0;                                     // visiting vertex�� �ٽ� 0���� �ʱ�ȭ
	}

	if (j != -1) {                                               // j�� ���� ������� ���� vertex�� ��������
		printf("\n===============[ error : graph disconnected ]================\n");
		printf("[ vertex num ]");
		for (int h = 0; h <= j; h++) {                               // 0~j���� �ݺ��ϸ鼭 ���
			printf(" %2d", vertex[h]);
		}
		puts("");
		//printf("=============[ being delete disconnected graph ]=============\n");
	}
}

void depthFS(int vertex_num, VertexHead* vlist) {  // ���� �켱 Ž��
	if (Error_ck(vertex_num, vertex_num, vlist)) {  // ������ �ִ� �� Ȯ���ϴ� �Լ� ������ ���� ��� 1�� return�Ǿ� ����, �ƴ� ��� 0�� ���ϵǾ� ��� ����
		return;
	}
	printf(" [ %d ] ", vertex_num);                // �ʱ� ���۰� ��� ( ������ vertex�� �迭�� �ε����� ��������� )
	Vertex* temp = NULL;
	push(vertex_num);                              // ���� vertex_num�� stack�� ���� �ִ´�
	visit_vertex[vertex_num - 1] = 1;              // ���� �ش� vertex�� ����

	while (top != -1) {
		temp = vlist[get()].head;                  // stack�� top�� ���� ����Ű�� �ִ� ��ġ�� num���� �ش��ϴ� vertex�� ����� vlist[num-1].head�� ���� �޴´�
		while (temp) {                             // temp�� ����� linked list Ž��
			if (!visit_vertex[temp->num - 1]) {    // linked list�� ������ִ� ��尡 �湮 ���� �ʾҴٸ�
				printf(" [ %d ] ", temp->num);     // ���� vertex num�� ����ϰ�
				push(temp->num);                   // vertex_num�� stack�� ����ִ´�
				visit_vertex[temp->num - 1] = 1;   // ���� �� vertex�� ���� �湮�ߴٰ� ǥ���Ѵ�
				break;
			}
			temp = temp->link;                     // �湮�� �� ��� ���� ���� �̵�
		}
		if (temp == NULL) pop();                   // temp�� NULL�� ���, stack���� ���� ������ ( �̸� top�� -1, �� stack �ȿ� ���� ������ ���� �ݺ� )
	}
	CheckGraph(vlist);                             // ������� ���� vertex�� �ִ��� Ȯ���� ���� �Լ�
}

void pop() {                     // stack�� ���� ���� �Լ�
	stack[top--] = NULL;         // top�� ��ġ�� NULL�� �ٲ۴��� 1��ŭ ���δ�
}

void push(int node) {           // stack�� ���� �ִ� �Լ�
	stack[++top] = node;         // top�� ���� 1��ŭ ������Ų �� ���ڸ��� node�� ����
}

int get() {                      // ���� top�� ����Ű�� ��ġ�� num�� ���� ����
	return stack[top] - 1;
}

void breadthFS(int vertex_num, VertexHead* vlist) {                    // �ʺ� �켱 Ž��
	int v_num;
	Vertex *temp = NULL;
	if (Error_ck(vertex_num, vertex_num, vlist)) {  // ������ �ִ� �� Ȯ���ϴ� �Լ� ������ ���� ��� 1�� return�Ǿ� ����, �ƴ� ��� 0�� ���ϵǾ� ��� ����
		return;
	}
	enQueue(vertex_num);                                               // ť�� vertex_num�� �ִ´�
	for (;;) {                                                         // ���� �ݺ�
		v_num = deQueue();                                             // ť�� �ִ� ���� �޴´�
		if (v_num == MAX_VERTEX + 1) break;                            // �̶� ���� MAX_VERTEX +1�̶�� ���� ( ť�� ���̻� ���� ���� ��� �̴� )
		printf(" [ %d ] ", v_num);
		temp = vlist[v_num - 1].head;                                  // �׸��� �̿� �ش��ϴ� linked list�� ���� ���� �޴´�
		while (temp) {                                                 // temp�� NULL�� �Ǳ� ������
			if (!visit_vertex[temp->num - 1]) enQueue(temp->num);         // �湮���� �ʾҴٸ� ť�� ���� ����
			temp = temp->link;                                         // temp�� ���� ���� �̵�
		}
	}                                                                  // ���� �켱 Ž���̹Ƿ� ���� vertex�� �������� ������ִ� vertex�� �湮���� ���� ��带 ��� ť�� ������, ���Լ����̶�� ť�� Ư���� ����� ���� �պκ��� ���� �޺κп� �ش� vertex���� ������ �� �ִ� ���( �湮���� �ʴ� )�� �ִ� ������ �۵��Ѵ�
	CheckGraph(vlist);                                                 // ������� ���� vertex�� �ִ��� Ȯ���� ���� �Լ�
}

int deQueue() {                         // ť���� ���� ���� �Լ�
	int temp;
	if (front == rear) {                // front�� rear�� ���� ��� ť�� �� ����ִ� ��� ������
		return MAX_VERTEX + 1;          // MAX_VERTEX+1�� ���� ����
	}
	front = ++front % MAX_VERTEX;       // front�� ���� 1��ŭ ���� ( ���� ť ������ MAX_VERTEX�� ������ ǥ���Ѵ� )
	temp = queue[front];                // front�� ����Ű�� ���� �ִ� data�� temp�� �ű��
	queue[front] = NULL;                // �ʱ�ȭ ��Ų��
	return temp;                        // temp�� �����Ѵ�
}

void enQueue(int aNode) {               // ť�� ���� �ִ� �Լ�
	rear = ++rear % MAX_VERTEX;         // rear�� ���� 1��ŭ ������Ų�� ( ���� ť ������ MAX_VERTEX�� ������ ǥ���Ѵ� )
	queue[rear] = aNode;                // rear�� ����Ű�� ���� data ����
	visit_vertex[aNode - 1] = 1;        // ������ data ��, �ش� vertex�� ���� visiting flag�� 1�� �ٲ۴� ( �湮�ߴٰ� �ٲ۴� )
}

int Error_ck(int vertex_num, int edge_num, VertexHead* vlist) {
	if (vlist == NULL) {																// vlist�� �����Ҵ��� ���� �ʾ��� ��� ���� �߻�
		printf("[ Error : creatGraph first ]\n");
		return 1;
	}

	if (!(0 < vertex_num && vertex_num <= 20) || !(0 < edge_num && edge_num <= 20)) {	// ���س��� vertex�� ������ ����� error
		printf("[ Error : Wrong input ]\n");
		return 1;
	}

	if (exist_vertex[vertex_num - 1] == 0) {											// �ش� vertex�� �������� ���� �� ����
		printf("[ Error : %d Vertex Doesn't Exist ]\n", vertex_num);
		return 1;
	}

	if (edge_num != 0 && exist_vertex[edge_num - 1] == 0) {												// �ش� vertex�� �������� ���� �� ����
		printf("[ Error : %d Vertex Doesn't Exist ]\n", edge_num);
		return 1;
	}
	return 0;
}