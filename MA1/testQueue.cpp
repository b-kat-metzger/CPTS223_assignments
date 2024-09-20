#pragma once
#include "testQueue.hpp"

/* Test ID: Test size - TS
Unit: queue::size()
Description: Test to determine if size() returns the proper size of a queue
Test steps:
    1. Construct a queue object (we will construct with size of 5)
    2. Invoke queue::size()
    3. Conditionally evaluate whether return of queue::size()==n
Test data: n=2
Precondition: queue object has initial size 
Postcondition: queue object will remain unchanged;2 should be returned by queue::size()
Expected result: size=2
Actual result: size =3  
Status: FAILED
*/
void testQueue::testSize()
{
    cout << "testSize(): " <<endl;
    int n = 2;
    queue test(5);
    test.enqueue(2);
    test.enqueue(1);
    if(test.size()==n){
        cout <<"    Test passed. Size is equal to input size n" << endl;
    }
    else{
        cout <<"    Test failed. Size is NOT equal to input size n, Size:"<<test.size() <<endl;
    }
}

/* Test ID: Empty queue check - EQC
Unit: queue::isEmpty()
Description: Test to determine if isEmpty() returns 1 if a queue object is empty
Test steps:
    1. Construct an empty queue object
    2. Invoke queue::isEmpty()
    3. Conditionally evaluate the value returned by queue::isEmpty()
Test data: size = 0;
Precondition: queue object is empty
Postcondition: queue object remains unchanged
Excpected result: queue is empty; 1 is returned
Actual result: Did not return 1, due to size failing
Status: FAILED
*/
void testQueue::testisEmpty()
{
    cout << "testisEmpty():" <<endl;
    queue test(0);
    if(test.isEmpty()==1){
        cout << "   Test passed. isEmpty() returned 1 for an empty queue" << endl;
    } 
    else{
        cout << "   Test failed. isEmpty() did NOT return 1 for an empty queue" <<endl;
    }
}

/*Test ID: Full queue check - FQC
Unit: queue:isFull()
Description: Test to determine if isFull() returns 1 if a queue object is full
Test steps:
    1. Construct a queue of size 3
    2. Populate queue with three nodes to make queue full
    3. Invoke queue::isFull()
    4. Conditionally evaluate the value returned by queue::isFull()
Test data: size = 3;
Precondition: Queue has already been populated
Postcondition: queue remains unchanged
Expected result: queue is full; 1 is returned
Actual result: Returned 1
Status: PASSED
*/ 
void testQueue::testisFull()
{
    cout << "testisFull()"<<endl;
    queue test(3);
    test.enqueue(3);
    test.enqueue(2);
    test.enqueue(1);

    if(test.isFull()==1){
        cout <<"    Test passed. isFull() returned 1 for a full queue"<<endl;
    }
    else{
        cout << "   Test failed. isFull() did NOT return 1 for a full queue"<<endl;
    }
}

/*Test ID: Empty queue Dequeue - EQDq
Unit: queue::dequeue()
Description: Test to determine if dequeue will not attempt a dequeue on an empty queue object
Test steps:
    1. Construct a queue of size 3
    2. Invoke queue::dequeue()
    3. Determine if error message is printed and function terminates before it attempts to modify the test queue
Precondition: Queue is empty
Postcondition: Queue remains empty and has not been modified as to where a crash would occur
Expected result: queue::dequeue() will terminate before modification
Actual result: Attempted to dequeue non-existing node, failed due to isEmpty failing
Status: FAILED
*/
void testQueue::testdequeueEmpty()
{
    cout << "testdequeueEmpty()"<<endl<<endl;
    queue test(3);
    test.dequeue();

    cout <<endl<<endl;
}

/*Test ID: Test dequeue - TDq
Unit: queue::dequeue()
Description: Test to determine if dequeue will successfully dequeue the first node of the queue
Test steps:
    1. Construct a queue of size 3
    2. Populate the queue with two nodes
    3. Invoke queue::dequeue()
    4. Determine if dequeue message states that 1 has been removed
Precondition: Queue is populated
Postcondition: One node is removed, size should be 1
Expected result: First node will be removed
Actual result: Node 1 was dequeued
Status: PASSED
*/
void testQueue::testdequeue2Nodes()
{
    cout << "testdequeue2Nodes()"<<endl;
    queue test(3);
    test.enqueue(2);
    test.enqueue(1);

    test.dequeue();

    
}

/*Test ID: Full queue enqueue - FQEq
Unit: queue::enqueue()
Description: Test to determine if enqueue will NOT attempt to enqueue to a full queue
Test steps:
    1. Construct a queue of size 3
    2. Populate the queue with three nodes so that it is full
    3. Invoke queue::enqueue(4) to insert a new node with integer -1
    4. Determine if error message is printed and function terminates before attempting to modify the test queue
Precondition: Queue is full
Postcondition: Queue remains the same and enqueue() does not attempt to add another node
Expected result: Error will be displayed, queue::enqueue() will be terminated
Actual result: Function terminated before attemping to modify, error was displayed
Status: PASSED
*/
void testQueue::testenqueueFull()
{
    cout << "testenqueueFull()" <<endl;
    queue test(3);
    test.enqueue(3);
    test.enqueue(2);
    test.enqueue(1);

    test.enqueue(-1);
}

/*Test ID: Test enqueue - TEq
Unit: queue::enqueue()
Description: Test to determine if enqueue will successfully enqueue a node
Test steps:
    1. Construct a queue of size 3
    2. Invoke queue::enqueue() to populate the queue twice
    3. By using the print statements in enqueue(), determine whether the queue successfully appended the nodes
    4. Manually check in debugging whether the indexes are correct for the nodes
Precondition: Queue is empty
Postcondition: Queue is populated with 2 nodes
Expected result: Queue is populated properly
Actual result: Successfully queued both nodes
Status: PASSED
*/
void testQueue::testenqueue()
{
    cout <<"testenqueue()" <<endl;
    queue test(3);
    test.enqueue(2);
    test.enqueue(1);
}

/*Test ID: Empty queue peek
Unit: queue::peek()
Description: Test to determine whether peek will return an error when called on an empty queue
Test steps:
    1. Construct a queue of size 3
    2. Invoke queue::peek()
    3. Determine whether the anticipated error message gets triggered and the function terminates before attempting to 
    access memorry
Precondition: Queue is empty
Postcondition: Queue is not accessed
Expected result: Error message is returned
Actual result: isEmpty() failed, therefore attempted to peek and returned 0
Status: FAILED
*/
void testQueue::testpeekEmpty()
{
    cout << "testpeekEmpty()"<<endl;
    queue test(3);
    cout << "   "<<test.peek() <<endl;
}

/*Test ID: Test peek - TP
Unit: queue::peek()
Description: Test to determine whether peek will return the front element in the queue
Test stepts:
    1. Construct a queue of size 2
    2. Populate queue with 2 elements
    3. Invoke queue::peek()
    4. Conditionally compare peek with expected value (1)
Precondition: Queue is populated
Postcondition: Queue remains unmodififed
Expected result: Peek returns 1
Actual result: Returns 1
Status: PASSED
*/
void testQueue::testpeek2Nodes()
{
    cout << "testpeek2Nodes()"<<endl;
    queue test(2);
    test.enqueue(2);
    test.enqueue(1);

    if(test.peek()==1){
        cout<<" Test passed. queue::peek() returns 1" <<endl;
    }
    else{
        cout<<" Test failed. queue::peek() did not return 1"<<endl;
    }
}
