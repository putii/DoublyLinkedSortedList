#ifndef SONB_HOMEWORKS_NODE_H
#define SONB_HOMEWORKS_NODE_H

#include <memory>

class Node {
public:
    // this constructor may be redundant but i aint sure
    Node(int dataArg, const std::shared_ptr<Node>& nextArg, const std::weak_ptr<Node>& prevArg) : data(dataArg), next(nextArg), prev(prevArg) {}
    explicit Node(int dataArg) : data(dataArg) {};
    int data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
};

#endif //SONB_HOMEWORKS_NODE_H
