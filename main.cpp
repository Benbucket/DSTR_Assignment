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
	int length;
	song* songHead;
	playlistItem* nextItem;
};

struct playlist {
	string playlistTitle;
	playlistItem* itemHead;
	playlist* next;
};



void addSong(); 
void displaySong();
void deleteSong();

void createPlaylist();
void viewPlaylist();
void addSongsToPlaylist();



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
		cin >> menuOption;

		switch (menuOption)
		{
		case 1:
			do {
				cout << "Songs Menu:" << endl;
				cout << "1. Add Song\n2. Display Songs\n3. Delete Songs\n4. Main Menu" << endl;
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
				cout << "Enter your selection [1-4]: " << endl;
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

song* head = NULL;
playlist* pHead = NULL;
playlistItem* piHead = NULL;

void createPlaylist()
{
	bool duplicate = false;
	string title;
	cout << "Enter the title of the playlist: ";
	getline(cin >> ws,title);

	if (pHead != NULL) {
		playlist* current = pHead;
		while (current != NULL) {
			if (current->playlistTitle == title) {
				duplicate = true;
				break;
			}
			current = current->next;
		}
	}

	if (pHead == NULL || !duplicate) {
		playlist* newPlaylist = new playlist;
		newPlaylist->playlistTitle = title;

		newPlaylist->next = pHead;
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
		cout << "The list is empty.\n";
	}
	else {
		playlist* current = pHead;
		while (current != NULL) {
			cout << "Playlist Title: " << current->playlistTitle << "\n";

			current = current->next;
		}
	}
}

void addSongsToPlaylist() {
	string playlistOption;
	int songIDToAdd;
	bool duplicate = false;
	bool found = false;
	bool songToAddFound = false;

	//Display all available playlists to add songs to
	if (pHead == NULL) {
		cout << "The list is empty.\n";
	}
	else {
		playlist* current = pHead;
		while (current != NULL) {
			cout << "Playlist Title: " << current->playlistTitle << "\n";
			current = current->next;
		}
		//Loop through the linked list of playlists and search for matching title

			//Allow users to select a playlist to add songs to (Select by entering exact playlist title)
			cout << "Enter the name of the playlist you want to add songs to: ";
			getline(cin >> ws, playlistOption);

			current = pHead;
			while (current != NULL) {
				if (current->playlistTitle == playlistOption) {
					found = true;
					cout << "You have found the playlist!" << endl;
					//TODO: INPUT HEAD OF SONG INTO LINKEDLIST HERE
					//TODO: Create playlistItem linkedlist here

					//TODO: Select a song you want to add into the playlist
					cout << "Song Collection:" << endl;
					displaySong();
					cout << "Select a song you want to add to the playlist. [Enter song ID]" << endl;
					cin >> songIDToAdd;
					//TODO: Validate whether songIDToAdd exists
					if (head != NULL) {
						song* current = head;
						while (current != NULL) {
							if (current->songID == songIDToAdd) {
								songToAddFound = true;
								//TODO: set the head of this song into playlistitem->songHead
								if (pHead->itemHead != NULL) {
									playlistItem* piCurrent = pHead->itemHead;
									while (piCurrent != NULL) {
										if (piCurrent->songHead == current) {
											cout << "This song already exists";
											duplicate = true;
											break;
										}
										piCurrent = piCurrent->nextItem;
									}
									playlistItem* newPlaylistItem = new playlistItem;
									newPlaylistItem->songHead = current;    //Set the songHead in the new playlistItem to be the selected song's head
									piCurrent->nextItem = newPlaylistItem;
									cout << "Succesfully added " << current->title << " to the playlist." << endl;
								}
								else
								{
									playlistItem* newPlaylistItem = new playlistItem;
									newPlaylistItem->songHead = current;    //Set the songHead in the new playlistItem to be the selected song's head
									pHead->itemHead = newPlaylistItem;
									cout << "Succesfully added " << current->title << " to the playlist." << endl;
								}
							}
							current = current->next;
						}
						if (!songToAddFound) {
							cout << "Invalid option." << endl;
						}	
					}
					break;
				}
				current = current->next;
			}
		if (!found) {
			cout << "This playlist does not exist." << endl;
		}
	}
}


//Functions for songs



void addSong()
{
	int id;
	bool duplicate = false;
	cout << "Enter the song ID: ";
	cin >> id;

	if (head != NULL) {                         //If the head is not NULL, which means the linkedlist is populated
		song* current = head;                 //Set the "current" to the start of the linkedList "head"
		while (current != NULL) {               //While loop is used to traverse the linkedList until it reaches the end which is null
			if (current->songID == id) {       //Checks whether the current's song id in the linked list is the same as our "ID" the user input
				duplicate = true;               //If it equals, set the "duplicate" flag to true and break from the loop
				break;
			}
			current = current->next;            //If not equals, move on to the next node and check again
		}
	}

	if (head == NULL || !duplicate) {           //If the head is NULL (means linkedlist is empty) OR there's no duplicates (true)
		song* newNode = new song;     //Create a new node in the heap memory
		newNode->songID = id;                  //Set the newNode's songID to id
		cout << "Enter title of the song: ";
		getline(cin >> ws, newNode->title);                   //getline(ws) helps to add space 
		cout << "Enter singer of the song: ";
		getline(cin >> ws, newNode->singer);
		cout << "Enter duration of the song in seconds: ";
		cin >> newNode->durationInSeconds;

		newNode->next = head;                   //Set the "next" to the head
		head = newNode;                         //then set the head to the newNode (new student) that we just made
	}
	else {
		cout << "Error! Duplicate ID!" << endl; //Else (there's a duplicate) show error
	}
}

void displaySong()
{
	if (head == NULL) {                         //If the head (first node) is NULL means linkedlist is empty
		cout << "The list is empty.\n";         //Show that the linkedlist is empty
	}
	else {
		song* current = head;                                  //Else set the current to the head
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

	if (head == NULL)
	{
		cout << "The list is empty.";
	}
	else
	{
		song* toDelete = head;
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
			if (toDelete == head)
			{
				head = head->next;
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

