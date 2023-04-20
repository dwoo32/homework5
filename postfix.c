#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX_STACK_SIZE 10 //MAX_STACK_SIZE 10으로 정의
#define MAX_EXPRESSION_SIZE 20 //MAX_EXPRESSION_SIZE 20으로 정의

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum //구조체 정의
{//구조제 멤버정의
   lparen = 0,  /* ( 왼쪽 괄호 */
   rparen = 9,  /* ) 오른쪽 괄호*/
   times = 7,   /* * 곱셈 */
   divide = 7,  /* / 나눗셈 */
   plus = 5,    /* + 덧셈 */
   minus = 5,   /* - 뺄셈 */
   operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];//char형 MAX_EXPRESSION_SIZE 매개변수로 받는 infixExp 함수 선언
char postfixExp[MAX_EXPRESSION_SIZE];//char형 MAX_EXPRESSION_SIZE 매개변수로 받는 postfixExp 함수 선언
char postfixStack[MAX_STACK_SIZE];//char형 MAX_STACK_SIZE 매개변수로 받는 postfixStack 함수 선언
int evalStack[MAX_STACK_SIZE];//int형 MAX_STACK_SIZE 매개변수로 받는 evalStack 함수 선언

int postfixStackTop = -1;//int형 변수 postfixStackTop -1로 초기화
int evalStackTop = -1;//int형 변수 evalStackTop -1로 초기화

int evalResult = 0;//int형 변수 evalResult 0으로 초기화


void postfixpush(char x);//postfixpush 함수 선언
char postfixPop();//char형 postfixPop 함수 선언
void evalPush(int x);//evalPush 함수 선언
int evalPop();//int형 evalPop 함수 선언
void getInfix();//getInfix 함수 선언
precedence getToken(char symbol);//getToken 함수 선언
precedence getPriority(char x);//getPriority 함수 선언
void charCat(char* c);//charCat 함수 선언
void toPostfix();//toPostfix함수 선언
void debug();//debug 함수 선언
void reset();//reset 함수 선언
void evaluation();//evaluation 함수 선언


int main()
{
   
   int count = 0;   //추가, int형 변수 count 0으로 초기화
   char command;//char형 변수 comand 변수 선언

   printf("[----- [Kimdongwoo] [2020039058] -----]\n");


   do {//메뉴 출력
      printf("----------------------------------------------------------------\n");
      printf("               Infix to Postfix, then Evaluation               \n");
      printf("----------------------------------------------------------------\n");
      printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
      printf("----------------------------------------------------------------\n");

      printf("Command = ");//command 입력받고
      scanf(" %c", &command);//command에 저장

      switch (command) {//command 입력받은 것에 따른 switch 조건문
      case 'i': case 'I'://i 대소문자 입력 받을 때
         getInfix();//getInfix 함수 호출
         count++;//count값 1증가
         break;
      case 'p': case 'P':// p 대소문자 입력 받을 때
         if (count == 0)   //count가 0일 때
         {
            printf("Please enter the Infix first!\n");//infix 먼저 입력하라고 출력
            continue;
         }
         toPostfix();//toPostfix 함수 호출
         break;
      case 'e': case 'E': //e 대소문자 입력 받을 때
         if (count == 0)   //count가 0일 때
         {
            printf("Please enter the Infix first!\n");//infix 먼저 입력하라고 출력
            continue;
         }
         evaluation();//evaluation 함수 호출
         break;
      case 'd': case 'D'://d 대소문자 입력 받을 때
         debug();//debug 함수 호출
         break;
      case 'r': case 'R'://r 대소문자 입력 받을 때
         reset();//reset 함수 호출
         count = 0; //count 0으로 초기화
         break;
      case 'q': case 'Q'://q 대소문자 입력 받을 때
         break;
      default://조건에 없는 알파벳 입력했을 때
         printf("\n       >>>>>   Concentration!!   <<<<<     \n");
         break;
      }

   } while (command != 'q' && command != 'Q');//q 대소문자가 입력되기 전까지 반복

   return 1;
}

void postfixPush(char x)//postfixPush함수 정의
{
   postfixStack[++postfixStackTop] = x;// postfixStack[postfixStackTop+1] 위치에 x값 할당
}

char postfixPop()//char형 postfixPop 함수 정의
{
   char x;//char형 변수 x선언
   if (postfixStackTop == -1)//postfixStackTop이 -1일 때
      return '\0'; //null return
   else {
      x = postfixStack[postfixStackTop--];//x에 postfixStack[postfixStackTop-1]값 할당
   }
   return x;//x 리턴
}

void evalPush(int x)//evalPush 함수 정의
{
   evalStack[++evalStackTop] = x;//evalStack[evalStackTop+1] 위치에 x값 할당
}

