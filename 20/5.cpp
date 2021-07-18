#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 1e5+5;
LL a[MAXN],n;
struct Node {
	LL v;
	int index;
	Node(LL a,int b):v(a),index(b){}
	Node():index(-1){}
};
stack<Node> s;
LL ans[MAXN];
int main() {
	scanf("%lld", &n);
	for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
	for(int i=1;i<=n;i++) {
		while(!s.empty() && s.top().v < a[i]) {
			ans[s.top().index] = i;
			s.pop();
		}
		s.push(Node(a[i], i));
	}
	for(int i=1;i<=n;i++) printf("%lld\n", ans[i]);
	return 0;
}
