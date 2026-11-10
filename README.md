# Parking Slot Management System

A Data Structures mini project written in C, with a separate HTML/CSS dashboard mockup.

## Data structure used
**Singly Linked List**

Each vehicle is stored in a dynamically allocated node containing:
- Vehicle registration number
- Assigned parking slot number
- Pointer to the next vehicle node

## Features
1. Park a vehicle and assign the first available slot.
2. Display all parked vehicles.
3. Remove a vehicle by registration number.
4. Display available and occupied slot counts.
5. Prevent duplicate registrations.
6. Display a full-parking message when all 10 slots are occupied.

## Compile and run (GCC)
```bash
gcc parking.c -o parking
./parking
```
On Windows:
```bash
gcc parking.c -o parking.exe
parking.exe
```

## Frontend
Open `index.html` in a browser. The frontend is a static HTML/CSS dashboard prototype. Its sample values are illustrative; it is not connected to the C console program. Connecting the browser UI to the C program would require an additional backend/API layer.

## Complexity analysis
Let `n` be the number of parked vehicles.

| Operation | Time complexity | Reason |
|---|---:|---|
| Park vehicle | O(n) | Check duplicates and traverse to the list tail |
| Remove vehicle | O(n) | Search for the registration number |
| Display vehicles | O(n) | Traverse and print every node |
| Display availability | O(1) | Uses the occupied counter |
| Find first available slot | O(n + S) | Traverse list and scan S = 10 slot positions |

Space complexity: **O(n)** for the linked-list nodes, with a fixed-size O(S) temporary slot array when finding an available slot.

## Learning outcomes
- Implement a singly linked list using structures and pointers.
- Perform insertion, deletion, and traversal.
- Use dynamic memory allocation (`malloc` and `free`).
- Analyze time and space complexity.
- Apply a data structure to a real-world parking problem.
# DS_Mini_Project
# DS_Mini_Project
