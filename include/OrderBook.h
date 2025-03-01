#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <map>
#include <string>
#include <list>

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

    std::map<double, std::list<Order>> buyOrders;
    std::map<double, std::list<Order>> sellOrders;

    void addOrder(int orderId, double price, int quantity, std::string orderType);
    Order findBestBuyOrder();
    Order findBestSellOrder();
    std::list<Order> findOrdersAtPrice(double price, std::string orderType);
    void printOrders();
    void printList(std::list<Order> orderList);
};

#endif // ORDERBOOK_H
