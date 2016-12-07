#include <iostream>
#include<algorithm>
#include<limits.h>
using namespace std;

int find(int a);
void Union(int set[],int a,int b);
#define max 300000

struct edge{
    int node1;
    int node2;
    int weight;
};
/*
bool cmp(edge a,edge b)
{
    return a.weight<b.weight;
}
*/

int cmp(const void *a, const void *b)
{
    return ((edge*)a)->weight - ((edge*)b)->weight;
}

int set[max];
int cost[max];
struct edge edgeTrue[max];
struct edge edgeFalse[max];
int main() {
    int Max=0;
    int falsenumber=0;
    int truenumber=0;
    int N,M;
    int i;
    int City1,City2,Cost,Status;
    cin>>N>>M;
    int count=0;
    for(i=0;i<M;i++) {
        cin >> City1 >> City2 >> Cost >> Status;
        if (Status == 0) {
            edgeFalse[falsenumber].node1 = City1;
            edgeFalse[falsenumber].node2 = City2;
            edgeFalse[falsenumber].weight = Cost;
            falsenumber++;
        } else if (Status == 1) {
            edgeTrue[truenumber].node1 = City1;
            edgeTrue[truenumber].node2 = City2;
            edgeTrue[truenumber].weight = Cost;
            truenumber++;
        }
    }
    int k=0;
    qsort(edgeFalse,falsenumber,sizeof(edgeFalse[0]),cmp);
   // sort(edgeFalse,edgeFalse+falsenumber,cmp);
    //-----------------------------------------------------------
    for(k=1;k<N+1;k++)
    {
        count=1;
        cost[k]=0;
        for(i=0;i<N+1;i++)
        {
            set[i]=-1;
        }
        //初始化set
        for(i=0;i<truenumber;i++)
        {
            if(count==N-1)break;

            if(edgeTrue[i].node1!=k&&edgeTrue[i].node2!=k)
            {
                int p1=find(edgeTrue[i].node2);
                int p2=find(edgeTrue[i].node1);
                if(p1!=p2) {
                    //set[p1] = p2;
                    Union(set,p1,p2);
                    count++;
                }
            }

        }
        for(i=0;i<falsenumber;i++) {
            if(count==N-1)break;
            if (edgeFalse[i].node1 != k && edgeFalse[i].node2 != k) {
                int p1 = find(edgeFalse[i].node1);
                int p2 = find( edgeFalse[i].node2);
                //在所有假边中找能联通这两个集合且最小的
                if (p1 != p2) {
                    cost[k] += edgeFalse[i].weight;
                    Union(set, p1, p2);
                    //set[p1]=p2;
                    count++;
                }
            }
        }
        if (count != N - 1)  //can't connect all the cities left
        {
            cost[k] = INT_MAX;
        }
    }
    int a[max];
    int index=0;
    for(i=1;i<N+1;i++)
    {
        if(cost[i]>Max)
        {
            index=0;
            Max=cost[i];
            a[index++]=i;
        }else if(cost[i]==Max)
        {
            a[index++]=i;
       }
    }
    if(Max==0)cout<<"0";
    else {
        for (i = 0; i < index - 1; i++) {
            cout << a[i] << " ";
        }
        cout << a[i];
    }
    return 0;
}
int find(int a)
{
    if(set[a]<=0)return a;
    else return set[a]=find(set[a]);
}
void Union(int set[],int a,int b)
{
    if(set[a]<set[b])//a is bigger
    {
        set[a]+=set[b];
        set[b]=a;

    }else
    {
        set[b]+=set[a];
        set[a]=b;
    }
}
