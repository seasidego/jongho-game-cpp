# Clash Royale

## Navigation

### 🔍 Key Functions

#### 1. `nav()`
* **Role**: The main entry point invoked by external systems such as unit controllers.
* **Workflow**:
  1. Converts pixel-based world coordinates (`currentPos`, `destPos`) into grid-based tile coordinates (`currentTile`, `destTile`).
  2. Invokes the recursive pathfinding function `navPart()` to compute the optimal tile route.
  3. Transforms the computed tile paths back into executable pixel coordinates (`toPos()`) before returning the final vector.

#### 2. `navPart()`
A recursive function that explores all traversable adjacent tiles from the current position to the destination and evaluates the **shortest path**.
1. **Tracking & Base Case**: 
   * Appends the `currentTile` to the current path history (`route`).
   * If `currentTile` matches `destTile`, it indicates successful arrival and returns the accumulated route immediately.
2. **8-Way Neighbor Scanning**:
   * Scans 8 neighboring tiles (including diagonals) centered around the current tile.
   * **Filtering Rules**: A tile is skipped if it fulfills any of the following conditions:
     * It is the current tile itself (offset `0, 0`).
     * It has already been visited in the current path history (prevents infinite backtracking loops).
     * It falls outside the boundaries of the grid map.
     * It is blocked by an obstacle or non-walkable tile (`!canCross()`).
3. **Recursive Exploration & Path Selection**:
   * Recursively triggers `navPart()` for all valid neighboring tiles stored in `needCheckTile`.
   * Evaluates all successfully reached paths within `allRoute` and extracts the optimal route that features the **minimum vector size** (shortest length).

---

### ⚠️ Technical Notes & Optimization
* **Memory Copy Overhead**: The implementation passes `std::vector<Vector2> route` by value through recursion and aggregates all generated paths into `allRoute`. For larger maps, this can trigger significant memory allocations and performance drops.
* **Future Work**: It is highly recommended to refactor this logic into an **A* Search Algorithm** or **BFS (Breadth-First Search)** for optimized real-time pathfinding as the game scale increases.
