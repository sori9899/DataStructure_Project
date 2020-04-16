#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int **creat_matrix(int row, int col);																// 동적할당을 통해 2차원 배열 생성, 오류시 NULL 반환
int free_matrix(int **matrix, int row, int col);													// 동적할당된 공간을 헤제, 오류시 -1 반환
void print_matrix(int **matrix, int row, int col);													// 2차원배열을 출력하는 함수
int fill_data(int **matrix, int row, int col);													    // 0~19까지의 값을 랜덤으로 2차원 배열에 채워주는 함수, 오류시 -2를 반환
int transpose_matrix(int **matrix, int **matrix_t, int row, int col);							    // A의 전치행렬 T를 구하는 함수, 오류시 -3을 반환
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col);		    // 행렬 A와 행렬B의 합을 구하는 함수, 오류시 -4를 반환
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col);		    // 행렬 A와 행렬B의 차을 구하는 함수, 오류시 -5를 반환
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col);		    // 행렬 A와 행렬B의 곱을 구하는 함수, 오류시 -6을 반환
void Start_matrix(char *arr, int ***temp, int row, int col, int BOOL);							    // matrix, matrix_a, matrix_b에 동적할당후 data를 채우고 이를 출력하는 부분을 하나로 묶었다.
void Error_message(int num);																	    // 에러 메시지를 출력하는 함수

int main(void) {
	srand(time(NULL));    // 랜덤값을 설정하기 위해 씨드값을 초기화

	int row, column;
	int ** matrix=NULL, **matrix_t=NULL, **matrix_a = NULL, **matrix_b = NULL, **matrix_sum = NULL, **matrix_sub = NULL, **matrix_axt = NULL;
	printf("2019038068 김성욱\n\n");

	printf("행렬의 행과 열을 입력하세요 :");
	scanf("%d %d", &row, &column);																	 // 행, 열을 입력받는다

	Start_matrix("matrix", &matrix, row, column, 1);												 // matrix에 2차원배열을 동적할당 후, data를 체우고, print하는 함수 (BOOL이 1이므로)
	Start_matrix("matrix_a", &matrix_a, row, column, 1);											 // matrix_a에 2차원배열을 동적할당 후, data를 체우고, print하는 함수 (BOOL이 1이므로)
	Start_matrix("matrix_b", &matrix_b, row, column, 1);											 // matrix_b에 2차원배열을 동적할당 후, data를 체우고, print하는 함수 (BOOL이 1이므로)

	Start_matrix("A+B", &matrix_sum, row, column, 0);												 // matrix_a에 2차원배열을 동적할당 후, data를 체우고, print하는 함수
	Error_message(addition_matrix(matrix_a, matrix_b, matrix_sum, row, column));					 // addition_matrix를 matrix_a, matrix_b에 대해 시행후, 그에 대한 오류 코드를 받아 Error message 출력
	print_matrix(matrix_sum, row, column);															 // matrix_sum을 출력하는 함수

	Start_matrix("A-B", &matrix_sub, row, column, 0);												 // matri_subx에 2차원배열을 동적할당 해주는 함수 (BOOL이 0이므로)
	Error_message(subtraction_matrix(matrix_a, matrix_b, matrix_sub, row, column));					 // subtraction_matrix를 matrix_a, matrix_b에 대해 시행후, 그에 대한 오류 코드를 받아 Error message 출력
	print_matrix(matrix_sub, row, column);															 // matrix_sub을 출력하는 함수

	Start_matrix("A의 전치행렬 T", &matrix_t, row, column, 0);										 // matri_t에 2차원배열을 동적할당 해주는 함수 (BOOL이 0이므로)
	Error_message(transpose_matrix(matrix, matrix_t, row, column));									 // transpose_matrix를 matrix에 대해 시행후, 그에 대한 오류 코드를 받아 Error message 출력
	print_matrix(matrix_t, row, column);															 // matrix_t을 출력하는 함수

	Start_matrix("A*T", &matrix_axt, row, column, 0);												 // matri_axt에 2차원배열을 동적할당 해주는 함수 (BOOL이 0이므로)
	Error_message(multiply_matrix(matrix_a, matrix_t, matrix_axt, row, column));					 // multiply_matrix를 matrix_a, matrix_t에 대해 시행후, 그에 대한 오류 코드를 받아 Error message 출력
	print_matrix(matrix_axt, row, column);															 // matrix_axt을 출력하는 함수

	printf("\n\n");
	Error_message(free_matrix(matrix, row, column));												 // matrix의 동적할당을 해재한 후, 그에 대한 오류코드를 받아 Error message 출력
	Error_message(free_matrix(matrix_a, row, column));												 // matrix_a의 동적할당을 해재한 후, 그에 대한 오류코드를 받아 Error message 출력
	Error_message(free_matrix(matrix_b, row, column));												 // matrix_b의 동적할당을 해재한 후, 그에 대한 오류코드를 받아 Error message 출력
	Error_message(free_matrix(matrix_t, row, column));												 // matrix_t의 동적할당을 해재한 후, 그에 대한 오류코드를 받아 Error message 출력
	Error_message(free_matrix(matrix_axt, row, column));											 // matrix_axt의 동적할당을 해재한 후, 그에 대한 오류코드를 받아 Error message 출력
	Error_message(free_matrix(matrix_sub, row, column));											 // matrix_sub의 동적할당을 해재한 후, 그에 대한 오류코드를 받아 Error message 출력
	Error_message(free_matrix(matrix_sum, row, column));											 // matrix_sum의 동적할당을 해재한 후, 그에 대한 오류코드를 받아 Error message 출력
	return 0;
}

