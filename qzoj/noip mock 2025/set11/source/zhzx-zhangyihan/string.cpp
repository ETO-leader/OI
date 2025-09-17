/*
 * @Author: jianhe
 * @Date: 2025-09-13 11:44:37
 * @LastEditTime: 2025-09-13 11:45:44
 */
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5+10;
ll T,c;string a,b;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
    cin>>c>>T;
    while(T--){
        cin>>a>>b;
        if(a.size()<=b.size()&&!((b.size()-a.size())&1)) cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}