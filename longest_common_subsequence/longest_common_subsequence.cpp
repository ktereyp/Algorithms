#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <cassert>
#include <chrono>
#include <ctime>


using namespace std;

int diff(vector<string> &result, vector<string> &left, vector<string>::iterator i_left, vector<string> &right, vector<string>::iterator i_right) {
    if (left.begin() >i_left || right.begin() > i_right) {
        return 0;
    }
    cout << "diff 1:" << i_left-left.begin() << ", " << i_right - right.begin() << endl;
    string l = *i_left;
    string r = *i_right;
    if (l.compare(r) == 0){
        result.insert(result.begin(), l); 
        return 1+diff(result, left, i_left-1, right, i_right-1);
    }else{
        int ll = diff(result, left, i_left, right, i_right-1);
        int lr = diff(result, left, i_left-1, right, i_right);
        if (ll >=lr){
            return ll;
        }else{
            return lr;
        }
    }
}

int i = 0;
int diff(vector<string> &result, map<int, pair<int, int> > &mem, vector<string> &left, vector<string>::iterator i_left, vector<string> &right, vector<string>::iterator i_right) {
    if (left.begin() >i_left || right.begin() > i_right) {
        return 0;
    }
    int l_index =  i_left - left.begin();
    int r_index = i_right - right.begin() ;
    auto last = mem.find(l_index);
    if(last != mem.end()) {
        if(mem[l_index].first == r_index){
            return mem[l_index].second;
        }
    }
    cout << "[size]:" << i++ << endl;
    
    string l = *i_left;
    string r = *i_right;
    if (l.compare(r) == 0){
        result.insert(result.begin(), l); 
        int r = 1+diff(result, mem,left, i_left-1, right, i_right-1);
        mem[l_index] = pair<int, int>(r_index, r);
        return r;
    }else{
        int ll = diff(result,mem, left, i_left, right, i_right-1);
        int lr = diff(result,mem, left, i_left-1, right, i_right);
        if (ll >=lr){
            mem[l_index] = pair<int, int>(r_index, ll);
            return ll;
        }else{
            mem[l_index] = pair<int, int>(r_index, lr);
            return lr;
        }
    }
}

int main(int argc, char **argv){
    if (argc != 3) {
        cerr << "need to file"  << endl;       
        exit(1);
    }
    string left_file(*(argv+1));
    string right_file(*(argv+2));
    ifstream left_in(left_file);
    ifstream right_in(right_file);
    if (!left_in || !right_in) {
        cerr << "open file err" << endl;
        exit(2);
    }
    vector<string> left;
    vector<string>right;
    
    string line;
    while(getline(left_in, line)) {
        left.push_back(line);
    }
    while(getline(right_in, line)) {
        right.push_back(line);
    }
    left_in.close();
    right_in.close();
    cout << "left file: " << left.size() << " lines, right file: " << right.size() << " lines" << endl;

    cout << &left << ","  << &right<< endl;

    vector<string> result;
    map<int, pair<int, int> > mem;
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    //int n = diff(result, left, left.end()-1, right,right.end()-1);
    end = chrono::system_clock::now();
    cout << "diff 1 use time: " << (chrono::duration<double>(end-start)).count() << endl;

    start = chrono::system_clock::now();
    int n2 = diff(result, mem, left, left.end()-1, right,right.end()-1);
    end = chrono::system_clock::now();
    cout << "diff 2 use time: " << (chrono::duration<double>(end-start)).count() << endl;
    //assert( n2 == n );
    cout << "common line : " << n2 << " lines:" << endl;
    /*
    for(vector<string>::iterator iter = result.begin(); iter != result.end();iter++) {
        cout << *iter << endl;
    }
    */

    return 0;
}
