#include<bits/stdc++.h>
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        unordered_map<string,vector<string>> m;
        int i;
        for(i=0;i<strs.size();i++)
        {
            string s = strs[i];
            sort(strs[i].begin(),strs[i].end());
            m[strs[i]].push_back(s);
        }
        for(auto &pr:m)
        {
            ans.push_back(pr.second);
        }
        return ans;
    }
};