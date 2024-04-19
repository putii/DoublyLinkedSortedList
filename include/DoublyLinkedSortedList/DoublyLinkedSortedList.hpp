#ifndef SONB_HOMEWORKS_DOUBLYLINKEDSORTEDLIST_H
#define SONB_HOMEWORKS_DOUBLYLINKEDSORTEDLIST_H

#include "Node.hpp"
#include <memory>

class DoublyLinkedSortedList {
public:
  void addValue(int);
  void removeList();
  void showRightToLeft();
  void showLeftToRight();
  bool empty() { return !bool(head); }
  int size();
  int front();
  int back();
  friend std::ostream& operator<<(std::ostream& os,
                                  const DoublyLinkedSortedList& list);
private:
  std::shared_ptr<Node> head;
  std::weak_ptr<Node> tail;
  void addNodeToEmptyList(const std::shared_ptr<Node>& newNode);
  void addNodeToNonEmptyList(const std::shared_ptr<Node>& newNode, int num);
  void insertFromLeft(const std::shared_ptr<Node> node,
                      const std::shared_ptr<Node>& newNode,
                      int num,
                      std::mutex& insertNodeMutex,
                      bool& isInserted);
  void insertFromRight(const std::shared_ptr<Node> node,
                       const std::shared_ptr<Node>& newNode,
                       int num,
                       std::mutex& insertNodeMutex,
                       bool& isInserted);
  void showLeftToRightHelper(const std::shared_ptr<Node>& node);
  void showRightToLeftHelper(const std::weak_ptr<Node>& node);
  int sizeHelper(const std::shared_ptr<Node>&, int);
};

std::ostream& operator<<(std::ostream& os,
                         const std::shared_ptr<DoublyLinkedSortedList>& list);


#endif // SONB_HOMEWORKS_DOUBLYLINKEDSORTEDLIST_H
