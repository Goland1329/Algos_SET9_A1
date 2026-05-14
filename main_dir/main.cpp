#include <bits/stdc++.h>
#include <chrono>
#include <utility>
#include <iomanip>

using namespace std;

long long char_comps = 0;

bool compareStd(string s1, string s2) {
    bool b;
    int k = 0;
    
    while(true) {
        if (k >= min(s1.length(), s2.length())) {
            char_comps++;
            if (s1.length() < s2.length()) {
                b = true;
            } else {
                b = false;
            }
            break;
        }
        
        char_comps++;
        
        if (s1[k] == s2[k]) {
            ++k;
            continue;
        }
        else if (s1[k] < s2[k]) {
            b = true;
            break;
        }
        else {
            b = false;
            break;
        }
    }
    
    return b;
}

void stdMergeSort(vector<string>& vec1, int l, int r) {
    int avg = (r + l) / 2;
    if (r - l < 1) return;
    stdMergeSort(vec1, l, avg);
    stdMergeSort(vec1, avg + 1, r);
    
    vector<string> vec_temp;
    
    int left_p = l;
    int right_p = avg + 1;
    
    while (left_p <= avg && right_p <= r) {
        if (compareStd(vec1[right_p], vec1[left_p])) {
            vec_temp.push_back(vec1[right_p++]);
        }
        else {
            vec_temp.push_back(vec1[left_p++]);
        }
    }
    
    while (left_p <= avg) {
        vec_temp.push_back(vec1[left_p++]);
    }
    while (right_p <= r) {
        vec_temp.push_back(vec1[right_p++]);
    }
    
    for (int i = 0; i < r - l + 1; ++i) {
        vec1[i + l] = vec_temp[i];
    }
}

void stdQuickSort(vector<string>& vec1) {
    if (vec1.size() < 2) return; 
    
    string pivot = vec1[0];
    
    vector<string> lesser;
    vector<string> equal;
    vector<string> greater;
    
    int k = 0;
    
    for (string i : vec1) {
        if (compareStd(i, pivot)) {
            lesser.push_back(i);
        }
        else if (compareStd(pivot, i)) {
            greater.push_back(i);
        }
        else {
            equal.push_back(i);
        }
    }
    
    stdQuickSort(lesser);
    stdQuickSort(greater);
    
    for (string i : lesser) vec1[k++] = i;
    for (string i : equal) vec1[k++] = i;
    for (string i : greater) vec1[k++] = i;
}

pair<bool, int> lcpCompare(string s1, string s2) {
    bool b;
    int k = 0;
    
    while(true) {
        if (k >= min(s1.length(), s2.length())) {
            b = false;
            break;
        }
        
        char_comps++; 
        
        if (s1[k] == s2[k]) {
            ++k;
            continue;
        }
        else if (s1[k] < s2[k]) {
            b = true;
            break;
        }
        else {
            b = false;
            break;
        }
    }
    
    return {b, k};
}
 
void mergeSort(vector<pair<string, int>>& vec1, int l, int r) {
    int avg = (r + l) / 2;
    if (r - l < 1) return;
    mergeSort(vec1, l, avg);
    mergeSort(vec1, avg + 1, r);
    
    vector<pair<string, int>> vec_temp;
    
    int left_p = l;
    int right_p = avg + 1;
    
    while (left_p <= avg && right_p <= r) {
        if (vec1[left_p].second > vec1[right_p].second) {
            vec_temp.push_back(vec1[left_p++]);
        }
        else if (vec1[left_p].second < vec1[right_p].second) {
            vec_temp.push_back(vec1[right_p++]);
        }
        else {
            pair<bool, int> res = lcpCompare(vec1[left_p].first, vec1[right_p].first);
            if (res.first) {
                vec_temp.push_back(vec1[left_p++]);
                vec1[right_p].second = res.second;
            }
            else {
                vec_temp.push_back(vec1[right_p++]);
                vec1[left_p].second = res.second;
            }
        }
    }
    
    while (left_p <= avg) {
        vec_temp.push_back(vec1[left_p++]);
    }
    while (right_p <= r) {
        vec_temp.push_back(vec1[right_p++]);
    }
    
    for (int i = 0; i < r - l + 1; ++i) {
        vec1[i + l] = vec_temp[i];
    }
}

void quickSort(vector<string>& vec1, int level) {
    if (vec1.size() < 2) return; 
    
    char pivot = vec1[0][level];
    
    vector<string> lesser;
    vector<string> equal;
    vector<string> greater;
    
    int k = 0;
    
    for (string i : vec1) {
        if (i.length() <= level) vec1[k++] = i;
        else {
            char_comps++; 
            if (i[level] < pivot) lesser.push_back(i);
            else if (i[level] == pivot) equal.push_back(i);
            else greater.push_back(i);
        }
    }
    
    quickSort(lesser, level);
    quickSort(equal, level + 1);
    quickSort(greater, level);
    
    for (string i : lesser) vec1[k++] = i;
    for (string i : equal) vec1[k++] = i;
    for (string i : greater) vec1[k++] = i;
}

void radixSort(vector<string>& vec1, int level) {
    if (vec1.size() < 2) return;
    
    int left = 0;
    int right = vec1.size() - 1;
    
    vector<vector<string>> vec_res(128);
    
    for (int i = 0; i < right - left + 1; ++i) {
        if (vec1[left + i].length() < level + 1) {
            swap(vec1[left], vec1[i]);
            ++left;   
        } else {
            char_comps++;
            vec_res[vec1[left + i][level]].push_back(vec1[left + i]);
        }
    }
    
    for (int i = 0; i < 128; ++i){
        radixSort(vec_res[i], level + 1);
    }
    
    for (auto i : vec_res) {
        for (string s : i) vec1[left++] = s;
    }
}

