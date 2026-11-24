#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=200005;
int n,x;
int arr[MAXN];
bool alive[MAXN];
bool check(int k){
    for(int i=1;i<=n;i++) alive[i]=false;
    for(int i=1;i<n;i++){
        if(arr[i+1]-arr[i]<=k){
            alive[i]=true;
            alive[i+1]=true;
        }
    }
    vector<int> rest;
    for(int i=1;i<=n;i++){
        if(!alive[i]) rest.push_back(arr[i]);
    }
    int sz=rest.size();
    int ans=0;
    for(int i=0;i<sz;i++){
        if(i<sz-1 && rest[i+1]-rest[i]<=2*k){
            ans++;
            i++;
        }
        else{
            ans++;
        }
    }
    return ans<=x;
}
void solve(){
    cin>>n>>x;
    for(int i=1;i<=n;i++) cin>>arr[i];
    int l=1,r=1e9,ans=r;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            r=mid-1;
            ans=mid;
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
