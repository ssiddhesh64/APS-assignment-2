//Given a strings S determine its longest substring that is also a
//palindrome. In case of multiple solutions, print the lexicographically
//smallest palindrome.

#include <algorithm>

#include <iostream>
#include <stdlib.h>
#include <string>
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


    string first = str1;
    int actuallen = str1.length();
    reverse(str1.begin(), str1.end());
    string str = first + "$" + str1;
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

    int maxi = lcp[0];
    int max_index = 0;
    for(int i = 1; i < n; i++){
        if(lcp[i] > maxi){
            if((ans[i]>actuallen && ans[i+1]<actuallen) || (ans[i]<actuallen && ans[i+1]>actuallen)){
                maxi = lcp[i];
                max_index = i;
            }

        }
    }

    int main_index = ans[max_index];

    for(int i = main_index; i < main_index+maxi; i++){
        cout << str[i];
    }

    return 0;
}

int main(){

    string str;
    cin >> str;
    int index = find_suffix(str);

    return 0;
}
