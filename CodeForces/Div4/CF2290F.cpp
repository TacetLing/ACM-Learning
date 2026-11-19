#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
    int n;
    cin>>n;
    vector<int> arr(n+5,0);
    vector<int> ans(n+5,0);
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=n;i++){
        if(arr[i]+n-i+1>n || arr[i]+n-i+1<=0){
            cout<<-1<<'\n';
            return;
        }
        ans[arr[i]+n-i+1]=i;
    }
    vector<int> cnt(n+5,0);
    for(int i=1;i<=n;i++) cnt[ans[i]]++;
    for(int i=1;i<=n;i++){
        if(cnt[i]!=1){
            cout<<-1<<'\n';
            return;
        }
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    cout<<'\n';
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