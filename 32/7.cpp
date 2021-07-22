#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005, MAXK = 65;
int n,k,last[MAXK];
typedef pair<int,int> Node;
#define index first
#define type second
Node nodes[MAXN];
int nodeCnt;
int ans=INT_MAX;
int main() {
	scanf("%d%d", &n, &k);
    for(int i=1;i<=k;i++) {
        int t;
        scanf("%d", &t);
        for(int j=1;j<=t;j++) {
            int w;
            scanf("%d", &w);
            nodes[++nodeCnt].index=w;
            nodes[nodeCnt].type=i;
        }
    }
    memset(last, 0xAF, sizeof(last));
    sort(nodes+1, nodes+n+1);
    for(int i=1;i<=n;i++) {
        last[nodes[i].type]=nodes[i].index;
        //printf("%d(%d): ", i, nodes[i].index); for(int j=1;j<=k;j++) printf("%d ", last[j]);
        int minv=INT_MAX;
        for(int j=1;j<=k;j++) minv=min(minv, last[j]);
        //printf("\nmin:%d\n", minv);
        //printf("ans:%d\n", nodes[i].index-minv);
        ans=min(ans,nodes[i].index-minv);
    }
    printf("%d\n", ans);
	return 0;
}
