#include "Node.hpp"

std::ostream& operator<<(std::ostream& os, const Node& node) {
  os << "node: { data: " << node.data << ", next: ";
  os << (node.next ? std::to_string(node.next->data) : "nullptr");
  os << ", prev: ";
  os << (node.prev.lock() ? std::to_string(node.prev.lock()->data) : "nullptr");
  return os << " }";
}

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Node>& node) {
  if(node) {
    os << "*{ " << *node << " }";
  } else {
    os << "nullptr";
  }
  return os;
}
