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

ll splitnode(ll cnode)
{

}

ll splitleaf(ll lnode)
{
	ll half = N/2;
	bnode tp;
	ll rnode=tree.size();
	tree.pb(tp);
	tree[rnode].parent=tree[lnode].parent;

	ll p1=half,p2=0;
	while(p1<N)
	{
		tree[rnode].val.pb(tree[lnode].val[p1]);
		tree[rnode].child.pb(tree[lnode].child[p1]);
	}
	p1=half,p2=0;
	while(p1<N)
	{
		tree[lnode].val.pop_back();
		if(p1!=half)
			tree[lnode].child.pop_back();
	}
	ll val=tree[rnode].val[0];
	
		
}

ll insert(ll cnode,ll val)
{
	ll flag=0;
	lp(i,0,tree[cnode].val.size())
	{
		if(val < tree[cnode].val[i] && tree[cnode].child.size() > i )
		{
			insert(tree[cnode].child[i], val);
			if(tree[cnode].val.size()==N)
			{
				splitnode(cnode);
			}
			return 0;
		}
		else if(val < tree[cnode].val[i])
		{
			swap(tree[cnode].val[i],val);
			flag=1;
		}			
	}		
	if(!flag)
	{
		tree[cnode].val.pb(val);
	}

	if(tree[cnode].val.size()==N+1)
	{
		splitleaf(cnode);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	ll n;
	cin >> n;
	ll ary[n];
	bnode root;  
	tree.pb(root);
	lp(i,0,n)
	{
		cin >> ary[i];
		insert(0,ary[i]);
	}	  
	return 0;
}