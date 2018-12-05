#include "Deque.h"
#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace std;


Deque::Deque( const Deque& dq ){
    if( dq.current_size == 0 ){
        left_p = NULL;
        right_p = NULL;
        cursor = NULL;
        current_size = 0;
    }
    else if( dq.current_size == 1 ){
        int temp_data;
        node * point;
        node * p1;
        point = dq.left_p;
        temp_data = point->data;
        p1 = new node(temp_data,NULL,NULL);
        left_p = p1;
        cursor = p1;
        right_p = p1;
        current_size = 1;
    }
    else{
        int temp_data;
        node * point;
        node * p1, * p2;
        point = dq.left_p;
        temp_data = point->data;
        p1 = new node(temp_data,NULL,NULL);
        left_p = p1;
        point = point->next;
        current_size = 1;
        while( point != NULL ){
            temp_data = point -> data;
            p2 = new node(temp_data,p1,NULL);
            p1->next = p2;
            p1 = p2;
            if( dq.cursor == point ){
                cursor = p2;
            }
            if( dq.right_p == point ){
                right_p = p2;
            }
            point = point->next;
            current_size++;
        }
    }
}
Deque::~Deque(){
    node *temp = left_p;
    while (temp != NULL){
        left_p = left_p->next;
        delete temp;
    }
}

Deque::Deque(){
    left_p = NULL;
    right_p = NULL;
    current_size = 0;
    cursor = NULL;
}

void Deque::push_left(int item){
    if (empty()){//check if deque is empty
        node *PushLeft = new node(item,NULL,NULL);
        left_p = PushLeft;
        right_p = PushLeft;
        cursor = PushLeft;
        current_size = 1;
    }
    else{
        node *PushLeft = new node(item,NULL,left_p); //make a new node
        
        left_p -> prev = PushLeft;//make old left prev point at new node
        PushLeft ->next = left_p;////new node has next pointer pointing at old left
        left_p = PushLeft;//left_p is now on the newest node
        current_size++;
    }
}

void Deque::push_right(int item){
    if (empty()){//check if deque is empty
        node *PushRight = new node(item,NULL,NULL);
        left_p = PushRight;
        right_p = PushRight;
        cursor = PushRight;
        current_size =1;
    }
    else{
        node *PushRight = new node(item,right_p,NULL); //make a new node
        
        right_p -> next = PushRight;//make old right prev point at new node
        PushRight ->prev = right_p;////new node has prev pointer pointing at old right
        right_p = PushRight;//right_p is now on the newdest node
        current_size++;
    }
}

int Deque::pop_left(){
    if (empty()){//check if its empty
        return false;
    }
    else if (size() == 1){
        int temp_data = 0;
        node* temp = left_p;
        left_p = NULL;
        right_p = NULL;
        cursor = NULL;
        current_size--;
        temp_data = temp->data;
        delete temp;
        return temp_data;
    }
    else if (size() == 2){
        int temp_data = 0;
        node *temp = left_p;
        left_p = right_p;
        left_p->prev = NULL;
        cursor = right_p;
        current_size--;
        temp_data = temp -> data;
        delete temp;
        return temp_data;
    }
    else{
       int temp_data = 0;
       node *temp = left_p;// temp pointer = left
       left_p = left_p->next;//left = next left
       left_p->prev = NULL;//make the prev pointer point to null
       if (temp == cursor){
           cursor_right();
       }
       current_size--;
       temp_data = temp->data;
       delete temp;
       return temp_data;
    }
}

int Deque::pop_right(){
    if (empty()){//check if its empty
        return false;
    }
    else if (size() == 1){
        int temp_data = 0;
        node*temp = right_p;
        left_p= NULL;
        right_p = NULL;
        cursor = NULL;
        current_size--;
        temp_data = temp->data;
        delete temp;
        return temp_data;
    }
    else if ( size() == 2 ){
        int temp_data = 0;
        node *temp = right_p;
        right_p = left_p;
        right_p->next = NULL;
        cursor = left_p;
        current_size--;
        temp_data = temp->data;
        delete temp;
        return temp_data;
    }
    else{
       int temp_data = 0;
       node *temp = right_p;
       right_p = right_p->prev;
       right_p->next = NULL;
       if (temp == cursor){
           cursor_left();
       }
       current_size--;
       temp_data = temp->data;
       delete temp;
       return temp_data;
    }
}

bool Deque::empty(){
    if (size() == 0){
        return true;
    }
    else{
       return false;
    } 
}

int Deque::size(){
    return current_size;
}

int Deque::peek_left(){
    return left_p->data;
}

int Deque::peek_right(){
    return right_p->data;
}

bool Deque::cursor_left(){
    if (cursor == NULL){//deque is still empty
        return false;
    }
    if (cursor == left_p){//cursor is at the very left
        return 0;
    }
    else{
        return cursor = cursor->prev;
    }
}

bool Deque::cursor_right(){
   if (cursor == NULL){//deque is still empty
        return false;
    }
    if (cursor == right_p){//cursor is at the very right
        return 0;
    }
    else{
         return cursor = cursor->next;
    }
}

int Deque::get_cursor(){
    if(cursor == NULL){
        return 3;
    }
    else{
        return cursor->data;
    }
}

void Deque::set_cursor(int i){
    cursor->data = i;
}

void Deque::display(){
    int display_data=0;
    node*TempCursor = left_p;
    cout<<"[";
    if (empty()){
        cout << "] size=" << size() << ", cursor=NULL" << endl;
    }
    else{
        while(TempCursor!= NULL){
            display_data = TempCursor->data;
            cout<<display_data<<";";
            TempCursor = TempCursor->next;
        }
        cout << "] size=" << size() << ", cursor=" << get_cursor() << endl;
    }
}

void Deque::verbose_display(){
    int display_data = 0;
    node *temp =left_p;
     if (empty()){
        cout << "empty" << endl;
    }
    else{
        while(temp!= NULL){
            display_data = temp->data;
            cout<<"pointer value = "<<display_data<<"   address = "<< temp <<"     "<<endl;
            temp = temp->next;
        }
    }
}


