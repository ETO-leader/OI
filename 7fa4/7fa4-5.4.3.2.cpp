#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
VI arr(88);
vector<unordered_map<int,lint>> D;
lint dfs(int p,int s,const lint k,
    int chp,bool lm=true){
    if(!(~p)) return max<lint>(s,0);
    if((!lm)&&D[p].count(s)) return D[p][s];
    lint&d=(lm?*(new lint(0)):D[p][s]);
    int mx=lm?arr[p]+1:k;
    cir(i,0,mx){
        d+=dfs(p-1,s+(chp?(p<chp?-i:i)
            :p*i),k,chp,lm&&i==(mx-1));
    }
    return d;
}
int initarr(lint x,const int k){
    int len=0;
    while(x){
        arr[len]=x%k;x/=k;++len;
    }
    return len;
}
lint runans(lint x,const int k){
    fill(arr.begin(),arr.end(),0);
    const int siz=initarr(x,k);
    lint res=0;
    cir(i,0,siz){
        D.clear();D.resize(88);
        res+=((!i)?1:-1)*dfs(siz,0,k,i);
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint lx,rx,k;cin>>lx>>rx>>k;
    cout<<runans(rx,k)-runans(lx-1,k)<<'\n';
    return 0;
}
