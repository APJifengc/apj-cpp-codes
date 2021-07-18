#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
int tot,nxt[MAXN*100],fst[MAXN],to[MAXN*100],n;
void add(int i,int j) {
    to[++tot]=j;
    nxt[tot]=fst[i];
    fst[i]=tot;
}
int dfn[MAXN], low[MAXN], num;
int root;
bitset<MAXN> cutPoint;
void tarjan(int u) {
    dfn[u]=low[u]=++num;
    int flag=0;
    for(int edge=fst[u]; edge; edge=nxt[edge]) {
        int v=to[edge];
        if (!dfn[v]) {
            tarjan(v);
            low[u]=min(low[u],low[v]);
            if (low[v]>=dfn[u]) {
                flag++;
                if (u!=root || flag>1) {
                    cutPoint[u]=1;
                }
            }
        } else {
            low[u]=min(low[u],dfn[v]);
        }
    }
}
int main() {
	scanf("%d", &n);
    int x,y;
    while(~scanf("%d%d", &x, &y)) add(x,y),add(y,x);
    for(int i=1;i<=n;i++)
        if (!dfn[i]) {
            root=i;
            tarjan(i);
        }
    printf("%d\n", cutPoint.count());
    for(int i=1;i<=n;i++) {
        if (cutPoint[i]) printf("%d\n", i);
    }
    return 0;
}
