#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
typedef __int128_t __int;
inline __int __lcm(const __int&a,const __int&b){
    return a/__gcd(a,b)*b;
}
ostream&operator<<(ostream&out,const __int&ot){
    if(ot>9) out<<(ot/10);
    return (out<<(int)(ot%10));
}
struct frac{
    __int up,dw;
    frac(__int a=0,__int b=1){up=a;dw=b;}
    frac& operator/=(const int&t){
        dw*=t;auto g=__gcd(up,dw);
        up/=g;dw/=g;
        return *this;
    }
    frac& operator+=(const frac&f){
        up=up*f.dw+f.up*dw;dw=dw*f.dw;
    	return this->operator/=(1);
    }
};
vector<frac> node;
vector<vector<int>> G;
vector<int> tops;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;tops.resize(n+1);
    G.resize(n+1);node.resize(n+1);
    cir(i,1,n+1){
    	int k,c;cin>>k;
    	cir(j,0,k) cin>>c,G[i].push_back(c),tops[c]++;
    }
    queue<int> q;
    cir(i,1,m+1) q.push(i),node[i].up=1;
    while(!q.empty()){
    	int f=q.front();q.pop();
    	if(!G[f].empty()) node[f]/=G[f].size();
    	for(auto&i:G[f]){
    		node[i]+=node[f];
    		if(!(--tops[i])) q.push(i);
    	}
    }
    cir(i,1,n+1) if(G[i].empty()) cout<<node[i].up<<' '<<node[i].dw<<endl;
    return 0;
}