void radixQuickSort(vector<string>& vec1, int level) {
    if (vec1.size() < 2) return;
    
    if (vec1.size() < 74) {
        quickSort(vec1, level);
        return;
    }
    
    int left = 0;
    int right = vec1.size() - 1;
    
    vector<vector<string>> vec_res(128);
    
    for (int i = 0; i < right - left + 1; ++i) {
        if (vec1[left + i].length() < level + 1) {
            swap(vec1[left], vec1[i]);
            ++left;   
        } else {
            char_comps++;
            vec_res[vec1[left + i][level]].push_back(vec1[left + i]);
        }
    }
    
    for (int i = 0; i < 128; ++i){
        radixQuickSort(vec_res[i], level + 1);
    }
    
    for (auto i : vec_res) {
        for (string s : i) vec1[left++] = s;
    }
}

class StringGenerator {
private:
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$:;^&*()-."; 
    mt19937 rng;

    string generateRandomString() {
        uniform_int_distribution<int> len_dist(10, 200);
        uniform_int_distribution<int> char_dist(0, ALPHABET.size() - 1);
        int len = len_dist(rng);
        string res = "";
        for (int i = 0; i < len; ++i) {
            res += ALPHABET[char_dist(rng)];
        }
        return res;
    }

public:
    vector<string> base_random;
    vector<string> base_reversed;
    vector<string> base_almost;

    StringGenerator() {
        rng.seed(42);
        int MAX_SIZE = 3000;
        
        base_random.reserve(MAX_SIZE);
        for (int i = 0; i < MAX_SIZE; ++i) {
            base_random.push_back(generateRandomString());
        }

        base_reversed = base_random;
        sort(base_reversed.begin(), base_reversed.end(), greater<string>());

        base_almost = base_random;
        sort(base_almost.begin(), base_almost.end());
        
        uniform_int_distribution<int> idx_dist(0, MAX_SIZE - 1);
        int swaps = MAX_SIZE * 0.05; 
        for(int i = 0; i < swaps; ++i) {
            swap(base_almost[idx_dist(rng)], base_almost[idx_dist(rng)]);
        }
    }

    vector<string> getArray(int type, int size) {
        if (type == 0) return vector<string>(base_random.begin(), base_random.begin() + size);
        if (type == 1) return vector<string>(base_reversed.begin(), base_reversed.begin() + size);
        return vector<string>(base_almost.begin(), base_almost.begin() + size);
    }
};


int utf8_length(const string& str) {
    int len = 0;
    for (char c : str) {
        if ((c & 0xC0) != 0x80) len++;
    }
    return len;
}

string padRight(string str, int width) {
    int len = utf8_length(str);
    if (width > len) {
        return str + string(width - len, ' ');
    }
    return str;
}


class StringSortTester {
private:
    StringGenerator generator;

    template <typename Func>
    double measureTime(Func sortFunc, int num_runs = 5) {
        double total_time = 0;
        for (int i = 0; i < num_runs; ++i) {
            total_time += sortFunc();
        }
        return total_time / num_runs;
    }

public:
    void runAllTests() {
        
        
        vector<string> type_names = {"Случайный", "Обратный", "Почти отсорт."};
        vector<string> algos = {
            "Стандарт QuickSort", "Стандарт MergeSort", 
            "Оптим. QuickSort", "Оптим. MergeSort", 
            "Radix", "Radix + QuickSort"
        };
        
        cout << padRight("Алгоритм", 25) 
            << padRight("Тип массива", 15) 
            << padRight("Размер" , 10) 
            << padRight("Время (мс)" , 13) 
            << "Сравнения\n";
        cout << string(80, '-') << "\n";

        for (int t = 0; t < 3; ++t) {
            for (int size = 100; size <= 3000; size += 100) {
                vector<string> orig = generator.getArray(t, size);

                for(int alg = 0; alg < 6; ++alg) {
                    
                    double time_ms = 0;
                    long long current_comps = 0;

                    time_ms = measureTime([&]() -> double {
                        char_comps = 0; 
                        auto start = chrono::high_resolution_clock::now();
                        
                        if (alg == 0) {
                            vector<string> data = orig;
                            stdQuickSort(data);
                        } 
                        else if (alg == 1) {
                            vector<string> data = orig;
                            stdMergeSort(data, 0, data.size() - 1);
                        }
                        else if (alg == 2) {
                            vector<string> data = orig;
                            quickSort(data, 0); 
                        }
                        else if (alg == 3) {
                            vector<pair<string, int>> data_pairs(orig.size());
                            for(size_t i = 0; i < orig.size(); ++i) {
                                data_pairs[i] = {orig[i], 0};
                            }
                            mergeSort(data_pairs, 0, data_pairs.size() - 1); 
                        }
                        else if (alg == 4) {
                            vector<string> data = orig;
                            radixSort(data, 0); 
                        }
                        else if (alg == 5) {
                            vector<string> data = orig;
                            radixQuickSort(data, 0); 
                        }

                        auto end = chrono::high_resolution_clock::now();
                        current_comps = char_comps;
                        return chrono::duration<double, milli>(end - start).count();
                    });

                    

                    cout << padRight(algos[alg], 25) 
                         << padRight(type_names[t], 15) 
                         << padRight(to_string(size) , 10) 
                         << padRight(to_string(time_ms) , 13)
                         << current_comps << "\n";
                }
                cout << string(80, '-') << "\n";
            }
        }
    }
};


int main() {
    StringSortTester tester;
    tester.runAllTests();
    return 0;
}
