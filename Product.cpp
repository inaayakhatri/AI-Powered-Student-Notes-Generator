#include "Product.h"
#include <iostream>
#include <fstream>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
using namespace std;

Product Product::products[100];
int Product::productCount = 0;
int Product::nextProductId = 1;
static string productsFilePath = "products.csv";

static string resolveProductFilePath(const string &filename)
{
    QString qFilename = QString::fromStdString(filename);
    QString appDir = QCoreApplication::applicationDirPath();
    QDir dir(appDir);
    QString pathInAppDir = dir.filePath(qFilename);
    if (QFileInfo::exists(pathInAppDir))
        return pathInAppDir.toStdString();
    QString pathInParent = dir.absoluteFilePath("../" + qFilename);
    if (QFileInfo::exists(pathInParent))
        return pathInParent.toStdString();
    return filename;
}

Product::Product(const string &name, double price, int qty) : id(nextProductId++), name(name), price(price), quantity(qty) {}

Product::Product(const string &name, const string &description, double price, int qty)
    : id(nextProductId++), name(name), description(description), price(price), quantity(qty)
{
}

Product::Product(int id, const string &name, const string &description, double price, int qty)
    : id(id), name(name), description(description), category("General"), price(price), quantity(qty)
{
}

string Product::getName() const
{
    return name;
}

string Product::getDescription() const
{
    return description;
}

int Product::getQuantity() const
{
    return quantity;
}

double Product::getPrice() const
{
    return price;
}

int Product::getId() const
{
    return id;
}

void Product::setQuantity(int qty)
{
    quantity = qty;
}

void Product::setDescription(const string &desc)
{
    description = desc;
}

void Product::setPrice(double price)
{
    this->price = price;
}

void Product::setCategory(const string &cat)
{
    category = cat;
}

string Product::getCategory() const
{
    return category;
}

bool Product::addProduct(const string &name, const string &description, double price, int qty, string &message)
{
    if (productCount >= 100)
    {
        message = "Product limit reached.";
        return false;
    }
    for (int i = 0; i < productCount; ++i)
    {
        if (products[i].name == name)
        {
            message = "Product already exists.";
            return false;
        }
    }
    if (price <= 0 || qty < 0)
    {
        message = "Invalid price or quantity.";
        return false;
    }
    products[productCount] = Product(name, description, price, qty);
    productCount++;
    saveProducts();
    message = "Product added successfully.";
    return true;
}

bool Product::updateProduct(const string &name, const string &description, double price, int qty, string &message)
{
    Product *p = findProduct(name);
    if (!p)
    {
        message = "Product not found.";
        return false;
    }
    if (price <= 0 || qty < 0)
    {
        message = "Invalid price or quantity.";
        return false;
    }
    p->setDescription(description);
    p->setPrice(price);
    p->setQuantity(qty);
    saveProducts();
    message = "Product updated successfully.";
    return true;
}

bool Product::removeProduct(const string &name, string &message)
{
    for (int i = 0; i < productCount; ++i)
    {
        if (products[i].name == name)
        {
            for (int j = i; j < productCount - 1; ++j)
                products[j] = products[j + 1];
            productCount--;
            saveProducts();
            message = "Product removed successfully.";
            return true;
        }
    }
    message = "Product not found.";
    return false;
}

bool Product::updateQuantity(const string &name, int qty, string &message)
{
    Product *p = findProduct(name);
    if (!p)
    {
        message = "Product not found.";
        return false;
    }
    if (qty < 0)
    {
        message = "Invalid quantity.";
        return false;
    }
    p->quantity = qty;
    saveProducts();
    message = "Quantity updated.";
    return true;
}

const Product *Product::getProducts(int &count)
{
    count = productCount;
    return products;
}

int Product::getProductCount()
{
    return productCount;
}

Product *Product::findProduct(const string &name)
{
    for (int i = 0; i < productCount; ++i)
    {
        if (products[i].name == name)
            return &products[i];
    }
    return nullptr;
}

void Product::loadProducts()
{
    productsFilePath = resolveProductFilePath("products.csv");
    ifstream file(productsFilePath);
    if (!file)
        return;
    string line;
    productCount = 0;
    int maxId = 0;
    while (getline(file, line) && productCount < 100)
    {
        try
        {
            size_t pos1 = line.find(',');
            if (pos1 == string::npos)
                continue;
            int id = stoi(line.substr(0, pos1));
            size_t pos2 = line.find(',', pos1 + 1);
            if (pos2 == string::npos)
                continue;
            string pname = line.substr(pos1 + 1, pos2 - pos1 - 1);
            size_t pos3 = line.find(',', pos2 + 1);
            if (pos3 == string::npos)
                continue;
            string desc = line.substr(pos2 + 1, pos3 - pos2 - 1);
            size_t pos4 = line.find(',', pos3 + 1);
            if (pos4 == string::npos)
                continue;
            string priceStr = line.substr(pos3 + 1, pos4 - pos3 - 1);
            string qtyStr = line.substr(pos4 + 1);
            double price = stod(priceStr);
            int qty = stoi(qtyStr);
            products[productCount] = Product(id, pname, desc, price, qty);
            if (id > maxId)
                maxId = id;
            productCount++;
        }
        catch (const invalid_argument &)
        {
            // skip invalid line
        }
    }
    nextProductId = maxId + 1;
}

void Product::saveProducts()
{
    ofstream file(productsFilePath.empty() ? "products.csv" : productsFilePath);
    for (int i = 0; i < productCount; ++i)
    {
        file << products[i].id << "," << products[i].name << "," << products[i].description 
        << "," << products[i].price << "," << products[i].quantity << endl;
    }
}
