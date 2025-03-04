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

    std::shared_ptr<OrderBook::Order> bestBuy = ob.findBestBuyOrder();
    std::cout << "\nBest Buy Order: " << bestBuy->quantity << " shares at $" << bestBuy->price << "\n";

    std::shared_ptr<OrderBook::Order> bestSell = ob.findBestSellOrder();
    std::cout << "Best Sell Order: " << bestSell->quantity << " shares at $" << bestSell->price << "\n";

    std::list<std::shared_ptr<OrderBook::Order>> ordersAt50 = ob.findOrdersAtPrice(50.5, "sell");
    
    ob.printList(ordersAt50);


    return 0;
}
