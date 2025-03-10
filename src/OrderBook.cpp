#include "OrderBook.h"

void OrderBook::addOrder(int orderId, double price, int quantity, const std::string& orderType) {
    auto newOrder = Order(orderId, price, quantity, orderType);
    
    if (orderType == "buy") {
        buyOrders.push(newOrder);
    } else if (orderType == "sell") {
        sellOrders.push(newOrder);
    }

    std::cout << "Order Added: " << orderType << " " << quantity 
              << " shares at $" << price << std::endl;

    matchOrders();
}

const OrderBook::Order* OrderBook::findBestBuyOrder() {
    if (!buyOrders.empty()) {
        return &buyOrders.top();
    }
    throw std::runtime_error("No buy orders available");
}

const OrderBook::Order* OrderBook::findBestSellOrder() {
    if (!sellOrders.empty()) {
        return &sellOrders.top();
    }
    throw std::runtime_error("No sell orders available");
}

std::list<const OrderBook::Order*> OrderBook::findOrdersAtPrice(double price, const std::string& orderType) {
    std::list<const OrderBook::Order*> ordersList;

    if (orderType == "buy") {
        auto tempQueue = buyOrders;
        while (!tempQueue.empty()) {
            const auto& order = tempQueue.top();
            if (order.price == price) {
                ordersList.push_back(&order);
            }
            tempQueue.pop();
        }
    } else {
        auto tempQueue = sellOrders;
        while (!tempQueue.empty()) {
            const auto& order = tempQueue.top();
            if (order.price == price) {
                ordersList.push_back(&order);
            }
            tempQueue.pop();
        }
    }
    return ordersList;
}


void OrderBook::printOrders() {
    std::cout << "\nBuy Orders (Highest Price First):\n";
    auto tempBuy = buyOrders;
    while (!tempBuy.empty()) {
        const auto& order = tempBuy.top();
        std::cout << "ID: " << order.orderId << " | " 
                  << order.quantity << " shares at $" << order.price << "\n";
        tempBuy.pop();
    }

    std::cout << "\nSell Orders (Lowest Price First):\n";
    auto tempSell = sellOrders;
    while (!tempSell.empty()) {
        const auto& order = tempSell.top();
        std::cout << "ID: " << order.orderId << " | " 
                  << order.quantity << " shares at $" << order.price << "\n";
        tempSell.pop();
    }
}

void OrderBook::printList(const std::list<const OrderBook::Order*>& orderList) {
    for (const auto& order : orderList) {
        std::cout << "ID: " << order->orderId << " | " 
                  << order->quantity << " shares at $" << order->price << "\n";
    }
}


void OrderBook::matchOrders() {
    while (!buyOrders.empty() && !sellOrders.empty()) {
        auto bestBid = buyOrders.top();  // Get best buy order (highest price)
        auto bestAsk = sellOrders.top(); // Get best sell order (lowest price)

        if (bestBid.price < bestAsk.price) {
            // No matching possible, exit
            break;
        }

        // Determine trade quantity
        int tradeQuantity = std::min(bestBid.quantity, bestAsk.quantity);
        double tradePrice = bestAsk.price;  // Trade happens at the ask price

        std::cout << "Executed Trade: " << tradeQuantity << " shares at $" << tradePrice << "\n";

        // Update order quantities
        bestBid.quantity -= tradeQuantity;
        bestAsk.quantity -= tradeQuantity;

        // Remove fully executed orders
        buyOrders.pop();
        sellOrders.pop();

        // If an order is partially filled, reinsert it
        if (bestBid.quantity > 0) {
            buyOrders.push(bestBid);
        }
        if (bestAsk.quantity > 0) {
            sellOrders.push(bestAsk);
        }
    }
}
