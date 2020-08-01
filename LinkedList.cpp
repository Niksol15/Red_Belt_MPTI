using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node {
        T value;
        Node* next = nullptr;
    };

    ~LinkedList(){
        while (head){
            PopFront();
        }
    }

    void PushFront(const T& value){
        Node* new_head = new Node;
        new_head -> next = head;
        new_head -> value = value;
        head = new_head;
    }
    void InsertAfter(Node* node, const T& value){
        if(node){
            Node* after = new Node;
            after -> value = value;
            after -> next = node -> next;
            node -> next = after;
        } else {
          PushFront(value);
        }
    }
    void RemoveAfter(Node* node){
        if(!node){
            PopFront();
        } else if(node -> next){
            Node* next_ = (node -> next) -> next;
            delete node -> next;
            node -> next = next_;
        }
    }
    void PopFront(){
        if(head){
            Node* new_head = head -> next;
            delete head;
            head = new_head;
        }
    }

    Node* GetHead() { return head; }
    [[nodiscard]] const Node* GetHead() const { return head; }

private:
    Node* head = nullptr;
};
