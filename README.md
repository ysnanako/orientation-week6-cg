# orientation-week6-cg

![GitHub repo size](https://img.shields.io/github/repo-size/ysnanako/orientation-week6-cg)
![GitHub last commit](https://img.shields.io/github/last-commit/ysnanako/orientation-week6-cg)

This project is part of the **National Cheng Kung University (NCKU) - Smart Electronic Design Automation Laboratory (SEDA)** summer training program, focusing on **circuit placement optimization using Conjugate Gradient (CG) methods**.

## 📖 Table of Contents

- [Project Overview](#project-overview)
- [Input Format](#input-format)
- [Output Format](#output-format)
- [Project Structure](#project-structure)
- [CG Optimization Flow](#cg-optimization-flow)
- [Example Execution](#example-execution)
- [Generated Plots](#generated-plots)
- [Contribution Guide](#contribution-guide)
- [Contact Information](#contact-information)

## 📝 Project Overview

This project implements **Conjugate Gradient (CG) optimization** for **circuit placement** by minimizing:

\[ \min WL(x) + \lambda D(x) \]

where:
- **WL(x)** represents **wirelength** minimization (using Log-Sum-Exponential model).
- **D(x)** represents **density** minimization (using Electrostatic Force model).
- **λ (lambda)** is a tunable parameter balancing wirelength and density constraints.

### **Key Features:**
1. **Parsing circuit layout data from input files (`test.txt`).**
2. **Using CG-based optimization for placement refinement.**
3. **Calculating gradients for wirelength and density functions.**
4. **Writing final placement results to output files (`output.dpx`).**

## 📄 Input Format

The program requires a single input file (`test.txt`) which describes the placement area, components, and netlist connectivity.

📄 **Example test.txt**
```
PlacementArea: 1000 1000
Component: C1 50 50
Component: C2 60 40
Net: N1 C1 C2
...
```

## 📄 Output Format

The program generates a placement result file:
- **output.dpx** - Final placement solution, visualized as a graphical plot.

📄 **Example output.dpx**
```
COLOR gray
SR 0 0 120 120
COLOR green
SRF 10 10 60 60
COLOR cyan
SRF 80 80 140 140
...
```

## 🧰 Project Structure

```
📂 orientation-week6-cg/  
│── 📂 src/  
│   ├── main.cpp  
│   ├── parser.h  
│   ├── parser.cpp  
│   ├── alg.ch  
│   ├── alg.cpp  
│── 📄 test.txt # (ignored)  
│── 📄 output.dpx # (ignored)  
│── 🔧 Makefile  
│── 📜 README.md # This file
│── 📜 .gitignore
```

## 🔹 **CG Optimization Flow**

### **1. Read Input Files**
- Parses `test.txt` for **circuit components, placement area, and netlist data**.
- Initializes **component positions and connectivity**.

### **2. Compute Initial Wirelength and Density**
- **Wirelength Calculation**: Uses **Log-Sum-Exponential (LSE) model**.
- **Density Calculation**: Uses **Electrostatic Force model**.

### **3. Gradient Calculation & CG Update**
- Computes **gradients for WL and D**.
- Updates component positions iteratively **until convergence**.

### **4. Output Final Placement Results**
- Saves final placement in `output.dpx`.

## ⚡ **Example Execution**

```bash
make
./exe
./display.x out.dpx
```

## 🖼️ Generated Plots

Below are the generated plots from the `matlab` and `gnuplot` output:

**init**  
![initial](https://github.com/user-attachments/assets/c4436d92-b041-460a-b9a2-57a334a4cf94)  
**out**  
![out](https://github.com/user-attachments/assets/1f945a87-53a1-49f1-b3fe-5e2caf3b69e9)  

## 🤝 Contribution Guide

1. Fork this repository.
2. Create a new branch (`git checkout -b feature-xyz`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the remote branch (`git push origin feature-xyz`).
5. Submit a Pull Request.

## 📬 Contact Information

- 📧 Email: [m16131056@gs.ncku.edu.tw](mailto:m16131056@gs.ncku.edu.tw)
- 🌎 University: [National Cheng Kung University (NCKU)](https://www.ncku.edu.tw)
- 📖 Course: Summer Training Program - Conjugate Gradient Placement Optimization
