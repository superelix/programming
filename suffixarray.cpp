#include<bits/stdc++.h>
using namespace std;
//radix sort implemented o(n logn)
void radix_sort(vector<pair<pair<int,int>,int>> &a){
    int n=a.size();
   { vector<int> cnt(n,0);
    for(auto u:a){
        cnt[u.first.second]++;
    }
    vector<int> pos(n);
    pos[0]=0;
    for(int i=1;i<n;i++){
        pos[i]=pos[i-1]+cnt[i-1];
    }
    vector<pair<pair<int,int>,int>> a_new(n);
    for(auto u:a){
        int i=u.first.second;
        a_new[pos[i]]=u;
        pos[i]++;
    }
    a=a_new;
}
  { vector<int> cnt(n,0);
    for(auto u:a){
        cnt[u.first.first]++;
    }
    vector<int> pos(n);
    pos[0]=0;
    for(int i=1;i<n;i++){
        pos[i]=pos[i-1]+cnt[i-1];
    }
    vector<pair<pair<int,int>,int>> a_new(n);
    for(auto u:a){
        int i=u.first.first;
        a_new[pos[i]]=u;
        pos[i]++;
    }
    a=a_new;
}
}
int main(){
    //build suffix array
    vector<pair<char,int>> a;
    string s;
    cin>>s;
    s+="$";
     int n=s.length();
    for(int i=0;i<s.length();i++){
        a.push_back({s[i],i});
    }
       vector<int> p(n),c(n);
    sort(a.begin(),a.end());
    for(int i=0;i<n;i++){
        p[i]=a[i].second;
    }
    c[p[0]]=0;
    for(int i=1;i<n;i++){
        if(a[i].first==a[i-1].first)c[p[i]]=c[p[i-1]];
        else c[p[i]]=c[p[i-1]]+1;
    }
    int k=1;
    while((1<<k)<n){
        vector<pair<pair<int,int>,int>> a;
        for(int i=0;i<n;i++){
            a.push_back({{c[i],c[(i+(1<<k))%n]},i});
        }
        radix_sort(a);
        for(int i=0;i<n;i++){
        p[i]=a[i].second;
    }
    c[p[0]]=0;
    for(int i=1;i<n;i++){
        if(a[i].first==a[i-1].first)c[p[i]]=c[p[i-1]];
        else c[p[i]]=c[p[i-1]]+1;
    }
        k++;
    }
    //build the lcp.
    
    vector<int> lcp(n);
    vector<int> rank(n);
    for(int i=0;i<n;i++)rank[p[i]]=i;
    k=0;
    for(int i=0;i<n;i++,(k?k--:0)){
        if(rank[i]==n-1){k=0;continue;}
        int j=p[rank[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k])k++;
        lcp[rank[i]+1]=k;
    }
      for(int i=0;i<n;i++){
        cout<<lcp[i]<<" "<<p[i]<<" "<<s.substr(p[i],n-p[i])<<endl;
    }
    return 0;
}