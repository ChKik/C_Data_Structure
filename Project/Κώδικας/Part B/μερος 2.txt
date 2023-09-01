#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <conio.h>
#define N 1406
#define true 1
#define max(x,y) (((x) >= (y)) ? (x) : (y))
#define HASHCHAINSIZE 23

typedef struct Node{
    char date[10];
    float pho;
    float temp;
    bool hasDupe;           //Gia na vlepoume an exei idies thermokrasies
    struct Node *dupe;
    struct Node *left;
	struct Node *right; //gia to HASH tha to xrisimopoihsw san to next node enw gia to AVL einai to right
	int upsos;     // upsos gia tous periorismous twn AVL
	int asciivalue;
}Data;
// tha valw san noumero gia to size toy HASH array to 23 giati einai enas kalos prwtos arithmos poy apexei kalh apostash apo to 2^5 kai to 2^4
Data *hashchain[HASHCHAINSIZE];

struct Node* minTemp(struct Node* node);

struct Node* maxTemp(struct Node* node);

struct Node *search(struct Node *root,char *date);

struct Node *change(struct Node *root,char *date, float temp);

int compare(char date1[10],char date2[10]);

int getHeight(struct Node *node);//ypologismos tou upsos kathe komvou

struct Node *newNode(char *date,float T_degC, float PO4um);

struct Node *insertion(struct Node *node,char *date, float T_degC, float PO4um);

struct Node *insertionTemp(struct Node *node,char *date, float T_degC, float PO4um);

void printTreeInorder(struct Node *root);

int getHB(struct Node *node);

struct Node *deletion(struct Node *root,char *date);

struct Node *lRot(struct Node *node);

struct Node *rRot(struct Node *node);

struct Node *stabilize(struct Node *node,char *date);

struct Node *stabilizeTemp(struct Node *node,float temp);

struct Node *MVN(struct Node *node);


int main()
{
    struct Node *root = NULL;
    struct Node *node = NULL;
    int choice,choice2;
    float inputF;
    char inputS[10];
    char ch;
    int linesch=-2; //plhthos grammwn
    int komma=0; //metraw kommata sto arxeio ocean
    float value;
    char p[10];
    char d[11];
    char t[10];
    int g;
    int i; //counter1
    int tempval=0;

    struct Node *day;                        //dunamikh desmeush ths struct
    day=malloc(sizeof(struct Node)*N*20);
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
            tempval=tempval+(ch);        //hashing
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
        linesch++; //+1 gia tis grammes}            //orizw se kathe day thn hmeromhnia se string, pho kai temp se float.
        strcpy(day[linesch].date,d);
        day[linesch].asciivalue=tempval;            //hashing
        day[linesch].pho=atof(p);
        day[linesch].temp=atof(t);
        for(i=0;i<10;i++){p[i]='\0';}               //Katharismos pinakwn
        for(i=0;i<11;i++){d[i]='\0';}
        for(i=0;i<10;i++){t[i]='\0';}
        komma=0;
        i=0;
        tempval=0;
     }
}


      printf("\nCounter\t  Date\t\t Temperature\t\n");
      for(i=0;i<N-1;i++){
        printf("\n%d\t %s\t\t%.02f\t",i,day[i].date,day[i].temp);  //ektupwseis toy database
}

printf("\nChoose the method you want to data to be loaded into:\n");

printf(" |---------------------------------------------|\n");
printf(" |1)Insert the data with an AVL by date        |\n");
printf(" |2)Insert the data with an AVL by temperature |\n");
printf(" |3)Insert the data with a HASH function       |\n");
printf(" |4)Exit                                       |\n");
printf(" |---------------------------------------------|\n");



