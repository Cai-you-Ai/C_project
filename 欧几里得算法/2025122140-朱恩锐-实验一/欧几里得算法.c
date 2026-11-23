#include<stdio.h>
#include<math.h>
#include<stdlib.h>
//定义一个链表用于存储在就计算过程中产生的数字
typedef struct List {
	int tmp1;
	int tmp2;
	struct List* next;
} List;

//定义一个结构体便于存储裴蜀对数
typedef struct bailuo {
	int s;
	int t;
} bailuo;

//建立新节点，在每次建立节点时分配内存
List* newNode_40() {
	List* node = (List*)malloc(sizeof(List));
	node->next = NULL;
	return node;
}

//得到尾节点，便于后续使用
List* getTail_40(List* head) {
	List* tail = head;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	return tail;
}

//通过尾插法插入新元素
List* insertTail_40(List* tail,int s,int t) {
	List* tmp = newNode_40();
	tmp->tmp1 = s;
	tmp->tmp2 = t;
	tail->next = tmp;
	tail = tmp;
	return tail;
}

//将反转链表便于取数
List* reList_40(List* head) {
	List* tmp;
	List* t;
	tmp = head->next;
	head->next = NULL;
	while (tmp != NULL) {
		t = tmp->next;
		tmp->next = head->next;
		head->next = tmp;
		tmp = t;
	}
	return head;
}
//打印元素，printList_40为打印求最大公因数的函数，printList1_40为打印求裴蜀函数的函数
void printList_40(List* head) {
	List* tmp = head;
	while (tmp->next != NULL) {
		tmp = tmp->next;
		printf("%d = %d x %d + %d\n", tmp->tmp1, tmp->tmp2, tmp->tmp1 / tmp->tmp2, tmp->tmp1 % tmp->tmp2);
	}
}

void printList1_40(List* head,List* head1,int reminder) {
	List* t1 = head;
	List* t2 = head1;
	while (t1->next != NULL&& t2->next != NULL) {
		t1 = t1->next;
		t2 = t2->next;
		printf("%d = %d x %d + %d x %d\n",reminder,t1->tmp1,t2->tmp1,t1->tmp2,t2->tmp2);
	}
}

//实现欧几里得算法辗转相除得到最大公因数功能的函数
int getCommonFactor_40(int m, int n, List* head) {
	List* tail = getTail_40(head);
	int reminder = 1;
	int tmp = 0;
	int Bus = 1;
	if (m % n == 0) {
		return n;
	}
	while (m%n != 0) {
		tail = insertTail_40(tail,m,n);
		reminder = m % n;
		tmp = n;
		n = reminder;
		m = tmp;

	}
	return reminder;
}

//求裴蜀对数得到逆元功能的函数
bailuo getBailuo_40(List* head,List* head1) {
	head = reList_40(head);
	List* tmp = head;
	List* tail = getTail_40(head1);
	tmp = tmp->next;
	tail = insertTail_40(tail, 1, -(tmp->tmp1 / tmp->tmp2));
	while (tmp->next != NULL) {
		tmp = tmp->next;
		tail = insertTail_40(tail, (tail->tmp2),(tail->tmp2)* ( - (tmp->tmp1 / tmp->tmp2))+tail->tmp1);
	}
	bailuo b;
	b.s = tail->tmp1;
	b.t = tail->tmp2;
	return b;
}

//----------------------函数区----------------------

int main() {
	int m, n,common_factor;
	List* head = newNode_40();
	List* head1 = newNode_40();
	printf("请输入待测的的一个数__\b\b");
	scanf_s("%d", &m);
	printf("请输入待测的的二个数__\b\b");
	scanf_s("%d", &n);
	printf("\n-------------------------------------------\n");
	
	//求最大公因数
	int CommonFactor = getCommonFactor_40(m, n, head);
	printf("最大公因数是:%d\n", CommonFactor);
	printf("辗转相除：\n");
	printList_40(head);
	printf("\n");

	//求裴蜀对数
	bailuo bailuo_factor = getBailuo_40(head, head1);
	printf("裴蜀对数:s=%d,t=%d\n", bailuo_factor.s, bailuo_factor.t);
	printf("求逆元：\n");
	printList1_40(head, head1,CommonFactor);
}