#include "CustomerPage.h"
#include <QVBoxLayout>   // Vertical layout for UI arrangement
#include <QHBoxLayout>   // Horizontal layout for UI arrangement
#include <QLabel>        // Text labels
#include <QPushButton>   // Clickable buttons
#include <QListWidget>   // List display widget
#include <QSpinBox>      // Numeric input spinner
#include <QIntValidator> // Validator for integer input
#include <QCheckBox>     // Checkbox for theme toggle
#include <QTabWidget>    // Tabbed interface
#include <QComboBox>     // Dropdown combo box
#include "Product.h"     // Product data model

// ============================================================================
// Constructor: Initialize the customer page UI with all components
// ============================================================================
CustomerPage::CustomerPage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // ========== PROFILE SECTION ==========
    // Display customer welcome message
    profileLabel = new QLabel;
    profileLabel->setAlignment(Qt::AlignCenter);
    profileLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    // ========== PRODUCT BROWSING SECTION ==========
    // Main product list widget to display all available products
    productList = new QListWidget;

    // Search box for filtering products by name or description
    searchProductEdit = new QLineEdit;
    searchProductEdit->setPlaceholderText("Search product name or description...");

    // Category dropdown for filtering products by category
    categoryFilterCombo = new QComboBox;
    categoryFilterCombo->addItem("All Categories");

    // List widget to display popular products (top 5% most ordered items)
    popularProductsList = new QListWidget;

    // ========== SHOPPING CART SECTION ==========
    // Widget to display items in the shopping cart
    cartList = new QListWidget;

    // Button to remove selected item from cart
    removeCartBtn = new QPushButton("Remove Item");

    // Quantity spinner for selecting how many items to add to cart
    quantitySpinBox = new QSpinBox;
    quantitySpinBox->setMinimum(1);
    quantitySpinBox->setMaximum(100);

    // Buttons for bulk order management
    cancelAllOrdersBtn = new QPushButton("Cancel All Orders");
    completeAllOrdersBtn = new QPushButton("Complete All Orders");

    // ========== ACTION BUTTONS ==========
    changePasswordBtn = new QPushButton("Change Password");
    addBtn = new QPushButton("Add to Cart");
    buyBtn = new QPushButton("Buy");
    cancelOrderBtn = new QPushButton("Cancel Order");
    themeToggle = new QCheckBox("Dark Theme");
    logoutBtn = new QPushButton("Logout");

    // ========== SIGNAL-SLOT CONNECTIONS ==========
    // Add selected product to cart
    connect(addBtn, &QPushButton::clicked, this, [this]()
            {
        if (productList->currentRow() >= 0) {
            QListWidgetItem *item = productList->currentItem();
            QString text = item->text();
            // Extract product name from display format "ID: Name - $Price"
            QString productName = text.section(": ", 1, 1).section(" - $", 0, 0);
            int qty = quantitySpinBox->value();
            emit addToCartRequested(productName, qty);
        } });

    // Remove selected item from cart
    connect(removeCartBtn, &QPushButton::clicked, this, [this]()
            {
        if (cartList->currentRow() >= 0) {
            QListWidgetItem *item = cartList->currentItem();
            if (item)
                emit removeFromCartRequested(item->text());
        } });

    // Bulk order management signals
    connect(cancelAllOrdersBtn, &QPushButton::clicked, this, &CustomerPage::cancelAllOrdersRequested);
    connect(completeAllOrdersBtn, &QPushButton::clicked, this, &CustomerPage::completeAllOrdersRequested);

    // Checkout and order management
    connect(buyBtn, &QPushButton::clicked, this, &CustomerPage::buyRequested);
    connect(cancelOrderBtn, &QPushButton::clicked, this, &CustomerPage::cancelOrderRequested);

    // Account and UI controls
    connect(changePasswordBtn, &QPushButton::clicked, this, &CustomerPage::changePasswordRequested);
    connect(themeToggle, &QCheckBox::toggled, this, &CustomerPage::themeToggled);
    connect(logoutBtn, &QPushButton::clicked, this, &CustomerPage::logoutRequested);

    // Live search and filter connections
    connect(searchProductEdit, &QLineEdit::textChanged, this, &CustomerPage::applyProductFilters);
    connect(categoryFilterCombo, &QComboBox::currentTextChanged, this, &CustomerPage::applyProductFilters);

    // ========== ORDER TRACKING SECTION ==========
    // Dropdown to filter orders by status (All, Pending, Confirmed, Cancelled)
    orderStatusFilterCombo = new QComboBox;
    orderStatusFilterCombo->addItem("All");
    orderStatusFilterCombo->addItem("Pending");
    orderStatusFilterCombo->addItem("Confirmed");
    orderStatusFilterCombo->addItem("Cancelled");
    connect(orderStatusFilterCombo, &QComboBox::currentTextChanged, this, &CustomerPage::trackOrdersRequested);

    // List widget displaying customer's order history
    ordersList = new QListWidget;
    // Double-click on order to see full details
    connect(ordersList, &QListWidget::itemDoubleClicked, this, &CustomerPage::orderDetailsRequested);

    // ========== TABBED INTERFACE SETUP ==========
    // Create tab widget to organize different views
    tabWidget = new QTabWidget;

    // ===== PRODUCTS TAB =====
    // Displays available products with search and category filters
    QWidget *productsTab = new QWidget;
    QVBoxLayout *productsTabLayout = new QVBoxLayout(productsTab);
    QHBoxLayout *filterLayout = new QHBoxLayout;
    filterLayout->addWidget(new QLabel("Search:"));
    filterLayout->addWidget(searchProductEdit);
    filterLayout->addWidget(new QLabel("Category:"));
    filterLayout->addWidget(categoryFilterCombo);
    productsTabLayout->addLayout(filterLayout);
    productsTabLayout->addWidget(new QLabel("Available Products:"));
    productsTabLayout->addWidget(productList);
    productsTab->setLayout(productsTabLayout);
    tabWidget->addTab(productsTab, "Products");

    // ===== POPULAR PRODUCTS TAB =====
    // Displays top 5% most frequently ordered products
    QWidget *popularTab = new QWidget;
    QVBoxLayout *popularTabLayout = new QVBoxLayout(popularTab);
    popularTabLayout->addWidget(new QLabel("Popular Products:"));
    popularTabLayout->addWidget(popularProductsList);
    popularTab->setLayout(popularTabLayout);
    tabWidget->addTab(popularTab, "Popular");

    // ===== SHOPPING CART TAB =====
    // Displays items added to cart and allows removal
    QWidget *cartTab = new QWidget;
    QVBoxLayout *cartTabLayout = new QVBoxLayout(cartTab);
    cartTabLayout->addWidget(new QLabel("Shopping Cart:"));
    cartTabLayout->addWidget(cartList);
    cartTabLayout->addWidget(removeCartBtn);
    cartTabLayout->addWidget(cancelAllOrdersBtn);
    cartTabLayout->addWidget(completeAllOrdersBtn);
    cartTab->setLayout(cartTabLayout);
    tabWidget->addTab(cartTab, "Cart");

    // ===== ORDER HISTORY TAB =====
    // Displays all customer orders with status tracking
    QWidget *ordersTab = new QWidget;
    QVBoxLayout *ordersTabLayout = new QVBoxLayout(ordersTab);
    ordersTabLayout->addWidget(new QLabel("Your Orders: (double-click an order for details)"));
    ordersTabLayout->addWidget(ordersList);
    ordersTab->setLayout(ordersTabLayout);
    tabWidget->addTab(ordersTab, "My Orders");

    // ========== MAIN LAYOUT ASSEMBLY ==========
    // Add all components to main layout
    layout->addWidget(profileLabel);
    layout->addWidget(tabWidget);

    // Product action buttons (Add to Cart, Buy)
    QHBoxLayout *productButtonLayout = new QHBoxLayout;
    productButtonLayout->addWidget(addBtn);
    productButtonLayout->addWidget(buyBtn);
    layout->addLayout(productButtonLayout);

    // Order action buttons (Cancel Order)
    QHBoxLayout *orderControlLayout = new QHBoxLayout;
    orderControlLayout->addWidget(cancelOrderBtn);
    layout->addLayout(orderControlLayout);

    // Order filtering section
    layout->addWidget(new QLabel("Filter My Orders:"));
    layout->addWidget(orderStatusFilterCombo);

    // Bottom action buttons (Password, Theme, Logout)
    QHBoxLayout *bottomButtonLayout = new QHBoxLayout;
    bottomButtonLayout->addWidget(changePasswordBtn);
    bottomButtonLayout->addWidget(themeToggle);
    bottomButtonLayout->addWidget(logoutBtn);
    layout->addLayout(bottomButtonLayout);

    // Stretch to fill remaining space
    layout->addStretch();

    setLayout(layout);
}

