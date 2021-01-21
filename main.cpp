#include <iostream>
#include <sstream>
using namespace std;

struct song
{
	int songID;
	string title;
	string singer;
	int durationInSeconds;
	song* next;
};

struct playlistItem								//THIS IS NOT USED YET (god bless me)
{
	song* ItemID;
	playlistItem* nextItem;
};

struct playlist {
	string playlistTitle;
	playlist* nextPlaylist;
	playlistItem* headSong;
};

song* sHead = NULL;
playlist* pHead = NULL;


void addSong();
void displaySong();
void deleteSong();
//void editSong(); ++
//searchSonginPlaylist();// Search and dispaly all playlist tha contains a specific song

void createPlaylist();
void viewPlaylist(); //Songs in playlist or ??
void addSongsToPlaylist();
void editPlaylistName();
void viewPlaylistSongs();
void removeSongsPlaylist();
//void deletePlaylist();

//playlist navigation: View songs in playlist??
bool songExistHelper();

int main()
{
	int menuOption;
	int option;
	char cont;
	do
	{
		cout << "Welcome to Music Management System." << endl;
		cout << "1. Songs Menu" << endl;
		cout << "2. Playlists Menu\n" << endl;
		cout << "Enter your selection [1-2]: ";
		while (!(cin >> menuOption)) {
			cout << "Invalid input!\n";
			cout << "Enter your selection [1-2]: ";
			cin.clear(); cin.ignore(1000, '\n');
		};

		switch (menuOption)
		{
		case 1:
			do {
				cout << "Songs Menu:" << endl;
				cout << "1. Add Song\n2. Display Songs\n3. Delete Songs\n4. Main Menu\n";
				cout << "5.?? Edit Song \n6. Find playlist with songs" << endl;
				cout << "Enter your selection [1-4]: " << endl;

				cin >> option;

				switch (option)
				{
				case 1:
					addSong();
					break;
				case 2:
					displaySong();
					break;
				case 3:
					deleteSong();
					break;
				case 4:
					system("cls");
					main();
				case 5:
					//editSong();
					break;
				case 6:
					//searchSonginPlaylist();
					break;
				default:
					cout << "Invalid option.\n";
				}
				cout << "\nDo you want to continue?\n";
				cin >> cont;
			} while (cont == 'y' || cont == 'Y');
			break;
		case 2:
			do {
				cout << "1. Create Playlist\n2. View Playlists\n3. Add songs to playlist\n4. Main Menu\n";
				cout << "5. Edit Playlist Name \n6. View Playlist Songs \n7. Remove Songs Playlist \n8. Delete Playlist\n";
				cout << "9. Playlist Navigation\n";
				cout << "Enter your selection [1-9]: " << endl;
				cin >> option;

				switch (option)
				{
				case 1:
					createPlaylist();
					break;
				case 2:
					viewPlaylist();
					break;
				case 3:
					addSongsToPlaylist();
					break;
				case 4:
					system("cls");
					main();
				case 5:
					editPlaylistName();
					break;
				case 6:
					viewPlaylistSongs();
					break;
				case 7:
					removeSongsPlaylist();
					break;
				case 8:
					//deletePlaylist();
				case 9:
					//playlistNavigation(); ???
				default:
					cout << "Invalid option.\n";
				}
				cout << "\nDo you want to continue?\n";
				cin >> cont;
			} while (cont == 'y' || cont == 'Y');
			break;
		default:
			cout << "Invalid option.\n";
		}
		cout << "\nDo you want to continue?\n";
		cin >> cont;
	} while (cont == 'y' || cont == 'Y');
}



void createPlaylist()
{
	bool duplicate = false;
	string title;
	cout << "Enter the title of the playlist: ";
	getline(cin >> ws, title);

	//Search for duplicate first. If no duplicate OR there are no playlist, then create NEW.
	if (pHead != NULL) {
		playlist* current = pHead;
		while (current != NULL) {
			if (current->playlistTitle == title) {
				duplicate = true;
				break;
			}
			current = current->nextPlaylist;
		}
	}

	if (pHead == NULL || !duplicate) {
		playlist* newPlaylist = new playlist;
		newPlaylist->playlistTitle = title;
		newPlaylist->headSong = NULL;
		newPlaylist->nextPlaylist = pHead;
		pHead = newPlaylist;
	}
	else
	{
		cout << "Error! Duplicate playlist title!" << endl;
	}
}

