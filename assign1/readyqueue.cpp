#include <iostream>
#include "readyqueue.h"

using namespace std;


/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue()  {
     capacity = 100;
     ctr = 0;
     pQueue = new PCB*[capacity];
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    for (int i = 0; i < ctr; i++) {
        pQueue[i] = nullptr;
    }
    delete[] pQueue;
}

/**
* @brief Resizes the pQueue 
*/
void ReadyQueue::resize() {
    int newCapacity = (capacity * 2); //calculate new size
    PCB** newQueue = new PCB*[newCapacity]; //allocate new array

    for (int i = 0; i < ctr; i++) {
        newQueue[i] = pQueue[i];             //copy over existing pointers
    }

    delete[] pQueue;                         //delete old pQueue
    pQueue = newQueue;                           
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
    if (pQueue[current]->priority <= pQueue[parent]->priority) { 
        return;
    }

    //Current is larger than the parent. Swap them.
    PCB* temp = pQueue[parent]; //save a pointer to the parent
    pQueue[parent] = pQueue[current];
    pQueue[current] = temp;

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
        child = (pQueue[left]->priority > pQueue[right]->priority ? left : right); //Otherwise, get the index of the higher priority child
    }

    //Base case 2: Child is less than or equal to current (parent)
    if (pQueue[child]->priority <= pQueue[current]->priority) {
        return;
    }

    //Current is smaller than it's largest child. Swap them
    PCB* temp = pQueue[child]; //save a pointer to the child
    pQueue[child] = pQueue[current];
    pQueue[current] = temp;

    //Recursive call down with new base index
    heapifyDown(child);
}

/**
 * @brief Add a PCB representing a process into the ready pQueue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {

    //Validate the pointer
    if (pcbPtr == nullptr) { 
        return;
    }

    //Validate Status: Do not accept a READY PCB (duplicate)
    if (pcbPtr->getState() == ProcState::READY) {
        return;
    }

    //Resize if at capacity
    if (ctr == capacity) {
        resize();
    }

    pcbPtr->setState(ProcState::READY); //Set the PCB status to READY
    pQueue[ctr] = pcbPtr;                //Add the PCB to the pQueue
    heapifyUp(ctr);                     //Restore the max heap property
    ctr++;                              //Increase the count of items in the pQueue
}

/**
 * @brief Remove and return the PCB with the highest priority from the pQueue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    
    //Check for empty pQueue 
    if (ctr == 0) {
        return nullptr;
    }

    PCB* temp = pQueue[0];               //Save a pointer to the head
    pQueue[0] = pQueue[ctr - 1];          //Move last item to the head
    pQueue[ctr - 1] = nullptr;           //Clean
    ctr--;                              //Decrease the count of items in the pQueue
    heapifyDown(0);                     //Restore the max heap property
    temp->setState(ProcState::RUNNING); //Update the state of the removed PCB
    return temp;                        //Return pointer to the removed PCB
}

/**
 * @brief Returns the number of elements in the pQueue.
 *
 * @return int: the number of PCBs in the pQueue
 */
int ReadyQueue::size() {
    return ctr;
}

/**
 * @brief Display the PCBs in the pQueue.
 */
void ReadyQueue::displayAll() {
    for (int i = 0; i < ctr; i++) {
        if (pQueue[i] != nullptr) {
            pQueue[i]->display();
        }
    }
}