while(1==1){
printf("Please select an option from the menu:\t\n");  //menu me amuntiko programmatismo
scanf("%d",&choice);
while(choice<1 || choice>4){
    printf("Wrong Input, try again\n");
    scanf("%d",&choice);}

switch (choice){
    case 1:
        system("cls");
        for(i=0;i<1405;i++){
            root = insertion(root, day[i].date,day[i].temp,day[i].pho);}
        while(1==1){
        printf("\n |-------What action do you want to take?------|\n");
        printf(" |                                             |\n");
        printf(" |1)Print tree inorder                         |\n");
        printf(" |2)Search for a date's temperature            |\n");
        printf(" |3)Change a date's temperature                |\n");
        printf(" |4)Delete a date                              |\n");
        printf(" |5)Exit                                       |\n");
        printf(" |---------------------------------------------|\n");

        scanf("%d",&choice);
        while(choice<0 || choice>5){
            printf("Wrong Input, try again\n");
            scanf("%d",&choice);}
        switch(choice){
            case 1:                                             //1)Print tree inorder
                printTreeInorder(root);
                break;
            case 2:                                             //2)Search for a date's temperature
                printf("\nPlease enter the date you wish to search (DD/MM/YYYY)\n");
                scanf("%s",inputS);
                while(strlen(inputS)!=10){
                    printf("Wrong date input, please try again.\n");     //Amuntikos programmatismos, opws kai sta epomena 2 cases
                    scanf("%s",inputS);}
                node=search(root,inputS);
                if(node!=NULL)
                    printf("The date's temperature is: %f",node->temp);
                break;
            case 3:                                             //3)Change a date's temperature
                printf("Please enter the date you wish to change (example (DD/MM/YYYY)\n");
                scanf("%s",inputS);
                while(strlen(inputS)!=10){
                    printf("Wrong date input, please try again.\n");
                    scanf("%s",inputS);}
                printf("Please enter the new temperature\n");
                scanf("%f",&inputF);
                change(root,inputS,inputF);
                break;
            case 4:                                                 //4)Delete a date
                printf("Please enter the date you wish to delete (example (DD/MM/YYYY)\n");
                scanf("%s",inputS);
                while(strlen(inputS)!=10){
                    printf("Wrong date input, please try again.\n");
                    scanf("%s",inputS);}
                deletion(root,inputS);
                break;
            case 5:                                             //5)Exit
                printf("Exiting the program!\n");
                exit(0);
                break;
        }
        }
    case 2:
        system("cls");
        for(i=0;i<1405;i++){
            root = insertionTemp(root, day[i].date,day[i].temp,day[i].pho);}
        while(1==1){
        printf("\n |-------What action do you want to take?------|\n");
        printf(" |                                             |\n");
        printf(" |1)Dates with the smallest temperature        |\n");
        printf(" |2)Dates with the highest temperature         |\n");
        printf(" |3)Exit                                       |\n");
        printf(" |---------------------------------------------|\n");

        scanf("%d",&choice);
        while(choice<0 || choice>5){
            printf("Wrong Input, try again\n");
            scanf("%d",&choice);}
        switch(choice){
            case 1:                             //1)Dates with the smallest temperature
                node=minTemp(root);
                printf("The date with the smallest temperature is:\n%s",node->date);
                while(node->hasDupe){           //Periptwsh pou einai panw apo mia hmeromhnies
                        node=node->dupe;
                        printf("\n%s",node->date);
                }
                printf("\n");
                break;
            case 2:                                 //2)Dates with the highest temperature
                node=maxTemp(root);
                printf("The date with the highest temperature is:\n%s",node->date);
                while(node->hasDupe){               //Periptwsh pou einai panw apo mia hmeromhnies
                        node=node->dupe;
                        printf("\n%s",node->date);
                }
                printf("\n");
                break;
            case 3:
                printf("Exiting the program!\n");
                exit(0);
                break;

        }
        }

    case 3:
    system("cls");      //EDW ARXIZEI TO HASHING   EDW ARXIZEI TO HASHING   EDW ARXIZEI TO HASHING   EDW ARXIZEI TO HASHING   EDW ARXIZEI TO HASHING   EDW ARXIZEI TO HASHING   EDW ARXIZEI TO HASHING
    system("cls");//katharizei tin othoni apo ta noymera ta prohgoymena //---------EDW THA EINAI TO HASHING---------
    for (i=0;i<HASHCHAINSIZE;i++){
        hashchain[i]=NULL;  //initialization toy hashchain me null
        }

int key=0;
int counter=0;

    for (i=0;i<N-1;i++){
       //den exoyme provlhma me tin arithmitikh float edw giati sugkrinoyme to sunolo twn ascii ths hmeromhnias

        key=(day[i].asciivalue)%(HASHCHAINSIZE); //to asciivalue toy day   dia 23
        printf("%d : %d\n",i,key);
        if (hashchain[key]==NULL){ //ama einai adeio vazoyme to day[i] sto haschain me to katallhlo key
        hashchain[key]=(day+i); //day+i gia na paei na deiksei o pointer sto epomeno day
        }
            else { //exoyme collision kai prepei na paei sto telos toy  right to epomeno day
                    Data *tempcarrier=hashchain[key];
                    while(tempcarrier->right){
                    tempcarrier=tempcarrier->right;  //to right einai san to next edw apla den to allazw giati yparxei sto AVL dentro
                }
            tempcarrier->right=(day+i); //vrikame ton pio deksio poy einai NULL kai toy vazoyme to day+i

                }
          }    //HASHING WITH CHAINING DONE


    for(i=0;i<HASHCHAINSIZE;i++){
        Data *hash_printer=hashchain[i];
        printf("\n\nChain Number %d: ",i);
        while(hash_printer){//oso den einai null typwnei
            printf("->%.02f",hash_printer->temp); //typwnw to temp
            hash_printer=hash_printer->right; //paei sto next
    }

    }
    printf("\nHashing with chaining procedure has been completed \n");  //DOULEVEI TO HASHING



    while (1==1){
    //EPILOGES GIA TO MENU TOY HASHING
    printf("What would you like to do with your hash table? \n");  //cases me toys algorithmous
    printf(" |---------------------------------------------|\n");
    printf(" |1)Search a temperature by date               |\n");
    printf(" |2)Edit a temperature with date input         |\n");
    printf(" |3)Delete a temperature with date input       |\n");
    printf(" |4)Exit                                       |\n");
    printf(" |---------------------------------------------|\n");
    while(true){
    printf("Please select an option from the menu:\t\n");  //menu me amuntiko programmatismo
    scanf("%d",&choice2);
    if ((choice2==1)||(choice2==2)||(choice2==3)||(choice2==4))break;}

    if(choice2==1){ //ANAZHTHSH THERMOKRASIAS VASH HMEROMHNIAS
    system("cls");

     char date_search[10];
     int date_search_sum=0;
     int search_key=0;
     int date_match;
     int date_found;
     i=0;


    while(true){ //gia test to while //stamataei na leitourgei stin deuterh hmeromhnia
    fflush(stdin);
    printf("\nGive a date to search in the database:\nMM/DD/YYYY\n");
    gets(date_search);
    if (strlen(date_search)==10)break;
    else printf("Wrong date input");
    }

        while(date_search[i]!='\0'){
            date_search_sum=date_search_sum+(date_search[i]); //ascii value tis imerominias poy psaxnw
            i++;
        }


    search_key=date_search_sum%HASHCHAINSIZE; //to search key tha exei tin timh toy bucket poy psaxnoyme

    Data *temp_search=hashchain[search_key];

    while(temp_search){  //oso to temp_search->right den einai NULL psaxnei gia to epomeno stoixeio
     //checharw ama einai idia ta dates

    if ((temp_search->asciivalue==date_search_sum)) //to search sto bucket kai an yparxei h hmerominia ayth sto database mas
        { //2 hmerominies mporei na exoyn to idio ascii noymero ara prepei na valw kai to string toy date na einai to idio
            date_match=strcmp(temp_search->date,date_search);
            if(date_match==0){
            date_found=1;
            break;}
         }
    temp_search=temp_search->right;
    }

    if(date_found==1)
    printf("Date %s you entered has a registered temperature of %.02f in bucket No %d of the hash chain\n ",date_search,temp_search->temp,search_key);
    else
    printf("The date you entered does not exist in our database!");
    }


    if(choice2==2){ //TROPOPOIHSH THS THERMOKRASIAS VASH HMEROMHNIAS POY THA DINETAI APO TON XRHSTH
    system("cls");

     char date_search[10];
     int date_search_sum=0;
     int search_key=0;
     int date_match;
     int date_found;
     char answer;
     float tempfloat=0;
     i=0;


    while(true){
    fflush(stdin);
    printf("\nGive a date to search in the database:\nMM/DD/YYYY\n");
    gets(date_search);
    if (strlen(date_search)==10)break;
    else printf("Wrong date input");
    }

        while(date_search[i]!='\0'){
            date_search_sum=date_search_sum+(date_search[i]); //ascii value tis imerominias poy psaxnw
            i++;
        }


    search_key=date_search_sum%HASHCHAINSIZE; //to search key tha exei tin timh toy bucket poy psaxnoyme

    Data *temp_search=hashchain[search_key];

    while(temp_search){  //oso to temp_search->right den einai NULL psaxnei gia to epomeno stoixeio
     //checharw ama einai idia ta dates

    if ((temp_search->asciivalue==date_search_sum)) //to search sto bucket kai an yparxei h hmerominia ayth sto database mas
        { //2 hmerominies mporei na exoyn to idio ascii noymero ara prepei na valw kai to string toy date na einai to idio
            date_match=strcmp(temp_search->date,date_search);
            if(date_match==0){
            date_found=1;
            break;}
         }
    temp_search=temp_search->right;
    }


    if(date_found==1){
    printf("Date %s you entered has a registered temperature of %.02f \n\n",date_search,temp_search->temp);
    while(true){
    printf("Would you like to edit the temperature for that date? Type y/n \n");
    fflush(stdin);
    scanf("%c",&answer);
    if (answer=='y')
        {
        printf("Enter the temperature you would like to edit the date with:\n");
        fflush(stdin);
        scanf("%f",&tempfloat);
        temp_search->temp=tempfloat;
        printf("The temperature of the date %s has been edited to %.02f Celsius \a",date_search,temp_search->temp); //ama exei kanei edit tin thermokrasia tote tha kanei print edw tin edited temp


        while(true){  //printer twn hashchain pali
        printf("\n\nWould you like to print the hashing chains again? Type y/n\n");
        fflush(stdin);
        scanf("%c",&answer);
            if (answer=='y')
            {
                for(i=0;i<HASHCHAINSIZE;i++){
                    Data *hash_printer=hashchain[i];
                printf("\n\nChain Number %d: ",i);
                    while(hash_printer){//oso den einai null typwnei
                printf("->%.02f",hash_printer->temp); //typwnw to temp
                hash_printer=hash_printer->right; //paei sto next
                                        }
                                            }
            printf("Press any key to exit the program!\n");
            getchar();//perimenei ton xrhsth na pathsei ena key gia na kanei exit ama thelei na dei ta chains
            exit(0);
            }
                if(answer=='n')
                {
                printf("Thank you for using our program!");
                exit(0);
                }
                    }


        }
        if(answer=='n')
            {
            printf("Thank you for using our program!");
            exit(0);
            }
        }
    }
    else
    printf("The date you entered does not exist in our database!");

}//telos choice2
    //ETOIMH KAI H EDIT EPILOGH

    if(choice2==3){ //DIAGRAFH MIAS EGGRAFHS APO TON PINAKA TOY HASHING POY THA DINETAI APO TON XRHSTH
    system("cls");
     char date_search[10];
     int date_search_sum=0;
     int search_key=0;
     int date_match=0;
     int date_found;
     char answer;
     i=0;


    while(true){
    fflush(stdin);
    printf("\nGive a date to delete from the database:\nMM/DD/YYYY\n");
    gets(date_search);
    if (strlen(date_search)==10)break;
    else printf("Wrong date input");
    }

        while(date_search[i]!='\0'){
            date_search_sum=date_search_sum+(date_search[i]); //ascii value tis imerominias poy psaxnw
            i++;
        }

    printf("\n\n");
    date_found=0;

    search_key=(date_search_sum)%(HASHCHAINSIZE); //to search key tha exei tin timh toy bucket poy psaxnoyme
    Data *datedeletion=hashchain[search_key];

/*exoyme 2 periptwseis stin diagrafh, to prwto node na exei tin timh poy thelei alliws to epomeno.
Ara prepei na koitaw kai sto epomeno panta kai na kanw tis aparaithtes allages stoys deiktes*/

     if((datedeletion->asciivalue==date_search_sum)&&(datedeletion))
        {//2 hmerominies mporei na exoyn to idio ascii noymero ara prepei na valw kai to string toy date na einai to idio
            date_match=strcmp(datedeletion->date,date_search);
            if(date_match==0){

            datedeletion=datedeletion->right;
            hashchain[search_key]=datedeletion;
            date_found=1; //etoimo to delete gia tin periptwsh poy to date einai prwto
            }
        }


        if((datedeletion)&&(date_found==0)){ //shmainei oti den einai sthn prwth thesh to date
            while(datedeletion->right)
            {                                                           //ama to epomeno date exei tin hmerominia poy theloyme
                if((datedeletion->right->asciivalue==date_search_sum))
                {        printf("%s,%.02f\n",datedeletion->date,datedeletion->temp);
                    date_match=strcmp(datedeletion->right->date,date_search);    //koitaw kai to string date oti einai to idio

                    if(date_match==0){                                   //tha diagraftei to epomeno date dhladh kai o pointer tha dixnei sto parapeomeno
                    datedeletion->right=datedeletion->right->right;       //prepei to epomeno date na parei to right toy paraepomenoy
                    date_found=1;
                    break; }//vrhkame to date
                }
              datedeletion=datedeletion->right;  //to temp_search koitaei sto epomenoi stoixeio tyo chain
            }
         }



    if(date_found==1) //edw tha ginetai h diagrafh
{
    printf("\nThe date %s you entered has been deleted from the database !\a\n",date_search);

while(true){
    printf("Would you like to print the hashing chains again? Type y/n\n");
    fflush(stdin);
    scanf("%c",&answer);
    if (answer=='y')
        {
            for(i=0;i<HASHCHAINSIZE;i++){
        Data *hash_printer=hashchain[i];
        printf("\n\nChain Number %d: ",i);
        while(hash_printer){//oso den einai null typwnei
            printf("->%.02f",hash_printer->temp); //typwnw to temp
            hash_printer=hash_printer->right; //paei sto next
        }
                                        }
        printf("Press any key to exit the program!\n");
        getchar();//perimenei ton xrhsth na pathsei ena key gia na kanei exit ama thelei na dei ta chains
        exit(0);
        }
    if(answer=='n')
    {
            printf("Thank you for using our program!");
            exit(0);
    }
  }
}
    else
    printf("The date you entered does not exist in our database!");

    }//telos diagrafhs




    if (choice2==4){ //EKSODOS APO TO PROGRAMMA
        printf("Exiting the program ! Goodbye !");
        exit(0);
    }


    break;



    break;

    case 4: printf("Exiting the program!\n");
    exit(0);
    break;
    }
}   //EDW TELEIWNEI TO HASHING         EDW TELEIWNEI TO HASHING         EDW TELEIWNEI TO HASHING         EDW TELEIWNEI TO HASHING         EDW TELEIWNEI TO HASHING         EDW TELEIWNEI TO HASHING


    free(day);
    fclose(ocean);
    return 0;
}
}
struct Node* minTemp(struct Node* node){        //Epistrefei to node me thn mikroterh thermokrasia
while (node->left != NULL)
    node = node->left;
return node;
}
struct Node* maxTemp(struct Node* node){        //>>      >>       >>    >>megaluterh thermokrasia
    while (node->left != NULL)
        node = node->right;
    return node;
}

