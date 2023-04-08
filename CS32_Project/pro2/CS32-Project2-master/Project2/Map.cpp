//
//  Map.cpp
//  Project 2
//
//  Created by JackieYJC on 1/24/16.
//  Copyright © 2016 JackieYJC. All rights reserved.
//

#include "Map.h"

#include <iostream>
using namespace std;

Map::Map() //default constructor
{
    m_head = new Node;
    m_size = 0;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
}

Map::~Map() //destructor
{
    for (int i = 0; i < size(); i++) {
        delete m_head->m_prev;
        if (m_head->m_next != nullptr) //if the next element has not already been deleted
        {
            m_head = m_head->m_next;
        }
        else{
            delete m_head;
            break;
        }
    }
}

Map::Map(const Map& other) //the copy constructor
{
    m_size = other.m_size; //copy the size
    
    m_head = new Node; //create a new dummy Node
    Node* a = m_head;
    Node* b = other.m_head;
    for (int i = 0; i < m_size; i++) {
        a->m_next = new Node; //create a new Node
        a->m_next->m_key = b->m_next->m_key; //copy the key into it
        a->m_next->m_value = b->m_next->m_value; // copy the value into it
        a->m_next->m_prev = a;
        a = a->m_next;
        b = b->m_next;
    }
    a->m_next = m_head;
    m_head->m_prev = a;
    
}

Map& Map:: operator= (const Map& rhs) //the assignment operator
{
    if (&rhs == this)
        return (*this);
    for (int i = 0; i < size(); i++) // delete the original list
    {
        delete m_head->m_prev;
        if (m_head->m_next != nullptr) //if the next element has not already been deleted
        {
            m_head = m_head->m_next;
        }
        else{
            delete m_head;
            break;
        }
    }
    
    //use the default constructor to make a new Node
    m_head = new Node;
    m_size = 0;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
    
    Node* a = m_head;
    
    m_size = rhs.size();
    Node* b = rhs.m_head;
    for (int i = 0; i < m_size; i++) //copy rhs into the new list
    {
        a->m_next = new Node;
        a->m_next->m_key = b->m_next->m_key;
        a->m_next->m_value = b->m_next->m_value;
        a->m_next->m_prev = a;
        a = a->m_next;
        b = b->m_next;
    }
    a->m_next = m_head;
    m_head->m_prev = a;
    
    return *this;
    
}

bool Map::empty() const //test if the Map is empty
{
    if (m_size == 0)
    {
        return true;
    }
    return false;
}

int Map::size() const // return the size of the Map
{
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value) // insert the pair into the Map if there's no such key before
{
    if (!contains(key)) {
        Node* a = m_head->m_prev; //find the end of the list
        a->m_next = new Node; //append a new Node
        a->m_next->m_key = key;
        a->m_next->m_value = value;
        a->m_next->m_prev = a;// link the new Node into the list
        a->m_next->m_next = m_head;
        m_head->m_prev = a->m_next;
        m_size++;
        return true;
    }
    return false;
    

}

bool Map::update(const KeyType& key, const ValueType& value) //update the value of the pair that contains key if there is such pair in the Map
{
    if (contains(key)) {
        Node* a = m_head;
        for (int i = 0; i < size(); i++) {
            a = a->m_next;
            if (a->m_key == key) {
                break; //found equal keys, break out of the for-loop
            }
        }
        a->m_value = value;
        return true;
    }
    return false;
    

}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) // a combination of insert and update
{
    if (contains(key)) {
        Node* a = m_head;
        for (int i = 0; i < size(); i++) // to find the pair that contains key
        {
            a = a->m_next;
            if (a->m_key == key) {
                break;
            }
        }
        a->m_value = value;
    }
    else{
        Node* a = m_head;
        for (int i = 0; i < size(); i++) // to find the end of the list
        {
            a = a->m_next;
        }
        a->m_next = new Node;
        a->m_next->m_key = key;
        a->m_next->m_value = value;
        a->m_next->m_prev = a;
        a->m_next->m_next = m_head;
        m_head->m_prev = a->m_next;
        m_size++;
    }
    return true;
    
}

