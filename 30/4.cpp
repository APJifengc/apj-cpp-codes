#include <bitset>
#include <stdio.h>
using namespace std;
const int MAXN = 35;
bitset<MAXN> a[MAXN];
int k,n;
int src[MAXN], dest[MAXN];
int cnt;
int main() {
    scanf("%d", &k);
    while(k--) {
        for(int i=1;i<MAXN;i++) a[i].reset();
        cnt=0;
        scanf("%d", &n);
        for(int i=1;i<=n;i++) scanf("%d", &src[i]);
        for(int i=1;i<=n;i++) scanf("%d", &dest[i]);
        for(int i=1;i<=n;i++) {
            a[i].set(i);
            a[i].set(0, src[i]^dest[i]);
        }
        int x,y;
        scanf("%d%d", &x, &y);
        while (x!=0||y!=0) {
            a[y].set(x);
            scanf("%d%d", &x, &y);
        }
        int i=1,cur=1;
        for(;i<=n&cur<=n;i++,cur++) {
            for(int j=i+1;j<=n;j++) if (a[j].test(cur)) swap(a[j],a[i]);
            if (!a[i].test(cur)) {
                cnt++;
                i--;
            } else {
                for(int j=1;j<=n;j++) 
                    if (j!=i && a[j].test(cur)) a[j]^=a[i];
            }
        }
        for(int k=i;k<=n;k++) {
            if (a[k].test(0)) {
                printf("Oh,it's impossible~!!\n");
                goto next; 
            }
        }
        printf("%d\n", (1<<(n-i+1)));
next:
        continue;
    }
    return 0;
}
