#include <bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
const int MAXN = 23;
long long f[1<<MAXN];
int a[MAXN];int p,n,m;
int main() {
	scanf("%d%d", &n, &m);
    for(int i=1;i<=m;i++) {
        int x,y;scanf("%d%d", &x, &y);
        a[x]|=(1<<(y-1));
    }
    f[0]=1;
    for(int i=1;i<(1<<n);i++) {
        int num=0;
        for(int j=i;j;j-=lowbit(j)) num++;
        for(int j=i&(~a[num]);j;j-=lowbit(j)) {
            f[i]+=f[i&(~lowbit(j))];
        }   
    }
    printf("%lld\n", f[(1<<n)-1]);
    return 0;
}
