/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */                 //계산할 문자열 저장
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;         // postfixStackTop을 1증가시킨 후 data 삽입
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];     // postfixStackTop에 위치한 data를 꺼낸뒤 1만큼 감소
	}
	return x;
}


void evalPush(int x)
{
	evalStack[++evalStackTop] = x;               // evalStackTop을 1증가시킨 후 data 삽입
}

int evalPop()
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];        // evalStackTop에 위치한 data를 꺼낸뒤 1만큼 감소
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

precedence getToken(char symbol)                 // 각각의 문자에 해당하는 값들을 반환해 준다 ( 위에서 tepydef로 지정한 정수를 반환 ) 
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}

}

precedence getPriority(char x)                   // 문자 x의 해당하는 값을 getToken으로부터 받아서 반환하는 함수
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x, ch; /* 문자하나를 임시로 저장하기 위한 변수 */
	int temp; /* postfixExp의 index 값을 조작하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')
	{
		x = *exp;
		temp = getPriority(x);
		if (temp == 1) {
			charCat(&x);           // x가 숫자인 경우 postfixExp에 대입
		}
		else if (temp == 9) {               // ')'인 경우
			while (1)                       // '(' 전까지 postfixPop에 있는 연산자를 postfixExp에 대입
			{
				x = postfixPop();
				if (x == '(') {             // '('가 나올경우 바로 종료 
					break;
				}
				charCat(&x);
			}
		}
		else if (temp==0) {                 // x가 '('인 경우 바로 대입
			postfixPush(x);
		}else{
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(x) && postfixStackTop != -1) {    // postfixStack에서 x보다 우선순위가 높은 연산자를 pop
				ch = postfixPop();
				charCat(&ch);
			}
			if (temp == 5 && getPriority(postfixStack[postfixStackTop]) == 4 || temp == 7 && getPriority(postfixStack[postfixStackTop]) == 6) {  // -,+ 혹은 /,*의 순서일때 실제 연산의 우선순위는 같지만 위에선 다르게 해놓았으므로 이경우를 처리
				ch = postfixPop();
				charCat(&ch);
			}
			postfixPush(x);
		}
		exp++;
	}
	
	for (int k = postfixStackTop; k>=0; k--) {   // infixExp에 있는 모든 문자를 다 거친후, postfixStack에 ㅏ남은 값들을 뒤에서부터 전부 pop해주는 코드
		ch = postfixPop();
		charCat(&ch);
	}
}


void debug()                                        // 디버그 즉, postfixStack, infixExp, postfixExp, eval result에 들어가 있는 data값을 확인해 주는 함수 
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)        
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()                                       // postfixStack, infixExp, postfixExp, eval result, evalStackTop, evalStackTop을 초기화 해주는 함수 
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()                                // postfixExp에 있는 내용을 활용해 계산한 결과를 eval result에 담는 함수
{
	char *x = postfixExp;                        // postfixExp의 주솟값을 전달
	int num, cal;
	while( *x != '\0') {
		if ( getPriority(*x)==1) {               // 만약 x가 숫자라면
			evalPush((int)*x - 48);   // evalStackTop 1증가
		}
		else {                                   // 숫자가 아닐경우
			num = evalPop();
			cal = getPriority(*x);
			if (num == 0 && cal == 6) {                       // 0으로 나눌 경우
				printf("Error : Can't be divided by zero\n"); // 오류 메시지 출력후 종료 
				return;
			}
			evalPush(Calcul(evalPop(), num, cal));     // Calcul로 n-2, n-1 번째 인덱스의 값을 전달 및 연산자의 ASCII코드 값 전달
		}
		x++;                                     // postfixExp내 다음 문자로 이동
	} 
	evalResult = evalPop();
	/* postfixExp, evalStack을 이용한 계산 */
}

int Calcul(int a, int b, int cal) {              // a,b사이의 연산을 수행후 그 결과를 return 해주는 함수 
	switch (cal)
	{
	case 7:
		return a * b;
	case 5:
		return a + b;
	case 4:
		return a - b;
	case 6:
		return a / b;	
	}
}

int main()
{
	char command;
	printf("2019038068 김성욱\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 0;


}




