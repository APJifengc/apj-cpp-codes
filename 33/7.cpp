#include <bits/stdc++.h>
#define ui unsigned int
#define lowbit(a) (a&(-a))
using namespace std;
ui n,m,k,maxn=0,maxm=0;
const ui P = 2147483648LL;
const ui MAXN = 300005;
struct BIT {
	ui a[MAXN];
	inline void add(ui i,ui d) {
		if (i==0) return;
		while(i<MAXN) {
			a[i]+=d;
			i+=lowbit(i);
		}
	}
	inline ui query(ui i) {
		if (i==0) return 0;
		ui res=0;
		while(i) {
			res+=a[i];
			i-=lowbit(i);
		}
		return res;
	}
	inline ui queryArea(ui i,ui j) {
		return query(j)-query(i-1);
	}
	BIT(){
		memset(a,0,sizeof(a));
	}
}bit;
ui x[MAXN],y[MAXN],xDis[MAXN],yDis[MAXN],w,xCnt,yCnt,xSize[MAXN],ySize[MAXN];	
BIT xBIT, yBIT;
bool xB[MAXN],yB[MAXN];
ui c[MAXN][15];
bool cmpY(const pair<int,int> &a, const pair<int,int> &b) {
	return (a.second==b.second?(a.first<b.first):(a.second<b.second));	
}
pair<int,int> trees[MAXN];
inline ui C(ui a,ui b) {
	return c[a][b]; 
}
ui d[MAXN],dd[MAXN];
int main() {
	scanf("%u%u", &n, &m);
	n++,m++;
	scanf("%u", &w);
	for(int i=1;i<=w;i++) {
		scanf("%u%u", &x[i], &y[i]);
		x[i]++,y[i]++;
		xDis[i]=x[i],yDis[i]=y[i];
	}
	scanf("%u", &k);
	c[1][0]=c[1][1]=1;
	for(int i=2;i<MAXN;i++) {
		for(int j=0;j<=min(14,i);j++) {
			if (j==0) c[i][j]=1;
			else if (i==j) c[i][j]=1;
			else c[i][j]=c[i-1][j]+c[i-1][j-1];
		}
	}
	sort(xDis+1, xDis+w+1);
	sort(yDis+1, yDis+w+1);
	xCnt = unique(xDis+1, xDis+w+1)-xDis-1;
	yCnt = unique(yDis+1, yDis+w+1)-yDis-1;
	n=maxn=xCnt;
	m=maxm=yCnt;
	for(int i=1;i<=w;i++) {
		x[i]=lower_bound(xDis+1,xDis+1+xCnt,x[i])-xDis;
		ySize[x[i]]++;
	}
	for(int i=1;i<=w;i++) {
		y[i]=lower_bound(yDis+1,yDis+1+yCnt,y[i])-yDis;
		xSize[y[i]]++;
	}
	for(int i=1;i<=w;i++) trees[i]=make_pair(x[i],y[i]);
	sort(trees+1,trees+1+w,cmpY);
	for(int i=1;i<=w;i++) x[i]=trees[i].first, y[i]=trees[i].second;
	ui l=0;
	ui ans=0;
	for(int i=1;i<=w;i++) {
		d[x[i]]++;
		ui newDd=C(d[x[i]],k)*C(ySize[x[i]]-d[x[i]],k);
		bit.add(x[i],newDd-dd[x[i]]);
		if (y[i]==y[i-1]) {
			ans+=C(l,k)*C(xSize[y[i]]-l,k)*bit.queryArea(x[i-1]+1,x[i]-1);
			l++;
		} else {
			l=1;
		}
		dd[x[i]]=newDd;
	}
	printf("%u\n", ans%P);
	return 0;
}
