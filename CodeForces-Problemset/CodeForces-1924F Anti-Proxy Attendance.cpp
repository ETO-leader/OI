#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class interactive{
public:
    static auto count(int l,int r){
        cout<<'?'<<' '<<l<<' '<<r<<'\n';
        cout.flush();
        int x;cin>>x;
        return x==r-l;
    }
    static auto ask(int x){
        cout<<'!'<<' '<<x<<'\n';
        cout.flush();
        int ok;cin>>ok;
        return ok;
    }
    static auto shield(){
        cout<<'#'<<'\n';
        cout.flush();
    }
};
auto link(vector<int> a,vector<int> b){
    for(auto&i:b) a.push_back(i);
    return a;
}
auto divide(vector<int> arr){
    const auto len=(int)(arr.size());
    if(len==2){
        return assert(
            accumulate(arr.begin(),arr.end(),0,
                [&](int a,int x){return a|=interactive::ask(x);}
            )
        );
    }
    const auto posl=(int)(round(len*0.36));
    const auto posr=(int)(round(len*0.64));
    if(interactive::count(arr[0],arr[posr-1])){
        if(interactive::count(arr[0],arr[posl-1])){
            if(interactive::count(arr[0],arr[len-1])){         // Certainly, segment A is impossible
                return divide(
                    vector(arr.begin()+posl,arr.end())
                );
            }else{                                             // Certainly, segment C is impossible
                return divide(
                    vector(arr.begin(),arr.begin()+posr)
                );
            }
        }else{                                                 // ==> count(B,C) == true
            if(interactive::count(arr[0],arr[posr-1])){        // Certainly, segment B is impossible
                return divide(link(
                    vector(arr.begin(),arr.begin()+posl),
                    vector(arr.begin()+posr,arr.end())
                ));
            }else{
                if(interactive::count(arr[0],arr[len-1])){     // Certainly, segment C is impossible
                    return divide(
                        vector(arr.begin(),arr.begin()+posr)
                    );
                }else{                                         // Certainly, segment A is impossible
                    return divide(
                        vector(arr.begin()+posl,arr.end())
                    );
                }
            }
        }
    }else{
        if(interactive::count(arr[0],arr[posl-1])){
            if(interactive::count(arr[0],arr[posr-1])){
                if(interactive::count(arr[0],arr[len-1])){     // Certainly, segment A is impossible
                    return divide(
                        vector(arr.begin()+posl,arr.end())
                    );
                }else{                                         // Certainly, segment C is impossible
                    return divide(
                        vector(arr.begin(),arr.begin()+posr)
                    );
                }
            }else{                                             // Certainly, segment B is impossible
                return divide(link(
                    vector(arr.begin(),arr.begin()+posl),
                    vector(arr.begin()+posr,arr.end())
                ));
            }
        }else{
            if(interactive::count(arr[0],arr[len-1])){     // Certainly, segment C is impossible
                return divide(
                    vector(arr.begin(),arr.begin()+posr)
                );
            }else{                                         // Certainly, segment A is impossible
                return divide(
                    vector(arr.begin()+posl,arr.end())
                );
            }
        }
    }
    abort();
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        divide([](int len){
            vector<int> a(len);
            iota(a.begin(),a.end(),1);
            return a;
        }(n));
        interactive::shield();
    }
    return 0;
}
