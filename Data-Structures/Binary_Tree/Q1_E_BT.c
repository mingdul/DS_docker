//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode{ //이진트리의 노드 구조체 선언
	int item;
	struct _btnode *left;   //왼쪽의 노드를 가리키는 포인터
	struct _btnode *right;  //오른쪽의 노드를 가리키는 포인터
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode{ //스택 노드?
    BTNode *btnode;        //보유하고 있는 이진 트리의 노드 포인터
    struct _stackNode *next;   //스택 내에서 다음 노드를 가리킨다.
}StackNode;

typedef struct _stack{  // 스탁을 나타내는 구조체
    StackNode *top;     //스택의 탑을 가리키는 노드?
}Stack;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int identical(BTNode *tree1, BTNode *tree2);  //두 트리가 동일한지 판별하는 함수

BTNode* createBTNode(int item);             //이진 노드를 만드는 함수?

BTNode* createTree();                       //트리를 만드는 함수
void push( Stack *stk, BTNode *node);       //스택에 push
BTNode* pop(Stack *stk);                    //스택에서 pop

void printTree(BTNode *node);
void removeAll(BTNode **node);                  

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c, s;
    char e;         //문자? 이거는 어디에 쓰이는 거지?
    BTNode *root1, *root2;  //노드 루트 1, 2 선언

    root1 = NULL;          //루트 노드가 NULL을 가리킨다.
    root2 = NULL;
    c = 1;

    printf("1: Create a binary tree1.\n");      //1번 트리를 만든다.
    printf("2: Create a binary tree2.\n");      //2번 트리를 만든다.
    printf("3: Check whether two trees are structurally identical.\n");
    printf("0: Quit;\n");

    while(c != 0){
        printf("Please input your choice(1/2/3/0): ");
        if(scanf("%d", &c) > 0)

        {

            switch(c)
            {
            case 1:
                removeAll(&root1);             //루트 1을 지운다?
                printf("Creating tree1:\n");      
                root1 = createTree();          
                printf("The resulting tree1 is: ");
                printTree(root1);              //루트 1의 트리를 print 
                printf("\n");
                break;
            case 2:
                removeAll(&root2);             
                printf("Creating tree2:\n");
                root2 = createTree();
                printf("The resulting tree2 is: ");
                printTree(root2);
                printf("\n");
                break;
            case 3:
                s = identical(root1, root2);    //루트 1과 2가 같은지에 대한 결과를 s에 저장
                if(s){                          //s가 0이 아니면?
                printf("Both trees are structurally identical.\n"); //같다는 말을 print
                }
                else{
                printf("Both trees are different.\n");          // 다르다는 말을 print 
                }
                removeAll(&root1);                //1 트리를 지운다.
                removeAll(&root2);                //2 트리를 지운다.
                break;
            case 0:
                removeAll(&root1);
                removeAll(&root2);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
		}
        else
        {
            scanf("%c",&e);
        }

    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int identical(BTNode *tree1, BTNode *tree2)
{
    if(tree1 == NULL && tree2 == NULL) return 1; //두개의 노드가 모두 NULL일 경우 1을 반환
    if(tree1 == NULL || tree2 == NULL) return 0; //한개의 노드만 NULL인 경우 0을 반환

    return (tree1->item == tree2->item) &&  //현재의 노드가 같으며
    identical(tree1->left, tree2->left) &&  //왼쪽 자식 노드가 같고
    identical(tree1->right, tree2->right);  //오른쪽 자식 노드가 같으면 1을 반환하도록
}

/////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item){ //item을 받아서 BTNode를 가리키는 포인터를 반환한다.
    BTNode *newNode = malloc(sizeof(BTNode));   //새로운 노드의 사이즈를 동적으로 할당
    newNode->item = item;      //새로운 노드의 item을 item으로 초기화
    newNode->left = NULL;      //왼쪽 노드는 NULL
    newNode->right = NULL;     //오른쪽 노드도 NULL
    return newNode;            //newNode를 반환
}   

//////////////////////////////////////////////////////////////////////////////////


BTNode *createTree()         //새로운 Tree를 만드는 함수
{
    Stack stk;               //스택 선언, 이름이 stk
    BTNode *root, *temp;     //BTNode를 가리키는 포인터 root, temp을 선언
    char s;                  //문자 s?
    int item;                //item?

    stk.top = NULL;          //stk의 top은 NULL
    root = NULL;             //루트도 NULL

    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    //이진 트리에 추가할 정수를 입력하시오.
    printf("Enter an integer value for the root: ");
    //루트노드를 입력하시오?
    if(scanf("%d",&item) > 0)//입력한 item이 0보다 클때
    {
        root = createBTNode(item); //item을 매개변수로 createBTNode를 호출하고, root노드를 초기화
        push(&stk,root);           //스택의 주소와 노드를 매개변수로 루트 노드를 push
    }
    else
    {
        scanf("%c",&s);           //문자를 입력 받는다? 정수가 아닌 값을 입력했을때 문자열을 입력받는다.
    }
    //예를 들어 사용자가 10을 입력 -> 정수로 읽혀서 item = 10, 리턴 값은 1
    //사용자가 a 입력 -> 정수로 반환 불가 -> scanf는 실패하고 버퍼에 a가 남아있음
    //이걸 다음 줄 scanf("%c", &s)로 읽어서 버퍼를 비우는 것

    while((temp = pop(&stk)) != NULL)    //스택에서 pop한 결과를 temp에 대입한다. temp가 NULL이 아니면 반복
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);
        //temp의 item의 왼쪽 자식을 입력하라는 메시지

        if(scanf("%d",&item)> 0)    //입력 받은 값이 0보다 크면
        {
            temp->left = createBTNode(item);   //temp의 왼쪽 자식 노드는 item으로 초기화
        }
        else
        {
            scanf("%c",&s);             //문자를 입력 받는다?
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        //temp의 오른쪽 자식 노드를 입력하는 메시지?
        if(scanf("%d",&item)>0)//위와 같은 동작
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)     //temp의 오른쪽 노드를 가리키는 포인터가 NULL이 아니면
            push(&stk,temp->right);// 스택에 오른쪽 노드를 push한다?
        if(temp->left != NULL)      //temp의 왼쪽 노드를 가리키는 포인터가 NULL이 ㅏ니면
            push(&stk,temp->left);  //왼쪽 노드를 스택에 push한다.
        //스택에 오른쪽 값, 왼쪽 값순으로 넣고 다시 while문을 시작할 때 pop을 하기때문에 
        //왼쪽 값을 전부 초기화 하고 오른쪽 값을 초기화하게 된다.
    }
    return root;                //루트 노드를 가리키는 값을 반환한다.
}

