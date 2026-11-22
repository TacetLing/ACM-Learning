#include<bits/stdc++.h>
using namespace std;
//#define int long long
constexpr int MAXN=100005;
int arr[MAXN];
struct node{
    int ls,rs,sum;
}tree[MAXN*23];
int root[MAXN],tot;
vector<int> all_x;
void update(int &cur,int prev,int l,int r,int val){
    cur=++tot;
    tree[cur]=tree[prev];
    tree[cur].sum++;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(val<=mid) update(tree[cur].ls,tree[prev].ls,l,mid,val);
    else update(tree[cur].rs,tree[prev].rs,mid+1,r,val);
    return;
}
int query(int u,int v,int l,int r,int val){
    if(all_x[r]<=val) return tree[u].sum-tree[v].sum;
    if(all_x[l]>val) return 0;
    int mid=(l+r)>>1;
    int res=0;
    res+=query(tree[u].ls,tree[v].ls,l,mid,val)+query(tree[u].rs,tree[v].rs,mid+1,r,val);
    return res;
}
int n;
stack<int> st;
int lf[MAXN],rg[MAXN];
int get_idx(int x){
    return lower_bound(all_x.begin(),all_x.end(),x)-all_x.begin();
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>arr[i],all_x.push_back(arr[i]);
    sort(all_x.begin(),all_x.end());
    all_x.erase(unique(all_x.begin(),all_x.end()),all_x.end());
    for(int i=1;i<=n;i++){
        while(!st.empty() && arr[st.top()]<arr[i]){
            st.pop();
        }
        if(st.empty()) lf[i]=0;
        else lf[i]=st.top();
        st.push(i);
    }
    while(!st.empty()) st.pop();
    for(int i=n;i>=1;i--){
        while(!st.empty() && arr[st.top()]<=arr[i]){
            st.pop();
        }
        if(st.empty()) rg[i]=n+1;
        else rg[i]=st.top();
        st.push(i);
    }
    int sz=all_x.size();
    for(int i=1;i<=n;i++){
        update(root[i],root[i-1],0,sz-1,get_idx(arr[i]));
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        int L=lf[i]+1,R=rg[i]-1;
        if(i-L<=R-i){
            for(int j=L;j<=i;j++){
                int target=arr[i]/arr[j];
                ans+=query(root[R],root[i-1],0,sz-1,target);
            }
        }
        else{
            for(int j=i;j<=R;j++){
                int target=arr[i]/arr[j];
                ans+=query(root[i],root[L-1],0,sz-1,target);
            }
        }
    }
    cout<<ans<<'\n';
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}