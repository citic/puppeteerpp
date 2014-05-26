#include "PlaylistPlayer.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <random>

USING_NS_CC;

const PlaylistPlayer::TrackInfo& PlaylistPlayer::TrackInfo::operator=(const TrackInfo& other)
{
	if ( this != & other )
	{
		title = other.title;
		length = other.length;
		filename = other.filename;
	}
	return *this;
}

bool PlaylistPlayer::TrackInfo::load(std::ifstream& file)
{
	// M3u files have two lines for each track. For example:
	//
	//	#EXTINF:46,Kevin MacLeod - Ambler
	//	Ambler.mp3
	//
	// description = "Kevin MacLeod - Ambler"
	// length = 46 (seconds)
	// filename = "Ambler.mp3"

	
	// FIRST LINE
	
	// Ignore the "#EXTINF:"
	file.ignore( strlen("#EXTINF:") );
	if ( ! file ) return false;
	
	// read the length in seconds: an integer
	int len = 0;
	file >> len;
	if ( ! file ) return false;
	length = len;
	
	// Ignore the comma and read the description of the track
	file.ignore(1);
	std::getline(file, title);
	if ( ! file ) return false;
	
	// SECOND LINE
	// The filename must be a relative path, because it varies from a platform to another
	std::getline(file, filename);
	if ( ! file ) return false;
	
	return static_cast<bool>(file);
}


// Static member definition
PlaylistPlayer* PlaylistPlayer::sharedPlaylistPlayer = nullptr;

PlaylistPlayer* PlaylistPlayer::getInstance()
{
	if ( ! sharedPlaylistPlayer )
		sharedPlaylistPlayer = new PlaylistPlayer();

	return sharedPlaylistPlayer;
}

void PlaylistPlayer::destroyInstance()
{
	delete sharedPlaylistPlayer;
	sharedPlaylistPlayer = nullptr;
}

bool PlaylistPlayer::load(const std::string& filename)
{
	// Playlist file must be in Resources folder or a descendant
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
	
	// Open it as text file
	std::ifstream file(fullPath);
	if ( ! file ) { log("PlaylistPlayer error: file not found: %s", fullPath.c_str()); return false; }
	
	// Be sure it is in m3u format
	std::string line;
	std::getline(file, line);
	if ( line != "#EXTM3U" ) { log("PlaylistPlayer error: playlist must be m3u format: %s", fullPath.c_str()); return false; }
	
	// Read each track info, and store it into a container
	for ( TrackInfo track; track.load(file); )
		tracks.push_back(track);
	
	// Done
	file.close();
	return true;
}

long PlaylistPlayer::play(bool loop, bool shuffle, bool shuffleAfterEachLoop)
{
	this->loop = loop;
	if ( shuffle ) this->shuffle();
	this->shuffleAfterEachLoop = shuffleAfterEachLoop;
	return playCurrentTrack();
}

long PlaylistPlayer::playCurrentTrack(bool loop)
{
	// Is there a valid track to play?
	if ( playingTrackIndex < 0 || playingTrackIndex >= tracks.size() ) return noTrack;
	
	// Get its filename and play it as background music
	const std::string& file = tracks[playingTrackIndex].filename;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(file.c_str(), loop);
	
	// After the clip has been played, another must be played
	// if ( ! loop ) ; // ToDo: This object need to set Actions. Inherit from LabelTTF?
		
	return playingTrackIndex;
}

void PlaylistPlayer::shuffle()
{
	// See http://en.cppreference.com/w/cpp/algorithm/random_shuffle
	std::random_device rd;
    std::mt19937 generator(rd());
	
    std::shuffle(tracks.begin(), tracks.end(), generator);
}
