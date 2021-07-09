#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
#define n 5

int _hash(string k){
    int hash_val = 0;
    int i = 0;
    while(k[i]!='\0'){
        hash_val += k[i];
        i++;
    }
    return abs(hash_val) % n;
}

template<typename T> class table{
    struct List{
        string key;
        T value;
        struct List *next;
        List():key(),value(),next(NULL){};
    };
    struct List *hashtable[n];
public:
    table(){
        for(int i=0;i<n;i++){
            struct List *ptr;
            ptr = new List();
            hashtable[i] = ptr;
        }
    }
    void insert(string key, T value){
        int hash_val = _hash(key);
        if(hashtable[hash_val]->key==""){
            hashtable[hash_val]->key = key;
            hashtable[hash_val]->value = value;
        } else {
            struct List *ptr;
            ptr = new List();
            ptr->next = new List();
            ptr->key = key;
            ptr->value = value;
            ptr->next = hashtable[hash_val];
            hashtable[hash_val] = ptr;
        }
        cout << "insert " << key << "," << value << " to table:" << hash_val << endl;
        return;
    }
    void tableInfo(){
        int i=0;
        struct List *ptr;
        ptr = new List();
        cout << "Hash table state" << endl;
        for(i=0;i<n;i++){
            ptr = hashtable[i];
            cout << i << ":";
            if(ptr->key==""){
                cout << "Empty";
            } else {
                while(ptr!=NULL){
                    cout << ptr->key << "," << ptr->value << " -> ";
                    ptr = ptr->next;
                }
            }
            cout << endl;
        }
    }
    void operator()(const string key) const;
    void operator-=(const string key) const;
};

template<typename T>  void table<T>::operator()(const string key) const{
    int hash_val = _hash(key);
    struct List *ptr;
    ptr = new List();
    ptr = hashtable[hash_val];
    cout << "Search ";
    while(ptr!=NULL){
        if(key.compare(ptr->key)==0){
            cout << "key:" << key << ",value:" << ptr->value << endl;
            return;
        }
        ptr = ptr->next;
    }
    cout << "Key:" << key << ",value:Not found" << endl;
    return;
}

template<typename T> void table<T>::operator-=(const string key) const{
    int hash_val = _hash(key);
    struct List *ptr;
    ptr = new List();
    ptr = hashtable[hash_val];
    struct List *ptr2;
    while(ptr!=NULL){
        if(key.compare(ptr->key)==0){
            if(ptr==hashtable[hash_val]){
                if(ptr->next==NULL){
                    ptr->key = "";
                    ptr->value = 0;
                    ptr->next = NULL;
                } else {
                    ptr->key = ptr->next->key;
                    ptr->value = ptr->next->value;
                    ptr->next = ptr->next->next;
                    delete(ptr->next);
                }
            } else {
                ptr2 = new List();
                ptr2 = hashtable[hash_val];
                while(ptr2->next!=ptr){
                    ptr2 = ptr2->next;
                }
                ptr2->next = ptr->next;
                delete(ptr);
            }
            cout << "table:" << hash_val << " " << key << " deleted" << endl;
            break;
        }
        ptr = ptr->next;
    }
    return;
}

int main(void){
    table<int> t;
    t.insert("aac",5);
    t.insert("abb",20);
    t.insert("bab",30);
    t.insert("bbb",10);
    t.tableInfo();
    t("aac");
    t("bbb");
    t -= "abb";
    t -= "bab";
    t -= "bbb";
    t.tableInfo();
    t("abb");
}