int getHB(struct Node *node){
	if (node!=NULL){return getHeight(node->left) - getHeight(node->right);}
	else return 0;
};
void printTreeInorder(struct Node *node) {
	if (node != NULL){
	    printTreeInorder(node->left);
        printf("\n%s -> %f , %f", node->date, node->temp, node->pho);
        printTreeInorder(node->right);
    }
};

struct Node *stabilize(struct Node *node,char *date){
    int bal,x,y;
    node->upsos = max(getHeight(node->left),getHeight(node->right))+1;  //epanaferoume to stability
    bal=getHB(node);
    if(node->left!=NULL){
        x=compare(date,node->left->date);
        if(x==1 && bal>1)                  //Periptwsh pou thelei Right Rotation
            return rRot(node);
        else if(x==-1 && bal>1){           //Left Right Rotation
            node->left=lRot(node->left);
            return rRot(node);
        }
    }
    if(node->right!=NULL){
        y=compare(date,node->right->date);
        if(y==-1 && bal<-1)                //Left Rotation
            return lRot(node);
        else if(y==1 && bal<-1){           //Right Left Rotation
            node->right=rRot(node->right);
            return lRot(node);
        }
    }
        return node;
};
struct Node *stabilizeTemp(struct Node *node,float temp){
    int bal;
    node->upsos = max(getHeight(node->left),getHeight(node->right))+1;  //epanaferoume to stability
    bal=getHB(node);
    if(node->left!=NULL){
        if(temp < node->left->temp && bal>1)                  //Periptwsh pou thelei Right Rotation
            return rRot(node);
        else if(temp > node->left->temp && bal>1){           //Left Right Rotation
            node->left=lRot(node->left);
            return rRot(node);
        }
    }
    if(node->right!=NULL){
        if(temp > node->right->temp && bal<-1)                //Left Rotation
            return lRot(node);
        else if(temp < node->right->temp && bal<-1){           //Right Left Rotation
            node->right=rRot(node->right);
            return lRot(node);
        }
    }
        return node;
};

