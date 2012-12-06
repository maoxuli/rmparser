#include "rdtpacket.h"
#include <memory.h>
#include <assert.h>
#ifdef _WIN32
#include <Windows.h>
#endif

RdtPacket::RdtPacket(uint16_t payloadSize)
{
	buffer = new uint8_t[ RDT_HEAD_LEN + payloadSize ];
	bufferSize = RDT_HEAD_LEN + payloadSize;
    
	payload = buffer + RDT_HEAD_LEN;
	payloadSize = payloadSize;
    
	SetVersion( RDT_VERSION_CONST);
}

RdtPacket::~RdtPacket(void)
{
    if(buffer != NULL)
    {
        delete[] buffer;
    }
}

uint16_t RdtPacket::GetSize()
{
    return bufferSize;
}

uint8_t* RdtPacket::GetBuffer()
{
    return buffer;
}

bool RdtPacket::SetPayload(const uint8_t* buf, uint16_t size)
{
    assert(payloadSize == size);
    memcpy(payload, buf, size);
    return true;
}

uint8_t RdtPacket::GetVersion()
{
    uint8_t version = buffer[0];
    version >>= 2;
    version <<= 2;
    return version;
}

bool RdtPacket::SetVersion(uint8_t version)
{
    assert(buffer != NULL);
    assert(bufferSize > 0);
    buffer[0] |= version;
    return true;
}

uint8_t RdtPacket::GetStreamID()
{
    assert(buffer != NULL);
    assert(bufferSize > 0);
    return buffer[0] & 0x2;
}

bool RdtPacket::SetStreamID(uint8_t id)
{
    assert(buffer != NULL);
    assert(bufferSize > 0);
    assert(id < 2);
    buffer[0] = buffer[0] | (id << 1);
    return true;
}

uint16_t RdtPacket::GetSeqNum()
{
    assert(buffer != NULL);
    assert(bufferSize > RDT_SEQ_NUM_OFFSET);
    return *(uint16_t*) buffer[RDT_SEQ_NUM_OFFSET];
}

bool RdtPacket::SetSeqNum(uint16_t seqNum)
{
    assert(buffer != NULL);
    assert(bufferSize > RDT_SEQ_NUM_OFFSET);
    *(uint16_t*) buffer[RDT_SEQ_NUM_OFFSET] = seqNum;
    return true;
}

bool RdtPacket::IsKeyFrame()
{
    assert(buffer != NULL);
    assert(bufferSize > RDT_FLAG_OFFSET);
    return (buffer[RDT_FLAG_OFFSET] & 0x1) == 0;
}

bool RdtPacket::SetKeyFrame(bool key)
{
    assert(buffer != NULL);
    assert(bufferSize > RDT_FLAG_OFFSET);
    buffer[RDT_FLAG_OFFSET] |= key ? 0x0 : 0x1;
    return true;
}

uint32_t RdtPacket::GetTimestamp()
{
    assert(buffer != NULL);
    assert(bufferSize > RDT_TIMESTAMP_OFFSET);
    return *(uint32_t*) buffer[RDT_TIMESTAMP_OFFSET];
}

bool RdtPacket::SetTimestamp(uint32_t timestamp)
{
    assert(buffer != NULL);
    assert(bufferSize > RDT_TIMESTAMP_OFFSET);
    *(uint32_t*) buffer[RDT_TIMESTAMP_OFFSET] = timestamp;
    return true;
}
