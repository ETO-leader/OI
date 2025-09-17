#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    int q;cin>>q;
    const auto n=(int)(s.size());
    vector<tuple<int,int,int>> qry(q);
    auto c=-1;
    for(auto&[l,r,id]:qry) cin>>l>>r,id=++c,--l,--r;
    const auto sqr=(int)(n/sqrt(q+1)+1);
    sort(qry.begin(),qry.end(),[&](auto&a,auto&b){
        return get<0>(a)/sqr==get<0>(b)/sqr?get<1>(a)<get<1>(b):get<0>(a)<get<0>(b);
    });
    auto c_g=0ll,c_c=0ll,c_d=0ll,
         c_gc=0ll,c_cd=0ll,
         c_gcd=0ll;
    auto emplace_l=[&](int p){
        if(s[p]=='g'){
            ++c_g;
            c_gc+=c_c;
            c_gcd+=c_cd;
        }else if(s[p]=='c'){
            ++c_c;
            c_cd+=c_d;
        }else if(s[p]=='d'){
            ++c_d;
        }
    };
    auto emplace_r=[&](int p){
        if(s[p]=='g'){
            ++c_g;
        }else if(s[p]=='c'){
            ++c_c;
            c_gc+=c_g;
        }else if(s[p]=='d'){
            ++c_d;
            c_cd+=c_c;
            c_gcd+=c_gc;
        }
    };
    auto remove_l=[&](int p){
        if(s[p]=='g'){
            --c_g;
            c_gc-=c_c;
            c_gcd-=c_cd;
        }else if(s[p]=='c'){
            --c_c;
            c_cd-=c_d;
        }else if(s[p]=='d'){
            --c_d;
        }
    };
    auto remove_r=[&](int p){
        if(s[p]=='g'){
            --c_g;
        }else if(s[p]=='c'){
            --c_c;
            c_gc-=c_g;
        }else if(s[p]=='d'){
            --c_d;
            c_cd-=c_c;
            c_gcd-=c_gc;
        }
    };
    vector<int64_t> ans(q);
    auto l=0,r=-1;
    for(auto&[ql,qr,id]:qry){
        while(r<qr) emplace_r(++r);
        while(ql<l) emplace_l(--l);
        while(r>qr) remove_r(r--);
        while(ql>l) remove_l(l++);
        ans[id]=c_gcd;
    }
    for(auto&x:ans) cout<<(x&((1u<<31)-1))<<'\n';
    return 0;
}