struct Node *MVN(struct Node* node){
struct Node *temp = node;
if (temp != NULL){
    while(temp->left != NULL) {temp = temp->left;}
    return temp;
}
};

struct Node *insertion(struct Node *node,char *date, float T_degC, float PO4um){
    int i;
    if(node != NULL ){
        i=compare(date,node->date);
	    if(i==1){ node -> left = insertion(node -> left,date,T_degC,PO4um);}                    //Otan to kleidi einai mikrotero ksanakalw thn insertion pros ta aristera
        else if(i==-1 || i==0)
                node -> right = insertion(node -> right,date,T_degC,PO4um);                     //Otan einai megalutero h iso, sta deksia
        else return node;
        stabilize(node,date);
    }
	else                                                                                        //Periptwsh exw adeio dentro
	 return newNode(date,T_degC,PO4um);
};


struct Node *insertionTemp(struct Node *node,char *date, float T_degC, float PO4um){
    if(node != NULL ){
	    if(T_degC<node->temp){ node -> left = insertionTemp(node -> left,date,T_degC,PO4um);}
        else if(T_degC>node->temp)
                node -> right = insertionTemp(node -> right,date,T_degC,PO4um);
        else if(T_degC==node->temp){
                struct Node *node2=node;                                                         //Periptwsh pou exoume thn idia thermokrasia
            while(node->hasDupe==true){node=node->dupe;}
            node->hasDupe=true;
            node->dupe=newNode(date,T_degC,PO4um);
            node=node2;         //Epeidh allaksa to node sthn while, to epanaferw sto arxiko node gia na to epistrepsw
            return node;
        }

        else return node;
        stabilizeTemp(node,T_degC);
    }
	else
	 return newNode(date,T_degC,PO4um);
};

