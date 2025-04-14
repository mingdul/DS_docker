//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>	 
#include <stdlib.h>	//malloc()함수가 정의되어 있는 헤더파일

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{	//구조체 이름
	int item;				 //정수형 아이템
	struct _listnode *next;	//리스트 노드라는 구조체를 가리키는 포인터 next
} ListNode;			// You should not change the definition of ListNode  //구조체 별칭, 이와 같이 선언하면 구조체 변수를 선언 할때 struct 키워드를 생략해서 사용할 수 있다. 

typedef struct _linkedlist{
	int size;				//정수형 사이즈
	ListNode *head;			//리스트 노드라는 구조체를 가리키는 포인터 head
} LinkedList;			// You should not change the definition of LinkedList //구조체 별칭


///////////////////////// function prototypes ////////////////////////////////////
//함수 전방선언?
//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);	//링크드리스트 포인터를 매개변수로 준다?
												//정수형 아이템 값을 매개변수로 받는
												//반환값이 정수형인 insertSortedLL 함수
void printList(LinkedList *ll);	//반환값이 없는 함수 void	//링크드 리스트 포인터를 받아서?(여기서 포인터를 받는 이유는 함수에서 값을 변환시키기 위해서)
void removeAllItems(LinkedList *ll); // 모든 아이템을 삭제하는 함수?
ListNode *findNode(LinkedList *ll, int index);	//구조체인 리스트 노드를 가리키는 포인터를 반환하는 함수 
int insertNode(LinkedList *ll, int index, int value); //인덱스 위치에 노드를 삽입하는 함수
int removeNode(LinkedList *ll, int index);  //인덱스 값의 노드를 삭제하는 함수


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;			//링크드 리스트 구조체 선언
	int c, i, j;			//정수형 변수 선언
	c = 1;					

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;			//구조체의 헤드를 NULL, 사이즈를 0으로 초기화한다.
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");	//정렬된 리스트에 정수를 삽입
	printf("2: Print the index of the most recent input value:\n");	//최근의 입력 값의 인덱스를 출력한다.
	printf("3: Print sorted linked list:\n");						//정렬된 리스트를 출력한다.
	printf("0: Quit:");												//종료

	while (c != 0)		//c가 0이 아닐때 반복을 한다.
	{
		printf("\nPlease input your choice(1/2/3/0): ");			//1,2,3,0 중에 명령을 선택
		scanf("%d", &c);											//입력한 값을 c의 주소에 넣는다?

		switch (c)													//c의 값에 따라 동작하는 케이스들
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");	//추가하려는 정수 입력력
			scanf("%d", &i);						//입력 값을 i의 주소에 넣는다?
			j = insertSortedLL(&ll, i);				//insertSortedLL 함수를 실행한다. 링크드리스트 ll의 주소와 추가 하려는 정수 i를 입력
													//함수의 반환 값인 해당 정수가 들어간 인덱스 위치를 j에 대입한다.
			printf("The resulting linked list is: ");
			printList(&ll);							//링크드 리스트에 삽입 후 ll에 링크드 리스트의 모든 값을 출력한다.
			break;							
		case 2:
			printf("The value %d was added at index %d\n", i, j); //입력을 한 정수 i가 j의 인덱스에 추가됨을 출력한다.
			break;
		case 3:
			printf("The resulting sorted linked list is: ");	
			printList(&ll);				//정렬된 링크드 리스트의 목록을 출력
			//removeAllItems(&ll);		//모든 아이템을 삭제 한다? 
			break;
		case 0:
			removeAllItems(&ll);		//ll의 주소값으로 removeAllItems 함수를 호출한다.
			break;
		default:							//if문의 else와 같은 역할?
			printf("Choice unknown;\n");	//아무 것도 선택하지 않았을 때
			break;
		}


	}
	return 0;		//메인 함수의 종료
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)			//1번 문제의 부분
{
	ListNode *temp, *cur;
	int index = 0;

	if(ll == NULL)			//링크드 리스트가 없을 때
		return -1;

	if(ll->head == NULL || ll->head->item > item){         //head에 노드가 없거나 넣으려는 값이 최소 값일 때
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = item;
		ll->head->next = cur;
		ll->size++;
		return index;
	}		
	temp = ll->head;

	while (temp->next != NULL && temp->next->item < item){				
		temp = temp->next;
		index++;
	}

	if(temp->next != NULL && temp->next->item == item)
		return -1;

	cur = temp->next;
	temp->next = malloc(sizeof(ListNode));
	temp->next->item = item;
	temp->next->next = cur;
	ll->size++;

	return index+1;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){					//현재 정렬된 상태의 링크드 리스트를 출력

	ListNode *cur;								//ListNode를 가리키는 포인터 cur선언
	if (ll == NULL)								//ll가 NULL이면 함수를 끝낸다.(여기서 NULL인 경우는 아예 구조체가 선언되지 않은 경우?)
		return;
	cur = ll->head;								//아니면 cur에 ll의 head의 값이 대입된다.

	if (cur == NULL)							//cur의 값이 NULL이라면(ll 구조체가 선언되고 리스트에 노드가 생성되지 않았을때)
		printf("Empty");						//Empty를 출력
	while (cur != NULL)							//cur 값이 NULL이 아니라면 (현재 cur에 들어가있는게 ListNode를 가리키는 포인터?)
	{
		printf("%d ", cur->item);				//cur 값을 ListNode.item의 값을 할당하고 해당 값을 출력한다.
		cur = cur->next;						//cur 값을 현재의 구조체에 ListNode.next의 값을 할당한다?
	}											//이 상태에서 LostNode.next는 다시 LostNode 구조체이기 때문에 item과 next를 가지고 있다?
	printf("\n");								//줄바꿈 문자 출력
}


