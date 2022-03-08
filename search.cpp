#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Trie {
public:	
	Trie* next[128];  //128 characters because of all lowercase/uppercase letters, hyphens, some numbers, etc in ascii table
	int searchnumber;	//this index is given to each complete query, -1 means that it is the end of a complete query from the dictionary
	
	
	Trie() {    //constructor for new trie
		for (int i = 0; i < 128; i++) {			//Less than 128 because of the number of characters in ascii table
			next[i] = NULL; 					//makes the next node NULL
		searchnumber = -1;						//each node is created assuming it is the end of a word (assigned -1)
		}
	}
};

void insert(Trie* root, int searchnumber, string query) {
	Trie* node = root;							//current node is the root
	
	for (int i = 0; i < query.size(); i++) {    //loop begins at the beginning of each word to be entered into the dictionary
		char k = query[i];						//assigns each letter of the word to be entered to a variable k
		if (!node->next[k]) {					//if the next node does not contain character k
			node->next[k] = new Trie();			//then a new node is created that will contain the character k
		}
		
		node = node->next[k];					//current node switches from the root to the next node that was created
	}
	node->searchnumber = searchnumber;			//assigns the searchnumber of the node according to the function

}

void collection(Trie* root, string query) {	
	Trie* node = root;											
	if (node->searchnumber != -1) {								//if the node is not equal to -1, meaning it IS a word from the dictionary
		cout << query << " " << node->searchnumber << endl;		//print out the word and the searchnumber associated with the word in the dictionary
	}
	for (int i = 0; i < 128; i++) {								
		if (node->next[i] != NULL) {							//if the value in the next node is not empty
			char k = i;											//assign the variable k to the character in the ascii table associated with each i
			collection(node->next[i], query + k);				//run the collection function again for the next node, and for the query prefix with character k added to it
		}
	}
}

void autocomplete(Trie* root, string query) {
	Trie* node = root;				
	for (int i = 0; i < query.size(); i++) {					//beginning with the first character in the query, and continuing to the last character
		char k = query[i];										//assign variable k to the first character in query prefix
		node = node->next[k];									//move the node downward to the next node
	}
	collection(node, query);									//call collection function again
}

void recommendation(Trie* root, string query) {	
	Trie* node = root;											
	if (node->searchnumber != -1) {								//if the node is not equal to -1, meaning it IS a word from the dictionary
		cout << query << " " << node->searchnumber << endl;		//print out the query minus the k value 
	}
	for (int i = 0; i < 128; i++) {											
		if (node->next[i] != NULL) {							//if the value in the node is not empty							
			char k = query.back();								//assign character k to the last incorrect element in the query							
			recommendation(node->next[i], query);				//run the recomendation function again for the next node, and the original query
		}
	}
}

void recommendationcomplete(Trie* root, string query) {
	for (int i = 0; i < 3; i++) {									//This loop means the recommendation feature will only run 3 times
		Trie* node = root;				
		for (int i = 0; i < query.size(); i++) {					//for the beginning of the query word until the end
			char k = query.back();									//assign character k to the last element of the string
			if (!node->next[k]) {									//if the next node does not contain the last element of the string				
				recommendation(node, query);						//call the recommendation query for the current node and query
			}		
			node = node->next[k];						
		}	
	}
}

int main() {
	
Trie* root = new Trie;						//creation of the Trie

fstream file;
string word; 
string filename = "Dictionary.txt";		
file.open(filename.c_str());					//Here is where the file is opened
vector <string> wordvector;
while (file >> word) {							//uses a space to delineate each word in the given dictionary
	wordvector.push_back(word);					//each word from dictionary is pushed into a vector for storage
}

for (int i = 0; i < wordvector.size(); ++i) {
	insert(root, i, wordvector.at(i));					//Here is where each word is inserted into the trie calling insert function
}

string checkword;										//The word entered for auto com-letion feature is assigned to variable checkword
cout << "This test is for automatic search completion:" << endl;
cout << " Please type search query: ";
cin >> checkword;
cout << "Your options are: " << endl;
autocomplete(root, checkword);							//autocomplete function is called using checkword value, and root


string recommended_word;								//The word entered for recommendation search feature is called recommended_word
cout << endl << "This test is for recommendation search:" << endl;
cout << " Please type search query: ";
cin >> recommended_word;
cout << "Do you mean: " << endl;
recommendationcomplete(root, recommended_word);			//recommendation complete function is called using recommended_word value, and root

return 0;
   

}