bool Map::erase(const KeyType& key)
{
    if (contains(key)) {
        Node* a = m_head;
        for (int i = 0; i < size(); i++)// to find the pair that contains the key
        {
            a = a->m_next;
            if (a->m_key == key) {
                break; //found, then get out of the for-loop
            }
        }
        a->m_prev->m_next = a->m_next;
        a->m_next->m_prev = a->m_prev;
        delete a;
        m_size--;
        return true;
    }
    else
        return false;
    
}

bool Map::contains(const KeyType& key) const
{
    Node* a = m_head;
    for (int i = 0; i < size(); i++) // to see if there is such key in the pairs of the Map
    {
        a = a->m_next;
        if (a->m_key == key) {
            return true;
        }
    }
    return false;
    
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    Node* a = m_head;
    for (int i = 0; i < size(); i++) // to see if there is and where there is such key in the Map
    {
        a = a->m_next;
        if (a->m_key == key) {
            value = a->m_value;
            return true;
        }
    }
    return false;
    
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i >= 0 && i < size()) {
        Node* a = m_head;
        for (int h = 0; h <= i; h++) // to find the pair that i represents in the list
        {
            a = a->m_next;
        }
        key = a->m_key;
        value = a->m_value;
        return true;
    }
    return false;
    
}

void Map::swap(Map& other)
{
    int a = m_size;
    m_size = other.m_size;
    other.m_size = a;
    //swap the m_size of the two
    
    Node* b = m_head;
    m_head = other.m_head;
    other.m_head = b;
    //swap the m_head of the two
    
    
}

void Map::dump() const{
    Node* a = m_head->m_next;
    for (int i = 0; i < m_size; i++) {
        cerr << a->m_key << " " << a->m_value << endl;
        a = a->m_next;
    }
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
    Map newResult = Map();
    
    int r = 0; //keeping track of whether there's conflict in equal keys
    for (int i = 0; i < m1.size(); i++) {
        int a = 0; //keeping track of whether the two keys equal
        KeyType b;
        ValueType c;
        m1.get(i,b,c);
        for (int h = 0; h < m2.size(); h++) {
            KeyType d;
            ValueType e;
            m2.get(h,d,e);
            if (b == d) {
                a = 1; // there are two keys that are equal
                if (c == e) {
                    newResult.insert(b, c);
                }
                else
                    r = 1; //there are conflict in equal keys
            }
        }
        if (a != 1) {
            newResult.insert(b, c);
        }
    }
    for (int i = 0; i < m2.size(); i++) {
        int z = 0; //keeping track of whether two keys are equal
        KeyType b;
        ValueType c;
        m2.get(i, b, c);
        for (int h = 0; h <= m1.size(); h++) {
            KeyType d;
            ValueType e;
            m1.get(h, d, e);
            if (b == d) {
                z = 1;// there are two keys that are equal
            }
        }
        if (z != 1) {
            newResult.insert(b, c);
        }
    }
    
    result = newResult;
    if (r == 1) //there are conflicts
    {
        return false;
    }
    return true;
    
    
}
void subtract(const Map& m1, const Map& m2, Map& result)
{
    Map newResult = Map();
    
    for (int i = 0; i < m1.size(); i++) {
        int a = 0; //keeping track of equal keys
        KeyType b;
        ValueType c;
        m1.get(i,b, c);
        for (int h = 0; h < m2.size(); h++) {
            KeyType d;
            ValueType e;
            m2.get(h, d,e);
            if (b == d) {
                a = 1; //there are equal keys
            }
        }
        if (a != 1)
        {
            newResult.insert(b, c);
        }
    }
    
    result = newResult; //replace result by newResult
}






