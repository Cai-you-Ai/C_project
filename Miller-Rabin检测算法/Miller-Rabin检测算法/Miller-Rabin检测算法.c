//信息安全254 朱恩锐 2025122140 本题参数m=2001
/*
算法说明：
本算法旨在通过Miller-Rabin检测算法检测一个数是否为素数
1.接收本题参数m,首先求出指数m-1(正奇数)
2.将m-1化成二进制的形式，并将二进制数字使用栈存储便于在进行模幂运算时取出使用
3.取每一个a，从2取到m-1分别进行检测mod(m)是否等于1或-1(m-1)
4.使用模重复平方法算出mod
5.如果一个a中的每一个从a^t到a^(t*2^s)都不满足条件，则判断m为合数，结束循环。否则取下一个a进行判断
*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//定义一个栈，通过栈的先进后出保存二进制每一个数字
typedef struct Binary {
	int data;
	struct Binary* next;
} Binary;


//建立新节点
Binary* newNode() {
	Binary* new_node = (Binary*)malloc(sizeof(Binary));
	new_node->next = NULL;
	return new_node;
}

//判断是否为素数
int isPrime(int m) {
	//特殊值
	if (m ==  2) {
		return 1;
	}
	if (m == 1) {
		return 0;
	}
	//判断是否为正奇数
	if (m % 2 == 0 || m<0) {
		return 0;
	}
	//分解m-1
	int ex = m - 1;
	int s = 0;
	int t = ex;
	int mod = 0;
	int i,p = 0;
	while (t % 2 == 0) {
		s++;
		t = t / 2;
	}
	//此时s^2+t = ex
	int a;
	
	for(a=2;a<ex;a++) {
		for (i = 0; i < s; i++) {
			mod = getMod(a, m, t, i);
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
Binary* getBinary(int n) {
	Binary* p = NULL;
	while (n / 2 != 0) {
		Binary* tmp = newNode();
		tmp->data = n % 2;
		tmp->next = p;
		p = tmp;
		n /= 2;
	}
		Binary* tmp = newNode();
		tmp->data = 1;
		tmp->next = p;
		p = tmp;
		return p;
}

//倒置二进制
Binary* reBinary(Binary* p) {
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

//通过求模幂运算求模
int getMod(int a, int m,int t,int s) {
	int tmp1 = 1;
	int tmp2 = a;
	Binary* p =getBinary(t * pow(2,s));
	p = reBinary(p);
	while (p) {
		if (p->data == 1) {
			tmp1 = (tmp2 * tmp1) % m;
		}
		tmp2 = (tmp2 * tmp2) % m;
		p = p->next;
	}
	return tmp1;
}
/*---------------------------------函数区---------------------------------*/
int main() {
	int m;
	printf("请输入待测整数:____\b\b\b\b");
	scanf_s("%d", &m);
	if (isPrime(m)) {
		printf("%d是素数\n", m);
	}
	else {
		printf("%d不是素数\n", m);
	}
}