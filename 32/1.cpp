#include <cstdio>
#include <cstring>
#include <deque>
#include <climits>
#include <utility>
using namespace std;
const int MAXN = 500005;
int a[7],f[MAXN],sum1;
typedef pair<int,int> Node;
#define v first
#define index second
deque<Node> q;
int main() {
    int cases=0;
    while(true) {
        scanf("%d%d%d%d%d%d", &a[1], &a[2], &a[3], &a[4], &a[5], &a[6]);
        sum1=0;
        for(int i=1;i<=6;i++) sum1+=a[i]*i;
        if (sum1==0) break;
        if (sum1%2!=0) {
            printf("Collection #%d:\nCan't be divided.\n\n", ++cases);
            continue;
        }
        sum1/=2;
        memset(f, 0, sizeof f);
        for(int i=1;i<=6;i++) {
            if (a[i]==1) {
                for(int j=sum1;j>=i;j--) {
                    f[j]=max(f[j],f[j-i]+i);
                }
            } else if (i*a[i]>=sum1) {
                for(int j=i;j<=sum1;j++) {
                    f[j]=max(f[j],f[j-i]+i);
                }
            } else for(int j=0;j<i;j++) {
                while(!q.empty()) q.pop_front();
                for(int k=j,num=0;k<=sum1;k+=i,num++) {
                    if (!q.empty() && q.front().index<k-a[i]*i) q.pop_front();
                    while(!q.empty() && q.back().v<(f[k]-num*i)) q.pop_back();
                    q.push_back(make_pair(f[k]-i*num, k));
                    f[k]=q.front().v+i*num;
                }
            }
        }
        if (f[sum1]==sum1) printf("Collection #%d:\nCan be divided.\n\n", ++cases);
        else printf("Collection #%d:\nCan't be divided.\n\n", ++cases);
        /*for(int i=1;i<=6;i++) {
          for(int j=0;j<=sum2;j++) {
          printf("f[%d][%d]=%d ", i, j, f[i][j]);
          }
          printf("\n");
          }*/
        continue;
    }
    return 0;
}
