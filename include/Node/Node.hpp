#ifndef SONB_HOMEWORKS_NODE_H
#define SONB_HOMEWORKS_NODE_H

#include <memory>
#include <iostream>

class Node {
public:
    Node(int dataArg, const std::shared_ptr<Node>& nextArg, const std::weak_ptr<Node>& prevArg) : data(dataArg), next(nextArg), prev(prevArg) {}
    explicit Node(int dataArg) : data(dataArg) {};
    int data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
};

std::ostream& operator<<(std::ostream& os, const Node& node);
std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Node>& node);

#endif //SONB_HOMEWORKS_NODE_H
