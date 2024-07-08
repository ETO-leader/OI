#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<int>;
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
    int n,q;cin>>n>>q;VI a(n),b(n),cnxi(n);
    bit<lint> bx(n+1),bxc(n+2);
    cir(i,0,n){
        cin>>a[i];++cnxi[b[i]=i-bx(a[i])];
        bx.update(a[i],1);
    }
    lint cnx=0;
    bxc.update(1,accumulate(b.begin(),b.end(),0LL));
    cir(i,0,n) bxc.update(i+2,-n+(cnx+=cnxi[i]));
    cir(i,0,q){
        int op,x;cin>>op>>x;
        if(op==1){
            --x;
            if(a[x]<a[x+1]){
                swap(a[x],a[x+1]);swap(b[x],b[x+1]);
                bxc.update(1,1);
                bxc.update(b[x+1]+2,-1);
                ++b[x+1];
            }else{
                swap(a[x],a[x+1]);swap(b[x],b[x+1]);
                bxc.update(1,-1);--b[x];
                bxc.update(b[x]+2,1);
            }
        }else{
            if(x>n-1) cout<<0<<'\n';
            else cout<<bxc(x+1)<<'\n';
        }
    }
    return 0;
}
