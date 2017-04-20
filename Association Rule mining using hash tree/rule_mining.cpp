#include<bits/stdc++.h>
#define ll long long int
#define mp make_pair
#define ff first
#define ss second
#define pb push_back

using namespace std ;
ll y,data_size=435,min_support=180,mod=10,maxi=20;
double min_conf =0.9 ;
string emp="0000000000000000000000000000000000" ;
ll a[20000][40] ;
vector<pair<string,ll> > freq,cur,cur1 ;
vector<pair<string,ll> >::iterator itr,itr1,itr2 ;
map<string,ll>m1 ;
map<string,ll>::iterator itr7,itr8 ;


int numbered[200000] ;
int hash_on_attr[200000] ; //  1 based index
int to_hash[200000] ; //  1 based index
int cnt = 1 ;
vector<ll>v[200000] ;
vector<string>u[20000] ;
vector<pair<double,pair<string,string> > > ans ;

void pree(){
      ifstream infile("data.txt"); // no=0 yes=1 republican=0; democrat=1
  int j = 1 ; string s ;
  while(infile>>s){ int k=1;
    for( int i=0;i<s.size();i++){
        if(s[i]=='y'){a[j][k]=1 ; k++;}
        else if(s[i]=='n'||s[i]=='?'){a[j][k]=0;k++;}
        else if(s[i]=='r'){a[j][k]=0;break;}
        else if(s[i]=='d'){a[j][k]=1;break;}
    }
  }
}

void pre(){
    freopen("data.txt","r",stdin) ; string s ;
for( int j=1;j<=data_size;j++){
         cin >> s ;
         int k=1;
    for( int i=0;i<s.size();i++){
        if(s[i]=='y'){a[j][k]=1 ;a[j][k+17]=0; k++;}
        else if(s[i]=='n'||s[i]=='?'){a[j][k]=0; a[j][k+17]=1; k++;}
        else if(s[i]=='r'){a[j][k]=0; a[j][k+17]=1;break;}
        else if(s[i]=='d'){a[j][k]=1; a[j][k+17]=0;break;}
    }
  }
}

ll score(string s){ int k =0 ;
for(int i=1;i<=data_size;i++){
    int flag=1;
    for(int j=1;j<=34;j++){
        if(s[j-1]=='1'&&a[i][j]!=1){flag=0;break;}
    }
    if(flag){k++;}
}
return k ;
}

void initializes(){
 string s ;
for( int i=1;i<=34;i++){
    s=emp ; s[i-1]='1';
    cur.pb(mp(s,score(s))) ;
}

}

void split(int node){  // splits bucket whenever overflows

 for(int i=0;i<mod;i++){
            v[node].pb(cnt++) ; hash_on_attr[cnt-1]=hash_on_attr[node]+1;
    }
    string s  ;
    int x=hash_on_attr[node] ;
for(int i=0;i<u[node].size();i++){
        s=u[node][i] ;
        int k =0 ; int j ;
    for( j=0;j<34;j++){
        if(s[j]=='1'){k++;}
        if(k==x){break;}
    }
    y =(j+1)%mod ;
u[v[node][y]].pb(s) ;
}
u[node].clear() ;
}


void insert_hash_tree(int mod,int maxi,string s,int node){ // itemset in
if(u[node].size()>=maxi){
    split(node) ;
}

if(v[node].size()==0){
    u[node].pb(s) ; //cout << "pushed in" << node <<endl ;
}
else{
     int x=hash_on_attr[node];
 int k = 0 ; int j ;
    for( j=0;j<34;j++){
        if(s[j]=='1'){k++;}
        if(k==x){break;}
    }
     y =(j+1)%mod ; //cout <<  s <<  " "  << x << " " << k << " "  << j << " " << y << endl ;
 insert_hash_tree(mod,maxi,s,v[node][y]);
}

if(u[node].size()>=maxi){
    split(node) ;
}
}


void support_counting(string s1,string s2,int node){ // s1=processed s2=to be considered
    string s ;
if(v[node].size()==0){
    for( int i=0;i<u[node].size();i++){
        s = u[node][i] ; int flag = 1 ; int j,k ;
        for(j=33;j>=0;j--){
            if(s1[j]=='1'){break;}
        }
        for(k=j-1;k>=0;k--){
            if(s[k]=='1'&&s1[k]=='0'){flag=0;}
        }
        for(k=j+1;k<34;k++){
            if(s[k]=='1'&&s2[k]=='0'){flag=0;}
        }
        if(flag)m1[s]++;
    }
}
else{
string s3=s1 ; int i;
for(  i=33;i>=0;i--){
    if(s1[i]=='1'){break;}
}

for(int j=i+1;j<=33;j++){
    if(s2[j]=='1'){s3[j]='1' ; support_counting(s3,s2,v[node][(j+1)%mod]); }
    s3=s1 ;
}
}
}

