#include <bits/stdc++.h>
#define lowbit(a) (a&(-a))
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
using namespace std;
int Time=clock();
bool mst;
const int N=1000005;
int d[N],id,n,tr[N],l,r;
ll cnt,K,mx;
void update(int a,int b){
	for(int i=a;i<=n;i+=lowbit(i))
		tr[i]+=b;
}
int query(int a){
	int ans=0;
	for(int i=a;i>0;i-=lowbit(i))
		ans+=tr[i];
	return ans;
}
void solve(){
	memset(tr,0,sizeof(tr));
	mx=0;
	ll tcnt=0;
	for(int i=1,j=1;i<=n;i++){
		tcnt+=query(n)-query(d[i]);
		update(d[i],1);
		while(tcnt>K){
			tcnt-=query(d[j]-1);
			update(d[j],-1);
			j++;
		}
		if(tcnt>mx)  mx=tcnt,l=j,r=i;
	}
}
bool med;
int main(){
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>id>>n>>K;
	for(int i=1;i<=n;i++)
		cin>>d[i];
	for(int i=1;i<=n;i++){
		cnt+=query(n)-query(d[i]);
		update(d[i],1);
	}
	K=cnt-K;
	if(K==0){
		cout<<"0";
		return 0;
	}
	solve();
	K-=mx;
	if(K==0)
		cout<<"1\n"<<l<<' '<<r;
	else{
		cout<<"2\n"<<l<<' '<<r<<'\n';
		sort(d+l,d+1+r);
		solve();
		cout<<l<<' '<<r;
	}
	// #ifndef ONLINE_JUDGE
	// cerr<<"Time:"<<fixed<<setprecision(5)<<1.0*(clock()-Time)/CLOCKS_PER_SEC<<"s"<<endl;
	// cerr<<"Memory:"<<fixed<<setprecision(5)<<1.0*(&med-&mst)/1024/1024<<"MB";
	// #endif
	return 0;
}