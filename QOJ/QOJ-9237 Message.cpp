#include"message.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class graph{
public:
    vector<int> uv;
public:
    auto link(int u,int v){
        uv[u]=v;
    }
    auto find(){
        const auto n=(int)(uv.size());
        vector<vector<int>> res;
        cir(i,0,n){
            vector<int> vis(n);
            auto u=i;
            vector<int> cur;
            while(!vis[u]) cur.emplace_back(u),vis[u]=true,u=uv[u];
            if(u==i) res.emplace_back(cur);
        }
        return res;
    }
    graph(int _n):uv(_n){}
};

static constexpr auto infolen=1025;
static constexpr auto infobits=31;
static constexpr auto packcount=66;

void send_message(vector<bool> m,vector<bool> c){
    m.emplace_back(true);
    while((int)(m.size())<infolen) m.emplace_back(false);
    cir(i,0,infobits) c[i]=!c[i];
    auto nxt=[&](int p){
        auto cnt=0;
        while(!c[(p+1)%infobits]) ++p,++cnt;
        return cnt;
    };
    vector<int> d(infobits,-1);
    cir(i,0,infobits) if(c[i]) d[i]=nxt(i);
    set<int> vaild_bits;
    cir(i,0,packcount) cir(j,0,infobits) if(c[j]){
        vaild_bits.emplace(i*infobits+j);
    }
    cir(i,0,infobits) if(c[i]) cir(x,0,d[i]+1) vaild_bits.extract(x*infobits+i);
    auto pos=0;
    cir(i,0,packcount){
        vector<bool> msg(infobits);
        cir(j,0,infobits) if(vaild_bits.contains(i*infobits+j)){
            msg[j]=m[pos];
            ++pos;
        }
        cir(j,0,infobits) if(d[j]==i) msg[j]=true;
        send_packet(msg);
    }
}

vector<bool> receive_message(vector<vector<bool>> r){
    graph chk(infobits);
    vector<int> d(infobits,-1);
    cir(i,0,infobits){
        cir(p,0,packcount) if(r[p][i]){
            d[i]=p;
            break;
        }
    }
    cir(i,0,infobits) if(d[i]>-1) chk.link(i,(i+d[i]+1)%infobits);
    const auto chkf=chk.find();
    auto ux=*ranges::max_element(chkf,[](auto&a,auto&b){return a.size()<b.size();});
    assert(ux.size()>15);
    ranges::sort(ux);
    vector<bool> res;
    cir(i,0,packcount){
        for(auto&p:ux) if(d[p]<i) res.emplace_back(r[i][p]); 
    }
    while(!res.back()) res.pop_back();
    res.pop_back();
    return res;
}
