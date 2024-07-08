#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
vector<VI> G;
VI cl;
void dfs(int u,int c,set<int>&ins){
    if(G[u].size()==1) ins.insert(c);
    for(auto&i:G[u]) dfs(i,c^1,ins);
}
void recol(int u,int c){
    cl[u]=c;
    for(auto&i:G[u]) recol(i,c^1);
}
pair<int,int> getcx(vector<int>&c){
    if(c[0]&&c[1]) return {0,1};
    if(c.size()==2){
        throw c[0]?0:1;
    }
    if(c[0]&&c[2]) return {0,2};
    if(c[1]&&c[2]) return {1,2};
    throw c[0]?0:(c[1]?1:2);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);
    VI h(n+1),f(n+1);cl.resize(n+1);
    cir(i,2,n+1){
        cin>>f[i];h[i]=h[f[i]]+1;
        G[f[i]].push_back(i);
    }
    int rst;
    if(*max_element(h.begin(),h.end())==1){
        cout<<1<<'\n';
        cir(i,2,n+1) cout<<1<<' ';
        cout.flush();
        cin>>rst;
        if(!rst){
            cout<<1<<'\n';cout.flush();
        }
        exit(0);
    }
    try{
        if(*max_element(h.begin(),h.end())<3)
            throw (string)("special type");
        VI cls;
        for(auto&i:G[1]){
            set<int> sc;
            dfs(i,0,sc);
            if(sc.size()>1){
                throw (string)("must use 3 colors");
            }
            if(sc.empty()) cls.push_back(0);
            else cls.push_back((*sc.begin())^1);
        }
        auto its=cls.begin();
        for(auto&i:G[1]){
            recol(i,*its);++its;
        }
        cout<<2<<'\n';
        cir(i,2,n+1) cout<<cl[i]+1<<' ';
        cout<<'\n';
        cout.flush();
        VI c(2);
        auto clc=[&](){
            try{
                if(!(c[0]&&c[1]))
                    throw c[0]?0:1;
                if(c[0]==c[1]) cout<<2<<'\n';
                else cout<<(c[0]>c[1]?2:1)<<'\n';
            }catch(int x){
                cout<<x+1<<'\n';
            }
            cout.flush();
        };
        while(cin>>rst&&(!rst)){
            for(auto&i:c) cin>>i;
            clc();
        }
    }catch(string){
        const int k=min(3,
            *max_element(h.begin(),h.end()));
        cout<<k<<'\n';
        if(k==3) cir(i,2,n+1){
            cout<<h[i]%k+1<<' ';
        }
        if(k==2) cir(i,2,n+1){
            cout<<(!(h[i]&1))+1<<' ';
        }
        cout<<'\n';
        cout.flush();
        VI c(k);
        auto clc=[&](){
            try{
                auto[c1,c2]=getcx(c);
                if(c1==0&&c2==1) cout<<1<<'\n';
                else if(c1==1&&c2==2) cout<<2<<'\n';
                else cout<<3<<'\n';
            }catch(int x){
                if(x>-1) cout<<x+1<<'\n';
            }
            cout.flush();
        };
        while(cin>>rst&&(!rst)){
            for(auto&i:c) cin>>i;
            clc();
        }
    }
    return 0;
}
