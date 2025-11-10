# 🔥 DikLang Compiler (Custom Language)  
Developed by 👑 **Dikshit Rao** (MNIT Jaipur, CSE)

---

## 🚀 Overview
DikLang is a **mini-compiler project** written in **C++**, demonstrating all stages of compilation:
- Lexical Analysis
- Syntax Analysis
- Semantic Checking
- Intermediate Code Generation
- Code Optimization & Emission

---

## 📁 Folder Structure
CustomCompiler/
├── include/ → Header files (lexer, parser, semantic, optimizer)
├── src/ → C++ source files
├── test/ → Sample .dik programs
├── Makefile → Build script
└── compiler.exe

yaml
Copy code

---

## 💻 Example Program

**File:** `test/test1.dik`
```dik
let a = 5;
let b = a + 10;
if (b > 10) {
    print(b);
}
Run:

bash
Copy code
mingw32-make clean && mingw32-make
./compiler test/test1.dik
🧩 Sample Output
css
Copy code
Parsing completed successfully!
Semantic Analysis completed successfully!
Generating Intermediate Code...
Optimizing Intermediate Code...

Final Optimized Code:
t1 = 5
a = t1
b = t1 + 10
PRINT b
Compilation Successful ✅
🧠 Built With
Tool	Purpose
C++17	Core language
Makefile	Build automation
GitHub	Version control
MinGW	C++ compiler

👑 Author
Name: Dikshit Rao
Institution: MNIT Jaipur
Branch: Computer Science & Engineering