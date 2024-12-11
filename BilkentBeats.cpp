/*
 * BilkentBeats.cpp
 * Created by: Lütfü Heysem Kızıloğlu
 * Section: 002
 * Student ID: 22301926
 */

#include "BilkentBeats.h"
#include <iostream>
#include <string>

using namespace std;

struct Song {
    int songId;
    string songName;
    string artists;
    Song* next;
    Song(int id, const string& name, const string& artist) : songId(id), songName(name), artists(artist), next(nullptr) {}
    ~Song(){
        next = nullptr;
    };
};

struct Playlist {
    int playlistId;
    Playlist* next;
    Song* songHead;
    Playlist(int id) : playlistId(id), next(nullptr), songHead(nullptr) {}
    ~Playlist(){
        next = nullptr;
        Song* currentSong = songHead;
        while (currentSong) {
            Song* nextSong = currentSong->next; 
            delete currentSong;
            currentSong = nextSong;
        }
    };
};

struct User {
    int userId;
    string userName;
    User* next;
    Playlist* playlistHead;
    User(int id, const string& name) : userId(id), userName(name), next(nullptr), playlistHead(nullptr) {}
    ~User(){
        next = nullptr;
        Playlist* currentPlaylist = playlistHead;
        while (currentPlaylist) {
            Playlist* nextPlaylist = currentPlaylist->next; 
            delete currentPlaylist;
            currentPlaylist = nextPlaylist;
        }
    };
};


User* BilkentBeats::userHead = nullptr;
Song* BilkentBeats::songHead = nullptr;
static bool cleanup_called = false;

// Constructor
BilkentBeats::BilkentBeats() {
    userHead = nullptr;
    songHead = nullptr;
}

// Destructor
BilkentBeats::~BilkentBeats() {
    if (!cleanup_called) { 
        cleanup_called = true;
        cleanup();
    }
}


// Add a new user
void BilkentBeats::addUser(const int userId, const string userName) {
    User* newUser = new User(userId, userName);
    if (!userHead || userHead->userId > userId) {
        newUser->next = userHead;
        userHead = newUser;
        cout << "Added user " << userId << "." << endl;
        return;
    }
    User* current = userHead;
    while (current->next && current->next->userId < userId) {
        current = current->next;
    }
    if (current->userId == userId) {
        cout << "Cannot add user. There is already a user with ID " << userId << "." << endl;
        delete newUser;
    } else {
        newUser->next = current->next;
        current->next = newUser;
        cout << "Added user " << userId << "." << endl;
    }
}

// Remove a user
void BilkentBeats::removeUser(const int userId) {
    if (!userHead) {
        cout << "Cannot remove user. There is no user with ID " << userId << "." << endl;
        return;
    }
    if (userHead->userId == userId) {
        User* temp = userHead;
        userHead = userHead->next;
        delete temp;
        cout << "Removed user " << userId << "." << endl;
        return;
    }
    User* current = userHead;
    while (current->next && current->next->userId != userId) {
        current = current->next;
    }
    if (!current->next) {
        cout << "Cannot remove user. There is no user with ID " << userId << "." << endl;
        return;
    }
    User* temp = current->next;
    current->next = current->next->next;
    delete temp;
    cout << "Removed user " << userId << "." << endl;
}

// Print users
void BilkentBeats::printUsers() const {
    if (!userHead) {
        cout << "There are no users to show." << endl;
        return;
    }
    User* current = userHead;
    cout << "Users in the system:" << endl;
    while (current) {
        cout << "User ID : " << current->userId << ", Name : " << current->userName;
        if (current->playlistHead) {
            cout << ", Playlist IDs : [";
            Playlist* playlist = current->playlistHead;
            while (playlist) {
                cout << playlist->playlistId;
                if (playlist->next) cout << ",";
                playlist = playlist->next;
            }
            cout << "]";
        } else {
            cout << ", Playlist IDs : None";
        }
        cout << endl;
        current = current->next;
    }
}

