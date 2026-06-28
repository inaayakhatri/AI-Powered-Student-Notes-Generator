cmake_minimum_required(VERSION 3.16)
project(ConsoleApp VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 Widgets for the GUI target
find_package(Qt6 COMPONENTS Widgets REQUIRED)

include_directories(.)

set(QT_SOURCES
    Admin.cpp
    Cart.cpp
    Customer.cpp
    Product.cpp
    User.cpp
    UserWindow.cpp
    OrderManager.cpp
    MainPage.cpp
    LoginPage.cpp
    RegisterPage.cpp
    CustomerPage.cpp
    AdminPage.cpp
    CheckoutDialog.cpp
    SalesDialog.cpp
    main.cpp
)

add_executable(main ${QT_SOURCES})
set_target_properties(main PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)
target_link_libraries(main PRIVATE Qt6::Widgets)
