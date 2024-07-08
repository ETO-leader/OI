#include"cache_ro.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class NoAlgorithm{
private:
    int w;uint32_t las,info;
    bool st;
public:
    auto query(uint32_t si,uint32_t ad){
        assert(w==1);
        if((!st)&&las==si) return info;
        st=false;las=si;
        return info=memory_read(si+ad);
    }
    NoAlgorithm(int _w):w(_w),las(0),st(true),info(0){}
};
class RandomAlgorithm{
private:
    class random_device_gen{
    private:
        uint64_t nxt;
        uint32_t randgen(){
            nxt=nxt*1103515245+12345;
            return (uint32_t)(nxt/65536)%32768;
        }
    public:
        auto operator()(){
            return randgen();
        }
        random_device_gen(uint64_t val=1):nxt(val){}
    };
    random_device_gen rnd;
    vector<bool> statu;
    vector<uint32_t> mem,wx;
    int w;
public:
    auto query(uint32_t si,uint32_t ad){
        auto findmem=[&](uint32_t s){
            cir(i,0,w) if(mem[i]==s&&(!statu[i])) return i;
            return -1;
        };
        auto findinvalid=[&](){
            cir(i,0,w) if(statu[i]) return i;
            return -1;
        };
        if(auto p=findmem(si);p>-1){
            return wx[p];
        }else if(auto p=findinvalid();p>-1){
            wx[p]=memory_read(si+ad);
            statu[p]=false;
            mem[p]=si;
            return wx[p];
        }
        auto upd=rnd()%w;
        mem[upd]=si;
        wx[upd]=memory_read(si+ad);
        return wx[upd];
    }
    RandomAlgorithm(int _w):w(_w),wx(_w),rnd(1),statu(_w,true),mem(_w){}
};
class FIFO_Algorithm{
private:
    multiset<pair<int,int>> ins;
    vector<uint32_t> mem,wx;
    vector<bool> statu;
    int w,c;
public:
    auto query(uint32_t si,uint32_t ad){
        auto findmem=[&](uint32_t s){
            cir(i,0,w) if(mem[i]==s) return i;
            return -1;
        };
        auto findinvalid=[&](){
            cir(i,0,w) if(statu[i]) return i;
            return -1;
        };
        if(auto p=findmem(si);p>-1){
            return wx[p];
        }else if(auto p=findinvalid();p>-1){
            statu[p]=false;
            mem[p]=si;wx[p]=memory_read(si+ad);
            ins.insert({++c,p});
            return wx[p];
        }
        auto upd=ins.begin()->second;
        ins.erase(ins.begin());
        mem[upd]=si;wx[upd]=memory_read(si+ad);
        ins.insert({++c,upd});
        return wx[upd];
    }
    FIFO_Algorithm(int _w):mem(_w),wx(_w),statu(_w,true),w(_w),c(0){}
};
class LFU_Algorithm{
private:
    vector<uint32_t> mem,wx;
    vector<bool> statu;
    vector<int> cnt;
    int w;
public:
    auto query(uint32_t si,uint32_t ad){
        auto findmem=[&](uint32_t s){
            cir(i,0,w) if(mem[i]==s&&(!statu[i])) return i;
            return -1;
        };
        auto findinvalid=[&](){
            cir(i,0,w) if(statu[i]) return i;
            return -1;
        };
        auto findchange=[&](){
            auto res=pair(_inf,0);
            cir(i,0,w) res=min(res,pair(cnt[i],i));
            return res.second;
        };
        if(auto p=findmem(si);p>-1){
            ++cnt[p];
            return wx[p];
        }else if(auto p=findinvalid();p>-1){
            statu[p]=false;
            mem[p]=si;cnt[p]=1;wx[p]=memory_read(si+ad);
            return wx[p];
        }
        auto upd=findchange();
        mem[upd]=si;cnt[upd]=1;wx[upd]=memory_read(si+ad);
        return wx[upd];
    }
    LFU_Algorithm(int _w):w(_w),mem(_w),wx(_w),statu(_w,true),cnt(_w){}
};
class LRU_Algorithm{
private:
    vector<uint32_t> mem,wx;
    vector<bool> statu;
    vector<int> cnt;
    int w,c;
public:
    auto query(uint32_t si,uint32_t ad){
        auto findmem=[&](uint32_t s){
            cir(i,0,w) if(mem[i]==s&&(!statu[i])) return i;
            return -1;
        };
        auto findinvalid=[&](){
            cir(i,0,w) if(statu[i]) return i;
            return -1;
        };
        auto findchange=[&](){
            auto res=pair(_inf,0);
            cir(i,0,w) res=min(res,pair(cnt[i],i));
            return res.second;
        };
        if(auto p=findmem(si);p>-1){
            cnt[p]=++c;
            return wx[p];
        }else if(auto p=findinvalid();p>-1){
            statu[p]=false;
            mem[p]=si;cnt[p]=++c;wx[p]=memory_read(si+ad);
            return wx[p];
        }
        auto upd=findchange();
        mem[upd]=si;cnt[upd]=++c;wx[upd]=memory_read(si+ad);
        return wx[upd];
    }
    LRU_Algorithm(int _w):w(_w),mem(_w),wx(_w),statu(_w,true),cnt(_w),c(0){}
};
class MRU_Algorithm{
private:
    vector<uint32_t> mem,wx;
    vector<bool> statu;
    vector<int> cnt;
    int w,c;
public:
    auto query(uint32_t si,uint32_t ad){
        auto findmem=[&](uint32_t s){
            cir(i,0,w) if(mem[i]==s&&(!statu[i])) return i;
            return -1;
        };
        auto findinvalid=[&](){
            cir(i,0,w) if(statu[i]) return i;
            return -1;
        };
        auto findchange=[&](){
            auto res=pair(_inf,0);
            cir(i,0,w) res=min(res,pair(-cnt[i],i));
            return res.second;
        };
        if(auto p=findmem(si);p>-1){
            cnt[p]=++c;
            return wx[p];
        }else if(auto p=findinvalid();p>-1){
            statu[p]=false;
            mem[p]=si;cnt[p]=++c;wx[p]=memory_read(si+ad);
            return wx[p];
        }
        auto upd=findchange();
        mem[upd]=si;cnt[upd]=++c;wx[upd]=memory_read(si+ad);
        return wx[upd];
    }
    MRU_Algorithm(int _w):w(_w),mem(_w),wx(_w),statu(_w,true),cnt(_w),c(0){}
};
class PLRU_Algorithm{
private:
    class tree{
    private:
        vector<int> dir;
        int n;
    public:
        auto modify(int u){
            u+=n;
            while(u){
                dir[u/2]=!(u&1);
                u/=2;
            }
        }
        auto query(){
            auto u=1;
            while(u<n) u=u*2+dir[u];
            return u-n;
        }
        tree(int _n):dir(_n<<1),n(_n){}
    };
    vector<uint32_t> mem,wx;
    tree tr;
    vector<bool> statu;
    int w;
public:
    auto query(uint32_t si,uint32_t ad){
        auto findmem=[&](uint32_t s){
            cir(i,0,w) if(mem[i]==s) return i;
            return -1;
        };
        if(auto p=findmem(si);p>-1){
            tr.modify(p);
            return wx[p];
        }
        auto upd=tr.query();
        mem[upd]=si;tr.modify(upd);
        statu[upd]=false;wx[upd]=memory_read(si+ad);
        return wx[upd];
    }
    PLRU_Algorithm(int _w):mem(_w),tr(_w),statu(_w,true),w(_w),wx(_w){}
};

vector<NoAlgorithm> NA;
vector<RandomAlgorithm> RD;
vector<FIFO_Algorithm> FF;
vector<LFU_Algorithm> LF;
vector<LRU_Algorithm> LR;
vector<MRU_Algorithm> MR;
vector<PLRU_Algorithm> PL;

int W,R;

template<typename _Ty>
auto rsz(vector<_Ty>&a){
    a.resize(1<<16,_Ty(W));
}

void cache_init(uint8_t w,uint8_t r){
    W=w;R=r;
    rsz(NA);rsz(RD);rsz(FF);rsz(LF);rsz(LR);rsz(MR);rsz(PL);
}

template<typename _Ty>
auto query(uint32_t address,_Ty&x){
    const auto lgw=(int)(round(log2(W)));
    return x[(address%(65536>>lgw))>>2].query(address/(65536>>lgw),address-address/(65536>>lgw));
}

uint32_t cache_read(uint32_t address){
    if(R==1) return query(address,NA);
    if(R==2) return query(address,RD);
    if(R==3) return query(address,FF);
    if(R==4) return query(address,LF);
    if(R==5) return query(address,LR);
    if(R==6) return query(address,MR);
    return query(address,PL);
}
