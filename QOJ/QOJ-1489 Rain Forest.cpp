#include"jumps.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class sparsetable{
private:
    static constexpr auto ups=21;
    vector<vector<int>> mx;
    auto init(vector<int> a){
        const auto n=(int)(a.size());
        mx.resize(ups,vector<int>(n));
        mx[0]=a;
        cir(c,1,ups) cir(i,0,n-(1<<c)+1){
            mx[c][i]=max(mx[c-1][i],mx[c-1][i+(1<<(c-1))]);
        }
    }
public:
    auto query(int l,int r){
        const auto lg=__lg(r-l+1);
        return max(mx[lg][l],mx[lg][r-(1<<lg)+1]);
    }
    sparsetable(vector<int> a){init(a);}
};

class case_solution{
private:
    sparsetable st;
    static constexpr auto ups=21;
    vector<vector<int>> up,upr;
    vector<int> a;
    map<int,int> pos;
    auto init(const int n){
        for(auto c=-1;auto&i:a) pos[i]=++c;
        vector<pair<int,int>> nxt(n);
        cir(i,0,n) nxt[i]=pair(a[i],i);
        stack<int> lfw,rgw;
        for(auto i=n-1;~i;--i){
            while((!rgw.empty())&&rgw.top()<a[i]) rgw.pop();
            if(!rgw.empty()) nxt[i]=max(nxt[i],pair(rgw.top(),pos[rgw.top()]));
            rgw.emplace(a[i]);
        }
        upr.resize(ups,vector<int>(n));
        cir(i,0,n) upr[0][i]=nxt[i].second;
        cir(c,1,ups) cir(i,0,n) upr[c][i]=upr[c-1][upr[c-1][i]];
        cir(i,0,n){
            while((!lfw.empty())&&lfw.top()<a[i]) lfw.pop();
            if(!lfw.empty()) nxt[i]=max(nxt[i],pair(lfw.top(),pos[lfw.top()]));
            lfw.emplace(a[i]);
        }
        up.resize(ups,vector<int>(n));
        cir(i,0,n) up[0][i]=nxt[i].second;
        cir(c,1,ups) cir(i,0,n) up[c][i]=up[c-1][up[c-1][i]];
    }
    auto start_value(const int l,const int r,const int target){
        auto ql=l,qr=r,ans=-1;
        while(ql-1<qr){
            const auto mid=midpoint(ql,qr);
            st.query(mid,r)<target+1?((qr=mid-1),(ans=mid)):(ql=mid+1);
        }
        return ans>-1?optional(st.query(ans,r)):nullopt;
    }
public:
    auto query(int x,int y,int c,int d){
        const auto target=st.query(y,c-1);
        if(target>st.query(c,d)) return -1;
        if(auto start=start_value(x,y,st.query(c,d))){
            auto u=pos[start.value()];
            auto res=0;
            for(auto i=ups-1;~i;--i) if(a[up[i][u]]<target){
                res+=(1<<i);u=up[i][u];
            }
            if(upr[0][u]>c-1) return res+1;
            if(a[up[0][u]]<st.query(c,d)+1) ++res,u=up[0][u];
            for(auto i=ups-1;~i;--i) if(upr[i][u]<c){
                res+=(1<<i);u=upr[i][u];
            }
            res+=(u<c);
            return res;
        }else{
            return -1;
        }
    }
    case_solution(vector<int> _a):st(_a),a(_a){
        init((int)(a.size()));
    }
};

unique_ptr<case_solution> sol;

void init(int,vector<int> a){
    sol=make_unique<case_solution>(a);
}

int minimum_jumps(int a,int b,int c,int d){
    return sol->query(a,b,c,d);
}
