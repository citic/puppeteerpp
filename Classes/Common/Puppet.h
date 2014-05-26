//  Created by Jeisson Hidalgo on 11/05/14.
#ifndef Puppet_h
#define Puppet_h

#include <cocos2d.h>

/** @class Puppet
Base class for all puppets to be animated on scenery
*/
class Puppet : public cocos2d::Sprite
{
  protected:

  public:
	/// Constructor
	Puppet();
	/// Copy constructor
	Puppet(const Puppet& other);
	/// Move constructor
	Puppet(Puppet&& other); // : member(other.member) { other.member = nullptr; }
	/// Assignment operator
	const Puppet& operator=(const Puppet& other);
	/// Move operator
	const Puppet& operator=(Puppet&& other); // { if ( this != other ) { delete this->member; this->member = other.member; other.member = nullptr; } return *this; }
	/// Destructor
	virtual ~Puppet();
	///
};

#endif /* defined(Puppet_h) */
