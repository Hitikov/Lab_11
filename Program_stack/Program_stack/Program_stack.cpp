#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Node {
	char& key = *(new char);
	Node* ptr_to_next_node = nullptr;
};

struct Stack {
	Node* head_node = nullptr;
	Node* tail_node = nullptr;
	int size = 0;
};

void pop(Stack* stack) {
	Node* delete_node = stack->head_node;
	stack->head_node = stack->head_node->ptr_to_next_node;
	stack->size--;
	delete delete_node;
}

void push(Stack* stack, char key) {
	Node* new_node = new Node;
	stack->size++;
	new_node->key = key;
	new_node->ptr_to_next_node = stack->head_node;
	stack->head_node = new_node;
}

void delete_key(Stack* stack, char key) {
	if (stack == nullptr) {
		cout << "Stack is not existing" << endl;
		return;
	}

	if (stack->head_node == nullptr) {
		cout << "Stack is empty" << endl;
		return;
	}

	cout << stack;

	Stack* buffer = new Stack;
	
	while ((stack->size > 0) && (stack->head_node->key != key)) {
		push(buffer, stack->head_node->key);
		pop(stack);
	}
	if (stack->head_node != nullptr) pop(stack);
	while (buffer->size > 0) {
		push(stack, buffer->head_node->key);
		pop(buffer);
	}

	delete buffer;
}

void add_node(Stack* stack, char str, const int& index = -1) {
	if (stack == nullptr) {
		cout << "Stack is not existing" << endl;
		return;
	}

	Node* new_node = new Node;
	new_node->key = str;

	if (stack->head_node == nullptr) {
		stack->head_node = new_node;
		stack->tail_node = new_node;
		stack->size++;
		return;
	}

	if ((index == -1) || (index == 0)) {
		push(stack, str);
		return;
	}
	
	Stack* buffer = new Stack;
	int i = 1;

	while ((stack->size > 0) && (i < index)) {
		push(buffer, stack->head_node->key);
		pop(stack);
		++i;
	}
	if (i == index) push(stack, str);
	while (buffer->size > 0) {
		push(stack, buffer->head_node->key);
		pop(buffer);
	}
	
}

void print_list(Stack* stack) {
	if (stack == nullptr) {
		cout << "Stack is not existing" << endl;
		return;
	}

	Node* current_node = stack->head_node;

	if (current_node == nullptr) {
		cout << "Stack is empty" << endl;
		return;
	}

	while (current_node != nullptr) {
		cout << current_node->key << "; ";
		current_node = current_node->ptr_to_next_node;
	}

	cout << endl;
}

void list_filesave(Stack* stack) {
	if (stack == nullptr) {
		cout << "Stack is not existing" << endl;
		return;
	}

	Node* current_node = stack->head_node;

	ofstream f("list_savestate.dat");

	while (current_node != nullptr) {
		f << current_node->key << "\n";
		current_node = current_node->ptr_to_next_node;
	}

	f.close();
}

void list_fileread(Stack* stack) {
	if (stack == nullptr) {
		cout << "Stack is not existing" << endl;
		return;
	}

	char buffer_char[1];
	string buffer_str;
	Stack* buffer = new Stack;

	ifstream f("list_savestate.dat");

	while (!f.eof()) {
		getline(f, buffer_str);
		buffer_char[0] = buffer_str[0];
		if (buffer_str != "") {
			add_node(buffer, buffer_str[0]);
		}
	}

	Node* current_node = buffer->head_node;

	while (current_node != nullptr) {
		add_node(stack, current_node->key);
		current_node = current_node->ptr_to_next_node;
	}
	delete buffer;

	f.close();
}

void list_delete(Stack* stack) {
	if (stack == nullptr) {
		cout << "Stack is not existing" << endl;
		return;
	}
	Node* remove_node;

	while (stack->head_node != nullptr) {
		remove_node = stack->head_node;
		stack->head_node = stack->head_node->ptr_to_next_node;
		delete remove_node;
	}

	delete stack;
}

int main() {
	int n, k;
	string str;
	char ch;
	Stack* stack = new Stack;

	cout << "Enter number of elements that will be entered on stack creation: ";
	cin >> n;
	cin.ignore();

	for (int i = 1; i <= n; ++i) {
		cout << "Enter key for element: ";
		getline(cin, str);
		ch = str[0];
		add_node(stack, ch);
		
	}

	print_list(stack);

	cout << "Enter key for deletion: ";
	getline(cin, str);
	ch = str[0];
	delete_key(stack, ch);
	print_list(stack);

	cout << "Enter index of element for adding and number (K) of entering element: ";
	cin >> n >> k;
	cin.ignore();

	for (int i = 1; i <= k; ++i) {
		cout << "Enter key for element: ";
		getline(cin, str);
		ch = str[0];
		add_node(stack, ch, n);
		
	}
	print_list(stack);

	cout << "Stack saved in file" << endl;
	list_filesave(stack);
	list_delete(stack);
	stack = nullptr;
	print_list(stack);


	stack = new Stack;


	cout << "Stack restored from file" << endl;
	list_fileread(stack);
	print_list(stack);

	list_delete(stack);


	return 0;
}