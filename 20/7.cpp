#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
int a[MAXN];
struct Node {
	int v,index;
	Node(int a,int b):v(a),index(b){}
	Node():index(-1){}
};
stack<Node> s;
int n,w;
int ans;
int main() {
	scanf("%d%d", &n, &w);
	for (int i=1;i<=n;i++) scanf("%d%d", &w, &a[i]);
	for(int i=1;i<=n;i++) {
		Node node = Node();
		while(!s.empty() && s.top().v >= a[i]) {
			node = s.top();
			s.pop();
			if (node.v != a[i]) ans++;
		}
		if (node.index != -1) {
			s.push(Node(a[i], node.index));
		} else {
			s.push(Node(a[i], i));
		}
	}
	while (!s.empty() && s.top().v != 0) {
		s.pop();
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}