struct Node *newNode(char *date,float T_degC, float PO4um) {  // kataskevh komvou
  struct Node *node = malloc(sizeof(struct Node));
  if(node==NULL){printf("\nMemory not allocated.\n");}
    strcpy(node->date,date);                    //Arxikopoihsh tou neou node
    node -> pho = PO4um;
    node -> temp = T_degC;
    node -> left = NULL;
    node -> right = NULL;
    node -> upsos = 1;
    node -> hasDupe = false;
  return node;
};

int getHeight(struct Node *node){               //gets to upsos kathe komvou
    if (node != NULL)
        return node->upsos;
    else return 0;
};

struct Node *lRot(struct Node *node){           //Left rotation, ama thelw na to kanw se ena zevgos a,b, to 'node' einai o goneas.
    struct Node *x1 = node->right;
    struct Node *x2 = x1->left;

    x1->left=node;
    node->right=x2;

    node->upsos=max(getHeight(node->left),getHeight(node->right))+1;
    x1->upsos=max(getHeight(x1->left),getHeight(x1->right))+1;
    return x1;
};

struct Node *rRot(struct Node *node){           //Right Rotation
    struct Node *x1 = node->left;
    struct Node *x2 = x1->right;
    x1->right=node;
    node->left=x2;

    node->upsos=max(getHeight(node->left),getHeight(node->right))+1;
    x1->upsos=max(getHeight(x1->left),getHeight(x1->right))+1;
    return x1;
};
struct Node *search(struct Node *node,char *date){
    if(node == NULL){
        printf("\nDate not found.\n");
            return node;
    }
    else if(compare(date,node->date)==1){search(node -> left,date);}                      //auto pou psaxnw einai mikrotero apto node pou evala ws orisma
    else if(compare(date,node->date)==-1){search(node -> right,date);}                    //>>  >>  >>  >>  >> >> megalutero >>  >>  >>  >>  >>  >>  >>
    else if(compare(date,node->date)==0){return node;}                                    //Found it
};

