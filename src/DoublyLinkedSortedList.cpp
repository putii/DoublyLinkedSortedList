#include "DoublyLinkedSortedList.hpp"
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <thread>

DoublyLinkedSortedList::DoublyLinkedSortedList() : head(nullptr), tail(head) {}

void DoublyLinkedSortedList::addValue(int num) {
  std::shared_ptr<Node> newNode = std::make_shared<Node>(
    num); // TODO why template functions dont need template params while calling but template classes do ?
  if (empty()) {
    head = newNode;
    tail = newNode;
  } else { // non-empty list
    std::mutex myMutex;
    bool isInserted = false;


    std::function<void(const std::shared_ptr<Node>&)> fromLeft;
    fromLeft = [&isInserted, num, &newNode, &myMutex, this, &fromLeft](const std::shared_ptr<Node>& node) {
      if (!node or isInserted) { // if we are at the end of list
        return;
      }
      if (num <= node->data) {
        if (myMutex.try_lock()) { // node insertion if on successful lock acquisition
          isInserted = true;
          newNode->next = node; /// this is ok
          if (node->prev.lock()) { // if node->prev is a node - we are in middle of list
            node->prev.lock()->next = newNode;
            newNode->prev = node->prev;
          } else { // if node is a head
            head = newNode;
          }
          node->prev = newNode;
        } else { // on unsuccessful lock acquisition - fromRight already acquired, inserted
          return;
        }
      } else { // for a > node->data
        fromLeft(node->next);
      }
    };

    std::function<void(const std::shared_ptr<Node>&)> fromRight;
    fromRight = [&isInserted, num, &newNode, &myMutex, this, &fromRight](const std::shared_ptr<Node>& node) {
      if (!node or isInserted) { // if we are at the end of list
        return;
      }
      if (num >= node->data) {
        if (myMutex.try_lock()) { // node insertion if on successful lock acquisition
          isInserted = true;
          newNode->prev = node; /// this is ok
          if (node->next) { // w srdku TODO
            newNode->next = node->next;
            node->next->prev = newNode;
          } else {
            tail = newNode;
          }
          node->next = newNode;
        } else { // on unsuccessful lock acquisition - fromLeft already acquired, inserted
          return;
        }
      } else {
        fromRight(node->prev.lock());
      }
    };

    std::jthread fromLeftThread(fromLeft, head);
    std::jthread fromRightThread(fromRight, tail.lock());
  } // non-empty list
}

/**
 * @param node cannot be nullptr, must be dereferencable
 */
void DoublyLinkedSortedList::showLeftToRightHelper(const std::shared_ptr<Node>& node) {
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
void DoublyLinkedSortedList::showRightToLeftHelper(const std::weak_ptr<Node>& node) {
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
  if (head) {
    showLeftToRightHelper(head);
  }
  std::cout << " }T\n";
}

void DoublyLinkedSortedList::showRightToLeft() {
  std::cout << "T{ ";
  if (tail.lock()) {
    showRightToLeftHelper(tail);
  }
  std::cout << " }H\n";
}

int DoublyLinkedSortedList::sizeHelper(const std::shared_ptr<Node>& node, int acc = 1) { // NOLINT(misc-no-recursion)
  // NOLINT(misc-no-recursion) to shut up linter (clang-tidy/CSA) about recursive function
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
  if (empty()) { // in std::list Calling front on an empty container causes undefined behavior
    return std::numeric_limits<int>::min(); // arbitrary chosen value
  } // https://en.cppreference.com/w/cpp/container/list/front
  return head->data;
}

int DoublyLinkedSortedList::back() {
  if (empty()) { // in std::list calling back on an empty container causes undefined behavior
    return std::numeric_limits<int>::min(); // arbitrary chosen value
  } // https://en.cppreference.com/w/cpp/container/list/back
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



