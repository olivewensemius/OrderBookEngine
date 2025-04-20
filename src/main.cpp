#include <iostream>
#include "OrderBook.h"
#include "../tests/benchmark.cpp"

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "benchmark") {
        benchmark();
        return 0;
    }
    
    std::cout << "\n===== ORDER BOOK DEMO =====\n";
    OrderBook ob;

    std::cout << "\nAdding Buy Orders:\n";
    ob.addOrder(1, 50.0, 100, "buy");
    ob.addOrder(2, 51.0, 200, "buy");
    ob.addOrder(3, 49.0, 150, "buy");
    
    std::cout << "\nAdding Sell Orders:\n";
    ob.addOrder(4, 49.5, 50, "sell");
    ob.addOrder(5, 50.5, 250, "sell");
    ob.addOrder(6, 51.5, 100, "sell");

    std::cout << "\n===== INITIAL ORDER BOOK STATE =====\n";
    ob.printOrders();
    
    std::cout << "\n===== MATCHING ORDERS =====\n";
    std::vector<OrderBook::Trade> trades = ob.matchOrders();
    
    std::cout << "\n===== ORDER BOOK AFTER MATCHING =====\n";
    ob.printOrders();
    
    ob.printTrades();
    
    std::cout << "\n===== ORDER MANIPULATION =====\n";
    
    ob.updateOrderQuantity(5, "sell", 100);
    
    ob.removeOrder(3, "buy");
    std::cout << "\n===== FINAL ORDER BOOK STATE =====\n";
    ob.printOrders();
    
    return 0;
}