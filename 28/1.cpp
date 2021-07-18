#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000005;
int tot,nxt[MAXN*2],first[MAXN],to[MAXN*2],n;
void add(int i,int j) {
    to[++tot]=j;
    nxt[tot]=first[i];
    first[i]=tot;
}
int dfn[MAXN], low[MAXN], num;
bool inStack[MAXN];
stack<int> st;
int minCnt = INT_MAX;
void tarjan(int u) {
    dfn[u]=low[u]=++num;
    st.push(u);
    inStack[u]=1;
    for(int edge=first[u]; edge; edge=nxt[edge]) {
        int v=to[edge];
        if (!dfn[v]) {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        } else if (inStack[v]) {
            low[u]=min(low[u],dfn[v]);
        }
    }
    if (dfn[u]==low[u]) {
        int cnt=0;
        while(st.top()!=u) {
            //printf("%d ", st.top());
            inStack[st.top()]=0;
            st.pop();
            cnt++;
        }
        //printf("%d, cnt=%d\n", u, cnt+1);
        inStack[u]=0;
        st.pop();
        if (cnt!=0) minCnt = min(minCnt, cnt+1);
    }
}
int main() {
	scanf("%d", &n);
    for(int i=1;i<=n;i++) {
        int x;
        scanf("%d", &x);
        add(i,x);
    }
    for(int i=1;i<=n;i++)
        if (!dfn[i]) 
            tarjan(i);
    printf("%d\n", minCnt);
	return 0;
}
