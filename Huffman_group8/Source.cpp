#include"iostream" 
#include <fstream>
#include "queue"   
#include "string"  
#include "iterator"  
#include "vector"  
#include "algorithm"  
using namespace std;

struct tree_node {  // from the pdf in canvas
	int leftchild;
	int rightchild;
	int parent;
};

struct symbol_info { // from the pdf in canvas
	char symbol;
	int frequency;
	int leaf;
};


struct forest_roots {  // from the pdf in canvas
	int weight;
	int root;
};

struct cmp        // using this to construct minHeap
{
	bool operator()(const forest_roots &a, const forest_roots &b)
	{
		return a.weight>b.weight;
	}
};

class huffmanCoding {
public:
	vector<char> freqC;     //using this vector to check the original message in other data structure
	vector<tree_node> TREE;
	vector<symbol_info> Symbol;
	priority_queue<forest_roots, vector<forest_roots>, cmp> FOREST;
	void Huffman();
	bool isLeaf(int index);
	void buildCode(vector<string> *v, int i, string s);
	vector<string> buildCode();
	vector<int> computeFreq(string file);
	void constructTREE(string file);
	void getResult(string input, string output);

	huffmanCoding() {
		vector<char> temp(256);
		freqC.assign(temp.begin(), temp.end());
		for (int i = 0;i < freqC.size();i++) {
			freqC[i] = '.';
		}
	}

};



vector<int> huffmanCoding::computeFreq(string file) {   // compute the frequency table

	vector<int> freq(256);
	ifstream infile(file); // for input file
	if (infile.fail()) {
		cout << "Input file \"" << file << "\" opening failed" << endl;
		return freq;
	}

	char symbol;
	infile.get(symbol);
	while (!infile.eof()) {
		if (symbol >= 'a'&&symbol <= 'z' || symbol >= 'A'&&symbol <= 'Z' || symbol >= '0'&&symbol <= '9') {
			freq[symbol]++;
			freqC[symbol] = symbol;
			//cout << symbol << endl;
			infile.get(symbol);
		}
		else {
			freqC[symbol] = '.';
			infile.get(symbol);
		}

	}
	infile.close();
	return freq;
}

void huffmanCoding::constructTREE(string file) {   //construct the TREE,Symbol and the FOREST
	vector<int> freq = computeFreq(file);
	int count = 1;
	tree_node t1;
	t1.leftchild = 0;
	t1.parent = 0;
	t1.rightchild = 0;
	TREE.push_back(t1);
	for (int i = 0;i <= 255;i++) {

		if (freqC[i] != '.') {
			symbol_info s;
			tree_node t;
			s.frequency = freq[i];
			s.leaf = count++;
			s.symbol = freqC[i];
			t.leftchild = 0;
			t.parent = 0;
			t.rightchild = 0;
			TREE.push_back(t);
			Symbol.push_back(s);
		}
	}

	for (int i = 0;i<Symbol.size();i++) {
		forest_roots f;
		f.root = Symbol[i].leaf;
		f.weight = Symbol[i].frequency;
		FOREST.push(f);
	}

}

void huffmanCoding::Huffman() {     //using priority_queue to get the huffman tree
	while (FOREST.size()> 1) {
		forest_roots least = FOREST.top();
		FOREST.pop();
		//cout << least.weight << endl;
		forest_roots second = FOREST.top();
		FOREST.pop();
		tree_node t;
		t.leftchild = least.root;
		t.rightchild = second.root;
		t.parent = 0;
		//cout <<"+++++++"<< t.parent<<"++++"<< t.leftchild <<"++++"<< t.rightchild << endl;
		TREE.push_back(t);
		TREE[least.root].parent = TREE.size() - 1;
		TREE[second.root].parent = TREE.size() - 1;
		forest_roots newroot;
		newroot.weight = least.weight + second.weight;
		newroot.root = TREE.size() - 1;
		FOREST.push(newroot);
	}

}

bool huffmanCoding::isLeaf(int index) {    //whether the node is a leaf
	if (TREE[index].leftchild == 0 && TREE[index].rightchild == 0) return true;
	return false;
}

