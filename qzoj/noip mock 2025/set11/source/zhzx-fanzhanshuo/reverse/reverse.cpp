#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int id,n,k,a[N],ans;
int tr[N];
void add(int x,int v){
	for(;x<=n;x+=(x&-x)) tr[x]+=v;
	return;
} 
int sum(int x){
	int s=0;
	for(;x;x-=(x&-x)) s+=tr[x];
	return s;
}
signed main(){
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>id>>n>>k;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i){
		add(a[i],1);
		ans+=i-sum(a[i]);
	}
	if(ans==k){
		cout<<0<<'\n';
		return 0;
	}
	for(int i=1;i<=n;++i) tr[i]=0;
	k=ans-k;ans=0;
	int l=1;
	for(int r=1;r<=n;++r){
		add(a[r],1);
		ans+=sum(n)-sum(a[r]);
		while(ans>k){
			add(a[l],-1);
			ans-=sum(a[l]);
			++l;
		}
		if(ans==k){
			cout<<1<<'\n'<<l<<' '<<r<<'\n';
			return 0;
		}
	}
	for(int i=1;i<=n;++i) tr[i]=0;
	ans=0;
	for(int r=1;r<=n;++r){
		add(a[r],1);
		ans+=sum(n)-sum(a[r]);
		if(ans>k){
			add(a[r],-1);
			ans-=sum(n)-sum(a[r]);
			--r;
			cout<<2<<'\n'<<1<<' '<<r<<'\n'<<r+1-(k-ans)<<' '<<r+1<<'\n';
			return 0;
		}
	}
	return 0;
}
