# 🟢 Grid Algorithms: Visual Guide

A quick-reference guide for common grid-based problems. Use this to distinguish between connectivity, optimization, and simulation logic.

---

| Symbol   | Meaning           | Context      |
| :------- | :-------------    | :------      |
| `X` / `.`| Land / Water      | Original Map |
| `*`      | Visited / Counted | **Flood Fill** (Connectivity) |
| `n`      | Max Square Size   | **DP / BSQ** (largest square) |
| `1` / `0`| Alive / Dead      | **Game of Life** (change by neibr)|

---

### 📊 Side-by-Side Visualization

| Original Map | largest isld(FF)| DP (BSQ)        | Game of Life    |
| :----------- | :-------------- | :-------------- | :-------------- |
| . X . . .    | . * . . .       | 1 1 1 1 1       | 0 1 0 0 0      |
| X X X . .    | * * * . .       | 1 2 2 2 2       | 1 1 1 0 0      |
| . X . X .    | . * . X .       | 1 2 3 3 3       | 1 1 1 1 1      |
| . . . X X    | . . . X X       | 1 2 3 4 4       | 0 1 1 1 1      |
| X . . X .    | X . . X .       | 1 2 3 4 5       | 0 1 0 1 0      |

---

### ⚙️ Core Logic & Formulas

**Flood Fill (Connectivity)**  
- **Goal:** find largest connected area
- **Mechanism:** Spread outward from a seed point  
- **Memory Tip:** Use a visited indicator 

**Dynamic Programming (Optimization)**  
- **Goal:** Find the largest square of `1`s  
- **Formula:**  
dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])

**Simulation (State Change)**
- **Goal:** Update the grid based on the previous state.
- **Formula:**  Every cell checks its 8 neighbors.
- **Tip:**Never update in-place. Use a temporary grid to store new values, then swap
