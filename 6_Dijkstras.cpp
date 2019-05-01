
// Single source shortest Path Algorithm
// Note - Graph indices start from 1 not 0

#include <iostream>
#include<string.h>
#define MAX 10

using namespace std;


class djs
{
	public:
	int i, j, k, a, b, u, v, n, ne;
	int min, mincost, cost[MAX][MAX], process[MAX]; 
	void shortestpath(int ,int);
	void displayGraph();
	void create();
	djs() {
		//initialize cost[][]		
		for (int i = 1; i <= MAX; i++)
			for(int j = 1; j <= MAX; j++)
			cost[i][j]=999;		
	}//constructor
};

void djs :: create()
{
	int ch, wt;
	cout<<"No. of Vertices in a graph ::  ";
	cin>>n;

	for (int i = 1; i< n; i++)//Vertices/Nodes
	 {
		for(int j = i+1; j <= n; j++)//Adjacency nodes
		{
			cout<<"Does edge is present between "<< i <<" and " <<j<<"?(1/0)- ";
			cin >> ch;
			if(ch==1) {
				cout << " Enter the weight? ";
				cin >> wt;
				cost[i][j] = cost[j][i] = wt;
			}
			
		}//inner for -j
	}//outer for - i
}//create

void djs::displayGraph(){
	int i,j;
	cout << "The entered Graph is : \n";
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			cout << "\t" << cost[i][j];
		}
		cout << "\n";
	}

}//display Graph

void djs:: shortestpath(int s,int t) 
{
	int newdist,dist[MAX],processed[MAX],preced[MAX],curr,i,k,dc,smalldist;
	int p,j=0;  //for path
	int path[MAX];

	for(i=1;i<=n;i++) //initialize
	{           
		processed[i]=preced[i]=0;  
		dist[i]=999;      //initialise distance to infinity
	}

	processed[s]=1;          //start from source
	dist[s]=0;
	curr=s;

	//WHILE LOOP OF SHORTEST PATH STARTS HERE
	while(curr!=t) {       //till not at destination
		smalldist=999;
		dc=dist[curr];  //distance of current node-dc

		for(i=1;i<=n;i++) //scan all vertices for finding shortest distance from curr
		{
			if(processed[i]==0){
				newdist=dc+cost[curr][i]; 

				if(newdist < dist[i]) {
					dist[i]=newdist;
					preced[i]=curr;
				}
				if(dist[i] < smalldist){
					smalldist=dist[i];
					k=i;
				}
			}//end of if not processed
		}//end of for

		curr=k;
		processed[curr]=1;
	}//end of while loop of shortest path ENDS HERE

	//FRAME THE PATH OF SHORTEST DISTANCE FROM SOURCE TO DESTINATION
	p = t;
	path[j++] = p;
	while (p != s)
	{
		p = preced[p];
		path[j++] = p;
	}
	cout <<"\n Shortest Path: "; 
	for(i=j-1;i>=0;i--) {
		cout << path[i];
	}

	cout << " Shortest distance : " << dist[t] << "\n";

}//shortest path


int main(){
	int s,t;
	djs obj;  //constructor will be called and initialization are made
	obj.create();
	obj.displayGraph();
	cout << "\n Enter start and target vertices: ";
	cin >> s;
	cin >> t;
	obj.shortestpath(s, t);
	return 0;
}//main


