#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
class sparsetable{
private:
    static constexpr auto ups=21;
    vector<vector<int>> a;
    vector<int> lgx;
    auto init(vector<int> x){
        const auto n=(int)(x.size());
        a.resize(ups,vector<int>(n));
        a[0]=x;
        cir(i,1,ups) cir(p,0,n-(1<<i)+1){
            a[i][p]=gcd(a[i-1][p],a[i-1][p+(1<<(i-1))]);
        }
        lgx.resize(n+7);
        cir(i,2,n+7) lgx[i]=lgx[i>>1]+1;
    }
public:
    auto query(int l,int r){
        if(l>r) return 0;
        const auto ql=(int)(lgx[r-l+1]);
        return gcd(a[ql][l],a[ql][r-(1<<ql)+1]);
    }
    sparsetable(vector<int> x){init(x);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        vector<int> a(n),b(n);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        sparsetable sta(a),stb(b);
        vector<pair<int,int>> aw(n);
        vector<int> prea(n),sufa(n),preb(n),sufb(n);
        map<int,int> spa,spb,ssa,ssb,vla,vlb,vra,vrb;
        cir(i,0,n){
            prea[i]=sta.query(0,i-1);
            preb[i]=stb.query(0,i-1);
            sufa[i]=sta.query(i+1,n-1);
            sufb[i]=stb.query(i+1,n-1);
        }
        // Query swapped range [l,r]
        const auto aska=[&](int l,int r){
            return gcd(prea[l],gcd(stb.query(l,r),sufa[r]));
        };
        const auto askb=[&](int l,int r){
            return gcd(preb[l],gcd(sta.query(l,r),sufb[r]));
        };
        ssa[aska(0,n-1)]=ssb[askb(0,n-1)]=n-1;
        for(auto c=-1;auto&i:prea) spa[i]=++c;
        for(auto c=-1;auto&i:preb) spb[i]=++c;
        for(auto c=n;auto&i:views::reverse(sufa)) ssa[i]=--c;
        for(auto c=n;auto&i:views::reverse(sufb)) ssb[i]=--c;
        auto ansmx=0;
        for(auto&[wa,l]:spa) for(auto&[wb,r]:ssa){
            const auto nw=aska(l,r);
            if(!vla.contains(nw)) vla[nw]=-1;
            if(!vra.contains(nw)) vra[nw]=n;
            vla[nw]=max(vla[nw],l);
            vra[nw]=min(vra[nw],r);
        }
        for(auto&[wa,l]:spb) for(auto&[wb,r]:ssb){
            const auto nw=askb(l,r);
            if(!vlb.contains(nw)) vlb[nw]=-1;
            if(!vrb.contains(nw)) vrb[nw]=n;
            vlb[nw]=max(vlb[nw],l);
            vrb[nw]=min(vrb[nw],r);
        }
        for(auto&[wa,ra]:vra) for(auto&[wb,rb]:vrb){
            if(!(wa&&wb)) continue;
            const auto la=vla[wa],lb=vlb[wb];
            // clog<<' '<<wa<<' '<<wb<<' '<<'['<<la<<','<<ra<<"] ["<<lb<<','<<rb<<']'<<'\n';
            const auto rl=min(la,lb),lr=max(ra,rb);
            // clog<<wa<<' '<<wb<<' '<<rl<<' '<<lr<<'\n';
            if((!(aska(rl,lr)%wa))&&(!(askb(rl,lr)%wb))) ansmx=max(ansmx,wa+wb);
        }
        auto cmethod=0ll;
        set<pair<int,int>> cnt;
        auto check=[&](int wa,int wb){
            if(cnt.contains({wa,wb})) return;
            cnt.emplace(wa,wb);
            vector f(n,vector<lint>(3));
            f[0][0]=(!(a[0]%wa))&&(!(b[0]%wb));
            f[0][1]=(!(b[0]%wa))&&(!(a[0]%wb));
            f[0][2]=f[0][1];
            cir(i,1,n){
                f[i][0]=f[i-1][0]*((!(a[i]%wa))&&(!(b[i]%wb)));
                f[i][1]=(f[i-1][1]+f[i-1][0])*((!(b[i]%wa))&&(!(a[i]%wb)));
                f[i][2]=f[i][1]+f[i-1][2]*((!(a[i]%wa))&&(!(b[i]%wb)));
            }
            cmethod+=f[n-1][2];
        };
        for(auto&[wa,ra]:vra) for(auto&[wb,rb]:vrb){
            if((!wa)||(!wb)||wa+wb!=ansmx) continue;
            check(wa,wb);check(wb,wa); 
        }
        println("{} {}",ansmx,cmethod);
    }();
    return 0;
}
