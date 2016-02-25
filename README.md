#####A bytecode interpreter for learning purposes

Having some fun trying to write the fastest bytecode interpreter I can. The original version was written in C# as an experiment but has now been optimized as much as I can. (It also includes an optimizer which optimizes the instructions, it can be commented back in to see better performance.) The C++ version is not performing as well as I would like as I am very new to C++.

Run the C++ version with:

    cd "C++ Version"
    g++ *.cpp -o main.exe -std=c++11 -O3
    main.exe
