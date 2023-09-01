#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#define N 1406
#define list temp           //ama theloume o kwdikas na psaxnei gia pho, vazoume pho anti gia temp
#define true 1

typedef struct data{
    char date[10];
    float pho;
    float temp;
}Data;

void InsertionSort(struct data *day);
void QuickSort(struct data *day,int mikroteros,int megaluteros);
void SwapDateTemp(struct data *day1,int a,int c);  //kanei switch metaksu 2 date ta string kai tis temp toys
void Printer(struct data *day);
int partisionQS(struct data *day,int mikroteros,int megaluteros);

void Printer(struct data *day){
    int i;
 printf("Algorithm executed successfully!\n Date\t\t Temperature\n");
    for (i=0;i<N-1;i++){
        printf("\n%s \t%0.2f\t\t",day[i].date,day[i].temp);   //kanei sorting alla den vlepei oles tis times gia kapoio logo
    }
}


int main()
{
    int choice;
    char ch;
    int linesch=-2; //plhthos grammwn
    int komma=0; //metraw kommata sto arxeio ocean
    float value;
    char p[10];
    char d[11];
    char t[10];
    int g;
    int i; //counter1

    Data *day;                        //dunamikh desmeush ths struct
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

    while(ch!=EOF){

    ch=fgetc(ocean);

    if(linesch>-2 && ch==',')
        {komma++;}

    if(linesch>-2){
        if(komma==0){
            d[i]=ch;
            i++;
        }

        if(komma==1){
            if(ch!=','){            //gia na mhn mpainei to , ston pinaka t[]
            t[i]=ch;
            i++;
        }
        else i=0;
        }

        if(komma==2){
            if(ch!=','){            //gia na mhn mpainei to , ston pinaka p[]
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
        day[linesch].temp=atof(t);
        for(i=0;i<10;i++){p[i]='\0';}
        for(i=0;i<11;i++){d[i]='\0';}
        for(i=0;i<10;i++){t[i]='\0';}
        komma=0;
        i=0;
     }
 }
      printf("\nCounter\t  Date\t\t Temperature\t\n");
      for(i=0;i<N-1;i++){
        printf("\n%d\t %s\t\t%.02f\t",i,day[i].date,day[i].temp);  //ektupwseis toy database
    }

printf("\n\n");
fflush(stdin); //flush to stdin channel gia na min exoyme provlhmata sto choice

printf(" |-----------------------------------|\n");
printf(" |1)Sort the data by Insertion Sort  |\n");
printf(" |2)Sort the data by Quick Sort      |\n");
printf(" |3)Exit                             |\n");
printf(" |-----------------------------------|\n");

/*if (ch==NULL)printf("edw einai EOF\n"); //einai NULL edw to ch giati paei stin sunarthsh den einai me pointer
else printf("\t ontws ? %d \t",ch);
rewind(ocean);*/


while(true){
printf("Please select an option from the menu:\t\n");  //menu me amuntiko programmatismo
scanf("%d",&choice);
if ((choice==1)||(choice==2)||(choice==3))break;}

switch (choice){
    case 1:
    system("cls");//katharizei tin othoni apo ta noymera ta prohgoymena
    printf("Insertion Sort Algorithm initiating\n");  //cases me toys algorithmous
    clock_t begin=clock();
    InsertionSort(day);
    clock_t end=clock();
    printf("\n\nThe execution time of InsertionSort is: %f seconds\n",(double)(end-begin)/CLOCKS_PER_SEC);
    Printer(day);

    break;

    case 2:
    system("cls");//katharizei tin othoni apo ta noymera ta prohgoymena
    printf("Quick Sort Algorithm initiating\n");
    clock_t tik=clock();
    QuickSort(day,0,N-1); // to N-1 einai to 1405
    clock_t tok=clock();
    printf("\n\nThe execution time of QuickSort is: %f seconds\n",(double)(tok-tik)/CLOCKS_PER_SEC);

    Printer(day);
    //SwapDateTemp(day,0,N-2);
    break;

    case 3: printf("Exiting the program!\n");
    exit(0);
    break;
    }

    fclose(ocean);
    free(day);
    return 0;



}


void InsertionSort(struct data *day){  //insertion algorithmos




char tempstring[51];

int prohgoymenos,epomenos,counter,i,j=0;
float twrinos,tempfloat;

for (i=1;i<N-1;i++){
    twrinos=day[i].temp;
    strcpy(tempstring,day[i].date);
    prohgoymenos=i-1;

        while((prohgoymenos>=0)&&(day[prohgoymenos].temp>twrinos)){
        day[prohgoymenos+1].temp=day[prohgoymenos].temp;
        strcpy(day[prohgoymenos+1].date,day[prohgoymenos].date);
        prohgoymenos=prohgoymenos-1;
        }
    day[prohgoymenos+1].temp=twrinos;
    strcpy(day[prohgoymenos+1].date,tempstring);
}


//telos insertion
}




void SwapDateTemp(struct data *day,int a,int b){
    int i;
//if(c==1405)b=1404; //mhpws eftaige to teleutaio array den kserw akoma psilovazei tin seira
//else

struct data swapptr; //voithikos pointer

strcpy(swapptr.date,day[a].date);
swapptr.temp=day[a].temp;



strcpy(day[a].date,day[b].date);
day[a].temp=day[b].temp;  // o a pairnei toy b
//printf("edw prepei na typwsei toy b: %s  kai to temp: %f \n",day[a].date,day[a].temp); //paei to b sto a

strcpy(day[b].date,swapptr.date); //paei sto temp to b sto a
day[b].temp=swapptr.temp;
//printf("edw prepei na typwsei toy a::%s kai to temp : %f \n",day[b].date,day[b].temp);
//int test=(int)day[a].temp;
//printf("TEST ARRAY     %d",test); //doulevei
}


int partisionQS(struct data *day,int mikroteros,int megaluteros){ //PartisionQS //megaluteros 1405
float pivot=0;
int i,j,high=0;

if (megaluteros==1405)high=1404; //giati exoyme to N=1405 alla megaluterh timh to day[1404]
else high=megaluteros;

pivot=day[high].temp; //etsi exw to day[1404] poy einai to teleutaio
i=mikroteros-1;

int tempday,temppivot;

for (j=mikroteros;j<high;j++){
        tempday=((int)(day[j].temp*100)); //* 100 gia na ginei h sugkrish kai na einai integer kai thelei kai parentheseis alliws den ginotan swsta giati to ekane prwta int kai meta *100
        temppivot=((int)(pivot*100));   //me apotelesma na xanoyme to 10diko meros
    if (tempday<=temppivot){
        i++;
        SwapDateTemp(day,i,j);
    }
}
SwapDateTemp(day,i+1,high);
return (i+1);
}



void QuickSort(struct data *day,int mikroteros,int megaluteros){  //QS
 /*epeidh exoyme float arithmoys me 2 arithmoys sto klassmatiko meros prepei na kanoyme
 oles tis temp*100 gia na einai int kai na ginei swsta o QuickSort*/
 int i,j=0;
 int QSpart;


   if (mikroteros<megaluteros){
     QSpart=partisionQS(day,mikroteros,megaluteros);



     QuickSort(day,mikroteros,QSpart-1); //gia ta aristera toy pivot
     QuickSort(day,QSpart+1,megaluteros); //gia ta deksia toy pivot
    }



}



