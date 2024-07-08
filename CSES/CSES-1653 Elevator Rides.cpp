#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct D_Node{
    int u,w,x;
    void min(D_Node D){
        if(D.u<u||D.u==u&&D.w<w) (*this)=D;
    }
	D_Node operator+(int k) const{
		auto dx=*this;
		if((dx.w+=k)>x) dx.u++,dx.w=k;
		return dx;
	}
};
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x;cin>>n>>x;vector<int> v(n);
	for(auto&i:v) cin>>i;
	const int _sz=1<<n;
	vector<D_Node> D(_sz,{_inf,_inf,x});
	D[0]={0,0,x};
	cir(i,1,_sz){
		cir(j,0,n) if((1<<j)&i){
			D[i].min((D[i-(1<<j)]+v[j]));
		}
	}
	cout<<(D[_sz-1].u+1)<<'\n';
    return 0;
}