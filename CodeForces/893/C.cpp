#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
unordered_set<int> s;
vector<int> isp,expr;
void init(int x){
    isp.resize(x,true);
    isp[0]=false;isp[1]=true;
    expr.push_back(1);
    cir(i,2,x){
        if(!isp[i]) continue;
        expr.push_back(i);
        for(auto j=1LL*i*i;j<x;j+=i)
            isp[j]=false;
    }
}
void dfsp(int x,int lp,int n){
    if(s.count(x)) return;
    cout<<x<<' ';
    s.insert(x);
    cir(i,1,lp+1){
        if(1LL*x*expr[i]>n) break;
        dfsp(x*expr[i],i,n);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;init(100007);
    while(T--){
        int n;cin>>n;s.clear();
        cir(i,0,expr.size()){
            if(expr[i]>n) break;
            dfsp(expr[i],i,n);
        }
        cout<<'\n';
    }
    return 0;
}
