#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
using namespace std;
int Time=clock();
bool mst;
int T,id,n,m;
const int N=100005;
char s1[N],s2[N],s[N];
bool med;
int main(){
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T>>id;
	while(T--){
		cin>>s1+1>>s2+1;
		n=strlen(s1+1),m=strlen(s2+1);
		int len=0;
		for(int i=1;i<=m;i++)
			if(s2[i]==s2[i+1])  i++;
			else  s[++len]=s2[i];
		m=len;
		for(int i=1;i<=m;i++)
			s2[i]=s[i];
		int p1=1,p2=1;
		bool flag=1;
		while(p1<=n||p2<=m){
			if(s1[p1]==s2[p2])  p1++,p2++;
			else{
				if(p1<n&&s1[p1]==s1[p1+1])  p1+=2;
				else{
					flag=0;
					break;
				}
			}
		}
		cout<<(flag?"YES\n":"NO\n");
	}
	// #ifndef ONLINE_JUDGE
	// cerr<<"Time:"<<fixed<<setprecision(5)<<1.0*(clock()-Time)/CLOCKS_PER_SEC<<"s"<<endl;
	// cerr<<"Memory:"<<fixed<<setprecision(5)<<1.0*(&med-&mst)/1024/1024<<"MB";
	// #endif
	return 0;
}