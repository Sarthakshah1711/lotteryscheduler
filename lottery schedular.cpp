#include <iostream>
#include<bits/stdc++.h>
#include <chrono>
#include<queue>
#include <ctime>
using namespace std;
#define ll long long int

ll tree[100005];   // This is size of tree


ll randomgenerator(ll limit)  //This function will generate random ticket from given range
{
    random_device rd;
   
    mt19937 gen(rd());
   
    uniform_int_distribution<> dis(1,limit);
    return dis(gen);
}


ll construnct_segment(vector<ll> &v,ll i,ll j,ll index)  //This function will construct tree form process
{
    if(i==j)
    {
        tree[index]=v[i];
        return tree[index];
    }
   
    ll mid=i+((j-i)/2);
    ll x=construnct_segment(v,i,mid,2*index+1);
    ll y=construnct_segment(v,mid+1,j,2*index+2);
    tree[index]=x+y;
    return tree[index];
}

void construct(vector<ll> &v)
{
    ll n=v.size();
    ll p=construnct_segment(v,0,n-1,0);
}

void inc(ll i,ll j,ll index,ll dif,ll node)    //This function increment ticket for given process
{
    if(node<i||node>j)
    {
        return ;
    }
   
    tree[index]+=dif;

    if(i!=j)
    {
        ll mid=i+((j-i)/2);
        inc(i,mid,2*index+1,dif,node);
        inc(mid+1,j,2*index+2,dif,node);
    }
    return ;
}


void dec(ll i,ll j,ll index,ll dif,ll node)    //This function decrement ticket for given process
{
    if(node<i||node>j)
    {
        return ;
    }
   
    tree[index]-=dif;

    if(i!=j)
    {
        ll mid=i+((j-i)/2);
        dec(i,mid,2*index+1,dif,node);
        dec(mid+1,j,2*index+2,dif,node);
    }
    return ;
}


ll searchingprocess(ll i,ll j,ll ticket,ll node)  //This function search process from given ticket
{
    if(i==j)
    {
        return i;
    }
   
    ll mid=i+((j-i)/2);
    if(tree[2*node+1]<ticket)
    {
        return searchingprocess(mid+1,j,ticket-tree[2*node+1],2*node+2);    
    }
    else
    {
        return searchingprocess(i,mid,ticket,2*node+1);
    }
}


void removeprocess(ll index,ll n,ll val)     // This function will remove process
{
    dec(0,n-1,0,val,index);
}

void addprocess(ll ticket,ll mini,ll q)     // This function will add process
{
    inc(0,q-1,0,ticket,mini);
}

int main()
{
    priority_queue<ll,vector<ll>,greater<ll>> pq;
    ll q;   // input for maximum size of queue
    cin>>q;
 
    vector<ll> v(q,0);  //entering process with keys
    ll available=0;
   
    ll n;  // How many process we want to add now
    cin>>n;
  
    for(ll j=n;j<q;j++)
    {
        pq.push(j);
    }
   
    for(ll i=0;i<n;i++)  // Enter the number ticket for every process
    {
        cin>>v[i];
    }
   
    construct(v); // construct tree
 
    ll limit=tree[0];
    ll r=randomgenerator(limit);  //Picking random ticket
   
    cout<<"Random Ticket Number :"<<r<<endl;
   
    ll d=searchingprocess(0,q-1,r,0);  // searching process  
   
    cout<<"Random ticket is at process Number :"<<d+1<<endl;
   
    pq.push(1);
    removeprocess(1,q,v[1]);  //remove process number 2 we input 1 bcz of 0-indexing
   
    d=searchingprocess(0,q-1,7,0);  //searching process after
    cout<<"After removing 2 nd process ticket number 7 is at process :"<<d+1<<endl;
   
   inc(0,q-1,0,2,0); //increment ticket for 1 st process
   
    d=searchingprocess(0,q-1,6,0);  
   
    cout<<"After adding 2 tickets at process 1 the 6 th ticket is at process :"<<d+1<<endl;
   
   ll g=pq.top();
   pq.pop();
   
   v[g]=10;  // we add process with 10 tickets
   addprocess(10,g,q);
   
   ll g1=searchingprocess(0,q-1,15,0);
   cout<<"After adding new process with 10 tickets ticket number 15 is at process :"<<g1+1<<endl;
   
}

/*
Enter the maximum size of queue
Enter the nubmer of you process 
for each process enter the number of tickets each process held

8
5
5 8 11 15 20
*/