void calc_freq_itemsets(){ // iterative calculation without hashtree
 string s1,s2 ;
for(int zz=1;zz<=34;zz++){
    itr=cur.begin() ; itr1 = cur.end() ;
    while(itr!=cur.end()){
       int  x =itr->ss ;   s1 = itr->ff ;
        if(x>=min_support){
            freq.pb((*itr)) ;int k ;
            for( k=33;k>=0;k--){
                if(s1[k]=='1'){break;}
            }
            for(int j=k+1;j<=33;j++){
                s2=s1 ; s2[j]='1' ;
                if(s2[j-17]!='1')cur1.pb(mp(s2,score(s2))) ;
            }
        }
        itr++;
    // itr=cur.erase(itr) ;
    }
    cur.clear() ;
    for(int i=0;i<cur1.size();i++){cur.pb(cur1[i]);}
    cur1.clear();
    cout << "complete " << zz << " " << freq.size() << endl ;
}

}

void itemset_to_rule(string s1,string s2){ //cout << "ghgh " << m1[s1] << " " << 1.0*m1[s2] << endl;
if(s2==emp||1.0*(1.0*m1[s1]/1.0*m1[s2])>=min_conf){ //cout << 1.0*(1.0*m1[s1]/1.0*m1[s2]) << endl;
  if(s2!=emp){ans.pb(mp((1.0*(1.0*m1[s1]/1.0*m1[s2])),mp(s1,s2)));}
  int i ;for(i=33;i>=0;i--){if(s2[i]=='1'){break;}}
  string s3,s4 ;
     for(int j=i+1;j<34;j++){
        if(s1[j]=='1'){
            s3=s1 ; s3[j]='0' ;
            s4=s2 ; s4[j]='1' ;
            itemset_to_rule(s3,s4);
        }
     }
}
}





int main(){

    ios::sync_with_stdio(false);

pre() ;

initializes() ;

for(int zz=0;zz<34;zz++){
    if(cur.size()==0){break;}
    m1.clear() ;
    for(int i=0;i<cnt;i++){hash_on_attr[i]=0 ; v[i].clear();u[i].clear(); }
    cnt=2; int node=1 ;hash_on_attr[1]=1 ;
    for(int i=0;i<mod;i++){
            v[node].pb(cnt++) ; hash_on_attr[cnt-1]=hash_on_attr[node]+1;
        }
    for(int sd=0;sd<cur.size();sd++){   //if(sd==20){break;}
insert_hash_tree(mod,maxi,cur[sd].ff,1) ;
        //cout << cur[sd].ff << " " <<  sd << endl;
    }

     cout << cnt << endl ;
     for(int sd=1;sd<data_size;sd++){
        string w1=emp,w2=emp ;
        for(int col=0;col<34;col++){
            w2[col]=a[sd][col]+48 ;
        }
       // cout << w1 << " " << w2 << endl ;
       //cout << sd << endl ;
        support_counting(w1,w2,1) ;
    }

     cout << m1.size() ;
    cur.clear() ;
    itr7 = m1.begin();  itr8=m1.end() ;
    while(itr7!=itr8){
        if((itr7->ss)>=min_support){cur1.pb(mp((itr7->ff),(itr7->ss)));freq.pb(mp((itr7->ff),(itr7->ss)));}
        itr7++;
    }

    for(int i=0;i<cur1.size();i++){
        string s1 = cur1[i].ff;
        int j ;
        for(j=33;j>=0;j--){
            if(s1[j]=='1'){break;}
        }
        for(int k=j+1;k<34;k++){
            string s2=s1 ; s2[k]='1' ;
            cur.pb(mp(s2,cur[i].ss)) ;
        }
    }
    cur1.clear() ;
    //break; // get k+1 from k in cur
}
//calc_freq_itemsets();
m1.clear() ;
for(int i=0;i<freq.size();i++){
    m1[freq[i].ff] = freq[i].ss ;
}
for(int i=0;i<freq.size();i++){
     itemset_to_rule(freq[i].ff,emp) ;
}
sort(ans.begin(),ans.end()) ;
for(int i=ans.size()-1;i>=0;i--){
        string s1 = ans[i].ss.ff ; string s2 =  ans[i].ss.ss ; int k = 0 ;
for(int j=0;j<34;j++){if(s2[j]=='1'){k++;}}
   if((s2[33]=='1'||s2[32]=='1')&&k==1)cout << ans[i].ss.ff << " " << ans[i].ss.ss << endl ;
}
//cout << endl << m1["0000000000000000000000000000000000"];

}