void huffmanCoding::buildCode(vector<string> *v, int i, string c) {//recursive operation to get the huffman code for original message
	if (isLeaf(i)) {
		(*v)[Symbol[i - 1].symbol] = c;
		return;
	}
	buildCode(v, TREE[i].leftchild, c + "0");
	//c.erase(c.size() - 1);
	buildCode(v, TREE[i].rightchild, c + "1");
	//c.erase(c.size() - 1);
}

vector<string> huffmanCoding::buildCode() {
	vector<string> v(256);
	buildCode(&v, TREE.size() - 1, "");
	return v;
}

void huffmanCoding::getResult(string input, string output) {   //get the result of the huffman
	ofstream outfile(output);
	constructTREE(input);
	cout << "-----Symbol vector which contains the frequency of the letter and digit of the sorce code --------" << endl;
	outfile << "-----the frequency table for the source text --------" << endl;
	outfile << "symbol" << "---" << "frequency" << endl;
	for (int i = 0;i<Symbol.size();i++) {
		cout << Symbol[i].symbol << "---" << Symbol[i].frequency << "---" << Symbol[i].leaf << endl;
		outfile << Symbol[i].symbol << "---" << Symbol[i].frequency << endl;
	}
	cout << "-----TREE before huffman--------" << endl;
	for (int i = 0;i<TREE.size();i++) {
		cout << TREE[i].leftchild << "---" << TREE[i].parent << "---" << TREE[i].rightchild << endl;
	}
	cout << "-----the size of priority_queue before huffman--------" << endl;
	cout << FOREST.size() << endl;
	Huffman();

	cout << "----------TREE after huffman -----------" << endl;
	for (int i = 0;i<TREE.size();i++) {
		cout << TREE[i].parent << "---" << TREE[i].leftchild << "---" << TREE[i].rightchild << endl;
	}
	cout << "----------Huffman code for each letter and digit in the source code-----------" << endl;
	vector<string> end(buildCode());
	outfile << "----------Huffman code for each letter and digit in the source code-----------" << endl;
	for (int i = 0;i<end.size();i++) {
		if (freqC[i] != '.') {
			cout << freqC[i] << "----->" << end[i] << endl;
			outfile << freqC[i] << "----->" << end[i] << endl;
		}
	}

	ifstream infile(input); // for input file
	if (infile.fail()) {
		cout << "open Input file \"" << input << "\"  failed" << endl;
		return;
	}
	else {

		string answer = "";
		string original = "";
		char symbol;
		infile.get(symbol);
		while (!infile.eof()) {
			if (symbol >= 'a'&&symbol <= 'z' || symbol >= 'A'&&symbol <= 'Z' || symbol >= '0'&&symbol <= '9') {
				answer += end[symbol];
				original += symbol;
			}
			infile.get(symbol);
		}
		infile.close();
		cout << "the length of original message in terms of number of bits:" << original.size() * 8 << endl;
		cout << "the length of the coded message in terms of number of bits:" << answer.size() << endl;
		cout << "compression ratio of huffman is:" << (double)answer.size() / (original.size() * 8) << endl;

		cout << endl;
		cout << endl;

		cout << "---------------the original text with only letters and numbers-----------------" << endl;
		cout << endl;

		cout << original << endl;
		cout << "---------------the coded text in bits-----------------" << endl;
		cout <<  endl;
		cout << answer << endl;
	

		outfile << "---------------the original text with only letters and numbers-----------------" << endl;
		outfile << original << endl;
		outfile << "---------------the coded message in bits-----------------" << endl;
		outfile << answer << endl;
		outfile << "the length of original message in terms of number of bits:" << original.size() * 8 << endl;
		outfile << "the length of the coded message in terms of number of bits:" << answer.size() << endl;
		outfile << "compression ratio of huffman is:" << (double)answer.size() / (original.size() * 8) << endl;
		outfile.close();
	}
	
}

int main() {

	huffmanCoding h;
	//h.getResult("Text.dat", "result.dat");
	h.getResult("infile.dat", "outfile.dat");
	return 0;
}

