#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // 256 elements on heap
    listSize = 0; //no valid element in list upon start up
    arrayCapacity = ARRAY_MAX_CAP; // array capacity should be max
}

objPosArrayList::~objPosArrayList()
{
    // use delete[] to call the destructors of all instances in the array 
    // (otherwise memory leak - only 1st element will be properly deleted)
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // check if listSize is equal to arrayCapacity. 
    // If it is at capacity, don't insert head:
    if(listSize == arrayCapacity)
    {
        return;
    }
    
    for(int i = listSize; i > 0; i--)
    {
        // this will shuffle all the elements toward the tail
        aList[i].setObjPos(aList[i-1]);
    }

    // Set the new head at the beginning of the list
    aList[0].setObjPos(thisPos);

    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // Add a new element at the end of the list and increment the size
    aList[listSize++] = thisPos;
}

void objPosArrayList::removeHead()
{
    // Shift all elements toward the head to remove the first element
    for(int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];  // shuffling towards the head
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    // Decrement the list size to effectively remove the last element
    listSize--; 
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    // Get the objPos of the first element in the list
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    // Get the objPos of the last element in the list
    returnPos.setObjPos(aList[listSize -1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    // Get the objPos at the specified index in the list
    returnPos.setObjPos(aList[index]);
}