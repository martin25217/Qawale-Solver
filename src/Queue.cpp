#include<stdexcept>
#include <string>

template <typename T> class Queue {

    private:
    struct Node {

        T value;
        Node* next;
    };
    int length = 0;
    Node* head = nullptr;
    Node* tail = nullptr;

    public:
        
    ~Queue(){
        this->clear();
    }
        
    bool enqueue(T value){

        Node *node = new Node{value, nullptr};

		if (!node) {
		    return false;
		}

		if (!tail) {
		    head = node;
		    tail = node;
		}

		else {
		    tail->next = node;
			tail = node;
		}
        length++;
		return true;
    }
        
    T dequeue(){

        if(!head) {
		    throw std::runtime_error("Dequeuing from empty Queue!");
		}

		if (head == tail) {
		    tail = nullptr;
		}

		Node* next = head->next;
		T value = head->value;
		delete head;
		head = next;

        length--;
		return value;
    }
       
    bool has(T value){
        Node *iterator = head;

        while (iterator){
            if(iterator->value == value) return true;
            iterator = iterator->next;
        }
        
        return false;
	}

    int size(){
        return length;
    }

    void clear(){

        Node *iterator = head;
        Node *temp;

        while (iterator){
            temp = iterator;
            iterator = iterator->next;
            delete temp;
        }

        head = nullptr;
        return;
	}

	string printQ(int maxHeight){
        string pr;
        Node *iterator = head;

        for(int i = 0; i < length; i++){
            T ele = iterator->value;
            if(ele == red) pr.push_back('r');
            else if(ele == white) pr.push_back('w');
            else pr.push_back('y');
            iterator->next;
        }

        for(int i = 0; i < maxHeight - length; i++) pr.push_back(' ');

        return pr;
    }
        
};
