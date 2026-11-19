#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
    int a,b,c;
    cin>>a>>b>>c;
    if(a+1!=b || b+1!=c) cout<<"No\n";
    else cout<<"Yes\n";
    return;
}   
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}