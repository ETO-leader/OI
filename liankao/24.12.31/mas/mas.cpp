#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("mas.in");
ofstream ouf("mas.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using ulint=unsigned long long;
class hashstr{
private:
    static constexpr auto hc=251ull;
    vector<ulint> h,pw;
    auto init(string s){
        for(auto hx=0ll;auto&c:s) h.emplace_back((hx*=hc)+=c);
        s+='\0';
        for(auto w=1ll;auto&c:s) pw.emplace_back(w),w*=hc;
    }
public:
    auto substr(int l,int r){
        return h[r]-(l?h[l-1]:0)*pw[r-l+1];
    }
    hashstr(string s){init(s);}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;
    string s;inf>>s;
    int q;inf>>q;
    const auto spc=count(s.begin(),s.end(),'a')==n;
    cir(i,0,q) [&]{
        int l,r,k;inf>>l>>r>>k;--l;--r;
        if(spc) return ouf<<(ulint)(r-l+1)*k-1<<'\n',void();
        const auto sx=s.substr(l,r-l+1)+s.substr(l,r-l+1);
        hashstr hx(sx);
        unordered_set<ulint> cnt;
        cir(len,1,(int)(sx.size())+1) cir(p,0,(r-l+1)){
            if(p+len-1<r-l+1||p+len>(int)(sx.size())) continue;
            cnt.emplace(hx.substr(p,p+len-1));
        }
        if(k>2){
            const auto nsx=sx+s.substr(l,r-l+1);
            hashstr nhx(nsx);
            unordered_set<ulint> ncnt;
            cir(len,1,(int)(nsx.size())+1) cir(p,0,(r-l+1)){
                if(p+len-1<r-l+1||p+len-1<(int)(sx.size())||p+len>(int)(nsx.size())) continue;
                if(!cnt.count(nhx.substr(p,p+len-1))) ncnt.emplace(nhx.substr(p,p+len-1));
            }
            // clog<<"NSIZ: "<<ncnt.size()<<'\n';
            ouf<<cnt.size()+ncnt.size()*(k-2)<<'\n';
        }else{
            ouf<<cnt.size()<<'\n';
        }
    }();
    return 0;
}
