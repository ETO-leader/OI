#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define outans(str) {cout<<str;continue;}
using namespace std;
template<typename T>
class sparsetable{
private:
    vector<vector<T>> st;
    int ht;
    void init(const vector<T>&v){
        int n=v.size();ht=log2(n)+2;
        st.assign(n,vector<T>(ht));
        cir(i,0,n) st[i][0]=v[i];
        cir(j,1,ht) cir(i,0,(n-(1<<(j-1))))
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
public:
    T operator()(int l,int r) const{
        int lg=log2(r-l+1);
        if(l>r) return -1;
        return max(st[l][lg],st[r-(1<<lg)+1][lg]);
    }
    sparsetable(const vector<T>&v){init(v);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n;map<int,tuple<int,int,int>> y;
    vector<int> v(n);
    cir(i,0,n){
        int yi;cin>>yi>>v[i];
        y[yi]={i,v[i],yi};
    }
    y[(int)(1e9+7)]={n,0,(int)(1e9+7)};
    sparsetable<int> st(v);cin>>m;
    cir(i,0,m){
        int l,r;cin>>l>>r;
        auto lb=y.lower_bound(l),rb=y.lower_bound(r);
        auto [il,wl,yl]=(lb->second);
        auto [ir,wr,yr]=(rb->second);
        if(yl==l&&yr==r){
            auto w=st(il+1,ir-1);
            if(wl<wr) outans("false\n");
            if(w>=wr) outans("false\n");
            outans((ir-il==r-l?"true\n":"maybe\n"));
        }
        if(yr==r){
            auto w=st(il,ir-1);
            if(w>=wr) outans("false\n");
            outans("maybe\n");
        }
        if(yl==l){
            auto w=st(il+1,ir-1);
            if(w>=wl) outans("false\n");
            outans("maybe\n");
        }
        outans("maybe\n");
    }
    return 0;
}