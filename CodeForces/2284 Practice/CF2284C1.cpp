#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=2e5+5;
vector<int> all_x;
bool is_prime[MAXN];
void oula(){
    for(int i=2;i<MAXN;i++){
        if(!is_prime[i]){
            all_x.push_back(i);
        }
        for(int j=0;j<(int)all_x.size() && all_x[j]*i<MAXN;j++){
            is_prime[all_x[j]*i]=true;
            if(i%all_x[j]==0) break;
        }
    }
    return;
}
int n;
void solve(){
    cin>>n;
    vector<int> arr(n+5,0);
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=n;i++){
        auto it=lower_bound(all_x.begin(),all_x.end(),arr[i]);
        cout<<*it<<' ';
    }
    cout<<'\n';
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    oula();
    // for(auto e : all_x){
    //     cout<<e<<' ';
    // }
    // cout<<'\n';
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}