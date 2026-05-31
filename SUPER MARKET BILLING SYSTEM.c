#include <stdio.h>
#include <string.h>
#define MAX_PRODUCTS 100
#define TAX_RATE 0.05            
#define DISCOUNT_THRESHOLD 10.0  
#define DISCOUNT_RATE 0.10       

struct Product 
{
    int code;
    char name[50];
    float price;
    int quantity;
};

void displayProducts(struct Product products[], int count)
{
    printf("\nAvailable Products:\n");
    printf("Code   %-15s   Price\n", "Name");
    printf("------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-6d %-15s   %.2f\n", products[i].code, products[i].name, products[i].price);
    }
    printf("\n");
}

float calculateBill(struct Product products[], int cart[], int quantities[], int cartCount) 
{
    float total = 0.0;

    printf("\nBill Details:\n");
    printf("Code   %-15s   Price   Quantity   Subtotal\n", "Name");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < cartCount; i++)
    {
        int index = cart[i];
        float subtotal = products[index].price * quantities[i];
        printf("%-6d %-15s   %.2f   %-9d   %.2f\n",
               products[index].code, products[index].name, products[index].price, quantities[i], subtotal);
        total += subtotal;
    }

    float discount = 0.0;
    if (total > DISCOUNT_THRESHOLD)
    {
        discount = total * DISCOUNT_RATE;
        printf("Discount Applied: -%.2f\n", discount);
        total -= discount;
    }

    float tax = total * TAX_RATE;
    printf("Tax Applied: +%.2f\n", tax);
    total += tax;

    printf("----------------------------------------------------------\n");
    printf("Total Amount: %.2f\n", total);
    return total;
}

int main() 
    {
    struct Product products[MAX_PRODUCTS] = {
        {101, "Apple", 0.50, 100},
        {102, "Banana", 0.30, 150},
        {103, "Orange", 0.80, 200},
        {104, "Milk", 1.20, 50},
        {105, "Bread", 1.50, 60}
    };
    int productCount = 5;

    int cart[MAX_PRODUCTS];
    int quantities[MAX_PRODUCTS];
    int cartCount = 0;

    int code, quantity;
    char addMore;

    printf("Welcome to the Supermarket Billing System!\n");
    displayProducts(products, productCount);

    do 
    {
        printf("Enter the product code: ");
        scanf("%d", &code);
        int found = -1;
        for (int i = 0; i < productCount; i++) 
        {
            if (products[i].code == code)
            {
                found = i;
                break;
            }
        }

        if (found != -1)
        {
            printf("Enter quantity: ");
            scanf("%d", &quantity);

            if (quantity > 0 && quantity <= products[found].quantity)
            {
                cart[cartCount] = found;
                quantities[cartCount] = quantity;
                cartCount++;
                products[found].quantity -= quantity;  
            } 
            else
            {
                printf("Insufficient stock or invalid quantity.\n");
            }
        }
        else 
        {
            printf("Invalid product code.\n");
        }

        printf("Do you want to add more items? (y/n): ");
        scanf(" %c", &addMore);
    }
    while (addMore == 'y' || addMore == 'Y');

    calculateBill(products, cart, quantities, cartCount);

    return 0;
}
