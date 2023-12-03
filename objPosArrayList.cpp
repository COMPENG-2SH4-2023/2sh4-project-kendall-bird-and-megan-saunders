#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

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
    delete[] aList; // use delete[] to call the destructors of all instances in the array (otherwise memory leak - only 1st element will be properly deleted)
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // ADD IN CODE:
    // still need error check - what if listSize is at capacity?
    // check if listSize is equal to arrayCapacity.
    // if yes, at capacity,don't insert.

    if(listSize == arrayCapacity)
    {
        return;
    }
    
    for(int i = listSize; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]); // this will shuffle all the elements toward the tail
    }

    aList[0].setObjPos(thisPos);

    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[listSize++] = thisPos;
}

void objPosArrayList::removeHead()
{
    for(int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];  // shuffling towards the head
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    listSize--; 
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize -1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}