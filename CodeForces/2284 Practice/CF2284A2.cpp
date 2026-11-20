#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
    int n;
    cin>>n;
    vector<int> arr(n+5,0);
    int sum=0;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        arr[i]=(1LL<<arr[i]);
        sum+=arr[i];
    }
    sort(arr.begin()+1,arr.begin()+n+1,greater<int>());
    int ans=0;
    for(int i=1;i<=n;i++){
        if(ans+arr[i]<=sum/2){
            ans+=arr[i];
        }
    }
    cout<<(sum-ans)*ans<<'\n';
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