void viewPlaylist()
{
	if (pHead == NULL) {
		cout << "\nThe list is empty.\n";
	}
	else {
		playlist* current = pHead;
		while (current != NULL) {
			cout << "Playlist Title: " << current->playlistTitle << "\n";
			current = current->nextPlaylist;
		}
	}
}

void addSongsToPlaylist() {
	viewPlaylist();
	int songID;
	string playlistTitle;
	bool playlistFound = false;
	bool songFound = false;
	bool duplicateSong = false;

	if (pHead == NULL) {
		cout << "No playlist found.\n";
	}
	else {
		cout << "\nEnter the name of the playlist: ";
		getline(cin >> ws, playlistTitle);

		playlist* currentPlaylist = pHead;
		while (currentPlaylist != NULL) {
			if (currentPlaylist->playlistTitle == playlistTitle) {
				playlistFound = true;
				break;
			}
			currentPlaylist = currentPlaylist->nextPlaylist;
		}
		if (playlistFound) {
			displaySong();

			if (sHead == NULL) {
				cout << "\nNo songs found." << endl;
			}
			else {
				cout << "\nEnter song ID to add song to the playlist: ";
				cin >> songID;

				song* currentSong = sHead;
				while (currentSong != NULL) {
					if (currentSong->songID == songID) {
						songFound = true;
						break;
					}
					currentSong = currentSong->next;
				}
				if (songFound) {
					playlistItem* currentPlaylistItem = currentPlaylist->headSong;

					while (currentPlaylistItem != NULL) {
						if (currentPlaylistItem->ItemID->songID == songID) {
							duplicateSong = true;
							break;
						}
						currentPlaylistItem = currentPlaylistItem->nextItem;
					}
					if (!duplicateSong) {
						playlistItem* newplaylistItem = new playlistItem;
						newplaylistItem->ItemID = currentSong;
						newplaylistItem->nextItem = NULL;

						if (currentPlaylist->headSong == NULL) {
							currentPlaylist->headSong = newplaylistItem;
							cout << "\nNew Song Added." << endl;
						}
						else {
							playlistItem* currentPlaylistItem = currentPlaylist->headSong;
							while (currentPlaylistItem->nextItem != NULL) {
								currentPlaylistItem = currentPlaylistItem->nextItem;
							}
							currentPlaylistItem->nextItem = newplaylistItem;
							cout << "\nNew Song Added." << endl;
						}
					}
					else {
						cout << "\nThis song already exists." << endl;
					}
				}
				else {
					cout << "\nSong not found." << endl;
				}
			}
		}
		else {
			cout << "\nPlaylist not found." << endl;
		}
	}
}

void editPlaylistName() {
	string playlistTitle;
	bool playlistFound = false;
	viewPlaylist();
	if (pHead == NULL) {
		cout << "No playlist found.\n";
	}
	else {
		cout << "\nEnter the name of the playlist you want to edit: ";
		getline(cin >> ws, playlistTitle);
		playlist* currentPlaylist = pHead;
		while (currentPlaylist != NULL) {
			if (currentPlaylist->playlistTitle == playlistTitle) {
				playlistFound = true;
				break;
			}
			currentPlaylist = currentPlaylist->nextPlaylist;
		}
		if (playlistFound) {
			cout << "Enter a new playlist title: ";
			getline(cin >> ws, currentPlaylist->playlistTitle);
		}
		else {
			cout << "This playlist doesn't exist.\n" << endl;
		}
		
	}
	viewPlaylist();
}
	
void viewPlaylistSongs() {
	string playlistTitle;
	viewPlaylist();
	if (pHead == NULL) {
		cout << "No playlist found.\n";
	}
	else {
		cout << "\nEnter the name of the playlist you want to view: ";
		getline(cin >> ws, playlistTitle);
		playlist* currentPlaylist = pHead;
		while (currentPlaylist != NULL) {
			if (currentPlaylist->playlistTitle == playlistTitle) {
				playlistItem* currentPlaylistItem = currentPlaylist->headSong;
				if (currentPlaylistItem == NULL) {
					cout << "This playlist is empty." << endl;
					break;
				}
				while (currentPlaylistItem != NULL) {
					cout << "title: " << currentPlaylistItem->ItemID->title;
					cout << "\tsinger: " << currentPlaylistItem->ItemID->singer;
					int durationInMinutes = currentPlaylistItem->ItemID->durationInSeconds / 60;
					cout << "\tDuration: " << durationInMinutes << " minutes " << currentPlaylistItem->ItemID->durationInSeconds % 60 << " seconds" << endl;
					currentPlaylistItem = currentPlaylistItem->nextItem;
				}
				break;
			}
			currentPlaylist = currentPlaylist->nextPlaylist;
		}
	}
}

