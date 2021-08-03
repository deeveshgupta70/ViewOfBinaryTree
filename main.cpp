#include<bits/stdc++.h>

using namespace std;


#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define F first
#define S second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
// typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}



class binaryTree
{
public:
	int data;
	binaryTree* left;
	binaryTree* right;
	binaryTree(int data){
		this->data = data;
		left = NULL;
		right = NULL;
	}
	~binaryTree(){
		delete left;
		delete right;
	}
	
};

binaryTree* builtTree(){

	int rootData;
	cin>>rootData;
	binaryTree* root = new binaryTree(rootData);

	queue<binaryTree*> node;
	node.push(root);

	while(!node.empty()){

		binaryTree* ptr = node.front();
		node.pop();

		int val;
		cin>>val;

		if( val != -1){
			ptr->left = new binaryTree(val);
			node.push(ptr->left);
		}

		cin>>val;

		if(val != -1){
			ptr->right = new binaryTree(val);
			node.push(ptr->right);
		}

	}

	return root;
}

// Level Order Traversal
void levelOrderTraversal(binaryTree* root){

	if(!root) return;

	queue<binaryTree*> node;

	node.push(root);

	while(!node.empty()){

		int count = node.size();

		while(count--){
			binaryTree* ptr = node.front();
			node.pop();

			cout<<ptr->data<<" ";

			if(ptr->left) node.push(ptr->left);

			if(ptr->right) node.push(ptr->right);
		}
		cout<<"\n";

	} 
}

// Preorder - Traversal
void preorderTraversal(binaryTree* root){

	if(!root) return;

	cout<<root->data<<" ";
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

void topView1(binaryTree* root)
{
	if(!root) return;

	queue<pair<binaryTree*,int>> node;

	int hd = 0;
	int l = 0;
	int r = 0;

	node.push(make_pair(root,hd));

	stack<int> left; // to store the left value;
	vector<int> right; // to store the right value;

	while(node.size()){

		binaryTree* ptr =  node.front().first;
		int hd = node.front().second;
		node.pop();

		if(hd < l){
			left.push(ptr->data);
			l = hd;
		}
		else if( hd > r){
			right.push_back(ptr->data);
			r = hd;
		}

		if(ptr->left) {
			node.push(make_pair(ptr->left,hd-1));
		}

		if(ptr->right){
			node.push(make_pair(ptr->right,hd+1));
		}

	}

	vector<int> res;
	while(left.size()){ // left Portion
		res.push_back(left.top());
		left.pop();
	}
	res.push_back(root->data); // middle portion

	res.insert(res.end(),right.begin(),right.end()); // right Portion

	for(auto i : res){
		cout<<i<<" ";
	}
}

////Give Top View 
void fillMapTop( binaryTree* root, int d, int  l , map<int, pair<int, int> >& mt){

	if(!root) return ;

	if (mt.count(d) == 0) {
		mt[d] = make_pair(root->data, l);
	}
	else if( mt[d].second > l){
		mt[d] = make_pair(root->data,l);
	}

	fillMapTop(root->left,d-1,l+1,mt);
	fillMapTop(root->right,d+1,l+1,mt);
}

/// Give Bottom View 
void fillMapBottom( binaryTree* root, int d, int  l , map<int, pair<int, int> >& mt){

	if(!root) return ;

	if( mt[d].second <= l){
		mt[d] = make_pair(root->data,l);
	}

	fillMapBottom(root->left,d-1,l+1,mt);
	fillMapBottom(root->right,d+1,l+1,mt);
}

void topView2(binaryTree* root){

	map <int,pair<int,int>> mt;
	map< int, pair<int,int> > mb;

	fillMapTop(root,0,0,mt);
	fillMapBottom(root,0,0,mb);


	cout<<" \n Top View :";
	for( auto i : mt){
		cout<< i.second.first <<" ";
	}
	cout<<" \n Bottom View :";
	for( auto i : mb){
		cout<< i.second.first <<" ";
	}
}

//// Left and Right View Of binary Tree
void getView( binaryTree* root){

	if(!root) return;

	vector<int> left;
	vector<int> right;

	queue<binaryTree*> node;
	node.push(root);
	while(node.size() )
	{

		int count = node.size();

		for( int i = 1 ; i <= count ; i++){

			binaryTree* ptr = node.front();
			node.pop();

			if( i == 1){
				left.push_back(ptr->data);
			}
			if( i == count){
				right.push_back(ptr->data);
			}

			if(ptr->left) node.push(ptr->left);

			if(ptr->right) node.push(ptr->right);
		}
	}

	cout<<"\n Left View :";
	for(auto i : left){
		cout<<i<<" ";
	}
	cout<<"\n right View :";
	for(auto i : right){
		cout<<i<<" ";
	}
}

    
int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
 
  	binaryTree* root  = builtTree();

	cout<<"\n Level Order Traversal :\n ";
  	levelOrderTraversal(root);

  	cout<<"\nTop View of Binary Tree 1:";
  	topView1(root);

  	cout<<"\nView of Binary Tree :";
  	topView2(root);

  	cout<< "\n \nLeft & Right View of Binary Tree \n";
  	getView(root);

	delete root;

return 0;

}


/*
Input1:
1 2 3 4 5 6 7 -1 -1 -1 -1  8 9 -1 -1 -1 -1 -1 -1 -1

Input 2:
1 2 3 -1 4 -1 -1 -1 5 -1 6 -1 -1


output 1:

 Level Order Traversal :
 1 
2 3 
4 5 6 7 
8 9 

Top View of Binary Tree 1:4 2 1 3 7 
View of Binary Tree : 
 Top View :4 2 1 3 7  
 Bottom View :4 8 6 9 7 
 
Left & Right View of Binary Tree 

 Left View :1 2 4 8 
 right View :1 3 7 9

output 2:

 Level Order Traversal :
 1 
2 3 
4 
5 
6 

Top View of Binary Tree 1:2 1 3 6 
View of Binary Tree : 
 Top View :2 1 3 6  
 Bottom View :2 4 5 6 
 
Left & Right View of Binary Tree 

 Left View :1 2 4 5 6 
 right View :1 3 4 5 6 

*/
