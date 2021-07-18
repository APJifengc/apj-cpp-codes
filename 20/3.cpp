#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 100005;
LL a[MAXN],n;
struct Node {
	LL v,index;
	Node(LL a,LL b):v(a),index(b){}
	Node():index(-1){}
};
stack<Node> s;
LL ans;
LL prefix[MAXN];
int main() {
	scanf("%lld", &n);
	for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
	for(int i=1;i<=n;i++) prefix[i]=prefix[i-1]+a[i];
	for(int i=1;i<=n;i++) {
		Node node = Node();
		while(!s.empty() && s.top().v >= a[i]) {
			node = s.top();
			s.pop();
			//printf("%d v=%d index=%d i=%d\n", node.v*(prefix[i-1]-prefix[node.index-1]), node.v, node.index, i);
			ans = max(ans, node.v*(prefix[i-1]-prefix[node.index-1]));
		}
		if (node.index!=-1) {
			s.push(Node(a[i], node.index));
		} else {
			s.push(Node(a[i], i));
		}
	}
	while(!s.empty()) {
		Node node = s.top();
		s.pop();
		//printf("%d v=%d index=%d n=%d\n", node.v*(prefix[n]-prefix[node.index-1]), node.v, node.index, n);
		ans = max(ans, node.v*(prefix[n]-prefix[node.index-1]));
	}
	printf("%lld\n", ans);
	return 0;
}
