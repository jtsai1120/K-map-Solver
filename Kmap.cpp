// 蔡承希 E24126170 

#include <vector>
#include <unordered_set>
#include <map>
#include <string>
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

struct Pair_Hash {
    template <class T1, class T2>
    size_t operator() (const pair<T1, T2> &v) const {
        return hash<T1>()(v.first) ^ hash<T2>()(v.second) << 1;    
    }
};

struct PI {
    int size_r;
    int size_c;
    int row;
    int col;
};

struct KmapSolution {
    int numVar;
    char **kmap;
    vector<string> primes;
    vector<string> essentials;
    vector<string> minimumSop;
};

string PI_to_Literals(int numVar, PI pi) {
    string tmp = "";
    switch(numVar) {
        case 2:
            if (pi.size_r==1 && pi.size_c==1) { // 1x1 Essential Prime Implicants
                tmp += (pi.col==0)? "a\'":"a";
                tmp += (pi.row==0)? "b\'":"b";
            }
            if (pi.size_r==1 && pi.size_c==2) { // 1x2 Essential Prime Implicants
                tmp += (pi.row==0)? "b\'":"b";
            }
            if (pi.size_r==2 && pi.size_c==1) { // 2x1 Essential Prime Implicants
                tmp += (pi.col==0)? "a\'":"a";
            }
            break;
        case 3:
            if (pi.size_r==1 && pi.size_c==1) { // 1x1 Essential Prime Implicants
                tmp += (pi.col<2)? "a\'":"a";
                tmp += (pi.col==1 || pi.col==2)? "b":"b\'";
                tmp += (pi.row==0)? "c\'":"c";
            }
            if (pi.size_r==1 && pi.size_c==2) { // 1x2 Essential Prime Implicants
                if (pi.col == 0) tmp += "a\'"; // don't care b
                if (pi.col == 1) tmp += "b"; // don't care a
                if (pi.col == 2) tmp += "a"; // don't care b
                if (pi.col == 3) tmp += "b\'"; // don't care a
                tmp += (pi.row==0)? "c\'":"c";
            }
            if (pi.size_r==2 && pi.size_c==1) { // 2x1 Essential Prime Implicants
                if (pi.col == 0) tmp += "a\'b\'"; 
                if (pi.col == 1) tmp += "a\'b"; 
                if (pi.col == 2) tmp += "ab"; 
                if (pi.col == 3) tmp += "ab\'"; 
            }
            if (pi.size_r==1 && pi.size_c==4) { // 1x4 Essential Prime Implicants
                tmp += (pi.row==0)? "c\'":"c";
            }
            if (pi.size_r==2 && pi.size_c==2) { // 2x2 Essential Prime Implicants
                if (pi.col == 0) tmp += "a\'"; 
                if (pi.col == 1) tmp += "b"; 
                if (pi.col == 2) tmp += "a"; 
                if (pi.col == 3) tmp += "b\'"; 
            }
            break;
        case 4:
            if (pi.size_r==1 && pi.size_c==1) { // 1x1 Essential Prime Implicants
                tmp += (pi.col<2)? "a\'":"a";
                tmp += (pi.col==1 || pi.col==2)? "b":"b\'";
                tmp += (pi.row<2)? "c\'":"c";
                tmp += (pi.row==1 || pi.row==2)? "d":"d\'"; 
            }
            if (pi.size_r==1 && pi.size_c==2) { // 1x2 Essential Prime Implicants
                if (pi.col == 0) tmp += "a\'"; // don't care b
                if (pi.col == 1) tmp += "b"; // don't care a
                if (pi.col == 2) tmp += "a"; // don't care b
                if (pi.col == 3) tmp += "b\'"; // don't care a
                if (pi.row == 0) tmp += "c\'d\'";
                if (pi.row == 1) tmp += "c\'d";
                if (pi.row == 2) tmp += "cd";
                if (pi.row == 3) tmp += "cd\'";
            }
            if (pi.size_r==2 && pi.size_c==1) { // 2x1 Essential Prime Implicants
                if (pi.col == 0) tmp += "a\'b\'"; 
                if (pi.col == 1) tmp += "a\'b"; 
                if (pi.col == 2) tmp += "ab"; 
                if (pi.col == 3) tmp += "ab\'"; 
                if (pi.row == 0) tmp += "c\'";
                if (pi.row == 1) tmp += "d";
                if (pi.row == 2) tmp += "c";
                if (pi.row == 3) tmp += "d\'";
            }
            if (pi.size_r==1 && pi.size_c==4) { // 1x4 Essential Prime Implicants
                if (pi.row == 0) tmp += "c\'d\'"; // don't care ab
                if (pi.row == 1) tmp += "c\'d"; // don't care ab
                if (pi.row == 2) tmp += "cd"; // don't care ab
                if (pi.row == 3) tmp += "cd\'"; // don't care ab
            }
            if (pi.size_r==4 && pi.size_c==1) { // 4x1 Essential Prime Implicants
                if (pi.col == 0) tmp += "a\'b\'"; 
                if (pi.col == 1) tmp += "a\'b"; 
                if (pi.col == 2) tmp += "ab"; 
                if (pi.col == 3) tmp += "ab\'"; 
            }
            if (pi.size_r==2 && pi.size_c==2) { // 2x2 Essential Prime Implicants
                if (pi.col == 0) tmp += "a\'"; 
                if (pi.col == 1) tmp += "b"; 
                if (pi.col == 2) tmp += "a"; 
                if (pi.col == 3) tmp += "b\'"; 
                if (pi.row == 0) tmp += "c\'";
                if (pi.row == 1) tmp += "d";
                if (pi.row == 2) tmp += "c";
                if (pi.row == 3) tmp += "d\'";
            }
            if (pi.size_r==2 && pi.size_c==4) { // 2x4 Essential Prime Implicants
                if (pi.row == 0) tmp += "c\'";
                if (pi.row == 1) tmp += "d";
                if (pi.row == 2) tmp += "c";
                if (pi.row == 3) tmp += "d\'";
            }
            if (pi.size_r==4 && pi.size_c==2) { // 4x2 Essential Prime Implicants
                if (pi.col == 0) tmp += "a\'";
                if (pi.col == 1) tmp += "b";
                if (pi.col == 2) tmp += "a";
                if (pi.col == 3) tmp += "b\'";
            }
    }
    return tmp;
};

