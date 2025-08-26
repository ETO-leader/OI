#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty,const _Ty c>
class hashbase{
private:
    vector<_Ty> pre,suf;
    void init(const string& s){
        _Ty h=0;
        for(char x:s) pre.emplace_back((h*=c)+=x);
        h=0;
        for(string::const_reverse_iterator it=s.rbegin();it!=s.rend();++it) 
            suf.emplace_back((h*=c)+=*it);
    }
public:
    size_t size(){return pre.size();}
    constexpr _Ty prec(size_t x){return x?pre[x-1]:0;}
    constexpr _Ty sufc(size_t x){return x?suf[x-1]:0;}
    constexpr _Ty full_val(){return (!pre.empty())?pre.back():0;}
    hashbase(const string& x){init(x);}
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
        for(int i=(int)(s.size())-1;i>=0;--i){
            if(s[i]=='*') break;
            suf+=s[i];
        }
        hashbase<uint64_t,251> hpre(pre),hsuf(suf);
        const auto pw=hpre.full_val();
        const auto sw=hsuf.full_val();
        int cnt=0;
        cir(i,0,n) if(hstr[i].size()+1>pre.size()+suf.size()){
            cnt+=(hstr[i].prec(pre.size())==pw&&hstr[i].sufc(suf.size())==sw);
        }
        cout<<cnt<<'\n';
    }
    return 0;
}
