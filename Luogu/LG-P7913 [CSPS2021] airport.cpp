#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct airp{
	int t,tag,id;
	inline bool operator<(const airp&ar){
		return t<ar.t;
	}
};
vector<int> getarr(int n,vector<airp> x){
	priority_queue<int,vector<int>,greater<int>> pq;
	unordered_map<int,int> which;
	vector<int> ret(n+1);
	cir(i,0,n) pq.push(i+1);
	for(auto&i:x){
		if(i.tag<0){
			if(which.count(i.id)) pq.push(which[i.id]);
			continue;
		}
		if(pq.empty()) continue;
		which[i.id]=pq.top();ret[pq.top()]++;
		pq.pop();
	}
	cir(i,1,n+1) ret[i]+=ret[i-1];
	return ret;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m1,m2;cin>>n>>m1>>m2;
    vector<airp> tag1(m1*2),tag2(m2*2);
    cir(i,0,m1){
    	int arr,lef;cin>>arr>>lef;
    	tag1[i*2]={arr,1,i};tag1[i*2+1]={lef,-1,i};
    }
    cir(i,0,m2){
    	int arr,lef;cin>>arr>>lef;
    	tag2[i*2]={arr,1,i};tag2[i*2+1]={lef,-1,i};
    }
    sort(tag1.begin(),tag1.end());
    sort(tag2.begin(),tag2.end());
    auto r1=getarr(n,tag1),r2=getarr(n,tag2);
    int ans=0;
    cir(i,0,n+1) ans=max(ans,r1[i]+r2[n-i]);
    cout<<ans<<endl;
    return 0;
}