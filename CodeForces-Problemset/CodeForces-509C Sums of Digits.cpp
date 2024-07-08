#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
ostream&operator<<(ostream&os,VI&d){
    reverse(d.begin(),d.end());
    for(auto&i:d) os<<i;
    reverse(d.begin(),d.end());
    return os;
}
VI&pull_up(VI&v,int x){
    cir(i,0,v.size()){
        if(x<=9-v[i]){
            v[i]+=x;return v;
        }
        x-=(9-v[i]);v[i]=9;
    }
    while(x>0) v.push_back(min(9,x)),x-=9;
    return v;
}
VI&cut_down(VI&v,int x){
    auto vx=v;int cnx=0;++x;
    for(auto&i:v){
        if(i>=x){++cnx;i-=x;break;}
        ++cnx;x-=i;i=0;
    }
    while(cnx!=v.size()&&v[cnx]==9) ++cnx;
    sort(v.begin(),v.begin()+cnx,greater<int>());
    if(cnx==v.size()) v.push_back(1);
    else v[cnx]++;
    return v;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,lx=0,x;cin>>n;VI v;
    cir(i,0,n){
        cin>>x;
        if(x>lx) cout<<pull_up(v,x-lx)<<'\n';
        else cout<<cut_down(v,lx-x)<<'\n';
        lx=x;
    }
    return 0;
}
