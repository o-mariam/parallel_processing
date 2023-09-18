Got it. Let's simplify the README for a single-file implementation.

---

# Parallel Kahn's Algorithm for Topological Sorting

This repository houses a parallelized version of Kahn’s algorithm for topological sorting. By leveraging the power of multi-core processors and parallel processing techniques, we aim to attain substantial speed-ups in the sorting procedure compared to the conventional serial algorithm.

---

## Features:

1. **Parallelization**: The algorithm takes advantage of running tasks in parallel to achieve faster execution.
   
2. **Task-based Paradigm**: Using OpenMP's task construct, the algorithm benefits from dynamic load balancing, which ensures efficient use of computational resources.

3. **Performance Analysis**: Speed-up achieved by the parallel algorithm is documented to give an idea about its effectiveness against the traditional serial approach.

---

## Technologies:

- **OpenMP**: An API designed for multi-platform shared-memory parallel programming in C.
  
- **C**: The entire solution is coded in the C programming language.

---

## File:

- `parallel_kahn.c`: This file contains the entire implementation of the parallelized version of Kahn’s algorithm, including utility functions and performance testing.

---

## Usage:

1. **Prerequisites**: Ensure you have a C compiler and OpenMP library installed.

2. **Compilation**: 
   ```
   gcc -fopenmp parallel_kahn.c -o parallel_kahn
   ```

3. **Execution**: 
   ```
   ./parallel_kahn
   ```

---

## Results:

After executing, the program will display the speed-ups achieved by the parallel algorithm for various input sizes. This provides an indication of the effectiveness of the parallelization.

---
