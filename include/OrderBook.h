#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <map>
#include <list>
#include <memory>
#include <string>
#include <queue>

class OrderBook {
public:
    struct Order {
        int orderId;        
        double price;       
        int quantity;       
        std::string orderType;  
        Order(int id, double p, int q, std::string type) 
            : orderId(id), price(p), quantity(q), orderType(type) {}
        
        bool operator<(const Order& other) const {
                return (orderType == "buy") ? (price < other.price) : (price > other.price);
            }
    };

    std::priority_queue<Order> buyOrders;  
    std::priority_queue<Order> sellOrders; 

    void addOrder(int orderId, double price, int quantity, const std::string& orderType);
    const Order* findBestBuyOrder();
    const Order* findBestSellOrder();
    std::list<const Order*> findOrdersAtPrice(double price, const std::string& orderType);
    void printOrders();
    void printList(const std::list<const Order*>& orderList);
    void matchOrders();
};

#endif // ORDERBOOK_H
