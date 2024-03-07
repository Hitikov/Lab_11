#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Node {
	char& key = *(new char);
	Node* ptr_to_next_node = nullptr;
};

struct Queue {
	Node* head_node = nullptr;
	Node* tail_node = nullptr;
	int size = 0;
};

void pop(Queue* queue) {
	Node* delete_node = queue->head_node;
	queue->head_node = queue->head_node->ptr_to_next_node;
	queue->size--;
	delete delete_node;
}

void push(Queue* queue, char key) {
	Node* new_node = new Node;
	queue->size++;
	new_node->key = key;
	queue->tail_node->ptr_to_next_node = new_node;
	queue->tail_node = new_node;
}

void delete_key(Queue* queue, char key) {
	if (queue == nullptr) {
		cout << "Queue is not existing" << endl;
		return;
	}

	if (queue->head_node == nullptr) {
		cout << "Queue is empty" << endl;
		return;
	}

	int i = 1;
	while (i <= queue->size) {
		if (queue->head_node->key == key) {
			pop(queue);
		}
		else
		{
			push(queue, queue->head_node->key);
			pop(queue);
			++i;
		}
	}
}

void add_node(Queue* queue, char str, const int& index = -1) {
	if (queue == nullptr) {
		cout << "Queue is not existing" << endl;
		return;
	}

	Node* new_node = new Node;
	new_node->key = str;

	if (queue->head_node == nullptr) {
		queue->head_node = new_node;
		queue->tail_node = new_node;
		queue->size++;
		return;
	}

	if ((index == -1) || (index == 0)) {
		push(queue, str);
		return;
	}

	int i = 1;
	while (i <= queue->size) {
		if (i == index) {
			push(queue, str);
			++i;
		}
		else
		{
			push(queue, queue->head_node->key);
			pop(queue);
			++i;
		}
	}
}

void print_list(Queue* queue) {
	if (queue == nullptr) {
		cout << "Queue is not existing" << endl;
		return;
	}

	Node* current_node = queue->head_node;

	if (current_node == nullptr) {
		cout << "Queue is empty" << endl;
		return;
	}

	while (current_node != nullptr) {
		cout << current_node->key << "; ";
		current_node = current_node->ptr_to_next_node;
	}

	cout << endl;
}

void list_filesave(Queue* queue) {
	if (queue == nullptr) {
		cout << "Queue is not existing" << endl;
		return;
	}

	Node* current_node = queue->head_node;

	ofstream f("list_savestate.dat");

	while (current_node != nullptr) {
		f << current_node->key << "\n";
		current_node = current_node->ptr_to_next_node;
	}

	f.close();
}

void list_fileread(Queue* queue) {
	if (queue == nullptr) {
		cout << "Queue is not existing" << endl;
		return;
	}

	char buffer_char[1];
	string buffer_str;

	ifstream f("list_savestate.dat");

	while (!f.eof()) {
		getline(f, buffer_str);
		buffer_char[0] = buffer_str[0];
		if (buffer_str != "") {
			add_node(queue, buffer_str[0]);
		}
	}

	f.close();
}

void list_delete(Queue* queue) {
	if (queue == nullptr) {
		cout << "Queue is not existing" << endl;
		return;
	}
	Node* remove_node;

	while (queue->head_node != nullptr) {
		remove_node = queue->head_node;
		queue->head_node = queue->head_node->ptr_to_next_node;
		delete remove_node;
	}

	delete queue;
}

int main() {
	int n, k;
	string str;
	char ch;
	Queue* queue = new Queue;

	cout << "Enter number of elements that will be entered on queue creation: ";
	cin >> n;
	cin.ignore();

	for (int i = 1; i <= n; ++i) {
		cout << "Enter key for element: ";
		getline(cin, str);
		ch = str[0];
		add_node(queue, ch);
	}

	print_list(queue);

	cout << "Enter key for deletion: ";
	getline(cin, str);
	ch = str[0];
	delete_key(queue, ch);
	print_list(queue);

	cout << "Enter number of element for adding and count (K) of entering element: ";
	cin >> n >> k;
	cin.ignore();

	for (int i = 1; i <= k; ++i) {
		cout << "Enter key for element: ";
		getline(cin, str);
		ch = str[0];
		add_node(queue, ch, n);
		++n;
	}
	print_list(queue);

	cout << "Queue saved in file" << endl;
	list_filesave(queue);
	list_delete(queue);
	queue = nullptr;
	print_list(queue);


	queue = new Queue;


	cout << "Queue restored from file" << endl;
	list_fileread(queue);
	print_list(queue);

	list_delete(queue);


	return 0;
}