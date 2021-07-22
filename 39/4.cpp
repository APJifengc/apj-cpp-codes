#include <bits/stdc++.h>
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
#define int long long
using namespace std;
const int MAXN = 250005;
int n,m;
struct Graph {
    int fst[MAXN],to[MAXN<<1],nxt[MAXN<<1],tot;
    void add(int u,int v) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
    }
}g;
struct BinaryIndexTree {
    int arr[MAXN<<1];
#define lowbit(x) (x&(-x))
    void add(int i,int d) {
        while(i<=2*n) {
            arr[i]+=d;
            i+=lowbit(i);
        }
    }
    int query(int i) {
        int res=0;
        while(i) {
            res+=arr[i];
            i-=lowbit(i);
        }
        return res;
    }
    BinaryIndexTree() { memset(arr, 0, sizeof arr); }
}bit;
int beginPos[MAXN], endPos[MAXN], dfsNum, depth[MAXN];
void dfs(int i,int pre) {
    depth[i]=depth[pre]+1;
    beginPos[i]=++dfsNum;
    forGraph(g,i,j,edge) if(j!=pre) dfs(j,i);
    endPos[i]=++dfsNum;
}
signed main() {
    scanf("%lld", &n);
    for(int i=1;i<n;i++) {
        int a,b;
        scanf("%lld%lld", &a, &b);
        g.add(a,b);
        g.add(b,a);
    }
    dfs(1, 1);
    scanf("%lld", &m);
    for(int i=1;i<=n+m-1;i++) {
        char op[2];int a;
        scanf("%s%lld", op, &a);
        if (op[0]=='A') {
            int b;scanf("%lld", &b);
            int x=max(a,b);
            bit.add(beginPos[x], 1);
            bit.add(endPos[x], -1);
        } else {
            printf("%lld\n", depth[a]-bit.query(beginPos[a])-1);
        }
    }
	return 0;
}
