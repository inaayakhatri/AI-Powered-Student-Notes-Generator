#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product
{
public:
    Product(const string &name = "", double price = 0.0, int qty = 0);

    Product(const string &name, const string &description, double price, int qty);

    Product(int id, const string &name, const string &description, double price, int qty);

    string getName() const;
    string getDescription() const;
    string getCategory() const;
    double getPrice() const;
    int getQuantity() const;
    int getId() const;
    void setQuantity(int qty);
    void setDescription(const string &desc);
    void setPrice(double price);
    void setCategory(const string &cat);

    static bool addProduct(const string &name, const string &description, double price, int qty, string &message);
    static bool updateProduct(const string &name, const string &description, double price, int qty, string &message);
    static bool removeProduct(const string &name, string &message);
    static bool updateQuantity(const string &name, int qty, string &message);
    static const Product *getProducts(int &count);
    static Product *findProduct(const string &name);
    static int getProductCount();
    static void loadProducts();
    static void saveProducts();

private:
    int id;
    string name;
    string description;
    string category;
    double price;
    int quantity;
    static Product products[100];
    static int productCount;
    static int nextProductId;
};

#endif // PRODUCT_H
