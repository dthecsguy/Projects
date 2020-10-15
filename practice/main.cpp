#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> addBorder(std::vector<std::string> picture) {
    int row = picture.size() + 2;
    int col = picture[0].size() + 2;

    //sets up appropriate grid
    std::vector<std::string> b(col);

    //logic
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == 0) {
                b[i].push_back('*');
            }

            else if (i == row - 1) {
                b[i].push_back('*');
            }

            else {
                if (j == 0)
                    b[i].push_back('*');
                else if (j == col - 1)
                    b[i].push_back('*');
                else
                    //print the correct row's letters
                    b[i].push_back(picture[i - 1][j - 1]);
            }
        }
    }

    return b;
}

/*class HashTable {
    std::vector
};*/

/*bool areSimilar(std::vector<int> a, std::vector<int> b) {
    bool isPoss = false;

    int wrongSpots[2];

    if (a == b)
        return true;

    //are there two elements in wrong spot in b?
    for (int i = 0, cnt = 0; i <= b.size(); i++) {
        if (cnt == 2) {
            //if they are switched do they create the string
            int temp = b[wrongSpots[0]];
            b[wrongSpots[0]] = b[wrongSpots[1]];
            b[wrongSpots[1]] = temp;

            for (int x : b) {
                std::cout << x << ", ";
            }

            if (a == b)
                isPoss = true;
        }
        else if (b[i] != a[i] && cnt < 2 && i != b.size()) {
            wrongSpots[cnt++] = i;
        } 
    }
    
    return isPoss;
}*/

std::vector<std::vector<int>> meanGroups(std::vector<std::vector<int>> a) { // the key is [mean, indice, lowest of array]
    std::vector<std::vector<int>> b;
    bool found = false;

    //for all elements in a
    for (int i = 0; i < a.size(); i++) {
        int sum = 0;

        //Sort a[i]
        std::sort(a[i].begin(), a[i].end());

        a[i].insert(a[i].begin(), i);

        //Get mean
        //for all elements in a[i]
        for (int j = 1; j < a[i].size(); j++) {
            sum+= a[i][j];
        }

        //divide sum by size
        float mean = int(double(sum) / double(a[i].size() - 1) * 1000);

        a[i].insert(a[i].begin(), mean);

        a[i].erase(a[i].begin() + 3, a[i].end());
    }

    //Group elements on mean
    //for all elements in a
    for (int i = 0; i < a.size(); i++) {

        //if zero elements in b push back {a[i][0], a[i][1]};
        if (i == 0) {
            b.push_back(a[i]);
        }
        else {

            found = false;
            //if a[0] is found in b
            //for all elements in b
            for (int j = 0; j < b.size(); j++) {
                //if a[i]'s mean matches 
                if (b[j][0] == a[i][0]) {
                    b[j].insert(b[j].end() - 1, a[i][1]);

                    if (a[i][2] < b[j][b[j].size() - 1]) {
                        b[j][b[j].size() - 1] = a[i][2];
                    }
                    found = true;
                    break;
                }
            }

            //if not found
            if (!found) {
                b.push_back(a[i]);
            }
        }
    }

    //sort b according to b[i][b.size() - 1];
    std::sort(b.begin(), b.end(), [](std::vector<int> x, std::vector<int> y) { return x[1] < y[1]; });

    for (int i = 0; i < b.size(); i++) {
        std::cout << "[";
        b[i].erase(b[i].begin());
        b[i].erase(b[i].end() - 1);

        for (int j = 0; j < b[i].size(); j++) {
            std::cout << b[i][j] << " ";
        }
        std::cout << "]" << std::endl;
    }

    return b;
}

bool palindromeRearranging(std::string inputString) {
    std::vector<std::pair<char, bool>> found;

    if (inputString.size() <= 1)
        return true;

    //for all letters in input
    for (int i = 0; i < inputString.size(); i++) {

        bool doAdd = true;

        for (int j = 0; j < found.size(); j++) {

            //if letter is in found[j].first    
            if (found[j].first == inputString[i]) {
                found[j].second = !(found[j].second);
                doAdd = false;
            }
        }

        //if doAdd add to found as false
        if (doAdd) {
            found.push_back(std::make_pair(inputString[i], false));
        }
    }

    if (all_of(found.begin(), found.end(), [](std::pair<char, bool> x) {return x.second; }))
        return true;
    else {
        bool lucky = false;

        for (std::pair<char, bool> x : found) {
            if (x.second == false && lucky == false)
                lucky = true;

            else if (x.second == false && lucky == true) {
                lucky = false;
                break;
            }
        }

        for (std::pair<char, bool> x : found) {
            std::cout << x.second << std::endl;
        }

        return lucky;
    }
}

