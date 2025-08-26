#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
auto operator%(complex<lint> a,const int m){
    return complex<lint>((real(a)+m)%m,(imag(a)+m)%m);
}
auto&operator%=(complex<lint>&a,const int m){
    return a=complex<lint>((real(a)+m)%m,(imag(a)+m)%m);
}
constexpr auto operator""x(const unsigned long long w){
    return complex<lint>(0,w);
}
class expr_tree{
public:
    struct nodeinfo{
        bool isop;
        pair<int,int> valrange;
        char oper;
        int ls,rs;
        nodeinfo(pair<int,int> valr):
            isop(false),valrange(valr),
            oper('\\'),ls(-1),rs(-1){}
        nodeinfo(char op,int _ls,int _rs):
            isop(true),valrange(-1,-1),
            oper(op),ls(_ls),rs(_rs){}
        nodeinfo()=default;
    };
    string s;
    const int m;
    vector<nodeinfo> tr;
    auto valulizer(int l,int r){
        auto res=complex<lint>(0);
        cir(i,l,r+1){
            if(isdigit(s[i])){
                ((res*=10)+=(s[i]-'0'))%=m;
            }else{
                if(i==l) res=1x;
                else res*=1x;
            }
        }
        return res;
    }
    auto evalute(auto l,auto r,char op){
        if(op=='+') return (l+r)%m;
        if(op=='-') return (l-r)%m;
        assert(op=='*');
        return (l*r)%m;
    }
    auto calculator(int u){
        if(!tr[u].isop){
            const auto[ul,ur]=tr[u].valrange;
            return valulizer(ul,ur);
        }
        const auto sgnls=complex<lint>(tr[u].ls<0?m-1:1);
        const auto sgnrs=complex<lint>(tr[u].rs<0?m-1:1);
        return evalute(calculator(abs(tr[u].ls))*sgnls,calculator(abs(tr[u].rs))*sgnrs,tr[u].oper);
    }
    int cnt;
    /*
        process a block from l to right-pos
        @arguments l
        @returns root-id & right-pos
    */
    auto build(int l)->pair<int,int>{
        auto getnode=[&](int p){
            auto r=p;
            while(r+1<(int)(s.size())&&s[r+1]!='+'&&s[r+1]!='-'&&s[r+1]!='*'&&s[r+1]!='('&&s[r+1]!=')') ++r;
            return pair(p,r);
        };
        stack<int> stc;
        char lastop='\\';
        while(s[l]!=')'){
            ++l;
            if(s[l]=='('){
                const auto[u,nl]=build(l);
                l=nl+1;
                if(stc.empty()||lastop=='+'||lastop=='-'){
                    stc.emplace(u*(lastop=='-'?-1:1));
                }else{
                    const auto w=stc.top();
                    stc.pop();
                    const auto cur=++cnt;
                    tr[cur]=nodeinfo('*',w,u);
                    stc.emplace(cur);
                }
                lastop=s[l];
            }else{
                const auto[ul,ur]=getnode(l);
                l=ur+1;
                ++cnt;
                const auto u=tr[cnt]=nodeinfo(pair(ul,ur));
                const auto uid=cnt;
                if(stc.empty()||lastop=='+'||lastop=='-'){
                    stc.emplace(uid*(lastop=='-'?-1:1));
                }else{
                    const auto w=stc.top();
                    stc.pop();
                    const auto cur=++cnt;
                    tr[cur]=nodeinfo('*',w,uid);
                    stc.emplace(cur);
                }
                lastop=s[l];
            }
        }
        while(stc.size()>1){
            const auto u=stc.top();stc.pop();
            const auto v=stc.top();stc.pop();
            const auto cur=++cnt;
            tr[cur]=nodeinfo('+',u,v);
            stc.emplace(cur);
        }
        assert(!stc.empty());
        return pair(stc.top(),l);
    }
public:
    auto eval(){
        const auto root=build(0).first;
        return calculator(root);
    }
    expr_tree(string _s,const int _m):s('('+_s+')'),tr(_s.size()+17),m(_m),cnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    int p,m;cin>>p>>m;
    expr_tree tr(s,m);
    const auto f=tr.eval();
    cir(c,0,m){
        if((imag(f)*c+real(f))%m==p){
            cout<<c<<'\n';
            break;
        }
    }
    return 0;
}
