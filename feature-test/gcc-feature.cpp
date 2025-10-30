#include <bits/stdc++.h>
using namespace std;
using ll = long long;

unordered_set<ll> st;
int main()
{
    for (ll i = 0; i < 200000; i++)
        st.insert(i);
    for (ll i = 0; i < 100000; i++)
        st.clear();
}