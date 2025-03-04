#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <memory>

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

    std::map<double, std::list<std::shared_ptr<Order>>> buyOrders;
    std::map<double, std::list<std::shared_ptr<Order>>> sellOrders;

    void addOrder(int orderId, double price, int quantity, const std::string& orderType);
    std::shared_ptr<Order> findBestBuyOrder();
    std::shared_ptr<Order> findBestSellOrder();
    std::list<std::shared_ptr<Order>> findOrdersAtPrice(double price, std::string orderType);
    void printOrders();
    void printList(std::list<std::shared_ptr<Order>> orderList);
};

#endif // ORDERBOOK_H
