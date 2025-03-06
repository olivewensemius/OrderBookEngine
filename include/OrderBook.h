#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <map>
#include <list>
#include <memory>
#include <string>

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

    std::map<double, std::list<std::unique_ptr<Order>>> buyOrders;
    std::map<double, std::list<std::unique_ptr<Order>>> sellOrders;

    void addOrder(int orderId, double price, int quantity, const std::string& orderType);
    const Order* findBestBuyOrder();
    const Order* findBestSellOrder();
    std::list<const Order*> findOrdersAtPrice(double price, const std::string& orderType);
    void printOrders();
    void printList(const std::list<const Order*>& orderList);
    void matchOrders();
};

#endif // ORDERBOOK_H
