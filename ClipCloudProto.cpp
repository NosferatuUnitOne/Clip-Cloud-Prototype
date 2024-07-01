#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <sstream>


using namespace std;

class versionC {
public:
	string name;
	string data;

	versionC(string& DATA, string NAME) {

		name = NAME;
		data = DATA;

	}

};

string timePrinter() {

	auto now = chrono::system_clock::now(); 
	time_t currentTime = chrono::system_clock::to_time_t(now); 
	tm localTime; 
	localtime_s(&localTime, &currentTime); 

	stringstream ss; 
	ss << (localTime.tm_mon + 1) << "-" << localTime.tm_mday << " " << localTime.tm_hour << ":" << localTime.tm_min << ":" << localTime.tm_sec; 
	return ss.str(); 
}

void UIOptionsC1() {

	cout << " " << endl;
	cout << "*****************************************************" << endl;
	cout << "1. Refresh" << endl;
	cout << "2. Add to favorites" << endl;
	cout << "3. Add to Version Control" << endl;
	cout << "4. Back" << endl;
	cout << "*****************************************************" << endl;
	cout << " " << endl;

}

void UIOptionsC3() {

	cout << " " << endl;
	cout << "*****************************************************" << endl;
	cout << "1. Delete Version" << endl;
	cout << "2. Back" << endl;
	cout << "*****************************************************" << endl;
	cout << " " << endl;

}

void UIOptionsC2() {

	cout << " " << endl; 
	cout << "*****************************************************" << endl;
	cout << "1. Remove Favorite" << endl;
	cout << "2. Back" << endl;
	cout << "*****************************************************" << endl;
	cout << " " << endl; 


}

void UIOptions(){

	cout << "*****************************************************" << endl;
	cout << "1. All" << endl;
	cout << "2. Favorites" << endl;
	cout << "3. Versions" << endl;
	cout << "4. Exit" << endl;
	cout << "*****************************************************" << endl;
}

string GetClipBoardText() {

	if (!OpenClipboard(nullptr)) {

		return "Failed to Open Clipboard";

	}

	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr) {

		CloseClipboard(); 
		return "Failed to get Clipboard Data";

	}

	char* pszText = static_cast <char*> (GlobalLock(hData));
	if (pszText == nullptr) {

		CloseClipboard();
		return "Failed to Lock Clipboard Data";

	}

	string textFinal = pszText;

	GlobalUnlock(hData);

	CloseClipboard();

	return textFinal;  

}

void clearScreen() {

	system("cls");

}

void ClipBoardMonitor(vector<string>& all) {


	string oldClipBoardText = GetClipBoardText(); 


	while (true) { 

		string currentClipBoardText = GetClipBoardText(); 

		if (oldClipBoardText != currentClipBoardText) { 
			if (all.size() > 50) { 

				all.erase(all.begin());   
			}

			all.push_back(currentClipBoardText); 
			oldClipBoardText = currentClipBoardText; 

		}

		this_thread::sleep_for(chrono::microseconds(500));
	}


}

string printSpecificItem(const vector<string>& all, int index) {

	string favHolder;

	if (index < 0 || index > all.size()) {

		cout << "Index" << index + 1 << "Is out of Range" << endl;

	}
	else {

		favHolder = all[index]; 
		return favHolder;
	}


}

int main() {

	vector<string> all; 
	vector<string> favorites; 
	vector<versionC> versionControl;   

	thread clipboardThread(ClipBoardMonitor, ref(all));
	clipboardThread.detach();

	
	string versionName;
	string versionHolder; 
	int indexChoice; 
	int option; 
	string favHolderMain; 
	int optionC1; 
	int optionC2;
	int optionC3; 

	do {

		UIOptions(); 
		cout << " " << endl;
		cin >> option;


		switch (option) {

		case 1:

			
			clearScreen();


			do {

				int counter = 1;
				cout << "All Clipboard History :" << endl; 
				for (const auto& History : all) { 
					
					cout << " " << endl;
					cout << counter << ". " << History << endl;  
					counter++; 

				} 

				UIOptionsC1(); 
				cin >> optionC1;  
				 
					switch (optionC1) { 

					case 1: 

						clearScreen(); 
						cout << "Refreshing....." << endl; 
						break; 
				
					case 2: 

						cout << "Select Index : " << endl; 
						cin >> indexChoice; 
						
						if (indexChoice > 0 && indexChoice <= all.size()) { 

							favHolderMain = printSpecificItem(all, indexChoice - 1); 
							favorites.push_back(favHolderMain);  
							clearScreen();
							cout << "Added to Favorites" << endl; 


						}

						else {

							clearScreen();
							cout << "Invalid index" << endl;

						}
						break;

					case 3:

						cout << "Select Index : " << endl;
						cin >> indexChoice;

						if (indexChoice > 0 && indexChoice <= all.size()) {
							
							versionHolder = printSpecificItem(all, indexChoice - 1);
							
							cout << "Please Enter Version Name : " << endl;
							cin >> versionName;

							versionControl.push_back(versionC(versionHolder, versionName));
							clearScreen();

						}
						else {

							clearScreen();
							cout << "Invalid Index" << endl;

						}

						break;

					case 4: 

						clearScreen();
						break;

					default:

						clearScreen();
						cout << "Invalid Input" << endl;
						break;

					}



			} while (optionC1 != 4); 

			break; 

		case 2:  

			clearScreen();  

			do {

				cout << "Favorites :" << endl;
				cout << " " << endl;

				int counter2 = 1;
				for (const auto& favoritism : favorites) {


					cout << counter2 << ". " << favoritism << endl;
					counter2++;

				}

				cout << " " << endl;
				UIOptionsC2();
				cin >> optionC2;

				switch (optionC2) {

				case 1: 

					cout << "Please Select an Index of the Favorite to Remove" << endl;  
					cout << " " << endl;
					cin >> indexChoice;
					cout << " " << endl;

					if (indexChoice > 0 && indexChoice <= favorites.size()) {

						favorites.erase(favorites.begin() + indexChoice - 1);
						clearScreen();
						cout << "Removed Index from Favorites" << endl;

   
					}
					else {

						cout << " " << endl; 
						cout << "Invalid Index" << endl;
						cout << " " << endl;
					}

					break;

				case 2:

					clearScreen();
					break;

				}
			} while (optionC2 != 2);
			
			break;

		case 3: 

			clearScreen(); 

			do { 

				cout << "Version Control :" << endl; 
				cout << " " << endl; 

				int counter3 = 1;
				for (const auto& versions : versionControl) { 


					cout << counter3 << " : " << versions.name << " " << versions.data << endl;
					counter3++; 

				}

				cout << " " << endl; 
				UIOptionsC3(); 
				cin >> optionC3; 

				switch (optionC3) { 

				case 1:

					cout << "Please Select an Index of Version to Remove" << endl;
					cout << " " << endl;
					cin >> indexChoice;
					cout << " " << endl;
					 
					if (indexChoice > 0 && indexChoice <= versionControl.size()) { 

						versionControl.erase(versionControl.begin() + indexChoice - 1);  
						clearScreen();
						cout << "Removed Index from History" << endl;  


					}
					else {
						 
						cout << " " << endl; 
						cout << "Invalid Index" << endl; 
						cout << " " << endl; 
					}

					break; 

				case 2:

					clearScreen();
					break;

				}

			} while (optionC3 != 2); 

			break;

		case 4:

			cout << "Thank you for Using ClipCloud by Nosferatu" << endl;
			return 0;

		default:




			cout << "Invalid operation" << endl;
			break;

		}

	} while (option != 4);


	

	return 0;

	//Thank you for doing this for me, Omar.

}