struct Node *change(struct Node *node,char *date, float temp){
        node=search(node,date);
        if(node!=NULL){
            node->temp=temp;
            printf("Temperature changed successfully.\n");
        }
};

struct Node *deletion(struct Node *node,char *date){
    search(node,node->date);                     //NULL check
    if(node==NULL){return node;}
    if(compare(date,node->date)==1) { node -> left = deletion(node -> left,date);}  //diagrafw ton komvo
    else if(compare(date,node->date)==-1) { node -> right = deletion(node -> right,date);}
    else {
        if(node -> left == NULL || node -> right == NULL){ // kanena h 1 paidi
            struct Node *curr;
            if (node -> left == NULL)
                curr = node->right;
            else
                curr = node->left;
            free(node);                 //Apeleftherwsh mnhmhs tou sugxwremenou node
            return curr;
        }else {  // 2 paidia
            struct Node *curr = MVN(node->right);
            strcpy(node->date,curr->date);
            node->right = deletion(node->right, curr->date);
        }
    }
    return node;
    stabilize(node,date);
};

int compare(char date1[10],char date2[10]){     //An h date1>date2 epistrefw -1, date1==date2 epistrefw 0, date1<date2 epistrefw -1. An compare=NULL tote error
    int i;
    int x=0;
    int z=0;
    int day1,day2,month1,month2,year1,year2;
    char d[2], d2[2], m[2], m2[2], y[4];
    for(i=0;i<5;i++){                       //Arxikopoihsh Pinakwn
            y[i]='\0';
            d[i]='\0';
            m[i]='\0';
    }
    i=0;

    while(x!=2 || z<4){                     //Diavazw month, date, year tou date1
        if((date1[i])!='/'){
            if (x==0)
                m[z]=date1[i];
            else if(x==1)
                d[z]=date1[i];
            else if(x==2)
                y[z]=date1[i];
        }
        else{
            z=-1;
            x+=1;
        }

        i+=1;
        z+=1;
    }
    day1=atof(d);                       //Metatrepw month,date,year se int me thn atof
    month1=atof(m);
    year1=atof(y);
    i=0;
    x=0;
    z=0;

    while(x!=2 || z<4){                 //To idio gia to 2o date
        if((date1[i])!='/'){
            if (x==0)
                m[z]=date2[i];
            else if(x==1)
                d[z]=date2[i];
            else if(x==2)
                y[z]=date2[i];
        }
        else{
            z=-1;
            x+=1;
        }

        i+=1;
        z+=1;
    }
    day2=atof(d);
    month2=atof(m);
    year2=atof(y);


    if(year1<year2){return 1;}                     //Sugkrinw tis hmeromhnies, an h date1>date2 epistrefw -1, date1==date2 epistrefw 0, date1<date2 epistrefw -1.
    else if(year1>year2){return -1;}
    else if(year1==year2){
        if(month1<month2){return 1;}
        else if(month1>month2){return -1;}
        else if(month1==month2){
            if(day1<day2){return 1;}
            else if(day1>day2){return -1;}
            else if(day1==day2){return 0;}
        }
    }
return NULL;
};

