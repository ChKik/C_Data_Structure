#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 1406
#define list temp           //ama theloume o kwdikas na psaxnei gia pho, vazoume pho anti gia temp

struct data{
    char date[10];
    float pho;
    float temp;
};

void InsertionSort(struct data *day);
int bisSearch(struct data *day, float x);
int bisSearchImproved(struct data day[N], float x);

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

    while( ch!=EOF){

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
    InsertionSort(day);
    for(i=0;i<N-1;i++){
        printf("\n%d %s\t%f\t%f",i,day[i].date,day[i].temp, day[i].pho);
    }

    printf("\n\nDo you want to search with the improved algorithm? (y/n)");
    scanf("%c",&ch);
    while(ch!='y' && ch!='n'){
            fflush(stdin);
        printf("Wrong input, please try again\n");                      //Amuntikos programmatismos
        scanf("%c",&ch);
    }
    printf("\nWhat value do you want to search for?");                   //Vazoume thn timh pou theloume na eisagoume
    scanf("%f",&value);
    if((value<day[0].list) || (value>day[N-2].list)){                     //Periptwsh pou den uparxei sto sunolo timwn tou pinaka
        printf("Value not found");
    }
    else{
        if(ch=='y'){g=bisSearchImproved(day,value);}                                      //Kalw thn BIS
        else if(ch=='n'){g=bisSearch(day,value);}
        if(g!=-1)
            printf("\nThe date with a value of %f is: %s",value,day[g].date);   //Tupwsh apotelesmatos
        else
            printf("\nValue not found");
    }


    //Kleisimo arxeiou
    fclose(ocean);
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

int bisSearch(struct data day[N], float x){
	int left=0;
	int right=N-2;
	int size=right-left;
	int i;
	int next=(int)ceil((size*(x-day[left].list)/(day[right].list-day[left].list)))+1;
    if(x==day[right].list)        //Periptwsh pou einai to 1o h to teleutaio stoixeio
       return right;
    if(x==day[left].list)
       return left;

	while (x!=day[next].list){
		i=0;
		size=right-left;
		if (size<=3){

			if(x==day[left].list){return left;}
            else if(x==day[left+1].list){return left+1;}
            else if(x==day[right].list){return right;}
            return -1;
		}
		if (x>= day[next].list){
			while (x>day[next+i*((int)sqrt(size))-1].list && next+i*((int)sqrt(size))-1<N) {i=i+1;}      //Prosthesa mia parapanw sunthhkh sto while epeidh evgaine eksw apo ta oria tou pinaka
			right=next+(int)(i*sqrt(size));
			left=next+(int)((i-1)*sqrt(size));
		}
		else if (x<day[next].list){
			while (x<day[next -i*((int)sqrt(size))+1].list && next+i*((int)sqrt(size))-1>0){i=i+1;}
			right=next-(int)((i-1)*sqrt(size));
			left=next-(int)(i*sqrt(size));
		}
		next=(int)ceil((left+(((right-left+1)*(x-day[left].list)/(day[right].list-day[left].list))))-1);

	}
	if (x==day[next].list){return next;}
		else return -1;
}

int bisSearchImproved(struct data day[N], float x){
	int left=0;
	int right=N-2;
	int size=right-left;
	int i;
	int next=(int)ceil(((size*((x-day[left].list)/(day[right].list-day[left].list)))))+1;
    if(x==day[right].list)        //Periptwsh pou einai to 1o h to teleutaio stoixeio
       return right;
    if(x==day[left].list)
       return left;

	while (x!=day[next].list){
		i=1;
		size=right-left;
		if (size<=3){
			if(x==day[left].list){return left;}
            else if(x==day[left+1].list){return left+1;}
            else if(x==day[right].list){return right;}
            return -1;
		}
		if (x>= day[next].list){
			while (x>(int)day[next+i*((int)sqrt(size))-1].list && next+i*((int)sqrt(size))-1<N) {i=i*2;} //STON KAKO EINAI I+=1, EDW EINAI H MONH ALLAGH
			right=next+(int)(i*sqrt(size));
			left=next+(int)((i-1)*sqrt(size));
		}
		else if (x<day[next].list){
			while (x<day[next -i*((int)sqrt(size))+1].list && next -i*((int)sqrt(size))+1>0){i=i*2;} //>>    >>     >>      >>      >>      >>
			right=next-(int)((i-1)*sqrt(size));
			left=next-(int)(i*sqrt(size));
		}
		next=(int)ceil((left+(((right-left+1)*(x-day[left].list)/(day[right].list-day[left].list))))-1);

	}
	if (x==day[next].list){return next;}
		else return -1;
}
