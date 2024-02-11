#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

#define undelivered 0
#define checkedout 1
#define delivered 2

typedef struct USER
{
    char nam[50];
    char pass[30];
    char num[20];
    float balance;
} user;
typedef struct ITEM
{
    int category;
    char item_name[50];
    float item_price;
    char seller[50];
    int quantity;
    int serial_num;
    int rating;
    char comment_review[50];
} item;
typedef struct Cart
{
    int serial_number;
    int quantity;
    float price;
    char buyer[50];
    char seller[50];
    int status;
} carts;
//Global variables
char login_user_name[50];
int login_status=0;
char admin_username[50];
const char *fileNames[] = {"sign_up_data.bin", "admin_login_data.bin", "product_data.bin","cart_info.bin"};

const char *categories[] =
{
    "Watches",
    "Wallets",
    "Electronics",
    "Clothing",
    "Shoes",
    "Books",
    "Kitchen Appliances",
    "Furniture",
    "Toys",
    "Sports Equipment",
    "Jewelry",
    "Beauty Products",
    "Home Decor",
    "Gardening Tools",
    "Pet Supplies"
};
//Function declarations
void front_page_guest();
void front_page_logged_in();
void products();
void search_item();
void cart();
void cartadd(int serial,int quantity,float price);
void sign_in_page();
void error_handling(int ch);
//user sign in sign up functions
void user_sign();
void sign_up();
void sign_in();
void user_name_check(user *details);
//-----------------------------------
// Function declarations for different categories
void display_pro(int ch);
//Admin_login functions
void admin_sign();
void admin_sign_up();
void admin_sign_in();
void admin_username_check(user *admin);
//----------------------------------
void admin_error();
//admin portal functions declarations
void add_products();
void show_seller_products();
void undelivered_items();
//-----------------------
void select_item(int ch);
void pause();
void checkout();
void edit_cart(int serial);


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
 // ASCII cat design
    printf("\t\t\t                /\\_/\\ \n");
    printf("\t\t\t               ( o.o )\n");
    printf("\t\t\t                > ^ < \n\n");

    // Shopping front page
    printf("\t\t           WELCOME TO THE SHOPPING FRONT PAGE\n");
    printf("\t\t           ==================================\n");
    printf("\t\t           1. View Products\n");
    printf("\t\t           2. Search for a Product\n");
    printf("\t\t           3. View Cart\n");
    printf("\t\t           4. Sign in/Register(USER)\n");
    printf("\t\t           5. Sign in/Register(SELLER)\n");
    printf("\t\t           6. Exit\n");
    printf("\t\t           >>");

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
        user_sign();
        break;
    case 5:
        admin_sign();
        break;
    case 6:
        printf("Thanks for visiting <3\n");
        exit(0);
        break;
    case 7:
        admin_sign_in();
        break;
    case 0:
        for(int i =0; i<4; i++)
        {
            FILE *fp = fopen(fileNames[i],"wb");
            fclose(fp);
        }
        printf("Memory cleared\n");
        pause();
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
    printf("=====================================\n");
    printf("          PRODUCT CATEGORIES          \n");
    printf("=====================================\n");
    printf("1.  Watches\n");
    printf("2.  Wallets\n");
    printf("3.  Electronics\n");
    printf("4.  Clothing\n");
    printf("5.  Shoes\n");
    printf("6.  Books\n");
    printf("7.  Kitchen Appliances\n");
    printf("8.  Furniture\n");
    printf("9.  Toys\n");
    printf("10. Sports Equipment\n");
    printf("11. Jewelry\n");
    printf("12. Beauty Products\n");
    printf("13. Home Decor\n");
    printf("14. Gardening Tools\n");
    printf("15. Pet Supplies\n");
    printf("=====================================\n");
    printf("Please select a category (1-15): ");

    scanf("%d", &category);
    if(category>15||category<1)
    {
        error_handling(login_status);
    }
    display_pro(category);
}
void search_item()
{
    item view;
    char s[50];
    system("cls");
    printf("\n=====================================\n");
    printf("          SEARCH ITEM            \n");
    printf("=====================================\n");
    printf("Enter Item Name: ");
    scanf(" %[^\n]s",s);
    // Convert to uppercase
    char *str = s;
    while (*str)
    {
        *str = toupper((unsigned char)*str);
        str++;
    }
    FILE *fp = fopen("product_data.bin","rb");
    int track[1000]= {0};
    if(fp==NULL)
    {
        perror("\n");
        return;
    }
    int i=0;
    int found=0;
    while(fread(&view,sizeof(item),1,fp)==1)
    {
        if(strstr(view.item_name,s)!=NULL)
        {
            found++;
            track[i++]=view.serial_num;
            char *str = view.item_name;
            //convert first one to uppercase
            if (*str)
            {
                *str = toupper((unsigned char)*str);
                str++;
            }

            // Convert the rest to lowercase
            while (*str)
            {
                *str = tolower((unsigned char)*str);
                str++;
            }
            printf("%d. %s\n",i,view.item_name);
        }
    }
    fclose(fp);
    if(!found)
    {
        printf("Not found\n");
        pause();
        back_to_front(login_status);
    }
    int choice;
    printf("Choose Product:\n>>");
    scanf(" %d",&choice);
    fflush(stdin);
    int serial = track[choice-1];
    if(login_status==1)
    {
        printf("Not logged In,login to buy\n");
        pause();
        back_to_front(login_status);
    }
    else
    {
        buy_menu(serial);
    }


}
void error_handling(int ch)
{
    fflush(stdin);
    printf("Something Went Wrong\n");
    pause();
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
    if(login_status==1)
    {
        printf("Login to access Cart\n");
        pause();
        back_to_front(login_status);
    }
    carts view;
    item see;
    FILE *fp=fopen("cart_info.bin","r+b");
    if(fp==NULL)
    {
        perror("\n");
    }
    FILE *fp2 = fopen("product_data.bin","r+b");
    if(fp2==NULL)
    {
        perror("\n");
    }
    long int track[1000]= {0};
    int k=0;
    while(fread(&view,sizeof(carts),1,fp)==1)
    {
        if(strcmp(view.buyer,login_user_name)==0&&view.status==0)
        {
            fseek(fp2, 0, SEEK_SET);
            while(fread(&see,sizeof(item),1,fp2)==1)
            {
                if(view.serial_number==see.serial_num)
                {
                    printf("Item name:%s\n",see.item_name);
                    printf("Item price:%.2f BDT\n",see.item_price);
                    printf("Quantity:%d\n",view.quantity);
                    printf("Total:%.2f BDT\n",view.quantity*see.item_price);
                    printf("\n");
                    track[k++]=see.serial_num;
                }
            }
        }
    }
    fclose(fp);
    fclose(fp2);
    printf("[1]CheckOut [2]Select and Edit [3] Return to Main\n");
    int ch;
    scanf(" %d",&ch);
    fflush(stdin);
    switch(ch)
    {
    case 1:
        checkout();
        break;
    case 2:
        printf("Choose Item no.");
        int cho;
        scanf(" %d",&cho);
        fflush(stdin);
        edit_cart(track[cho-1]);
        break;
    case 3:
        pause();
        back_to_front(login_status);
        break;
    }


}
void edit_cart(int serial)
{
    carts view;
    item see;
    FILE *fp=fopen("cart_info.bin","r+b");
    if(fp==NULL)
    {
        perror("\n");
    }
    FILE *fp2 = fopen("product_data.bin","r+b");
    if(fp2==NULL)
    {
        perror("\n");
    }
    long int track[1000]= {0};
    long int position1=0;
    long int position2=0;
    int k=0;
    int i=0;
    int j=0;
    while(fread(&view,sizeof(carts),1,fp))
    {
        if(view.serial_number==serial)
        {
            position1=ftell(fp);
            break;
        }
    }
    printf("Selected Item:");
     while(fread(&see,sizeof(item),1,fp2))
    {
        if(see.serial_num==serial)
        {
            printf("%s\n",see.item_name);
            position2=ftell(fp2);
            break;
        }
    }
    printf("Quantity: %d\n",view.quantity);
    fflush(stdin);
    printf("\nNew quantity:");
    int nq;
    scanf(" %d",&nq);
   fflush(stdin);
   int shift = view.quantity-nq;
   //moving back one position
   fseek(fp, position1 - sizeof(carts), SEEK_SET);
   fseek(fp2, position2 - sizeof(item), SEEK_SET);
   //now changed value is updated and stored;
   view.quantity-=shift;
   see.quantity+=shift;
   fwrite(&view,sizeof(carts),1,fp);
   fwrite(&see,sizeof(item),1,fp2);
   fclose(fp);
   fclose(fp2);
   pause();
   cart();

}
void checkout()
{
    carts all;
    printf("[1]CheckOut All [2]Check-Out 1 by 1 [3]Go to Main\n>>");
    int ch;
    long int pos=0;
    scanf(" %d",&ch);
    if(ch==1)
    {   int checked=0;
        FILE *fp3=fopen("cart_info.bin","r+b");
        if(fp3==NULL)
        {
            perror("\n");
        }
        while(fread(&all,sizeof(carts),1,fp3)==1)
        {
            if(strcmp(all.buyer,login_user_name)==0&&all.status==0)
            {  checked++;
                pos = ftell(fp3);
                all.status=1;
                fseek(fp3, pos - sizeof(carts), SEEK_SET);
                fwrite(&all, sizeof(carts), 1, fp3);

            }
        }
        fclose(fp3);
        if(!checked)
        {
            printf("No Item Found\n");
            pause();
            back_to_front(login_status);
        }
        else
        {
            printf("Successfully Checked out\n");
            pause();
            back_to_front(login_status);
        }
    }
    else if(ch==2)
    {

    }
    else
    {
        back_to_front(login_status);
    }


}
void cartadd(int serial,int quantity,float price)
{
    carts add;
    add.serial_number=serial;
    add.quantity=quantity;
    add.price=price;
    strcpy(add.buyer,login_user_name);
    item seller;
    //adding seller info
    FILE *fp2 = fopen("product_data.bin","rb");
    if(fp2==NULL)
    {
        perror("\n");
        return;
    }
    while(fread(&seller,sizeof(item),1,fp2)==1)
    {
        if(seller.serial_num==serial)
        {
            strcpy(add.seller,seller.seller);
            break;
        }
    }
    fclose(fp2);
    add.status=0;

    FILE *fp=fopen("cart_info.bin","ab");
    if(fp==NULL)
    {
        perror("\n");
    }
    fwrite(&add,sizeof(carts),1,fp);
    fclose(fp);
    back_to_front(login_status);
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
    printf("=====================================\n");
    printf("            LOGIN MENU                \n");
    printf("=====================================\n");
    printf("1.  Sign up\n");
    printf("2.  Sign in\n");
    printf("3.  Back to front page\n");
    printf("=====================================\n");
    printf("Please select an option (1-3): ");
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
    fflush(stdin);
    system("cls");
    user details;
    printf("Enter username: ");
    scanf("%[^\n]s", details.nam);
    fflush(stdin);
    user_name_check(&details);

    printf("Enter password: ");
    scanf("%[^\n]s", details.pass);
    fflush(stdin);


    printf("Enter Number: ");
    scanf("%[^\n]s",details.num);
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
    pause();
    user_sign();
}
void sign_in()
{
    system("cls");
    char username[50];
    char password[50];
    fflush(stdin);
    printf("Enter username: ");
    scanf("%[^\n]s",username);
    fflush(stdin);

    printf("Enter password: ");
    scanf("%[^\n]s", password);
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
            pause();
            front_page_logged_in();

        }
        else
        {
            printf("Username or Password is wrong\n");
            fclose(fp);
            pause();
            front_page_guest();

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
            pause();
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
    printf("=====================================\n");
    printf("    Welcome to the Shopping Front Page\n");
    printf("==================//|%s|//============\n", login_user_name);
    printf("1.  View Products\n");
    printf("2.  Search for a Product\n");
    printf("3.  View Cart\n");
    printf("4.  Logout (%s)\n", login_user_name);
    printf("5.  Exit\n");
    printf("=====================================\n");
    printf("Please select an option (1-5): ");
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
        pause();
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
void display_pro(int ch)
{
    item product;
    int track[100]= {0};
    FILE *fp=fopen("product_data.bin","rb");
    if(fp==NULL)
    {
        perror("\n");
    }
    int found=0;
    printf("Showing %s:\n",categories[ch-1]);
    int i =0;
    while(fread(&product,sizeof(item),1,fp)==1)
    {
        if(product.category==ch)
        {
            found=1;

            char *str = product.item_name;
            //convert first one to uppercase
            if (*str)
            {
                *str = toupper((unsigned char)*str);
                str++;
            }

            // Convert the rest to lowercase
            while (*str)
            {
                *str = tolower((unsigned char)*str);
                str++;
            }
            printf("%d: %s\n",i+1,product.item_name);
            track[i++]=product.serial_num;
        }
    }
    if(!found)
    {
        printf("Not found!!");
        fclose(fp);
        pause();
        back_to_front(login_status);
    }
    fclose(fp);
    printf("\nChoose product:>>");
    int choice;
    scanf(" %d",&choice);
    if(login_status==1)
    {
        printf("Not logged in, Login to order\n");
        pause();
        back_to_front(login_status);

    }
    int serial_number = track[choice-1];
    buy_menu(serial_number);


}
void buy_menu(int serial_number)
{
    item view;
    FILE *fp;
    fp = fopen("product_data.bin","r+b");
    if(fp==NULL)
    {
        perror("\n");
    }
    printf("Selected Item:");
    long int pos;
    while(fread(&view,sizeof(item),1,fp)==1)
    {
        if(serial_number==view.serial_num)
        {
            char *str = view.item_name;
            //convert first one to uppercase
            if (*str)
            {
                *str = toupper((unsigned char)*str);
                str++;
            }

            // Convert the rest to lowercase
            while (*str)
            {
                *str = tolower((unsigned char)*str);
                str++;
            }
            printf("%s\n",view.item_name);
            printf("%.2f BDT\n",view.item_price);
            printf("In stock: %d\n",view.quantity);
            pos = ftell(fp);
            break;
        }
    }
    printf("\nBuy? [1]Yes [2]No\n");
    int select;
    int quantity;
    scanf(" %d",&select);
    switch(select)
    {
    case 1:
        printf("Quantity:\n");
        scanf(" %d",&quantity);
        break;
    case 2:
        fclose(fp);
        back_to_front(login_status);
        break;
    }
    printf("Item Name: %s\n",view.item_name);
    printf("Item Price: %.2f\n",view.item_price);
    printf("\nTOTAL: %.2f\n",quantity*view.item_price);
    printf("Successfully Added to Cart\n\n");
    float price = view.item_price;
    sleep(2);
    fseek(fp, pos - sizeof(item), SEEK_SET);
    view.quantity-=quantity;
    fwrite(&view,sizeof(item),1,fp);
    fclose(fp);
    cartadd(serial_number,quantity,price);

}
void admin_portal()
{

    while(1)
    {
        system("cls");
        printf("=====================================\n");
    printf("           ADMIN MENU                \n");
    printf("==================//|%s|//============\n", admin_username);
    printf("1.  Add Products\n");
    printf("2.  Remove Products\n");
    printf("3.  List of |%s|'s Items\n", admin_username);
    printf("4.  Delivered Items\n");
    printf("5.  Undelivered Items\n");
    printf("6.  Products with Complaint\n");
    printf("7.  Logout\n");
    printf("=====================================\n");
    printf("Please select an option (1-7): ");
        int ch;
        scanf(" %d",&ch);
        fflush(stdin);
        switch(ch)
        {
        case 1:
            add_products();
            break;
        case 2:
            printf("Working on\n");
            break;
        case 3:
            show_seller_products();
            break;
        case 4:
            printf("Working on\n");
            break;
        case 5:
            printf("+----------------------------------------+\n");
    printf("|       Undelivered Items Menu           |\n");
    printf("+----------------------------------------+\n");
    printf("| Item                       |  Quantity |\n");
    printf("+----------------------------|-----------+\n");
    printf("| Product 1                  |      5    |\n");
    printf("| Product 2                  |      2    |\n");
    printf("| Product 3                  |      1    |\n");
    printf("+----------------------------|-----------+\n");
    printf("|            Total           |   8 items |\n");
    printf("+----------------------------------------+\n");
            undelivered_items();
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
    scanf(" %[^\n]s",admin.nam);
    fflush(stdin);
    admin_username_check(&admin);

    printf("Enter Password:\n");
    scanf(" %[^\n]s",admin.pass);
    fflush(stdin);

    printf("Enter Number:\n");
    scanf(" %[^\n]s",admin.num);
    fflush(stdin);

    FILE *fp=fopen("admin_login_data.bin","ab");
    if(fp==NULL)
    {
        perror("\n");
    }
    else
    {
        fwrite(&admin,sizeof(user),1,fp);
    }
    fclose(fp);
    printf("Succesfully Registered\n");
    pause();
    admin_sign();
}
void admin_sign_in()
{
    char username[50];
    printf("Enter Username:");
    scanf(" %[^\n]s",username);
    fflush(stdin);

    char password[50];
    printf("Enter Password:");
    scanf(" %[^\n]s",password);
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
        while(fread(&admin,sizeof(user),1,fp)==1)
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
            pause();
            fclose(fp);
            admin_portal();
        }
        else
        {
            printf("Username or Password Wrong\n");
            pause();
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
        while(fread(&admin2,sizeof(user),1,fp)==1)
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
            pause();
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
    pause();
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
void add_products()
{
    item add;

    printf("Item catgory:\n");
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
    scanf("%d",&add.category);
    fflush(stdin);

    system("cls");
    printf("Selected Item catagory: %[^\n]s\n",categories[add.category]);

    printf("Item Name:");
    scanf(" %[^\n]s",add.item_name);
    fflush(stdin);
    char *str = add.item_name;
    while (*str)
    {
        *str = toupper((unsigned char)*str);
        str++;
    }

    printf("Item price:");
    scanf(" %f",&add.item_price);
    fflush(stdin);

    printf("Item quanitity:");
    scanf(" %d",&add.quantity);
    fflush(stdin);

    strcpy(add.seller,admin_username);
    printf("\nSeller Name is:%s\n",add.seller);

    srand((unsigned int)time(NULL));
    add.serial_num=rand() % 900000 + 100000;
    printf("Item ID: %d\n",add.serial_num);

    printf("\n\nConfirm add? Y\\N:\n>>");
    char ch;
    scanf(" %c",&ch);
    if(ch=='Y'||ch=='y')
    {
        FILE *fp;
        fp = fopen("product_data.bin","ab");
        if(fp==NULL)
        {
            perror("\n");
        }
        else
        {
            fwrite(&add,sizeof(item),1,fp);
        }
        fclose(fp);
        printf("Successfully Added Item\n");
        pause();
        admin_portal();
    }
    else
    {
        pause();
        admin_portal();
    }

}
void show_seller_products()
{
    system("cls");
    item show;
    FILE *fp=fopen("product_data.bin","rb");
    if(fp==NULL)
    {
        perror("\n");
    }
    int found=0;
    while(fread(&show,sizeof(item),1,fp)==1)
    {
        if(strcmp(show.seller,admin_username)==0)
        {
            found=1;
            char *str = show.item_name;
            //convert first one to uppercase
            if (*str)
            {
                *str = toupper((unsigned char)*str);
                str++;
            }

            // Convert the rest to lowercase
            while (*str)
            {
                *str = tolower((unsigned char)*str);
                str++;
            }
            printf("ITEM CATAGORY:%s\n",categories[show.category-1]);
            printf("ITEM NAME:%s\n",show.item_name);
            printf("ITEM PRICE:%.2f BDT\n",show.item_price);
            printf("ITEM QUANTITY:%d\n",show.quantity);
            printf("\n\n");

        }
    }
    if(!found)
    {
        printf("Seller has no active item\n");
    }
    pause();
    admin_portal();
}
void undelivered_items()
{
    carts view;
    FILE *fp = fopen("cart_info.bin","rb");
    if(fp==NULL)
    {
        perror("\n");
        return 1;
    }
    while(fread(&view,sizeof(carts),1,fp)==1)
    {
        if(strcmp(admin_username,view.seller)==0&&view.status==1)
        {
            printf("Item Id:%d\n",view.serial_number);
            printf("Item Price:%.2f BDT\n",view.price);
            printf("Item Quantity:%d\n",view.quantity);
        }
    }
    fclose(fp);
    pause();
    admin_portal();
}
void pause()
{

    fflush(stdin);
    printf("Enter to continue......");
    getchar();
}
