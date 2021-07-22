#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
int n,q,a[MAXN];
int stMax[MAXN][16],stMin[MAXN][16],Log[MAXN];
void init() {
    Log[1]=0;
    for(int i=2;i<=n;i++) Log[i]=Log[i/2]+1;
    memset(stMin, 0x7F, sizeof stMin);
    for(int i=1;i<=n;i++) stMax[i][0]=stMin[i][0]=a[i];
    for(int j=1;j<=Log[n];j++) {
        for(int i=1;i<=n && (i+(1<<j)-1)<=n;i++) {
            stMax[i][j]=max(stMax[i][j-1], stMax[i+(1<<(j-1))][j-1]);
            stMin[i][j]=min(stMin[i][j-1], stMin[i+(1<<(j-1))][j-1]);
        }
    }
}
int RMQ(int l,int r) {
    int len = Log[r-l+1];
    return max(stMax[l][len], stMax[r-(1<<len)+1][len])-
        min(stMin[l][len], stMin[r-(1<<len)+1][len]);
}
int main() {
    scanf("%d%d", &n, &q);	
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    init();
    int l,r;
    while(scanf("%d%d", &l, &r) != EOF) {
        printf("%d\n", RMQ(l,r));
    }
    return 0;
}
