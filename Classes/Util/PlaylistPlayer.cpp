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
PlaylistPlayer* PlaylistPlayer::_sharedPlaylistPlayer = nullptr;

PlaylistPlayer::PlaylistPlayer()
{
}

PlaylistPlayer::~PlaylistPlayer()
{
	// Stop background music, if any
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

PlaylistPlayer* PlaylistPlayer::createInstance(const std::string& m3uFilename, const std::string& fontFile, float fontSize, const Size& dimensions, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
	destroyInstance();
	_sharedPlaylistPlayer = new PlaylistPlayer();

	if (_sharedPlaylistPlayer && FileUtils::getInstance()->isFileExist(fontFile))
	{
		TTFConfig ttfConfig(fontFile.c_str(),fontSize,GlyphCollection::DYNAMIC);
		if (_sharedPlaylistPlayer->setTTFConfig(ttfConfig))
		{
			_sharedPlaylistPlayer->setDimensions(dimensions.width,dimensions.height);
			_sharedPlaylistPlayer->autorelease();

			return _sharedPlaylistPlayer;
		}
	}

	delete _sharedPlaylistPlayer;
	return nullptr;
}

void PlaylistPlayer::destroyInstance()
{
	if ( _sharedPlaylistPlayer )
	{
		// Delete the shared playlist player if it is not used for somebody else
		_sharedPlaylistPlayer->release();
		_sharedPlaylistPlayer = nullptr;
	}
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
		_tracks.push_back(track);

	// Done
	file.close();
	return true;
}

long PlaylistPlayer::play(bool loop, bool shuffle, bool shuffleAfterEachLoop)
{
	_loop = loop;
	if ( shuffle ) this->shuffle();
	_shuffleAfterEachLoop = shuffleAfterEachLoop;
	return playCurrentTrack();
}

long PlaylistPlayer::playCurrentTrack(bool loop)
{
	// Is there a valid track to play?
	if ( _playingTrackIndex < 0 || _playingTrackIndex >= _tracks.size() ) return _noTrack;

	// Get its filename and play it as background music
	const std::string& file = _tracks[_playingTrackIndex].filename;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(file.c_str(), loop);

	// After the clip has been played, another must be played
	if ( ! loop )
	{
//		CallFunc::create()
	}

	return _playingTrackIndex;
}

void PlaylistPlayer::shuffle()
{
	// See http://en.cppreference.com/w/cpp/algorithm/random_shuffle
	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(_tracks.begin(), _tracks.end(), generator);
}