CustomerPage::~CustomerPage()
{
}

// ============================================================================
// PURPOSE: Display the customer's username and role in the profile section
// PARAMETERS: username - The logged-in customer's username
// DESCRIPTION: Updates the profile label at the top of the page to show a welcome
//              message with the customer's name and role indicator.
// ============================================================================
void CustomerPage::setProfile(const QString &username)
{
    profileLabel->setText("Welcome, " + username + " (Customer)");
}

// ============================================================================
// PURPOSE: Initialize product list display on page load
// DESCRIPTION: Calls applyProductFilters() to populate the product list with
//              all available products using current filter settings.
// ============================================================================
void CustomerPage::loadProducts()
{
    applyProductFilters();
}

// ============================================================================
// PURPOSE: Refresh the shopping cart display
// DESCRIPTION: Clears the cart list widget and repopulates it with current
//              items from the Cart object. Called whenever cart contents change.
// ============================================================================
void CustomerPage::updateCartView()
{
    cartList->clear();
    auto items = cart.getItems();
    for (const QString &item : items)
    {
        cartList->addItem(item);
    }
}

// ============================================================================
// PURPOSE: Filter and display products based on search and category criteria
// DESCRIPTION: Clears the product list and repopulates it with only products
//              matching the current search text and selected category.
//              - Gets search text from searchProductEdit (case-insensitive)
//              - Gets category filter from categoryFilterCombo
//              - Searches both product name and description for matches
//              - Formats each item as: "ID: Name - $Price (qty: Available)\nDescription"
//              - Called when search text or category selection changes
// ============================================================================
void CustomerPage::applyProductFilters()
{
    productList->clear();
    int count = 0;
    const Product *products = Product::getProducts(count);
    QString searchText = searchProductEdit->text().trimmed().toLower();
    QString category = categoryFilterCombo->currentText();

    for (int i = 0; i < count; i++)
    {
        QString name = QString::fromStdString(products[i].getName());
        QString description = QString::fromStdString(products[i].getDescription());
        QString combined = (name + " " + description).toLower();
        if (!searchText.isEmpty() && !combined.contains(searchText))
            continue;
        if (category != "All Categories")
        {
            // As a simple category helper, search category text in the product description.
            if (!description.toLower().contains(category.toLower()) && !name.toLower().contains(category.toLower()))
                continue;
        }

        QString item = QString::number(products[i].getId()) + ": " + name + " - $" + QString::number(products[i].getPrice()) + " (qty: " + QString::number(products[i].getQuantity()) + ")\n" + description;
        productList->addItem(item);
    }
}

