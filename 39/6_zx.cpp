#include <bits/stdc++.h>
#define forGraph(g,u,v,i) for(int i=g.fst[u],v=g.to[i];i;i=g.nxt[i],v=g.to[i])
using namespace std;
const int MAXN = 40005;
int n,m,k;
struct Graph {
    int fst[MAXN], nxt[MAXN<<1], to[MAXN<<1], w[MAXN<<1], tot;
    void add(int u,int v,int ww) {
        to[++tot]=v;
        nxt[tot]=fst[u];
        fst[u]=tot;
        w[tot]=ww;
    }
}g;
struct BinaryIndexTree {
    int a[MAXN<<1];
#define lowbit(x) (x&(-x))
    int query(int i) {
        int res=0;
        while(i) {
            res+=a[i];
            i-=lowbit(i);
        }
        return res;
    }
    void add(int i,int d) {
        while(i<=2*n) {
            a[i]+=d;
            i+=lowbit(i);
        }
    }
}bit;
int startPos[MAXN],endPos[MAXN],depth[MAXN],dfsNum;
int first[MAXN],dNum;
int st[MAXN<<1][20],Log[MAXN<<1];
int lis[MAXN<<1];
void dfs(int i,int pre,int e) {
    depth[i]=depth[pre]+1;
    startPos[i]=++dfsNum;
    first[i]=++dNum;
    lis[dNum]=i;
    bit.add(dfsNum, g.w[e]);
    forGraph(g,i,j,edge) if(j!=pre) {
        dfs(j,i,edge);
        lis[++dNum]=i;
    }
    endPos[i]=++dfsNum;
    bit.add(dfsNum, -g.w[e]);
}
void init() {
    Log[1]=0; for(int i=2;i<=dNum;i++) Log[i]=Log[i/2]+1;
    for(int i=1;i<=dNum;i++) st[i][0]=i;
    for(int j=1;j<=Log[dNum];j++) 
        for(int i=1;i+(1<<j)-1<=dNum;i++) {
            int a=st[i][j-1],b=st[i+(1<<(j-1))][j-1];
            st[i][j]=depth[lis[a]]<depth[lis[b]]?a:b;
        }
}
int lca(int x,int y) {
    x=first[x],y=first[y];
    if (x>y) swap(x,y);
    int len=Log[y-x+1];
    int a = st[x][len], b=st[y-(1<<len)+1][len];
    return lis[depth[lis[a]]<depth[lis[b]]?a:b];
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i=1;i<=m;i++) {
        int u,v,w;char op[2];
        scanf("%d%d%d%s", &u, &v, &w, op);
        g.add(u,v,w);
        g.add(v,u,w);
    }
    dfs(1,1,0);
    init();
    scanf("%d", &k);
    for(int i=1;i<=k;i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        printf("%d\n", bit.query(startPos[x])+bit.query(startPos[y])-2*bit.query(startPos[lca(x,y)]));
    }
    return 0;
}
