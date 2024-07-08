#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T>
class bit{
private:
    vector<T> v;
    int lowbit(int x){return x&(-x);}
public:
    void update(int x,T w){
        for(;x<v.size();x+=lowbit(x))
            v[x]+=w;
    }
    T operator()(int x){
        T res=0;
        for(;x;x-=lowbit(x)) res+=v[x];
        return res;
    }
    bit(int _x):v(_x){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> v(n);
    for(auto&i:v) cin>>i;
    reverse(v.begin(),v.end());
    lint cnx=0;
    bit<int> b(n+1);
    for(auto&i:v){
        cnx+=b(i);b.update(i,1);
    }
    cout<<1LL*n*(n-1)/2-cnx<<'\n';
    return 0;
}
