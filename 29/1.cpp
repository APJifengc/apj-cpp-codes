#include <bits/stdc++.h>
using namespace std;
void exgcd(int a,int b,int &x,int &y) {
	if (!b) x=1,y=0;
	else {
		exgcd(b, a%b, x, y);
		int t=x;x=y;y=t-(a/b)*y;
	}
}
int a,b;
int main() {
	scanf("%d%d",&a,&b);
	int x,y;
	exgcd(a,b,x,y);
	printf("%d\n", (x%b+b)%b);
	return 0;
 }
