
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct ltcode
{
    unsigned long long frequency;
    unsigned char letter;
    string code = "";
};

void zeroset(ltcode *c)
{
    for (unsigned int i = 0; i < 256; ++i)
    {
        c[i].frequency = 0;
        c[i].letter = i;
    }
}

bool f(ltcode x, ltcode y)
{
    if (x.frequency != y.frequency) return x.frequency > y.frequency;
    else return x.letter > y.letter;
}

struct B
{
    string list;
    int i;

    int left;
    int right;

    string code = "";

    B()
    {
        list = "";
        i = 0;
    }
};

void print_binary_tree(int num, vector <B> &tree)
{
    if (tree[num].list.size() > 1)
    {
        cout << "\"'" << tree[num].list << "', " << tree[num].i << ", code: \'" << tree[num].code << "\'\" -> \"'" << tree[tree[num].left].list << "', " << tree[tree[num].left].i << ", code: \'" << tree[tree[num].left].code << "\'\" [ label = \"0\" ];\n";
        cout << "\"'" << tree[num].list << "', " << tree[num].i << ", code: \'" << tree[num].code << "\'\" -> \"'" << tree[tree[num].right].list << "', " << tree[tree[num].right].i << ", code: \'" << tree[tree[num].right].code << "\'\" [ label = \"1\" ];\n";
        print_binary_tree(tree[num].left, tree);
        print_binary_tree(tree[num].right, tree);
    }
}

void print_tree_graph(vector <B> &tree)
{
    cout << "digraph G {\n";
    print_binary_tree(tree.size()-1, tree);
    cout << "}\n";
}

void huffman_encoding_in(int num, string code, vector <B> &tree, ltcode *letter_codes)
{
    tree[num].code = code;
    if (tree[num].list.size() > 1)
    {
        huffman_encoding_in(tree[num].left, code+"0", tree, letter_codes);
        huffman_encoding_in(tree[num].right, code+"1", tree, letter_codes);
    }
    else
    {
        for (int j = 0; ; ++j)
        {
            if (letter_codes[j].letter == tree[num].list[0])
            {
                letter_codes[j].code = code;
                break;
            }
        }
    }
}

void huffman_encoding(vector <B> &sorted_tree, ltcode *letter_codes)
{
    huffman_encoding_in(sorted_tree.size()-1, "", sorted_tree, letter_codes);
}

int main() {
    unsigned char c;
    string S;
    ltcode count[256], stringlinks[256];
    zeroset(count);

    while (scanf("%c", &c))
    {
        if (c == '\n') break;
        S += c;
        ++count[c].frequency;
    }
    sort(count, count+256, f);

    vector <B> tree;
    B tmp;
    tmp.list = "0";
    int j = 0, letter_amount;
    for (j = 0; (count[j].frequency); ++j)
    {
        tmp.i = count[j].frequency;
        tmp.list[0] = count[j].letter;
        tree.push_back(tmp);
    }
    int maxsize = j-1, size;

    sort(tree.begin(), tree.end(), [] (B a, B b)
    {
        if (a.i != b.i) return (a.i < b.i);
        else return (a.list.size() < b.list.size());
    });

    for (j = 0; size < maxsize;)
    {
        tmp.list = tree[j].list + tree[j+1].list;
        tmp.i = tree[j].i + tree[j+1].i;
        tmp.left = j;
        tmp.right = j+1;

        size = tmp.list.size();

        tree.push_back(tmp);
        j += 2;
        sort(tree.begin()+j, tree.end(), [] (B a, B b)
        {
            if (a.i != b.i) return (a.i < b.i);
            else return (a.list.size() < b.list.size());
        }
        );
    }
    huffman_encoding(tree, count);
    print_tree_graph(tree);
    cout << "\nCodes of letters:\n";
    for (j = 0; (count[j].frequency); ++j)
    {
        cout << '\'' << count[j].letter << "\'(" << count[j].code << ")  ";
        stringlinks[count[j].letter].code = count[j].code;
    }
    cout << "\n\nEncoded string:\n";
    for (unsigned int i = 0; i < S.size(); ++i)
    {
        cout << stringlinks[S[i]].code;
    }
    cout << '\n';
    system("pause");
    return 0;
}
