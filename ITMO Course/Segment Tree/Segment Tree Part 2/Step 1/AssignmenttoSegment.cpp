#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 

using namespace std;
using namespace __gnu_pbds; 

typedef     unsigned long long int ull;
typedef     long long int    ll;
typedef     long double      ld;
typedef     pair<ll,ll>      pll;
#define     FOR(i,a,b)       for(ll i=a;i<b;i++)
#define     FORE(i,a,b)      for(int i=a;i<=b;i++)
#define     FORD(i,b,a)      for(int i=b;i>a;i--)
#define     FORDE(i,b,a)     for(ll i=b;i>=a;i--)
#define     debug(x)         cout<< '>'<<#x<<" : "<<x<<"\n";
#define     debug2(x,y)      cout<< '>'<<#x<<" : "<<x<<"\n"; cout<< '>'<<#y<<" : "<<y<<"\n";
#define     debug3(x,y,z)    cout<< '>'<<#x<<" : "<<x<<"\n"; cout<< '>'<<#y<<" : "<<y<<"\n";cout<< '>'<<#z<<" : "<<z<<"\n";
#define     umap             unordered_map
#define     uset             unordered_set
#define     lb               lower_bound
#define     ub               upper_bound
#define     mp               make_pair
#define     in               insert
#define     s                second
#define     f                first
#define     nn               cout<<"\n"
#define     pb               push_back
#define     testcase         int t;cin>>t;while(t--)
#define     gcd(a,b)         __gcd(a,b)
#define     maxv             INT_MAX
#define     minv             INT_MIN
#define     MOD              1000000007
#define     FastIO           ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(0);
#define     here             cout<<"I'm here\n";
#define     flush            fflush(stdout);
#define endl '\n'         
#define ordered_set_single tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update>

struct segmenttree{

    ll sz=1;
    ll NO_OPERATION = LLONG_MAX;
    vector<ll> segtree;



    void init(ll n)
    {
        sz = 1;
        NO_OPERATION = LLONG_MAX;
        while (sz<n)
        {
            sz = sz * 2;
        }
        segtree.assign(2 * sz, 0);
    }

    ll operation(ll a,ll b)
    {
        if(b==NO_OPERATION)
        return a;

        return b;
    }

    void apply_operation(ll& a,ll b)
    {
        a = operation(a, b);
    }

    

    void propogate(ll x,ll lx ,ll rx)
    { 
        if(rx-lx==1)
        return;
        
        if (segtree[x] == NO_OPERATION)
        {
            return;
        }
        apply_operation(segtree[2 * x + 1], segtree[x]);
        apply_operation(segtree[2 * x + 2], segtree[x]);
        segtree[x] = NO_OPERATION;

    }

    ll get_segment(ll idx,ll x,ll lx ,ll rx)
    {


        //  get sum from l to r-1
        // we currently store in x sum from lx to rx-1
        
        propogate(x, lx, rx);

        if(rx-lx==1)
        {
            return segtree[x];
        }

        
        
        ll mid = (lx + rx) / 2;
        
        if(idx<mid)
        {

        // left child             +                        
        return  get_segment(idx, 2 * x + 1, lx, mid);
        }
        // right child       
        return   get_segment(idx, 2 * x + 2, mid,rx);

    

        
    }
    
    ll get_segment(ll idx)
    {
        return get_segment(idx, 0, 0, sz);
    }

    
    void modify(ll l, ll r,ll v,ll x,ll lx ,ll rx)
    {
        propogate(x, lx, rx);

        if (l >= rx || r <= lx)
        {
            // don't intersect
            return;
        }

        if(l<=lx && rx<=r)
        {
            //  complete intersection
              segtree[x]=v;
              return;
        }
        
        ll mid = (lx + rx) / 2;
        
        // left child             +                   
        modify(l, r, v, 2 * x + 1, lx, mid);
        //  right child
        modify(l, r, v, 2 * x + 2, mid, rx);


        return;
    }

    void modify(ll l, ll r,ll v)
    {
        modify(l, r, v, 0, 0, sz);
    }
};

signed main(int argc, char** argv)
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    FastIO;
    long t=1;
    while(t--)
    {
        ll n, m;
        cin >> n >> m;
        segmenttree arr;
        arr.init(n);
        while(m--)
        {
            ll op;
            cin >> op;
            if(op==1)
            {
                ll l, r, v;
                cin >> l >> r >> v;
                arr.modify(l, r, v);

            }
            else
            {
                ll idx;
                cin >> idx;
                cout<<arr.get_segment(idx)<<" ";
            }
        }
    }
    return 0;
}
