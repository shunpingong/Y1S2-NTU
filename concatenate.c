////////////////////////////////////////////////////////////////////

//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int num;
	struct _listnode *next;
} ListNode;
typedef struct _linkedlist{
	ListNode *head;
	int size;
} LinkedList;
typedef struct _dbllistnode{
	int num;
	struct _dbllistnode *pre;
	struct _dbllistnode *next;
} DblListNode;
////////////////////////////////////////////////////////////////////
////////////

int removeNode(ListNode **ptrHead, int index);
int removeNode2(LinkedList *ll,int index);
int split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList);
int duplicateReverse(ListNode *head, ListNode **ptrNewHead);

void printList(ListNode *head);
ListNode * findNode(ListNode *head, int index);
int insertNode(ListNode **ptrHead, int index, int value);



// these are for the practice questions
int moveMaxToFront(ListNode **ptrHead);
int concatenate(ListNode **ptrHead1, ListNode *head2);
int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2);
int insertDbl(DblListNode **ptrHead, int index, int value);
void printDblList(DblListNode *head);
////////////////////////////////////////////////////////////////////
////////////
int main()
{
	int i;
	char reply;
	ListNode *head = NULL;
	ListNode *dupRevHead = NULL;
	ListNode *oddHead = NULL;
	ListNode *evenHead = NULL;
	ListNode *list1Head=NULL, *list2Head=NULL;
	ListNode *combAltHead = NULL;
	DblListNode *dblHead = NULL;
	LinkedList llist;
	int size=0;

	//build a linked list
	if (insertNode(&head, 0, 6)==0) size++;
	if (insertNode(&head, 0, 4)==0) size++;
	if (insertNode(&head, 0, 2)==0) size++;
	printf("After inserting 3 values.");
	printList(head);


	//removeNode(): question 1
	if (removeNode(&head, 3)==0) size--;//this one can't be removed.
	if (removeNode(&head, 1)==0) size--;
	if (removeNode(&head, 0)==0) size--;

	printf("\nafter remove using removeNode(), ");
	printList(head);

	//insert some nodes
	if (insertNode(&head, 2, 3)==0) size++; // this one can't be inserted.
	if (insertNode(&head, 1, 1)==0) size++;
	if (insertNode(&head, 0, 0)==0) size++;

	printf("\nafter insert, ");
	printList(head);


	//removeNode2(): question 2
	llist.head =head;
	llist.size = size;
	removeNode2(&llist, 2);
	removeNode2(&llist, 0);
	removeNode2(&llist, 0);
	head=llist.head;


	printf("\nafter remove using removeNode2(), ");
	printList(llist.head);
	// empty linked list now

	//split(): question 3
	for (i = 1; i <10; i++)//build a new linked list
		insertNode(&head, 0, i);
	printf("\n\ninsert 1-9 to the linked list,");
	printList(head);
	printf("split the current list, results:\n");
	split(head, &evenHead, &oddHead);
	printf("the even list");
	printList(evenHead);
	printf("the odd list");
	printList(oddHead);

	//duplicateReverse(): question 4
	printf("\n");
	printList(head);
	duplicateReverse(head, &dupRevHead);
	printf("After duplicateReverse(),");
	printList(dupRevHead);

	////////////////////////////////////////////////////////////////////////
	//the following are for the PRACTICE QUESTIONS

	printf("\n\nNow for the practice questions");

	//1.moveMaxToFront()
	printf("\n************** moveMaxToFront *******************\n");
	printList(dupRevHead);
	moveMaxToFront(&dupRevHead);
	printf("after moveMaxToFront()");
	printList(dupRevHead);

	//3. concatenate()
	printf("\n************** concatenate() *******************\n");
	concatenate(&head, dupRevHead);
	printf("concatenate(current list, duplicate reverse list)\n  ");
	printList(head);


	printf("enter any key to exit:");
	fflush(stdin);
	scanf("%c", &reply);
}
////////////////////////////////////////////////////////////////////
void printList(ListNode *head){
	ListNode *cur=head;

	if (cur == NULL)
		return;

	printf("the current linked list is:\n");
	while (cur != NULL){
		printf("%d ", cur->num);
		cur = cur->next;
	}
	printf("\n");
}

void printDblList(DblListNode *head){
	if (head == NULL) return;
	while (head != NULL){
		printf("%d ", head->num);
		head = head->next;
	}
	printf("\n");
}

