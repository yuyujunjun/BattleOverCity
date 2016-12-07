#include <iostream>
#include<algorithm>
using namespace std;

int find(int set[],int a);
void Union(int set[],int a,int b);
#define max 501

struct edge{
    int node1;
    int node2;
    int weight;
};
bool cmp(edge a,edge b)
{
    return a.weight<b.weight;
}
int main() {
    struct edge *edgeFalse;
    struct edge *edgeTrue;
    int falsenumber=0;
    int truenumber=0;
    int set[max]={0};
    int cost[max]={0};
    int N,M;
    int i;

    int City1,City2,Cost,Status;
    cin>>N>>M;
    edgeFalse=(struct edge*)malloc(sizeof(struct edge)*(M));

    edgeTrue=(struct edge*)malloc(sizeof(struct edge)*(M));
    for(i=0;i<M;i++)
    {
        edgeFalse[i].weight=edgeFalse[i].node1=edgeFalse[i].node2=0;
        edgeTrue[i].weight=edgeTrue[i].node1=edgeTrue[i].node2=0;
    }
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
    //-----------------------------------------------------------
    for(k=1;k<N+1;k++)
    {
        for(i=0;i<N+1;i++)
        {
            set[i]=-1;
        }
        //初始化set
        for(i=0;i<truenumber;i++)
        {
            if(edgeTrue[i].node1!=k&&edgeTrue[i].node2!=k&&find(set,edgeTrue[i].node1)!=find(set,edgeTrue[i].node2))
            {
                Union(set,edgeTrue[i].node2,edgeTrue[i].node1);
            }
        }
        int mincost;
        sort(edgeFalse,edgeFalse+falsenumber,cmp);
        for(i=0;i<falsenumber;i++) {
            // mincost=0;
            //int parent1=find(set,edgeFalse[i].node1);
            //int parent2=find(set,edgeFalse[i].node2);
            //if(parent1!=parent2&&parent1!=k&&parent2!=k)
            //{
            //  mincost=edgeFalse[i].weight;
            //for(int j=0;j<falsenumber;j++)
            //{
            if (edgeFalse[i].node1 != k && edgeFalse[i].node2 != k) {
                int p1 = find(set, edgeFalse[i].node1);
                int p2 = find(set, edgeFalse[i].node2);
                //在所有假边中找能联通这两个集合且最小的
                if (p1 != p2) {
                    mincost = edgeFalse[i].weight;
                    cost[k] += mincost;
                    Union(set, find(set, p1), find(set, p2));
                }
            }
        }
    }
    int Max=0;
    int a[N+1];
    int index=0;
    for(i=0;i<N+1;i++)
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
            cout << a[i]<<" ";
        }
        cout<<a[i];

    }
    return 0;
}
int find(int set[],int a)
{
    if(set[a]<=0)return a;
    else return set[a]=find(set,set[a]);
}
void Union(int set[],int a,int b)
{
    if(find(set,a)<find(set,b))//a is bigger
    {
        set[find(set,a)]+=set[find(set,b)];
        set[b]=find(set,a);

    }else
    {
        set[find(set,b)]+=set[find(set,a)];
        set[a]=find(set,b);
    }
}
/*
edge del (edge head,int element)
{
    edge p=head;
    if(p->id==element)
    {
        edge temp=p->next;
        free(p);
        return temp;
    }
    else{
        while(p->next!=NULL&&p->next->id!=element)p=p->next;
        edge temp=p->next;
        p->next=temp->next;
        free(temp);
        return head;
   }
}*/
/*
edge add(edge head,int element,int weight)
{
    edge p=head;
    edge temp=(edge)malloc(sizeof(struct edge_true));
    temp->next=NULL;
    temp->id=element;
    temp->weight=weight;
    if(head==NULL){
        head=temp;
        return head;
    }else
    {
        while(p->next)p=p->next;
        p->next=temp;
        return head;
    }
}
*/