int evalPop()//int형 evalPop 함수 정의
{
   if (evalStackTop == -1)//evalStackTop이 -1 일 때
      return -1;//-1 리턴
   else//-1이 아니라면
      return evalStack[evalStackTop--];//evalStack[evalStackTop-1] 리턴
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()//getInfix 함수 호출
{
   printf("Type the expression >>> ");
   scanf("%s", infixExp);//infixExp 값 입력받기
}

precedence getToken(char symbol)//getToken함수 호출
{
   switch (symbol) {//symbol 값에 따른 switch 조건문
   case '(': return lparen;// (: lparen 리턴
   case ')': return rparen;// ): rparen 리턴
   case '+': return plus;// +: plus 리턴
   case '-': return minus;// -: minus 리턴
   case '/': return divide;// /: divide 리턴
   case '*': return times;// *: times 리턴
   default: return operand;// 조건에 없는 문자일 경우 operand 반환
   }
}

precedence getPriority(char x)//입력받은 x의 우선순위를 반환하는 getPriority 반환
{
   return getToken(x);//getToken(x)값 리턴
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)//charCat 함수 선언
{
   if (postfixExp == '\0')//postfixExp이 null인 경우
      strncpy(postfixExp, c, 1);//postfixExp를 c에 복사
   else//null이 아닌 경우
      strncat(postfixExp, c, 1);//postfixExp를 c에 붙여넣기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()//toPostfix 함수 호출
{
   char* exp = infixExp; //char형 포인터 exp에 infixEXp 저장
   char x;//char형 변수 x 선언

   /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
   while (*exp != '\0')//exp가 null이 아닐동안
   {
      if (getPriority(*exp) == operand)//getPriority(exp가 가르키는 값을 매개변수로)함수의 반환값 == operand 일 때
      {
         x = *exp;//x에 포인터exp가 가르키는 값 할당
         charCat(&x);//charCat(x의 주소) 호출
      }

      else if (getPriority(*exp) == lparen)//getPriority(exp가 가르키는 값을 매개변수로)함수의 반환값 == lparen 일 때
      {
         postfixPush(*exp);//postfixPush(exp가 가르키는 값을 매개변수로)함수 호출
      }

      else if (getPriority(*exp) == rparen)//getPriority(exp가 가르키는 값을 매개변수로)함수의 반환 값 ==rparen
      {

         while ((x = postfixPop()) != '(')//x에 postfixpop의 반환값을 할당한 후, x가 (가 아닐 동안 반복
         {
            charCat(&x);//charCat(x의 주소를 매개변수로)함수 호출
         }
      }

      else
      {

         while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))//postfixStack[postfixStackTop]의 우선순위가 *exp의 우선순위보다 높을동안
         {
            x = postfixPop();//x에 postfixpop함수 리턴값 할당
            charCat(&x);//charCat(x의 주소를 매개변수로)함수 호출
         }
         postfixPush(*exp);//postfixPush(exp가 가르키는 값을 매개변수로)함수 호출
      }

      exp++;
   }


   while (postfixStackTop != -1)//postfixStackTop이 -1이 아닐동안 반복
   {
      x = postfixPop();//x에 postfixPop함수 리턴값 할당
      charCat(&x);//charCat(x의 주소를 매개변수로)함수 호출
   }
}

//infixExp,postfixExp,eavl result,postfixStack 출력하는 함수
void debug()//debug 함수 호출
{
   printf("\n---DEBUG\n");
   printf("infixExp =  %s\n", infixExp);//infixExp출력
   printf("postExp =  %s\n", postfixExp);//postfixExp 출력
   printf("eval result = %d\n", evalResult);//evalResult 출력

   printf("postfixStack : ");
   for (int i = 0; i < MAX_STACK_SIZE; i++)//i=0, i가 MAX_STACK_SIZE보다 작을 때 까지, i++
   {
      printf("%c  ", postfixStack[i]);//postfixStack[i] 호출
   }

   printf("\n");
}


void reset()//reset함수 호출
{
   infixExp[0] = '\0';//infixExp의 시작주소에 null 할당
   postfixExp[0] = '\0';//postfixExp의 시작주소에 null 할당

   for (int i = 0; i < MAX_STACK_SIZE; i++)//i=0, i가 MAX_STACK_SIZE보다 작을 때까지 반복
   {
      postfixStack[i] = '\0';//postfixStack[i]에 null 할당
   }

   postfixStackTop = -1;//postfixStackTop -1 할당
   evalStackTop = -1;//evalStackTop -1 할당
   evalResult = 0;//evalResult 0 할당
}


void evaluation()//evaluation함수 호출
{
   int opr1, opr2, i;//int형 변수opr1, opr2, i 선언

   int length = strlen(postfixExp);//int형 변수 length에 strlen(postfixExp)함수 리턴값 할당
   char symbol;//char형 변수 symbol 선언
   evalStackTop = -1;//evalStackTop -1 할당

   for (i = 0; i < length; i++)//i=0, i가 length보다 작을 때까지 반복
   {
      symbol = postfixExp[i];//symbol에 postfixExp배열에 저장된 값 저장
      if (getToken(symbol) == operand)//지정된 연산자 외의 값이 입력됐을 때
      {
         evalPush(symbol - '0');//연산자 0을 evalStack에 push
      }

      else
      {

         opr2 = evalPop();//opr2에 evalPop함수 리턴값(top에 있던 값) 할당 
         opr1 = evalPop();//opr1에 evalPop함수 리턴값(top 다음에 있던 값) 할당

         switch (symbol)
         {
         case '+': evalPush(opr1 + opr2); break;//+ 이면 evalPush(opr1+opr2)
         case '-': evalPush(opr1 - opr2); break;//- 이면 evalPush(opr1-opr2)
         case '*': evalPush(opr1 * opr2); break;//* 이면 evalPush(opr1*opr2)
         case '/': evalPush(opr1 / opr2); break;// / 이면 evalPush(opr1/opr2)
         default: break;
         }
      }
   }


   evalResult = evalPop();//evalResult에 evalStack[evalStackTop] 할당
}