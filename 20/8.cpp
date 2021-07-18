#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
bool ma[MAXN][MAXN];
int h[MAXN][MAXN];
struct Node {
	int v,index;
	Node(int a,int b):v(a),index(b){}
	Node():index(-1){}
};
struct Stack {
	Node a[MAXN];
	int t;
	inline bool empty() { return (t==0);  }
	inline Node top() { return a[t];  }
	inline void pop() { t--;  }
	inline void push(Node node) { a[++t] = node;  }
	inline void clear() { t=0;  }
	Stack():t(0){}
}q;
int a,b;
int ans;
int main() {
	scanf("%d%d", &a, &b);
	for(int i=1;i<=a;i++) {
		for(int j=1;j<=b;j++) {
			char c[2];
			scanf("%s", c);
			if (c[0]=='F') ma[i][j]=1;
		}
	}
	for(int i=1;i<=b;i++) {
		for(int j=1;j<=a;j++) {
			if (ma[j][i]) h[j][i]=h[j-1][i]+1;
			else h[j][i]=0;
		}
	}
	for(int i=a;i>=1;i--) {
		Stack st = Stack();
		for(int j=1;j<=b;j++) {
			Node node = Node();
			while(!st.empty() && st.top().v >= h[i][j]) {
				node=st.top();st.pop();
				//printf("v=%d index=%d i=%d j=%d\n", node.v, node.index, i, j);
				ans = max(ans, (j-node.index)*node.v);
			}
			if (node.index!=-1) st.push(Node(h[i][j], node.index));
			else st.push(Node(h[i][j], j));
		}
		while(!st.empty()) {
			ans = max(ans, (b-st.top().index+1)*st.top().v);
			st.pop();
		}
	}
	printf("%d\n", 3*ans);
	return 0;
}
