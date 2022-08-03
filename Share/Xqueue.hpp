//
// Created by chou on 22-8-1.
//

#ifndef XSCRIPT2_XQUEUE_HPP
#define XSCRIPT2_XQUEUE_HPP

#include <cstddef>

namespace XScript2 {
    template<typename T>
    struct xqueue_node {
        xqueue_node<T> *next;
        T node;

        xqueue_node() : next(nullptr), node() {}

        xqueue_node(xqueue_node<T> *p, const T &c) : next(p), node(c) {}
    };

    /**
     * @biref A queue implementation for replacing STL
     * @note C++ STL std::queue woqunimabi, caonimageshabiwanyi. Son of a bitch.
     */
    template<typename T>
    class xqueue {
        size_t size;
        /**
         * the tail of queue
         */
        xqueue_node<T> *first;
        /**
         * the head of queue
         */
        xqueue_node<T> *last;
    public:
        void push(const T &node);

        void pop();

        T &front();

        bool empty();

        xqueue();

        ~xqueue();
    };

    template<typename T>
    void xqueue<T>::push(const T &node) {
        auto f = new xqueue_node<T>(nullptr, node);
        if (!size) {
            first = last = f;
        } else {
            last->next = f;
            last = f;
        }
        size++;
    }

    template<typename T>
    void xqueue<T>::pop() {
        if (size) {
            auto *ele = first;
            first = first->next;
            size--;
            delete ele;
        } else {
            throw std::out_of_range("xqueue<T>::pop() expected at least 1 element in queue.");
        }
    }

    template<typename T>
    T &xqueue<T>::front() {
        return first->node;
    }

    template<typename T>
    xqueue<T>::xqueue() : size(0) {

    }

    template<typename T>
    bool xqueue<T>::empty() {
        return !size;
    }

    template<typename T>
    xqueue<T>::~xqueue() {
        if (size) {
            auto nxt = first->next;
            while (first) {
                nxt = nxt->next;
                delete first;
                first = nxt;
            }
        }
    }
} // XScript2

#endif //XSCRIPT2_XQUEUE_HPP
