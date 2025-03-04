#include "OrderBook.h"

void OrderBook::addOrder(int orderId, double price, int quantity, 
const std::string& orderType) {
    auto newOrder = std::make_shared<Order>(orderId, price, quantity, orderType);

    if(orderType == "buy"){
        buyOrders[price].push_back(newOrder);
    }else if(orderType == "sell"){
        sellOrders[price].push_back(newOrder);
    };

    std::cout << "Order Added: " << orderType << " " << quantity 
              << " shares at $" << price << std::endl;

}

std::shared_ptr<OrderBook::Order> OrderBook::findBestBuyOrder(){
    if(!buyOrders.empty()){
        return buyOrders.rbegin()->second.front();
    }
    throw std::runtime_error("No buy orders available");
}

std::shared_ptr<OrderBook::Order> OrderBook::findBestSellOrder(){
    if(!sellOrders.empty()){
        return sellOrders.begin()->second.front();
    }
    throw std::runtime_error("No sell orders available");
    
}

std::list<std::shared_ptr<OrderBook::Order>> OrderBook::findOrdersAtPrice(double price, std::string orderType) {
    if (orderType == "buy") {
        auto it = buyOrders.find(price);
        if (it != buyOrders.end()) {
            return it->second;
        }
    } else {
        auto it = sellOrders.find(price);
        if (it != sellOrders.end()) {
            return it->second;
        }
    }
    return {};
}

void OrderBook::printOrders() {
    std::cout << "\nBuy Orders:\n";
    for (auto it = buyOrders.rbegin(); it != buyOrders.rend(); ++it) {
        for (const auto &order : it->second) {
            std::cout << "ID: " << order->orderId << " | " 
                      << order->quantity << " shares at $" << order->price << "\n";
        }
    }

    std::cout << "\nSell Orders:\n";
    for (auto it = sellOrders.begin(); it != sellOrders.end(); ++it) {
        for (const auto &order : it->second) {
            std::cout << "ID: " << order->orderId << " | " 
                      << order->quantity << " shares at $" << order->price << "\n";
        }
    }
}

void OrderBook::printList(std::list<std::shared_ptr<OrderBook::Order>> orderList){
    for (const auto& order : orderList) {
        std::cout << "ID: " << order->orderId << " | " 
                  << order->quantity << " shares at $" << order->price << "\n";
    }
}