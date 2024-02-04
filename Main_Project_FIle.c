#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct USER
{
    char nam[50];
    char pass[30];
    char num[20];
} user;
typedef struct ITEM
{
    int category;
    char item_name[50];
    float item_price;
} item;
//Global variables
char login_user_name[50];
int login_status=0;
char admin_username[50];
//Function declarations
void front_page_guest();
void front_page_logged_in();
void products();
void search_item();
void cart();
void sign_in_page();
void error_handling(int ch);
//user sign in sign up functions
void user_sign();
void sign_up();
void sign_in();
void user_name_check(user *details);
//-----------------------------------
// Function declarations for different categories
void displayWatches();
void displayWallets();
void displayElectronics();
void displayClothing();
void displayShoes();
void displayBooks();
void displayKitchenAppliances();
void displayFurniture();
void displayToys();
void displaySportsEquipment();
void displayJewelry();
void displayBeautyProducts();
void displayHomeDecor();
void displayGardeningTools();
void displayPetSupplies();

// Function to display products based on the selected category
void displayProducts(int category);
//Admin_login functions
void admin_sign();
void admin_sign_up();
void admin_sign_in();
void admin_username_check(user *admin);
//----------------------------------
void admin_error();


int main()
{
    system("cls");
    front_page_guest();
}
void front_page_guest()
{
    login_status=1;
    system("cls");
    fflush(stdin);
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
        error_handling(login_status);
        break;

    }
}
void products()
{
    int category;
    system("cls");
    printf("Select a category (1-15):\n");
    printf("1. Watches\n");
    printf("2. Wallets\n");
    printf("3. Electronics\n");
    printf("4. Clothing\n");
    printf("5. Shoes\n");
    printf("6. Books\n");
    printf("7. Kitchen Appliances\n");
    printf("8. Furniture\n");
    printf("9. Toys\n");
    printf("10. Sports Equipment\n");
    printf("11. Jewelry\n");
    printf("12. Beauty Products\n");
    printf("13. Home Decor\n");
    printf("14. Gardening Tools\n");
    printf("15. Pet Supplies\n");

    scanf("%d", &category);
    if(category>15||category<1)
    {
        error_handling(login_status);
    }
    displayProducts(category);
}
void search_item()
{

}
void error_handling(int ch)
{
    fflush(stdin);
    printf("Something Went Wrong\n");
    sleep(3);
    switch(ch)
    {
    case 1:
        front_page_guest();
        break;
    case 2:
        front_page_logged_in();
        break;
    }
}
void cart()
{

}
void sign_in_page()
{
    system("cls");
    printf("1.User Sign in/Sign Up\n");
    printf("2.Admin Sign in/Sign Up\n");
    printf("3.Back to Front Page\n");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        user_sign();
        break;
    case 2:
        admin_sign();
        break;
    case 3:
        back_to_front(login_status);
        break;
    default:
        error_handling(login_status);
        break;

    }
}
void user_sign()
{
    system("cls");
    FILE *fp;
    fp = fopen("sign_up_data.bin","rb");
    if(fp==NULL)
    {
        fopen("sign_up_data.bin","wb");
    }
    fclose(fp);
    printf("1.Sign up\n");
    printf("2.Sign in\n");
    printf("3.Back to front page\n");
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
    case 3:
        back_to_front(login_status);
        break;
    default:
        error_handling(login_status);
        break;
    }

}
void sign_up()
{
    system("cls");
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
    printf("Successfully registered\n");
    sleep(2);
    user_sign();
}
void sign_in()
{
    system("cls");
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
            login_status=2;
            strcpy(login_user_name,username);
            fclose(fp);
            front_page_logged_in();
            sleep(3);
        }
        else
        {
            printf("Username or Password is wrong\n");
            fclose(fp);
            front_page_guest();
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
            sleep(4);
            fclose(fp);
            front_page_guest();
        }
    }
    fclose(fp);

}
void front_page_logged_in()
{
    system("cls");
    fflush(stdin);
    printf("Welcome to the Shopping Front Page\n");
    printf("===================//|%s|//=============\n",login_user_name);
    printf("1. View Products\n");
    printf("2. Search for a Product\n");
    printf("3. View Cart\n");
    printf("4. Logout(%s)\n",login_user_name);
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
        printf("Succesfully Logged Out\n");
        login_status=1;
        sleep(2);
        front_page_guest();
        break;
    case 5:
        printf("Thanks for visiting <3\n");
        exit(0);
        break;
    default:
        error_handling(login_status);
        break;

    }
}
void displayWatches()
{
    printf("Displaying Watches\n");
    // Function to show watches
}

void displayWallets()
{
    printf("Displaying Wallets\n");
    // Function to show wallets
}

void displayElectronics()
{
    printf("Displaying Electronics\n");
    // Function to show electronics
}

void displayClothing()
{
    printf("Displaying Clothing\n");
    // Function to show clothing
}

void displayShoes()
{
    printf("Displaying Shoes\n");
    // Function to show shoes
}

void displayBooks()
{
    printf("Displaying Books\n");
    // Function to show books
}

void displayKitchenAppliances()
{
    printf("Displaying Kitchen Appliances\n");
    // Function to show kitchen appliances
}

void displayFurniture()
{
    printf("Displaying Furniture\n");
    // Function to show furniture
}

void displayToys()
{
    printf("Displaying Toys\n");
    // Function to show toys
}

void displaySportsEquipment()
{
    printf("Displaying Sports Equipment\n");
    // Function to show sports equipment
}

