#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class NoAlgorithm{
public:
    NoAlgorithm(int w,int q){
        assert(w==1);
        string las="\\";
        cir(i,0,q){
            string si;cin>>si;
            if(!i){
                cout<<-1<<'\n';
                las=si;
            }else{
                cout<<(las==si?-1:0)<<'\n';
                las=si;
            }
        }
    }
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
public:
    RandomAlgorithm(int w,int q){
        random_device_gen rnd(1);
        vector<bool> statu(w,true);
        vector<string> mem(w,"\\");
        auto findmem=[&](string s){
            cir(i,0,w) if(mem[i]==s) return true;
            return false;
        };
        auto findinvalid=[&](){
            cir(i,0,w) if(statu[i]) return i;
            return -1;
        };
        cir(i,0,q){
            string si;cin>>si;
            if(findmem(si)){
                cout<<-1<<'\n';
            }else if(auto p=findinvalid();p>-1){
                cout<<-1<<'\n';
                statu[p]=false;
                mem[p]=si;
            }else{
                auto upd=rnd()%w;
                mem[upd]=si;
                cout<<upd<<'\n';
            }
        }
    }
};
class FIFO_Algorithm{
public:
    FIFO_Algorithm(int w,int q){
        multiset<pair<int,int>> ins;
        vector<string> mem(w,"\\");
        vector<bool> statu(w,true);
        auto findmem=[&](string s){
            cir(i,0,w) if(mem[i]==s) return true;
            return false;
        };
        auto findinvalid=[&](){
            cir(i,0,w) if(statu[i]) return i;
            return -1;
        };
        cir(i,0,q){
            string si;cin>>si;
            if(findmem(si)){
                cout<<-1<<'\n';
            }else if(auto p=findinvalid();p>-1){
                cout<<-1<<'\n';
                statu[p]=false;
                mem[p]=si;
                ins.insert({i,p});
            }else{
                auto upd=ins.begin()->second;
                ins.erase(ins.begin());
                mem[upd]=si;
                ins.insert({i,upd});
                cout<<upd<<'\n';
            }
        }
    }
};
class LFU_Algorithm{
public:
    LFU_Algorithm(int w,int q){
        vector<string> mem(w,"\\");
        vector<bool> statu(w,true);
        vector<int> cnt(w);
        auto findmem=[&](string s){
            cir(i,0,w) if(mem[i]==s) return i;
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
        cir(i,0,q){
            string si;cin>>si;
            if(auto p=findmem(si);p>-1){
                ++cnt[p];
                cout<<-1<<'\n';
            }else if(auto p=findinvalid();p>-1){
                statu[p]=false;
                mem[p]=si;cnt[p]=1;
                cout<<-1<<'\n';
            }else{
                auto upd=findchange();
                mem[upd]=si;cnt[upd]=1;
                cout<<upd<<'\n';
            }
        }
    }
};
class LRU_Algorithm{
public:
    LRU_Algorithm(int w,int q){
        vector<string> mem(w,"\\");
        vector<bool> statu(w,true);
        vector<int> mdf(w);
        auto findmem=[&](string s){
            cir(i,0,w) if(mem[i]==s) return i;
            return -1;
        };
        auto findinvalid=[&](){
            cir(i,0,w) if(statu[i]) return i;
            return -1;
        };
        auto findchange=[&](){
            auto res=pair(_inf,0);
            cir(i,0,w) res=min(res,pair(mdf[i],i));
            return res.second;
        };
        cir(i,0,q){
            string si;cin>>si;
            if(auto p=findmem(si);p>-1){
                mdf[p]=i;
                cout<<-1<<'\n';
            }else if(auto p=findinvalid();p>-1){
                statu[p]=false;
                mem[p]=si;mdf[p]=i;
                cout<<-1<<'\n';
            }else{
                auto upd=findchange();
                mem[upd]=si;mdf[upd]=i;
                cout<<upd<<'\n';
            }
        }
    }
};
class MRU_Algorithm{
public:
    MRU_Algorithm(int w,int q){
        vector<string> mem(w,"\\");
        vector<bool> statu(w,true);
        vector<int> mdf(w);
        auto findmem=[&](string s){
            cir(i,0,w) if(mem[i]==s) return i;
            return -1;
        };
        auto findinvalid=[&](){
            cir(i,0,w) if(statu[i]) return i;
            return -1;
        };
        auto findchange=[&](){
            auto res=pair(_inf,0);
            cir(i,0,w) res=min(res,pair(-mdf[i],i));
            return res.second;
        };
        cir(i,0,q){
            string si;cin>>si;
            if(auto p=findmem(si);p>-1){
                mdf[p]=i;
                cout<<-1<<'\n';
            }else if(auto p=findinvalid();p>-1){
                statu[p]=false;
                mem[p]=si;mdf[p]=i;
                cout<<-1<<'\n';
            }else{
                auto upd=findchange();
                mem[upd]=si;mdf[upd]=i;
                cout<<upd<<'\n';
            }
        }
    }
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
public:
    PLRU_Algorithm(int w,int q){
        vector<string> mem(w,"\\");
        tree tr(w);
        vector<bool> statu(w,true);
        auto findmem=[&](string s){
            cir(i,0,w) if(mem[i]==s) return i;
            return -1;
        };
        cir(i,0,q){
            string si;cin>>si;
            if(auto p=findmem(si);p>-1){
                tr.modify(p);
                cout<<-1<<'\n';
            }else{
                auto upd=tr.query();
                mem[upd]=si;tr.modify(upd);
                cout<<(statu[upd]?-1:upd)<<'\n';
                statu[upd]=false;
            }
        }
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int w,r,q;cin>>w>>r>>q;
    if(r==1) NoAlgorithm(w,q);
    if(r==2) RandomAlgorithm(w,q);
    if(r==3) FIFO_Algorithm(w,q);
    if(r==4) LFU_Algorithm(w,q);
    if(r==5) LRU_Algorithm(w,q);
    if(r==6) MRU_Algorithm(w,q);
    if(r==7) PLRU_Algorithm(w,q);
    return 0;
}
