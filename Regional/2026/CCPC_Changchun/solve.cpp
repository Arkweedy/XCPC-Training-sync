#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

void solve()
{
    string s;
    cin >> s;
    vector<int>st;
    // 0 -> 1
    // 1 -> odd 0
    // 2 -> even 0

    // 1 + 1 -> 0
    // 0 + 0 -> 00
    // 1 00 + 1 -> 1


    for(auto ch : s){
        int x = ch - '0';
        int opc = x;
        top : 
        switch (opc)
        {
        case 0 :
            if(st.empty())st.push_back(1);
            else if(st.back() == 0)st.push_back(1);
            else if(st.back() == 1){
                st.pop_back();
                st.push_back(2);
            }
            else {
                ;
            }
            break;
        case 1 :
            if(st.empty())st.push_back(0);
            else if(st.back() == 0){
                st.pop_back();
                opc = 0;
                goto top;
            }
            else if(st.back() == 1){
                st.push_back(0);
            }
            else {//2
                st.pop_back();
                if(st.empty()){
                    st.push_back(2);
                    st.push_back(0);
                }
                else if(st.back() == 0){
                    st.pop_back();
                    opc = 0;
                    goto top;
                }
                else {
                    assert(0);
                }
            }
            break;
        }
    }

    int ans = st.size();
    cout << ans << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}