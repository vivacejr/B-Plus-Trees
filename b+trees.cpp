#include<bits/stdc++.h>
using namespace std;
// typedef long long int in;
typedef long double ld;

#define lp(var,start,end) for (int var = start; var <end ; ++var)
#define rlp(var,start,end) for(int var = start; var>=end ; var--)
#define pb push_back
#define mp make_pair
#define pf push_front
#define ff first
#define ss second
#define vint vector<int>
#define vld vector<ld>
#define pint pair<int,int> 
#define pld pair<ld,ld> 
#define vpint vector<pint>
#define vpld vector<pld>
#define aint(X) X.begin(),X.end()
#define endl "\n"
#define sz(x) ((int)((x).size()))
const int N=3,inf=1e9;

struct bnode{
	
	int parent;
	vint val;
	vector<int> child;
	int right;
};

vector<bnode> tree;
int rootnode;
int splitleaf(int lnode)
{
	int half = 2;
	bnode tp;
	int rnode=tree.size();
	tree.pb(tp);

	tree[rnode].parent=tree[lnode].parent;

	int p1=half,p2=0;
	while(p1<=N)
	{
		// cout<<tree[lnode].val[p1]<<"yo"<<endl;
		tree[rnode].val.pb(tree[lnode].val[p1]);
		p1++;
	}
	p1=half,p2=0;
	while(p1<=N)
	{
		tree[lnode].val.pop_back();
		p1++;	
	}
	tree[rnode].right=tree[lnode].right;
	tree[lnode].right=rnode;
	int val=tree[rnode].val[0];

	if(tree[lnode].parent==-1)
	{
		bnode tp;
		int pnode = tree.size();
		tree.pb(tp);
		tree[pnode].parent=-1;
		tree[pnode].right=-1;
		tree[pnode].val.pb(val);
		tree[pnode].child.pb(lnode);
		tree[pnode].child.pb(rnode);
		tree[lnode].parent=pnode;
		tree[rnode].parent=pnode;
		rootnode = pnode;
		return 0;
	}
	else
	{
		int val1=val;
		int cnode = tree[lnode].parent;
		// cout<<cnode<<endl;
		lp(i,0,tree[cnode].val.size())
		{
			// cout<<tree[cnode].val[i]<<"yo"<<endl;
			if(val < tree[cnode].val[i])
			{	
				swap(tree[cnode].val[i], val);
			}
		}
		// cout<<val<<endl;
		tree[cnode].val.pb(val);
		lp(i,0,tree[cnode].val.size())
		{
			if(val1 < tree[tree[cnode].child[i]].val[0])
			{
				swap(rnode,tree[cnode].child[i]);
			}
		}

		tree[cnode].child.pb(rnode);
		// cout<<tree[cnode].child.size()<<endl;
		lp(i,0,tree[cnode].child.size())
		{
			tree[tree[cnode].child[i]].parent=cnode;
		}
		// <<1<<endl;
	}
}

int splitnode(int lnode)
{
	int half = (N+1)/2;
	bnode tp;
	int rnode=tree.size();
	tree.pb(tp);
	tree[rnode].parent=tree[lnode].parent;

	int p1=half,p2=0;
	while(p1<=N)
	{
		tree[rnode].val.pb(tree[lnode].val[p1]);
		tree[rnode].child.pb(tree[lnode].child[p1]);
		p1++;
		p2++;
	}
	tree[rnode].child.pb(tree[lnode].child[p1]);

	p1=half,p2=0;
	while(p1<=N)
	{
		tree[lnode].val.pop_back();
		tree[lnode].child.pop_back();
		p1++;
		p2++;	
	}
	// cerr<<1<<endl;
	int val=tree[rnode].val[0];
	lp(i,0,tree[rnode].val.size())
	{
		if(tree[rnode].val.size()!=i)
			tree[rnode].val[i]=tree[rnode].val[i+1];
		tree[rnode].child[i]=tree[rnode].child[i+1];
	}
	tree[rnode].val.pop_back();
	tree[rnode].child.pop_back();

	lp(i,0,tree[lnode].child.size())
	{
		tree[tree[lnode].child[i]].parent=lnode;
	}
	lp(i,0,tree[rnode].child.size())
	{
		tree[tree[rnode].child[i]].parent=rnode;
	}
	tree[rnode].right=tree[lnode].right;
	tree[lnode].right=rnode;
	if(tree[lnode].parent==-1)
	{
		bnode tp;
		int pnode = tree.size();
		tree.pb(tp);

		tree[pnode].val.pb(val);
		tree[pnode].parent=-1;
		tree[pnode].right=-1;
		tree[pnode].child.pb(lnode);
		tree[pnode].child.pb(rnode);
		tree[lnode].parent=pnode;
		tree[rnode].parent=pnode;
		rootnode = pnode;
		return 0;
	}
	else
	{
		int val1=val;
		int cnode = tree[lnode].parent;
		lp(i,0,tree[cnode].val.size())
		{
			if(val < tree[cnode].val[i])
			{	
				swap(tree[cnode].val[i], val);
			}
		}
		tree[cnode].val.pb(val);
		lp(i,0,tree[cnode].val.size())
		{
			if(val1 < tree[tree[cnode].child[i]].val[0])
			{
				swap(rnode,tree[cnode].child[i]);
			}
		}
		tree[cnode].child.pb(rnode);
		lp(i,0,tree[cnode].child.size())
		{
			tree[tree[cnode].child[i]].parent=cnode;
		}
	}
}

