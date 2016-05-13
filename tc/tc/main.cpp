//
//  main.cpp
//  tc
//
//  Created by Xueyong Qian on 09/06/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char * argv[])
{
    vector<bool> v{0,1,1,1,0};
    for(auto x:v)
    {
        cout << x <<" ";
    }
    return 0;
}

