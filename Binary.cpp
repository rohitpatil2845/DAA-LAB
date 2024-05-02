#include<iostream>
using namespace std;
int main(){
int i,n;
int a[9];     // Declaring an integer array 'a' of size 9
cout<<"Enter the elements in array :"<<endl; 
for(i=0; i<9; i++){
cin>>a[i];                                       // Taking input for each element of the array from the user
}
int low = 0;
int high = 9-1;
int mid = (low+high)/2;                      // Calculating the middle index of the array
cout<<"Enter the element to be searched:"; cin>>n;
for(i=0; i<9; i++){
if (n == mid) {                      // Checking if the element to be searched is equal to the middle element 
cout<<"Element found !";
break;           // Exiting the loop
}
if(n > mid) {
low = mid+1;  }
if (n < mid) {
high = mid-1;  }
mid = (low+high)/2;             // Calculating the new middle index
}
if(i == 9)
cout<<"\nElement not found!";               // Displaying a message indicating element not found
return 0;                                                 // Indicating successful completion of the program
}

/* Output:-
Enter the elements in array :
21 
12
4
54
32
67
87
14
90
Enter the element to be searched:4
Element found !
*/
