#ifndef __RMPARSER_H__
#define __RMPARSER_H__

#include "rmreader.h"
#include "rdtpacket.h"

class RmParser
{
public:
	RmParser(const std::string& name);
	virtual ~RmParser();
	
	bool		Initialize();
    uint32_t    GetPacketCount();
    
    bool        LocatePacket(uint32_t index);
    RdtPacket*  NextRdtPacket();

private:
    std::string fileName;
	RmReader*	reader;

    RdtPacket*  MakeRdtPacket(rmff_frame_t* frame);
};

#endif // __RMPARSER_H__
