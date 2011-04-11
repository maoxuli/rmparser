#include "rmreader.h"
#include <memory.h>
#include <assert.h>

RmReader::RmReader(const std::string& name)
: fileName(name)
{
    file = NULL;
}

RmReader::~RmReader()
{
	if(file != NULL)
	{
		rmff_close_file( file );
		file = NULL;
	}
}

bool RmReader::Initialize() 
{
    assert(file == NULL);
    file = rmff_open_file(fileName.c_str(),MB_OPEN_MODE_READING);
	if( file == NULL) 
    {
		return false;
	}
    
    if( rmff_read_headers(file) != RMFF_ERR_OK )
    {
        return false;
    }

    MakeFrameIndex();
	return true; 
}

bool RmReader::MakeFrameIndex()
{
    assert(file != NULL);
    void* hd = file->handle;
	mb_file_io_t* io = file->io;
    
    rmff_frame_t* frame = NULL;
    uint32_t index = 0;
    int64_t startPos = io->tell(hd);
	while( (frame = rmff_read_next_frame(file, NULL) ) != NULL )
	{ 
        rmff_release_frame(frame);
        positions[index] = startPos;
        startPos = io->tell(hd);
    }
    
    return true;
}

uint32_t RmReader::GetFrameCount()
{
    assert(file != NULL);
    if(file != NULL)
    {
        return file->prop_header.num_packets;
    }
    else
    {
        return 0;
    }
}

bool RmReader::LocateFrame(uint32_t index)
{
    assert(file != NULL);
    assert(index < positions.size());
    
	void* hd = file->handle;
    mb_file_io_t* io = file->io;

    int64_t offset = positions[index];
    return io->seek(hd, offset, SEEK_SET);
}

rmff_frame_t* RmReader::NextFrame()
{
    assert(file != NULL);
	return rmff_read_next_frame( file, NULL );
}

void RmReader::ReleaseFrame( rmff_frame_t* frame )
{
	rmff_release_frame( frame );
}
