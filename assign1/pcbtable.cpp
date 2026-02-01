/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author ??? (TODO: your name)
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   table.resize(size);              //set table to desired size
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
    for (int i = 0; i < table.size(); i++) {
        if (table[i] != nullptr) {      //if the index contains a pointer
            delete table[i];            //free memory
            table[i] = nullptr;         //get rid of possible dangler
        }
    }
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    if (idx >= table.size()) {  //if index is out of bounds (or empty)
        return nullptr;         //return nullptr
    }
    return table[idx];          //otherwise return a valid pointer
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {

    //Case 1: Pointer is null/Index is invalid/Pointer is a duplicate at the index
    if (pcb == nullptr || idx >= table.size() || pcb == table[idx]) { 
        return;
    }

    //Case 2: Index already contains a pointer
    if (table[idx] != nullptr) {
        delete table[idx];          //remove existing pointer
        table[idx] = pcb;           //assign new pointer
    } else {
        //Case 3: Index is unoccupied
        table[idx] = pcb;
    }
}