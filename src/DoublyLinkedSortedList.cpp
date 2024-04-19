#include "DoublyLinkedSortedList.hpp"
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <thread>

std::ostream& operator<<(std::ostream& os, const DoublyLinkedSortedList& list) {
  os << "list : {\n";
  os << "  head: " << list.head << ",\n";
  os << "  tail: " << list.tail.lock() << ",\n";
  return os << "}\n";
}

struct DebugLogger {
  static void logAddingValue(int num) {
#ifdef DEBUG
    std::cout << "Adding value: " << num << '\n';
#endif
  }

  static void logAddingNodeToNonEmptyList() {
#ifdef DEBUG
    std::cout << "List is not empty. Adding node in the correct position.\n";
#endif
  }


  static void logAddingNodeToEmptyList() {
#ifdef DEBUG
    std::cout << "List is empty. Adding node as head and tail.\n";
#endif
  }


  static void logInsertingNodeInMiddle() {
#ifdef DEBUG
    std::cout << "Inserting node in the middle of the list." << '\n';
#endif
  }

  static void logInsertingNodeAtHead() {
#ifdef DEBUG
    std::cout << "Inserting node at the head of the list." << '\n';
#endif
  }

  static void logInsertingNodeAtTail() {
#ifdef DEBUG
    std::cout << "Inserting node at the tail of the list." << '\n';
#endif
  }

  static void logRecursivelyCallingInsertFromLeft() {
#ifdef DEBUG
    std::cout << "Recursively calling insertFromLeft()." << '\n';
#endif
  }

  static void logRecursivelyCallingInsertFromRight() {
#ifdef DEBUG
    std::cout << "Recursively calling fromRight." << '\n';
#endif
  }

  static void logFinishedAddingValue(const DoublyLinkedSortedList& list,
                                     int num) {
#ifdef DEBUG
    std::cout << "Finished adding value: " << num << '\n';
    std::cout << "After adding: " << list << '\n';
#endif
  }
};

void DoublyLinkedSortedList::addValue(int num) {
  std::shared_ptr<Node> newNode = std::make_shared<Node>(num);
  if (empty()) {
    addNodeToEmptyList(newNode);
  } else {
    addNodeToNonEmptyList(newNode, num);
  }
  DebugLogger::logFinishedAddingValue(*this, num);
}

void DoublyLinkedSortedList::addNodeToEmptyList(
  const std::shared_ptr<Node>& newNode) {
  DebugLogger::logAddingNodeToEmptyList();
  head = newNode;
  tail = newNode;
}

void DoublyLinkedSortedList::addNodeToNonEmptyList(
  const std::shared_ptr<Node>& newNode,
  int num) {
  DebugLogger::logAddingNodeToNonEmptyList();
  std::mutex insertNodeMutex;
  bool isInserted = false;

  std::jthread fromLeftThread(&DoublyLinkedSortedList::insertFromLeft,
                              this,
                              head,
                              newNode,
                              num,
                              std::ref(insertNodeMutex),
                              std::ref(isInserted));
  std::jthread fromRightThread(&DoublyLinkedSortedList::insertFromRight,
                               this,
                               tail.lock(),
                               newNode,
                               num,
                               std::ref(insertNodeMutex),
                               std::ref(isInserted));
}

void DoublyLinkedSortedList::insertFromLeft(

  const std::shared_ptr<Node> node,
  const std::shared_ptr<Node>& newNode,
  int num,
  std::mutex& insertNodeMutex,
  bool& isInserted) {
  if (!node or isInserted) { return; }
  if (num <= node->data) {
    if (insertNodeMutex.try_lock()) {
      isInserted = true;
      newNode->next = node;
      if (node->prev.lock()) {
        DebugLogger::logInsertingNodeInMiddle();
        node->prev.lock()->next = newNode;
        newNode->prev = node->prev; // assigning weakPtr to weakPtr???
      } else {
        DebugLogger::logInsertingNodeAtHead();
        head = newNode;
      }
      node->prev = newNode;
    }
  } else {
    DebugLogger::logRecursivelyCallingInsertFromLeft();
    insertFromLeft(node->next, newNode, num, insertNodeMutex, isInserted);
  }
}

void DoublyLinkedSortedList::insertFromRight(
  const std::shared_ptr<Node> node,
  const std::shared_ptr<Node>& newNode,
  int num,
  std::mutex& insertNodeMutex,
  bool& isInserted) {
  if (!node or isInserted) { return; }
  if (node->data <= num) {
    if (insertNodeMutex.try_lock()) {
      isInserted = true;
      newNode->prev = node;
      if (node->next) {
        DebugLogger::logInsertingNodeInMiddle();
        newNode->next = node->next;
        node->next->prev = newNode;
      } else {
        DebugLogger::logInsertingNodeAtTail();
        tail = newNode;
      }
      node->next = newNode;
    }
  } else {
    DebugLogger::logRecursivelyCallingInsertFromRight();
    insertFromRight(
      node->prev.lock(), newNode, num, insertNodeMutex, isInserted);
  }
}

/**
 * @param node cannot be nullptr, must be dereferencable
 */
void DoublyLinkedSortedList::showLeftToRightHelper(
  const std::shared_ptr<Node>& node) {
  std::cout << node->data;
  if (node->next) {
    std::cout << ", ";
    showLeftToRightHelper(node->next);
  } else {
    return;
  }
}

/**
 * @param node cannot be nullptr, must be dereferencable
 */
void DoublyLinkedSortedList::showRightToLeftHelper(
  const std::weak_ptr<Node>& node) {
  std::cout << node.lock()->data;
  if (node.lock()->prev.lock()) {
    std::cout << ", ";
    showRightToLeftHelper(node.lock()->prev);
  } else {
    return;
  }
}

void DoublyLinkedSortedList::showLeftToRight() {
  std::cout << "H{ ";
  if (head) { showLeftToRightHelper(head); }
  std::cout << " }T\n";
}

void DoublyLinkedSortedList::showRightToLeft() {
  std::cout << "T{ ";
  if (tail.lock()) { showRightToLeftHelper(tail); }
  std::cout << " }H\n";
}

int DoublyLinkedSortedList::sizeHelper(
  const std::shared_ptr<Node>& node,
  int acc = 1) { // NOLINT(misc-no-recursion)
  // NOLINT(misc-no-recursion) to shut up linter (clang-tidy/CSA) about
  // recursive function
  if (bool(node->next)) { // if next is a valid node
    return sizeHelper(node->next, ++acc);
  } else { // if next is nullptr
    return acc;
  }
}

int DoublyLinkedSortedList::size() {
  if (empty()) { return 0; }
  return sizeHelper(head);
}

int DoublyLinkedSortedList::front() {
  if (empty()) { // in std::list calling front on an empty container causes
                 // undefined behavior
    return std::numeric_limits<int>::min(); // arbitrary chosen value
  } // https://en.cppreference.com/w/cpp/container/list/front
  return head->data;
}

int DoublyLinkedSortedList::back() {
  if (empty()) { // in std::list calling back on an empty container causes
                 // undefined behavior
    throw std::runtime_error("Cannot call back() on an empty list");
  } // https://en.cppreference.com/w/cpp/container/list/back
  if (!tail.lock()) {
    throw std::runtime_error(
      "Calling back(), non-empty list but tail = nullptr!");
  }
  return tail.lock()->data;
}

/**
 * deletes all nodes, leaves list with no nodes
 * mem dealloc thanks to RAII, smart pointers
 */
void DoublyLinkedSortedList::removeList() {
  head = nullptr;
  tail = head;
}
