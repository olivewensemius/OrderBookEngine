#include "OrderBook.h"

void OrderBook::addOrder(int orderId, double price, int quantity, std::string orderType) {
    Order newOrder(orderId, price, quantity, orderType);

    if(orderType == "buy"){
        buyOrders[price].push_back(newOrder);
    }else if(orderType == "sell"){
        sellOrders[price].push_back(newOrder);
    };

    std::cout << "Order Added: " << orderType << " " << quantity 
              << " shares at $" << price << std::endl;
}

OrderBook::Order OrderBook::findBestBuyOrder(){
    if(!buyOrders.empty()){
        return buyOrders.rbegin()->second.front();
    }
    throw std::runtime_error("No buy orders available");
}

OrderBook::Order OrderBook::findBestSellOrder(){
    if(!sellOrders.empty()){
        return sellOrders.begin()->second.front();
    }
    throw std::runtime_error("No sell orders available");
}

std::list<OrderBook::Order> OrderBook::findOrdersAtPrice(double price, std::string orderType) {
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
            std::cout << "ID: " << order.orderId << " | " 
                      << order.quantity << " shares at $" << order.price << "\n";
        }
    }

    std::cout << "\nSell Orders:\n";
    for (auto it = sellOrders.begin(); it != sellOrders.end(); ++it) {
        for (const auto &order : it->second) {
            std::cout << "ID: " << order.orderId << " | " 
                      << order.quantity << " shares at $" << order.price << "\n";
        }
    }
}

void OrderBook::printList(std::list<OrderBook::Order> orderList){
    for (const auto& order : orderList) {
        std::cout << "ID: " << order.orderId << " | " 
                  << order.quantity << " shares at $" << order.price << "\n";
    }
}

std::vector<OrderBook::Trade> OrderBook::matchOrders() {
    std::vector<Trade> newTrades;
    while (!buyOrders.empty() && !sellOrders.empty()) {
        auto bestBuyIt = buyOrders.rbegin();  //highest buy price
        auto bestSellIt = sellOrders.begin(); // lowest sell price
        
        if (bestBuyIt->first >= bestSellIt->first) {
            double tradePrice = bestSellIt->first;
            
            auto& buyOrderList = bestBuyIt->second;
            auto& sellOrderList = bestSellIt->second;
            

            while (!buyOrderList.empty() && !sellOrderList.empty()) {
                Order& buyOrder = buyOrderList.front();
                Order& sellOrder = sellOrderList.front();
                
                int tradeQuantity = std::min(buyOrder.quantity, sellOrder.quantity);
                
                // create a new trade
                Trade newTrade(buyOrder.orderId, sellOrder.orderId, tradePrice, tradeQuantity);
                newTrades.push_back(newTrade);
                completedTrades.push_back(newTrade);
            
                buyOrder.quantity -= tradeQuantity;
                sellOrder.quantity -= tradeQuantity;
                
                if (buyOrder.quantity == 0) {
                    buyOrderList.pop_front();
                }
                
                if (sellOrder.quantity == 0) {
                    sellOrderList.pop_front();
                }

                if (buyOrderList.empty()) {
                    break;
                }
            }
            
            if (buyOrderList.empty()) {
                buyOrders.erase(std::next(bestBuyIt).base());
            }
            
            if (sellOrderList.empty()) {
                sellOrders.erase(bestSellIt->first);
            }
        } else {
            break;
        }
    }
    
    std::cout << "Matched " << newTrades.size() << " trades" << std::endl;
    return newTrades;
}

void OrderBook::removeOrder(int orderId, std::string orderType) {
    auto& orders = (orderType == "buy") ? buyOrders : sellOrders;
        for (auto& [price, orderList] : orders) {
        for (auto it = orderList.begin(); it != orderList.end(); ++it) {
            if (it->orderId == orderId) {
                orderList.erase(it);
                if (orderList.empty()) {
                    orders.erase(price);
                }
                std::cout << "Order " << orderId << " removed" << std::endl;
                return;
            }
        }
    }
    
    std::cout << "Order " << orderId << " not found" << std::endl;
}

void OrderBook::updateOrderQuantity(int orderId, std::string orderType, int newQuantity) {
    auto& orders = (orderType == "buy") ? buyOrders : sellOrders;
    
    for (auto& [price, orderList] : orders) {
        for (auto& order : orderList) {
            if (order.orderId == orderId) {
                order.quantity = newQuantity;
                std::cout << "Order " << orderId << " updated to quantity " << newQuantity << std::endl;
                return;
            }
        }
    }
    
    std::cout << "Order " << orderId << " not found" << std::endl;
}

void OrderBook::printTrades() {
    std::cout << "\nCompleted Trades:\n";
    for (const auto& trade : completedTrades) {
        std::cout << "Trade: Buy Order #" << trade.buyOrderId 
                  << " and Sell Order #" << trade.sellOrderId
                  << " | " << trade.quantity << " shares at $" << trade.price << "\n";
    }
}