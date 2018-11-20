#include <iostream>
#include<climits>
#include<cstdlib>
#include <time.h>
#include <algorithm>

using namespace std;

int partition(int arr[], int lo, int hi);


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// returns random index between lo to hi
int random_index(int lo, int hi){
    int n = hi - lo + 1;
    srand(time(NULL));
    return rand()%n + lo;
}

int kth_smallest(int arr[], int lo, int hi, int k){

    if(k > 0 && hi-lo+1 >= k){                  //  if number of elements in array are more than k
        int pivot = random_index(lo, hi);
        swap(&arr[pivot], &arr[hi]);
        int index = partition(arr, lo, hi);

        if(index-lo==k-1) return arr[index];

        if(index-lo > k-1){
            return kth_smallest(arr, lo, index-1, k);
        }
        else{
            return kth_smallest(arr, index + 1 , hi, k - index + lo - 1);
        }
    }
    return INT_MAX;                             //  if number of elements in array are less than k
}

int partition(int arr[], int lo, int hi){

    int i = lo;
    int pivot = arr[hi];
    for(int j = lo; j < hi; j++){
        if(arr[j] <= pivot){
            swap(&arr[i],&arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[hi]);
    return i;
}


int main(){

    freopen("infile.txt", "r", stdin);

    //int v[1000000];
    int t;
    cin >> t;
    //cout << t;
    int n;
    int k;
    int cnt=0, tie = 0, other = 0;
    while(t--){
        // cout<<"hgchgc";
        cin >> n;
        cin >> k;
        int v[n],b[n];
        for(int i = 0; i < n; i++){
            cin >> v[i];
            b[i]=v[i];
        }
        clock_t t;
        t = clock();
        nth_element(b, b+k-1, b+n);
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        cout << b[k-1];
        printf("Execution time : %f seconds\n", time_taken);

        clock_t a;
        a = clock();
        int index = kth_smallest(v, 0, n-1, k);
        a = clock() - a;
        double tt = ((double)a)/CLOCKS_PER_SEC;
        printf("Execution time : %f seconds\n", tt);
       //cout << "hi";


        cout << index << endl<<endl;

        if(t<a) cnt++;
        if(t==a) tie++;
        if(t>a) other++;



    }
    cout << cnt << endl;
    cout << tie << endl;
    cout << other << endl;

}



