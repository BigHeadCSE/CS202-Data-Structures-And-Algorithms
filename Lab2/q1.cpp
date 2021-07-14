#include<iostream>

using namespace std;

//Structure for storing starting and the finishing time .
struct movie{
	int start;
	int finish;
};


//Merge function of the merge sort

void merge(movie arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    movie L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i].finish <= R[j].finish)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(movie arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids
        // overflow for large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Function to print an array
void printArray(movie A[], int size)
{
    for(int i = 0; i < size; i++)
        cout << A[i].start << " "<<A[i].finish<<endl;
}

// Main Function

//Taking input from the file ('./input-file/coding-question-a.txt')

int main(){
	freopen("input-file/coding-question-a.txt", "r", stdin);

	int t=6;           //t is hardcoded as the no. of test cases present in the file as value of t is not given in the file.
	while(t--){
		int n;
		cin>>n;
		movie arr[n];

		int flag=0;
		for(int i=0;i<n;i++){
			cin>>arr[i].start>>arr[i].finish;
			if(arr[i].start <0 || arr[i].finish >24){
				flag=1;
			}
		}

		if(flag){
			cout<<"--->Dropping one test case here due to wrong values.\n";
			continue;
		}
		mergeSort(arr,0,n-1);   // Sorting the array according to the finish time in ascending order.

		int count=1;			// Counter for the number of elements.
		int cnt[n];				// Storing the index of the qualified movie.
		cnt[0]=0;
		int cur=0;
		for(int i=1;i<n;i++){
			if(arr[i].start>=arr[cur].finish){
				cnt[count]=i;
				cur=i;
				count++;
			}
		}
		cout<<"Maximum no. of movies: "<<count<<"\n";
		for(int i=0;i<count;i++){
			cout<<arr[cnt[i]].start<<" "<<arr[cnt[i]].finish<<endl;
		}
	}
}
