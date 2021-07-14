/*
S Samarth Reddy
B19109
Group 25
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int dfs(vector<pair<int,ll>> Graph[], int parent[], bool visited[], int A, int B, ll maxC){
	if(A == B) return 1;

	visited[A]= true;

    //simple dfs to find if it is possible to go from A to B
	for(int i=0; i< Graph[A].size(); i++ ){
		if( (visited[Graph[A][i].first] ==false) && Graph[A][i].second <=maxC){
			parent[Graph[A][i].first]= A;
			return dfs(Graph, parent, visited, Graph[A][i].first,B, maxC);
		}
	}
	return 0;
}

//printing the path if dfs functions returns 1
void PathPrint(int parent[], int B){
	vector<int> path;
	while(B != -1){
		path.push_back(B);
		B= parent[B];
	}
	for(int i= path.size()-1; i >=0; i--){
		cout<<path[i]<<" ";
	}
}

int main(){
    cout<<"Assuming vertice names are of the form 1,2,3...n\n";

	int n, m;
	cin>>n>>m;

	vector<pair<int,ll>> g[n+1];   // assuming vertice names start from 1 to n
    int parent[n+1];

	for(int i=0; i<m; i++){
		int u, v;
		ll c;
		cin>>u>>v>>c;
		g[u].push_back({ v,c });
		g[v].push_back({ u,c });
	}

	int A, B;                      //starting point and destination
	ll maxC;
	cin>>A>>B>>maxC;

    parent[A]=-1;                   //to identify starting point while printing path

	bool visited[n+1];
	for(int i=0; i<=n; i++){
        visited[i]=false;
	}

	if( dfs(g, parent, visited, A, B, maxC)){
		cout<<"POSSIBLE"<<endl;
		PathPrint(parent, B);
		cout<<endl;
	}
	else cout<<"NOT POSSIBLE"<<endl;


	return 0;
}
