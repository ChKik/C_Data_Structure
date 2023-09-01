#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 1406


struct data{
        char date[10];
        float pho;
    };


void CountingSort(struct data *array,int n);

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
  for(i=0;i<N-1;i++)
    {
        printf("\n%s \t%4.2f",day[i].date,day[i].pho);
    }


 printf("\n-----------------------------------------------------------");
 printf("\nThe sorted dates according to the phosphate values are: \n");

 clock_t begin=clock();

 CountingSort(day,N);

clock_t end=clock();

  //Epanafora twn dekadikwn arithmwn phoshpate
  for(int i=0; i<N; i++)
     day[i].pho=day[i].pho/100;


//Taksinomhmeno arxeio
    for(i=0;i<N-1;i++)
        printf("\n%s \t%4.2f",day[i].date,day[i].pho);


 //Peiramatikh Diadikasia
  printf("\n\nThe execution time of CountingSort is: %f seconds\n",(double)(end-begin)/CLOCKS_PER_SEC);

 //Kleisimo arxeiou kai apodesmeush ths mnhmhs pou desmeusame dynamika
   fclose(ocean);
   free(day);
 }

void CountingSort(struct data *array,int n)
{


    float array1[n];
    float count[n];
    float x=(array[0].pho); //temporary metablhth


    //Metatroph twn arithmwn phosphate se akeraious gia thn xrhsh tou Counting Sort
    for(int i=0; i<n; i++)
        array[i].pho=array[i].pho*100;


    for(int i=1; i<n; i++)
    {
        if(array[i].pho>x)
         x=array[i].pho;
    }

    for(int i=0; i<=x; ++i)
        count[i]=0;


    for(int i=0; i<n; i++)
        count[(int)array[i].pho]++;

    for(int i=1; i<=x; i++)
        count[i]+=count[i-1];

    for(int i=n-1; i>=0; i--)
    {
        array1[(int)count[(int)array[i].pho]-1]=array[i].pho;
        count[(int)array[i].pho]--;
    }

    for(int i=0; i<n; i++)
        array[i].pho=array1[i];


}
