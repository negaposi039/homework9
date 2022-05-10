/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
void freeNode(Node* ptr); // 재귀 함수로 노드 메모리 할당 해제 함수

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n[----- [Kim Hyeong Jin]  [2021041079] -----]\n");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': // 메뉴 z : 트리 초기화 함수 호출
			initializeBST(&head);
			break;
		case 'q': case 'Q': // 메뉴 q : 메모리 할당 해제 함수 호출
			freeBST(head);
			break;
		case 'n': case 'N': // 메뉴 n : 노드 추가 함수 호출
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D': // 메뉴 d : 단말노드 삭제 함수 호출
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F': // 메뉴 f : 반복문으로 key 값에 대한 노드 탐색 함수 호출 후 결과 출력
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S': // 메뉴 s : 재귀함수로 key 값에 대한 노드 탐색 함수 호출 후 결과 출력
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':  // 메뉴 i : 중위 운행 함수 호출
			inorderTraversal(head->left);
			break;
		case 'p': case 'P': // 메뉴 p : 전위 운행 함수 호출
			preorderTraversal(head->left);
			break;
		case 't': case 'T': // 메뉴 t : 후위 운행 함수 호출
			postorderTraversal(head->left);
			break;
		default: // 이외의 경우 : 에러 메시지
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 메뉴 q : 반복문 탈출 후 종료

	return 1;
}

int initializeBST(Node** h) { // 트리 초기화 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) // NULL이 아닐 시
		freeBST(*h); // 할당 해제 함수 호출

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // 동적 할당
	(*h)->left = NULL;	/* root */ // 초기화
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr) // 중위 운행 함수
{
	if(ptr) {
		inorderTraversal(ptr->left); // 부모 노드의 왼쪽 자식 노드 탐색
		printf(" [%d] ", ptr->key); // 부모 노드의 key 값 출력
		inorderTraversal(ptr->right); // 부모 노드의 오른쪽 자식 노드 탐색
	}
}

void preorderTraversal(Node* ptr) // 전위 운행 함수
{
	if(ptr) {
		printf(" [%d] ", ptr->key); // 부모 노드의 key 값 출력
		preorderTraversal(ptr->left); // 부모 노드의 왼쪽 자식 노드 탐색
		preorderTraversal(ptr->right); // 부모 노드의 오른쪽 자식 노드 탐색
	}
}

void postorderTraversal(Node* ptr) // 후위 운행 함수
{
	if(ptr) {
		postorderTraversal(ptr->left); // 부모 노드의 왼쪽 자식 노드 탐색
		postorderTraversal(ptr->right); // 부모 노드의 오른쪽 자식 노드 탐색
		printf(" [%d] ", ptr->key); // 부모 노드의 key 값 출력
	}
}


int insert(Node* head, int key) // 트리 노드 추가 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // 새로 추가할 노드의 부모 노드 포인터 할당
	newNode->key = key; // 입력한 key 값 저장
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) { // 트리에 노드가 없으면
		head->left = newNode;  // 새로 추가할 노드를 첫 노드로 저장
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;  // ptr 포인터에 head->left 저장

	Node* parentNode = NULL; // parentNode 포인터에 NULL 저장
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // ptr->key < key 이면
			ptr = ptr->right; // ptr에 ptr->right 저장
		else
			ptr = ptr->left; // ptr에 ptr->left 저장
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) // parentNode->key > key 이면
		parentNode->left = newNode; // 왼쪽에 newNode 저장
	else
		parentNode->right = newNode; // 오른쪽에 newNode 저장
	return 1;
}

int deleteLeafNode(Node* head, int key) // 단말 노드 삭제 함수
{
	if (head == NULL) { // head가 NULL 이면
		printf("\n Nothing to delete!!\n"); // 에러 메시지
		return -1;
	}

	if (head->left == NULL) { // head->left가 NULL 이면
		printf("\n Nothing to delete!!\n"); // 에러 메시지
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) { // ptr->key가 key이면
			if(ptr->left == NULL && ptr->right == NULL) { // ptr이 단말 노드이면

				/* root node case */
				if(parentNode == head)
					head->left = NULL; // NULL 저장

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL; // NULL 저장
				else
					parentNode->right = NULL; // NULL 저장

				free(ptr); // 메모리 해제
			}
			else { // 단말 노드가 아닐 경우
				printf("the node [%d] is not a leaf \n", ptr->key); // 단말 노드가 아니라는 메시지
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // ptr->key < key이면
			ptr = ptr->right; // ptr에 ptr->right 저장
		else
			ptr = ptr->left; // ptr에 ptr->left 저장


	}

	printf("Cannot find the node for key [%d]\n ", key); // 이외의 경우 key에 대한 노드가 없다는 메시지

	return 1;
}

Node* searchRecursive(Node* ptr, int key) // 재귀함수로 key 값에 대한 노드 탐색 함수
{
	if(ptr == NULL) // ptr이 NULL이면
		return NULL; // NULL 리턴

	if(ptr->key < key) // 입력받은 key 값이 더 크면
		ptr = searchRecursive(ptr->right, key); // 함수 호출하여 오른쪽 탐색
	else if(ptr->key > key) // ptr->key가 더 크면
		ptr = searchRecursive(ptr->left, key); // 함수 호출하여 왼쪽 탐색

	/* if ptr->key == key */
	return ptr; // ptr 리턴

}
Node* searchIterative(Node* head, int key) // 반복문으로 key 값에 대한 노드 탐색 함수
{
	/* root node */
	Node* ptr = head->left; // key 값에 대한 노드 포인터

	while(ptr != NULL) // NULL이 아니면 반복
	{
		if(ptr->key == key) // key 값과 같으면
			return ptr; // ptr 리턴

		if(ptr->key < key) ptr = ptr->right; // key 값이 더 크면 오른쪽 탐색
		else // 이외의 경우 (key 값이 더 작으면)
			ptr = ptr->left; // 왼쪽 탐색
	}

	return NULL;
}

void freeNode(Node* ptr) // 재귀함수로 노드 메모리 할당 해제 함수
{
	if(ptr) {
		freeNode(ptr->left); // 왼쪽 자식노드로 freeNode 호출
		freeNode(ptr->right); // 오른쪽 자식노드로 freeNode 호출
		free(ptr); // ptr 메모리 할당 해제
	}
}

int freeBST(Node* head) // 메모리 할당 해제 함수
{

	if(head->left == head) // head->left가 head이면
	{
		free(head); // head 할당 해제
		return 1;
	}

	Node* p = head->left; 

	freeNode(p); // freeNode 함수 호출

	free(head); // head 할당 해제
	return 1;
}





