#pragma GCC optimize("Ofast","unroll-loops","inline","no-stack-protector")
#define private public
#include <bitset>
#undef private
#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
inline constexpr auto reverse_u64(uint64_t x){
    x=((x&0x5555555555555555ull)<<1)|((x>>1)&0x5555555555555555ull);
    x=((x&0x3333333333333333ull)<<2)|((x>>2)&0x3333333333333333ull);
    x=((x&0x0f0f0f0f0f0f0f0full)<<4)|((x>>4)&0x0f0f0f0f0f0f0f0full);
    return __builtin_bswap64(x);
}
namespace flash_man{
    static array<char,10000000> buf;
    auto p1 = buf.begin(), p2 = buf.begin();
    #define getchar() p1 == p2 && (p2 = (p1 = buf.begin()) + fread(buf.begin(), 1, 10000000, stdin), p1 == p2) ? EOF : *p1++
    template <typename type>
    inline auto read(type &x) {
        x = 0;
        char c = getchar();
        while (!isdigit(c)) {
            c = getchar();
        }
        while (isdigit(c)) {
            x = (x << 1) + (x << 3) + (c ^ 48);
            c = getchar();
        }
    }
    template <typename..._Args>
    inline auto read(_Args&... args) {
        ((read(args)),...);
    }
    inline auto writeln(const string s){
        for(auto&x:s) putchar_unlocked(x);
        putchar_unlocked('\n');
    }
    #undef getchar
}
static const int maxx=1.5e5+17;
static array<uint64_t,maxx> tmp,utmp;
template<const int maxa>
class calc{
private:
    static constexpr auto w=64;
    static constexpr auto bw=64;
    template<const int maxb>
    class ext_bitset:public bitset<maxb>{
    public:
        using bitset<maxb>::bitset;
        using bitset<maxb>::operator=;
        auto reverse_k(const int k) const{
            const auto upk=(k+bw-1)/bw;
            ext_bitset<maxb> res;res.reset();
            cir(i,0,upk) res._M_w[i]=reverse_u64(this->_M_w[upk-i-1]);
            res>>=(upk*bw-k);
            return res;
        }
        auto and_any(const ext_bitset<maxb>&b) const{
            const auto bn=maxb/bw;
            for(auto i=0;i+4<bn;i+=4){
                if((this->_M_w[i]&b._M_w[i])||
                (this->_M_w[i+1]&b._M_w[i+1])||
                (this->_M_w[i+2]&b._M_w[i+2])||
                (this->_M_w[i+3]&b._M_w[i+3])
                ) return true;
            }
            for(auto i=(bn/4)*4;i<bn;++i) if(this->_M_w[i]&b._M_w[i]) return true;
            return false;
        }
        auto rotate(int up,int v){
            auto bv=v>>6,lv=v&63,rv=64-lv;
            up/=bw;
            if(!lv){
                auto i=0,j=bv;
                for(;j<up;++i,++j) tmp[j]=this->_M_w[i];
                for(j=0;i<up;++i,++j) tmp[j]=this->_M_w[i];
                memcpy(this->_M_w,tmp.data(),sizeof(this->_M_w));
            }else{
                auto i=0,j=bv;
                for(;j<up-1;++i,++j){
                    tmp[j]=this->_M_w[i]<<lv;
                    utmp[j+1]=this->_M_w[i]>>rv;
                }
                tmp[j]=this->_M_w[i]<<lv;
                utmp[0]=this->_M_w[i]>>rv;
                for(++i,j=0;i<up;++i,++j){
                    tmp[j]=this->_M_w[i]<<lv;
                    utmp[j+1]=this->_M_w[i]>>rv;
                }
                for(i=0;i<up;++i){
                    this->_M_w[i]=tmp[i]|utmp[i];
                }
            }
        }
    };
public:
    auto eval(int n,int q,int v,int id){
        vector<int> a(n);
        for(auto&i:a) flash_man::read(i);
        ext_bitset<maxa> bv;bv.reset();
        cir(i,0,v) bv.set(i);
        vector<ext_bitset<maxa>> sg(w<<1);
        const auto bcnt=(n+w-1)/w+1;
        auto ls=[&](const auto u){return u*2;};
        auto rs=[&](const auto u){return u*2+1;};
        auto build=[&](auto __self,int u,int l,int r){
            if(r-l+1<bcnt){
                cir(i,l,r+1) sg[u].set(a[i]);
                return;
            }
            const auto mid=(l+r)/2;
            __self(__self,ls(u),l,mid);
            __self(__self,rs(u),mid+1,r);
            sg[u]=sg[ls(u)];
            sg[u]|=sg[rs(u)];
        };
        build(build,1,0,n-1);
        struct nodetag{
            int cov,add;
            nodetag(int _cov=-1,int _add=0):cov(_cov),add(_add){}
        };
        vector<nodetag> tg(w<<1);
        vector<int> lasop(w<<1,-1);
        auto apply=[&](int u,int l,int r,const nodetag x){
            if(r-l+1>bcnt-1){
                if(x.cov>-1){
                    if(lasop[u]>-1) sg[u].reset(lasop[u]);
                    else sg[u].reset();
                    tg[u].cov=x.cov;tg[u].add=0;
                    sg[u].set(x.cov);
                    if(x.add){
                        sg[u].reset(x.cov);
                        (tg[u].add+=x.add)%=v;
                        sg[u].set((x.cov+x.add)%v);
                    }
                    lasop[u]=(x.cov+x.add)%v;
                }else if(x.add){
                    (tg[u].add+=x.add)%=v;
                    if(lasop[u]<0){
                        sg[u].rotate(v,x.add%v);
                    }else{
                        const auto p=lasop[u];
                        sg[u].reset(p);
                        sg[u].set((p+x.add)%v);
                        (lasop[u]+=x.add)%=v;
                    }
                }
            }else{
                if(x.cov==-1&&(!x.add)) return;
                sg[u].reset();
                if(x.cov>-1) fill(a.begin()+l,a.begin()+r+1,x.cov);
                if(x.add){
                    auto i=l;
                    for(;i+4<r+1;i+=4){
                        a[i]+=x.add;
                        a[i+1]+=x.add;
                        a[i+2]+=x.add;
                        a[i+3]+=x.add;
                        a[i]-=(a[i]>v-1?v:0);
                        a[i+1]-=(a[i+1]>v-1?v:0);
                        a[i+2]-=(a[i+2]>v-1?v:0);
                        a[i+3]-=(a[i+3]>v-1?v:0);
                    }
                    for(;i<r+1;++i) a[i]+=x.add,a[i]-=(a[i]>v-1?v:0);
                    i=l;
                    for(;i+4<r+1;i+=4){
                        sg[u].set(a[i]);
                        sg[u].set(a[i+1]);
                        sg[u].set(a[i+2]);
                        sg[u].set(a[i+3]);
                    }
                    for(;i<r+1;++i) sg[u].set(a[i]);
                }else{
                    sg[u].set(x.cov);
                }
            }
        };
        auto push_down=[&](int u,int l,int r){
            if(tg[u].add>0||tg[u].cov>-1){
                const auto mid=(l+r)/2;
                apply(ls(u),l,mid,tg[u]);
                apply(rs(u),mid+1,r,tg[u]);
            }
            tg[u].cov=-1;tg[u].add=0;
        };
        auto cover=[&](auto __self,int u,int l,int r,int ql,int qr,int x){
            if(r<ql||qr<l) return;
            if(r-l+1<bcnt){
                sg[u].reset();
                const auto rl=max(ql,l),rr=min(qr,r);
                fill(a.begin()+rl,a.begin()+rr+1,x);
                sg[u].set(x);
                auto i=l;
                for(;i+4<rl;i+=4){
                    sg[u].set(a[i]);
                    sg[u].set(a[i+1]);
                    sg[u].set(a[i+2]);
                    sg[u].set(a[i+3]);
                }
                for(;i<rl;++i) sg[u].set(a[i]);
                i=rr+1;
                for(;i+4<r+1;i+=4){
                    sg[u].set(a[i]);
                    sg[u].set(a[i+1]);
                    sg[u].set(a[i+2]);
                    sg[u].set(a[i+3]);
                }
                for(;i<r+1;++i) sg[u].set(a[i]);
                return;
            }
            if(ql-1<l&&r-1<qr) return apply(u,l,r,nodetag(x,0));
            lasop[u]=-1;
            push_down(u,l,r);
            const auto mid=(l+r)/2;
            __self(__self,ls(u),l,mid,ql,qr,x);
            __self(__self,rs(u),mid+1,r,ql,qr,x);
            sg[u]=sg[ls(u)];
            sg[u]|=sg[rs(u)];
        };
        auto add=[&](auto __self,int u,int l,int r,int ql,int qr,int x){
            if(r<ql||qr<l) return;
            if(r-l+1<bcnt){
                const auto rl=max(ql,l),rr=min(qr,r);
                auto i=rl;
                for(;i+4<rr+1;i+=4){
                    a[i]+=x;
                    a[i+1]+=x;
                    a[i+2]+=x;
                    a[i+3]+=x;
                    a[i]-=(a[i]>v-1?v:0);
                    a[i+1]-=(a[i+1]>v-1?v:0);
                    a[i+2]-=(a[i+2]>v-1?v:0);
                    a[i+3]-=(a[i+3]>v-1?v:0);
                }
                for(;i<rr+1;++i) a[i]+=x,a[i]-=(a[i]>v-1?v:0);
                sg[u].reset();
                i=l;
                for(;i+4<r+1;i+=4){
                    sg[u].set(a[i]);
                    sg[u].set(a[i+1]);
                    sg[u].set(a[i+2]);
                    sg[u].set(a[i+3]);
                }
                for(;i<r+1;++i) sg[u].set(a[i]);
                return;
            }
            if(ql-1<l&&r-1<qr) return apply(u,l,r,nodetag(-1,x));
            lasop[u]=-1;
            push_down(u,l,r);
            const auto mid=(l+r)/2;
            __self(__self,ls(u),l,mid,ql,qr,x);
            __self(__self,rs(u),mid+1,r,ql,qr,x);
            sg[u]=sg[ls(u)];
            sg[u]|=sg[rs(u)];
        };
        auto query=[&](auto __self,int u,int l,int r,int ql,int qr,ext_bitset<maxa>&ans){
            if(r-l+1<bcnt){
                const auto rl=max(ql,l),rr=min(qr,r);
                auto i=rl;
                for(;i+4<rr+1;i+=4){
                    ans.set(a[i]);
                    ans.set(a[i+1]);
                    ans.set(a[i+2]);
                    ans.set(a[i+3]);
                }
                for(;i<rr+1;++i) ans.set(a[i]);
                return;
            }
            if(ql-1<l&&r-1<qr) return ans|=sg[u],void();
            push_down(u,l,r);
            const auto mid=(l+r)/2;
            if(qr<mid+1) return __self(__self,ls(u),l,mid,ql,qr,ans);
            if(mid<ql) return __self(__self,rs(u),mid+1,r,ql,qr,ans);
            __self(__self,ls(u),l,mid,ql,qr,ans);
            __self(__self,rs(u),mid+1,r,ql,qr,ans);
        };
        auto s=ext_bitset<maxa>(),ns=ext_bitset<maxa>();
        auto lasans=0;
        cir(i,0,q){
            int op;flash_man::read(op);
            int rl,rr,x;flash_man::read(rl,rr,x);
            const auto l=min(rl^lasans,rr^lasans)-1;
            const auto r=max(rl^lasans,rr^lasans)-1;
            if(op==1){
                cover(cover,1,0,n-1,l,r,x);
            }else if(op==2){
                add(add,1,0,n-1,l,r,x);
            }else if(op==3){
                s.reset();
                query(query,1,0,n-1,l,r,s);
                ns=s;ns<<=x;
                auto ok=s.and_any(ns);
                if(ok) lasans=l+1;
                flash_man::writeln(ok?"Yes":"No");
            }else if(op==4){
                s.reset();
                query(query,1,0,n-1,l,r,s);
                auto ns=s.reverse_k(x+1);
                auto ok=s.and_any(ns);
                if(ok) lasans=l+1;
                flash_man::writeln(ok?"Yes":"No");
            }else{
                s.reset();
                query(query,1,0,n-1,l,r,s);
                auto ok=false;
                for(auto i=1;i*i<x+1;++i) if(!(x%i)){
                    ok|=(s.test(i)&s.test(x/i));
                }
                if(!x) ok|=s.test(0);
                if(ok) lasans=l+1;
                flash_man::writeln(ok?"Yes":"No");
            }
        }
    }
};
int main(){
    int n,q,v,id;flash_man::read(n,q,v,id);
    if(v<(int)(5e4+7)){
        calc<50007>().eval(n,q,v,id);
    }else if(v<(int)(1e5)+7){
        calc<100007>().eval(n,q,v,id);
    }else{
        calc<150007>().eval(n,q,v,id);
    }
    return 0;
}
