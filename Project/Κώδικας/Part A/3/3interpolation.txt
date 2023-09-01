

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 1406
#define list temp           //ama theloume o kwdikas na psaxnei gia pho, vazoume pho anti gia temp

struct data{
    char date[10];
    float pho;
    float temp;
};

void InsertionSort(struct data *day);
int interpolationSearch(struct data *day, float x);

int main()
{
    char ch;
    int linesch=-2; //plhthos grammwn
    int komma=0; //metraw kommata sto arxeio ocean
    float value;
    char p[10];
    char d[11];
    char t[10];
    int g;
    int i; //counter1

    struct data *day;                        //dunamikh desmeush ths struct
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

    InsertionSort(day);                                                    //Taksinomhsh to struct array
    for(i=0;i<N-1;i++){
        printf("\n%d %s\t%f\t%f",i,day[i].date,day[i].temp, day[i].pho);
    }



    printf("\n\nWhat value do you want to search for?");                   //Vazoume thn timh pou theloume na eisagoume
    scanf("%f",&value);

        clock_t begin=clock();
        g=interpolationSearch(day,value);                                   //Kalw thn interpolation search
        clock_t end=clock();



        if(g!=-1)
            printf("\nThe date with a value of %f is: %s",value,day[g].date);   //Tupwsh apotelesmatos
        else
            printf("\nValue not found");

            printf("\n\nThe execution time of InterpolationSearch is: %f seconds\n",(double)(end-begin)/CLOCKS_PER_SEC);

    //Kleisimo arxeiou kai apodesmeush ths mnhmhs pou desmeusame dunamika
    fclose(ocean);
    free(day);
    return 0;

}

void InsertionSort(struct data *day){
    char tempstring[51];
    int prohgoymenos,epomenos,counter,i,j=0;
    float twrinos,tempfloat;

    for (i=1;i<N-1;i++){
        twrinos=day[i].list;
        strcpy(tempstring,day[i].date);
        prohgoymenos=i-1;

            while((prohgoymenos>=0)&&(day[prohgoymenos].list>twrinos)){
            day[prohgoymenos+1].list=day[prohgoymenos].list;
            strcpy(day[prohgoymenos+1].date,day[prohgoymenos].date);
            prohgoymenos=prohgoymenos-1;
            }
        day[prohgoymenos+1].list=twrinos;
        strcpy(day[prohgoymenos+1].date,tempstring);
    }
}

int interpolationSearch(struct data *day, float x){
    int left=0;
    int right=N-2;
    int next=((x-day[left].list)/(day[right].list-day[left].list))*(right-left)+left;
    while(x!=day[next].list && left<right){
        if(x<=day[next].list){right=next-1;}
        else {left=next+1;}
        next=((x-day[left].list)/(day[right].list-day[left].list))*(right-left)+left;
    }
    if(x==day[next].list){return next;}
    else return -1;
}
