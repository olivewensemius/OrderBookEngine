#include "OrderBook.h"

void OrderBook::addOrder(int orderId, double price, int quantity, const std::string& orderType) {
    auto newOrder = std::make_unique<Order>(orderId, price, quantity, orderType);

    if (orderType == "buy") {
        buyOrders[price].push_back(std::move(newOrder));
    } else if (orderType == "sell") {
        sellOrders[price].push_back(std::move(newOrder));
    }

    std::cout << "Order Added: " << orderType << " " << quantity 
              << " shares at $" << price << std::endl;

    matchOrders();
}

const OrderBook::Order* OrderBook::findBestBuyOrder() {
    if (!buyOrders.empty()) {
        return buyOrders.rbegin()->second.front().get();
    }
    throw std::runtime_error("No buy orders available");
}

const OrderBook::Order* OrderBook::findBestSellOrder() {
    if (!sellOrders.empty()) {
        return sellOrders.begin()->second.front().get();
    }
    throw std::runtime_error("No sell orders available");
}

std::list<const OrderBook::Order*> OrderBook::findOrdersAtPrice(double price, const std::string& orderType) {
    std::list<const OrderBook::Order*> ordersList;

    if (orderType == "buy") {
        auto it = buyOrders.find(price);
        if (it != buyOrders.end()) {
            for (const auto& order : it->second) {
                ordersList.push_back(order.get());  // ✅ Convert unique_ptr to raw pointer
            }
        }
    } else {
        auto it = sellOrders.find(price);
        if (it != sellOrders.end()) {
            for (const auto& order : it->second) {
                ordersList.push_back(order.get());
            }
        }
    }
    return ordersList;
}

void OrderBook::printOrders() {
    std::cout << "\nBuy Orders:\n";
    for (auto it = buyOrders.rbegin(); it != buyOrders.rend(); ++it) {
        for (const auto& order : it->second) {
            std::cout << "ID: " << order->orderId << " | " 
                      << order->quantity << " shares at $" << order->price << "\n";
        }
    }

    std::cout << "\nSell Orders:\n";
    for (auto it = sellOrders.begin(); it != sellOrders.end(); ++it) {
        for (const auto& order : it->second) {
            std::cout << "ID: " << order->orderId << " | " 
                      << order->quantity << " shares at $" << order->price << "\n";
        }
    }
}

void OrderBook::printList(const std::list<const OrderBook::Order*>& orderList) {
    for (const auto& order : orderList) {
        std::cout << "ID: " << order->orderId << " | " 
                  << order->quantity << " shares at $" << order->price << "\n";
    }
}

void OrderBook::matchOrders() {
    while (!buyOrders.empty() && !sellOrders.empty()){
        auto bestBid = buyOrders.rbegin();
        auto bestAsk = sellOrders.begin();

        if(bestBid->first < bestAsk->first){
            break;
        }

        auto& buyQueue = bestBid->second;
        auto& sellQueue = bestAsk->second;

        while(!buyQueue.empty() && !sellQueue.empty()){
            auto& buyOrder = buyQueue.front();
            auto& sellOrder = sellQueue.front();

            int tradeQuantity = std::min(buyOrder->quantity, sellOrder->quantity);
            double tradePrice = sellOrder->price;

            std::cout << "Executed Trade: " << tradeQuantity << " shares at $" << tradePrice << "\n";

            buyOrder->quantity -= tradeQuantity;
            sellOrder->quantity -= tradeQuantity;

            if (buyOrder->quantity == 0) {
                buyQueue.pop_front();
            }
            if (sellOrder->quantity == 0) {
                sellQueue.pop_front();
            }
        }

        if (buyQueue.empty()) {
            buyOrders.erase(bestBid->first);
        }
        if (sellQueue.empty()) {
            sellOrders.erase(bestAsk->first);
        }


    }
}