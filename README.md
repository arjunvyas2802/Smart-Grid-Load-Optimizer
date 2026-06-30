# Real-Time Smart Grid Load Optimizer

A high-performance command-line C++ simulation of an automated **Priority-Based Load Shedding** framework designed to maintain power grid stability under high-stress overload conditions. 

## ⚡ The Problem & The Core Mechanism
During massive peak-demand events (e.g., heatwaves), total power draw can quickly exceed a substation's maximum capacity, threatening a catastrophic city-wide blackout. 

This engine prevents grid collapse by implementing a **Greedy Optimization Strategy**:
1. It ingests real-time power grid telemetry datasets.
2. In the event of an overload, it leverages an $O(N \log N)$ custom sorting algorithm to rearrange grid sectors based on strict utility importance (`Critical` > `Industrial` > `Residential`).
3. If two sectors share the same priority level, it applies a **load magnitude tie-breaker**, prioritizing the removal of the heaviest power drains first.
4. It executes an $O(N)$ reverse-greedy elimination sweep to systematically drop low-priority nodes until total current load falls below `maxCapacity`.

## 🛠️ Technology Stack & C++ Optimizations
- **Language:** C++11 / Modern C++
- **Data Layout:** Contiguous memory sequences (`std::vector`) to maintain hardware cache locality and maximize sequential data traversal speeds.
- **Type Safety:** Strongly typed scoped enums (`enum class priorityLevel`) to protect system parameters from implicit type narrowing or logical runtime corruption.

## 🚀 How to Run the Project
You can build, test, and run this entire project instantly using an online C++ compiler like **OnlineGDB**:
1. Copy the entire contents of `main.cpp`.
2. Paste it into the editor at [OnlineGDB](https://www.onlinegdb.com/).
3. Click **Run**.