map<int, vector<int>> mn2 = { 
    {0, {0, 0}}, {2, {0, 1}}, 
    {1, {1, 0}}, {3, {1, 1}},
};
map<vector<int>, int> mn2_reverse = { 
    {{0, 0}, 0}, {{0, 1}, 2}, 
    {{1, 0}, 1}, {{1, 1}, 3},
};
map<int, vector<int>> mn3 = { 
    {0, {0, 0}}, {2, {0, 1}}, {6, {0, 2}}, {4, {0, 3}}, 
    {1, {1, 0}}, {3, {1, 1}}, {7, {1, 2}}, {5, {1, 3}},
};
map<vector<int>, int> mn3_reverse = { 
    {{0, 0}, 0}, {{0, 1}, 2}, {{0, 2}, 6}, {{0, 3}, 4}, 
    {{1, 0}, 1}, {{1, 1}, 3}, {{1, 2}, 7}, {{1, 3}, 5},
};
map<int, vector<int>> mn4 = { 
    {0, {0, 0}}, {4, {0, 1}}, {12, {0, 2}}, {8, {0, 3}}, 
    {1, {1, 0}}, {5, {1, 1}}, {13, {1, 2}}, {9, {1, 3}}, 
    {3, {2, 0}}, {7, {2, 1}}, {15, {2, 2}}, {11, {2, 3}}, 
    {2, {3, 0}}, {6, {3, 1}}, {14, {3, 2}}, {10, {3, 3}}, 
};
map<vector<int>, int> mn4_reverse = { 
    {{0, 0}, 0}, {{0, 1}, 4}, {{0, 2}, 12}, {{0, 3}, 8}, 
    {{1, 0}, 1}, {{1, 1}, 5}, {{1, 2}, 13}, {{1, 3}, 9}, 
    {{2, 0}, 3}, {{2, 1}, 7}, {{2, 2}, 15}, {{2, 3}, 11}, 
    {{3, 0}, 2}, {{3, 1}, 6}, {{3, 2}, 14}, {{3, 3}, 10}, 
};

