#include <iostream>
#include<algorithm>
using namespace std;

int find(int set[],int a);
void Union(int set[],int a,int b);
#define max 501
typedef struct edge_true *edge;

struct edge_true{
    int id;
    int weight;
    struct edge_true* next;
};
struct Vnode{
    edge firstedge;
};
struct edge_false{
    int node1;
    int node2;
    int weight;
};
edge del (edge head,int element);
edge add(edge head,int element,int weight);
bool cmp(edge_false a,edge_false b)
{
    return a.weight<b.weight;
}
int main() {
    struct Vnode *node;
    struct edge_false *edgeFalse;
    int falsenumber=0;
    int truenumber=0;
    int set[max]={0};
    int cost[max]={0};
    int N,M;
    int i;

    int City1,City2,Cost,Status;
    cin>>N>>M;
    node=(struct Vnode*)malloc(sizeof(struct Vnode)*(N+1));
    edgeFalse=(struct edge_false*)malloc(sizeof(struct edge_false)*(M));
    for(i=0;i<N+1;i++)
    {
        node[i].firstedge=NULL;
    }
    for(i=0;i<M;i++)
    {
        edgeFalse[i].weight=edgeFalse[i].node1=edgeFalse[i].node2=0;
    }
    for(i=0;i<M;i++) {
        cin >> City1 >> City2 >> Cost >> Status;
        if (Status == 0) {
            edgeFalse[falsenumber].node1 = City1;
            edgeFalse[falsenumber].node2 = City2;
            edgeFalse[falsenumber].weight = Cost;
            falsenumber++;
        } else if (Status == 1) {
            edge temp = (edge) malloc(sizeof(struct edge_true));
            temp->weight = Cost;
            temp->id = City2;
            temp->next = NULL;
            if (node[City1].firstedge == NULL) {
                node[City1].firstedge = temp;
            } else {
                edge t = node[City1].firstedge;
                while (t->next)t = t->next;
                t->next = temp;
            }
            edge temp2=(edge)malloc(sizeof(struct edge_true));
            temp2->weight = Cost;
            temp2->id = City1;
            temp2->next = NULL;
            if (node[City2].firstedge == NULL) {
                node[City2].firstedge = temp2;
            } else {
                edge t = node[City2].firstedge;
                while (t->next)t = t->next;
                t->next = temp2;
            }
            truenumber++;
        }
    }
    int k=0;
    //-----------------------------------------------------------
    for(k=1;k<N+1;k++)
    {
        edge temp=node[k].firstedge;
        int id=k;
        while(temp)
        {
            node[temp->id].firstedge=del(node[temp->id].firstedge,id);
            temp=temp->next;
        }
        for(i=0;i<N+1;i++)
        {
            set[i]=-1;
        }
        //初始化set
        for(i=1;i<N+1;i++)
        {
            if(i!=k) {
                edge temp = node[i].firstedge;
                while (temp) {
                    if (find(set, i) != find(set, temp->id)) {
                        Union(set, find(set, i), find(set, temp->id));
                    }
                    temp = temp->next;
                }
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
        temp=node[k].firstedge;
        id=k;
        while(temp)
        {
            node[temp->id].firstedge=add(node[temp->id].firstedge,id,temp->weight);
            temp=temp->next;
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
        set[a]+=set[b];
        set[b]=a;

    }else
    {
        set[b]+=set[a];
        set[a]=b;
    }
}
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
}
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
