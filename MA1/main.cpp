// This code was taken from https://www.techiedelight.com/queue-implementation-cpp/
// The code has been modified from the original to provide opportunities to learn
/*ATTRIBUTES
    1. Using an array means that your queue cannot be resized, leading to problems like having a full-queue 
    2. The only way to add nodes to the queue is by calling enqueue since the array is a private member with no other 
    modfifiers such as setters, this means that you need to use enqueue in other test cases which is bad practice.
    If enqueue does not work, you cannot test other functions which require populated queues to properly test. To fix this,
    create another way to populate the queue that does not involve using a funciton
    3. When enqueuing an dequeing, the index of each element gets adjusted, so while the time complexity is O(1), 
    the space complexity is different
    4. The deconstructor of queue.h should use delete[] instead of delete since you want to deallocate the whole array
    this causes a memory leak
    5. Using std::numberic_limits<int>::min() is bad practice since it returns an int that could be an 
    element of arr depending on what is stored, although it is unlikely this will happen because ints are stored in 32-bits
    so the minimum number is (2^31)-1. Better practice would be to throw an exception 


*/
#include "queue.h"
#include "testQueue.cpp"

// main function
int main()
{
    // call your test functions here!
    testQueue test;
    test.testSize();
    test.testisEmpty();
    test.testisFull();

    test.testdequeueEmpty();
    test.testdequeue2Nodes();

    test.testenqueueFull();
    test.testenqueue();

    test.testpeekEmpty();
    test.testpeek2Nodes();
    return 0;
}

