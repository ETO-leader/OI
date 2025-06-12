#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const auto ans=vector<vector<vector<int>>>{
    vector<vector<int>>{
    },
    vector<vector<int>>{
        vector<int>{1},
        vector<int>{2},
    },
    vector<vector<int>>{
        vector<int>{1,2},
        vector<int>{1,3},
        vector<int>{1,4},
        vector<int>{2,3},
        vector<int>{2,4},
        vector<int>{3,4},
    },
    vector<vector<int>>{
        vector<int>{1,2,3},
        vector<int>{1,2,4},
        vector<int>{1,3,5},
        vector<int>{1,4,6},
        vector<int>{1,5,6},
        vector<int>{2,3,6},
        vector<int>{2,4,5},
        vector<int>{2,5,6},
        vector<int>{3,4,5},
        vector<int>{3,4,6},
    },
    vector<vector<int>>{
        vector<int>{1,2,3,4},
        vector<int>{1,2,3,5},
        vector<int>{1,4,6,7},
        vector<int>{1,5,6,7},
        vector<int>{2,4,6,8},
        vector<int>{2,5,6,8},
        vector<int>{3,4,7,8},
        vector<int>{3,5,7,8},
    },
    vector<vector<int>>{
        vector<int>{1,2,3,4,5},
        vector<int>{1,2,3,6,7},
        vector<int>{1,4,5,8,9},
        vector<int>{1,6,7,8,9},
        vector<int>{2,4,6,8,10},
        vector<int>{2,5,7,8,10},
        vector<int>{3,4,6,9,10},
        vector<int>{3,5,7,9,10},
    },
    vector<vector<int>>{
        vector<int>{1,2,3,4,5,6},
        vector<int>{1,2,3,4,7,8},
        vector<int>{1,5,6,7,8,9},
        vector<int>{2,5,7,9,10,11},
        vector<int>{2,6,8,9,10,12},
        vector<int>{3,5,8,10,11,12},
    },
    vector<vector<int>>{
        vector<int>{1,2,3,4,5,6,7},
        vector<int>{1,2,3,4,5,8,9},
        vector<int>{1,6,7,8,9,10,11},
        vector<int>{2,6,8,10,11,12,13},
        vector<int>{2,7,9,10,12,13,14},
    },
    vector<vector<int>>{
        vector<int>{1,2,3,4,5,6,7,8},
        vector<int>{1,2,3,4,5,6,9,10},
        vector<int>{1,7,8,9,10,11,12,13},
        vector<int>{2,7,9,11,12,14,15,16},
        vector<int>{2,8,10,11,13,14,15,16},
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        cerr<<n<<'\n';
        if(n>16){
            cout<<4<<'\n';
            cir(i,0,n) cout<<i+1<<' ';
            cout<<'\n';
            cir(i,0,n) cout<<i+n+1<<' ';
            cout<<'\n';
            cir(i,0,n) cout<<i*2+1<<' ';
            cout<<'\n';
            cir(i,0,n) cout<<(i+1)*2<<' ';
            cout<<'\n';
            return;
        }
        vector<vector<int>> ans,stc;
        vector<uint64_t> stcw;
        auto visit=0ull;
        mt19937 eng(251);
        vector<int> ord(n*2);
        iota(ord.begin(),ord.end(),0);
        auto dfs=[&](auto __self,int cnt){
            if(cnt>(int)(ans.size())) ans=stc;
            if((++visit)>10000000) return;
            shuffle(ord.begin(),ord.end(),eng);
            vector<int> cur;
            vector<uint64_t> ban(n*2);
            cir(i,0,(int)(stcw.size())) cir(j,i+1,(int)(stcw.size())){
                const auto s=stcw[i]&stcw[j];
                cir(p,0,n*2) if((s>>p)&1) ban[p]|=s;
            }
            auto nxt=[&](auto __nself,uint64_t invaild,uint64_t s,int pos){
                if((int)(cur.size())+(n*2-pos)<n) return;
                if(pos==n*2){
                    if(count(stcw.begin(),stcw.end(),s)) return;
                    if(n==2) assert(cur[0]!=cur[1]);
                    stc.emplace_back(cur);
                    stcw.emplace_back(s);
                    __self(__self,cnt+1);
                    stc.pop_back();
                    stcw.pop_back();
                    return;
                }
                auto p=ord[pos];
                if((!((invaild>>p)&1))&&(int)(cur.size())<n){
                    cur.emplace_back(p);
                    __nself(__nself,invaild|ban[p],s|(1ull<<p),pos+1);
                    cur.pop_back();
                }
                __nself(__nself,invaild,s,pos+1);
            };
            nxt(nxt,0,0,0);
        };
        [&]{
            vector<int> x(n);
            iota(x.begin(),x.end(),0);
            stc.emplace_back(x);
            iota(x.begin(),x.end(),n);
            stc.emplace_back(x);
            stcw.emplace_back((1ull<<n)-1);
            stcw.emplace_back(((1ull<<(n*2))-1)^((1ull<<n)-1));
            ans=stc;
            dfs(dfs,2);
        }();
        cout<<ans.size()<<'\n';
        for(auto&x:ans){
            for(auto&i:x) cout<<i+1<<' ';
            cout<<'\n';
        }
    }();
    return 0;
}
