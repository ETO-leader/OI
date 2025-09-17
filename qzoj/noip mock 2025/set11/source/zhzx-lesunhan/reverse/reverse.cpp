#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
void init();void Solve();
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	int T=1,id;init();
//	cin>>id>>T;
	while(T--) Solve();
	return 0;
}
void init(){
}
int id,n,k,a[1000005],t[1000005],l=1,cnt,sum,K,a1,a2,a3,a4;
void add(int x,int y){for(;x<=n;x+=(x&-x)) t[x]+=y;}
int query(int x){
	int res=0;
	for(;x;x-=(x&-x)) res+=t[x];
	return res;
}
void Solve(){
	cin>>id>>n>>k;K=k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		sum+=query(n)-query(a[i]);
		add(a[i],1);
	}
	k=sum-k;
	for(int i=1;i<=n;i++) t[i]=0;
	if(k==0){
		cout<<"1\n1 1\n";
		return;
	}
	add(a[1],1);l=1;
	for(int i=1;i<=n;i++){
		while(l<n&&cnt+(query(n)-query(a[l+1]))<=k){
			l++;
			cnt+=(query(n)-query(a[l]));
			add(a[l],1);
		}
		if(cnt==k){
			cout<<1<<endl;
			cout<<i<<' '<<l<<endl;
			return;
		}
		if(l<n){
			if(cnt+query(n)-query(a[l+1])>=k){
				a1=i;a2=l;a3=l-(k-cnt)+1;a4=l+1;
			}
		}
		cnt-=query(a[i]-1);
		add(a[i],-1);
	}
	cout<<"2\n"<<a1<<' '<<a2<<endl<<a3<<' '<<a4<<endl;
//	sort(a+a1,a+a2+1);
//	sort(a+a3,a+a4+1);
//	sum=0;
//	for(int i=1;i<=n;i++){
//		sum+=query(n)-query(a[i]);
//		add(a[i],1);
//	}
//	if(sum==K) cerr<<"YES\n";
//	else cerr<<"NO\n";
}
