#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#define Max 1000
int IsBalance(int x) {
	int a[Max];
	int cnt0=0, cnt1 = 0;
	for (int i = 0; i < Max; i++) {
		a[i] = x % 2;
		if (a[i] == 0)
			cnt0++;
		else cnt1++;
		x = x / 2;
		if (x == 1) {
			cnt1++;
			break;
		}
	}
	if (cnt0 == cnt1)
		return 1;
	else return 0;
}
int main() {
	int n, x;
	int cnt=0, judge = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		judge = IsBalance(x);
		if (judge==1)
			cnt++;
		
	}
	printf("%d", cnt);
	return 0;
}