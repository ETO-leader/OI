#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,fu=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fu=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*fu;
}
void write(int x){
	if(x<0)	x=-x,putchar('-');
	if(x<10){putchar(x+'0');return;}
	write(x/10);putchar(x%10+'0');
}
const int N=1e5+10;
char s[N],t[N];
int n,m;
namespace case1{
	static bool f[3][20010];
	void solve(){
		for(int i=0;i<3;i++)
			for(int j=0;j<=m;j++)
				f[i][j]=0;
		f[0][0]=1;
		for(int i=0;i<=n;i++)
			for(int j=1;j<=m;j++){
				int op=(i%3);
				if(i>=1&&f[(op+2)%3][j-1]&&s[i]==t[j])	f[op][j]=true;
				else if(j>=2&&f[op][j-2]&&t[j]==t[j-1])	f[op][j]=true;
				else f[op][j]=false;
			}
		if(f[n%3][m])	puts("YES");
		else	puts("NO");
	}
}
namespace case2{
	static bool f[25][100010];
	void solve(){
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++)
				f[i][j]=0;
		f[0][0]=1;
		for(int i=0;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(i>=1&&f[i-1][j-1]&&s[i]==t[j])	f[i][j]=true;
				if(j>=2&&f[i][j-2]&&t[j]==t[j-1])	f[i][j]=true;
			}
		if(f[n%3][m])	puts("YES");
		else	puts("NO");
	}
}
namespace case3{
	void solve(){
		bool suc=true;
		int res=0;
		for(int i=1;i<=m;i++){
			if(t[i]!=s[1]){
				if(i==m||t[i+1]!=t[i]){
					suc=false;
					break;
				}
				res+=2,i++;
			}
		}
//		cout<<m<<" "<<res<<" "<<n<<endl;
		if(suc&&m-res>=n&&!((m-res-n)&1))	puts("YES");
		else	puts("NO");
	}
}
namespace case4{
	static int f[100010][15];
	void solve(){
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m-n;j++)
				f[i][j]=0;
		f[0][0]=1;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m-n;j++){
				if(i>=1&&f[i-1][j]&&s[i]==t[i+j])	f[i][j]=true;
				if(j>=2&&f[i][j-2]&&t[i+j]==t[i+j-1])	f[i][j]=true;
//				if(f[i][j])	cout<<i<<" "<<j<<endl;
			}
		if(f[n][m-n])	puts("YES");
		else	puts("NO"); 
	}
}
signed main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int T=read(),id=read();
	while(T--){
		scanf("%s",s+1);
		scanf("%s",t+1);
		n=strlen(s+1),m=strlen(t+1);
		if(n>m){
			puts("NO");
			continue;
		}
		else if(id<=4)	case1::solve();
		else if(id==5)	case2::solve();
		else if(id==6)	case3::solve();
		else if(id==7)	case4::solve();
	}
	return 0;
}
