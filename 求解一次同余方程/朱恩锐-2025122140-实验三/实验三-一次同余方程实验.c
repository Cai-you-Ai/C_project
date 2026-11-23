#include<stdio.h>
#include<math.h>
#include<stdlib.h>

typedef struct List {
	int tmp1;
	int tmp2;
	struct List* next;
} List;

//建立新节点
List* newNode_40() {
	List* node = (List*)malloc(sizeof(List));
	node->next = NULL;
	return node;
}

//得到尾节点
List* getTail_40(List* head) {
	List* tail = head;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	return tail;
}

//通过尾插法插入新元素
List* insertTail_40(List* tail, int s, int t) {
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

//缩小节点
List* reduceList_40(List* head,int f) {
	List* tmp = head->next;
	if (f == 0) {
		return;
	}
	while (tmp != NULL) {
		tmp->tmp1 = tmp->tmp1 / f;
		tmp->tmp2 = tmp->tmp2 / f;
		tmp = tmp->next;
	}
	return head;
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
	while (m % n != 0) {
		tail = insertTail_40(tail, m, n);
		reminder = m % n;
		tmp = n;
		n = reminder;
		m = tmp;
	}
	return reminder;
}

//欧几里得扩展算法
int getBailuo_40(List* head, List* head1) {
	head = reList_40(head);
	List* tmp = head;
	List* tail = getTail_40(head1);
	tmp = tmp->next;
	tail = insertTail_40(tail, 1, -(tmp->tmp1 / tmp->tmp2));
	while (tmp->next != NULL) {
		tmp = tmp->next;
		tail = insertTail_40(tail, (tail->tmp2), (tail->tmp2) * (-(tmp->tmp1 / tmp -> tmp2)) + tail->tmp1);
	}
	return tail->tmp1;
}

//求解一次同余方程
void resolveFormat_40(int factor,int x0,int b,int m) {
	int i = 0;
	for (i = 0; i < factor; i++) {
		printf("x = %d(mod %d)  ", (b / factor * x0 + (m / factor) * i)%m,m);
	}
}

int main() {
	int a, m, b,factor;
	List* head = newNode_40();
	List* head1 = newNode_40();
	printf("请输入a: a=");
	scanf_s("%d", &a);
	printf("请输入b: b=");
	scanf_s("%d", &b);
	printf("请输入m: m=");
	scanf_s("%d", &m);

	factor = getCommonFactor_40(a, m, head);
	if (b % factor != 0) {
		printf("gcd(a,m)不能整除b，该方程无解");
		return 0;
	}
	printf("gcd(a,m)=%d\na/(a,m)=%d\nb/(a,m)=%d\nm/(a,m)=%d\n", factor,(a/factor),(b/factor),(m/factor));

	head = reduceList_40(head, factor);
	int x0 = ((getBailuo_40(head, head1)) + (m / factor))%m;
	printf("一次同余方程a/(a,m) x=1(mod m/(a,m)) 的解为：x=%d(mod %d)\n", x0,m/factor);
	printf("一次同余方程%d x=%d (mod %d)的解为:\n",a, b, m);
	resolveFormat_40(factor,x0,b,m);
	return 0;
}
