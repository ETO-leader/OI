#include"perm.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

static constexpr auto maxb=(int)(1e7);

auto ask(vector<int> p){
    vector<bool> res(p.size());
    for(auto l=0;l<(int)(p.size());l+=maxb){
        const auto qarr=vector(p.begin()+l,p.begin()+min(l+maxb,(int)(p.size())));
        const auto ns=query(qarr);
        cir(i,l,l+(int)(ns.size())) res[i]=ns[i-l];
    }
    return res;
}

vector<int> solve(int n,int subtask){
    mt19937_64 eng(251);
    const auto c=251;
    vector<unordered_set<int>> gr(n);
    auto roundc=15;
    auto gen=[&]{
        vector<int> gp,qv;
        vector<vector<int>> uv;
        cir(r,0,roundc){
            gp.emplace_back((int)(qv.size()));
            vector<int> vaild;
            cir(i,0,n) if(gr[i].size()<2) vaild.emplace_back(i);
            shuffle(vaild.begin(),vaild.end(),eng);
            vaild.resize(min<int>(vaild.size(),c));
            for(auto&i:vaild) qv.emplace_back(i);
            for(auto&i:vaild) qv.emplace_back(i);
            uv.emplace_back(vaild);
        }
        for(auto&x:qv) ++x;
        const auto s=ask(qv);
        vector<vector<int>> res;
        cir(r,0,roundc){
            auto&vaild=uv[r];
            auto x=gp[r]+1;
            while(x-gp[r]<(int)(vaild.size())&&(!s[x])) ++x;
            res.emplace_back(vector(vaild.begin(),vaild.begin()+(x-gp[r])));
        }
        return res;
    };
    while([&]{
        auto res=2;
        for(auto&i:gr) res=min(res,(int)(i.size()));
        return res;
    }()<2){
        auto invaild=0;
        for(auto&i:gr) invaild+=i.size()<2;
        if(invaild<5000) break;
        roundc=min(invaild<15000?120:196,(int)(4.9e6)/invaild);
        auto cnt=0;
        for(auto&i:gr) cnt+=(int)(i.size())<2;
        vector<int> qry,sp;
        vector<unordered_set<int>> uins;
        auto us=gen();
        cir(r,0,roundc){
            const auto s=us[r];
            for(auto&i:s) qry.emplace_back(i);
            auto p=(int)(qry.size());
            sp.emplace_back(p);
            us.emplace_back(s);
            uins.emplace_back(unordered_set(s.begin(),s.end()));
            cir(i,0,n) if((int)(gr[i].size())<2&&(!uins[r].count(i))){
                qry.emplace_back(i);
                qry.emplace_back(i);
            }
            for(auto&x:s) qry.emplace_back(x);
        }
        for(auto&i:qry) ++i;
        const auto c=ask(qry);
        qry.clear();
        vector<int> bp;
        vector<vector<int>> uqn;
        cir(r,0,roundc){
            vector<int> qn;
            auto p=sp[r];
            auto ins=uins[r];
            auto s=us[r];
            auto cnt=0;
            for(auto x:c) cnt+=x;
            cir(i,0,n) if((int)(gr[i].size())<2&&(!ins.count(i))){
                if(c[p]) qn.emplace_back(i);
                ++p;
                ++p;
            }
            uqn.emplace_back(qn);
            bp.emplace_back((int)(qry.size()));
            cir(i,0,(int)(s.size())){
                qry.emplace_back(s[i]);
                cir(j,0,(int)(qn.size())){
                    qry.emplace_back(qn[j]);
                    qry.emplace_back(qn[j]);
                }
                qry.emplace_back(s[i]);
            }
        }
        for(auto&i:qry) ++i;
        const auto st=ask(qry);
        cir(r,0,roundc){
            auto qn=uqn[r];
            auto p=bp[r];
            auto s=us[r];
            cir(i,0,(int)(s.size())){
                ++p;
                cir(j,0,(int)(qn.size())){
                    if(st[p]){
                        gr[s[i]].emplace(qn[j]);
                        gr[qn[j]].emplace(s[i]);
                    }
                    ++p;
                    ++p;
                }
                ++p;
            }
        }
    }
    [&]{
        vector<int> qry;
        vector<int> ns;
        cir(i,0,n) if((int)(gr[i].size())<2) ns.emplace_back(i);
        const auto un=(int)(ns.size());
        cir(i,0,un){
            qry.emplace_back(ns[i]+1);
            cir(j,i+1,un){
                qry.emplace_back(ns[j]+1);
                qry.emplace_back(ns[j]+1);
            }
            qry.emplace_back(ns[i]+1);
        }
        const auto result=ask(qry);
        vector<pair<int,int>> es;
        [&]{
            auto p=0;
            cir(i,0,un){
                ++p;
                cir(j,i+1,un){
                    if(result[p]) es.emplace_back(ns[i],ns[j]);
                    ++p;
                    ++p;
                }
                ++p;
            }
        }();
        for(auto&[u,v]:es){
            gr[u].emplace(v);
            gr[v].emplace(u);
        }
    }();
    auto p=*gr[0].begin();
    auto las=0;
    vector<int> stc{1};
    while(p){
        stc.emplace_back(p+1);
        for(auto&x:gr[p]) if(x!=las){
            swap(p,las);
            p=x;
            break;
        }
    }
    return stc;
}
