**TASK 1**

Create the most effective (the one that creates the minimum amount of additional objects) representation of Triangle with the help of its points and (or) segments. Keep track of objects. Create a function to construct a Triangle's median with the following signature: const Segment& Triangle::median(const Segment& side) const

*My comment*: From the signature const Segment & Triangle :: median (const Segment & side) const
it is clear that the median has to be stored somewhere so that it can be returned as a reference. To do this, mutable pointers to Segments (medians) are stored in Triangle. They are initialized with zeros and are calculated on first demand. If the points of the triangle are changed, then the medians will change, so after such changes, the old medians will be deleted and the pointers set to zero. The medians are mutable so that they can be calculated for a const triangle.

**TASKS 2 and 3**

2. Create class Calendar, which provides the functionality to determine day of the week by its date.

3. Add national celebrations' dates to Calendar.

*My comment*: The Calendar class contains a list of days of the week, as well as their names. It has methods that return a day from the list or a String with the name of a day by its date.

It also contains an array with the dates of national holidays of fixed size (because there is the same amount of holidays every year). The array is not static and depends on the attribute _year, since there are holidays (Easter and Trinity), whose dates depend on the year. Contains a static array of holiday names.
The class also contains methods that allow to find out whether the given date is a weekend, a holiday or a working day (not a weekend and not a holiday).

**TASKS 4 and 5**

4. Create class Alarm to signal on a particular day and time.

5. Make it possible to cancel alarm or repeat it if it's not cancelled during a particular period defined in class.

*My comment*: It would be nice to implement the alarm signal using multithreading, but we are not allowed to use C++11 or additional libraries. Therefore, the alarm is waiting to be cancelled as follows: asking the user (displays in the cin) whether he wants to cancel the signal until the user says "y" or until the timeout specified by the class settings expires. If the signal has not been canceled, it repeats itself and the wait for cancellation begins again. And so on until the signal is cancelled.

**TASK 6**

Make it possible to create an Alarm, which will signal every workday (excluding celebrations).

*My comment*: Between each signal, the Alarm sleeps for about 1 day (1 day minus the time that was spent waiting for signal's cancellation). Every day the alarm clock checks whether today's day is a workday, and if so, the signal starts. Also, every day the alarm clock checks whether it is necessary to change the calendar for another year and does when it is necessary.
Cancelling the signal cancels the signal that is being played at the moment, and not the whole alarm, the alarm will still work the next workday.

**TASK 7**

Create parameterized class Pair, which will contain Key and Value.

*My comment*: In the class Pair, there is a default constructor so that the objects of this class can be put into an array (for use in the stack), since when creating an array all its elements are initialized.
Similarly, comparison operators for pairs (by key) are implemented.

**TASK 8**

Priority Stack is a stack, which contains Pairs. Create class QuickPushPriorityStack in such a way that operation void push(const Pair&) has O(1) complexity. The last added element with highest (lowest) priority is popped.

*My comment*: Sequence (written before as a homework) was used as a container for Stack because it contains the necessary functionality.

The complexity of push operation is O(1) because it adds an element to the end of the sequence. So to perform this operation we only need to overwrite one cell of the array, which has the complexity of O(1)\*.

\* but from time to time the size of the array expands to accommodate all the elements or shrinks so that there is not to much unused space

Then for top and pop operations we have to find the desired index. The index is searched from the end of the sequence to the beginning. In the worst case, the desired element is in the beginning of the sequence, so the complexity is O(N), where N is the number of the elements in the stack.

**TASK 9**

Create class QuickTopPriorityStack in such a way that operations Value top() const і void pop() have O(1) complexity.

*My comment*: Top and pop operations have complexity O(1) because the elements are stored in the sequence in the correct order, and we need to take the last element for top or cut the sequence for pop. That is, to perform these operations, we have to either access the cell of the array, or decrement a variable (_size), the complexity of both is O(1)\*.
\* the size of the array changes from time to time

Then for the push operation, we have to find the desired index to insert a new item. The index is searched from the end of the sequence to the beginning. In the worst case, the desired element is in the beginning of the sequence, so the complexity is O(N), where N is the number the elements in the stack.

**TASK 10**

Create mutual interface for classes from tasks 8 and 9.

*My comment*: Classes from Tasks 8 and 9 have mutual Non Virtual Interface, which is free of substitutions (so that the interface functions in the derived classes can not be overridden).
I decided to use NVI in order to separate the base class' part responsible for the inheritance of the interface from the part resposible for the definition of behavior.

Base class' interface functions call private unimplemented virtual functions that will be implemented in derived classes.
