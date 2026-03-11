# CHESS_PROJECT-19
A fully functional Chess game with rule validation, complex logic, Self-made Ai mode and Stock-Fish mode.

# ♟️ C++ Console Chess Engine & Custom GUI

A complete, fully featured chess game built from scratch in standard C++ (1,700+ lines of code). This project features a custom-built console graphical interface, game state management, and AI integration, all developed without the use of external rendering libraries like SFML or Raylib.

## 🌟 Key Features

* **Custom Console Rendering:** Built a dynamic graphical interface directly in the console using `gotoRowCol` (cursor positioning). Features a live updating side-menu to track player information and game states alongside the main board.
* **Complete Chess Logic:** Fully implemented standard chess rules, move validation, and match states entirely from scratch.
* **Multiple Game Modes:** * Player vs Player
  * Player vs Custom Self-AI
  * Player vs Stockfish (Integrated with the professional Stockfish engine)
* **Game State Management:** Includes robust File I/O to **Save** and **Load** ongoing games, as well as options to Resign or Quit mid-match.

## 📸 Interface Preview
<img width="1897" height="885" alt="Menu" src="https://github.com/user-attachments/assets/99091f22-6f22-4950-b4b7-6583cccec69a" />
<img width="1918" height="1001" alt="Interface" src="https://github.com/user-attachments/assets/2b60d8f7-2d9d-49c0-8e19-963607f5ad85" />



## 💻 Tech Stack & Concepts
* **Language:** C++
* **Environment:** Visual Studio
* **Core Concepts Used:** Advanced Windows Console Buffer manipulation (`gotoRowCol`), File I/O for save states, Object-Oriented Programming, and External Process Communication (Stockfish API).

## 🚀 How to Run Locally

1. Clone this repository to your local machine.
2. Download the official `stockfish` executable and place it in the project directory (required for Stockfish AI mode).
3. Open the `BSAi-25019_Chess-Phase_5.sln` file in **Visual Studio**.
4. Build and run the project directly through Visual Studio.
