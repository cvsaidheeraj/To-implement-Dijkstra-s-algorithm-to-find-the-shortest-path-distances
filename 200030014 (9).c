#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct vertex{
    long int sd;
    long int pre;
    long int colour;
}Vert ;

typedef struct graph
{
    long int weight;
    long int data;
    struct graph *next;
}Graph;

Graph* new(int value, int weigh)
{
    Graph* temp;
    temp = malloc(sizeof(Graph));
    temp ->next = NULL;
    temp->data = value;
    temp->weight = weigh ;
    return temp;
}

void distance(Vert every[], int u, int v, int weigh)
{
    if(every[u].sd != INT_MAX)
    {
        if(every[v].sd > every[u].sd+weigh)
        {
        every[v].sd = every[u].sd+weigh;
        every[v].pre = u;
    }
    }
    return;
}

void push(Graph* A[], int num1, int num2 , int weight)
{
    Graph* temp;
    temp = new(num2, weight);
    if(A[num1] == NULL){
        A[num1] = temp;
    }
    else{
        temp->next = A[num1];
       A[num1] = temp;
    }
}

void sort();
void declare();
void set();

void set(Graph* gr_arr[], Vert each[] , int dum)
{
    register int i=0;
    while(i<dum+1)
    {
        gr_arr[i] = NULL;
        each[i].sd = INT_MAX;
        each[i].pre = -1;
        each[i].colour = -1;
        i++;

    }
}

void sort(Vert every[], int A[], int index, int var)
{
    register int i=index;
    while(i<var)
    {
        register int k=index;
        while(k<var-1)
        {
            if( (every[A[k]].sd) > (every[A[k+1]].sd))
            {
                int dumm = A[k];
                A[k] = A[k+1];
                A[k+1] = dumm;
            }
            k++;
        }
        i++;
    }
    return;
}

void declare(int A[] , int B[], int C[], int sum)
    {
        register int j=0;
        while(j<sum)
        {
           A[j] = C[j];
           B[j] = C[j];
           j++;
        }
    }
int main(int argc, char*argv[])
{
    FILE *infile;
    FILE *outfile;
    outfile=fopen("dijkstra.txt","w");
    infile=fopen(argv[1],"r");
    int sourceval = atoi(argv[2]);
    int xvertex,yvertex,vertweigh;
     int vertices=0;
    while(fscanf(infile,"%d %d %d",&xvertex,&yvertex,&vertweigh)!=EOF)
    {
        if(yvertex > vertices)
        vertices = yvertex;
        if(xvertex > vertices)
        vertices = xvertex;  
    }

    rewind(infile);
    int curr[vertices+1];
    register int i=0;
    while(i<vertices+1)
    {
        curr[i] = -1;
        i++;
    }
    int varx = 0;
    int vary = 0;
    int cons = 0;
    while(fscanf(infile,"%d %d %d",&xvertex,&yvertex,&vertweigh)!=EOF)
    {
         i=0;
        while(i<vertices+1)
        {
            if(curr[i]==xvertex)
            varx=1;
            
            if(curr[i]==yvertex)
            vary=1;

            i++;
            
        }
        if(varx==0){
            curr[cons]=xvertex;
            cons+=1;
        }
        if(vary==0){
            curr[cons]=yvertex;
            cons+=1;
        }
        varx=0;
        vary=0;
    }
    
    int sum = cons;
    int arr1[sum],arr2[sum];
    declare(arr1 , arr2, curr, sum);
    rewind(infile);
    Graph* array[vertices+1];
    Vert each[vertices+1];
    set(array, each ,vertices);
    int u,v;
    each[sourceval].sd=0;
    while(fscanf(infile,"%d %d %d", &xvertex, &yvertex, &vertweigh)!=EOF){
    push(array,xvertex,yvertex,vertweigh);
    }
    int var=sum;
    int start=0;
    for(int i=0;i<var;i++)

    {
        sort(each,arr1,start,sum);
        u = arr1[start];
        arr1[start]=-1;
        start+=1;
        Graph* tempvar ;
        tempvar = array[u];
        while(tempvar)
        {
            v=tempvar->data;
            distance(each,u,v,tempvar->weight);
            tempvar=tempvar->next;
        }
    }
    i=0;
    while(i<sum)
    {
            if(each[arr2[i]].sd == INT_MAX){
            fprintf(outfile,"%d %d\n",arr2[i],-1);
            }
            else{
            fprintf(outfile,"%d %ld\n",arr2[i],each[arr2[i]].sd);
            }
            i++;
    }
  
fclose(infile);
fclose(outfile);
return 38;
}

