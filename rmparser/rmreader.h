#ifndef __RMREADER_H__
#define __RMREADER_H__

#include "librmff.h"
#include <string>
#include <vector>

class RmReader 
{
public:
    RmReader(const std::string& name);
    ~RmReader();
    
    bool Initialize();
    
    uint32_t GetFrameCount();
    bool LocateFrame(uint32_t index);
    
    rmff_frame_t* NextFrame();
    void ReleaseFrame(rmff_frame_t* frame);
    
private:
    std::string fileName;
	rmff_file_t* file;
    
    // Random access of data packet requires a index of frame positions.
    // The index is created when the parser is initialized.
    // Today: Cache in a meta file for next time usage.
    std::vector<int64_t> positions;
    
    bool MakeFrameIndex();
};

#endif    //__RMREADER_H__