int **creat_matrix(int row, int col) {																 // 동적할당을 통해 2차원 배열 생성, 오류시 NULL 반환
	int **matrix=NULL;
	if (row <= 0 || col <= 0) {
		printf("Error : row와 col의 크기를 확인하세요\n");
		return NULL;																				 // row와 col중 하나라도 0보다 같거나 작을 경우 오류 메시지 출력후 NULL 반환
	}

	matrix = (int **)malloc(sizeof(int *)*row);														 // 행의 개수만큼 동적할당
	matrix[0] = (int *)malloc(sizeof(int)*row*col);													 // 행*열 만큼 동적할당
	for (int i = 1; i < row; i++) {
		matrix[i] = matrix[i - 1] + col;															 // matrix[0]에 동적할당한 부분에서 열의 개수만큼 주소값을 움직이며 배열 연결
	}

	if (matrix == NULL) {																			 // matrix에 동적할당이 되지 않았을 경우 NULL이 담겨있으므로 오류
		printf("Error : matrix에 동적할당이 되지 않았습니다\n");
		return NULL;
	}
	return matrix;																					 // 동적할당된 matrix 반환( int ** )형이므로 주솟값 반환
}

int free_matrix(int **matrix, int row, int col) {													 // 동적할당된 공간을 헤제, 오류시 -1 반환
	if (matrix == NULL) {																			 // 동적할당이 안되었다면 matrix에 NULL이 반환되므로, 이를 사용해 matrix가 NULL일 경우 오류발생
		printf( "Error : 동적할당 되지 않은 공간을 해제할 수 없습니다.\n");
		return -1;
	}

	free(matrix[0]);																				 // creat_matrix에서 matrix[0]에 row*col만큼 동적할당한 후, 각각의 인덱스엔 주솟값의 연결만 해주었지 때문에 동적할당의 해제는 matrix[0]만 하면 된다
	free(matrix);																					 // matrix에 row만큼 동적할당한 공간 해제

	return 0;
}

void print_matrix(int **matrix, int row, int col) {													 // 2차원배열을 출력하는 함수
	if (matrix == NULL) {																			 // 동적할당이 안되었다면 matrix에 NULL이 반환되므로, 이를 사용해 matrix가 NULL일 경우 오류발생
		printf("Error : 출력할 수 있는 data가 없습니다(동적할당된 공간이 없습니다).\n");
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%5d ", matrix[i][j]);
		}
		puts("");
	}
	puts("");
}

int fill_data(int **matrix, int row, int col) {														  // 0~19까지의 값을 랜덤으로 2차원 배열에 채워주는 함수, 오류시 -2를 반환
	if (matrix == NULL) {																			  // 동적할당이 안되었다면 matrix에 NULL이 반환되므로, 이를 사용해 matrix가 NULL일 경우 오류발생
		printf("Error : matrix에 동적할당된 공간이 없습니다.\n");
		return -2;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = rand() % 20;																  // 초기화된 seed값을 통해 나오는 숫자들을 20으로 나누어 0~19까지 랜덤한 값을 생성
		}
	}
	return 0;
}

