/*A university is receiving applications from students to register for language courses offered in six different languages. Each language has limited seats and time of submission of request is to be used for making a decision. The following are the fields provided in the application:
a.	Register Number, Name, Time and date of submission, Preference of language {Option1, Option2, Option3}
b.	Devise a solution that would automate the process of allocating the languages based on the order of preference given by students. Use appropriate data structures to process the data. Include provision for swapping of the language that has been allocated for a student on mutual consent. */

//C program for stable matching of language based on the preference given by the student.
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#define N 6
struct Sstudent
{
    int iregNo;
    char cname[25];
    int ihour;
    int iminute;
    int iday;
    int imonth;
    int iyear;
    int il1,il2,il3,il4,il5,il6;
};

void swap()
{
    //ireg1=the registration no. of the student who wish to swap language il1
    //ireg2=the registration no. of student with whom the language il1 is swapped
    //il2 is the language given to ireg2
    int ireg1,ireg2,il1,il2,itemp;
    printf("\n");
    printf("LANGUAGE SWAP ON MUTUAL CONSENT");
    printf("\n");
    printf("Enter your registration number: ");
    scanf("%d",&ireg1);
    printf("Enter your language code: ");
    scanf("%d",&il1);
    printf("Enter the registration number of the student you wish to swap language: ");
    scanf("%d",&ireg2);
    printf("Enter the language code of that student: ");
    scanf("%d",&il2);

    //swapping the languages
    itemp=il1;
    il1=il2;
    il2=itemp;

    //printing swapped languages

    printf("*********Current languages********\n");
    printf("Student Reg.No.  languages alloted\n");
    printf("     %d                %d\n",ireg1,il1);
    printf("     %d                %d\n",ireg2,il2);
}

//this function returns true if student 'istud' prefers language 'ilang1'over 'ilang'
int sPreferL1OverL(int iprefer[2*N][N],int istud,int ilang, int ilang1)
{
    int i;

    //Check if istud prefers ilang over his current engagement ilang1
    for(i=0;i<N;i++)
    {

       /*If ilang1 comes before ilang in the preference
       list of istud, then istud prefers his
       current engagement, don't do anything*/
       if(iprefer[istud][i]==ilang1)
        return true;

       /*if ilang comes before ilang1 in istud list,
       then free his current engagement and engage him with ilang*/
       if(iprefer[istud][i]==ilang)
        return false;
    }
}

/*Prints stable matching for N languages and N students.
languages are numbered as 0 to N-1. Students are numbered as N
to 2N-1.*/
void stablePair(int iprefer[2*N][N])
{
    /*Stores language chosen by a student. This is our output
    array that stores information. The value of istudLang[i]
    indicates the language assigned to student N+i. Note that
    the student numbers between N and 2*N-1. The value -1
    indicates that (N+i)th student is free*/
    int istudLang[N];

    /*An array to store availability of languages. If ilangFree[i] is
    false, the language 'i' is free, otherwise engaged.*/
    int ilangFree[N];

    //Initialize all languages and students as free
    //memset() is used to fill a block of memory with a particular value.
    memset(istudLang,-1,sizeof(istudLang));
    memset(ilangFree,false,sizeof(ilangFree));
    int freeCount=N;

    //while there are free languages
    while (freeCount>0)
    {
        //Pick the first free language (we could pick any)
        int ilang;
        for(ilang=0;ilang<N;ilang++)
            if(ilangFree[ilang]==false)
                break;

        /*One by one go to all students according to languages preferences.
        Here ilang is the picked free language*/
        int i;
        for(i=0;i<N && ilangFree[ilang]==false;i++)
        {
            int istud = iprefer[ilang][i];

            /*The student of preference is free, istud and ilang
            become engaged (Note that the engagement can be changed later).
            So we can say they are engaged not permanently together.*/
            if(istudLang[istud-N]==-1)
            {
                istudLang[istud-N]=ilang;
                ilangFree[ilang]=true;
                freeCount--;
            }
            else //If istud is not free
            {
                //Find current engagement of istud
                int ilang1=istudLang[istud-N];

                /*If istud prefers ilang over his current engagement ilang1,
                then break the engagement between istud and ilang1 and
                enagage ilang with istud.*/
                if(sPreferL1OverL(iprefer,istud,ilang,ilang1)==false)
                {
                    istudLang[istud-N]=ilang;
                    ilangFree[ilang]=true;
                    ilangFree[ilang1]=false;
                }
            }//End of Else
        }//End of the for loop that goes to all students in languages list
    }//End of main while loop


//Print the solution

printf("\n");
printf("**********LANGUAGE GIVEN**********\n");
printf("Student Reg.No.     Language given\n");
int i;
for(i=0;i<N;i++)
printf("     %d                   %d\n",i+N,istudLang[i]);
}


