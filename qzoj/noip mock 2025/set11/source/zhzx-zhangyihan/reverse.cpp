/*
 * @Author: jianhe
 * @Date: 2025-09-13 10:01:35
 * @LastEditTime: 2025-09-13 11:44:07
 */
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(x) (x&-x)
const ll N=1e6+10;
ll c,n,k,a[N],b[N],q[N],t[N],p,rl,rr,rl1,rr1,ct;vector<pair<ll,ll> > ans;
void add(ll x,ll k){while(x<=n) t[x]++,x+=lowbit(x);}
ll qry(ll x){ll ct=0;while(x) ct+=t[x],x-=lowbit(x);return ct;}
void solve(int x,int y,int z,int w){
	for(int i=1;i<=n;i++) b[i]=a[i];
	sort(b+x,b+y+1);sort(b+z,b+w+1);
	ll ct=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(b[i]>b[j]) ct++;
    if(ct==k){cout<<"2\n"<<x<<" "<<y<<"\n"<<z<<" "<<w;exit(0);}
}
void solve1(int x,int y){
	for(int i=1;i<=n;i++) b[i]=a[i];
	sort(b+x,b+y+1);
	ll ct=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(b[i]>b[j]) ct++;
    if(ct==k){cout<<"1\n"<<x<<" "<<y;exit(0);}
}
void bl(){
    if(n>10000) return;
    for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
            solve1(i,j);
    if(n>12) return;
    for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			for(int p=i;p<=n;p++)
				for(int q=p;q<=n;q++) 
					solve(i,j,p,q);
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    freopen("reverse.in","r",stdin);
    freopen("reverse.out","w",stdout);
    cin>>c>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];bl();
    for(int i=n;i;i--) q[i]=q[i+1]+qry(a[i]-1),add(a[i],1);
    k=q[1]-k;for(int i=1;i<=n;i++) t[i]=0;
    for(int i=1,j=1;i<=n;i++){
        while(j<=n&&ct+j-i-qry(a[j])<=k) ct+=j-i-qry(a[j]),add(a[j],1),j++;
        if(ct>p&&ct<=k) p=ct,rl=i,rr=j-1;
        ct-=qry(a[i]-1),add(a[i],-1);
    }
    if(k) k-=p,ans.push_back({rl,rr}),p=0;
    for(int i=1,j=1;i<=n;i++){
        while(j<=n&&ct+j-i-qry(a[j])<=k) ct+=j-i-qry(a[j]),add(a[j],1),j++;
        if(ct>p&&ct<=k) p=ct,rl=i,rr=j-1;
        ct-=qry(a[i]-1),add(a[i],-1);
    }
    if(k) k-=p,ans.push_back({rl,rr}),p=0;
    // if(k) ans.push_back({rl1,rr1});
    cout<<ans.size()<<"\n";for(auto x:ans) cout<<x.first<<" "<<x.second<<"\n";
    return 0;
}