void displayJewelry()
{
    printf("Displaying Jewelry\n");
    // Function to show jewelry
}

void displayBeautyProducts()
{
    printf("Displaying Beauty Products\n");
    // Function to show beauty products
}

void displayHomeDecor()
{
    printf("Displaying Home Decor\n");
    // Function to show home decor
}

void displayGardeningTools()
{
    printf("Displaying Gardening Tools\n");
    // Function to show gardening tools
}

void displayPetSupplies()
{
    printf("Displaying Pet Supplies\n");
    // Function to show pet supplies
}

void displayProducts(int category)
{
    system("cls");
    switch(category)
    {
    case 1:
        displayWatches();
        break;
    case 2:
        displayWallets();
        break;
    case 3:
        displayElectronics();
        break;
    case 4:
        displayClothing();
        break;
    case 5:
        displayShoes();
        break;
    case 6:
        displayBooks();
        break;
    case 7:
        displayKitchenAppliances();
        break;
    case 8:
        displayFurniture();
        break;
    case 9:
        displayToys();
        break;
    case 10:
        displaySportsEquipment();
        break;
    case 11:
        displayJewelry();
        break;
    case 12:
        displayBeautyProducts();
        break;
    case 13:
        displayHomeDecor();
        break;
    case 14:
        displayGardeningTools();
        break;
    case 15:
        displayPetSupplies();
        break;
    default:
        printf("Invalid Category\n");
        sleep(2);
        error_handling(login_status);
        break;
    }
}
void admin_portal()
{
    system("cls");
  printf("1.Add Products\n");
  printf("2.Remove Products\n");
  printf("3.List of |%s|'s Items\n",admin_username);
  printf("4.Delivered Item\n");
  printf("5.Undelivered Item\n");
  printf("6.Products with complaint\n");
  printf("7.Logout\n");
  int ch;
  scanf("%d",&ch);
  switch(ch)
  {
  case 1:
    printf("Working on\n");
    break;
  case 2:
     printf("Working on\n");
    break;
  case 3:
     printf("Working on\n");
    break;
  case 4:
     printf("Working on\n");
    break;
  case 5:
     printf("Working on\n");
    break;
  case 6:
     printf("Working on\n");
    break;
  case 7:
     printf("Successfully logged out\n");
     fflush(stdin);
     back_to_front(login_status);
    break;
  default:
    admin_error();
    break;
  }
}
void admin_sign()
{
    FILE *fp = fopen("admin_login_data.bin","rb");
    if(fp==NULL)
    {
        fp = fopen("admin_login_data.bin","wb");
    }
    fclose(fp);
    system("cls");
    printf("1.Sign Up\n");
    printf("2.Sign In\n");
    printf("3.Back to front page\n");
    int ch;
    scanf("%d",&ch);
    switch(ch)
    {
    case 1:
        admin_sign_up();
        break;
    case 2:
        admin_sign_in();
        break;
    case 3:
        back_to_front(login_status);
        break;
    default:
        error_handling(login_status);
        break;
    }
}
void admin_sign_up()
{
    system("cls");
    user admin;
    printf("Enter Username:\n");
    scanf(" %s",admin.nam);
    fflush(stdin);
    admin_username_check(&admin);

    printf("Enter Password:\n");
    scanf(" %s",admin.pass);
    fflush(stdin);

    printf("Enter Number:\n");
    scanf(" %s",admin.num);
    fflush(stdin);

    FILE *fp=fopen("admin_login_data.bin","ab");
    if(fp==NULL)
    {
        perror("\n");
    }
    else
    {
       fwrite(&admin,sizeof(admin),1,fp);
    }
    fclose(fp);
    printf("Succesfully Registered\n");
    sleep(2);
    admin_sign();
}
void admin_sign_in()
{
   char username[50];
   printf("Enter Username:");
   scanf(" %s",username);
   fflush(stdin);

   char password[50];
   printf("Enter Password:");
   scanf(" %s",password);
   fflush(stdin);

   user admin;
   FILE *fp;
   fp = fopen("admin_login_data.bin","rb");
   if(fp==NULL)
   {
       perror("\n");
   }
   else
   {
       int match=0;
       while(fread(&admin,sizeof(admin),1,fp)==1)
       {
           if(strcmp(admin.nam,username)==0&&strcmp(admin.pass,password)==0)
           {
               match=1;
               break;
           }

       }
       if(match)
           {
               printf("Succesfully Logged in\n");
               fflush(stdin);
               strcpy(admin_username,username);
               sleep(2);
               fclose(fp);
               admin_portal();
           }
           else
           {
               printf("Username or Password Wrong\n");
               sleep(2);
               fclose(fp);
               back_to_front(login_status);
           }
   }
}
void admin_username_check(user *admin)
{
    user admin2;
    FILE *fp=fopen("admin_login_data.bin","rb");
    if(fp==NULL)
    {
        perror("\n");
    }
    else
    {
        int match=0;
        while(fread(&admin2,sizeof(admin2),1,fp)==1)
        {
            if(strcmp(admin2.nam,admin->nam)==0)
            {
                match=1;
                break;
            }
        }
        if(match)
        {
            printf("Username Already Exists\n");
            sleep(2);
            fclose(fp);
            error_handling(login_status);
        }
        fclose(fp);
    }
}
void admin_error()
{
    fflush(stdin);
    printf("Something is wrong\n");
    sleep(2);
    admin_portal();
}
void back_to_front(int ch)
{
    switch(ch)
    {
    case 1:
        front_page_guest();
        break;
    case 2:
        front_page_logged_in();
        break;
    }
}
