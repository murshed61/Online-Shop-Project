#include<stdio.h>
#include<stdlib.h>
typedef struct USER
{
    char nam[50];
    char pass[30];
    char num[20];
} user;

void sign_up();
void sign_in();
void user_name_check(user *details);
int main()
{
    while(1)
    {
        system("cls");
        printf("1.Sign up\n");
        printf("2.Sign in\n");
        int choice;
        scanf(" %d",&choice);
        switch(choice)
        {
        case 1:
            sign_up();
            break;
        case 2:
            sign_in();
            break;
        }
        sleep(2);
    }
}
void sign_up()
{
    user details;
    FILE *fp;
    printf("Enter username\n");
    scanf(" %s",details.nam);
    fflush(stdin);
    user_name_check(&details);

    printf("Enter password\n");
    scanf(" %s",details.pass);
    fflush(stdin);

    printf("Enter Number\n");
    scanf(" %s",details.num);
    fflush(stdin);
    fp = fopen("Files/sign_up_data.txt","a");
    if(fp==NULL)
    {
        perror("\n");
    }
    else
    {
        fprintf(fp,"%s+",details.nam);
        fprintf(fp,"%s+",details.pass);
        fprintf(fp,"%s,",details.num);

    }
    fclose(fp);
}
void sign_in()
{
    user details;
    FILE *fp;
    fp = fopen("Files/sign_up_data.txt","r");
    if(fp==NULL)
    {
        perror("\n");
    }
    else
    {
        char username[50];
        char pass[50];

        printf("Enter Username:\n");
        scanf(" %s",username);
        fflush(stdin);

        printf("Enter Password:\n");
        scanf(" %s",pass);
        fflush(stdin);
        int user_match=0;
        int pass_match=0;
        int u_incre=0;
        int p_incre=0;
        int user_check=-1;
        while (fscanf(fp, "%[^+]+%[^+]+%[^,],", details.nam, details.pass, details.num) == 3)//Azxcv
        {
            u_incre++;
            if(strcmp(details.nam,username)==0)
            {
                user_match=1;
                user_check=u_incre;
            }
            if(strcmp(details.pass,pass)==0)
            {
                if(user_check==u_incre)
                {
                    pass_match=1;
                }

            }
            if(user_match)
            {
                break;
            }

        }
        sleep(1);
        if(!user_match)
        {
            printf("Username Not Found\n");
        }
        else if(user_match&&pass_match)
        {
            printf("Login Successful\n");
        }
        else if(user_match&&!pass_match)
        {
            printf("Passsword Incorrect\n");
        }
        else
        {
            printf("Logic Mistake\n");
        }

    }
    fclose(fp);


}
void user_name_check(user *details)
{
    user details2;
    FILE *fp;
    fp = fopen("Files/sign_up_data.txt","r");
    if(fp==NULL)
    {
        perror("\n");
    }
    else
    {
        int user_match=0;
        while (fscanf(fp, "%[^+]+%[^+]+%[^,],", details2.nam, details2.pass, details2.num) == 3)
        {
            if(strcmp(details2.nam,details->nam)==0)
            {
                user_match=1;

            }
        }
        if(user_match)
        {
            printf("User already exists\n");
            sleep(5);
            fclose(fp);
            main();
        }
    }

}
