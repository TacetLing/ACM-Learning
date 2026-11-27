#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=100005;
constexpr int LOGN=19;
constexpr int INF=1e18;
int n,m,dp[MAXN],suf_max[MAXN],suf_min_dp[MAXN];
int st[MAXN][LOGN];
int lg2[MAXN];
int arr[MAXN];
int b[MAXN];
void precompute(){
    lg2[1]=0;
    for(int i=2;i<MAXN;i++){
        lg2[i]=lg2[i/2]+1;
    }
    return;
}
int mk[MAXN];
void calc(int l,int r){
    for(int i=l;i<=r;i++){
        st[i][0]=mk[i];
    }
    for(int j=1;(1<<j)<=r-l+1;j++){
        for(int i=l;i+(1<<j)-1<=r;i++){
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
    return;
}
int query(int L,int R){
    int k=lg2[R-L+1];
    return min(st[L][k],st[R-(1<<k)+1][k]);
}
void cdq(int l,int r){
    if(l>=r) return;
    int mid=(l+r)>>1;
    cdq(l,mid);
    suf_max[mid]=0;
    mk[mid]=dp[mid];
    suf_min_dp[mid]=dp[mid];
    for(int j=mid-1;j>=l;j--){
        suf_max[j]=max(suf_max[j+1],arr[j+1]);
        suf_min_dp[j]=min(suf_min_dp[j+1],dp[j]);
        mk[j]=dp[j]+suf_max[j];
    }
    calc(l,mid);
    int cur_pre_max=0;
    int p=l-1;
    for(int i=mid+1;i<=r;i++){
        cur_pre_max=max(cur_pre_max,arr[i]);
        auto it=upper_bound(suf_max+l,suf_max+mid+1,cur_pre_max,greater<int>());
        p=it-suf_max-1;
        int ql=max(l,b[i]);
        int qr=p;
        if(ql<=qr){
            dp[i]=min(dp[i],query(ql,qr));
        }
        int low=max({l,b[i],p+1});
        if(low<=mid){
            dp[i]=min(dp[i],suf_min_dp[low]+cur_pre_max);
        }
    }
    cdq(mid+1,r);
    return;
}
void solve(){
    cin>>n>>m;
    int sum=0,j=0;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum+=arr[i];
        while(sum>m){
            sum-=arr[++j];
        }
        b[i]=j;
        dp[i]=INF;
    }
    dp[0]=0;
    precompute();
    cdq(0,n);
    cout<<dp[n]<<'\n';
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
