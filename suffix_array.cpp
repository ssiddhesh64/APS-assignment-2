#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

vector<int> find_suffix(char* str);

struct suffix_node{
    int index;
    int rank;
    int next_rank;
};

int comp(struct suffix_node a, struct suffix_node b){
    //return (a.rank == b.rank) ? (a.next_rank < b.next_rank ? 1 : 0) : (a.rank < b.rank ? 1 : 0);

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


int find_suffix(string str1){

    string str = str1 + str1;
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

    // for(int i = 0; i < n ; i++){

    //     cout << suffix[i].index << " " << suffix[i].rank << " " << suffix[i].next_rank << endl;
    // }

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

    //cout << "111" << endl;

    vector<int> ans(n);

    for(int i = 0; i < n; i++){
        ans[i] = suffix[i].index;
        //cout << ans[i] << " ";
    }

    //cout << endl;

    //int min_index = 0;
    //int min_val;

    if(ans[0] < str.length()){
        return ans[0];
    }
    else{
        return ans[0]-str.length();
    }

    // for(int i = 1; i < str.length(); i++){
    //     if(ans[i] < min_val){
    //         min_val = ans[i];
    //         if(ans[i] < str.length()){
    //             min_index = ans[i];
    //         }
    //         else{
    //             min_index = ans[i] - str.length();
    //         }
    //     }
    // }
    //return min_index;
}

int main(){


    string str;
    cin >> str;
    int index = find_suffix(str);

    int count = 0;
    int i = index;
    while(count < str.length()){
        cout << str[i%str.length()];
        i++;
        count++;
    }
    cout << endl;

    return 0;
}
