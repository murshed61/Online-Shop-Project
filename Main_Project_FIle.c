#include <stdio.h>
#include <stdlib.h>
//Function declarations
typedef struct USER
{
    char nam[50];
    char pass[30];
    char num[20];
} user;
void front_page();
void products();
void search_item();
void cart();
void sign_in_page();
void error_handling();
//user sign in sign up functions
void user_sign();
void sign_up();
void sign_in();
void user_name_check(user *details);
//-----------------------------------

int main()
{
    front_page();
}
void front_page()
{
    printf("Welcome to the Shopping Front Page\n");
    printf("================================\n");
    printf("1. View Products\n");
    printf("2. Search for a Product\n");
    printf("3. View Cart\n");
    printf("4. Sign in/Register\n");
    printf("5. Exit\n");
    int choice;
    scanf(" %d",&choice);
    switch(choice)
    {
    case 1:
        products();
        break;
    case 2:
        search_item();
        break;
    case 3:
        cart();
        break;
    case 4:
        sign_in_page();
        break;
    case 5:
        printf("Thanks for visiting <3\n");
        exit(0);
        break;
    default:
        error_handling();
        break;

    }
}
void products()
{

}
void search_item()
{

}
void error_handling()
{

}
void cart()
{

}
void sign_in_page()
{
    printf("1.User Sign in/Sign Up\n");
    printf("2.Admin Sign in/Sign Up\n");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        user_sign();
        break;
    case 2:
        printf("Working on\n");
        break;

    }
}
void user_sign()
{
    FILE *fp;
    fp = fopen("Files/sign_up_data.bin","rb");
    if(fp==NULL)
    {
        fopen("Files/sign_up_data.bin","wb");
    }
    fclose(fp);
    printf("1.Sign up\n");
    printf("2.Sign in\n");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        sign_up();
        break;
    case 2:
        sign_in();
        break;
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
    fp = fopen("Files/sign_up_data.bin","ab");
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
    fp = fopen("Files/sign_up_data.bin","rb");
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
    fp = fopen("Files/sign_up_data.bin","rb");
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
