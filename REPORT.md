# Custom Language Compiler (DikLang)

## 1️⃣ Project Overview
This project is a **custom compiler** for a simple high-level language named **DikLang**, designed and implemented by **Dikshit Rao** as part of the Compiler Design course.

The compiler performs all major compilation phases:
1. **Lexical Analysis** – Tokenization of source code  
2. **Syntax Analysis** – Grammar validation  
3. **Semantic Analysis** – Logical consistency (e.g., variable declarations)  
4. **Intermediate Code Generation** – Produces 3-address intermediate code  
5. **Optimization & Code Emission** – Simplifies IR and generates optimized output

---

## 2️⃣ Project Motivation
The goal was to understand **how a compiler works internally**, step by step — from reading a program to producing executable-like code — and implement it practically using **C++**.

---

## 3️⃣ Tools & Technologies
| Component | Tool/Language |
|------------|---------------|
| Programming Language | C++17 |
| Build System | Makefile |
| Version Control | Git + GitHub |
| IDE | Visual Studio Code |
| Compiler | MinGW (g++) |
| OS | Windows 10 |

---

## 4️⃣ Architecture
     ┌────────────────────┐
     │   Source Program   │
     └────────┬───────────┘
              ↓
     ┌────────────────────┐
     │  Lexical Analyzer  │
     │ (Token Generation) │
     └────────┬───────────┘
              ↓
     ┌────────────────────┐
     │   Syntax Analyzer  │
     │ (Grammar Checking) │
     └────────┬───────────┘
              ↓
     ┌────────────────────┐
     │ Semantic Analyzer  │
     │ (Variable Checking)│
     └────────┬───────────┘
              ↓
     ┌────────────────────┐
     │ Intermediate Code  │
     │    Generation      │
     └────────┬───────────┘
              ↓
     ┌────────────────────┐
     │   Optimizer + IR   │
     │   → Code Emitter   │
     └────────────────────┘

---

## 5️⃣ Language Features (DikLang)
✅ `let` keyword for variable declaration  
✅ `print()` for output  
✅ Arithmetic operations: `+`, `-`, `*`, `/`  
✅ Conditional: `if (...) { ... }`  
✅ End of statement: `;`

---

## 6️⃣ Sample Program
```dik
let a = 5;
let b = a + 10;
if (b > 10) {
    print(b);
}

## 7️⃣ Generated Intermediate Code
t1 = 5
a = t1
t2 = a + 10
b = t2
PRINT b

8️⃣ Learning Outcomes

Understood all compiler phases

Implemented a working compiler in C++

Gained experience with Makefiles, Git, and version control

Learned optimization techniques like constant folding and redundancy elimination

9️⃣ Future Enhancements

Add data type checking (int, float)

Implement loops (while/for)

Generate real Assembly or C output

Improve expression tree-based parsing

🔟 Author

Name: Dikshit Rao
Institute: MNIT Jaipur
Department: Computer Science and Engineering
Project: DikLang Compiler (Custom Language)