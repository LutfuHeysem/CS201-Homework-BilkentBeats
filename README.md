In this homework, you will create a music streaming service called BilkentBeats, implemented
using linked lists. The music streaming service consists of users, songs, and playlists, each
identified by unique IDs across the system. Note that these ID types are independent of each
other. For instance, there cannot be more than one user with ID 6, but there can be a playlist
with ID 6 and a song with ID 6. They would be different entities.
In this system, you will store a linked list of users and a linked list of songs. For each user,
you will store a linked list of playlists. For each playlist, you will store a linked list of songs IDs.
In your implementation, you MUST use sorted linked lists for storing the users, songs, and
playlists, and MUST use unsorted linked lists for storing the songs in playlists.


1.1 Users
Each user has a unique ID and a name. You need to use a sorted linked list to store the items
with respect to ascending user IDs. The required functions are as follows:
• addUser: Adds a new user to the system with an ID and a name. Since IDs must be
unique, the system must check whether or not the specified user ID already exists, and if
it exists, it must not allow the operation and display a warning message. Initially, a user
does not have any playlist. Example log messages:
– Added user 6.
– Cannot add user. There is already a user with ID 6.
• removeUser: The system will allow removing users. If you remove the user, all related
playlists are removed as well. If the user does not exist, the system must display a warning
message. Example log messages:
– Removed user 6.
– Cannot remove user. There is no user with ID 6.
• printUsers: Prints IDs, user names, and also list of playlist IDs. If there is no user in
the system, give a warning message. The entries must be shown in ASCENDING ORDER
with respect to the IDs. Example log messages:
– There are no users to show.
– Users in the system:
User ID : 21, Name : Bora, Playlist IDs : [16,18]
User ID : 25, Name : Filiz, Playlist IDs : None
User ID : 26, Name : Ebru, Playlist IDs : [19]
User ID : 29, Name : Melda, Playlist IDs : [15]


1.2 The Music Library
BilkentBeats stores all songs in the music library as a sorted linked list in ascending order by
song ID. You need to use this linked list to access the information about the songs. Each song
is identified by a unique ID. Songs also store their names and the names of the artists. Note
that a song can be in multiple playlists. The required functions are as follows:
• addSong: Adds a song to the BilkentBeats music library. If the song was already added,
give a warning message and do not allow the operation. Example log messages:
– Added song 23.
– Cannot add song. BilkentBeats already contains song 23.
• removeSong: Removes the song from the BilkentBeats music library. If the song does not
exist, give a warning message. If the song is successfully removed, you need to ensure all
user playlists are updated accordingly. Example log messages:
– Removed song 23.
– Cannot remove song. There is no song with ID 23.
• printSongs: Prints the IDs, names, and artists of all songs in the music library. If there
is no song in the music library, give a warning message. The entries should be shown in
ASCENDING ORDER according to IDs. Example log messages:
– Cannot print songs. There is no song in the music library.
– Music Library:
Song 23 : Bohemian Rhapsody - Queen
Song 27 : Billie Jean - Michael Jackson
Song 46 : Nature Boy - Nat King Cole
Song 89 : Starman - David Bowie
Song 92 : Imagine - John Lennon


1.3 Playlists
Each playlist is identified by a unique ID. It also has a list of song IDs. Each playlist can belong
to a single user. Note that the songs in a playlist are not sorted according to their song IDs but
they appear in the order in which they are added to the playlist. The required functions are as
follows:
• addPlaylist: Adds a new playlist to the user with an ID. The system must first check
whether user ID exists. If it exists, then it should check whether specified playlist ID exists
in any user. If the specified user does not exist or there is already a playlist with the same
ID in a user, it must not allow the operation and display a warning message. Initially, a
playlist does not contain any songs. Example log messages:
– Added playlist 6 to user 4.
– Cannot add playlist. There is no user with ID 4.
– Cannot add playlist. There is a user having a playlist with ID 6.
• removePlaylist: The system will allow removing playlists from users. If the user does
not exist or the user does not contain the specified playlist, the system must display a
warning message. Example log messages:
– Removed playlist 6 from user 4.
– Cannot remove playlist. There is no user with ID 4.
– Cannot remove playlist. User 4 does not have a playlist with ID 6.
• addSongToPlaylist: Adds a song to the playlist. If the specified playlist ID does not
exist, or the song does not exist in the music library, or the song is already in the playlist,
give a warning message and do not allow the operation. Example log messages:
– Added song 23 to playlist 6.
– Cannot add song. There is no playlist with ID 6.
– Cannot add song. There is no song with ID 23.
– Cannot add song. The playlist already contains song 23.
• removeSongFromPlaylist: Removes the song from the specified playlist. If the playlist
does not exist or the playlist does not contain the specified song, give a warning message.
Example log messages:
– Removed song 23 from playlist 6.
– Cannot remove song. There is no playlist with ID 6.
– Cannot remove song. There is no song 23 in playlist 6.
• printSongsInPlaylist: Prints the IDs, names, and artists of the songs for the given
playlist. If the specified playlist does not exist, give a warning message. The entries
should be displayed in order of adding to the playlist. Example log messages:
– Cannot print songs. There is no playlist with ID 4.
3
– There are no songs to show in playlist 4.
– Songs in playlist 4:
Song 23 : Bohemian Rhapsody - Queen
Song 89 : Starman - David Bowie
Song 46 : Nature Boy - Nat King Cole