int insert(int cnode,int val)
{
	// if(tree[cnode].val.size()>0)
		// cout<<cnode<<" "<<tree[cnode].val[0]<<" "<<tree[cnode].parent<<endl;
	lp(i,0,tree[cnode].val.size()+1)
	{
		if(	( i==tree[cnode].val.size()  || val < tree[cnode].val[i]) && tree[cnode].child.size() > i) 
		{
			insert(tree[cnode].child[i], val);
			if(tree[cnode].val.size()==N+1)
			{
				splitnode(cnode);
			}
			return 0;
		}
		else if((i==tree[cnode].val.size()||val < tree[cnode].val[i]))
		{
			if(i==tree[cnode].val.size())
				break;
			swap(tree[cnode].val[i],val);
		}			
	}		
	tree[cnode].val.pb(val);

	if(tree[cnode].val.size()==N+1)
	{
		// cerr<<val<<endl;
		splitleaf(cnode);
	}
}

void find(int cnode,int val)
{
	if(tree[cnode].child.size()==0)
	{
		lp(i,0,tree[cnode].val.size())
		{
			if(tree[cnode].val[i]==val)
			{
				cout<<"YES"<<endl;
				return ;
			}		
		}
		cout<<"NO"<<endl;
		return ;
	}
	lp(i,0,tree[cnode].val.size()+1)
	{
		if(	( i==tree[cnode].val.size()  || val < tree[cnode].val[i]) && tree[cnode].child.size() > i) 
		{
			find(tree[cnode].child[i], val);
			return ;
		}
	}
}

int cnt(int cnode, int x, int y)
{
	int val=x-1;
	if(tree[cnode].child.size()==0)
	{
		int c=0;
		while(cnode!=-1)
		{
			int f=0;
			lp(i,0,tree[cnode].val.size())
			{
				if(tree[cnode].val[i]>y)
				{
					return c;
				}
				else if(tree[cnode].val[i]>=x)
				{
					c++;
				}
			}
			cnode=tree[cnode].right;
		}
		return c;
	}
	lp(i,0,tree[cnode].val.size()+1)
	{
		if(	( i==tree[cnode].val.size()  || val < tree[cnode].val[i]) && tree[cnode].child.size() > i) 
		{
			return cnt(tree[cnode].child[i],x,y);
		}
	}	
}


int print()
{
	queue<pint> q;
	q.push(mp(rootnode,0));
	int cur=0;
	cout<<0<<endl;
	while(!q.empty())
	{
		pint a = q.front();
		// cout<<a.ff<<endl;
		q.pop();
		if(a.ss>cur)
		{
			cur=a.ss;
			cout<<endl<<a.ss<<endl;
		}
		cout<<"[";
		lp(i,0,tree[a.ff].val.size())
		{
			cout<<tree[a.ff].val[i]<<" ";
		}	
		cout<<"]";
		lp(i,0,tree[a.ff].child.size())
		{
			q.push(mp(tree[a.ff].child[i],a.ss+1));
		}
	}		
}
inline pair<int, pair<int,int> > parse(char query[])
{
	vector<string> vec;
	string s;
	istringstream iss(query);
	while(getline(iss, s, ' ')) vec.pb(s);
	if(vec[0] == "INSERT") return mp(0, mp(stoi(vec[1]),-1));
	else if(vec[0] == "FIND") return mp(1, mp(stoi(vec[1]),-1));
	else if(vec[0] == "COUNT") return mp(2, mp(stoi(vec[1]),-1));
	else return mp(3, mp(stoi(vec[1]), stoi(vec[2])));
}
int main(int argc, char ** argv)
{
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	bnode tp;
	tp.parent=-1;
	tp.right=-1;
	rootnode=0;
	tree.pb(tp);
	string file = argv[1];
	ifstream in(file);
	// cerr<<file<<endl;
	if(!in)
	{
		cout<<"F"<<endl;
		return 0;
	}
	char query[255];
	while(in)
	{
		int ans=0;
		in.getline(query, 255);
		// cerr<<query<<endl;	
		if(!in) break;
		pair<int, pair<int,int> > res = parse(query);
		// cerr<<1<<endl;
		if(res.first == 0) insert(rootnode, res.ss.ff);
		else if(res.ff == 1)
		{
			find(rootnode, res.ss.ff);
		}
		else if(res.ff == 2)
		{
			cout<<cnt(rootnode, res.ss.ff, res.ss.ff)<<endl;
		}
		else
		{
			cout<<cnt(rootnode, res.ss.ff, res.ss.ss)<<endl;
		}
	}
	return 0;
}