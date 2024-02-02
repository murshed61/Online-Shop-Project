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
    FILE *fp;
    fp = fopen("sign_up_data.bin","rb");
    if(fp==NULL)
    {
        fopen("sign_up_data.bin","wb");
    }
    fclose(fp);
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
    printf("Enter username: ");
    scanf("%s", details.nam);
    fflush(stdin);
    user_name_check(&details);

    printf("Enter password: ");
    scanf("%s", details.pass);
    fflush(stdin);


    printf("Enter Number: ");
    scanf("%s",details.num);
    fflush(stdin);
    FILE *fp;
    fp = fopen("sign_up_data.bin","ab");
    if(fp==NULL)
    {
        perror("\n");
    }
    else
    {
        fwrite(&details,sizeof(user),1,fp);
    }
    fclose(fp);
}
void sign_in()
{
    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%s",username);
    fflush(stdin);

    printf("Enter password: ");
    scanf("%s", password);
    fflush(stdin);

    user details;
    FILE *fp;
    fp = fopen("sign_up_data.bin","rb");
    if(fp==NULL)
    {
        perror("\n");
    }
    else
    {
        int match=0;
        while(fread(&details,sizeof(user),1,fp)==1)
        {
            if(strcmp(username,details.nam)==0&&strcmp(password,details.pass)==0)
            {
                match=1;
                break;
            }
        }
        if(match)
        {
            printf("Login Successful\n");
            sleep(3);
        }
        else
        {
            printf("Username or Password is wrong\n");
            sleep(3);
        }
    }
    fclose(fp);
}
void user_name_check(user *details)
{
    user details2;
    FILE *fp;
    fp = fopen("sign_up_data.bin","rb");
    if(fp==NULL)
    {
        perror("\n");
    }
    else
    {
        int user_match=0;
        while (fread(&details2, sizeof(details2),1,fp) == 1)
        {
            if(strcmp(details2.nam,details->nam)==0)
            {
                user_match=1;
                break;
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
