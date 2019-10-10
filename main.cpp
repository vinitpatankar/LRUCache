#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>

struct Node{
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(int k, int val):prev(nullptr),next(nullptr),key(k),value(val){};
};

class Cache{
   
    protected: 
    std::map<int,Node*> mp; //map the key to the node in the linked list
    int cp;
    Node* tail;
    Node* head;
    virtual void set(int, int) = 0;
    virtual int get(int) = 0;

};
class LRUCache : public Cache
{
    private:
    int size{0};
    public:
    LRUCache(int capacity)
    {
        cp = capacity;
    }
    virtual void set(int key, int value)
    {
        if(mp.count(key) > 0)
        {
            // Cache hit
            Node* p = mp[key];
            p->value = value;
            if(p->next) p->next->prev = p->prev;
            if(p->prev) p->prev->next = p->next;
            p->next = head;
            head = p;
        }
        else
        {
            // Cache miss
            if(size >= cp)
            {
                // Cache full
                // Delete tail since thats the LRU
                Node* t = tail;
                mp.erase(t->key);
                if(t->prev) t->prev->next = nullptr;
                tail = t->prev;
                delete t;
                if(tail == nullptr)
                {
                    delete head;
                    head = nullptr;
                }
                --size;
            }
            Node* n = new Node(key, value);
            if(size == 0)
            {
                head = n;
                tail = n;
            }
            else
            {
                Node* n = new Node(key, value);
                n->next = head;
                head->prev = n;
                head = n;
            }
            ++size;
            mp[key] = n;
        }
    }
    virtual int get(int key)
    {
        if(mp.count(key) == 0) return -1;    
        Node* p = mp[key];
        int value = p->value;
        if(p->prev) p->prev->next = p->next;
        if(p->next) p->next->prev = p->prev;
        p->next = head;
        head = p;
        return value;
    }
};
int main() {
    int n, cp,i;
    std::cin >> n >> cp;
    LRUCache l(cp);
    for(i=0;i<n;i++)
    {
        std::string action;
        std::cin >> action;
        if(action == "get") {
           int key;
           std::cin >> key;
           std::cout << l.get(key) << '\n';
        } 
        else if(action == "set") {
           int key, value;
           std::cin >> key >> value;
           l.set(key,value);
        }
    }
    return 0;
}
