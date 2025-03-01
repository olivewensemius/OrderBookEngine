#!/bin/bash
echo "Running Benchmark..."
./build/OrderBook benchmark > benchmark_results.txt
echo "Benchmark complete. Results saved to benchmark_results.txt"
