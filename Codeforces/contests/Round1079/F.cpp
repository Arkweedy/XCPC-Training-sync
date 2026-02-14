#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.02.12 00:28

// matched 不管
// 剩下的一定是 ）））（（（ +  ]]] [[[
// 1步1对 / 2步1对


void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int>ar, br;
    vector<int>pa, pb;
    for(int i = 0;i < n;i++){
        if(s[i] == '(')pa.push_back(i);
        else if(s[i] == '[')pb.push_back(i);
        else if(s[i] == ')'){
            if(!pa.empty())pa.pop_back();
            else ar.push_back(i);
        }
        else if(s[i] == ']'){
            if(!pb.empty())pb.pop_back();
            else br.push_back(i);
        }
    }
    int sum = pa.size() / 2 + pb.size() / 2 + ar.size() / 2 + br.size() / 2;
    int ra = pa.size() % 2, rb = pb.size() % 2, rc = ar.size() % 2, rd = br.size() % 2;
    if(ra && rb && rc && rd){
        sum += 2;
    }
    else if((ra && rb) || (rc && rd)){
        sum++;
    }
    else if(ra + rb + rc + rd == 2){
        int l = -1 ,r = n + 1;
        if(!ar.empty()) l = max(l, ar.back());
        if(!br.empty()) l = max(l, br.back());
        if(!pa.empty()) r = min(r, pa[0]);
        if(!pb.empty()) r = min(r, pb[0]);
        //cerr << l << " " << r << endl;
        if(l > r)sum ++;
        else sum += 2;
    }
    cout << sum << endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}