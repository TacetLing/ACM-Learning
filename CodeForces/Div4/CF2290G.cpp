#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=1000005;
int n,k;
int h[MAXN];
bool check(int mid){
    vector<int> arr(n+5,0);
    for(int i=1;i<=n;i++) arr[i]=h[i];
    for(int j=0;j<2;j++){
        for(int i=1;i<=n;i++){
            int prev=(i==1 ? n : i-1);
            arr[i]=max(arr[i],arr[prev]-mid);
        }
    }
    for(int j=0;j<2;j++){
        for(int i=n;i>=1;i--){
            int nxt=(i==n ? 1 : i+1);
            arr[i]=max(arr[i],arr[nxt]-mid);
        }
    }
    int total=0;
    for(int i=1;i<=n;i++){
        total+=arr[i]-h[i];
        if(total>k) return false;
    }
    return true;
}
void solve(){
    cin>>n>>k;
    int max_d=0;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    for(int i=1;i<=n;i++){
        int nxt=(i==n ? 1 : i+1);
        max_d=max(max_d,abs(h[i]-h[nxt]));
    }
    int l=0,r=max_d,ans=r;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else l=mid+1;
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