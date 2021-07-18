#include <bits/stdc++.h>
using namespace std;
double a[11000];
vector<int> r[11000];
int n,m;
double p,q;
void dfs(int i, double w, int step) {
	if (step<0) return;
	a[i]+=w*p/q;
	for(int j : r[i]) {
		dfs(j, w*((1.0-p/q)/(double)r[i].size()), step-1);
	}
}
int main() {
	cin >> n >> m >> p >> q;
	for(int i=1;i<=m;i++) {
		int x,y;
		cin >> x >> y;
		r[x].push_back(y);
		r[y].push_back(x);
	}
	dfs(1,1,10);
	for(int i=1;i<=n;i++) {
		printf("%d: %.2lf\n", i, a[i]);
	}
	return 0;
}
