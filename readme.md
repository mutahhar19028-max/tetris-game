# 🎮 Advanced Tetris Clone — C++ + Raylib

A modern, feature-rich Tetris clone developed in C++ using [Raylib](https://www.raylib.com/). This project combines solid Object-Oriented Programming (OOP) architecture with real-time visual polish, special effects, boosters, themes, and dynamic background systems.

---

## 🧱 Core Features

### ✅ Internal Resolution
- Game renders at **1280x720** using `RenderTexture2D`.
- Maintains **aspect ratio** and centers gameplay when the window is resized or maximized.
- Adds **black bars** (letterboxing) to preserve consistency.

### ✅ Modular Block System (Aggregation)
- Blocks are handled via `Block*` pointers (e.g. `IBlock`, `TBlock`, `ShinyBlock`).
- Easily extendable with custom block types and logic.
- Each block is responsible for its shape, color, and unique behavior.

### ✅ Special Block Types
- **ShinyBlock**:
  - Shines with a glow animation for 5 seconds.
  - If locked during this glow period, it grants a **random booster**.
- **ExplodingBlock** (Planned):
  - Destroys a 3×3 grid around it when cleared.

### ✅ Booster System
- Boosters are added dynamically and stored in `BoosterManager`.
- Implemented via polymorphism using `std::shared_ptr<Booster>`.
- Types:
  - `ClearLineBooster`: Instantly clears a line.
  - `ScoreMultiplierBooster`: Temporarily multiplies score for a duration.

### ✅ Dynamic Backgrounds
- Loads a **set of 44 background images**.
- Supports **blur effects** and smooth **fade transitions**.
- Allows toggling visibility of the backgrounds.

### ✅ Themes and Animations
- Users can **switch themes** dynamically (color palettes, UI styles).
- `AnimationManager` handles visual animations tied to gameplay and menus.

### ✅ Polished UI / Menus
- Screens: Start Menu, Settings, Pause Menu, Credits, and Game Over.
- UI built using **raygui** with hover effects, sliders (e.g., for volume), and toggles.
- Smooth transitions between screens.

---

## 🎮 Controls

| Key        | Action                                  |
|------------|------------------------------------------|
| `←`        | Move block left                         |
| `→`        | Move block right                        |
| `↓`        | Soft drop (also adds score)             |
| `↑`        | Rotate block                            |
| `SPACE`    | Hard drop (instantly place block)       |
| `C`        | Cycle current game theme                |
| `A`        | Cycle next animation                    |
| `T`        | Switch to next background image         |
| `X`        | Toggle background image visibility      |
| `R`        | Reset the game                          |
| `P`        | Pause the game                          |
| `M`        | Return to main menu                     |
| `ESC`      | Exit game                               |

### 🔧 Developer Shortcuts

| Key        | Debug / Dev Tool                         |
|------------|-------------------------------------------|
| `F2`       | Level up instantly                       |
| `F3`       | Add one line to lines-cleared count      |
| `F4`       | Add `ClearLineBooster` manually          |
| `F5`       | Add `ScoreMultiplierBooster` manually    |

---

## 🛠️ Project Structure