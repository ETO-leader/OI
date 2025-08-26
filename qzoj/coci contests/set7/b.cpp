#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty,const _Ty c>
class hashbase{
private:
    vector<_Ty> pre,suf;
    auto init(string s){
        auto h=(_Ty)(0);
        for(auto&x:s) pre.emplace_back((h*=c)+=x);
        h=0;
        for(auto&x:views::reverse(s)) suf.emplace_back((h*=c)+=x);
    }
public:
    auto size(){return pre.size();}
    constexpr auto prec(auto x){return x?pre[x-1]:0;}
    constexpr auto sufc(auto x){return x?suf[x-1]:0;}
    constexpr auto full_val(){return (!pre.empty())?pre.back():0;}
    hashbase(auto x){init(x);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    vector<hashbase<uint64_t,251>> hstr;
    hstr.reserve(n);
    cir(i,0,n){
        string s;cin>>s;
        hstr.emplace_back(s);
    }
    cir(i,0,q){
        string s;cin>>s;
        string pre,suf;
        cir(i,0,(int)(s.size())){
            if(s[i]=='*') break;
            pre+=s[i];
        }
        for(auto i=(int)(s.size())-1;~i;--i){
            if(s[i]=='*') break;
            suf+=s[i];
        }
        const auto pw=hashbase<uint64_t,251>(pre).full_val();
        const auto sw=hashbase<uint64_t,251>(suf).full_val();
        auto cnt=0;
        cir(i,0,n) if(hstr[i].size()+1>pre.size()+suf.size()){
            cnt+=(hstr[i].prec(pre.size())==pw&&hstr[i].sufc(suf.size())==sw);
        }
        cout<<cnt<<'\n';
    }
    return 0;
}
