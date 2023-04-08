//
//  Map.h
//  Project 2
//
//  Created by JackieYJC on 1/24/16.
//  Copyright © 2016 JackieYJC. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <string>

typedef std::string KeyType;
typedef double ValueType;

class Map
{
public:
    Map();
    ~Map();
    Map(const Map& other);
    Map& operator= (const Map& rhs);
    
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    void dump() const;
    
private:
    struct Node
    {
        KeyType m_key;
        ValueType m_value;
        Node* m_next;
        Node* m_prev;
    };
    Node* m_head;
    int m_size;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);

//implement the member functions (with comments,pseudo first)
//implement the destrcutor/copy/assignment
//implement two non-member function (with comments, pseudo first)
//testing & debugging
//write the report
//re-read the spec and double check everything with Max

#endif /* Map_h */
