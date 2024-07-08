#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
vector<int> v;
void dfs(int x,int mx,int n,vector<int>&vx){
	if(x==mx){vx.push_back(n);return;}
	dfs(x+1,mx,n+v[x],vx);
	dfs(x+1,mx,n,vx);
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n;cin>>n;v.resize(n);
	for(auto&i:v) cin>>i;
	vector<int> v1,v2;
	dfs(0,n/2,0,v1);dfs(n/2,n,0,v2);
	sort(v1.begin(),v1.end());
	sort(v2.begin(),v2.end());
	db ans=0;
	const int sz1=v1.size(),sz2=v2.size();
	const db Al=accumulate(v.begin(),v.end(),0);
	auto calc=[&](db x){return (db)(Al-x)*x/2;};
    auto to_calc=[&](db x){return calc(x*2);};
    int j=sz2-1;
	cir(i,0,sz1){
		while(j&&calc(v1[i]+v2[j])<=calc(v1[i]+v2[j-1])) --j;
		ans=max(ans,calc(v1[i]+v2[j]));
	}
    j=sz1-1;
	cir(i,0,sz2){
		while(j&&to_calc(v2[i]+v1[j])<=to_calc(v2[i]+v1[j-1])) --j;
		ans=max(ans,to_calc(v1[j]+v2[i]));
	}
	cout<<fixed<<setprecision(1)<<ans<<endl;
	return 0;
}