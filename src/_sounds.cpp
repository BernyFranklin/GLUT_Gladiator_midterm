#include "../include/_sounds.h"

_sounds::_sounds()
{
    //ctor
}

_sounds::~_sounds()
{
    //dtor
    sndEng->drop();
}
void _sounds::playMusic(char* fileName)
{
    sndEng->play2D(fileName,true);
}

void _sounds::playSounds(char* fileName)
{
    sndEng->play2D(fileName, false,false);
}

void _sounds::pauseSound(char* fileName)
{
    sndEng->play2D(fileName,true,false);
}

void _sounds::initSounds()
{
   if(!sndEng)cout<<"ERROR** Sound Engine did not Start "<<endl;
}
