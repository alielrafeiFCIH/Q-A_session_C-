#ifndef STACK_H
#define STACK_H
#define SIZE 300
template<class X>
class Stack
{   
    X *arr;
	int peak;
	int capacity;
    public:
        Stack();
        Stack(int size);
        void push(X);
        void pop();
        X top();
        bool isFull();
        int size();
        bool empty();
   
};
template <class X>
Stack<X>::Stack()
{
    arr = new X[SIZE];
	capacity = SIZE;
	peak = -1;
    //ctor
}
template <class X>
Stack<X>::Stack(int size){
	arr = new X[size];
	capacity = size;
	peak = -1;
}
template <class X>
void Stack<X>::push(X x)
{
	if(isFull()){
		
	}else{
        arr[++peak] = x;
    }
	
}
template <class X>
void Stack<X>::pop()
{
	if(!empty()){
		peak--;
	}
	
}
template <class X>
X Stack<X>::top(){
	if (!empty())
		return arr[peak];
	
}
template <class X>
int Stack<X>::size()
{
	return peak + 1;
}
template <class X>
bool Stack<X>::isFull(){
	return peak == capacity - 1;	
}
template <class X>
bool Stack<X>::empty(){
	return peak == - 1;	
}


#endif // STACK_H
