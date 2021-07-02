#include <iostream>

using namespace std;

void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

void reverse_array(int* array, int offset, int length){
    array += offset;
    int mid = length/2;
    for(int i = 0; i < mid; i++){
        swap(array[i], array[length-1-i]);
    }
}

int bin_search(int const* a, int* indices, int value, int l, int r){
    if(r-l < 1){
        if(r < l || a[indices[l]] > value)
            return l-1;
        else
            return l;
    }

    int m = (l+r)/2;
    if(a[indices[m]] > value)
        return bin_search(a, indices, value, l, m);
    else
        return bin_search(a, indices, value, m+1, r);
}

void solve(int n, int const* a, int* before, int* indices){
    indices[0] = 0;
    for(int i = 1; i <= n; i++){
        indices[i] = -1;
    }

    int length = 0;
    for(int i = 1; i <= n; i++){

        int j = bin_search(a, indices, a[i], 1, length);
        int& nextIndex = indices[j+1];
        if(nextIndex == -1 || a[nextIndex] > a[i]){
            nextIndex = i;
            before[i] = indices[j];
            if(j + 1 > length){
                length = j + 1;
            }
        }
    }

    std::cout << length << "\n";
    int answer_array[length];
    int index = indices[length];
    for(int i = 0; i < length; i++){
        answer_array[i] = a[index];
        index = before[index];
    }
    reverse_array(answer_array, 0, length);
    for(int i = 0; i < length; i++){
        std::cout << answer_array[i] << " ";
    }
}

int main(){
    int n;
    cin >> n;
    int* a = new int[n+5];
    int* before = new int[n+5];
    int* indices = new int[n+5];

    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    solve(n, a, before, indices);

    return 0;
}