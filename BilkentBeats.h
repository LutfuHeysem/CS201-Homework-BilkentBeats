/*
 * BilkentBeats.h
 * Created by: Lütfü Heysem Kızıloğlu
 * Section: 002
 * Student ID: 22301926
 */

#ifndef BILKENTBEATS_H
#define BILKENTBEATS_H

#include <string>
#include <iostream>

using namespace std;

class Song;
class User;
class Playlist;

class BilkentBeats {
private:
    static void cleanup();

    static User* userHead;
    static Song* songHead;

public:
    BilkentBeats();
    ~BilkentBeats();
    
    BilkentBeats(const BilkentBeats&) = delete;
    BilkentBeats& operator=(const BilkentBeats&) = delete;

    void addUser(const int userId, const string userName);
    void removeUser(const int userId);
    void printUsers() const;

    void addSong(const int songID, const string songName, const string artists);
    void removeSong(const int songID);
    void printSongs() const;

    void addPlaylist(const int userId, const int playlistId);
    void removePlaylist(const int userId, const int playlistId);
    void addSongToPlaylist(const int playlistId, const int songId);
    void removeSongFromPlaylist(const int playlistId, const int songId);
    void printSongsInPlaylist(const int playlistId) const;
};

#endif