KmapSolution *solveKmap(int numVar, const vector<int> minterms, const vector<int> dontcares) {
    char **kmap;
    vector<string> primes;
    vector<string> essentials;
    vector<string> minimumSop;

    unordered_set<pair<int,int>, Pair_Hash> _1x1;
    unordered_set<pair<int,int>, Pair_Hash> _1x2;
    unordered_set<pair<int,int>, Pair_Hash> _2x1;
    unordered_set<pair<int,int>, Pair_Hash> _1x4;
    unordered_set<pair<int,int>, Pair_Hash> _4x1;  
    unordered_set<pair<int,int>, Pair_Hash> _2x2;
    unordered_set<pair<int,int>, Pair_Hash> _2x4;
    unordered_set<pair<int,int>, Pair_Hash> _4x2;

    unordered_set<pair<int,int>, Pair_Hash> _1x1_to_delete;
    unordered_set<pair<int,int>, Pair_Hash> _1x2_to_delete;
    unordered_set<pair<int,int>, Pair_Hash> _2x1_to_delete;
    unordered_set<pair<int,int>, Pair_Hash> _1x4_to_delete;
    unordered_set<pair<int,int>, Pair_Hash> _4x1_to_delete;
    unordered_set<pair<int,int>, Pair_Hash> _2x2_to_delete;

    vector<PI> primes_non_literals;
    vector<vector<vector<PI>>> find_EPI(4, vector<vector<PI>>(4));
    vector<vector<bool>> covered(4, vector<bool>(4, 0));
    vector<PI> essentials_non_literals;
    vector<PI> minimumSop_non_literals;  

    switch(numVar) {
        case 2:
            // edge cases
            if (minterms.size() + dontcares.size() == pow(2, numVar)) { // all 1
                kmap = new char *[2];
                for(int r = 0; r < 2; r++) {
                    kmap[r] = new char[2];
                    for(int c = 0; c < 2; c++) {
                        kmap[r][c] = '1';
                    }
                }
                for (int i : dontcares) kmap[mn2[i][0]][mn2[i][1]] = 'x';
                primes.push_back("1");
                essentials.push_back("1");
                minimumSop.push_back("1");
                KmapSolution *sol = new KmapSolution;
                sol->numVar = numVar;
                sol->kmap = kmap;
                sol->primes = primes;
                sol->essentials = essentials;
                sol->minimumSop = minimumSop;
                return sol;
            }
            if (minterms.size() == 0) { // all 0
                kmap = new char *[2];
                for(int r = 0; r < 2; r++) {
                    kmap[r] = new char [2];
                    for(int c = 0; c < 2; c++) {
                        kmap[r][c] = '0';
                    }
                }
                for (int i : dontcares) kmap[mn2[i][0]][mn2[i][1]] = 'x';
                //primes.push_back("0");
                //essentials.push_back("0");
                minimumSop.push_back("0");
                KmapSolution *sol = new KmapSolution;
                sol->numVar = numVar;
                sol->kmap = kmap;
                sol->primes = primes;
                sol->essentials = essentials;
                sol->minimumSop = minimumSop;
                return sol;
            }
            
            // Put 0, 1, x into Kmap
                kmap = new char *[2];
                for (int r = 0; r < 2; r++) {
                    kmap[r] = new char [2];
                    for (int c = 0; c < 2; c++) 
                        kmap[r][c] = '0';
                } 
                
                for (int i : minterms) 
                    kmap[mn2[i][0]][mn2[i][1]] = '1';
                
                for (int i : dontcares) {
                    kmap[mn2[i][0]][mn2[i][1]] = 'x';
                }
            
            // Find all Prime Implicants
                // Size 1 :
                    // 1x1 Implicants
                    for (int i : minterms) _1x1.insert(make_pair(mn2[i][0], mn2[i][1])); 
                    for (int i : dontcares) _1x1.insert(make_pair(mn2[i][0], mn2[i][1]));

                // Size 2 :
                    // 1x2 Implicants
                    for (pair<int,int> p : _1x1) {
                        if (p.second == 0 && (kmap[p.first][p.second+1]=='1' || kmap[p.first][p.second+1]=='x')) {
                            _1x2.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair(p.first, p.second+1));
                        }
                    }
                    
                    // 2x1 Implicants
                    for (pair<int,int> p : _1x1) {
                        if (p.first == 0 && (kmap[p.first+1][p.second]=='1' || kmap[p.first+1][p.second]=='x')) {
                            _2x1.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair(p.first+1, p.second));
                        }
                    }

                    // delete 1x1 non-Prime Implicants
                    for (pair<int,int> p : _1x1_to_delete) _1x1.erase(p);

            // Put all Prime Implicants into a vector
            
            // Size 1 :
                // 1x1 Prime Implicants
                for (pair<int,int> p : _1x1) primes_non_literals.push_back({1, 1, p.first, p.second});
            
            // Size 2 :
                // 1x2 Prime Implicants
                for (pair<int,int> p : _1x2) primes_non_literals.push_back({1, 2, p.first, p.second});

                // 2x1 Prime Implicants
                for (pair<int,int> p : _2x1) primes_non_literals.push_back({2, 1, p.first, p.second});

            // check if the Prime Implicants is all made of don't care terms
            for (vector<PI>::iterator it = primes_non_literals.begin(); it != primes_non_literals.end(); it++) {
                bool is_contain_1 = 0;
                PI pi = *it;
                for (int r = 0; r < pi.size_r; r++) {
                    for (int c = 0; c < pi.size_c; c++) {
                        vector<int> tmp = {(pi.row+r)%2, (pi.col+c)%2};
                        if (find(minterms.begin(), minterms.end(), mn2_reverse[tmp]) != minterms.end())
                            is_contain_1 = 1;
                    }
                }
                if (!is_contain_1) {
                    primes_non_literals.erase(it);
                    it--;
                }
            }
            
            for (PI pi : primes_non_literals) primes.push_back(PI_to_Literals(2, pi));

            // Put all Prime Implicants into a 2D vector to record which Prime Implicant covers the specific minterm 
            
            // Size 1 :
                // 1x1 Prime Implicants
                for (pair<int,int> p : _1x1) {
                    find_EPI[p.first][p.second].push_back({1, 1, p.first, p.second});
                }
            
            // Size 2 :
                // 1x2 Prime Implicants
                for (pair<int,int> p : _1x2) {
                    find_EPI[p.first][p.second].push_back({1, 2, p.first, p.second});
                    find_EPI[p.first][(p.second+1)%2].push_back({1, 2, p.first, p.second});
                }

                // 2x1 Prime Implicants
                for (pair<int,int> p : _2x1) {
                    find_EPI[p.first][p.second].push_back({2, 1, p.first, p.second});
                    find_EPI[(p.first+1)%2][p.second].push_back({2, 1, p.first, p.second});
                }
            
            // Using that 2D vector to find Essential Prime Implicants
            for (int i : minterms) {
                int r = mn2[i][0];
                int c = mn2[i][1];
                if (find_EPI[r][c].size()==1 && !covered[r][c]) {
                    PI tmp_PI = find_EPI[r][c][0];
                    essentials_non_literals.push_back(tmp_PI);
                    if (tmp_PI.size_r==1 && tmp_PI.size_c==1) // 1x1
                        covered[tmp_PI.row][tmp_PI.col] = 1;
                    if (tmp_PI.size_r==1 && tmp_PI.size_c==2) { // 1x2
                        covered[tmp_PI.row][tmp_PI.col] = 1;
                        covered[tmp_PI.row][(tmp_PI.col+1)%2] = 1;
                    }
                    if (tmp_PI.size_r==2 && tmp_PI.size_c==1) { // 2x1
                        covered[tmp_PI.row][tmp_PI.col] = 1;
                        covered[(tmp_PI.row+1)%2][tmp_PI.col] = 1;
                    }
                }
            }

            // Transfer Essential Prime Implicants into literals and put them into "essentials"
            for (PI pi : essentials_non_literals) {
                string essential_literals = PI_to_Literals(2, pi);
                essentials.push_back(essential_literals);
                minimumSop.push_back(essential_literals);
            }

            // Find if need to add other Prime Implicant(s) to cover the remaining minterm(s) 
            for (int i : minterms) {
                if (!covered[mn2[i][0]][mn2[i][1]]) {
                    int max_size = 0;
                    PI max_size_pi;
                    for (PI pi : find_EPI[mn2[i][0]][mn2[i][1]]) {
                        if (pi.size_r * pi.size_c >= max_size) {
                            max_size = pi.size_r * pi.size_c;
                            max_size_pi = pi;
                        }
                    }
                    covered[mn2[i][0]][mn2[i][1]] = 1;
                    bool is_contained = 0;
                    for (PI be_checked_pi : minimumSop_non_literals) {
                        if (be_checked_pi.size_r == max_size_pi.size_r && be_checked_pi.size_c == max_size_pi.size_c && be_checked_pi.row == max_size_pi.row && be_checked_pi.col == max_size_pi.col) 
                            is_contained = 1;
                    }
                    if (!is_contained) minimumSop_non_literals.push_back(max_size_pi);
                } 
            }
            
            for (PI pi : minimumSop_non_literals) 
                minimumSop.push_back(PI_to_Literals(2, pi));

            break;
        case 3:
            // edge cases
            if (minterms.size() + dontcares.size() == pow(2, numVar)) { // all 1
                kmap = new char *[2];
                for(int r = 0; r < 2; r++) {
                    kmap[r] = new char [4];
                    for(int c = 0; c < 4; c++) {
                        kmap[r][c] = '1';
                    }
                }
                for (int i : dontcares) kmap[mn3[i][0]][mn3[i][1]] = 'x';
                primes.push_back("1");
                essentials.push_back("1");
                minimumSop.push_back("1");
                KmapSolution *sol = new KmapSolution;
                sol->numVar = numVar;
                sol->kmap = kmap;
                sol->primes = primes;
                sol->essentials = essentials;
                sol->minimumSop = minimumSop;
                return sol;
            }
            if (minterms.size() == 0) { // all 0
                kmap = new char *[2];
                for(int r = 0; r < 2; r++) {
                    kmap[r] = new char [4];
                    for(int c = 0; c < 4; c++) {
                        kmap[r][c] = '0';
                    }
                }
                for (int i : dontcares) kmap[mn3[i][0]][mn3[i][1]] = 'x';
                //primes.push_back("0");
                //essentials.push_back("0");
                minimumSop.push_back("0");
                KmapSolution *sol = new KmapSolution;
                sol->numVar = numVar;
                sol->kmap = kmap;
                sol->primes = primes;
                sol->essentials = essentials;
                sol->minimumSop = minimumSop;
                return sol;
            }
            
            // Put 0, 1, x into Kmap
                kmap = new char *[2];
                for (int r = 0; r < 2; r++) {
                    kmap[r] = new char [4];
                    for (int c = 0; c < 4; c++) 
                        kmap[r][c] = '0';
                } 
                
                for (int i : minterms) 
                    kmap[mn3[i][0]][mn3[i][1]] = '1';
                
                for (int i : dontcares) {
                    kmap[mn3[i][0]][mn3[i][1]] = 'x';
                }

            // Find all Prime Implicants
                // Size 1 :
                    // 1x1 Implicants
                    for (int i : minterms) _1x1.insert(make_pair(mn3[i][0], mn3[i][1])); 
                    for (int i : dontcares) _1x1.insert(make_pair(mn3[i][0], mn3[i][1]));
                
                // Size 2 :
                    // 1x2 Implicants
                    for (pair<int,int> p : _1x1) {
                        if (kmap[p.first][(p.second+1)%4]=='1' || kmap[p.first][(p.second+1)%4]=='x') {
                            _1x2.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair(p.first, (p.second+1)%4));
                        }
                    }
                    
                    // 2x1 Implicants
                    for (pair<int,int> p : _1x1) {
                        if (p.first == 0 && (kmap[p.first+1][p.second]=='1' || kmap[p.first+1][p.second]=='x')) {
                            _2x1.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair(p.first+1, p.second));
                        }
                    }

                    // delete 1x1 non-Prime Implicants
                    for (pair<int,int> p : _1x1_to_delete) _1x1.erase(p);

                // Size 4 :
                    // 1x4 Implicants
                    for (pair<int,int> p : _1x2) {
                        if (p.second==0 && _1x2.count(make_pair(p.first, 2))) {
                            _1x4.insert(make_pair(p.first, p.second));
                            _1x2_to_delete.insert(make_pair(p.first, 0));
                            _1x2_to_delete.insert(make_pair(p.first, 1)); // 若該元素不存在，unordered_set 仍不會出現 error
                            _1x2_to_delete.insert(make_pair(p.first, 2));
                            _1x2_to_delete.insert(make_pair(p.first, 3)); // 若該元素不存在，unordered_set 仍不會出現 error
                        }
                    }

                    // 2x2 Implicants
                    for (int c = 0; c < 4; c++) {
                        if (_1x2.count(make_pair(0,c)) && _1x2.count(make_pair(1,c))) {
                            _2x2.insert(make_pair(0,c));
                            _1x2_to_delete.insert(make_pair(0, c));
                            _1x2_to_delete.insert(make_pair(1, c));
                            _2x1_to_delete.insert(make_pair(0, c));
                            _2x1_to_delete.insert(make_pair(0, (c+1)%4));
                        }
                    }

                    //delete 1x2 non-Prime Implicants
                    for (pair<int,int> p : _1x2_to_delete) _1x2.erase(p);

                    //delete 2x1 non-Prime Implicants
                    for (pair<int,int> p : _2x1_to_delete) _2x1.erase(p);

            // Put all Prime Implicants into a vector

                // Size 1 :
                    // 1x1 Prime Implicants
                    for (pair<int,int> p : _1x1) primes_non_literals.push_back({1, 1, p.first, p.second});
                
                // Size 2 :
                    // 1x2 Prime Implicants
                    for (pair<int,int> p : _1x2) primes_non_literals.push_back({1, 2, p.first, p.second});

                    // 2x1 Prime Implicants
                    for (pair<int,int> p : _2x1) primes_non_literals.push_back({2, 1, p.first, p.second});

                // Size 4 :
                    // 1x4 Prime Implicants
                    for (pair<int,int> p : _1x4) primes_non_literals.push_back({1, 4, p.first, p.second});

                    // 2x2 Prime Implicants
                    for (pair<int,int> p : _2x2) primes_non_literals.push_back({2, 2, p.first, p.second});

                // check if the Prime Implicants is all made of don't care terms
                for (vector<PI>::iterator it = primes_non_literals.begin(); it != primes_non_literals.end(); it++) {
                    bool is_contain_1 = 0;
                    PI pi = *it;
                    for (int r = 0; r < pi.size_r; r++) {
                        for (int c = 0; c < pi.size_c; c++) {
                            vector<int> tmp = {(pi.row+r)%2, (pi.col+c)%4};
                            if (find(minterms.begin(), minterms.end(), mn3_reverse[tmp]) != minterms.end())
                                is_contain_1 = 1;
                        }
                    }
                    if (!is_contain_1) {
                        primes_non_literals.erase(it);
                        it--;
                    }
                    
                }
                
                for (PI pi : primes_non_literals) primes.push_back(PI_to_Literals(3, pi));

            // Put all Prime Implicants into a 2D vector to record which Prime Implicant covers the specific minterm 
                // Size 1 :
                    // 1x1 Prime Implicants
                    for (pair<int,int> p : _1x1) {
                        find_EPI[p.first][p.second].push_back({1, 1, p.first, p.second});
                    }
                
                // Size 2 :
                    // 1x2 Prime Implicants
                    for (pair<int,int> p : _1x2) {
                        find_EPI[p.first][p.second].push_back({1, 2, p.first, p.second});
                        find_EPI[p.first][(p.second+1)%4].push_back({1, 2, p.first, p.second});
                    }

                    // 2x1 Prime Implicants
                    for (pair<int,int> p : _2x1) {
                        find_EPI[p.first][p.second].push_back({2, 1, p.first, p.second});
                        find_EPI[p.first+1][p.second].push_back({2, 1, p.first, p.second});
                    }
                
                // Size 4 :
                    // 1x4 Prime Implicants
                    for (pair<int,int> p : _1x4) {
                        for (int c = 0; c < 4; c++) {
                            find_EPI[p.first][c].push_back({1, 4, p.first, p.second});
                        }
                    }
                
                    // 2x2 Prime Implicants
                    for (pair<int,int> p : _2x2) {
                        find_EPI[p.first][p.second].push_back({2, 2, p.first, p.second});
                        find_EPI[p.first+1][p.second].push_back({2, 2, p.first, p.second});
                        find_EPI[p.first][(p.second+1)%4].push_back({2, 2, p.first, p.second});
                        find_EPI[p.first+1][(p.second+1)%4].push_back({2, 2, p.first, p.second});
                    }
            
            // Using that 2D vector to find Essential Prime Implicants
            for (int i : minterms) {
                int r = mn3[i][0];
                int c = mn3[i][1];
                if (find_EPI[r][c].size()==1 && !covered[r][c]) {
                    PI tmp_PI = find_EPI[r][c][0];
                    essentials_non_literals.push_back(tmp_PI);
                    if (tmp_PI.size_r==1 && tmp_PI.size_c==1) // 1x1
                        covered[tmp_PI.row][tmp_PI.col] = 1;
                    if (tmp_PI.size_r==1 && tmp_PI.size_c==2) { // 1x2
                        covered[tmp_PI.row][tmp_PI.col] = 1;
                        covered[tmp_PI.row][(tmp_PI.col+1)%4] = 1;
                    }
                    if (tmp_PI.size_r==2 && tmp_PI.size_c==1) { // 2x1
                        covered[tmp_PI.row][tmp_PI.col] = 1;
                        covered[tmp_PI.row+1][tmp_PI.col] = 1;
                    }
                    if (tmp_PI.size_r==1 && tmp_PI.size_c==4) { // 1x4
                        for (int c = 0; c < 4; c++) {
                            covered[tmp_PI.row][c] = 1;
                        }
                    }
                    if (tmp_PI.size_r==2 && tmp_PI.size_c==2) { // 2x2
                        covered[tmp_PI.row][tmp_PI.col] = 1;
                        covered[tmp_PI.row+1][tmp_PI.col] = 1;
                        covered[tmp_PI.row][(tmp_PI.col+1)%4] = 1;
                        covered[tmp_PI.row+1][(tmp_PI.col+1)%4] = 1;
                    }
                }
            }
            
            // Transfer Essential Prime Implicants into literals and put them into "essentials"
            for (PI pi : essentials_non_literals) {
                string essential_literals = PI_to_Literals(3, pi);
                essentials.push_back(essential_literals);
                minimumSop.push_back(essential_literals);
            }

            // Find if need to add other Prime Implicant(s) to cover the remaining minterm(s)
            for (int i : minterms) {
                if (!covered[mn3[i][0]][mn3[i][1]]) {
                    int max_size = 0;
                    PI max_size_pi;
                    for (PI pi : find_EPI[mn3[i][0]][mn3[i][1]]) {
                        if (pi.size_r * pi.size_c >= max_size) {
                            max_size = pi.size_r * pi.size_c;
                            max_size_pi = pi;
                        }
                    }
                    covered[mn3[i][0]][mn3[i][1]] = 1;
                    bool is_contained = 0;
                    for (PI be_checked_pi : minimumSop_non_literals) {
                        if (be_checked_pi.size_r == max_size_pi.size_r && be_checked_pi.size_c == max_size_pi.size_c && be_checked_pi.row == max_size_pi.row && be_checked_pi.col == max_size_pi.col) 
                            is_contained = 1;
                    }
                    if (!is_contained) minimumSop_non_literals.push_back(max_size_pi);
                } 
            }
            
            for (PI pi : minimumSop_non_literals) 
                minimumSop.push_back(PI_to_Literals(3, pi));
            
            break;
        case 4:
            // Put 0, 1, x into Kmap
            kmap = new char *[4];
            for (int r = 0; r < 4; r++) {
                kmap[r] = new char [4];
                for (int c = 0; c < 4; c++) 
                    kmap[r][c] = '0';
            } 
            
            for (int i : minterms) 
                kmap[mn4[i][0]][mn4[i][1]] = '1';
            
            for (int i : dontcares) {
                kmap[mn4[i][0]][mn4[i][1]] = 'x';
            }

            // edge cases
            if (minterms.size() + dontcares.size() == pow(2, numVar)) { // all 1
                primes.push_back("1");
                essentials.push_back("1");
                minimumSop.push_back("1");
                KmapSolution *sol = new KmapSolution;
                sol->numVar = numVar;
                sol->kmap = kmap;
                sol->primes = primes;
                sol->essentials = essentials;
                sol->minimumSop = minimumSop;
                return sol;
            }
            if (minterms.size() == 0) { // all 0
                minimumSop.push_back("0");
                KmapSolution *sol = new KmapSolution;
                sol->numVar = numVar;
                sol->kmap = kmap;
                sol->primes = primes;
                sol->essentials = essentials;
                sol->minimumSop = minimumSop;
                return sol;
            }

            // Find all Prime Implicants
                // Size 1 :
                    // 1x1 Implicants
                    for (int i : minterms) _1x1.insert(make_pair(mn4[i][0], mn4[i][1])); 
                    for (int i : dontcares) _1x1.insert(make_pair(mn4[i][0], mn4[i][1]));
                
                // Size 2 :
                    // 1x2 Implicants
                    for (pair<int,int> p : _1x1) {
                        if (kmap[p.first][(p.second+1)%4]=='1' || kmap[p.first][(p.second+1)%4]=='x') {
                            _1x2.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair(p.first, (p.second+1)%4));
                        }
                    }
                    
                    // 2x1 Implicants
                    for (pair<int,int> p : _1x1) {
                        if (kmap[(p.first+1)%4][p.second]=='1' || kmap[(p.first+1)%4][p.second]=='x') {
                            _2x1.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair(p.first, p.second));
                            _1x1_to_delete.insert(make_pair((p.first+1)%4, p.second));
                        }
                    }

                    // delete 1x1 non-Prime Implicants
                    for (pair<int,int> p : _1x1_to_delete) _1x1.erase(p);

                // Size 4 :
                    // 1x4 Implicants
                    for (pair<int,int> p : _1x2) {
                        if (p.second==0 && _1x2.count(make_pair(p.first, 2))) {
                            _1x4.insert(make_pair(p.first, p.second));
                            _1x2_to_delete.insert(make_pair(p.first, 0));
                            _1x2_to_delete.insert(make_pair(p.first, 1)); // 若該元素不存在，unordered_set 仍不會出現 error
                            _1x2_to_delete.insert(make_pair(p.first, 2));
                            _1x2_to_delete.insert(make_pair(p.first, 3)); // 若該元素不存在，unordered_set 仍不會出現 error
                        }
                    }

                    // 4x1 Implicants
                    for (pair<int,int> p : _2x1) {
                        if (p.first==0 && _2x1.count(make_pair(2, p.second))) {
                            _4x1.insert(make_pair(p.first, p.second));
                            _2x1_to_delete.insert(make_pair(0, p.second));
                            _2x1_to_delete.insert(make_pair(1, p.second)); // 若該元素不存在，unordered_set 仍不會出現 error
                            _2x1_to_delete.insert(make_pair(2, p.second));
                            _2x1_to_delete.insert(make_pair(3, p.second)); // 若該元素不存在，unordered_set 仍不會出現 error
                        }
                    }

                    // 2x2 Implicants
                    for (int r = 0; r < 4; r++) {
                        for (int c = 0; c < 4; c++) {
                            if (_1x2.count(make_pair(r,c)) && _1x2.count(make_pair((r+1)%4, c))) {
                                _2x2.insert(make_pair(r,c));
                                _1x2_to_delete.insert(make_pair(r, c));
                                _1x2_to_delete.insert(make_pair((r+1)%4, c));
                                _2x1_to_delete.insert(make_pair(r, c));
                                _2x1_to_delete.insert(make_pair(r, (c+1)%4));
                            }
                        }
                    }

                    //delete 1x2 non-Prime Implicants
                    for (pair<int,int> p : _1x2_to_delete) _1x2.erase(p);

                    //delete 2x1 non-Prime Implicants
                    for (pair<int,int> p : _2x1_to_delete) _2x1.erase(p);
                
                // Size 8 :
                    // 2x4 Implicants
                    for (int r = 0; r < 4; r++) {
                        if (_1x4.count(make_pair(r, 0)) && _1x4.count(make_pair((r+1)%4, 0))) {
                            _2x4.insert(make_pair(r, 0));
                            _1x4_to_delete.insert(make_pair(r, 0));
                            _1x4_to_delete.insert(make_pair((r+1)%4, 0));
                            _2x2_to_delete.insert(make_pair(r, 0));
                            _2x2_to_delete.insert(make_pair(r, 1));
                            _2x2_to_delete.insert(make_pair(r, 2));
                            _2x2_to_delete.insert(make_pair(r, 3));
                        }
                    }

                    // delete 1x4 non-Prime Implicants
                    for (pair<int,int> p : _1x4_to_delete) _1x4.erase(p);

                    // 4x2 Implicants
                    for (int c = 0; c < 4; c++) {
                        if (_4x1.count(make_pair(0, c)) && _4x1.count(make_pair(0, (c+1)%4))) {
                            _4x2.insert(make_pair(0, c));
                            _4x1_to_delete.insert(make_pair(0, c));
                            _4x1_to_delete.insert(make_pair(0, (c+1)%4));
                            _2x2_to_delete.insert(make_pair(0, c));
                            _2x2_to_delete.insert(make_pair(1, c));
                            _2x2_to_delete.insert(make_pair(2, c));
                            _2x2_to_delete.insert(make_pair(3, c));
                        }
                    }

                    // delete 4x1 non-Prime Implicants
                    for (pair<int,int> p : _4x1_to_delete) _4x1.erase(p);

                    // delete 2x2 non-Prime Implicants
                    for (pair<int,int> p : _2x2_to_delete) _2x2.erase(p);

        // Put all Prime Implicants into a vector

            // Size 1 :
                // 1x1 Prime Implicants
                for (pair<int,int> p : _1x1) primes_non_literals.push_back({1, 1, p.first, p.second});
            
            // Size 2 :
                // 1x2 Prime Implicants
                for (pair<int,int> p : _1x2) primes_non_literals.push_back({1, 2, p.first, p.second});

                // 2x1 Prime Implicants
                for (pair<int,int> p : _2x1) primes_non_literals.push_back({2, 1, p.first, p.second});

            // Size 4 :
                // 1x4 Prime Implicants
                for (pair<int,int> p : _1x4) primes_non_literals.push_back({1, 4, p.first, p.second});

                // 4x1 Prime Implicants
                for (pair<int,int> p : _4x1) primes_non_literals.push_back({4, 1, p.first, p.second});

                // 2x2 Prime Implicants
                for (pair<int,int> p : _2x2) primes_non_literals.push_back({2, 2, p.first, p.second});

            // Size 8 :
                // 2x4 Prime Implicants
                for (pair<int,int> p : _2x4) primes_non_literals.push_back({2, 4, p.first, p.second});

                // 4x2 Prime Implicants
                for (pair<int,int> p : _4x2) primes_non_literals.push_back({4, 2, p.first, p.second});

            // check if the Prime Implicants is all made of don't care terms
            for (vector<PI>::iterator it = primes_non_literals.begin(); it != primes_non_literals.end(); it++) {
                bool is_contain_1 = 0;
                PI pi = *it;
                for (int r = 0; r < pi.size_r; r++) {
                    for (int c = 0; c < pi.size_c; c++) {
                        vector<int> tmp = {(pi.row+r)%4, (pi.col+c)%4};
                        if (find(minterms.begin(), minterms.end(), mn4_reverse[tmp]) != minterms.end())
                            is_contain_1 = 1;
                    }
                }
                if (!is_contain_1) {
                    primes_non_literals.erase(it);
                    it--;
                }
            }
            
            for (PI pi : primes_non_literals) primes.push_back(PI_to_Literals(4, pi));

        // Put all Prime Implicants into a 2D vector to record which Prime Implicant covers the specific minterm 
            // Size 1 :
                // 1x1 Prime Implicants
                for (pair<int,int> p : _1x1) {
                    find_EPI[p.first][p.second].push_back({1, 1, p.first, p.second});
                }
            
            // Size 2 :
                // 1x2 Prime Implicants
                for (pair<int,int> p : _1x2) {
                    find_EPI[p.first][p.second].push_back({1, 2, p.first, p.second});
                    find_EPI[p.first][(p.second+1)%4].push_back({1, 2, p.first, p.second});
                }

                // 2x1 Prime Implicants
                for (pair<int,int> p : _2x1) {
                    find_EPI[p.first][p.second].push_back({2, 1, p.first, p.second});
                    find_EPI[(p.first+1)%4][p.second].push_back({2, 1, p.first, p.second});
                }
            
            // Size 4 :
                // 1x4 Prime Implicants
                for (pair<int,int> p : _1x4) {
                    for (int c = 0; c < 4; c++) {
                        find_EPI[p.first][c].push_back({1, 4, p.first, p.second});
                    }
                }

                // 4x1 Prime Implicants
                for (pair<int,int> p : _4x1) {
                    for (int r = 0; r < 4; r++) {
                        find_EPI[r][p.second].push_back({4, 1, p.first, p.second});
                    }
                }
            
                // 2x2 Prime Implicants
                for (pair<int,int> p : _2x2) {
                    find_EPI[p.first][p.second].push_back({2, 2, p.first, p.second});
                    find_EPI[(p.first+1)%4][p.second].push_back({2, 2, p.first, p.second});
                    find_EPI[p.first][(p.second+1)%4].push_back({2, 2, p.first, p.second});
                    find_EPI[(p.first+1)%4][(p.second+1)%4].push_back({2, 2, p.first, p.second});
                }

            // Size 8 :
                // 2x4 Prime Implicants
                for (pair<int,int> p : _2x4) {
                    for (int c = 0; c < 4; c++) {
                        find_EPI[p.first][c].push_back({2, 4, p.first, p.second});
                        find_EPI[(p.first+1)%4][c].push_back({2, 4, p.first, p.second});
                    }
                }

                // 4x2 Prime Implicants
                for (pair<int,int> p : _4x2) {
                    for (int r = 0; r < 4; r++) {
                        find_EPI[r][p.second].push_back({4, 2, p.first, p.second});
                        find_EPI[r][(p.second+1)%4].push_back({4, 2, p.first, p.second});
                    }
                }
        
        // Using that 2D vector to find Essential Prime Implicants
        for (int i : minterms) {
            int r = mn4[i][0];
            int c = mn4[i][1];
            if (find_EPI[r][c].size()==1 && !covered[r][c]) {
                PI tmp_PI = find_EPI[r][c][0];
                essentials_non_literals.push_back(tmp_PI);
                if (tmp_PI.size_r==1 && tmp_PI.size_c==1) // 1x1
                    covered[tmp_PI.row][tmp_PI.col] = 1;
                if (tmp_PI.size_r==1 && tmp_PI.size_c==2) { // 1x2
                    covered[tmp_PI.row][tmp_PI.col] = 1;
                    covered[tmp_PI.row][(tmp_PI.col+1)%4] = 1;
                }
                if (tmp_PI.size_r==2 && tmp_PI.size_c==1) { // 2x1
                    covered[tmp_PI.row][tmp_PI.col] = 1;
                    covered[(tmp_PI.row+1)%4][tmp_PI.col] = 1;
                }
                if (tmp_PI.size_r==1 && tmp_PI.size_c==4) { // 1x4
                    for (int c = 0; c < 4; c++) {
                        covered[tmp_PI.row][c] = 1;
                    }
                }
                if (tmp_PI.size_r==4 && tmp_PI.size_c==1) { // 4x1
                    for (int r = 0; r < 4; r++) {
                        covered[r][tmp_PI.col] = 1;
                    }
                }
                if (tmp_PI.size_r==2 && tmp_PI.size_c==2) { // 2x2
                    covered[tmp_PI.row][tmp_PI.col] = 1;
                    covered[(tmp_PI.row+1)%4][tmp_PI.col] = 1;
                    covered[tmp_PI.row][(tmp_PI.col+1)%4] = 1;
                    covered[(tmp_PI.row+1)%4][(tmp_PI.col+1)%4] = 1;
                }
                if (tmp_PI.size_r==2 && tmp_PI.size_c==4) { // 2x4
                    for (int c = 0; c < 4; c++) {
                        covered[tmp_PI.row][c] = 1;
                        covered[(tmp_PI.row+1)%4][c] = 1;
                    }
                }
                if (tmp_PI.size_r==4 && tmp_PI.size_c==2) { // 4x2
                    for (int r = 0; r < 4; r++) {
                        covered[r][tmp_PI.col] = 1;
                        covered[r][(tmp_PI.col+1)%4] = 1;
                    }
                }
            }
        }
        
        // Transfer Essential Prime Implicants into literals and put them into "essentials"
        for (PI pi : essentials_non_literals) {
            string essential_literals = PI_to_Literals(4, pi);
            essentials.push_back(essential_literals);
            minimumSop.push_back(essential_literals);
        }

        // Find if need to add other Prime Implicant(s) to cover the remaining minterm(s)
        for (int i : minterms) {
            if (!covered[mn4[i][0]][mn4[i][1]]) {
                int max_size = 0;
                PI max_size_pi;
                for (PI pi : find_EPI[mn4[i][0]][mn4[i][1]]) {
                    if (pi.size_r * pi.size_c >= max_size) {
                        max_size = pi.size_r * pi.size_c;
                        max_size_pi = pi;
                    }
                }
                covered[mn4[i][0]][mn4[i][1]] = 1;
                bool is_contained = 0;
                for (PI be_checked_pi : minimumSop_non_literals) {
                    if (be_checked_pi.size_r == max_size_pi.size_r && be_checked_pi.size_c == max_size_pi.size_c && be_checked_pi.row == max_size_pi.row && be_checked_pi.col == max_size_pi.col) 
                        is_contained = 1;
                }
                if (!is_contained) minimumSop_non_literals.push_back(max_size_pi);
            } 
        }
        
        for (PI pi : minimumSop_non_literals) 
            minimumSop.push_back(PI_to_Literals(4, pi));
        
        break;
    }

    KmapSolution *sol = new KmapSolution;
    sol->numVar = numVar;
    sol->kmap = kmap;
    sol->primes = primes;
    sol->essentials = essentials;
    sol->minimumSop = minimumSop;
    return sol;
}

