/*Princess Angela Cacao 
IT2B INTEPROG*/

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <string>

using namespace std;

// Product Class
class Product {
public:
    string productId;
    string name;
    double price;

    Product(string id, string n, double p) : productId(id), name(n), price(p) {}

    void displayProduct() {
        cout << "| " << setw(10) << left << productId << " | " << setw(15) << name 
             << " | " << setw(10) << fixed << setprecision(0) << price << " |" << endl;
    }
};

// ShoppingCart Class
class ShoppingCart {
public:
    struct CartItem {
        Product* product;
        int quantity;
    };

    vector<CartItem> items;

    void addProduct(Product* product, int quantity) {
        for (auto& item : items) {
            if (item.product->productId == product->productId) {
                item.quantity += quantity;
                cout << "Product quantity updated successfully!" << endl;
                return;
            }
        }
        items.push_back({product, quantity});
        cout << "Product added successfully!" << endl;
    }

    void displayCart() {
        if (items.empty()) {
            cout << "Shopping cart is empty!" << endl;
            return;
        }
        cout << "-----------------------------------------------------------" << endl;
        cout << "| " << setw(10) << "Product ID" << " | " << setw(15) << "Name" 
             << " | " << setw(10) << "Price" << " | " << setw(10) << "Quantity" << " |" << endl;
        cout << "-----------------------------------------------------------" << endl;
        for (auto& item : items) {
            cout << "| " << setw(10) << item.product->productId << " | " << setw(15) << item.product->name 
                 << " | " << setw(10) << fixed << setprecision(0) << item.product->price 
                 << " | " << setw(10) << item.quantity << " |" << endl;
        }
        cout << "-----------------------------------------------------------" << endl;
    }

    double calculateTotal() {
        double total = 0;
        for (auto& item : items) {
            total += item.product->price * item.quantity;
        }
        return total;
    }

    void clearCart() {
        items.clear();
    }
};

// Order Class
class Order {
public:
    int orderId;
    double totalAmount;
    vector<ShoppingCart::CartItem> items;

    Order(int id, ShoppingCart& cart) : orderId(id), totalAmount(cart.calculateTotal()), items(cart.items) {}

    void displayOrder() {
        cout << "\nOrder ID: " << orderId << endl;
        cout << "Total Amount: " << fixed << setprecision(0) << totalAmount << endl;
        cout << "Order Details:" << endl;
        if (items.empty()) {
            cout << "No items in this order." << endl;
        } else {
            cout << "-------------------------------------------------------------------------" << endl;
            cout << "| " << setw(10) << "Product ID" << " | " << setw(15) << "Name" 
                 << " | " << setw(10) << "Price" << " | " << setw(10) << "Quantity" 
                 << " | " << setw(10) << "Total" << " |" << endl;
            cout << "-------------------------------------------------------------------------" << endl;
            for (auto& item : items) {
                double itemTotal = item.product->price * item.quantity;
                cout << "| " << setw(10) << item.product->productId << " | " << setw(15) << item.product->name 
                     << " | " << setw(10) << fixed << setprecision(0) << item.product->price 
                     << " | " << setw(10) << item.quantity 
                     << " | " << setw(10) << fixed << setprecision(0) << itemTotal << " |" << endl;
            }
            cout << "-------------------------------------------------------------------------" << endl;
        }
    }
};

int main() {
    vector<Product> products = {
        {"1", "Blush", 200},
        {"2", "Eye Shadow", 300},
        {"3", "Lipstick", 400},
        {"4", "Powder", 350},
        {"5", "Mascara", 500}
    };

    ShoppingCart cart;
    vector<Order> orders;
    int orderIdCounter = 1;
    char choice;

    do {
        cout << "\nAngela's Shop Area" << endl;
        cout << "1. View Products\n2. Add Product to Cart\n3. View Shopping Cart\n4. Checkout\n5. View Orders\n6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
           case '1': 
                cout << "----------------------------------------------" << endl;
                cout << "| " << setw(10) << "Product ID" << " | " << setw(15) << "Name" << " | " << setw(10) << "Price" << " |" << endl;
                cout << "----------------------------------------------" << endl;
                for (auto& p : products) {
                    p.displayProduct();
                }
                cout << "----------------------------------------------" << endl;
                break;
            case '2': {
                string productId;
                int quantity;
                cout << "Enter Product ID to add (or 'C' to Cancel): ";
                cin >> productId;
                if (productId == "C" || productId == "c") break;
                cout << "Enter quantity: ";
                cin >> quantity;
                if (cin.fail() || quantity <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid quantity. Please enter a valid number." << endl;
                    break;
                }
                bool found = false;
                for (auto& p : products) {
                    if (p.productId == productId) {
                        cart.addProduct(&p, quantity);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Invalid Product ID!" << endl;
                }
                break;
            }
            case '3':
                cart.displayCart();
                break;
            case '4':
                if (cart.items.empty()) {
                    cout << "Your cart is empty!" << endl;
                } else {
                    char confirm;
                    cout << "Proceed to checkout? (Y/N): ";
                    cin >> confirm;
                    if (confirm == 'Y' || confirm == 'y' ) {
                        orders.push_back(Order(orderIdCounter++, cart));
                        cart.clearCart();
                        cout << "You have successfully checked out the products!" << endl;
                    } else {
                        cout << "Checkout canceled." << endl;
                    }
                }
                break;
            case '5': 
                if (orders.empty()) {
                    cout << "No orders found!" << endl;
                } else {
                    for (auto& order : orders) {
                        order.displayOrder();
                    }
                }
                break;
            case '6': 
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
                break;
        }
    } while (choice != '6');  
    return 0;
}