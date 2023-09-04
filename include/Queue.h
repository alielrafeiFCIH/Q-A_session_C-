#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue 
{
	T *arr; 		
	int capacity;   
	int f;  	
	int rear;   	
	int count;  	

    public:
        Queue(int size);			
        void pop();
        void push(T x);
        T& front();
        int size();
        bool empty();
        bool isFull();
};

template <class T>
Queue<T>::Queue(int size){
	arr = new T[size];
	capacity = size;
	f = 0;
	rear = -1;
	count = 0;
}


template <class T>
void Queue<T>::pop(){
	
	if (empty()){
		// do nothing
	}else{
        f = (f + 1) % capacity;
        count--;
    }

}


template <class T>
void Queue<T>::push(T item){
	if (isFull()){
		//do nothing
	}else{
        rear = (rear + 1) % capacity;
        arr[rear] = item;
        count++;
    }
	
}


template <class T>
T& Queue<T>::front(){
	if (empty()) {
		// do nothing
	}else{
        return arr[f];
    }
	
}


template <class T>
int Queue<T>::size(){
	return count;
}


template <class T>
bool Queue<T>::empty(){
	return (size() == 0);
}


template <class T>
bool Queue<T>::isFull(){
	return (size() == capacity);
}
#endif // QUEUE_H
