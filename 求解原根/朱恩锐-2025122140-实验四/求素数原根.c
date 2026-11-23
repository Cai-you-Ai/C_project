#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//定义一个链表，通过链表的先进后出保存二进制每一个数字，用于模重复平方法求幂
typedef struct Binary {
	int data;
	struct Binary* next;
} Binary;

//使用Miller-Rabin素性检测法判断一个数是否为素数
//建立新节点
Binary* newNode_40() {
	Binary* new_node = (Binary*)malloc(sizeof(Binary));
	new_node->next = NULL;
	return new_node;
}

//判断是否为素数
int isPrime_40(int m) {
	//特殊值
	if (m == 2) {
		return 1;
	}
	if (m == 1) {
		return 0;
	}
	//判断是否为正奇数
	if (m % 2 == 0 || m < 0) {
		return 0;
	}
	//分解m-1
	int ex = m - 1;
	int s = 0;
	int t = ex;
	int mod = 0;
	int i, p = 0;
	while (t % 2 == 0) {
		s++;
		t = t / 2;
	}
	//此时s^2+t = ex
	int a;

	for (a = 2; a < ex; a++) {
		for (i = 0; i < s; i++) {
			mod = getMod_40(a, m, t, i);
			if (mod == 1 || mod == m - 1) {
				p = 1;
			}
			if (p == 1) {
				break;
			}
		}
		if (p == 0) {
			return 0;
		}
		else {
			p = 0;
		}
	}
	return 1;
}

//求二进制
Binary* getBinary_40(int n) {
	Binary* p = NULL;
	while (n / 2 != 0) {
		Binary* tmp = newNode_40();
		tmp->data = n % 2;
		tmp->next = p;
		p = tmp;
		n /= 2;
	}
	Binary* tmp = newNode_40();
	tmp->data = 1;
	tmp->next = p;
	p = tmp;
	return p;
}

//倒置二进制
Binary* reBinary_40(Binary* p) {
	if (p == NULL || p->next == NULL) return p;
	Binary* tmp1 = p;
	Binary* tmp2 = p->next;
	Binary* tmp3 = tmp2->next;
	tmp1->next = NULL;
	tmp2->next = tmp1;
	tmp1 = tmp2;
	tmp2 = tmp3;
	while (tmp2) {
		tmp3 = tmp3->next;
		tmp2->next = tmp1;
		tmp1 = tmp2;
		tmp2 = tmp3;
	}
	return tmp1;
}

//通过摸平方法求模
int getMod_40(int a, int m, int t, int s) {
	int tmp1 = 1;
	int tmp2 = a;
	Binary* p = getBinary_40(t * pow(2, s));
	p = reBinary_40(p);
	while (p) {
		if (p->data == 1) {
			tmp1 = (tmp2 * tmp1) % m;
		}
		tmp2 = (tmp2 * tmp2) % m;
		p = p->next;
	}
	return tmp1;
}

//使用辗转相除法求两个数的最大公因数gcd(a,m)
int getFactor_40(int a, int m) {
	int factor = 0;
	int max, min;
	if (a > m) {
		max = a;
	}
	else {
		max = m;
	}
	min = a + m - max;
	if (max % min == 0) {
		return min;
	}
	while (max % min != 0) {
		factor = max % min;
		max = min;
		min = factor;
	}
	return min;
}

//求a对模m的阶
int getIndex_40(int a, int m,Binary* head) {
	int i = 0;
	int mod = 0;
	int ord = 0;
	for (i = 1; i < m; i++) {
		if ((m - 1) % i == 0) {
			Binary* tmp = newNode_40();
			mod = getMod_40(a, m, i, 0);
			tmp->data = i;
			tmp->next = head->next;
			head->next = tmp;
			if (mod == 1 && ord == 0) {
				ord = i;
			}
		}
	}
	return ord;
}

//求原根的函数
void getOrd_40(int a, int m,Binary* head) {
	int g;
	int ord;
	printf("打印所有的阶\n");
	for (g = 2; g < m; g++) {
		ord = getIndex_40(g,m,head);
		printf("%dmod(%d)=%d  ", g, m, ord);
	}
	printf("\n\n");
	for (g = 2; g < m; g++) {
		ord = getIndex_40(g, m, head);
		if (ord == m - 1) {
			printf("找到mod %d的一个原根g=%d\n", m, g);
		}
	}
}

int main() {
	int m;
	int a;
	int ord;
	Binary* head = newNode_40();
	printf("输入整数,m=");
	scanf_s("%d", &m);
	printf("\n");
	while(!isPrime_40(m)) {
		printf("%d不是素数，请重新输入一个整数m\n", m);
		printf("重新输入一个新整数，m=");
		scanf_s("%d", &m);
	}
	printf("\n");
	printf("输入整数，a=");
	scanf_s("%d", &a);
	while(getFactor_40(a,m) != 1) {
		printf("a与m不互素\n");
		printf("重新输入一个整数，a=");
		scanf_s("%d", &a);
	}

	printf("\n**********开始求%d对模%d的阶**********\n",a,m);
	printf("%d的欧拉函数φ(m)值是:%d\n", m, m - 1);
	ord = getIndex_40(a, m,head);
	head = reBinary_40(head);
	Binary* tmp = head;
	tmp = tmp->next;
	while (tmp->next) {
		printf("%d是%d的欧拉函数的因子\n", tmp->data, m);
		tmp = tmp->next;
	}
	printf("%d对模%d的阶为Ordm(a)=%d\n", a, m, ord);
	printf("打印出%d的模%d的阶Ord=%d\n", a, m, ord);

	printf("\n**********开始求%d的原根**********\n",m);
	getOrd_40(a, m,head);
}