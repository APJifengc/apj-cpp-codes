#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1000006;
int n,a,b,c,x[MAXN],p[MAXN],f[MAXN];
int q[MAXN],head=1,tail=1;
inline int X(int i) { return p[i]; }
inline int Y(int i) { return f[i]+a*p[i]*p[i]-b*p[i]; }
inline double slope(int i,int j) { return (double)(Y(i)-Y(j))/(double)(X(i)-X(j)); }
signed main() {
	scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
    for(int i=1;i<=n;i++) scanf("%lld", &x[i]);
    for(int i=1;i<=n;i++) p[i]=p[i-1]+x[i];
    for(int i=1;i<=n;i++) {
        while(head<tail && slope(q[head], q[head+1]) >= 2*a*p[i]) head++;
        int j=q[head];f[i]=f[j]+a*pow(p[i]-p[j],2)+b*(p[i]-p[j])+c;
        while(head<tail && slope(q[tail-1], i)>=slope(q[tail-1], q[tail])) tail--;
        q[++tail]=i;
    }
    printf("%lld\n", f[n]);
	return 0;
}
