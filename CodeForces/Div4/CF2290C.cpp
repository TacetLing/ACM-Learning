#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int> all_x;
int get_idx(int x){
    return lower_bound(all_x.begin(),all_x.end(),x)-all_x.begin();
}
void solve(){
    int n;
    all_x.clear();
    cin>>n;
    vector<int> h(n+5,0);
    for(int i=1;i<=n;i++){
        cin>>h[i];
        all_x.push_back(h[i]);
    }
    sort(all_x.begin(),all_x.end());
    all_x.erase(unique(all_x.begin(),all_x.end()),all_x.end());
    int sz=all_x.size();
    vector<int> cnt(sz+5,0);
    vector<int> pre;
    vector<int> suf;
    for(int i=1;i<=n;i++){
        cnt[get_idx(h[i])]++;
    }
    int ans=0;
    for(int i=0;i<=sz;i++){
        ans+=min(2LL,cnt[i]);
        if(cnt[i]==1){
            pre.push_back(all_x[i]);
        }
        else if(cnt[i]==2){
            pre.push_back(all_x[i]);
            suf.push_back(all_x[i]);
        }
        else if(cnt[i]==0){
            continue;
        }
        else{
            pre.push_back(all_x[i]);
            for(int j=1;j<=cnt[i]-1;j++){
                suf.push_back(all_x[i]);
            }
        }
    }
    cout<<ans<<'\n';
    for(auto e : pre){
        cout<<e<<' ';
    }
    reverse(suf.begin(),suf.end());
    for(auto e : suf){
        cout<<e<<' ';
    }
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