void push(Stack *stk, BTNode *node){   //push 함수, 스택 구조체와, BTnode구조체를 가리키는 포인터를 매개변수로 받는다.
    StackNode *temp;                    //스택노드를 가리키는 포인터 temp선언
    //스택 노드를 하나 생성하는 것과 같은 느낌

    temp = malloc(sizeof(StackNode));   //temp에 StackNode만큼의 사이즈를 동적 할당한다.
    if(temp == NULL)                    //temp가 비었으면 return
        return;
    temp->btnode = node;               //temp의 btnode는 node가 된다.
    if(stk->top == NULL){              //매개변수로 받은 stk의 top이 NULL이라면
        stk->top = temp;               //stk의 top은 temp가 된다.   
        temp->next = NULL;             //temp의 다음 노드는 NULL이 된다.
    }
    else{                             //stk의 top이 비어있지 않다면
        temp->next = stk->top;        //tem8p의 next는 stk의 top이 된다.
        stk->top = temp;              //후에 stk의 top은 temp가 된다.
    }
}

BTNode* pop(Stack *stk){             //stk을 매개변수로 받아 BTNode를 반환하는 함수
   StackNode *temp, *top;           //StackNode를 가리키는 포인터 temp, top선언
   BTNode *ptr;                     //BTNode를 가리키는 포인터 ptr선언
   ptr = NULL;                      //ptr은 NULL

   top = stk->top;                  //스택의 top을 stk의 top으로 초기화
   if(top != NULL){                 //top이 NULL이 아니라면
        temp = top->next;           //temp는 top->next
        ptr = top->btnode;          //ptr은 top의 btnode

        stk->top = temp;            //stk의 top은 temp
        free(top);                  //top의 메모리 할당해제
        top = NULL;                 //top은 NULL 
        //해제된 메모리에 대한 접근을 방지하기 위한 안전장치
        //top 자체는 지역 변수이기 때문에 실제로 스택 구조에 직접적인 영향은 없지만
        //이런 식의 방어적 프로그래밍은 코드 안정성을 높이는 데 유용하다.
   }
   return ptr;                      //ptr을 반환한다. 여기서 ptr은 top->btnode 이거나 NULL이 될 수 있다.
}

void printTree(BTNode *node){       //노드를 받아서 print하는 함수  !! 중위순회를 하는 것으로 보인다.

    if(node == NULL) return;        //노드가 NULL이라면 return

    printTree(node->left);          //재귀적으로 노드의 왼쪽 자식 노드를 print한다.
    printf("%d ",node->item);       //node의 item을 print
    printTree(node->right);         //재귀적으로 노드의 오른쪽 자식 노드를 print한다.
}

void removeAll(BTNode **node){      //노드를 받아서 remove하는 함수, 노드를 가리키는 포인터를 가리키는 포인터를 매개변수로 받는다?
    //이렇게 포인터의 포인터를 받는 이유는 포인터 값을 함수 안에서 수정하기 위해서?
    if(*node != NULL){              //노드가 NULL이 아닌 경우
        removeAll(&((*node)->left));  //재귀적으로 왼쪽 노드를 가리키는 포인터의 주소를 매개변수로 함수를 호출한다.
        removeAll(&((*node)->right)); 
        free(*node);        //트리의 끝까지 들어왔기 때문에 메모리 할당을 해제한다.
        *node = NULL;       //이 포인터 값을 NULL으로 만드는 이유는?? 포인터가 아닌 노드 자체인 것?
    }
}
