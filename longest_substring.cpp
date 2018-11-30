//Given an integer K , print the length of the longest substring that appears
//in the text at least K times.If no such substring exist, print -1.


#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<int> find_suffix(char* str);

struct suffix_node{
    int index;
    int rank;
    int next_rank;
};

int comp(struct suffix_node a, struct suffix_node b){

    if(a.rank == b.rank){
        if(a.next_rank < b.next_rank){
            return 1;
        }
        else return 0;
    }
    else{
        if(a.rank < b.rank){
            return 1;
        }
        else return 0;
    }

}

vector<int> sliding_window_minimum(vector<int> &lcp, int k) {

    vector<int> min_array;

    deque<pair<int, int>> w;
    for (int i = 0; i < lcp.size(); i++) {
        while(w.empty()==false && w.back().first >= lcp[i]){
            w.pop_back();
        }

        w.push_back(make_pair(lcp[i], i));

        while(w.front().second <= i - k){
            w.pop_front();
        }

        min_array.push_back(w.front().first);
        //cout << (window.front().first) << ' ';
    }

    return min_array;
}

vector<int> find_suffix(string str){

    int n = str.length();

    struct suffix_node suffix[n];

    for(int i = 0 ;i < n; i++){
        suffix[i].index = i;
        suffix[i].rank = str[i] - 'a';
        if(i + 1 < n){
            suffix[i].next_rank = str[i+1] - 'a';
        }
        else{
            suffix[i].next_rank = -1;
        }
    }

    sort(suffix, suffix+n, comp);

    vector<int> ind(n);

    for(int k = 4; k < 2*n; k=k*2){

        int r = 0;
        int prev_rank = suffix[0].rank;
        suffix[0].rank = r;
        ind[suffix[0].index] = 0;

        for(int i = 1; i < n; i++){

            if(suffix[i].rank == prev_rank && suffix[i].next_rank == suffix[i-1].next_rank){
                prev_rank = suffix[i].rank;
                suffix[i].rank = r;
            }
            else{
                prev_rank = suffix[i].rank;
                suffix[i].rank = ++r;
            }
            ind[suffix[i].index] = i;
        }

        for(int i = 0; i < n; i++){
            int j = suffix[i].index + k/2;
            if(j < n){
                suffix[i].next_rank = suffix[ind[j]].rank;
            }
            else{
                suffix[i].next_rank = -1;
            }
        }

        sort(suffix, suffix+n, comp);
    }

    vector<int> ans(n);

    for(int i = 0; i < n; i++){
        ans[i] = suffix[i].index;
    }

    vector<int> lcp(n);
    vector<int> r(n);

    for(int i = 0; i < n; i++){
        r[ans[i]]=i;
    }

    for(int i = 0, h=0; i < n; i++){
        if(r[i]==n-1){
            h=0;
            continue;
        }
        int j = ans[r[i]+1];
        while(i+h<n && j+h<n && str[i+h]==str[j+h]){
            h++;
        }

        lcp[r[i]] = h;
        if(h>0) h--;
    }
    return lcp;
}

int main(){

    string str;
    int k;
    cin >> str;
    cin >> k;
    vector<int> lcp = find_suffix(str);

    std::vector<int> minimum;
    minimum = sliding_window_minimum(lcp, k-1);

    int maxi = minimum[0];

    for(int i = 1; i < minimum.size(); i++){
        if(minimum[i] > maxi){
            maxi = minimum[i];
        }
    }

    cout << "Final Answer: " << maxi << endl;

    return 0;
}