// ============================================================================
// PURPOSE: Display the top 5% most frequently ordered products
// PARAMETERS: products - List of popular product names and details
// DESCRIPTION: Clears the popular products list and populates it with the
//              provided product list. These are the most frequently ordered
//              items based on order history analytics.
// ============================================================================
void CustomerPage::setPopularProducts(const QStringList &products)
{
    popularProductsList->clear();
    for (const QString &product : products)
        popularProductsList->addItem(product);
}

// ============================================================================
// PURPOSE: Request refresh of customer's order history
// DESCRIPTION: Emits signal to load and display all orders for the current
//              customer. Called when switching to Orders tab.
// ============================================================================
void CustomerPage::loadOrders()
{
    emit trackOrdersRequested();
}

// ============================================================================
// PURPOSE: Load shopping cart from persistent storage
// PARAMETERS: username - The customer's username used to identify cart file
// DESCRIPTION: Clears current cart and loads items from the customer's saved
//              cart file (cart_<username>.csv). Updates the cart display.
//              Called when user logs in to restore previous shopping session.
// ============================================================================
void CustomerPage::loadCart(const QString &username)
{
    cart.clearCart();
    cart.loadFromFile("cart_" + username.toStdString() + ".csv");
    updateCartView();
}

// ============================================================================
// PURPOSE: Persist shopping cart to file storage
// PARAMETERS: username - The customer's username used to identify cart file
// DESCRIPTION: Saves current cart contents to a CSV file named cart_<username>.csv.
//              Called on logout or after significant cart changes to preserve
//              items for the next session.
// ============================================================================
void CustomerPage::saveCart(const QString &username)
{
    cart.saveToFile("cart_" + username.toStdString() + ".csv");
}

