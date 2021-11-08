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
