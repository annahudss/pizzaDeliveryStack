# Pizza Delivery Stack System

A C++ project developed as part of university coursework, implementing a pizza delivery order management system using a linked-list-based stack.

## Overview

The system manages pizza orders using a custom stack data structure. It allows orders to be added, removed, displayed and reordered according to delivery distance.

## Features

- **Push Orders:** Add new pizza orders to the stack.
- **Pop Orders:** Remove the next order and simulate its delivery time.
- **Display Orders:** View the current orders in the stack.
- **Order Validation:** Validate pizza types and compartment IDs.
- **Distance-Based Sorting:** Reorder orders by delivery distance.
- **File Handling:** Save order information to a text file.
- **Memory Management:** Use dynamic memory allocation and a destructor to release allocated memory.

## Technologies

- C++
- Linked Lists
- Stack Data Structures
- Pointers and Dynamic Memory Allocation
- File Handling
- Exception Handling

## How to Run

Compile using a C++ compiler:

```bash
g++ pizza_delivery_stack.cpp -o pizza_delivery_stack
```

Run:

```bash
./pizza_delivery_stack
```

On Windows:

```bash
pizza_delivery_stack.exe
```

## Current Limitations

- Order information is currently hardcoded in the menu.
- Delivery is simulated rather than connected to a real delivery service.
- File logging currently records orders remaining in the stack.
- The project could be extended with interactive order entry and persistent order storage.

## Learning Outcomes

This project provided practical experience with implementing data structures, managing memory, handling files and applying object-oriented programming concepts in C++.
