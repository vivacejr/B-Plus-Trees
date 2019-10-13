#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define sc(n) scanf("%d",&n)
#define scl(n) scanf("%lld",&n)
#define pr(n) prllf("%d",n)
#define prl(n) prllf("%lld",n)
#define nl prllf("\n")
#define fr(i,n) for(i=0;i<n;i++)
#define rep(i,st,en) for(i=st;i<=en;i++)
#define repv(i,en,st) for(i=en;i>=st;i--)
#define fout cout<<fixed<<setprecision(7)
#define bi(n) __builtin_popcount(n)
#define bil(n) __builtin_popcountll(n)


typedef long long ll;
typedef pair<ll,ll> pii;
const ll N = 100010;
ll mod = 1e9+7;
ll fmod(ll b,ll exp){
    ll res =1;
    while(exp){if(exp&1ll)res=(res*b)%mod;
    b =(b*b)%mod;exp/=2ll;
    }
    return res;
}

ll BUCKET_CAPACITY =  30;
const double LOAD_FACTOR = 0.75;
/*
    One node or a collection of records 
*/
struct node{
    //vector<ll> data;
    set<ll> data;
    node(){
        data.clear();
    }
    void addData(ll val){
        //data.pb(val);
        data.insert(val);
        assert(data.size()<=BUCKET_CAPACITY);
    }
    bool checkforVal(ll val){
        return (data.find(val)!= data.end());
        //for(ll j:data)if(j==val)return true;
        //return false; 
    }
    void prll(){
        for(ll value:data)cout<<value<<" ";
        cout<<"\n";
    }
};
/*
   Collection of nodes having support for overflow nodes
*/
struct bucket{
    list<node> buc;
    bucket(){
        buc.clear();
        buc.pb(node());
    }
    void addNode(){ buc.pb(node());}
    bool addVal(ll val,ll check=1){
        //Check for every node if values is present
        if(check)
            for(auto i:buc)if(i.checkforVal(val))return true;
        if(buc.size()==0)addNode();
        auto it = buc.end();it--;
        //If current node is full add new 
        if(((it->data).size())== BUCKET_CAPACITY)
            addNode();
        it = buc.end();it--;
        it->addData(val);
        return false;
    }
    void prll(){
        for(auto j:buc)j.prll();
    }
};
/* 
    Hash Table using Linear Hashing Technique
    slot        - the list of table hashed values
    modulo      - Current hash function (%2^i)
    slottoSplit - Next bucket to split
    totalEntries- Total values added
*/
struct HashTable
{
    vector<bucket> slot;
    ll slottoSplit,totalEntries;
    ll modulo;
    HashTable(){
        slot.clear();
        //Initialzing with room for 2
        slot.pb(bucket());slot.pb(bucket());
        modulo = 2;
        totalEntries = 0;slottoSplit=0;
    }
    ll findBkt(ll value){
        ll bktno = (value&(modulo-1));
        //ll bktno = (abs(value)%modulo);
        if( bktno >= slot.size())bktno -= (modulo>>1);
        return bktno;
    }
    bool checkLoad(){
        // check if r/n > LOAD_FACTOR
        double n = slot.size()*(BUCKET_CAPACITY);
        return (totalEntries> (n*LOAD_FACTOR));
    }
    void split(){
        slot.pb(bucket());
        if(modulo < slot.size())modulo<<=1;
        //Create temporary for current bucket
        bucket tmp = bucket();
        for(auto i:slot[slottoSplit].buc){
            for(ll j:i.data){
                ll bktno = findBkt(j);
                if(bktno == slottoSplit)tmp.addVal(j,0);
                else slot[bktno].addVal(j,0);
            }
        }
        slot[slottoSplit]=tmp;
        slottoSplit++;
        //Re-initialize step
        if(slottoSplit == (modulo/2))slottoSplit = 0;
    }

    bool add(ll value){
        ll bktno = findBkt(value);
        bool isPresent = slot[bktno].addVal(value);
        if(isPresent)return true;
        totalEntries++;
        bool isSplit = checkLoad();
        if(isSplit)split();
        return false;
    }
};

HashTable linearHash = HashTable();

bool solve(ll value){
    bool isPresent = linearHash.add(value);
    return (!isPresent);
}


struct BufferManager{
    vector<vector<ll> > inpbuf;
    vector<ll> outbuf;
    ll M,B;
    //ll inpsize,outsize,bufize;
    BufferManager(ll _M,ll _B){
        M = _M/8;
        B = _B/8;
        inpbuf.clear();outbuf.clear();
    }
    bool addtoBuffer(ll cmd)
    {
        ll en = inpbuf.size()-1;
        if(en<0 || inpbuf[en].size()== B){
            vector<ll>  new_vec;
            new_vec.pb(cmd);
            inpbuf.pb(new_vec);
        }
        else inpbuf[en].pb(cmd);
        if( en == M-2)
            return (inpbuf[en].size()==B);
        return false;
    }
    void operate(){
       
        for(ll i=0;i<inpbuf.size();i++){
            for(ll j=0;j<inpbuf[i].size();j++){
                bool ans = solve(inpbuf[i][j]);
                if(ans)outbuf.pb(inpbuf[i][j]);
                if(outbuf.size()== B)
                    prll();
            }
            inpbuf[i].clear();
        }
        prll();
        inpbuf.clear();
    }
    void prll(){
        for(ll i=0;i<outbuf.size();i++)
            cout<<outbuf[i]<<"\n";
        outbuf.clear();
    }
};

string s;
int main(int argc, const char *argv[])
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    ll t=1,n,i,j,m,q;
    if(argc!=2)
    {
        cout<<"enter file name"<<endl;
        return 0;
    }
    ifstream infile(argv[1]);
    ll M = 256,B= 256;
    if(!(B>0 && M >=2 && M<= (1000000/B)))
    {
        cout<<"M>=2 and M*B<=10^6 - condition not met!!";
        return 0;
    }
    //BUCKET_CAPACITY = max(20,B/12)
    BufferManager buffer = BufferManager(256,256);
    while(getline(infile,s)){ 
        ll cmd = stoi(s);
        bool areBuffersOver = buffer.addtoBuffer(cmd);
        if(areBuffersOver)
            buffer.operate();
    }
    buffer.operate();

    return 0;
}