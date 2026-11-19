#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    vector<int> diff(28,0);
    for(int i=0;i<n;i++){
        if(s[i]!=s[n-i-1]){
            int u=s[i]-'a'+1,v=s[n-i-1]-'a'+1;
            diff[min(u,v)]++;
            diff[max(u,v)]--;
        }
    }
    vector<int> arr(28,0);
    for(int i=1;i<=27;i++){
        arr[i]=arr[i-1]+diff[i];
    }
    int ans=0;
    for(int i=1;i<=27;i++){
        if(arr[i]>0) ans++;
    }
    cout<<ans<<'\n';
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