ListNode * findNode(ListNode *head, int index){
	if (head == NULL || index < 0) return NULL;
	while (index > 0){
		head = head->next;
		if (head == NULL)
			return NULL;
		index--;
	}
	return head;
}


int insertNode(ListNode **ptrHead, int index, int value){
	ListNode *pre, *cur;
	// If empty list or inserting first node, need to update head pointer
	if (*ptrHead == NULL || index == 0){
		cur = *ptrHead;
		*ptrHead = malloc(sizeof(ListNode));
		(*ptrHead)->num = value;
		(*ptrHead)->next = cur;
		return 0;
	}
	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ptrHead, index-1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->num = value;
		pre->next->next = cur;
		return 0;
	}
	return -1;
}
////////////////////////////////////////////////////////////////////
int removeNode(ListNode **ptrHead, int index){
	ListNode *pre, *cur;
	// Sanity check for empty list
	if (*ptrHead == NULL)
		return -1;
	// If removing first node, need to update head pointer
	if (index == 0){
		cur = *ptrHead;
		 *ptrHead = cur->next;
		free(cur);
		return 0;
	}
	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ( (pre = findNode(*ptrHead, index-1))!= NULL){
		if (pre->next == NULL) return -1;
		cur = pre->next;
		pre->next=cur->next;
		free(cur);
		return 0;
	}
	return -1;
}
////////////////////////////////////////////////////////////////////////////////
int removeNode2(LinkedList *ll, int index) {
	ListNode *cur, *pre;

	if (ll->head ==NULL) return -1;

	if (index==0)
	{
		cur=ll->head;
		ll->head =cur->next;
		free(cur);
		ll->size --;
		return 0;
	}

	if ( (pre = findNode(ll->head,index-1))!= NULL)
	{//not the first node
		if (pre->next == NULL) return -1;
		cur = pre->next;
		pre->next=cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}


int split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList)
{
	int even = 1, evenSize = 0, oddSize = 0;
	ListNode *cur=head;

	if (cur == NULL)
		return -1;
	while (cur!= NULL){
		if (even==1){
			insertNode(ptrEvenList, evenSize, cur->num);
			evenSize++;
		}
		else{
			insertNode(ptrOddList, oddSize, cur->num);
			oddSize++;
		}
	cur = cur ->next;
	even = -even;
	}
	return 0;
}

int duplicateReverse(ListNode *head, ListNode **ptrNewHead){
	ListNode *cur=head;

	if (cur == NULL) return -1;
	// Simply traverse the list and insert each visited node into the new list at index 0 each time
	while (cur != NULL){

		if (insertNode(ptrNewHead, 0, cur->num) == -1)
			return -1;
		cur = cur ->next;
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
int moveMaxToFront(ListNode **ptrHead)
{
    ListNode *pre, *cur;
	ListNode *preMax = NULL;
	int maxItem;
	// Empty list
	if (*ptrHead == NULL) return -1;
	// Only one node in the list
	if ( (*ptrHead)->next == NULL )
		return 0;
	cur = (*ptrHead);
	maxItem = (*ptrHead)->num;
	// preMax gets set to the address of the ListNode with the max value
	// If preMax is still NULL at the end, first node had the max value
	while (cur != NULL){
		if (cur->num > maxItem){
			maxItem = cur->num;
			preMax = pre;
			}
		pre = cur;
		cur = cur->next;
	}
	// Never saw a value higher than the first node, nothing to move
	if (preMax == NULL)
		return 0;
	// Move node with max value to first position
	cur = preMax->next;
	preMax->next = preMax->next->next;
	// Update head pointer
	cur->next = *ptrHead;
	*ptrHead = cur;
	return 0;
}


int concatenate(ListNode **ptrHead1, ListNode *head2)
{
	ListNode *temp = *ptrHead1;
	
	if (*ptrHead1 ==NULL && head2 ==NULL){
		return -1;
	}
	if (*ptrHead1 == NULL && head2!= NULL){
		*ptrHead1 = head2;
		return 0;
	}
	if (head2 == NULL){
		return 0;
	}
	//temp->next != NULL, we ensure that the loop terminates when temp points to the last node of the linked list, and we avoid accessing a null pointer
	while (temp->next != NULL){
		temp = temp->next;
	}
	temp->next = head2;
	return 0;
}