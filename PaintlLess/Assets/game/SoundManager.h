#pragma once

class SoundManager {

private:
public:
	SoundManager(){}
	virtual ~SoundManager(){}
	void changeSFXvolume(int volume);
	void changeMusicVolume(int volume);
	void restoreAllVolume();

};