#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class caseistream{
private:
    stringstream inf;
public:
    auto init(){
        int n;cin>>n;inf<<n<<'\n';
        cir(i,0,n){
            int w;cin>>w;inf<<w<<' ';
        }
        inf<<'\n';
    }
    auto&stream(){return inf;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    caseistream inf;inf.init();
    int n;inf.stream()>>n;
    vector<lint> a(n);
    for(auto&i:a) inf.stream()>>i;
    cir(i,0,n) a[i]-=i;
    vector<__gnu_pbds::priority_queue<lint>> w(n);
    vector<int> lef(n);
    ranges::iota(lef,0);
    auto val=a;
    auto getlef=[&](auto __self,int p)->int {
        return lef[p]==p?p:lef[p]=__self(__self,lef[p]);
    };
    cir(i,0,n){
        auto p=i;
        // while(p+1<n&&a[p+1]<a[p]+1) ++p;
        cir(x,i,p+1) w[i].push(a[x]),lef[x]=i;
        const auto left=(p-i+2)/2;
        while((int)(w[i].size())>left) w[i].pop();
        val[i]=w[i].top();
        i=p;
    }
    cir(i,1,n) while(true){
        const auto v=getlef(getlef,i);
        if(!v) break;
        const auto u=getlef(getlef,v-1);
        if(val[u]<val[v]+1) break;
        lef[v]=u;
        w[u].join(w[v]);
        const auto left=(i-u+2)/2;
        while((int)(w[u].size())>left) w[u].pop();
        val[u]=w[u].top();
    }
    auto ans=0ll;
    vector<lint> ansa(n);
    cir(i,0,n) ans+=abs(a[i]-val[getlef(getlef,i)]),ansa[i]=val[getlef(getlef,i)]+i;
    cout<<ans<<'\n';
    ranges::copy(ansa,ostream_iterator<lint>(cout," "));
    cout<<'\n';
    return 0;
}
