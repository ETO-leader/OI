#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("ladamatek.in");
ofstream ouf("ladamatek.out");
class suffixam{
private:
    static constexpr auto alpha=26;
    vector<array<int,alpha>> tr;
    vector<int> fail,len,f;
    int cur,cnt;
    auto allocm(){
        return ++cnt;
    }
    auto copy(const int fr,const int u){
        const auto cl=allocm();
        len[cl]=len[fr]+1;
        tr[cl]=tr[u];fail[cl]=fail[u];
        return cl;
    }
    auto emplace(const char c){
        const auto u=allocm();
        len[u]=len[cur]+1;f[u]=1;
        auto ux=cur;
        while(ux>-1&&(!tr[ux][c])){
            tr[ux][c]=u;ux=fail[ux];
        }
        if(ux==-1) return fail[cur=u]=0,void();
        const auto vx=tr[ux][c];
        if(len[ux]+1==len[vx]){
            fail[u]=vx;
        }else{
            const auto cl=copy(ux,vx);
            while(ux>-1&&tr[ux][c]==vx){
                tr[ux][c]=cl;ux=fail[ux];
            }
            fail[u]=fail[vx]=cl;
        }
        cur=u;
    }
    auto check(){
        vector<int> a(cnt);
        iota(a.begin(),a.end(),1);
        sort(a.begin(),a.end(),[&](auto u,auto v){
            return len[u]>len[v];
        });
        for(auto&u:a) f[fail[u]]+=f[u];
    }
public:
    auto init(const string s){
        for(const auto&c:s) emplace(c-'a');
        check();
    }
    auto count(int a,int b,int c,int d){
        auto u=0,x=0;
        cir(i,0,d){
            x=(x*a+b)%c;
            const auto v=x%26;
            if(!tr[u][v]) return 0;
            u=tr[u][v];
        }
        return f[u];
    }
    suffixam(int n):tr(n<<1),f(n<<1),fail(n<<1,-1),len(n<<1),cur(0),cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    string s;inf>>s;
    suffixam sam(s.size());
    sam.init(s);
    int q;inf>>q;
    cir(i,0,q){
        int a,b,c,d;inf>>a>>b>>c>>d;
        ouf<<sam.count(a,b,c,d)<<'\n';
    }
    return 0;
}