void removeAllItems(LinkedList *ll)				//모든 아이템을 삭제하는 함수?
{
	ListNode *cur = ll->head;					//리스트 노드의 주소를 가리키는 포인터 cur에 링크드리스트의 head값을 대입한다?
	ListNode *tmp;								//새로운 리스트 노드를 가리키는 포인터 tmp를 선언

	while (cur != NULL){						//현재 cur 값이 NULL이 아니라면
		tmp = cur->next;						//tmp에 cur의 next를 대입한다.
		free(cur);								//힙에 할당했던 cur의 메모리를 반환한다.
		cur = tmp;								//tmp의 값을 cur에 대입
	}											//해당 과정을 반복 -> 링크드 리스트의 head부터 차례로 메모리를 반환하면서 뒤로 이동한다.
	ll->head = NULL;							//모는 노드를 삭제하고 head를 NULL으로 만든다.
	ll->size = 0;								//size는 0으로 ((*li).size와 같은 표현)
}


ListNode *findNode(LinkedList *ll, int index){	//ListNode의 가리키는 포인터를 반환하는 함수

	ListNode *temp;								//ListNode 구조체를 가리키는 temp 변수 선언

	if (ll == NULL || index < 0 || index >= ll->size) //(ll이 NULL이거나 인덱스값이 0보다 작거나 인덱스가 ll의 사이즈보다 클때)
		return NULL;							//NULL을 반환	

	temp = ll->head;						//temp에 (*ll).head의 값을 대입

	if (temp == NULL || index < 0)			//head가 NULL 이거나 index가 0보다 작을 경우 NULL을 반환
		return NULL;

	while (index > 0){						//위의 두가지에 해당하지 않으면 index가 0보다 클때까지
		temp = temp->next;					//temp에 head라는 ListNode의 next값을 대입
		if (temp == NULL)					//해당 값이 없다면 NULL을 반환
			return NULL;					
		index--;							//index 값을 -1한다.
	}

	return temp;							//여기서 이 값은 포인터인가? 값인가?
}

int insertNode(LinkedList *ll, int index, int value){  //insertNode 함수, 정수를 반환

	ListNode *pre, *cur;							//구조체 listNode를 가리키는 포인터 pre, cur선언

	if (ll == NULL || index < 0 || index > ll->size + 1) //ll의 값이 NULL이거나 index가 0보다 작거나, 값이 더해졌을 때 인덱스포다 크다면
		return -1;										// -1 을 반환

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){	//헤드 노드가 없거나, 첫번째에 노드를 삽입하는 경우
		cur = ll->head;						//cur에 head값을 대입(여기서 head는 NULL이거나 어떤 노드를 가리키고 있을 것)
		ll->head = malloc(sizeof(ListNode));//헤드에 ListNode의 사이즈만큼 데이터를 할당한다? 
		ll->head->item = value;				//헤드의 item에 value를 대입하고
		ll->head->next = cur;				//헤드 노드의 다음노드에 NULL이나 헤드에서 밀려난 노드를 대입한다.
		ll->size++;							//링크드 리스트의 사이즈를 1 증가시킨다.
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){	//findNode함수를 호출하는데 여기서 index-1인 이유는 원하는 위치-1 의 뒤에 추가 되어야 해당위치 값을 가질수 있기 때문
		//pre는 삽입 원한는 위치의 전의 노드
		cur = pre->next;						 	//cur에 찾은 값의 다음 노드를 대입한다.(원래 가지고 있던 다음 노드에 대한 정보)
		pre->next = malloc(sizeof(ListNode));		//pre에 다음 노드의 값을 동적으로 할당한다? 값을 늘린다?
		//새 노드를 동적 메모리 할당으로 생성하고, pre->next에 연결한다.
		pre->next->item = value;					//새로 할당한 노드에 값을 저장한다. value가 삽입하고자 하는 값
		pre->next->next = cur;						//새 노드의 다음 노드를 원래 이어져 있던 노드(cur)로 연결한다.
		ll->size++;								//현재 링크드 리스트의 사이즈를 1증가 시킨다.
		return 0;
	}

	return -1;	//삽입이 불가능하다면 -1을 반환
}


int removeNode(LinkedList *ll, int index){	//노드를 삭제하는 함수

	ListNode *pre, *cur;					

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)	//리스트가 비어있거나 인덱스가 0보다 작거나 index가 리스트의 크기보다 작거나 같을 때
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){				//첫번째 노드를 삭제하는 경우
		cur = ll->head->next;		//인덱스 1의 노드를 cur에 대입한다.
		free(ll->head);				//head의 메모리 할당을 반환한다.
		ll->head = cur;				//head 노드에 head 다음의 노드를 대입한다.
		ll->size--;					//노드 사이즈를 1 줄인다.

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){	//pre에 삭제하고자 하는 전 노드의 값을 대입한다.

		if (pre->next == NULL)				// 삭제하고자 하는 노드가 없다면
			return -1;

		cur = pre->next;				//현재 삭제하고자 하는 노드를 cur에 대입한다.
		pre->next = cur->next;			//삭제하고자 하는 노드의 전 값에 삭제하고자 하는 노드의 다음 노드를 대입한다.
		free(cur);					//삭제하고자 하는 노드의 메모리를 반환한다.
		ll->size--;					//리스트 전체의 사이즈를 줄인다.
		return 0;
	}

	return -1;		//삭제하고자 하는 노드의 전값이 없다면 -1을 반환한다.
}
