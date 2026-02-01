#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue()  {
     capacity = 100;
     ctr = 0;
     queue = new PCB*[capacity];
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    //TODO: add your code to release dynamically allocate memory
}

/**
* @brief Resizes the queue 
*/
void ReadyQueue::resize() {
    int newCapacity = (capacity * 2); //calculate new size
    PCB** newQueue = new PCB*[newCapacity]; //allocate new array

    for (int i = 0; i < ctr; i++) {
        newQueue[i] = queue[i];             //copy over existing pointers
    }

    delete[] queue;                         //delete old queue
    queue = newQueue;                           
    capacity = newCapacity;
}

/**
* @brief Restores the max heap property after adding an item
*/
void ReadyQueue::heapifyUp(int idx) {
    
    int current = idx; //current index
    //Base case 1: Current is the root
    if (current == 0) {
        return;
    }
    
    int parent = (current - 1) / 2; //parent index
    //Base case 2: Current is less than/equal to the parent
    if (queue[current]->priority <= queue[parent]->priority) { 
        return;
    }

    //Current is larger than the parent. Swap them.
    PCB* temp = queue[parent]; //save a pointer to the parent
    queue[parent] = queue[current];
    queue[current] = temp;

    //Recursive call up with new base index
    heapifyUp(parent);
}

/**
* @brief Restores the max heap property after removing an item
*/
void ReadyQueue::heapifyDown(int idx) {
    
    int current = idx; //current index (parent)
    int left = (2 * current) + 1; //left child index
    int right = (2 * current) + 2; //right child index

    //Base case 1: No children exist (check against left child index)
    if (left >= ctr) {
        return;
    }

    int child;
    if (right >= ctr) { //If the right child does not exist, default to the left child
        child = left;
    } else {
        child = (queue[left]->priority > queue[right]->priority ? left : right); //Otherwise, get the index of the higher priority child
    }

    //Base case 2: Child is less than or equal to current (parent)
    if (queue[child]->priority <= queue[current]->priority) {
        return;
    }

    //Current is smaller than it's largest child. Swap them
    PCB* temp = queue[child]; //save a pointer to the child
    queue[child] = queue[current];
    queue[current] = temp;

    //Recursive call down with new base index
    heapifyDown(child);
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    //TODO: add your code here
    // When adding a PCB to the queue, you must change its state to READY.
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    //TODO: add your code here
    // When removing a PCB from the queue, you must change its state to RUNNING.
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return ctr;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    //TODO: add your code here
}