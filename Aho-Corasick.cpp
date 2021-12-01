//если вы это читаете, вы находитесь в полном отчаянии
//"е мое, это ж мы еще и букву не знаем" (с) Ким

#include <algorithm>;
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define p_b push_back
struct Node {
    map<char, Node*> go;
    Node* eps;
    Node* par;
    char let;
    vector<string> ans;
};

Node* build(vector<string> dict) {
    Node* root = new Node;
    for (auto word : dict) {
        auto node = root;
        for (char c : word) {
            if (node->go.count(c)) {
                node = node->go[c];
            } else {
                node->go[c] = new Node;
                node->go[c]->par = node;
                node->go[c]->let = c;
                node = node->go[c];
            }
        }
        node->ans.push_back(word);
    }
    return root;
}

void make_eps(Node* root) {
    vector<Node*> vert;
    root->eps = root;
    for (auto [l, r] : root->go) {
        r->eps = root;
        for (auto [ll, rr] : r->go) {
            vert.push_back(rr);
        }
    }

    for (int i = 0; i < vert.size(); ++i) {
        auto node = vert[i]->par;
        auto c = vert[i]->let;
        do {
            node = node->eps;
        } while (node != root && !node->go.count(c));

        if (node->go.count(c)) {
            vert[i]->eps = node->go[c];
        } else {
            vert[i]->eps = root;
        }
        node = vert[i];

        for (auto v : node->eps->ans) {
            node->ans.push_back(v);
        }
        for (auto [l, r] : vert[i]->go) {
            vert.push_back(r);
        }
    }
}

void go(Node* root, const string& text) {
    Node* node = root;
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        if (node->go.count(c)) {
            node = node->go[c];
        } else {
            while (node != root && !node->go.count(c)) {
                node = node->eps;
            }
            if (node->go.count(c)) {
                node = node->go[c];
            } else {
                node = root;
                continue;
            }
        }
        for (auto v : node->ans) {
            cout << i << ": " << v << '\n';
        }
    }
}

int main() {}