#include "rmparser.h"
#include <memory.h>
#include <assert.h>

RmParser::RmParser(const std::string& name)
: fileName(name)
{
	reader = NULL;
}

RmParser::~RmParser()
{	
    if(reader != NULL)
    {
        delete reader;
        reader = NULL;
    }
}

bool RmParser::Initialize()
{
	if(reader == NULL)
    {
		reader = new RmReader(fileName);
    }
    
    assert(reader != NULL);
    if(!reader->Initialize())
    {
        return false;
    }
	
	return true;
}

uint32_t RmParser::GetPacketCount()
{
    assert(reader != NULL);
    return reader->GetFrameCount();
}

bool RmParser::LocatePacket(uint32_t index)
{
    assert(reader != NULL);
    reader->LocateFrame(index);
    return true;
}

RdtPacket* RmParser::NextRdtPacket()
{
    assert(reader != NULL);
    
    rmff_frame_t* frame = reader->NextFrame();
    if(frame == NULL)
    {
        return NULL;
    }
    
    RdtPacket* packet = MakeRdtPacket(frame);
    reader->ReleaseFrame(frame);
    
    return packet;
}

// Create RDT packet with real media frame
RdtPacket* RmParser::MakeRdtPacket(rmff_frame_t* frame) 
{		
    assert(frame != NULL);
	if(frame == NULL ) 
    {
        return NULL;
    }
    
	RdtPacket* packet = new RdtPacket(frame->size);
    assert(packet != NULL);
    if(packet == NULL)
    {
        return NULL;
    }
    
    // Payload
    packet->SetPayload((uint8_t*)frame->data, frame->size);

    // Headers
    packet->SetStreamID(frame->id);
    // packet->SetSeqNum();
    packet->SetKeyFrame(frame->flags == 2 ? true : false);
    packet->SetTimestamp(frame->timecode);
    
    return packet;
}
