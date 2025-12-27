# Image Transformer in C++

This repository contains my work for a **C++ Object-Oriented Programming course on Coursera**.  
It implements an image transformation tool using modular, object-oriented design principles.

---

## Overview

The project demonstrates C++ OOP fundamentals such as classes, encapsulation, inheritance, and abstraction through image manipulation.  
It supports basic image operations like overlaying and blending images, with a structure designed for easy extensibility.

---

## Project Structure

```
cpp-image-transformer/
├── ImageTransform.h
├── ImageTransform.cpp
├── main.cpp
├── Makefile
├── alma.png
├── overlay.png
├── tests/
│   ├── (unit tests)
├── uiuc/
│   ├── (supporting files)
```

---

## Features

- Modular, object-oriented architecture  
- Image overlay and blending support  
- Easy to extend with new transformation classes  
- Includes test suite for validation  
- Clean separation of interface and implementation  

---

## Requirements

- **C++17** or newer  
- Standard C++ libraries  
- (No external dependencies)

---

## Build and Run

```bash
# Build the project
make

# Run the image transformer
./ImageTransformer alma.png overlay.png output.png
```

### Run Tests

```bash
cd tests
make
./run_tests
```

---

## How It Works

- The core logic is implemented in `ImageTransform.cpp` and `ImageTransform.h`.  
- `main.cpp` demonstrates how to instantiate and use transformation objects.  
- The design makes it easy to add new features like rotate, crop, or filter operations by extending the base class.

---

## Extending the Project

To add a new transformation:
1. Create a new subclass of the base transformation class.
2. Implement the transformation logic.
3. Update `main.cpp` to include and test your new transformation.

---

## Testing

- Unit tests are located in the `tests/` directory.  
- They validate transformation correctness and pixel-level accuracy.  
- Run them via `make` inside the tests folder.

---


## 🏫 Acknowledgment

This project was developed as part of the **Object-Oriented Data Structures in C++** specialization on Coursera.
