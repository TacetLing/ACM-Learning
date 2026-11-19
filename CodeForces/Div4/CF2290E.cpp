#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=200005;
void solve(){
    int n,k;
    cin>>n>>k;
    vector<int> arr(n+5,0),f(n+5,0);
    for(int i=1;i<=n;i++){ 
        cin>>arr[i];
        f[i]=arr[i];
    }
    int sum=0,l=n+1,r=n;
    int ans=0;
    for(int i=n;i>=1;i--){
        while(l>i+1){
            l--;
            sum+=f[l];
        }
        while(r>i+k){
            sum-=f[r];
            r--;
        }
        f[i]=(f[i]+sum)%2;
        ans^=f[i];
    }
    if(ans) cout<<"Alice\n";
    else cout<<"Bob\n";
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