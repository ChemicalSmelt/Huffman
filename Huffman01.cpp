//Huffman coding for c++

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
class Node;
map<char, int> Mfreq;
vector<Node*> forest;
int oritotal = 0;
int total = 0;

class Node {
public:
    Node* left;
    Node* right;
    int freq;
    char val;
    Node() : val('\0'), freq(0), left(NULL), right(NULL) {

    }

    Node(char nval, int f) : val(nval),freq(f),left(NULL),right(NULL) {

    }
};


bool comp(Node* a, Node* b) {
    return a->freq < b->freq;
}

Node* Huffman(Node* a, Node* b) {
    Node* newHead = new Node('\0', a->freq + b->freq);
    newHead->left = a->freq < b->freq ? a : b;
    newHead->right = a->freq < b->freq ? b : a;
    return newHead;
}


void InorderTraversal(Node* node ,string s) {
    if (node->val != '\0') {
        cout << node->val << " | " << s << endl;
        total += Mfreq[node->val] * s.length();
    }
    if (node->left) InorderTraversal(node->left,s + "0");
    if (node->right) InorderTraversal(node->right,s + "1");
    delete node;
}



int main()
{
    string data;
    getline(cin, data);
    for (auto& c : data) {
        Mfreq[c]++;
    }
    for (auto& c : Mfreq) {
        if (c.second != 0) {
            forest.push_back(new Node(c.first,c.second));
            oritotal += c.second * 8;
        }
    }
    Node* head = NULL;
    for (int i = 0; i < forest.size()-1; i+=2) {
        sort(forest.begin() + i, forest.end(), comp);
        head = Huffman(forest[i], forest[i+1]);
        forest.push_back(head);
    }
    InorderTraversal(head, "");
    cout << "originalSize (Ascii) = " << oritotal << endl;
    cout << "Huffmantotal (bits) = " << total << endl;
    cout << fixed << setprecision(3) << "Proportion = " << total / (float)oritotal << endl;
    return 0;

}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
