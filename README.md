# 🃏 Poker Terminal Game (C)

A simple command-line poker game written in C. Play directly in your terminal while learning and exploring core concepts like game logic, structs, and memory management.

## 🎮 Features

- Terminal-based gameplay (no GUI required)
- Standard 52-card deck
- Poker hand evaluation (pair, straight, flush, etc.)
- Turn-based system
- Lightweight and fast
- Written in pure C (no external libraries)

## 🛠️ Tech Stack

- Language: C
- Compiler: GCC (or any C-compatible compiler)
- Platform: Cross-platform (Linux, macOS, Windows with MinGW)

## 🚀 Getting Started

**### 1. Clone the repository**
```bash
git clone https://github.com/your-username/poker-terminal-game.git
cd poker-terminal-game
```

**### 2. Compile the program**
If you have a single file:
```bash
gcc main.c deck.c player.c game.c utils.c -o poker
```

### 3. Run the game
```bash
./poker

## 🎲 How to play:
1. Run the program
2. Each player is dealt cards
3. Follow on-screen prompts to:
  Bet
  Check
  Fold
4. The game evaluates hands and determines the winner

## 🃏 Hand Rankings (Highest → Lowest)
1. Royal Flush
2. Straight Flush
3. Four of a Kind
4. Full House
5. Flush
6. Straight
7. Three of a Kind
8. Two Pair
9. One Pair
10. High Card

## 🎮 Controls
b → Bet
c → Check
f → Fold
q → Quit

## 📁 Project Structure

poker-terminal-game/
│── main.c
│── deck.c
│── deck.h
│── player.c
│── player.h
│── game.c
│── game.h
│── utils.c
│── utils.h
└── README.md



## 🔧 Future Improvements
Add AI opponents
Implement chip/betting system
Multiplayer support
Improve terminal UI
Add input validation and error handling

##🐛 Known Issues
No advanced betting logic (yet)
Limited input validation

## 🤝 Contributing
Contributions are welcome! Feel free to fork the repo and submit a pull request.

## 📜 License
This project is licensed under the MIT License.

## 🙌 Acknowledgments
Inspired by classic poker games
Built as a learning project for C programming
