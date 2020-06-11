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

 /* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
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
// initialize���� main �Լ��� �ִ� array�� ���� �����ϱ� ���� ���� �������� �ּҸ� ���� �����ͷ� ����
{
	int *temp = NULL;

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if (*a == NULL) {     // a�� ���ִ� ��� 
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);   
		// temp�� MAX_ARRAY_SIZE ��ŭ ���������� �Ҵ���
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/     
		// �̷��� �Ҵ���� ������ �ּҸ� (*a) �� main �Լ��� array�� ���� 
	}
	else  
	// ������ �����Ҵ�� ������ ������ ��� 
		temp = *a;   
		// �� ������ �ּڰ���  temp�� ����

	/* �������� �迭�� ������ ���� */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)   
		// temp�� �Ҵ�� ������ ũ�⸸ŭ �ݺ��ϸ� 
		temp[i] = rand() % MAX_ARRAY_SIZE;   
		// ���������� ���� ����( 0 ~12���� )

	return 0;
}

int freeArray(int *a)   
// �����Ҵ�� ������ ��ü�ϴ� �ڵ� ( array�� �����Ҵ�� �迭�� )
{
	if (a != NULL) 
		// a�� NULL �� �ƴ� ���, �� �Ҵ�� ������ ������ ��츸 free�� ���� 
		free(a);
	return 0;
}

void printArray(int *a)  
// �迭�� ����ϴ� �ڵ�
{
	if (a == NULL) {  
	// a�� NULL�̶�� ���� 
		printf("nothing to print.\n");
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)  
	// ��������� �����ֱ� ���� �迭�� ������ �����ش� 
		printf("a[%02d] ", i);
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)  
	// ������ �迭�� �ε����� ����� �� ��� 
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)  
// ��������, O(MAX_ARRAY_SIZE*MAX_ARRAY_SIZE)
{
	int min;  
	// �ε����� �������� ��� �񱳸� �Ҷ�, ������ �ε����� ����� ����  ���� ���� ���� ������ ����
	int minindex;  
	// ���Ҷ� ���� ã�� ���� ���� ���� 
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  // ������ �迭�� ��� 

	for (i = 0; i < MAX_ARRAY_SIZE; i++)  
	// 0 ~ MAX_ARRAY_SIZE ��ŭ �ݺ�
	{
		minindex = i;  
		// key�� ����
		min = a[i];    
		// key ������ ������ �ε����� ����Ǿ��ִ� �� ���� 
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++) 
		// i~ MAX_ARRAY_SIZE��ŭ �ݺ� 
		{
			if (min > a[j])  
			// ���� �������ִ� key���� ���� �� Ŭ���
			{
				min = a[j];    
				// �� ���� ������ key���� �� ���� ����
				minindex = j;
			}
		}
		a[minindex] = a[i];   
		// ���� ���� ���� key�� ���� ��ġ ����
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)  
// ���� ����, O(MAX_ARRAY_SIZE*MAX_ARRAY_SIZE)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  
	// �迭�� �ʱ� ���� ��� 
	 
	for (i = 1; i < MAX_ARRAY_SIZE; i++)  
	// 1~MAX_ARRAY_SIZE ���� �ݺ�
	{
		t = a[i];  
		j = i;
		while (a[j - 1] > t && j > 0) 
		// �տ� �����ϴ� �迭�� ���� ��ٴ� �����Ͽ� �ڿ��� ���� Ž�� 
		{                             
			// ���� j-1 ��, t�� ������ ���� ������ �ִ� �ε����� ��ġ�� �պκ� ���� Ž�� 
			a[j] = a[j - 1];          
			// a[j]�� ���� temp�� ����Ǿ� �����Ƿ� �� ��ġ�� ã���� ���� ��ĭ�� �ڷ� �δ� 
			j--;                      
			// j�� ���ҽ�Ų�� 
		}
		a[j] = t;                     
		// ���� �ݺ��� ������ ���� temp�� ���� �� �տ� ���� ���, Ȥ�� temp�� �� ��ġ�� ã�� ����̹Ƿ� �� ���� 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);    
	// ������ �� ��� 

	return 0;
}

