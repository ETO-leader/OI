#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
auto&inf(cin);
auto&ouf(cout);
static constexpr auto maxn=(int)(1e5+7);
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,q;inf>>n>>q;
    vector<int> a(n);
    for(auto&i:a) inf>>i;
    vector<int> cnt(n+7);
    bitset<maxn> v;
    auto mex=[&](int l,int r){
        v.set();
        cir(i,l,r+1) v.reset(a[i]);
        auto res=v._Find_first();
        return res;
    };
    cir(i,0,q){
        int op;inf>>op;
        if(op==1){
            int l,r;inf>>l>>r;--l;--r;
            reverse(a.begin()+l,a.begin()+r+1);
        }else{
            int l,r;inf>>l>>r;--l;--r;
            ouf<<mex(l,r)<<'\n';
        }
    }
    return 0;
}

