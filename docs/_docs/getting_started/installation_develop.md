---
title: Get starting
category: getting-started
description: For development installation
order: 1
layout: page
---

# 1. Prepare
* git
* cmake[^3.16]
* GCC or Clang[^std 11]
* eigen3[^3.3]
* gnuplot(for graph writing)

# 2. How to install?
## 2.1 For Windows with GCC
```ps
git clone "{{ site.github.repository_url }}.git"
cd sound_utils
cmake -B ./build -G "MinGW Makefiles"
cmake --build ./build
```
If Ctest(see below command) is successful, this library available.
```ps
ctest --test-dir ./build
```
