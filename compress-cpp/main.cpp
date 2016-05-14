//
//  main.cpp
//  compress-cpp
//
//  Created by Xueyong Qian on 22/09/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <array>
#include <queue>
#include <map>

using namespace std;

constexpr int Num = 257;
constexpr int buf_size = 4096;

struct Node{
    long val;
    Node* left;
    Node* right;
    Node(long l, Node* a=nullptr, Node* b=nullptr): val{l}, left{a}, right{b}{}
    virtual ~Node(){delete left; delete right;}
    
};

struct Internal_Node:Node{
    Internal_Node(Node* a, Node* b):Node{a->val+b->val, a, b}{}
    ~Internal_Node(){}
};

struct Leaf_Node:Node{
    Leaf_Node(long v, int symb):Node{v}, symbol{symb}{}
    const int symbol;
    ~Leaf_Node(){}
};

struct Node_Cmp{
    bool operator()(Node* a, Node* b) { return a->val > b->val;}
};

void fill_table(const Node* node, const vector<bool>& v, map<int, vector<bool>>& table)
{
    if (const Leaf_Node* leaf = dynamic_cast<const Leaf_Node*>(node)) {
        table[leaf->symbol] = v;
    }
    else{
        vector<bool> vl{v};
        vl.push_back(false);
        fill_table(node->left, vl, table);
        
        vector<bool> vr{v};
        vr.push_back(true);
        fill_table(node->right, vr, table);
    }
}

size_t bool_to_int(const vector<bool>& v)
{
    size_t n = 0;
    for(auto x:v){
        n = 2 * n + x;
    }
    return n;
}

vector<bool> int_to_bool(size_t n, size_t size)
{
    vector<bool> v;
    while (n) {
        v.push_back(n & 1);
        n >>= 1;
    }
    while(v.size() < size){
        v.push_back(0);
    }
    reverse(v.begin(), v.end());
    return v;
}

void write_bit(ostream& os, const vector<bool>& v, int end = 0)
{
    static int bit_left = 8;
    static  unsigned char value = 0;
    static array<unsigned char, buf_size> buffer{};
    static int used{};
    for(auto x: v){
        value |= static_cast<int>(x);
        --bit_left;
        if (bit_left <= 0) {
            //os.put(value);
            buffer[used++] = value;
            if (used == buf_size) {
                os.write(reinterpret_cast<char*>(buffer.data()), buf_size);
                used = 0;
            }
            value = 0;
            bit_left = 8;
        }
        value <<= 1;
    }
    if (end && bit_left != 8) {
        value <<= (bit_left -1) ;
        buffer[used++] = value;
        os.write(reinterpret_cast<char*>(buffer.data()), used);
    }
}


bool get_bit(istream& is)
{
    static array<unsigned char, buf_size> buffer{};
    static unsigned char mask = 1 << 7;
    static unsigned char count{};
    static unsigned char value{};
    static int used{buf_size};
    
    if(count == 8){
        count = 0;
    }
    if(count == 0){
        if (used == buf_size) {
            is.read(reinterpret_cast<char*>( buffer.data()), buf_size);
            used = 0;
        }
        value = buffer[used++];
        ++count;
        return (value & mask) != 0;
    }
    else{
        ++count;
        value <<= 1;
        return (value & mask) != 0;
    }
}

int main(int argc, const char * argv[])
{
    cout << "Please enter input file name:\n";
    string fin;
    cin >> fin;
    cout << "Please type 1 to zip, others to unzip\n";
    int zip;
    cin >>zip;
    ifstream ifs{fin};
    
    if(zip == 1){
        array<long, Num> freq{};
        vector<unsigned char> input;
        ifs.seekg (0, ifs.end);
        input.resize(ifs.tellg());
        ifs.seekg (0, ifs.beg);
        ifs.read(reinterpret_cast<char*>(input.data()), input.size());
        for(auto x:input)
            ++freq[x];
        freq[Num-1] = 1;
        
        priority_queue<Node*, vector<Node*>, Node_Cmp> tree;
        for (int i = 0; i < Num; ++i) {
            if(freq[i])
                tree.push(new Leaf_Node{freq[i], i});
        }
        while (tree.size() > 1) {
            Node* left{tree.top()};
            tree.pop();
            Node* right{tree.top()};
            tree.pop();
            tree.push(new Internal_Node{left, right});
        }
        map<int, vector<bool>>code_table{};
        fill_table(tree.top(), vector<bool>{}, code_table);
        delete tree.top();
        
        vector<int> vc;
        for(auto x:code_table){
            vc.push_back(x.first);
        }
        sort(vc.begin(), vc.end(), [&code_table](int a, int b)
             {size_t na = code_table[a].size(); size_t nb = code_table[b].size(); return na == nb ? a < b : na < nb;});
        
        code_table[vc[0]] =vector<bool>(code_table[vc[0]].size(), 0);
        for (int i = 1; i < vc.size(); ++i) {
            code_table[vc[i]] = int_to_bool((bool_to_int(code_table[vc[i-1]]) + 1) << (code_table[vc[i]].size()-code_table[vc[i-1]].size()),code_table[vc[i]].size());
        }
        
        array<vector<bool>, Num> arr_table;
        for(auto x:code_table)
            arr_table[x.first] = x.second;
        
        ofstream ofs{"zip"};
        ofs.put(vc.size()-2);     //length of table
        ofs.put(arr_table[Num-1].size());
        for(auto x:vc){
            if (x != Num - 1) {
                ofs.put(x);
                ofs.put(arr_table[x].size());
            }
        }
        for(auto x: input){
            write_bit(ofs, arr_table[x]);
        }
        write_bit(ofs,arr_table[Num-1],1);
        ofs.close();
    }
    else{
        int len = ifs.get();
        int fake_eof = ifs.get();
        vector<pair<int, int>> vp;
        int uc{};
        for(int i = 0; i <= len; ++i){
            uc = ifs.get();
            vp.emplace_back(uc,ifs.get());
        }
        vp.emplace_back(Num-1, fake_eof);
        sort(vp.begin(), vp.end(), [](pair<int, int> a, pair<int, int> b){ return a.second == b.second ? a.first < b.first : a.second < b.second;});
        
        ofstream ofs{"unzip"};
        vector<int> length_table(vp.back().second + 1, 0);
        for(auto x:vp){
            ++length_table[x.second];
        }
        
        size_t row, first_code_on_row,accumulator,first_index_on_row;
        row = first_code_on_row = accumulator = first_index_on_row = 0;
        array<unsigned char, buf_size> buffer{};
        int used = 0;
        while(true){
            ++row;
            accumulator |= get_bit(ifs);
            first_code_on_row <<= 1;
            if(accumulator - first_code_on_row < length_table[row]){
                int symbol =vp[accumulator - first_code_on_row + first_index_on_row].first;
                if (symbol == Num -1) {
                    ofs.write(reinterpret_cast<char*> (buffer.data()), used);
                    break;
                }
                buffer[used++] = symbol;
                if (used == buf_size) {
                    ofs.write(reinterpret_cast<char*> (buffer.data()), buf_size);
                    used = 0;
                }
                row = accumulator = first_index_on_row = first_code_on_row = 0;
            }
            else{
                first_code_on_row += length_table[row];
                first_index_on_row += length_table[row];
                accumulator <<= 1;
            }
        }
        ofs.close();
    }
    ifs.close();
    return 0;
}
