#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class division_by_zero{};
template<typename _Ty>
class expr{
private:
    static auto eval_val(_Ty a,_Ty b,char op){
        if(op=='/'&&(!b)) throw division_by_zero();
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
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    array<string,4> a;cin>>a[0]>>a[1]>>a[2]>>a[3];
    auto dfs=[&](auto __self,int p,int cnt,bool las,int br,string cur)->void {
        if(p>3){
            cir(i,0,cnt) cur+=')';
            try{
                if(fabs(expr<double>::eval(cur)-24)<1e-6){
                    cout<<cur<<'\n';
                    exit(0);
                }
            }catch(division_by_zero){}
            return;
        }
        if(las){
            __self(__self,p,cnt,false,br,cur+'+');
            __self(__self,p,cnt,false,br,cur+'-');
            __self(__self,p,cnt,false,br,cur+'*');
            __self(__self,p,cnt,false,br,cur+'/');
        }
        if(br<6&&(!las)) __self(__self,p,cnt+1,false,br+1,cur+'(');
        if(!las) __self(__self,p+1,cnt,true,br,cur+a[p]);
    };
    sort(a.begin(),a.end());
    do{
        dfs(dfs,0,0,false,0,"");
    }while(next_permutation(a.begin(),a.end()));
    return 0;
}
