#include <iostream>
#include "OrderBook.h"
#include "../tests/benchmark.cpp"

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "benchmark") {
        benchmark();
        return 0;
    }
    
    OrderBook ob;
    ob.addOrder(1, 50.0, 100, "buy");
    ob.addOrder(2, 51.0, 200, "buy");
    ob.addOrder(3, 49.5, 150, "sell");
    ob.addOrder(4, 50.5, 250, "sell");

    ob.printOrders();

    const OrderBook::Order* bestBuy = ob.findBestBuyOrder();
    std::cout << "\nBest Buy Order: " << bestBuy->quantity << " shares at $" << bestBuy->price << "\n";

    const OrderBook::Order* bestSell = ob.findBestSellOrder();
    std::cout << "Best Sell Order: " << bestSell->quantity << " shares at $" << bestSell->price << "\n";

    std::list<const OrderBook::Order*> ordersAt50 = ob.findOrdersAtPrice(50.5, "sell");
    
    ob.printList(ordersAt50);
    
    // Add orders and test matching
    ob.addOrder(1, 100.0, 50, "buy");
    ob.addOrder(2, 102.0, 100, "buy");
    ob.addOrder(3, 101.0, 200, "buy");
    ob.addOrder(4, 101.5, 150, "sell");
    ob.addOrder(5, 101.0, 50, "sell");
    ob.printOrders();


    return 0;
}
