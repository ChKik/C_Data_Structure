#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 1406


struct data{
        char date[10];
        float pho;
    };


void swap(int *a, int *b);
void heapify(struct data *array,int n,int i);
void HeapSort(struct data *array,int n);

main()
{
  char ch;
  int linesch=-2; //plhthos grammwn
  int komma=0; //metraw kommata sto arxeio ocean
  char p[10];
  char d[11];
  char t[10];
  int i; //counter1

  struct data *day;

    //Desmeush mnhmhs gia thn domh
    day=malloc(sizeof(struct data)*N);

    if(day==NULL)
    {
        printf("Adunamia demseushs mnhmhs");
        exit(0);

    }

    FILE *ocean;
    ocean=fopen("ocean.txt","r"); //diabazei to arxeio kai elegxei an anoigei epituxws

    if(ocean!=NULL)
        printf("Success in opening file ocean \n");

    else
        {
            printf("Error in opening file");
            exit(0);
    }



    //Diabasma arxeiou

    while(ch!=EOF){

    ch=fgetc(ocean);

    if(linesch>-2 && ch==',')
        {komma++;}

    if(linesch>-2)
     {
        if(komma==0)
        {
            d[i]=ch;
            i++;
        }


        if(komma==2)
        {
           if(ch!=',')
           {            //gia na mhn mpainei to , ston pinaka p[]
            p[i]=ch;
            i++;
           }
        else
          i=0;

        }
    }

    if(ch=='\n')
        {
        linesch++; //+1 gia tis grammes}
        strcpy(day[linesch].date,d);
        day[linesch].pho=atof(p);

        for(i=0;i<10;i++){p[i]='\0';}
        for(i=0;i<11;i++){d[i]='\0';}

        komma=0;
        i=0;
     }



 }


 //Ektupwsh tou arxikou arxeiou ocean
 for(i=0;i<N-1;i++){
        printf("\n%s \t%4.2f",day[i].date,day[i].pho);
    }


printf("\n-----------------------------------------------------------");
printf("\nThe sorted dates according to the phosphate values are: \n");


  clock_t tic=clock();

  HeapSort(day,N);

  clock_t toc = clock();

//Taksinomhmeno arxeio
    for(i=0;i<N-1;i++){
        printf("\n%s \t%4.2f",day[i].date,day[i].pho);
    }


  //Peiramatikh Diadikasia
  printf("\n\nThe execution time of HeapSort is: %f seconds\n",(double)(toc-tic)/CLOCKS_PER_SEC);

 //Kleisimo arxeiou kai apodesmeush ths mnhmhs pou desmeusame dynamika
   fclose(ocean);
   free(day);



 }


void swap(int *a, int *b)
{
   int temp;
   temp=*a;
   *a=*b;
   *b=temp;

}

//Briskoume ton megalutero arithmo kai ton topothetoume sthn riza
void heapify(struct data *array,int n,int i)
{
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;

    if(left<n && array[left].pho>array[largest].pho)
      {largest=left;}

    if(right<n && array[right].pho>array[largest].pho)
      {largest=right;}

    //Kanoume swap tous kombous kai sunexizoyme me anadromikh klhsh ths sunarthshs an h riza den einai o megalyteros arithmos
    if(largest!=i)
    {
        swap(&array[i].pho,&array[largest].pho);
        heapify(array,n,largest);
    }

}

void HeapSort(struct data *array,int n)
{
    //Dhmiourgoume ton megisto swro
     for (int i=n/2-1; i>=0; i--)
      heapify(array, n, i);

    //HeapSort
     for (int i=n-1; i>=0; i--)
     {
      swap(&array[0].pho, &array[i].pho);

    //Pame to megalutero stoixeio sthn riza
      heapify(array, i, 0);
    }
}
