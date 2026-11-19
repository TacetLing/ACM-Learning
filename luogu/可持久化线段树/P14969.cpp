#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MAXN=500005;
int limit;
vector<int> tree_1,tree_2;
int lowbit(int x){
    return x&-x;
}
void add(int x,int val,vector<int> &tree){
    for(;x<=limit;x+=lowbit(x)){
        tree[x]+=val;
    }
    return;
}
int query(int x,vector<int> &tree){
    if(x<=0) return 0;
    int res=0;
    for(;x>0;x-=lowbit(x)){
        res+=tree[x];
    }
    return res;
}
struct node{
    int l,r,x;
    bool operator<(const node&other) const{
        return x>other.x;
    }
};
struct point{
    int val,id;
    bool operator<(const point&other) const{
        return val<other.val;
    }
};
int n;
vector<int> adj[MAXN<<1];
void solve(){
    cin>>n;
    limit=n;
    int total=0;
    tree_1.assign(n+5,0);
    tree_2.assign(n+5,0);
    vector<point> arr(n+5,{0,0});
    for(int i=1;i<=n;i++){
        cin>>arr[i].val;
        arr[i].id=i;
        total+=arr[i].val;
        adj[arr[i].val].push_back(i);
    }
    sort(arr.begin()+1,arr.begin()+n+1);
    vector<node> qrys;
    for(int e=0;e<=n;e++){
        int last=0;
        for(int pos : adj[e]){
            if(last+1<=pos-1){
                qrys.push_back({last+1,pos-1,e});
            }
            last=pos;
        }
        if(last+1<=n){
            qrys.push_back({last+1,n,e});
        }
    }
    sort(qrys.begin(),qrys.end());
    int curr=n;
    int ans=0;
    for(auto q : qrys){
        while(curr>=1 && arr[curr].val>q.x){
            add(arr[curr].id,1,tree_1);
            add(arr[curr].id,arr[curr].val,tree_2);
            curr--;
        }
        int cnt=query(q.r,tree_1)-query(q.l-1,tree_1);
        int sum=query(q.r,tree_2)-query(q.l-1,tree_2);
        ans=max(ans,sum-q.x*cnt);
    }
    cout<<total-ans<<'\n';
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}