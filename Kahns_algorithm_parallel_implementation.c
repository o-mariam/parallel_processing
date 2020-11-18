#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>

#define MAX 400

int front = -1,rear = -1;
int V,i,j,n,place;
int origin ,destin;
int arr[MAX][MAX]; /*Adjacency Matrix*/


int main()
{

    int i,j,v;

    FILE * fPtr;

//Άνοιγμα αρχείου
    fPtr = fopen("dag.txt", "r");

    // fopen() return NULL if last operation was unsuccessful
    if(fPtr == NULL)
    {
        // Unable to open file hence exit
        printf("Unable to open file.\n");
        exit(EXIT_FAILURE);
    }

    // File open success.
    printf("File opened.\n\n");

    char word1[4];


    for(i=0; i<1; i++){ // Διάβασμα της πρώτης γραμμής του αρχείου
        fscanf(fPtr,"%s%*[^\n]",word1);
    }

    int V = atoi(word1); //μετατροπή απο string σε int



//Αρχικοποίηση Μητρώου Γετνίασης

    for(i = 0; i < V; i++)
        for(j = 0; j < V; j++)
            arr[i][j] = 0;


//Εισαγωγή Ακμών

        while(!feof(fPtr)) {
            for(i=0; i<1; i++){fscanf(fPtr, "%*[^\n]\n");}
            fscanf(fPtr,"%d %d", &origin,&destin);
            arr[origin][destin]=1;
        }

//Κλείσιμο File

    fclose(fPtr);

/*
//Τύπωμα Μητρώου Γετνίασης(optional)

   printf("\n\n");

   for(i = 1; i < V+1; i++)
        {
            for(j = 1; j < V+1; j++)
            {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }
*/


//Αρχικοποίηση ουράς S

    int queueS[V];

    for(i=0;i<V;i++){
        queueS[i]=0;
    }


//Αρχικοποίηση πίνακα που περιέχει τη τοπολογική

    int topo_order[V];

    for(i=0;i<V;i++){
        topo_order[i]=0;
    }


//Εισαγωγή στην ουρά S

    void insert_queue(int v){
        if(rear == V-1 ){
            printf("Not enough space ");
        }
        else{
	    #pragma omp task shared(front)
            {
	    if(front == -1){
                front=front+1;
            }
            rear+=1;
	    #pragma omp taskwait
            queueS[rear]=v;
        }}
    }


//Διαγραφή απο ουρά S

    int delete_queue(){
        int del_vert;
	#pragma omp task shared(del_vert)
        {del_vert=queueS[front];}
	#pragma omp taskwait
        queueS[front]=0;
        front=front+1;
        return del_vert;
    }

//Εύρεση βαθμών

    int degrees[V];

    for(i=0;i<V;i++){
        int sum=0;
        for(j=0;j<V;j++){
            sum	+=arr[j][i];
            degrees[i]=sum;
        }
    }

/*//Τύπωμα Βαθμών Κόμβων(optional)

    printf("\n\nDegrees of nodes are:\n");
    for(i=0;i<V;i++){
        printf("%d ", degrees[i]);
    }

*/
    printf( "\n");


//Τοπολογική Διάταξη

    int num_threads = 4;

    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    printf("Before parallel version. \n Seconds : %ld\n  Micro seconds : %ld", current_time.tv_sec, current_time.tv_usec);


    printf( "\n");

 #pragma omp parallel num_threads(num_threads)
 {
    #pragma omp single
    {
        for(i=0;i<V;i++){
            if(degrees[i]==0)
                #pragma omp task firstprivate(i)
                insert_queue(i);
        }
    }
 }

    place=0;


   while(front!=-1){
    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp single
        {


            v=delete_queue();
            topo_order[place]=v;
            if(front==V){front=-1;}
            place=place+1;
            for(j=0; j<V; j++){
                if(arr[v][j]==1){
                    arr[v][j]=0;
                    degrees[j]=degrees[j]-1;
                        if(degrees[j]==0)
                            #pragma omp critical
                            insert_queue(j);
                }
            }
        }
    }
   }

  gettimeofday(&current_time, NULL);
  printf("After parallel version. \n Seconds : %ld\n Micro seconds : %ld",current_time.tv_sec, current_time.tv_usec);


    printf( "\n");

    printf("\n\nTopological order is: ");
    for(i=0; i<V; i++)
        printf( "%d ",topo_order[i] );


    printf( "\n");



  return 0;
}//End of main()
