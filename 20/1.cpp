#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
struct Node {
	int v,index;
	Node(int a,int b):v(a),index(b){}
};
deque<Node> qmin,qmax;
int a[MAXN],n,k;
int ans[MAXN][2];
int main() {
	scanf("%d%d", &n, &k);
	for(int i=1; i<=n; i++) scanf("%d", &a[i]);
	for(int i=1; i<=n; i++) {
		while(!qmax.empty() && qmax.back().v < a[i]) qmax.pop_back();
		while(!qmin.empty() && qmin.back().v > a[i]) qmin.pop_back();
		qmax.push_back(Node(a[i], i));
		qmin.push_back(Node(a[i], i));
		while(!qmax.empty() && qmax.front().index<=i-k) qmax.pop_front();
		while(!qmin.empty() && qmin.front().index<=i-k) qmin.pop_front();
		if (i>=k) ans[i-k][0]=qmin.front().v,ans[i-k][1]=qmax.front().v;
	}
	for(int i=0;i<=n-k; i++) printf("%d ", ans[i][0]);
	printf("\n");
	for(int i=0;i<=n-k; i++) printf("%d ", ans[i][1]);
	printf("\n");
	return 0;
}
