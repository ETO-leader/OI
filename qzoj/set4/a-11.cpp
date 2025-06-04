#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
complex<lint> operator%(complex<lint> a,const int m){
    return complex<lint>((real(a)+m)%m,(imag(a)+m)%m);
}
complex<lint>&operator%=(complex<lint>&a,const int m){
    return a=complex<lint>((real(a)+m)%m,(imag(a)+m)%m);
}
constexpr complex<lint> operator""_x(unsigned long long w){
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
            isop(true),valrange(make_pair(-1,-1)),
            oper(op),ls(_ls),rs(_rs){}
        nodeinfo()=default;
    };
    string s;
    const int m;
    vector<nodeinfo> tr;
    complex<lint> valulizer(int l,int r){
        complex<lint> res(0,0);
        cir(i,l,r+1){
            if(isdigit(s[i])){
                (res*=10)+=(s[i]-'0');
                res%=m;
            }else{
                if(i==l) res=1_x;
                else res*=1_x;
            }
        }
        return res;
    }
    complex<lint> evalute(complex<lint> l,complex<lint> r,char op){
        if(op=='+') return (l+r)%m;
        if(op=='-') return (l-r)%m;
        assert(op=='*');
        return (l*r)%m;
    }
    complex<lint> calculator(int u){
        if(!tr[u].isop){
            int ul=tr[u].valrange.first,ur=tr[u].valrange.second;
            return valulizer(ul,ur);
        }
        complex<lint> sgnls(tr[u].ls<0?m-1:1),sgnrs(tr[u].rs<0?m-1:1);
        return evalute(calculator(abs(tr[u].ls))*sgnls,calculator(abs(tr[u].rs))*sgnrs,tr[u].oper);
    }
    int cnt;
    pair<int,int> build(int l){
        auto getnode=[&](int p){
            int r=p;
            while(r+1<(int)(s.size())&&s[r+1]!='+'&&s[r+1]!='-'&&s[r+1]!='*'&&s[r+1]!='('&&s[r+1]!=')') ++r;
            return make_pair(p,r);
        };
        stack<int> stc;
        char lastop='\\';
        while(s[l]!=')'){
            ++l;
            if(s[l]=='('){
                pair<int,int> pr=build(l);
                int u=pr.first;
                l=pr.second+1;
                if(stc.empty()||lastop=='+'||lastop=='-'){
                    stc.emplace(u*(lastop=='-'?-1:1));
                }else{
                    int w=stc.top();stc.pop();
                    int cur=++cnt;
                    tr[cur]=nodeinfo('*',w,u);
                    stc.emplace(cur);
                }
                lastop=s[l];
            }else{
                pair<int,int> pr=getnode(l);
                int ul=pr.first,ur=pr.second;
                l=ur+1;
                ++cnt;
                tr[cnt]=nodeinfo(make_pair(ul,ur));
                int uid=cnt;
                if(stc.empty()||lastop=='+'||lastop=='-'){
                    stc.emplace(uid*(lastop=='-'?-1:1));
                }else{
                    int w=stc.top();stc.pop();
                    int cur=++cnt;
                    tr[cur]=nodeinfo('*',w,uid);
                    stc.emplace(cur);
                }
                lastop=s[l];
            }
        }
        while(stc.size()>1){
            int u=stc.top();stc.pop();
            int v=stc.top();stc.pop();
            int cur=++cnt;
            tr[cur]=nodeinfo('+',u,v);
            stc.emplace(cur);
        }
        assert(!stc.empty());
        return make_pair(stc.top(),l);
    }
public:
    complex<lint> eval(){
        int root=build(0).first;
        return calculator(root);
    }
    expr_tree(string _s,const int _m):s("("+_s+")"),tr(_s.size()+17),m(_m),cnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    int p,m;cin>>p>>m;
    expr_tree tr(s,m);
    complex<lint> f=tr.eval();
    cir(c,0,m){
        if((imag(f)*c+real(f))%m==p){
            cout<<c<<'\n';
            break;
        }
    }
    return 0;
}
