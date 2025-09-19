#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto hash_v=251ull;
class sparsetable{
private:
    static constexpr auto ups=21;
    struct node{
        char val;
        int len;
        array<int,ups> nxt;
        array<uint64_t,ups> hsh;
        node(char v=0):val(v),len(1){
            memset(nxt.data(),255,sizeof(nxt));
            memset(hsh.data(),0,sizeof(hsh));
        }
    };
    vector<node> tr;
    vector<uint64_t> pw;
public:
    auto append_left(char c,int pos=0){
        const auto u=(int)(tr.size());
        tr.emplace_back(c);
        tr[u].nxt[0]=pos;
        tr[u].hsh[0]=c;
        if(u!=pos) tr[u].len+=tr[pos].len;
        cir(i,1,ups){
            tr[u].nxt[i]=tr[tr[u].nxt[i-1]].nxt[i-1];
            tr[u].hsh[i]=tr[u].hsh[i-1]*pw[i-1]+tr[tr[u].nxt[i-1]].hsh[i-1];
        }
        return u;
    }
    auto compare(int u,int v){
        for(auto i=ups-1;~i;--i) if(tr[u].len>(1<<i)-1&&tr[v].len>(1<<i)-1&&tr[u].hsh[i]==tr[v].hsh[i]){
            u=tr[u].nxt[i];
            v=tr[v].nxt[i];
        }
        if(tr[u].len==1||tr[v].len==1) return tr[u].len<tr[v].len;
        return tr[u].val<tr[v].val;
    }
    auto export_str(int u){
        string res;
        while(tr[u].nxt[0]!=u){
            res+=tr[u].val;
            u=tr[u].nxt[0];
        }
        res+=tr[u].val;
        return res;
    }
    auto reserve(const auto n){
        tr.reserve(n);
    }
    sparsetable(){
        pw.resize(ups+7,1);
        pw[0]=ups;
        cir(i,1,ups+7) pw[i]=pw[i-1]*pw[i-1];
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    const auto n=(int)(s.size());
    sparsetable st;
    st.reserve(n+1);
    vector<int> f(n+1);
    f[n]=st.append_left('#');
    vector<int> pos(n,-1);
    stack<int> stk;
    for(auto i=n-1;~i;--i){
        if(s[i]==')'){
            stk.emplace(i);
        }else{
            if(!stk.empty()){
                pos[i]=stk.top();
                stk.pop();
            }
        }
    }
    for(auto i=n-1;~i;--i){
        if(pos[i]<0){
            f[i]=st.append_left(s[i],f[i+1]);
        }else{
            const auto u=st.append_left(s[i],f[i+1]);
            const auto v=f[pos[i]+1];
            f[i]=(st.compare(u,v)?u:v);
        }
    }
    auto ans=st.export_str(f[0]);
    ans.pop_back();
    cout<<ans<<'\n';
    return 0;
}