int bubbleSort(int *a) 
// ���� ����, O(MAX_ARRAY_SIZE*MAX_ARRAY_SIZE)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  
	// �ʱ� �迭 �� ��� 

	for (i = 0; i < MAX_ARRAY_SIZE; i++) 
	// 0~MAX_ARRAY_SIZE ���� �ݺ�( �ݺ��ؾ� �ϴ� �� )
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)  
		// 0~MAX_ARRAY_SIZE ��ŭ �ݺ��ϸ� ����, 
		{                                     
			// [ ���� ������ �����Ҷ�, �� ���࿡���� ���� ū ���� �׻� ���� �ڿ� ���� ������ [ MAX_ARRAY_SIZE-i ] ��ŭ �ݺ��ص� �ȴ�, �̰�쿡�� O(MAX_ARRAY_SIZE*MAX_ARRAY_SIZE)�̴�
			if (a[j - 1] > a[j])   
			// ���� �ε����� ���� �� ũ�ٸ� 
			{                     
				// �հ� ���� ���� �ٲ۴� 
				t = a[j - 1];      
				a[j - 1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  
	// �ٲ� �迭�� ��� 

	return 0;
}

int shellSort(int *a)  
// �� ���� 
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  // ������ �迭���� ��� 

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)  
	// ���ذ��� ��ü �迭 ����/2�� ��Ƽ� ����, �̿� ���� ������ ������ �� h/=2���� ������ ���� �ٿ�����, �׸��� h=1�� �Ǿ����� ��� ���� ���ؼ� �񱳸� ���� ( ��, h=1�϶��� ���������� �����ϴ� �κ��̴� )
	{
		for (i = 0; i < h; i++)  
		// �迭 ������ h�� ���ݸ�ŭ �̵��ϸ� �� ������ ���� �ε�����ŭ �ݺ��Ѵ�( �ߺ��Ǿ� �񱳵Ǵ� �� ���� ex) h=3�϶��� ������ �ߺ��Ǵ� ��츦 �����ϰ� 0,1,2���� ����� �� ����( 4,5,6 ... �� �տ� 0,1,2���� h�� ���ݸ�ŭ ���� ���� �����ϴ� ��ġ�� ��ħ���� �ʿ� ����), h=1�϶��� h=0�϶� ���ϴ� ��쿡 h=2,3... ,n�϶� ���� h��ŭ ���ϴ� �Ͱ� ��ħ���� 0�϶��� ��
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h) 
			// �ι�° for������ ������ ���� �ε������� h�� ���ݸ�ŭ �̵��ϸ� ���� �� 
			// i=0 �̰� h=3�϶�, [ j=3�϶�, 0��, 3�� Ž�� //  j=6�϶�, 0��, 3��, 6�� Ž�� //  j=9�϶�, 0��, 3��, 9�� Ž�� // j=12�϶�, 0��, 3��, 9��, 12�� Ž�� // j=15�϶� ���ǿ� ��������� ����  ] ������ �����δ�. 
			// �� ���ݰ� �����ε����� ���ϸ� ���ݿ� �°� �����ϸ� �� ��ġ�� ã�������� ���� �ڿ��� ���� ���� ������ ���������� �����Ѵ�.
			// �׷��Ƿ� ������ 1�϶��� j=1 ���� j=12���� ���������� �����ϰ� �ȴ� 
			{
				v = a[j];  // j�� key������ ����
				k = j;     
				while (k > h - 1 && a[k - h] > v)  // k > h-1 : �� ������ a[k-h]> v�� ��� k-=h�� �����ϰ� �Ǵµ�, �̶��� k���� h-1���� ���� ���, ���� �����ϰ� �ִ� ��쿡 ���� ������ ���� ��������� Ž���� �����ϴ� ����
					                               // a[k - h] > v : v�� �� ��ġ�� ã�� ����
				{
					a[k] = a[k - h];
					k -= h;
				}
				a[k] = v;  // ���� ��ġ�� �ٲ��� �ʾҴٸ� k�� ���� �״�� �̹Ƿ� ���� X, �� ��ġ�� �ٲ���ٸ� k-=h�� �����߱� ������ ã�� ��ġ�� ��Ȯ�� ���� ������ �ִ�( �̰�� k-=h�� �����ϰ� ���� while������ AND���� ������ ����� ��������� )
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);
	// �ٲ� �迭�� ��� 
	return 0;
}