// ============================================================================
// PURPOSE: Empty the shopping cart and refresh display
// DESCRIPTION: Clears all items from the Cart object and updates the cart
//              list widget to reflect the empty state.
// ============================================================================
void CustomerPage::clearCart()
{
    cart.clearCart();
    updateCartView();
}

// ============================================================================
// PURPOSE: Provide access to the customer's shopping cart
// RETURNS: Reference to the Cart object for item manipulation
// DESCRIPTION: Returns a reference to the internal cart object, allowing
//              external code to add/remove items or query cart contents.
// ============================================================================
Cart &CustomerPage::getCart()
{
    return cart;
}

// ============================================================================
// PURPOSE: Retrieve the name of the currently selected product
// RETURNS: Product name and ID (e.g., "ID: ProductName"), or empty string if none selected
// DESCRIPTION: Parses the selected item from the product list to extract
//              the product name. The format in list is "ID: Name - $Price (qty: X)\nDesc"
//              and this extracts the "ID: Name" portion.
// ============================================================================
QString CustomerPage::getSelectedProductName() const
{
    if (productList->currentRow() >= 0)
    {
        QListWidgetItem *item = productList->currentItem();
        if (item)
        {
            QString text = item->text();
            return text.section(" - $", 0, 0);
        }
    }
    return QString();
}

// ============================================================================
// PURPOSE: Get the index of the currently selected order
// RETURNS: Order index if selected, or -1 if no order is selected
// DESCRIPTION: Retrieves the order index stored in the Qt::UserRole data
//              of the selected list item. This index is used to access the
//              order details from the order history.
// ============================================================================
int CustomerPage::getSelectedOrderIndex() const
{
    if (ordersList->currentRow() >= 0)
    {
        QListWidgetItem *item = ordersList->currentItem();
        if (item)
        {
            return item->data(Qt::UserRole).toInt();
        }
    }
    return -1;
}

// ============================================================================
// PURPOSE: Get the currently selected order status filter
// RETURNS: Selected filter value ("All", "Pending", "Confirmed", "Cancelled")
// DESCRIPTION: Returns the current text from the order status filter dropdown.
//              Used to determine which orders to display in the My Orders tab.
// ============================================================================
QString CustomerPage::getSelectedOrderFilter() const
{
    return orderStatusFilterCombo->currentText();
}

// ============================================================================
// PURPOSE: Populate the order history list with customer's orders
// PARAMETERS: orders - Vector of pairs containing (order display text, order index)
// DESCRIPTION: Clears the orders list and adds each order with its display
//              text (format: grouped by orderId with total qty and price).
//              Stores the order index in Qt::UserRole for retrieval when selected.
// ============================================================================
void CustomerPage::setOrderItems(const QVector<QPair<QString, int>> &orders)
{
    ordersList->clear();
    for (const auto &order : orders)
    {
        QListWidgetItem *item = new QListWidgetItem(order.first);
        item->setData(Qt::UserRole, order.second);
        ordersList->addItem(item);
    }
}

// ============================================================================
// PURPOSE: Update theme toggle state to reflect current theme
// PARAMETERS: isDark - true if dark theme is active, false for light theme
// DESCRIPTION: Sets the theme checkbox state without triggering the toggled
//              signal. Called to sync the UI with the actual theme state.
// ============================================================================
void CustomerPage::setTheme(bool isDark)
{
    themeToggle->setChecked(isDark);
}