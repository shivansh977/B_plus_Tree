#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <bitset>
#include <cmath>
#define ll int long long
#define makearr int arr[n]; for(int i=0;i<n;i++) cin>>arr[i];
#define For(i,j,n) for(int i=j;i<n;i++)
#define pb push_back
#define mp make_pair
#define pi pair<int,int>
#define pll pair<ll,ll>
#define ri(n) int n; cin>>n;
#define rll(n) ll n; cin>>n;
#define di(n) int n;
#define dll(n) ll n;
using namespace std;
class BPTNode{
    public:
    vector<int> key;
    vector<BPTNode*> ptr;
    bool isleaf;
    BPTNode* left;
    BPTNode* right;
    BPTNode* par;
    BPTNode(){
        key={};
        ptr={};
        isleaf=false;
        left=NULL;
        right=NULL;
        par=NULL;
    }
};
void BPTSplit(BPTNode* &n, int d, BPTNode* &root, int t, int* dn, int* in){
    if(n->isleaf){
        int sepa=(n->key)[d];(*dn)++;
        BPTNode* a=new BPTNode();BPTNode* b=new BPTNode();
        a->isleaf=true;b->isleaf=true;
        For(i,0,d) (a->key).pb((n->key)[i]);
        For(i,d,2*d+1) (b->key).pb((n->key)[i]);
        if(n->par==NULL){
            BPTNode* temp=new BPTNode();(*in)++;
            root=temp;
            (root->key).pb(sepa);
            a->par=root;b->par=root;
            (root->ptr).pb(a);(root->ptr).pb(b);
        }
        else{
            BPTNode* p=n->par;
            int idx=-1;
            For(i,0,(p->ptr).size()){
                if((p->ptr)[i]==n){
                    idx=i;break;
                }
            }
            vector<BPTNode*> temp;
            For(i,0,idx){
                temp.pb((p->ptr)[i]);
            }
            temp.pb(a);temp.pb(b);
            For(i,idx+1,(p->ptr).size()){
                temp.pb((p->ptr)[i]);
            }
            p->ptr=temp;
            (p->key).pb(sepa);
            a->par=p;b->par=p;
            sort((p->key).begin(),(p->key).end());
            if((p->key).size()>2*t+1) BPTSplit(p,d,root,t,dn,in);
        }
    }
    else{
        BPTNode* a=new BPTNode();BPTNode* b=new BPTNode();(*in)++;
        int y=(n->key)[t];
        For(i,0,t) (a->key).pb((n->key)[i]);
        For(i,t+1,2*t+2) (b->key).pb((n->key)[i]);
        For(i,0,t+1){
            (a->ptr).pb((n->ptr)[i]);
            ((n->ptr)[i])->par=a;
        }
        For(i,t+1,2*t+3){
            (b->ptr).pb((n->ptr)[i]);
            ((n->ptr)[i])->par=b;
        }
        if(n->par==NULL){
            BPTNode* temp=new BPTNode();(*in)++;
			root=temp;
            (root->key).pb(y);
            a->par=root;b->par=root;(root->ptr).pb(a);(root->ptr).pb(b);
        }
        else{
            BPTNode* p=n->par;
            int idx=-1;
            For(i,0,(p->ptr).size()){
                if((p->ptr)[i]==n){
                    idx=i;break;
                }
            }
            vector<BPTNode*> temp;
            For(i,0,idx){
                temp.pb((p->ptr)[i]);
            }
            temp.pb(a);temp.pb(b);
            For(i,idx+1,(p->ptr).size()){
                temp.pb((p->ptr)[i]);
            }
            (p->ptr)=temp;
            a->par=p;b->par=p;
            (p->key).pb(y);sort((p->key).begin(),(p->key).end());
            if((p->key).size()>2*t+1) BPTSplit(p,d,root,t,dn,in);
        }
    }
    return;
}
void BPTinsert(BPTNode* &trav, BPTNode* &root, int val, int d, int t, int* dn, int* in){
    if(!trav->isleaf){
        vector<int>::iterator it=lower_bound((trav->key).begin(),(trav->key).end(),val);
        int plac=it-(trav->key).begin();
        BPTinsert((trav->ptr)[plac],root,val,d,t,dn,in);
    }
    else{
        if((trav->key).size()==2*d){
            (trav->key).pb(val);
            sort((trav->key).begin(),(trav->key).end());
            BPTSplit((trav),d,root,t,dn,in);
        }
        else{
            (trav->key).pb(val);
            sort((trav->key).begin(),(trav->key).end());
        }
    }
    return;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ri(d);ri(t);
    int x;
    BPTNode* root=new BPTNode();
    root->isleaf=true;
    int dn=1,in=0;
    int flag=0;
    while(cin>>x){
        if(x==1){
            flag=1;
            int val;cin>>val;
            BPTinsert(root,root,val,d,t,&dn,&in);
        }
        else if(x==2){
            if(!flag){
                cout<<0<<" "<<0<<"\n";
            }
            else{
                cout<<in<<" "<<dn<<" ";
                For(i,0,(root->key).size()){
                    cout<<(root->key)[i]<<" ";
                }cout<<"\n";
            }
        }
        else break;
    }
    return 0;
}