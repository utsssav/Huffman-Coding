#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// A Tree node
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
	
	Node(char ch1, int freq1, Node* l=NULL, Node* r=NULL)
	{
	    ch = ch1;
	    freq = freq1;
	    left = l;
	    right = r;
	}
};

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};

// traverse the Huffman Tree and store Huffman Codes
// in a map.
void encode(Node* root, string str,
			unordered_map<char, string> &huffmanCode)
{
	if (root == NULL)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// traverse the Huffman Tree and decode the encoded string
void decode(Node* root, int &index, string str)
{
	if (root == NULL) {
		return;
	}

	// found a leaf node
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

// Builds Huffman Tree and decode given input text
Node* buildHuffmanTree(string text)
{
	// count frequency of appearance of each character
	// and store it in a map
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of
	// Huffman tree;
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair: freq) {
		pq.push(new Node(pair.first, pair.second));
	}

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		pq.push(new Node('\0', sum, left, right));
	}
	
	return pq.top();
}

// Huffman coding algorithm
int main()
{
	string text = "Data dominates. If you've chosen the right data structures and organized things well, the algorithms will almost always be self-evident. Data structures, not algorithms, are central to programming.   -Rob Pike";
	
	// root stores pointer to root of Huffman Tree
	Node* root = buildHuffmanTree(text);

	// traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair: huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << text << '\n';

	// print encoded string
	string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';

	// traverse the Huffman Tree again and this time
	// decode the encoded string
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 1) {
		decode(root, index, str);
	}

	return 0;
}

// Time Complexity : O(nlog(n)) 

// Auxillary Space : O(n)

/* Input Output

Huffman Codes are :

n 11111
d 111101
c 111100
a 1110
e 1101
y 1100111
z 11001101
P 11001100
I 11001011
' 11001010
, 100000
. 010110
r 0110
- 1100000
s 0111
D 1100001
u 01010
o 0100
t 000
i 0010
R 11001001
w 010111
l 0011
p 1000010
v 1000011
m 10001
h 10010
g 10011
  101
b 1100010
f 1100011
k 11001000

Original string was :
Data dominates. If you've chosen the right data structures and organized things well, the algorithms will almost always be self-evident. Data structures, not algorithms, are central to programming.   -Rob Pike

Encoded string is :
1100001111000011101011111010100100010010111111110000110101110101101011100101111000111011100111010001010110010101000011110110111110010010010001111101111111010001001011011010110001010011100100001011111011110000111010101110000110010101111000000101001101101011110111101111111110110101000110100111110111110010110011011101111101101000100100010111111001101111010101111101001100111000001010001001011011011110001110011010001100010000100101000101111010101110010001100111011110001110001010001110001011110001101011111101100111011110111000101101101011111010011110001111000001101100001100101111011101111110000101101011100001111000011101010111000011001010111100000010100110110101111000001011111101000001011110001110011010001100010000100101000101111000001011110011011011011111001101111110000110111000111010000100101100001001100100100110110111010001100010010111111001101011010110110111000001100100101001100010101110011000010110010001101

Decoded string is: 
Data dominates. If you've chosen the right data structures and organized things well, the algorithms will almost always be self-evident. Data structures, not algorithms, are central to programming.   -Rob Pike
*/