int quickSort(int *a, int n)
// �� ���� 
{
	int v, t;
	int i, j;

	if (n > 1)  // �Ѱ� ���� *a, n�� ���� �������� ���� �Ҽ� ���� ���( �̰�� pivot�� ��ġ�� i�� ���� ���� i>j�̱� ������ ������ ���� �Ұ���, n>1�� �Ǳ� ������ �ܰ迡�� ������ ���� ���·� �Ѿ���� ���� )
	{
		v = a[n - 1]; 
		// ���� ������ �ε����� data ��, ��, pivot �� ��
		i = -1;  
		j = n - 1;
		// ���� �������� �ε�����

		while (1) // ���� �ݺ� 
		{
			while (a[++i] < v); 
			// pivot���� ū ���� ���ö����� �ݺ� ( ���� ���� ��쵵 ���� )
			while (a[--j] > v); 
			// pivot ���� ���� ���� ���ö� ���� �ݺ� ( ���� ���� ��쵵 ���� )

			if (i >= j) break;  
			// ���� �ݺ��� ���� ����, Ž���� �� ��쿡 ���� Ž���� ����� ���
			// �ؿ��� ������ i>=j�� �ƴҰ�� ���� ���� ��ġ�� �ٲٴ� �۾�, �� pivot�� �������� ���� ���� ���ʿ� ū ���� �����ʿ� �ִ� �۾��� ��ȯ 
			t = a[i]; 
			a[i] = a[j];
			a[j] = t;
		}
		// i�� ���� pivot�� ���� ��ġ�� ����
		t = a[i];
		a[i] = a[n - 1];
		a[n - 1] = t;

		quickSort(a, i); 
		// �ٲ� pivot�� ��ġ�κ��� ���ʿ� ��ġ�ϴ� �迭�� ( ��, pivot���� ���� ���� )�� ����Լ��� ȣ���� �� ���� ���� 
		quickSort(a + i + 1, n - i - 1);
		// �ٲ� pivot�� ��ġ�κ��� �����ʿ� ��ġ�ϴ� �迭�� ( ��, pivot���� ū ���� )�� ����Լ��� ȣ���� �� ���� ���� 
	}


	return 0;
}

int hashCode(int key) {
	// �����Լ� 
	// �Ѱ��� key���� ���� ������ �� MAX_HASH_TABLE_SIZE ��ŭ ���� �������� �Ѱ��ش� ( key�� Ȩ �ּ�  )
	return key % MAX_HASH_TABLE_SIZE; // Ȩ �ּ� ���� 
}

int hashing(int *a, int **ht)  
// ���� ��
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if (*ht == NULL) {
		// �Ҵ��� ������ ���� ��� ���� �Ҵ�
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
		// �Ҵ��� ������ �ּڰ��� �Ѱ��ش� 
	}
	else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
		// ������ ������ ������ ��� �� ������ �ּڰ��� ����
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;
	// 0~MAX_HASH_TABLE_SIZE������ �� �ʱ�ȭ 

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	// �ʱ�ȭ 
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	// 0~MAX_HASH_TABLE_SIZE���� �ݺ�
	{
		key = a[i];
		hashcode = hashCode(key);
		// ���� �Լ� ȣ�� 
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		// ���� ���� ���� Ȩ �ּ��� ����( Ȩ ��Ŷ )�� ����ִٸ�
		{
			hashtable[hashcode] = key; 
			// data ����
		}
		else {
			// ������� ���� ��� ��, �浿(collision)�� �߻��ϰ� overflow�� �߻��� ���
			index = hashcode;
			// index�� ���� �Լ��� ���� ���� Ȩ �ּҰ��� ���� 

			while (hashtable[index] != -1)
			// ���� ����� 
			// ����ִ� ������ �����Ҷ� ���� �ݺ� 
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				// �ε����� ���� 1�� ������Ű�� MAX_HASH_TABLE_SIZE�� ������ �ε����� �迭�� ���̸� �Ѿ�� �ʵ��� ���ش�( ex: index�� ���� 13�� �ɰ�� �迭�� �ε����� 0~12������ ���������� MAX_HASH_TABLE_SIZE�� ������ 0��° �ε����� ���� ���ִ� �����̴� )
				/*
				printf("index = %d\n", index);
				*/
			}
			// ���� ������� ���� ã�� ������ key�� ����
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
// �ؽ��� �迭���� ������ key���� ã�� �Լ� 
{
	int index = hashCode(key);
	// �����Լ��� ȣ���� key���� ���� Ȩ �ּҸ� �޴´� 
	if (ht[index] == key)
	// ���� Ȩ �ּҰ� ����Ű�� ������ ����� data����(Ȩ ��Ŷ�� �ִ� ��) ã�� ���ϰ� ���ٸ�
	// Ȩ �ּҸ� ���� 
		return index;

	// �׷��� ���� ���( �����Լ��� ���� ���� Ȩ �ּҿ� key���� ���� ��� )
	while (ht[++index] != key)
	// key���� ���� ���� ����� ��ġ�� ���ö� ���� index�� �����ϸ� ã�´�
	// ���� �����
	{
		index = index % MAX_HASH_TABLE_SIZE;
		// �ε����� ���� 1�� ������Ű�� MAX_HASH_TABLE_SIZE�� ������ �ε����� �迭�� ���̸� �Ѿ�� �ʵ��� ���ش�.
	}
	// key���� ����� ��ġ�� ã�� �� �ε����� ����
	return index;
}
