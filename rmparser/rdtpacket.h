#ifndef	__RDTPACKET_H__
#define __RDTPACKET_H__

#include <stdint.h>

/*
 * RDT Header
 * | Version | Seq     | Flag   | TimeStamp | Reserved | Reserved |
 * | 1 Byte  | 2 Bytes | 1 Byte | 4 Bytes   | 1 Byte   | 1 Byte   |
 * 
 * Version = 0x40 | (StreamID << 1)
 * Flag = 0x0 | KeyFrame (0: Key, 1: Non-Key)
 *
 * End Packet: Version = 0x80 | (StreamID << 2)
 */

class RdtPacket
{
public:
    
    RdtPacket(uint16_t payloadSize);
	~RdtPacket(void);
    
    uint16_t GetSize();
    uint8_t* GetBuffer();
    
    bool SetPayload(const uint8_t* buf,uint16_t size);
    
	uint8_t	GetVersion();
	bool	SetVersion( uint8_t );
    
	uint8_t	GetStreamID();
	bool	SetStreamID( uint8_t );
    
	uint16_t GetSeqNum();
	bool	 SetSeqNum( uint16_t );
    
    bool    IsKeyFrame();
    bool    SetKeyFrame( bool );
    
	uint32_t GetTimestamp();
	bool	 SetTimestamp( uint32_t );
    
private:

	enum 
    {
        RDT_SEQ_NUM_OFFSET      = 1,
        RDT_FLAG_OFFSET         = 3,
        RDT_TIMESTAMP_OFFSET    = 4,
        
        RDT_HEAD_LEN            = 10,
        
        RDT_VERSION_CONST       = 0x40
    };
    
    uint8_t*  buffer;
    uint16_t  bufferSize;
    
    uint8_t*  payload;
    uint16_t  payloadSize;
};


#endif 

