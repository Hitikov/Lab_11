#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Node {
	char& key = *(new char[1]);
	Node* ptr_to_next_node = nullptr;
};

struct List {
	Node* head_node = nullptr;
	Node* tail_node = nullptr;
	int size = 0;
};

void delete_key(List* list, char key) {
	if (list == nullptr) {
		cout << "List is not existing" << endl;
		return;
	}

	if (list->head_node == nullptr) {
		cout << "List is empty" << endl;
		return;
	}

	Node* remove_node = list->head_node;
	Node* prev_node = nullptr;
	while ((remove_node->key != key) && (remove_node != nullptr)) {
		prev_node = remove_node;
		remove_node = remove_node->ptr_to_next_node;
	}

	if (remove_node == nullptr) {
		cout << "No key found" << endl;
		return;
	}

	//???
	if ((list->head_node == remove_node) && (list->tail_node == remove_node)) {
		list->head_node = nullptr;
		list->tail_node = nullptr;
	}
	else if (list->head_node == remove_node) {
		list->head_node = remove_node->ptr_to_next_node;
	}
	else if (list->tail_node == remove_node) {
		list->tail_node = prev_node;
		prev_node->ptr_to_next_node = nullptr;
	}
	else {
		prev_node->ptr_to_next_node = remove_node->ptr_to_next_node;
	}

	delete remove_node;

}

void add_node(List* list, char str, const int& index = -1) {
	if (list == nullptr) {
		cout << "List is not existing" << endl;
		return;
	}

	Node* new_node = new Node;
	new_node->key = str;

	list->size++;

	if (list->head_node == nullptr) {
		list->head_node = new_node;
		list->tail_node = new_node;
		return;
	}

	if (index == -2) {
		list->tail_node->ptr_to_next_node = new_node;
		list->tail_node = new_node;
		return;
	}

	if ((index == -1) || (index == 0)) {
		new_node->ptr_to_next_node = list->head_node;
		list->head_node = new_node;
		return;
	}

	int counter = 0;
	Node* current_node;
	Node* prev_node = nullptr;

	current_node = list->head_node;
	while (counter != index) {
		prev_node = current_node;
		current_node = current_node->ptr_to_next_node;
		++counter;
	}
	
	new_node->ptr_to_next_node = current_node;
	if (prev_node != nullptr) {
		prev_node->ptr_to_next_node = new_node;
	}
}

void print_list(List* list) {
	if (list == nullptr) {
		cout << "List is not existing" << endl;
		return;
	}


	Node* current_node = list->head_node;

	if (current_node == nullptr) {
		cout << "List is empty" << endl;
		return;
	}

	while (current_node != nullptr) {
		cout << current_node->key << "; ";
		current_node = current_node->ptr_to_next_node;
	}

	cout << endl;

}

void list_filesave(List* list) {
	if (list == nullptr) {
		cout << "List is not existing" << endl;
		return;
	}

	Node* current_node = list->head_node;

	ofstream f("list_savestate.dat");

	while (current_node != nullptr) {
		f << current_node->key << "\n";
		current_node = current_node->ptr_to_next_node;
	}

	f.close();
}

void list_fileread(List* list) {
	if (list == nullptr) {
		cout << "List is not existing" << endl;
		return;
	}

	char buffer_char[1];
	string buffer_str;

	ifstream f("list_savestate.dat");

	while (!f.eof()) {
		getline(f, buffer_str);
		buffer_char[0] = buffer_str[0];
		if (buffer_str != "") {
			add_node(list, buffer_str[0], -2);
		}
	}

	f.close();
}

void list_delete(List* list) {
	if (list == nullptr) {
		cout << "List is not existing" << endl;
		return;
	}
	Node* remove_node;

	while (list->head_node != nullptr) {
		remove_node = list->head_node;
		list->head_node = list->head_node->ptr_to_next_node;
		delete remove_node;
	}

	delete list;
}

int main() {
	int n, k;
	string str;
	char ch[1];
	List* list = new List;

	cout << "Enter number of elements that will be entered on list creation: ";
	cin >> n;
	cin.ignore();

	for (int i = 1; i <= n; ++i) {
		cout << "Enter key for element: ";
		getline(cin, str);
		ch[0] = str[0];
		add_node(list, ch[0]);
	}

	print_list(list);

	cout << "Enter key for deletion: ";
	getline(cin, str);
	ch[0] = str[0];
	delete_key(list, ch[0]);
	print_list(list);

	cout << "Enter number(№) of element for adding and count (K) of entering element: ";
	cin >> n >> k;
	n--;
	cin.ignore();

	for (int i = 1; i <= k; ++i) {
		cout << "Enter key for element: ";
		getline(cin, str);
		ch[0] = str[0];
		add_node(list, ch[0], n);
	}
	print_list(list);

	cout << "List saved in file" << endl;
	list_filesave(list);
	list_delete(list);
	list = nullptr;
	print_list(list);


	list = new List;


	cout << "List restored from file" << endl;
	list_fileread(list);
	print_list(list);

	list_delete(list);


	return 0;
}