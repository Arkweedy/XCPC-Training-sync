#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr int B = 500;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int sg(int n);

map<int,int>mp1;


int sg(int n)
{
    if(n == 0 || n == 1)return 0;
    if(mp1.count(n))return mp1[n];
    set<int>buf;
    for(int i=0;i<=n-2;i++){
        buf.insert(sg(i)^sg(n-2-i));
    }

    int res = 0;
    for(int i = 0;i < B;i++){
        if(!buf.count(i)){
            res = i;
            break;
        }
    }

    return mp1[n] = res;
}

//int sg(int n, int m)
//{
//    if(n > m)swap(n, m);
//    if(n == 0)return sg(m);
//}


//int sg(vector<int>a)
//{
//    int n = a.size();
//    vector<int>buf(B);
//    for(int i = 0;i < n;i++){
//        for(int j = i;j < n;j++){
//            if(i != j){
//                for(int x = 1;x <= a[i];x++){
//                    for(int y = 1;y <= a[j];y++){
//                        vector<int>b,c;
//                        if(a[i] - x != 0)b.push_back(a[i] - x);
//                        for(int k = i + 1;k < j;k++){
//                            b.push_back(a[k]);
//                        }
//                        if(y - 1 != 0)b.push_back(y - 1);
//                        if(x - 1 != 0)c.push_back(x - 1);
//                        if(a[j] - y != 0)b.push_back(a[j] - y);
//                        for(int k = j + 1;k != i; k = (k + 1) % n){
//                            c.push_back(a[k]);
//                        }
//                        buf[sg(b,c)] = 1;
//                    }
//                }
//            }
//            else{
//                for(int x = 1;x <= a[i];x++){
//                    for(int y = x + 1;j <= a[i];y++){
//                        vector<int>b,c;
//                        if(x + 1 != y)b.push_back(y - x - 1);
//                        if(x >= 1)c.push_back(x - 1);
//                        if(y )
//                    }
//                }
//            }
//        }
//    }
//}

string bin(int x)
{
    string s;
    for(int i = 0;i < 30;i++){
        if(x >> i & 1){
            s += '1';
        }
        else{
            s += '0';
        }
    }
    while(s.back() == '0')s.pop_back();
    reverse(s.begin(),s.end());
    return s;
}

using ull = unsigned long long;

void solve()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int,int>>seg(m);
    vector<int>b;
    for(int i=0;i<m;i++){
        auto &[x,y]  = seg[i];
        cin>>x>>y;
        if(x>y)swap(x,y);
        b.push_back(x);
        b.push_back(y);
    }
    b.push_back(0);
    b.push_back(n-1);
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    int k = b.size();
    vector<ull>c(k+1);
    for(auto &[x,y]:seg){
        int u = lower_bound(b.begin(),b.end(),x) - b.begin();
        int v = lower_bound(b.begin(),b.end(),y) - b.begin();

        ull val = rng();
        c[u] ^= val;
        c[v] ^= val;
        
    }
    
    map<ull,int>ha;
    if(m==0){
        if(sg(n))cout<<"YES\n";
        else cout<<"NO\n";
    }
    else{
        for(int i=1;i<k;i++)c[i]^=c[i-1];
        //for(int i=0;i<k;i++)cout<<c[i]<<endl;
        
        auto dis = [&](int i,int j){
            if(j>i)return  j - i;
            else return j + n - i;
        };
        
        for(int i=0;i < k;){
            int j = i;
            int len = 0;
            while(c[j%k] == c[i]){
                j = j + 1;
                len += dis(c[i],c[j%k]);
            }
            ha[c[i]] = max(ha[c[i]],len-1);
            i = j;
        }
        int res =0;
        for(auto [_,k]:ha){
            res^=sg(k);
            //cout<<k-1<<endl;
        }
        if(sg(n))cout<<"YES\n";
        else cout<<"NO\n";
    }
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
