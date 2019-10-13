	#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;

#define lp(var,start,end) for (ll var = start; var <end ; ++var)
#define rlp(var,start,end) for(ll var = start; var>=end ; var--)
#define pb push_back
#define mp make_pair
#define pf push_front
#define ff first
#define ss second
#define vll vector<ll>
#define vld vector<ld>
#define pll pair<ll,ll> 
#define pld pair<ld,ld> 
#define vpll vector<pll>
#define vpld vector<pld>
#define all(X) X.begin(),X.end()
#define endl "\n"
#define sz(x) ((ll)((x).size()))
const ll N=3,inf=1e18;

struct bnode{
	
	ll parent;
	vll val;
	vector<ll> child;
};

vector<bnode> tree;
ll rootnode;
ll splitleaf(ll lnode)
{
	ll half = 2;
	bnode tp;
	ll rnode=tree.size();
	tree.pb(tp);

	tree[rnode].parent=tree[lnode].parent;

	ll p1=half,p2=0;
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

	ll val=tree[rnode].val[0];

	if(tree[lnode].parent==-1)
	{
		bnode tp;
		ll pnode = tree.size();
		tree.pb(tp);
		tree[pnode].parent=-1;
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
		// cout<<tree[lnode].val.size()<<endl;
		// cout<<tree[rnode].val.size()<<endl;	
		ll val1=val;
		ll cnode = tree[lnode].parent;
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

ll splitnode(ll lnode)
{
	ll half = (N+1)/2;
	bnode tp;
	ll rnode=tree.size();
	tree.pb(tp);
	tree[rnode].parent=tree[lnode].parent;

	ll p1=half,p2=0;
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
	ll val=tree[rnode].val[0];
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
	if(tree[lnode].parent==-1)
	{
		bnode tp;
		ll pnode = tree.size();
		tree.pb(tp);
		tree[pnode].val.pb(val);
		tree[pnode].parent=-1;
		tree[pnode].child.pb(lnode);
		tree[pnode].child.pb(rnode);
		tree[lnode].parent=pnode;
		tree[rnode].parent=pnode;
		rootnode = pnode;
		return 0;
	}
	else
	{
		ll val1=val;
		ll cnode = tree[lnode].parent;
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

ll insert(ll cnode,ll val)
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

ll print()
{
	queue<pll> q;
	q.push(mp(rootnode,0));
	ll cur=0;
	cout<<0<<endl;
	while(!q.empty())
	{
		pll a = q.front();
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

int main()
{
	// ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	ll n;
	cin >> n;
	ll ary[n];
	rootnode = 0;
	bnode root;  
	root.parent = -1 ;
	tree.pb(root);
	lp(i,0,n)
	{
		cin >> ary[i];
		insert(rootnode,ary[i]);
	}	  
	cerr<<"print"<<endl;
	print();
	cout<<endl;
	return 0;
}