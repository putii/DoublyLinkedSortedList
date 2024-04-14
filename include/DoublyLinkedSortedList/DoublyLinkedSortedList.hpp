#ifndef SONB_HOMEWORKS_DOUBLYLINKEDSORTEDLIST_H
#define SONB_HOMEWORKS_DOUBLYLINKEDSORTEDLIST_H

#include  <memory>
#include "Node.hpp"

class DoublyLinkedSortedList {
    std::shared_ptr<Node> head;
    std::weak_ptr<Node> tail;

    void showLeftToRightHelper(const std::shared_ptr<Node>& node);
    void showRightToLeftHelper();
    int sizeHelper(const std::shared_ptr<Node>&, int);
public:
    DoublyLinkedSortedList(); // how do I want to construct it?
    void addValue(int);
    void removeList();
    void showRightToLeft();
    void showLeftToRight();
    bool empty() { return !bool(head); }
    int size();

    /**
     * getHead
     * @return *head
     */
    int front(); // getHead?

    /**
     * getTail
     * @return *tail
     */
    int back(); // getTail?


    // ~DoublyLinkedSortedList(); // i do need to implement it as I will need to allocate memory or stuff like that
    // or maybe I should use smartPointers or leave memory allocation to Nodes themselves ?
    // I may want to write all member funcitons recursively
};


#endif //SONB_HOMEWORKS_DOUBLYLINKEDSORTEDLIST_H
