#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty>
class expr{
private:
    static auto eval_val(_Ty a,_Ty b,char op){
        return
            op=='+'?a+b:
            op=='-'?a-b:
            op=='*'?a*b:
            a/b;
    }
    static auto eval_str(string::iterator&p)->_Ty{
        ++p;
        auto res=(_Ty)(0),prod=(_Ty)(1),las=(_Ty)(0);
        auto lasop='*';
        for(auto f=true;*p!=')';++p){
            if(!isdigit(*p)){
                if(((string)("+-*/")).find(*p)!=string::npos&&(!f)) prod=eval_val(prod,las,lasop);
                if(*p=='+') res+=prod,prod=1,las=0,lasop='*',f=true;
                if(*p=='-'){
                    if(!f) res+=prod,prod=-1,las=0,lasop='*';
                    else prod*=-1;
                    f=true;
                }
                if(*p=='*') las=0,lasop='*',f=true;
                if(*p=='/') las=0,lasop='/',f=true;
                if(*p=='(') las=eval_str(p),f=false;
            }else{
                (las*=10)+=((*p)-'0');
                f=false;
            }
        }
        prod=eval_val(prod,las,lasop);
        return res+=prod;
    }
public:
    static auto eval(string s){
        s='('+s+')';
        auto p=s.begin();
        return eval_str(p);
    }
};
class checker{
public:
    static auto check(string s){
        auto cnt=0;
        s='('+s+')';
        for(auto&x:s){
            cnt+=(x=='('?1:(x==')'?-1:0));
            if(cnt<0) return false;
        }
        if(cnt) return false;
        if(s.find("(+")!=string::npos) return false;
        if(s.find("(*")!=string::npos) return false;
        if(s.find("(/")!=string::npos) return false;
        if(s.find("+)")!=string::npos) return false;
        if(s.find("-)")!=string::npos) return false;
        if(s.find("*)")!=string::npos) return false;
        if(s.find("/)")!=string::npos) return false;
        if(s.find("++")!=string::npos) return false;
        if(s.find("--")!=string::npos) return false;
        if(s.find("**")!=string::npos) return false;
        if(s.find("//")!=string::npos) return false;
        if(s.find("+*")!=string::npos) return false;
        if(s.find("+/")!=string::npos) return false;
        if(s.find("-+")!=string::npos) return false;
        if(s.find("-*")!=string::npos) return false;
        if(s.find("-/")!=string::npos) return false;
        if(s.find("*+")!=string::npos) return false;
        if(s.find("*/")!=string::npos) return false;
        if(s.find("/+")!=string::npos) return false;
        if(s.find("/*")!=string::npos) return false;
        return true;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;s.pop_back();
    if(!checker::check(s)) cout<<"NO"<<'\n';
    else cout<<expr<int64_t>::eval(s)<<'\n';
    return 0;
}
