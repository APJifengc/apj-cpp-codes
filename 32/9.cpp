#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1000005;
int n,x[MAXN],p[MAXN],c[MAXN],a[MAXN],b[MAXN],f[MAXN];
int q[MAXN],head=1,tail=1;
inline long double slope(int j,int k) { return (long double)(f[k]+b[k]-f[j]-b[j])/(a[k]-a[j]); }
signed main() {
	scanf("%lld", &n);
    for(int i=1;i<=n;i++) scanf("%lld%lld%lld", &x[i], &p[i], &c[i]);
    for(int i=1;i<=n;i++) a[i]=a[i-1]+p[i],b[i]=b[i-1]+x[i]*p[i];
    for(int i=1;i<=n;i++) {
        while(head<tail && slope(q[head], q[head+1]) <= x[i]) head++;
        int j=q[head];f[i]=f[j]+x[i]*(a[i-1]-a[j])-b[i-1]+b[j]+c[i];
        while(head<tail && slope(q[tail-1], i)<=slope(q[tail-1], q[tail])) tail--;
        q[++tail]=i;
    }
    printf("%lld\n", f[n]);
	return 0;
}
