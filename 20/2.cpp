#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 400005;
struct Node {
	LL v;
	int index;
	Node(int a,int b):v(a),index(b){}
	Node():index(-1){}
};
int n;
int a[MAXN];
stack<Node> q;
LL ans;
int main() {
	scanf("%d", &n);
	for(int i=1;i<=n;i++) scanf("%d", &a[i]);
	for(int i=1;i<=n;i++) {
		Node node = Node();
		while(!q.empty() && q.top().v >= a[i]) {
			node = q.top();q.pop();
		//	printf("%lld v=%lld index=%d i=%d\n", node.v*(i-node.index), node.v, node.index, i);
			ans=max(ans, node.v*(i-node.index));
		}
		if (node.index != -1) {
			q.push(Node(a[i], node.index));
		} else {
			q.push(Node(a[i], i));
		}
	}
	while(!q.empty()) {
		Node node = q.top();
		q.pop();
		ans = max(ans, node.v*(n-node.index+1));
	}
	printf("%lld\n", ans);
	return 0;
}