//Drivers function to and structure to ask input from user.
int main()
{

 clock_t t;
    int inum,i;
    struct Sstudent *Sstud; //Allocates memory to store address
    struct Sstudent Sil;    //Allocate memory to store members of struct Sstudent variable il
Sstud=(struct Sstudent *)malloc(N * sizeof(struct Sstudent));
printf("\n");
    printf("*******************LANGUAGES OFFERED AND THEIR NUMERIC CODES******************");
printf("\n\t\t\t\tSpanish-0\n\t\t\t\tChinese-1\n\t\t\t\tGerman-2\n\t\t\t\tJapanese-3\n\t\t\t\tKorean-4\n\t\t\t\tFrench-5\n");
printf("\n");
    for(i=0;i<N;i++)
    {
        printf("Enter the student's Registration No., Name, Time of submission(HH:MM)-24 hour format,Date of submission(DD/MM/YY),Preference of language: \n");
        scanf("%d %s %d:%d %d/%d/%d %d,%d,%d,%d,%d,%d",&Sstud[i].iregNo,Sstud[i].cname,&Sstud[i].ihour,&Sstud[i].iminute,&Sstud[i].iday,&Sstud[i].imonth,&Sstud[i].iyear,&Sstud[i].il1,&Sstud[i].il2,&Sstud[i].il3,&Sstud[i].il4,&Sstud[i].il5,&Sstud[i].il6);

    }

printf("\n");
printf("Reg.No.   Name  Time of submission  Date of submission  Preference of Language\n");
for(i=0;i<N;i++)
{
printf("   %d      %s        %d:%d              %d/%d/%d         {%d, %d, %d, %d, %d, %d}\n",(Sstud+i)->iregNo,(Sstud+i)->cname,(Sstud+i)->ihour,(Sstud+i)->iminute,(Sstud+i)->iday,(Sstud+i)->imonth,(Sstud+i)->iyear,(Sstud+i)->il1,(Sstud+i)->il2,(Sstud+i)->il3,(Sstud+i)->il4,(Sstud+i)->il5,(Sstud+i)->il6);
}

  int iprefer[2*N][N]={{-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1}, // Student reg. No.
        {0,1,2,3,4,5},
        {0,1,2,3,4,5},
        {0,1,2,3,4,5},
        {0,1,2,3,4,5},
        {0,1,2,3,4,5},
        {0,1,2,3,4,5}, //language codes
    };
for(i=0;i<N;i++){//filling up 2d array according to input
    iprefer[0][(Sstud+i)->il1] = (Sstud+i)->iregNo;
    iprefer[1][(Sstud+i)->il2] = (Sstud+i)->iregNo;
    iprefer[2][(Sstud+i)->il3] = (Sstud+i)->iregNo;
    iprefer[3][(Sstud+i)->il4] = (Sstud+i)->iregNo;
    iprefer[4][(Sstud+i)->il5] = (Sstud+i)->iregNo;
    iprefer[5][(Sstud+i)->il6] = (Sstud+i)->iregNo;
}
printf("\n");
for(i=0;i<2*N;i++){
    for(int j=0;j<N;j++){
        printf("%d,",iprefer[i][j]);
    }
    printf("\n");
}
    stablePair(iprefer);


    int ichoice;
    printf("\n");
    printf("***************SWAP YOUR LANGUAGE*******************\n");
    printf("NOTE: You can request for language swap only twice\n");
    for(i=0;i<2;i++)
    {

    printf("*Press (1) if you wish to swap languages with another student \n");
    printf("*Press (2) if you wish to submit\n");
    scanf("%d",&ichoice);
    switch(ichoice)
    {
        case 1: swap();
        break;
        case 2: printf("-----------Your language course has been alloted-------------\n");
        exit(0);
        break;
        default: printf("Invalid Choice");
        break;
    }
    }




    t = clock();
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\nProgram took %f seconds to execute \n", time_taken);

    return 0;
}

/*
INPUT:
6  Tina  20:00  01/2/21  5, 4, 3, 2, 1, 0
7  Rina  08:28  09/3/21  4, 3, 2, 1, 0, 5
8  Mina  14:15  07/4/21  3, 2, 1, 0, 5, 4
9  Lina  03:30  02/5/21  2, 1, 0, 5, 4, 3
10 Jina  21:00  01/6/21  1, 0, 5, 4, 3, 2
11 Bina  09:34  05/7/21  0, 5, 4, 3, 2, 1

OUTPUT:

Reg.No.   Name  Time of submission  Date of submission  Preference of Language
   6      Tina        20:00              1/2/21          {5, 4, 3, 2, 1, 0}
   7      Rina        08:28              9/3/21          {4, 3, 2, 1, 0, 5}
   8      Mina        14:15              7/4/21          {3, 2, 1, 0, 5, 4}
   9      Lina        03:30              2/5/21          {2, 1, 0, 5, 4, 3}
   10     Jina        21:00              1/6/21          {1, 0, 5, 4, 3, 2}
   11     Bina        09:34              5/7/21          {0, 5, 4, 3, 2, 1}

Student Reg.No.      Language given
     6                      5
     7                      4
     8                      3
     9                      2
     10                      1
     11                      0

Incase of a swap of language:
INPUT:
Your Reg.No.=6
Your Language Code=5
Reg.No. of student whom to swap with=9
Language code of that student=2

OUTPUT:
Student Reg.No.   Languages alloted
      6                   2
      9                   5
*/


