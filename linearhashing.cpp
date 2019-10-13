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
const ll N=3,inf=1e9;

ll BUCKET_CAPACITY =  30;
const double LOAD_FACTOR = 0.75;
/*
    One node or a collection of records 
*/
struct node
{
    vector<ll> v;

    void add(ll val)
    {
        //data.pb(val);
        ll f=0;
        lp(i,0,v.size())
        {
            if(v[i]==val)
            {
                f=1;
                break;
            }
        }
        if(!f)
        {
            lp(i,0,v.size())
            {
                if(val<v[i])
                {   
                    swap(val,v[i]);
                }
            }
            v.pb(val);
        }
    }
    ll check(ll val)
    {
        lp(i,0,v.size())
        {
            if(v[i]==val)
            {
                return 1;
            }
        }
        return 0;
    }
};

struct bnode
{

    vector<node> vb;

    bnode()
    {
        node tp;
        vb.pb(tp);
    }
    ll add(ll val,ll chk=1){
        //Check for every node if values is present
        if(chk)
        {
            lp(i,0,vb.size())
            {
                if(vb[i].check(val))
                {
                    return 1;
                }
            }
        }
        if(vb.size()==0)
        {
            node tp;
            vb.pb(tp);
        }

        if(vb[vb.size()-1].v.size()== BUCKET_CAPACITY)
        {
            node tp;
            vb.pb(tp);
        }
        (vb[vb.size()-1].add(val));
        return 0;
    }
};

struct Table
{
    ll cslot;
    ll tot;
    ll mod;
    vector<bnode> vt;

    //intialises the table with two buckets already present
    Table(){
        mod = 2;
        tot = 0;
        cslot=0;
        vt.pb(bnode());
        vt.pb(bnode());
    }

    void divide()
    {
        vt.pb(bnode());
        if(mod < vt.size())
        {
            mod*=2;
        }

        bnode tp = bnode();
        lp(i,0,vt[cslot].vb.size())
        {
            lp(j,0,vt[cslot].vb[i].v.size())
            {
                ll z=mod-1;
                ll num = (vt[cslot].vb[i].v[j]&(z));

                if( num >= vt.size())
                {
                    num -= (mod/2);
                }
                if(num == cslot)
                {
                    tp.add(vt[cslot].vb[i].v[j],0);
                }
                else 
                {
                    vt[num].add(vt[cslot].vb[i].v[j],0);
                }
            }
        }
        vt[cslot]=tp;
        cslot++;

        if(cslot == (mod/2))
        {
            cslot = 0;
        }
    }

    ll add(ll val)
    {
        ll num = (val&(mod-1));

        if( num >= vt.size())
        {
            num -= (mod/2);
        }
        if(vt[num].add(val))
        {
            return 1;
        }
        tot++;
        if(tot > (((ld)vt.size()*(BUCKET_CAPACITY))*LOAD_FACTOR))
        {
            divide();
        }
        return 0;
    }
};
inline ll parse(char query[])
{
    vector<string> vec;
    string s;
    istringstream iss(query);
    while(getline(iss, s, ' ')) vec.pb(s);
    return stoi(vec[0]);
}




int main(int argc, const char *argv[])
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    Table ds = Table();
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
        ll ans=0;
        in.getline(query, 255);
        if(!in) break;
        ll a =parse(query);
        // ll n;
        // cin >> n;
        // lp(i,0,n)
        // {
            // ll a;
            // cin >> a;
            ll x = ds.add(a);
            if(!x)
            {
                cout<<a<<endl;
            }
        // }

    }
    return 0;
}