int transpose_matrix(int **matrix, int **matrix_t, int row, int col) {                                // A의 전치행렬 T를 구하는 함수, 오류시 -3을 반환
	if (matrix == NULL) {                                                                             // 동적할당이 안되었다면 matrix에 NULL이 반환되므로, 이를 사용해 matrix가 NULL일 경우 오류발생
		printf("Error : matrix에 데이터가 없습니다(동적할당된 공간이 없습니다).\n");
		return -3;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_t[i][j] = matrix[j][i];
		}
	}

	return 0;
}

int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col) {             // 행렬 A와 행렬B의 합을 구하는 함수, 오류시 -4를 반환
	if (matrix_a == NULL || matrix_b==NULL) {                                                         // 동적할당이 안되었다면 matrix에 NULL이 반환되므로, 이를 사용해 matrix가 NULL일 경우 오류발생
		printf("Error : matrix_a(or matrix_b)에 데이터가 없습니다(동적할당된 공간이 없습니다).\n");
		return -4;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
		}
	}

	return 0;
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col) {          //  행렬 A와 행렬B의 차을 구하는 함수, 오류시 -5를 반환
	if (matrix_a == NULL || matrix_b == NULL) {                                                       // 동적할당이 안되었다면 matrix에 NULL이 반환되므로, 이를 사용해 matrix가 NULL일 경우 오류발생
		printf("Error : matrix_a(or matrix_b)에 데이터가 없습니다(동적할당된 공간이 없습니다).\n");
		return -5;
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
		}
	}
	return 0;
}

int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col) {             // 행렬 A와 행렬B의 곱을 구하는 함수, 오류시 -6을 반환
	int sum = 0, z = 0, x = 0, y = 0;
	if (matrix_a == NULL) {                                                                           // 동적할당이 안되었다면 matrix에 NULL이 반환되므로, 이를 사용해 matrix가 NULL일 경우 오류발생
		printf("Error : matrix에 데이터가 없습니다(동적할당된 공간이 없습니다)\n");
		return -6;
	}

	while (z < row*col) {
		sum = 0;
		for (int k = 0; k < row; k++) {
			sum+=matrix_a[x][k] * matrix_t[k][y];
		}
		*(matrix_axt[0]+z)= sum;
		y++;
		if (y == col) {
			x++;
			y = 0;
		}
		z++;
	}

	return 0;
}

void Start_matrix(char *arr, int ***temp, int row, int col, int BOOL) {                               // matrix, matrix_a, matrix_b에 동적할당후 data를 채우고 이를 출력하는 부분을 하나로 묶었다.
	printf("\n%s\n", arr);
	printf("------------------------------------------------------------\n");
	*temp = creat_matrix(row, col);                                                                   // 만들고자 하는 행렬에 대한 변수의 주소를 받았으므로, temp는 삼중포인터이며, *temp가 우리가 생성하고자 하는 행렬의 변수를 가리키므로 이와 같이 적용했다.
	if (*temp == NULL) {                                                                              // creat_matrix, 즉 동적할당에 실패했을때 NULL이 반환되므로 이를 사용해 오류메시지를 출력
		printf("Error : 동적할당에 실패했습니다.\n");
	}
	if (BOOL == 1) {
		Error_message(fill_data(*temp, row, col));                                                    // fill_data를 matrix에 대해 시행후, 그에 대한 오류 코드를 받아 Error message 출력
		print_matrix(*temp, row, col);                                                                // matrix를 출력하는 함수
	}
}

void Error_message(int num) {                                                                         // 에러 메시지를 출력하는 함수
	switch (num)
	{
	case -1:
		printf("Error : free_matrix에 실패했습니다.\n");
		break;
	case -2:
		printf("Error : fill_data에 실패했습니다.\n");
		break;
	case -3:
		printf("Error : transpose_matrix에 실패했습니다.\n");
		break;
	case -4:
		printf("Error : addition_matrix에 실패했습니다.\n");
		break;
	case -5:
		printf("Error : subtraction_matrix에 실패했습니다.\n");
		break;
	case -6:
		printf("Error : multiply_matrix에 실패했습니다.\n");
		break;
	}
}
