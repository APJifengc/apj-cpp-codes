#include <bits/stdc++.h>
#define forGraph(u,v,i) for(int i=fst[u],v=to[i];i;i=nxt[i],v=to[i])
using namespace std;
const int MAXN = 100005, MAXM = 1000005;
int nxt[MAXM],fst[MAXN],to[MAXM],tot;
int dfn[MAXN],low[MAXN],num,n,m;
bitset<MAXN> cutpoint;
void add(int u,int v) {
    to[++tot]=v;
    nxt[tot]=fst[u];
    fst[u]=tot;
}
int root;
long long cnt[MAXN],ans[MAXN];
void tarjan(int u) {
    //printf("%d->", u);
    dfn[u]=low[u]=++num;
    long long flag=0,z=0;
    cnt[u]=1;
    forGraph(u,v,edge) {
        if (!dfn[v]) {
            tarjan(v);
            //printf("%d->%d(%d)\n", u, v, cnt[v]);
            //printf("\nans[%d]+=%d (=%d)\n", u, (cnt[u]-1)*cnt[v], ans[u]);
            //printf("cnt[%d]+=%d (=%d)\n", u, cnt[v], cnt[u]);
            low[u]=min(low[u],low[v]);
            if (low[v]>=dfn[u]) {
                ans[u]+=z*cnt[v];
                z+=cnt[v];
                flag++;
                if (flag>1 || u!=root) {
                    cutpoint[u]=1;
                }
            }
            cnt[u]+=cnt[v];
        } else {
            low[u]=min(low[u],dfn[v]);
        }
    }
    ans[u]+=z*(n-z-1);
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i=1;i<=m; i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        add(x,y);
        add(y,x);
    }
    for(int i=1;i<=n;i++) {
        if (!dfn[i]) {
            root=i;
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++) {
        //printf("cnt[%d]=%d\n",i,cnt[i]);
        if (cutpoint[i]) {
            printf("%lld\n", (ans[i]+n-1)*2LL);
        } else {
            printf("%d\n", (n-1)*2);
        }
    }
    return 0;
}