void printKmapSolution(KmapSolution *sol) {
    int nRow, nCol;
    switch (sol->numVar) {
    case 2:
        nRow = 2; nCol = 2;
        break;
    case 3:
        nRow = 2; nCol = 4;
        break;
    case 4:
        nRow = 4; nCol = 4;
        break;
    }

    cout << "K-map:\n";
    for (int i = 0; i < nRow; ++i) {
        for (int j = 0; j < nCol; ++j)
            cout << sol->kmap[i][j] << " ";
        cout << endl;
    }   

    cout << "Prime implicants: ";
    for (int i = 0; i < sol->primes.size(); ++i) {
        cout << sol->primes[i];
        if (i != sol->primes.size() - 1) cout << ", ";
    }
    cout << endl;
    

    cout << "Essential prime implicants: ";
    for (int i = 0; i < sol->essentials.size(); ++i) {
        cout << sol->essentials[i];
        if (i != sol->essentials.size() - 1) cout << ", ";
    }
    cout << endl;
    
    cout << "Minimum SOP: ";
    for (int i = 0; i < sol->minimumSop.size(); ++i) {
        cout << sol->minimumSop[i];
        if (i != sol->minimumSop.size() - 1) cout << " + ";
    }
    cout << endl;
    
}

int main() {
    int numVar = 4;
    vector<int> minterms = {0,1,2,3,4,5,8,9,10,11,12,13,14,15}; 
    vector<int> dontcares = {6, 7};
    KmapSolution *sol = solveKmap(numVar, minterms, dontcares);
    printKmapSolution(sol);
    return 0;
}

