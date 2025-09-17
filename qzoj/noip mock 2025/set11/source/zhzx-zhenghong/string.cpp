#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+5;
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void write(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
int T,id;
string s;int n;
string t;int m;
bool f[N][N];
signed main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout); 
	T=read(),id=read();
	if(id==6){
		while(T--){
			cin>>s>>t;
			int p=t.size()-s.size();
			if(p%2==0)cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
		return 0;
	}else if(id<=3){
		while(T--){
			memset(f,0,sizeof f);
			f[0][0]=1;
			cin>>s>>t;
			n=s.size();s=" "+s;
			m=t.size();t=" "+t;
			for(int i=0;i<=n;i++){
				for(int j=1;j<=m;j++){
					if(i>=1 && s[i]==t[j])f[i][j]|=f[i-1][j-1];
					if(j>=2 && t[j]==t[j-1])f[i][j]|=f[i][j-2];
				}
			}
			if(f[n][m]==1)cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
		return 0;
	}
	while(T--){
		cin>>s>>t;s+="$",t+="$";
		n=s.size();s=" "+s;
		m=t.size();t=" "+t;
		int i=1,j=1,flg=1;
		while(i<=n && j<=m){
			while(s[i]!=t[j]){
				if(j>=m || t[j]!=t[j+1]){flg=0;break;}
				j+=2;
			}
			if(flg==0)break;
			if(s[i]==t[j])i++,j++;
		}
		if(i!=n+1)flg=0;if(j!=m+1)flg=0;
		if(flg==0)cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;
}
