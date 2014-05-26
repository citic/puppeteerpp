//
//  PlaylistPlayer.h
//
//  Created by Jeisson Hidalgo on 07/05/14.
//
//

#ifndef PlaylistPlayer_h
#define PlaylistPlayer_h

#include <fstream>
#include <string>
#include <vector>

/** A simple player able to play several tracks listed into a .m3u file
*/
class PlaylistPlayer
{
  public: // Nested data types
	/** Information of a track retrieved from a m3u list file */
	struct TrackInfo
	{
	  public:
		/// A description, usually the name of the author and the song's name
		std::string title;
		/// Length in seconds
		float length = 0.0f;
		/// Name of the sound file
		std::string filename;
		
	  public:
		/// Constructor
		explicit TrackInfo(const std::string& title = "", float length = 0.0f, const std::string& filename = "")
			: title(title), length(length), filename(filename) { }
		/// Copy Constructor
		TrackInfo(const TrackInfo& other) : title(other.title), length(other.length), filename(other.filename) { }
		/// Assignment operator
		const TrackInfo& operator=(const TrackInfo& other);
		/// Loads this track from a m3u file
		/// @return true if loading was successful, false otherwise
		bool load(std::ifstream& file);
		/// Plays this sound with SimpleAudioEngine as background sound
		void play();
	};
	
  protected: // Data members
	/// Shared instance of the player
	static PlaylistPlayer* sharedPlaylistPlayer;
	/// Indicates no track is playing
	static const long noTrack = -1;
	/// Current track being played, -1 for none
	long playingTrackIndex = noTrack;
	/// The list of tracks loaded from a m3u file
	std::vector<TrackInfo> tracks;
	/// The name of the current m3u loaded file, empty if nothing is loaded
	std::string filename;
	/// True if after finishing the list, it must automatically rewind
	bool loop = false;
	///
	bool shuffleAfterEachLoop = false;
	/// Each time a new track is played, a label displaying the description of the track will be
	/// shown for @a labelDescriptionLength seconds. Keep 0.0f to disable it. The label will emerge
	/// from bottom of the screen
	float labelDescriptionLength = 0.0f;
	///
	float crossfadeLength = 0.0f;
	
  public: // Shared instance management
    /// Get the shared Engine object, it will new one when first time be called
    static PlaylistPlayer* getInstance();
	/// Destroy the shared instance of the player
	static void destroyInstance();
	
  public: // Playback operations
	/// Load a m3u playlist file
	/// @return true in success, false instead
	bool load(const std::string& filename);
	/// Play the full playlist from the beginning, track by track
	/// @param loop Send true if the playlist must be played indefenitely, false for playing once
	/// @return The index of the current track being played (0), @a noTrack on error
	long play(bool loop = false, bool shuffle = false, bool shuffleAfterEachLoop = false);
	/// Plays the next track on the playlist
	/// @return the track number of the new playing track, @a noTrack if no more tracks available
	long playNextTrack();
	/// Plays the current track if stopped, or restart playing it if already playing
	/// @param loop Send true if the current track must be played repeatedly
	/// @return The index of the current track being played (0), @a noTrack on error
	long playCurrentTrack(bool loop = false);
	/// Stop current playback. Do not rewind the playlist
	void stop();
	/// Makes the first track the next one. If playing the current track is stopped
	void rewind();
	/// Randomizes the order of the tracks. The current track being played is not affected, if any.
	void shuffle();
};


#endif /* defined(PlaylistPlayer_h) */
