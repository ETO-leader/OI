// dp i j = dp i-1 i k(j~k)ok
// dp i j |= dp i-1 j-1 (if si==tj)
// dp i j |= dp i j-3-kn
// 表示现在到s的第i位置匹配到了t的k位
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define reg register
#define rint reg int
#define fastio ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
const int N=4e4+5;
int n,m;string s,t;
bitset<N> dp[N];
int C=0;
void VBF(){
	for(int i=0;i<=n;i++)dp[i].reset();
	dp[0][0] = 1;
	for(rint i=2;i<=m;i+=2){
		if(t[i-1]!=t[i-2])break;
		dp[0][i]=1;
	}
	for(rint i=1;i<=n;i++){
		for(rint j=1;j<=m;j++){
			for(rint k=j-2;k>=0;k-=2){
				if(t[k]!=t[k+1])break;  // 不合法的数据
				dp[i][j] = dp[i][j]|dp[i][k];
			}
			if(s[i-1]==t[j-1]) dp[i][j] = dp[i][j]|dp[i-1][j-1];
		}
	}
	if(dp[n][m])puts("YES");
	else puts("NO");
	return;
}
void work(){
	cin>>s>>t;n=s.size(),m=t.size();
	if(n>m||(m-n)%2!=0){puts("NO");return;}
	VBF();
	return;
}
signed main(){
	fastio;
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int T,_;cin>>T>>_;while(T--)work();
	return 0;
}
