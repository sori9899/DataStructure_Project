/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

 /* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do {
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)  
// initialize에서 main 함수에 있는 array를 직접 조작하기 위해 단일 포인터의 주소를 이중 포인터로 받음
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if (*a == NULL) {     // a가 비여있는 경우 
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);   
		// temp에 MAX_ARRAY_SIZE 만큼 정수형으로 할당후
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/     
		// 이렇게 할당받은 공간의 주소를 (*a) 즉 main 함수의 array에 복사 
	}
	else  
	// 기존에 동적할당된 공간이 존제할 경우 
		temp = *a;   
		// 그 공간의 주솟값을  temp에 복사

	/* 랜덤값을 배열의 값으로 저장 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)   
		// temp에 할당된 공간의 크기만큼 반복하며 
		temp[i] = rand() % MAX_ARRAY_SIZE;   
		// 램덤적으로 값을 저장( 0 ~12까지 )

	return 0;
}

int freeArray(int *a)   
// 동적할당된 공간을 해체하는 코드 ( array에 동적할당된 배열음 )
{
	if (a != NULL) 
		// a가 NULL 이 아닐 경우, 즉 할당된 공간이 존제할 경우만 free를 실행 
		free(a);
	return 0;
}

void printArray(int *a)  
// 배열을 출력하는 코드
{
	if (a == NULL) {  
	// a가 NULL이라면 종료 
		printf("nothing to print.\n");
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)  
	// 명시적으로 보여주기 위해 배열의 구조를 보여준다 
		printf("a[%02d] ", i);
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)  
	// 각각의 배열의 인덱스에 저장된 값 출력 
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)  
// 선택정렬, O(MAX_ARRAY_SIZE*MAX_ARRAY_SIZE)
{
	int min;  
	// 인덱스의 기준점을 잡고 비교를 할때, 각각의 인덱스에 저장된 값중  가장 작은 값을 저장할 공간
	int minindex;  
	// 비교할때 마다 찾은 가장 작은 값을 
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  // 기존의 배열값 출력 

	for (i = 0; i < MAX_ARRAY_SIZE; i++)  
	// 0 ~ MAX_ARRAY_SIZE 만큼 반복
	{
		minindex = i;  
		// key값 설정
		min = a[i];    
		// key 값으로 설정된 인덱스에 저장되어있는 값 저장 
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++) 
		// i~ MAX_ARRAY_SIZE만큼 반복 
		{
			if (min > a[j])  
			// 만약 설정되있는 key값의 값이 더 클경우
			{
				min = a[j];    
				// 더 작은 값으로 key값과 그 값을 변경
				minindex = j;
			}
		}
		a[minindex] = a[i];   
		// 가장 작은 값과 key값 간의 위치 변경
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)  
// 삽입 정렬, O(MAX_ARRAY_SIZE*MAX_ARRAY_SIZE)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  
	// 배열의 초기 상태 출력 
	 
	for (i = 1; i < MAX_ARRAY_SIZE; i++)  
	// 1~MAX_ARRAY_SIZE 까지 반복
	{
		t = a[i];  
		j = i;
		while (a[j - 1] > t && j > 0) 
		// 앞에 존제하는 배열이 정렬 됬다는 가정하에 뒤에서 부터 탐색 
		{                             
			// 만약 j-1 즉, t와 동일한 값을 가지고 있는 인덱스의 위치의 앞부분 부터 탐색 
			a[j] = a[j - 1];          
			// a[j]의 값은 temp에 저장되어 있으므로 들어갈 위치를 찾을때 까지 한칸씩 뒤로 민다 
			j--;                      
			// j를 감소시킨다 
		}
		a[j] = t;                     
		// 위의 반복이 끝나는 경우는 temp의 값이 맨 앞에 들어가는 경우, 혹은 temp가 들어갈 위치를 찾은 경우이므로 값 삽입 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);    
	// 정렬한 값 출력 

	return 0;
}

int bubbleSort(int *a) 
// 버블 정렬, O(MAX_ARRAY_SIZE*MAX_ARRAY_SIZE)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  
	// 초기 배열 값 출력 

	for (i = 0; i < MAX_ARRAY_SIZE; i++) 
	// 0~MAX_ARRAY_SIZE 까지 반복( 반복해야 하는 수 )
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)  
		// 0~MAX_ARRAY_SIZE 만큼 반복하며 정렬, 
		{                                     
			// [ 버블 정렬을 시행할때, 매 시행에서의 가장 큰 값은 항상 가장 뒤에 가게 됨으로 [ MAX_ARRAY_SIZE-i ] 만큼 반복해도 된다, 이경우에도 O(MAX_ARRAY_SIZE*MAX_ARRAY_SIZE)이다
			if (a[j - 1] > a[j])   
			// 앞의 인덱스의 값이 더 크다면 
			{                     
				// 앞과 뒤의 값을 바꾼다 
				t = a[j - 1];      
				a[j - 1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  
	// 바꾼 배열을 출력 

	return 0;
}

int shellSort(int *a)  
// 쉘 정렬 
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  // 기존의 배열값을 출력 

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)  
	// 기준값을 전체 배열 길이/2로 잡아서 시작, 이에 대해 정렬이 끝났을 시 h/=2로해 간격을 점차 줄여나감, 그리고 h=1이 되었을때 모든 값에 대해서 비교를 시작 ( 즉, h=1일때가 삽입정렬을 적용하는 부분이다 )
	{
		for (i = 0; i < h; i++)  
		// 배열 내에서 h의 간격만큼 이동하며 비교 가능한 시작 인덱스만큼 반복한다( 중복되어 비교되는 것 제외 ex) h=3일때는 정렬이 중복되는 경우를 제외하고 0,1,2에서 출발할 수 있음( 4,5,6 ... 은 앞에 0,1,2에서 h의 간격만큼 비교할 경우와 정렬하는 위치가 곂침으로 필요 없음), h=1일때도 h=0일때 비교하는 경우에 h=2,3... ,n일때 간격 h만큼 비교하는 것과 곂침으로 0일때만 비교
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h) 
			// 두번째 for문에서 정해진 시작 인덱스에서 h의 간격만큼 이동하며 값을 비교 
			// i=0 이고 h=3일때, [ j=3일때, 0번, 3번 탐색 //  j=6일때, 0번, 3번, 6번 탐색 //  j=9일때, 0번, 3번, 9번 탐색 // j=12일때, 0번, 3번, 9번, 12번 탐색 // j=15일때 조건에 위배됨으로 종료  ] 식으로 움직인다. 
			// 즉 간격과 시작인덱스를 정하면 간격에 맞게 증가하며 들어갈 위치를 찾을때까지 값을 뒤에서 부터 비교해 나가며 삽입정렬을 실행한다.
			// 그러므로 간격이 1일때는 j=1 부터 j=12까지 삽입정렬을 실행하게 된다 
			{
				v = a[j];  // j를 key값으로 설정
				k = j;     
				while (k > h - 1 && a[k - h] > v)  // k > h-1 : 비교 했을때 a[k-h]> v인 경우 k-=h를 시행하게 되는데, 이때의 k값이 h-1보다 작을 경우, 지금 시행하고 있는 경우에 대한 정렬이 끝난 경우임으로 탐색을 종료하는 조건
					                               // a[k - h] > v : v가 들어갈 위치를 찾는 조건
				{
					a[k] = a[k - h];
					k -= h;
				}
				a[k] = v;  // 만약 위치가 바뀌지 않았다면 k의 값이 그대로 이므로 문제 X, 들어갈 위치가 바뀌었다면 k-=h를 수행했기 때문에 찾은 위치에 정확히 값을 넣을수 있다( 이경우 k-=h를 실행하고 다음 while문에서 AND뒤의 조건이 위배되 종료됨으로 )
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);
	// 바꾼 배열을 출력 
	return 0;
}

int quickSort(int *a, int n)
// 퀵 정렬 
{
	int v, t;
	int i, j;

	if (n > 1)  // 넘겨 받은 *a, n에 대해 퀵정렬을 더는 할수 없는 경우( 이경우 pivot의 위치와 i의 값이 같고 i>j이기 때문에 퀵정렬 시행 불가능, n>1이 되기 직전의 단계에서 정렬이 끝난 상태로 넘어오기 때문 )
	{
		v = a[n - 1]; 
		// 가장 오른쪽 인덱스의 data 값, 즉, pivot 이 됨
		i = -1;  
		j = n - 1;
		// 가장 오른쪽의 인덱스값

		while (1) // 무한 반복 
		{
			while (a[++i] < v); 
			// pivot보다 큰 값이 나올때까지 반복 ( 값이 같을 경우도 종료 )
			while (a[--j] > v); 
			// pivot 보다 작은 값이 나올때 까지 반복 ( 값이 같을 경우도 종료 )

			if (i >= j) break;  
			// 무한 반복문 종료 조건, 탐색이 이 경우에 대한 탐색이 종료된 경우
			// 밑에는 위에서 i>=j가 아닐경우 서로 값의 위치를 바꾸는 작업, 즉 pivot을 기준으로 작은 값을 왼쪽에 큰 값을 오른쪽에 넣는 작업의 일환 
			t = a[i]; 
			a[i] = a[j];
			a[j] = t;
		}
		// i의 값과 pivot의 값의 위치를 변경
		t = a[i];
		a[i] = a[n - 1];
		a[n - 1] = t;

		quickSort(a, i); 
		// 바뀐 pivot의 위치로부터 왼쪽에 위치하는 배열들 ( 즉, pivot보다 작은 값들 )을 재귀함수를 호출해 퀵 정렬 시행 
		quickSort(a + i + 1, n - i - 1);
		// 바뀐 pivot의 위치로부터 오른쪽에 위치하는 배열들 ( 즉, pivot보다 큰 값들 )을 재귀함수를 호출해 퀵 정렬 시행 
	}


	return 0;
}

int hashCode(int key) {
	// 제산함수 
	// 넘겨준 key값에 대해 정해진 수 MAX_HASH_TABLE_SIZE 만큼 나눈 나머지를 넘겨준다 ( key의 홈 주소  )
	return key % MAX_HASH_TABLE_SIZE; // 홈 주소 리턴 
}

int hashing(int *a, int **ht)  
// 정적 해
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) {
		// 할당한 공간이 없을 경우 공간 할당
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
		// 할당한 공간의 주솟값을 넘겨준다 
	}
	else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
		// 기존에 공간이 존제할 경우 그 공간의 주솟값을 재사용
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;
	// 0~MAX_HASH_TABLE_SIZE까지의 값 초기화 

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	// 초기화 
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	// 0~MAX_HASH_TABLE_SIZE까지 반복
	{
		key = a[i];
		hashcode = hashCode(key);
		// 제산 함수 호출 
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		// 만약 리턴 받은 홈 주소의 공간( 홈 버킷 )이 비어있다면
		{
			hashtable[hashcode] = key; 
			// data 삽입
		}
		else {
			// 비어있지 않을 경우 즉, 충동(collision)이 발생하고 overflow가 발생할 경우
			index = hashcode;
			// index에 제산 함수로 부터 받은 홈 주소값을 저장 

			while (hashtable[index] != -1)
			// 선형 조사법 
			// 비어있는 공간이 존제할때 까지 반복 
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				// 인덱스의 값을 1씩 증가시키며 MAX_HASH_TABLE_SIZE로 나누며 인덱스가 배열의 길이를 넘어가지 않도록 해준다( ex: index의 값이 13이 될경우 배열의 인덱스는 0~12까지만 존제함으로 MAX_HASH_TABLE_SIZE로 나누어 0번째 인덱스가 들어가게 해주는 역할이다 )
				/*
				printf("index = %d\n", index);
				*/
			}
			// 선형 조사법을 통해 찾은 공간에 key값 저장
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
// 해싱한 배열에서 지정한 key값을 찾는 함수 
{
	int index = hashCode(key);
	// 제산함수를 호출해 key값에 대한 홈 주소를 받는다 
	if (ht[index] == key)
	// 만약 홈 주소가 가리키는 공간에 저장된 data값이(홈 버킷에 있는 값) 찾는 값하고 같다면
	// 홈 주소를 리턴 
		return index;

	// 그렇지 않은 경우( 제산함수를 통해 받은 홈 주소에 key값이 없는 경우 )
	while (ht[++index] != key)
	// key값과 같은 값이 저장된 위치가 나올때 까지 index를 증가하며 찾는다
	// 선형 조사법
	{
		index = index % MAX_HASH_TABLE_SIZE;
		// 인덱스의 값을 1씩 증가시키며 MAX_HASH_TABLE_SIZE로 나누며 인덱스가 배열의 길이를 넘어가지 않도록 해준다.
	}
	// key값이 저장된 위치를 찾아 그 인덱스를 리턴
	return index;
}
