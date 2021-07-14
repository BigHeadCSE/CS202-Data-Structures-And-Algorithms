#include<iostream>

using namespace std;

// taking input from the file ('./input-file/coding-question-b.txt')


int main(){
	//freopen("input-file/coding-question-b.txt", "r", stdin);

	int n;
	cin>>n;
	int arr[n];

	for(int i=0;i<n;i++){
		cin>>arr[i];
	}

    // Using counting sort as all are integers in range [0,1000)
	int count[1001]={0};
	for(int i=0;i<n;i++){
		count[arr[i]]++;
	}
	int cntr=0;
	for(int i=0;i<1001;i++){        // Storing values back in the given array .
		for(int j=0;j<count[i];j++){
			arr[cntr]=i;
			cntr++;
		}
	}

	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;

}
