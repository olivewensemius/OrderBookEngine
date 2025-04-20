#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

class OrderBook {
public:
    struct Order {
        int orderId;        
        double price;       
        int quantity;       
        std::string orderType;  
        Order(int id, double p, int q, std::string type) 
            : orderId(id), price(p), quantity(q), orderType(type) {}
    };
    
    // trade record structure to keep track of executed trades
    struct Trade {
        int buyOrderId;
        int sellOrderId;
        double price;
        int quantity;
        
        Trade(int buy, int sell, double p, int q) 
            : buyOrderId(buy), sellOrderId(sell), price(p), quantity(q) {}
    };

    // price-ordered maps for buy and sell sides
    std::map<double, std::list<Order>> buyOrders;
    std::map<double, std::list<Order>> sellOrders;
    
    // store all completed trades
    std::vector<Trade> completedTrades;

    // core order management 
    void addOrder(int orderId, double price, int quantity, std::string orderType);
    void removeOrder(int orderId, std::string orderType);
    void updateOrderQuantity(int orderId, std::string orderType, int newQuantity);
    
    // matching and execution
    std::vector<Trade> matchOrders();
    
    // lookup
    Order findBestBuyOrder();
    Order findBestSellOrder();
    std::list<Order> findOrdersAtPrice(double price, std::string orderType);
    // display
    void printOrders();
    void printList(std::list<Order> orderList);
    void printTrades();
};

#endif // ORDERBOOK_H