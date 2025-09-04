#include<bits/stdc++.h>
using namespace std;

void WaveForm(vector<vector<int> >matrix, int row, int col){

    for(int j=0; j<col; j++){
        if(j%2==0){
            for(int i=0; i<row; i++){
                cout<< matrix[i][j]<<" ";
            }ṁ
        }
        else{
            for(int i=row-1; i>=0; i--){
                cout<< matrix[i][j]<<" ";
            }
        }
    }
}

int main(){

    int row, col;
    cout << "Enter number of rows and columns: ";
    cin >> row >> col;

    vector<vector<int> >matrix(row,vector<int>(col));

    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            cin>> matrix[i][j];
        }
    }

    WaveForm(matrix, row, col);
    return 0;
}