// Add a new song
void BilkentBeats::addSong(const int songID, const string songName, const string artists) {
    Song* newSong = new Song(songID, songName, artists);
    if (!songHead || songHead->songId > songID) {
        newSong->next = songHead;
        songHead = newSong;
        cout << "Added song " << songID << "." << endl;
        return;
    }
    Song* current = songHead;
    while (current->next && current->next->songId < songID) {
        current = current->next;
    }
    if (current->songId == songID) {
        cout << "Cannot add song. BilkentBeats already contains song " << songID << "." << endl;
        delete newSong;
    } else {
        newSong->next = current->next;
        current->next = newSong;
        cout << "Added song " << songID << "." << endl;
    }
}
    
    
// Remove the song from the music library
void BilkentBeats::removeSong(const int songID) {
    if (!songHead) {
        cout << "Cannot remove song. There is no song with ID " << songID << "." << endl;
        return;
    }
    
    if (songHead->songId == songID) {
        Song* temp = songHead;
        songHead = songHead->next;
        delete temp;
    } else {
        Song* current = songHead;
        while (current->next && current->next->songId != songID) {
            current = current->next;
        }
        if (!current->next) {
            cout << "Cannot remove song. There is no song with ID " << songID << "." << endl;
            return;
        }
        Song* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
    
    cout << "Removed song " << songID << "." << endl;
    
    User* currentUser = userHead;
    while (currentUser) {
        Playlist* playlist = currentUser->playlistHead;
        while (playlist) {
            Song* songInPlaylist = playlist->songHead;
            Song* prevSong = nullptr;

            while (songInPlaylist) {
                if (songInPlaylist->songId == songID) {
                    if (!prevSong) {
                        playlist->songHead = songInPlaylist->next;
                    } else {
                        prevSong->next = songInPlaylist->next;
                    }
                    delete songInPlaylist;
                    break; 
                }
                prevSong = songInPlaylist;
                songInPlaylist = songInPlaylist->next;
            }
            playlist = playlist->next;
        }
        currentUser = currentUser->next;
    }
}


// Print songs
void BilkentBeats::printSongs() const {
    if (!songHead) {
        cout << "Cannot print songs. There is no song in the music library." << endl;
        return;
    }
    Song* current = songHead;
    cout << "Music Library:" << endl;
    while (current) {
        cout << "Song " << current->songId << " : " << current->songName << " - " << current->artists << endl;
        current = current->next;
    }
}


//Add Playlist
void BilkentBeats::addPlaylist(const int userId, const int playlistId) {
    User* currentUser = userHead;
    while (currentUser) {
        Playlist* playlistCheck = currentUser->playlistHead;
        while (playlistCheck) {
            if (playlistCheck->playlistId == playlistId) {
                cout << "Cannot add playlist. There is a user having a playlist with ID " << playlistId << "." << endl;
                return;  
            }
            playlistCheck = playlistCheck->next;
        }
        currentUser = currentUser->next;
    }

    User* userToAdd = userHead;
    while (userToAdd && userToAdd->userId != userId) {
        userToAdd = userToAdd->next;
    }
    if (!userToAdd) {
        cout << "Cannot add playlist. There is no user with ID " << userId << "." << endl;
        return;
    }

    Playlist* newPlaylist = new Playlist(playlistId);

    if (!userToAdd->playlistHead) {
        userToAdd->playlistHead = newPlaylist;
    } else {
        Playlist* pCurrent = userToAdd->playlistHead;
        while (pCurrent->next) {
            pCurrent = pCurrent->next;
        }
        pCurrent->next = newPlaylist;
    }

    cout << "Added playlist " << playlistId << " to user " << userId << "." << endl;
}


//Remove playlist
void BilkentBeats::removePlaylist(const int userId, const int playlistId) {
    User* currentUser = userHead;
    while (currentUser && currentUser->userId != userId) {
        currentUser = currentUser->next;
    }
    if (!currentUser) {
        cout << "Cannot remove playlist. There is no user with ID " << userId << "." << endl;
        return;
    }

    Playlist* prevPlaylist = nullptr;
    Playlist* currentPlaylist = currentUser->playlistHead;

    if (currentPlaylist && currentPlaylist->playlistId == playlistId) {
        currentUser->playlistHead = currentPlaylist->next;
        
        while (currentPlaylist->songHead) {
            Song* songToDelete = currentPlaylist->songHead;
            currentPlaylist->songHead = currentPlaylist->songHead->next;
            delete songToDelete;
        }
        
        delete currentPlaylist;
        cout << "Removed playlist " << playlistId << " from user " << userId << "." << endl;
        return;
    }

    while (currentPlaylist && currentPlaylist->playlistId != playlistId) {
        prevPlaylist = currentPlaylist;
        currentPlaylist = currentPlaylist->next;
    }

    if (!currentPlaylist) {
        cout << "Cannot remove playlist. User " << userId << " does not have a playlist with ID " << playlistId << "." << endl;
        return;
    }

    if (prevPlaylist) {
        prevPlaylist->next = currentPlaylist->next; 
    } 
    else { 
        currentUser->playlistHead = currentPlaylist->next; 
    }

    while (currentPlaylist->songHead) {
        Song* songToDelete = currentPlaylist->songHead;
        currentPlaylist->songHead = currentPlaylist->songHead->next;
        delete songToDelete;
    }

    delete currentPlaylist;
    cout << "Removed playlist " << playlistId << " from user " << userId << "." << endl;
}


//Add song to playlist
void BilkentBeats::addSongToPlaylist(const int playlistId, const int songId) {
    Song* song = songHead;
    while (song && song->songId != songId) {
        song = song->next;
    }
    if (!song) {
        cout << "Cannot add song. There is no song with ID " << songId << "." << endl;
        return;
    }

    User* currentUser = userHead;
    Playlist* targetPlaylist = nullptr;
    while (currentUser) {
        Playlist* pCurrent = currentUser->playlistHead;
        while (pCurrent) {
            if (pCurrent->playlistId == playlistId) {
                targetPlaylist = pCurrent;
                break;
            }
            pCurrent = pCurrent->next;
        }
        if (targetPlaylist) break;
        currentUser = currentUser->next;
    }
    if (!targetPlaylist) {
        cout << "Cannot add song. There is no playlist with ID " << playlistId << "." << endl;
        return;
    }

    Song* songInPlaylist = targetPlaylist->songHead;
    while (songInPlaylist) {
        if (songInPlaylist->songId == songId) {
            cout << "Cannot add song. The playlist already contains song " << songId << "." << endl;
            return;
        }
        songInPlaylist = songInPlaylist->next;
    }

    Song* newSongInPlaylist = new Song(*song); 
    newSongInPlaylist->next = nullptr;

    if (!targetPlaylist->songHead) {
        targetPlaylist->songHead = newSongInPlaylist;
    } else {
        Song* lastSong = targetPlaylist->songHead;
        while (lastSong->next) {
            lastSong = lastSong->next;
        }
        lastSong->next = newSongInPlaylist;
    }

    cout << "Added song " << songId << " to playlist " << playlistId << "." << endl;
}


// remove song from playlist
void BilkentBeats::removeSongFromPlaylist(const int playlistId, const int songId) {
    User* currentUser = userHead;
    Playlist* targetPlaylist = nullptr;
    while (currentUser) {
        Playlist* pCurrent = currentUser->playlistHead;
        while (pCurrent) {
            if (pCurrent->playlistId == playlistId) {
                targetPlaylist = pCurrent;
                break;
            }
            pCurrent = pCurrent->next;
        }
        if (targetPlaylist) break;
        currentUser = currentUser->next;
    }
    if (!targetPlaylist) {
        cout << "Cannot remove song. There is no playlist with ID " << playlistId << "." << endl;
        return;
    }
    Song* songInPlaylist = targetPlaylist->songHead;
    Song* prevSong = nullptr;
    while (songInPlaylist && songInPlaylist->songId != songId) {
        prevSong = songInPlaylist;
        songInPlaylist = songInPlaylist->next;
    }
    if (!songInPlaylist) {
        cout << "Cannot remove song. There is no song " << songId << " in playlist " << playlistId << "." << endl;
        return;
    }
    if (!prevSong) {
        targetPlaylist->songHead = songInPlaylist->next;
    } else {
        prevSong->next = songInPlaylist->next;
    }
    delete songInPlaylist;
    cout << "Removed song " << songId << " from playlist " << playlistId << "." << endl;
}


//print songs in playlist
void BilkentBeats::printSongsInPlaylist(const int playlistId) const {
    User* currentUser = userHead;
    Playlist* targetPlaylist = nullptr;
    while (currentUser) {
        Playlist* pCurrent = currentUser->playlistHead;
        while (pCurrent) {
            if (pCurrent->playlistId == playlistId) {
                targetPlaylist = pCurrent;
                break;
            }
            pCurrent = pCurrent->next;
        }
        if (targetPlaylist) break;
        currentUser = currentUser->next;
    }
    if (!targetPlaylist) {
        cout << "Cannot print songs. There is no playlist with ID " << playlistId << "." << endl;
        return;
    }
    if (!targetPlaylist->songHead) {
        cout << "There are no songs to show in playlist " << playlistId << "." << endl;
        return;
    }
    Song* songInPlaylist = targetPlaylist->songHead;
    cout << "Songs in playlist " << playlistId << ":" << endl;
    while (songInPlaylist) {
        cout << "Song " << songInPlaylist->songId << " : " << songInPlaylist->songName << " - " << songInPlaylist->artists << endl;
        songInPlaylist = songInPlaylist->next;
    }
}

void BilkentBeats::cleanup() {
    while (userHead) {
        User* tempUser = userHead;
        userHead = userHead->next;
        while (tempUser->playlistHead) {
            Playlist* tempPlaylist = tempUser->playlistHead;
            tempUser->playlistHead = tempPlaylist->next;
            while (tempPlaylist->songHead) {
                Song* tempSong = tempPlaylist->songHead;
                tempPlaylist->songHead = tempSong->next;
                delete tempSong;
            }
            delete tempPlaylist;
        }
        delete tempUser;
    }
    while (songHead) {
        Song* tempSong = songHead;
        songHead = songHead->next;
        delete tempSong;
    }
}