void removeSongsPlaylist()
{
	viewPlaylistSongs();
	string songTitle;
	bool exist = false;
	playlist* currentPlaylist = pHead;
	playlistItem* currentPlaylistItem = currentPlaylist->headSong;

	cout << "Enter a Song Title to remove: " << endl;
	getline(cin >> ws, songTitle);

	while(currentPlaylistItem != NULL)
	{
		playlistItem* toDelete = currentPlaylist->headSong;
		playlistItem* prev = NULL;

		while (toDelete != NULL)
		{
			if (toDelete->ItemID->title == songTitle)
			{
				exist = true;           //If the song id exists, set boolean to true then break out of this
				break;
			}

			prev = toDelete;
			toDelete = toDelete->nextItem;
		}

		if (exist)
		{
			if (toDelete == currentPlaylist->headSong)
			{
				currentPlaylist->headSong = currentPlaylist->headSong->nextItem;
				delete toDelete;
			}
			else
			{
				prev->nextItem = toDelete->nextItem;
				delete toDelete;
			}
			cout << "Song titled: " << songTitle << " has been removed from " << currentPlaylist->playlistTitle << endl;
		}
		else
		{
			cout << "Song not found in playlist.\n";
		}
	}
}
	




//Functions for songs


bool songExistHelper(int songIDtoFind, song* &current) {
	//Returns true if exist, false if not-exists
	//also false is song list empty;
	//song* current = head;			//Set the "current" to the start of the linkedList "head"

	while (current != NULL) {		//While loop is used to traverse the linkedList until it reaches the end which is null
		if (current->songID == songIDtoFind) {	 //Checks whether the current's song id in the linked list is the same as our "ID" the user input
			return true;			//If it equals, return TRUE;
		}
		current = current->next;		 //If not equals, move on to the next node and check again
	}
	return false;
}

void addSong()
{
	int id;
	bool duplicate = false;
	cout << "Enter the song ID: ";
	cin >> id;

	song* current = sHead;

	if (sHead != NULL) {
		duplicate = songExistHelper(id,current);
	}

	if (sHead == NULL || !duplicate) {           //If the head is NULL (means linkedlist is empty) OR there's no duplicates (true)
		song* newNode = new song;     //Create a new node in the heap memory
		newNode->songID = id;                  //Set the newNode's songID to id
		cout << "Enter title of the song: ";
		getline(cin >> ws, newNode->title);                   //getline(ws) helps to add space 
		cout << "Enter singer of the song: ";
		getline(cin >> ws, newNode->singer);
		cout << "Enter duration of the song in seconds: ";
		cin >> newNode->durationInSeconds;

		newNode->next = sHead;                   //Set the "next" to the head
		sHead = newNode;                         //then set the head to the newNode (new student) that we just made
	}
	else {
		cout << "Error! Duplicate ID!" << endl; //Else (there's a duplicate) show error
	}
}

void displaySong()
{
	if (sHead == NULL) {                         //If the head (first node) is NULL means linkedlist is empty
		cout << "The list is empty.\n";         //Show that the linkedlist is empty
	}
	else {
		song* current = sHead;                                  //Else set the current to the head
		while (current != NULL) {                                   //While the current not NULL
			cout << "Song ID: " << current->songID << "\t";     //Display using current->
			cout << "Title: " << current->title << "\t";
			cout << "Singer: " << current->singer << "\t";
			int durationInMinutes = current->durationInSeconds / 60;
			cout << "Duration: " << durationInMinutes << " minutes " << current->durationInSeconds % 60 << " seconds" << endl;

			current = current->next;                                //Set the current to the next using "current->next"
		}
	}
}

void deleteSong()
{
	int id;
	bool exist = false;

	cout << "Enter a Song ID: " << endl;
	cin >> id;

	if (sHead == NULL)
	{
		cout << "The list is empty.";
	}
	else
	{
		song* toDelete = sHead;
		song* prev = NULL;

		while (toDelete != NULL)
		{
			if (toDelete->songID == id)
			{
				exist = true;           //If the song id exists, set boolean to true then break out of this
				break;
			}

			prev = toDelete;
			toDelete = toDelete->next;
		}

		if (exist)
		{
			if (toDelete == sHead)
			{
				sHead = sHead->next;
				delete toDelete;
			}
			else
			{
				prev->next = toDelete->next;
				delete toDelete;
			}
			cout << "Song " << id << " deleted.";
		}
		else
		{
			cout << "Song not found.\n";
		}
	}
}

