#ifndef __BYTE_QUEUE_H__
#define __BYTE_QUEUE_H__

extern "C"{
#include <string.h>
#include <stdint.h>
}

#include <array>

#include "typeSimple.h"

#define QUEUE_LINEAR_SIZE       256
#define QUEUE_CIRCULAR_SIZE     256

class QueLinear{
public:
    void Init();
    void Refresh();

    void Enqueue(uint8_t data);
    bool Dequeue(uint8_t* chr);
    bool IsEmpty();
    bool IsFull();

    u8 rcvBuf[QUEUE_LINEAR_SIZE];

private:
    int32_t m_front;
    int32_t m_rear;
    int32_t m_size;
    //std::array<uint8_t, QUEUE_LINEAR_SIZE> m_buf;
    uint8_t m_buf[QUEUE_CIRCULAR_SIZE];
};


class QueDMACircular{
public:
    void Init();
    void Refresh(u32);

    void SetNDTRegister(uint32_t* addr);    // Set Number of Data Transmitt

    bool Dequeue(uint8_t* chr);
    bool IsEmpty();
    bool IsFull();
    uint8_t* GetBufStartAddr(){ return &m_buf[0]; }
    
private:
    uint32_t m_front;
    uint32_t m_rear;
    uint32_t m_size;
    uint32_t* m_pstRear;
    uint8_t m_buf[QUEUE_CIRCULAR_SIZE];
    //std::array<uint8_t, QUEUE_CIRCULAR_SIZE> m_buf;
};


#endif
