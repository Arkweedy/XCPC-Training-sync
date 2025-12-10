#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m,c;
    cin>>n>>m>>c;
    vector<int>cnt(m + 1);
    int ma = 0;
    for(int i = 0;i < n;i++){
        int x;
        cin>>x;
        cnt[x]++;
        ma = max(ma, x);
    }

    vector<pair<int,int>>pr;
    for(int i = 0;i <= m;i++){
        if(cnt[i] != 0){
            pr.emplace_back(i,cnt[i]);
        }
    }

    int x = n / c;
    int ok = count(cnt.begin(),cnt.end(), x);
    int macnt = *max_element(cnt.begin(),cnt.end());
    if(ok == c){
        cout<<-1<<endl;
        return;
    }
    if(macnt > x){
        cout<<0<<endl;
        return;
    }

    //check range : [c, ma]
    //neg : cnt mod k > x || unique cnt < c || unique cnt > c || cnt mod k < x
    //if k -> unique cnt > c  --> pk unique cnt > c // case 1
    //if k -> cnt mod k < x --> pk cnt mod k < x // case 2
    //case 1 and case 2 ??? 
    //other cases ? 
    //if k is ok --> for all a = b \mod k, x * gcd(a, b), x \geq 2 neg
    //--> how to check ?  
    
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(pr.begin(),pr.end(),g);

    vector<int>isok(ma + 1, 1);

    auto check = [&](int k)->void
    {
        //cerr<<"check "<<k<<endl;
        vector<int>mc(k + 1);
        vector<int>dif;
        int gc = 0;
        
        for(const auto& [i, ci] : pr){
            mc[i % k] += ci;
            if(i % k == 0)gc = gcd(gc, i);
            if(mc[i % k] == ci){
                dif.push_back(i % k);
            }
            if(dif.size() > c)break;//maybe check O(c) 
        }
        if(mc[0] > x){
            for(int j = 1;j * k <= gc;j++){
                isok[j * k] = 0;
            }
        }
        for(auto dc : dif){
            if(mc[dc] < x){
                for(int j = 1;j * k <= ma;j++){
                    isok[j * k] = 0;
                }
                break;
            }
            else if(mc[dc] > x){
                isok[k] = 0;
            }
        }
        return;
    };

    vector<int>ans;
    for(int i = c;i <= ma;i++){
        if(isok[i])check(i);
        if(isok[i])ans.push_back(i);
    }

    cout<<ans.size()<<" ";
    for(auto a : ans){
        cout<<a<<" ";
    }
    cout<<"\n";
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