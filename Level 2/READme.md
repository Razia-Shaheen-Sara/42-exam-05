# 🟢 Grid Algorithms: Visual Guide

A quick-reference guide for common grid-based problems. Use this to distinguish between connectivity, optimization, and simulation logic.

---

### 🗺️ Legend
| Symbol   | Meaning         | Context |
| :------- | :------------- | :------ |
| `X` / `.`| Land / Water   | Original Map |
| `*`      | Visited / Counted | **Flood Fill** (Connectivity) |
| `n`      | Max Square Size   | **DP / BSQ** (Optimization) |
| `1` / `0`| Alive / Dead      | **Game of Life** (Simulation) |

---

### 📊 Side-by-Side Visualization

| Index | Flood Fill       | DP (BSQ)        | Game of Life      |
| :---: | :-------------- | :-------------- | :----------------|
| 0     | . * . . .       | 1 1 1 1 1       | 0 1 0 0 0        |
| 1     | * * * . .       | 1 2 2 2 2       | 1 1 1 0 0        |
| 2     | . * . X .       | 1 2 3 3 3       | 1 1 1 1 1        |
| 3     | . . . X X       | 1 2 3 4 4       | 0 1 1 1 1        |
| 4     | X . . X .       | 1 2 3 4 5       | 0 1 0 1 0        |

---

### ⚙️ Core Logic & Formulas

**Flood Fill (Connectivity)**  
- **Goal:** Count islands or fill areas  
- **Mechanism:** Spread outward from a seed point  
- **Memory Tip:** Use a visited set or modify the grid in-place  

**Dynamic Programming (Optimization)**  
- **Goal:** Find the largest square of `1`s  
- **Formula:**  
```text
dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
