#include <iostream>
#include <chrono>
#include "../include/OrderBook.h"

void benchmark() {
    OrderBook test;
    int numOrders = 100000; 
    std::cout << "\nRunning Performance Benchmark...\n";

    // Order insertion
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOrders; ++i) {
        test.addOrder(i, 50.0 + (i % 5), 100, (i % 2 == 0) ? "buy" : "sell");
    }
    auto end = std::chrono::high_resolution_clock::now();
    double insertionTime = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Inserted " << numOrders << " orders in " << insertionTime << " ms\n";

    // Order lookup
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOrders; ++i) {
        test.findOrdersAtPrice(50.0 + (i % 5), (i % 2 == 0) ? "buy" : "sell");
    }
    end = std::chrono::high_resolution_clock::now();
    double lookupTime = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Looked up " << numOrders << " orders in " << lookupTime << " ms\n";

    // Order retrieval
    start = std::chrono::high_resolution_clock::now();
    test.findBestBuyOrder();
    test.findBestSellOrder();
    end = std::chrono::high_resolution_clock::now();
    double bestOrderTime = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Best Order Retrieval Time: " << bestOrderTime << " ms\n";


    std::cout << "\nBenchmarking Completed!\n";
}