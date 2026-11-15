#include<bits/stdc++.h>

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int>ans;
        for(auto x : asteroids){
            if(x < 0){
                int sz = -x;
                int flag = -1;
                while(!ans.empty() && ans.back() > 0){
                    int last = ans.back();
                    ans.pop_back();
                    if(sz < last){
                        ans.push_back(last);
                        flag = 0;
                        break;
                    }
                    else if(sz == last){
                        flag = 1;
                        break;
                    }
                    else{
                        flag = 2;
                    }
                }
                if(flag == 2 || flag == -1){
                    ans.push_back(x);
                }
            }
            else{
                ans.push_back(x);
            }
        }
        return ans;
    }
};