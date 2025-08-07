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
        auto cnt=1;++p;
        auto res=(_Ty)(0),prod=(_Ty)(1),las=(_Ty)(0);
        auto lasop='*';
        for(;*p!=')';++p){
            if(!isdigit(*p)){
                if(((string)("+-*/")).find(*p)!=string::npos) prod=eval_val(prod,las,lasop);
                if(*p=='+') res+=prod,prod=1,las=0,lasop='*';
                if(*p=='-') res+=prod,prod=-1,las=0,lasop='*';
                if(*p=='*') las=0,lasop='*';
                if(*p=='/') las=0,lasop='/';
                if(*p=='(') las=eval_str(p);
            }else{
                (las*=10)+=((*p)-'0');
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
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    cout<<expr<int64_t>::eval(s)<<'\n';
    return 0;
}
