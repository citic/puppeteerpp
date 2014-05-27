#ifndef PlaylistPlayer_h
#define PlaylistPlayer_h

#include <cocos2d.h>
#include <fstream>
#include <string>
#include <vector>

USING_NS_CC;

/** A simple audio player for Cocos2d-x able to play several tracks listed into a .m3u file
	@author Jeisson Hidalgo-Cespedes <jeissonh@gmail.com>
	@version 1.0 [2014.05]

	Place all audio files you want to play in the same folder, under Resources directory. Create
	a m3u file listing the files you want to hear in your game. Most audio players are able to
	save playlist in m3u format, for example VLC.

	@a PlaylistPlayer is a singleton instance. You should create the instance in your AppDelegate
	object calling the @a createInstance() method. You can call @a getInstance() method anytime
	you require the singleton instance. Call @a destroyInstance() for releasing memory resources
	or creating a new playlist player.

	@code
		#include <PlaylistPlayer.h>

		bool AppDelegate::applicationDidFinishLaunching()
		{
			// [...]
			PlaylistPlayer::createInstance("MySongs/Playlist.m3u", "Fonts/MusicFont.ttf");
			PlaylistPlayer::getInstance()->play(true, true, true);
		}
	@encode

	A @a PlaylistPlayer is also a label. Each time a new track is played, the label is shown for
	a short time giving details about the track. It is useful for giving credit to the authors of
	the music.
*/
class PlaylistPlayer : public Label
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
	static PlaylistPlayer* _sharedPlaylistPlayer;
	/// Indicates no track is playing
	static const size_t _noTrack = (size_t)-1;
	/// Current track being played, -1 for none
	long _playingTrackIndex = _noTrack;
	/// The list of tracks loaded from a m3u file
	std::vector<TrackInfo> _tracks;
	/// The name of the current m3u loaded file, empty if nothing is loaded
	std::string _m3uFilename;
	/// True if after finishing the list, it must automatically rewind
	bool _loop = false;
	///
	bool _shuffleAfterEachLoop = false;
	/// Each time a new track is played, a label displaying the description of the track will be
	/// shown for @a labelDescriptionLength seconds. Keep 0.0f to disable it. The label will emerge
	/// from bottom of the screen
	float _labelDescriptionLength = 0.0f;
	///
	float _crossfadeLength = 0.0f;

  public: // Construction and destruction
	/// Constructor
	PlaylistPlayer();
	/// Destructor
	virtual ~PlaylistPlayer();

  public: // Shared instance management
	/// Creates the singleton shared instance
	static PlaylistPlayer* createInstance(const std::string& m3uFilename, const std::string& fontFile, float fontSize, const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT, TextVAlignment vAlignment = TextVAlignment::TOP);
	/// Get the shared Engine object, it will new one when first time be called
	/// @return A pointer to the shared player, nullptr if no shared player has been created before
	/// Call @a createInstance() before executing @a getInstance()
	inline static PlaylistPlayer* getInstance() { return _sharedPlaylistPlayer; }
	/// Destroy the shared instance of the player. It is useful for releasing memory resources or
	/// loading a new playlist by calling @a createInstance()
	static void destroyInstance();

  public: // Playback operations
	/// Load a m3u playlist file
	/// @return true in success, false instead
	bool load(const std::string& _m3uFilename);
	/// Play the full playlist from the beginning, track by track
	/// @param loop Send true if the playlist must be played indefenitely, false for playing once
	/// @return The index of the current track being played (0), @a noTrack on error
	long play(bool _loop = false, bool shuffle = false, bool _shuffleAfterEachLoop = false);
	/// Plays the next track on the playlist
	/// @return the track number of the new playing track, @a noTrack if no more tracks available
	long playNextTrack();
	/// Plays the current track if stopped, or restart playing it if already playing
	/// @param loop Send true if the current track must be played repeatedly
	/// @return The index of the current track being played (0), @a noTrack on error
	long playCurrentTrack(bool _loop = false);
	/// Stop current playback. Do not rewind the playlist
	void stop();
	/// Makes the first track the next one. If playing the current track is stopped
	void rewind();
	/// Randomizes the order of the tracks. The current track being played is not affected, if any.
	void shuffle();
};


#endif /* defined(PlaylistPlayer_h) */
