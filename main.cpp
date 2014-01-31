/* Daouda Sakho
 * CSCI335 HW 3
 * to Compile: g++ -Wall -o hw3 Leftist.h main.cpp
 */

#include "LeftistHeap.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {

	
	LeftistHeap<string> leftistWords;		//Leftist heap
	string line;					// line string
	ifstream myfile ("words.txt");

	if ( myfile.is_open( ) ) {

		time_t start, end;
		double dif;

		time (&start);
		while ( myfile.peek( ) != EOF ) {

		  myfile >> line;
		  leftistWords.insert( line );
	
		} // end while

	myfile.close( );
	time (&end);
	dif = difftime(end, start);

	cout << "Loading File Took " << dif << " seconds.\n";

	} // end if

	else cout << "Unable to open file\n";
	
	//User Interface
       int choice = 0, k;

        while ( choice != 3 ) {

		cout << "\n\n**************Menu**************\n\n"
			<< "[1] - Display Heap\n"
			<< "(Warning if the file size is too big"
			<< " then tree data will be truncated.)\n"
			<< "[2] - Delete K Elements\n"
			<< "[3] - Exit\n"
			<< "\nEnter Your Choice: ";
		
		cin >> choice;

		         switch (choice) {
		               case 1:
					leftistWords.displayHeap( );
					break;
		               case 2:
		               		cout << "How many deletions for the Heap?\n";
		               	  	cin >> k;
		               	   
					for(int i = 0; i <= k; ++i)
						leftistWords.deleteMin( );
						cout << "\nNUMBER OF COMPARISONS - " 
						  	<< leftistWords.getComparisons( ) << "\n";
		                   break;
		               case 3:
				   cout << "\nGoodbye, Have a Nice Day :D\n";
				   break;
		               default:
		                     cout << "\n\aIncorrecct data entry - please try again";
		                     break;

		         } // end switch     
        }
   
	return 0;

}
