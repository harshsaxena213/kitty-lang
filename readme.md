# 🐱 kitty-lang

`kitty-lang` is a small, experimental, "just-for-fun" programming language project, currently **under development**.  
The goal of this repository is *not* to bring any groundbreaking features to the table — instead, it exists as a playground to **learn language design**, **parsing/tokenization**, and **assembly generation** in C++.

---

## 🚧 Project Status

- **Work In Progress** (very early stage)
- Basic tokenizer and assembler output support
- No full parser or interpreter yet
- Intended for self-learning and exploration of compiler construction concepts

---

## ✨ Features (so far)
- **Tokenizer** (`tokenization.hpp`):
  - Recognizes `tail` keyword
  - Supports integer literals
  - Statement terminator symbol: `@`
- **Assembly Converter** (`asmconv.hpp`):
  - Generates basic NASM-style `_start` entry code for the tokens
- **Simple CLI** (`main.cpp`):
  - Reads `.kitty` source file and converts it into `out.asm`

---

## 🔧 Building

You need:
- C++17 or newer compiler
- CMake 3.20 or later
- NASM (if you want to assemble and run the output)

Steps:
```
  git clone https://github.com/harshsaxena213/kitty-lang.git
  cd kitty-lang
  cmake --build ./build
```

```
  ./build/meow ./source.kitty
```
This will:
1. Tokenize your `.kitty` code
2. Generate the corresponding NASM assembly in `./asm/out.asm`

---

**Breakdown:**
- `123@` → integer literal `123`, statement ends with `@`
- `tail` → special keyword meaning **end of program**; signals assembler to finish code output.

---

## 🐱 The `tail` Keyword

In `kitty-lang`:
- Functions as a minimal **explicit program terminator**
- Similar to `end`, `return`, or `exit` in other languages
- Currently has **no complex runtime behavior**, it’s just a marker in the tokenizer & assembly generator.

---

## 🔤 Syntax Rules

- **Statement Terminator:**  
  Every statement must end with `@` (similar to `;` in C++/Java)
- **Keywords:**  
  `tail` is currently the only keyword
- **Literals:**  
  Only integer literals are supported as of now
- **No Variables / Functions / Loops yet** — coming in future experiments

---

## 📂 Project Structure
```
kitty-lang/
├── src/
│ ├── main.cpp
│ ├── headers/
│ │ ├── tokenization.hpp
│ │ ├── asmconv.hpp
├── asm/ # Generated assembly output
├── CMakeLists.txt
```
---

## 🎯 Development Goals
This project is designed for:

- Having fun building something from scratch

---

## ⚠️ Disclaimer
This is **not a stable or production-ready language**.  
The syntax, implementation, and features may change at any time, and the project might contain bugs or incomplete functionality.

---

## 📬 Contributing
Since this repository is a personal learning project, suggestions are welcome, but please keep in mind that the design goal is **educational exploration over feature completeness**.

---

Made by with ❤️ for fun and learning.