std::string mergeStrings(std::string s1, std::string s2) {
    std::vector<std::pair<char, int>> ps1, ps2;
    std::string b;

    if (s1.size() == 0 && s2.size() != 0)
        return s2;

    if (s2.size() == 0 && s1.size() != 0)
        return s1;

    if (s1.size() + s2.size() == 0)
        return b;

    //count the occurence of each letter in each string
    for (int i = 0; i < s1.size(); i++) {

        //if firsr iteration
        if (i == 0) {
            ps1.push_back(std::make_pair(s1[i], 1));
            continue;
        }

        //try to find pair with key
        std::vector<std::pair<char, int>>::iterator it = find_if(ps1.begin(), ps1.end(), \
            [&s1, i](std::pair<char, int> p) { return p.first == s1[i]; });

        //if found
        if (it != ps1.end()) {
            it->second++;
        }
        //else
        else {
            ps1.push_back(std::make_pair(s1[i], 1));
        }
    }

    for (std::pair<char, int> x : ps1) {
        std::cout << "( " << x.first << " , " << x.second << " )" << std::endl;
    }

    //count the occurence of each letter in each string
    for (int i = 0; i < s2.size(); i++) {

        //if firsr iteration
        if (i == 0) {
            ps2.push_back(std::make_pair(s2[i], 1));
            continue;
        }

        //try to find pair with key
        std::vector<std::pair<char, int>>::iterator it = find_if(ps2.begin(), ps2.end(), \
            [&s2, i](std::pair<char, int> p) { return p.first == s2[i]; });

        //if found
        if (it != ps2.end()) {
            it->second++;
        }
        //else
        else {
            ps2.push_back(std::make_pair(s2[i], 1));
        }
    }

    for (std::pair<char, int> x : ps2) {
        std::cout << "( " << x.first << " , " << x.second << " )" << std::endl;
    }

    int n = s1.size() + s2.size();

    //for all elements in both strings
    for (int i = 0; i < n; i++) {

        //if s1.size() == 0 and s2.size() > 0
        if (s1.size() == 0 && s2.size() > 0) {
            //add s2 to b
            b = b + s2;
            break;
        }
        //if s2.size() == 0 and s1.size() > 0
        else if (s2.size() == 0 && s1.size() > 0) {
            //add s1 to b
            b = b + s1;
            break;
        }
        //if s1[0] value is less than s2[0] value find_if(pairs.begin(), pairs.end(), [](std::pair<char, int> p){ return p.first == s1[0]})
        else if (find_if(ps1.begin(), ps1.end(), [s1](std::pair<char, int> p) { return p.first == s1[0]; })->second <
            find_if(ps2.begin(), ps2.end(), [s2](std::pair<char, int> p) { return p.first == s2[0]; })->second) {
            //add s1[0] to b
            b.push_back(s1[0]);
            s1.erase(s1.begin());
        }
        //else if s2[0] < s1[0]
        else if (find_if(ps1.begin(), ps1.end(), [s1](std::pair<char, int> p) { return p.first == s1[0]; })->second >
            find_if(ps2.begin(), ps2.end(), [s2](std::pair<char, int> p) { return p.first == s2[0]; })->second) {
            //add s2[0] to b
            b.push_back(s2[0]);
            s2.erase(s2.begin());
        }
        //else
        else {
            //if s1[0] is less than or equal to s2[0]
            if (s1[0] <= s2[0]) {
                //add s1[0] to b
                b.push_back(s1[0]);
                s1.erase(s1.begin());
            }
            //else
            else {
                //add s2[0] to b
                b.push_back(s2[0]);
                s2.erase(s2.begin());
            }
        }
    }

    return b;
}



int main() {
    
    //std::vector<std::string> b = addBorder({ "abc", "ded" });

    //bool isPoss = palindromeRearranging("zaa");

    //std::vector<std::vector<int>> b = meanGroups({ {-1, 0, 0, 0, 0}, {-1, 1}, {1}, {1, 1, 1, 0, 1}, {-1, -1, 1, 0}, {1, -1}, {0, 0}, {0, -1, 1, 0}, {1, -1, 1, 1, 0, -1, 1} });

    std::string b = mergeStrings(" cddab", "bfetrfb");

    std::cout << b;

    return 0;
}