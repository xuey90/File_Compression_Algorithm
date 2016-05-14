//
//  main.cpp
//  array
//
//  Created by Xueyong Qian on 25/07/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <iostream>
#include <array>
using namespace std;

struct Point{
    int x, y;
};
int main(int argc, const char * argv[]) {
    // insert code here...
    using Array = array<Point, 2>;
    Array p {{1, 2}, {3, 4}};
    return 0;
}
