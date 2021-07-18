#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 1000005;
struct Stack {
	int a[MAXN];
	int t;
	inline bool empty() { return (t==0);  }
	inline int top() { return a[t];  }
	inline void pop() { t--;  }
	inline void push(int node) { a[++t] = node;  }
	inline void clear() { t=0;  }
	Stack():t(0){memset(a,0,sizeof(a));}

}l;
LL maxr;
int n,m;
int a[MAXN];
LL p[MAXN];
int ans;
int main() {
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++) scanf("%d", &a[i]);
	while(m--) {
		int k; scanf("%d", &k);
		for(int i=1;i<=n;i++) p[i]=p[i-1]+a[i]-k;
		l.clear ();
		for(int i=1;i<=n;i++) if (p[i]<=p[l.top()]) l.push(i);
		ans = 0;
		for(int i=n;i>=1;i--) {
			while(!l.empty() && p[i]>=p[l.a[l.t-1]]) l.pop();
			ans=max(ans, i-l.top());		
		}
		printf("%d ", ans);

	}
	printf("\n");
	return 0;

}


