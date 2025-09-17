#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3005;
int T,id,n,m;
bool f[maxn][maxn];
string s,t;
int read(){
	char ch=getchar();int ret=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
	return ret*f;
}
void solve6(){while(T--){cin>>s>>t;int p=t.size()-s.size();if(p%2==0)cout<<"YES"<<endl;else cout<<"NO"<<endl;}}
void solve123(){while(T--){memset(f,0,sizeof f);f[0][0]=1;cin>>s>>t;n=s.size();s=" "+s;m=t.size();t=" "+t;for(int i=0;i<=n;i++){for(int j=1;j<=m;j++){if(i>=1 && s[i]==t[j])f[i][j]|=f[i-1][j-1];if(j>=2 && t[j]==t[j-1])f[i][j]|=f[i][j-2];}}if(f[n][m]==1)cout<<"YES"<<endl;else cout<<"NO"<<endl;}}
void solveccf(){while(T--){cin>>s>>t;s+="$",t+="$";n=s.size();s=" "+s;m=t.size();t=" "+t;int i=1,j=1,flg=1;while(i<=n && j<=m){while(s[i]!=t[j]){if(j>=m || t[j]!=t[j+1]){flg=0;break;}j+=2;}if(flg==0)break;if(s[i]==t[j])i++,j++;}if(i!=n+1)flg=0;if(j!=m+1)flg=0;if(flg==0)cout<<"NO"<<endl;else cout<<"YES"<<endl;}}
signed main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout); 
	T=read(),id=read();
	if(id==6){
		solve6();
		return 0;
	}else if(id<=3){
		solve123();
		return 0;
	}
	solveccf();
	return 0;
}
