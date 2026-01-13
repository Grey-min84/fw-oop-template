#include "byteQueue.h"

void QueLinear::Init(){
    // 모든 원소를 0으로
    //m_buf.fill(0);
	for(int idx=0; idx< QUEUE_CIRCULAR_SIZE; ++idx){
		m_buf[idx] = 0;
	}
	m_size = 0;
    m_front = m_rear = 0;
}

void QueLinear::Refresh(){
    m_front = m_rear = 0;
	m_size = 0;
}


void QueLinear::Enqueue(uint8_t inB){
    
    if( m_size < QUEUE_LINEAR_SIZE)
	{
		m_buf[m_rear++] = inB;
		m_size++;
	}
	else
	{
		m_buf[m_rear++] = inB;

		m_front++;
	}

	if(m_rear >= QUEUE_LINEAR_SIZE)
		m_rear = 0;

	if( m_front >= QUEUE_LINEAR_SIZE )
		m_front = 0;
}



bool QueLinear::Dequeue(uint8_t* chr){

	bool l_ucRet = false;

	if( m_size > 0 )
	{
		*chr = m_buf[m_front++];
		m_size--;

		if( m_front >= QUEUE_LINEAR_SIZE )
			m_front = 0;

		l_ucRet = true;
	}
	else
	{
		l_ucRet = false;
	}

	return l_ucRet;
}


bool QueLinear::IsEmpty(){
	if(m_size == 0)
		return true;
	else
		return false;
}

bool QueLinear::IsFull(){
	return m_size == QUEUE_LINEAR_SIZE;
}




void QueDMACircular::Init(){

	m_front = m_rear = 0;
	m_size = 0;
	//m_pstRear = nullptr;

	// 모든 원소를 0으로
	//m_buf.fill(0);
	for(int idx=0; idx< QUEUE_CIRCULAR_SIZE; ++idx){
		m_buf[idx] = 0;
	}
}





void QueDMACircular::Refresh(u32 uiSize){

	m_front = m_rear = 0;
	m_size = uiSize;
}


void QueDMACircular::SetNDTRegister(uint32_t* addr){

	m_pstRear = addr;
}

bool QueDMACircular::Dequeue(uint8_t* chr){

	uint32_t uiRear = m_size - *m_pstRear;

	m_rear = *m_pstRear;

	if (m_front == uiRear) {

		return false;
	}
	else {
		*chr = m_buf[m_front%m_size];
		m_front++;
		m_front = m_front%m_size;
		return true;
	}
}


bool QueDMACircular::IsEmpty(){

	uint32_t uiRear = m_size - *m_pstRear;

	m_rear = uiRear;

	if (m_front == uiRear) {
		return true;
	}

	return false;
}


bool QueDMACircular::IsFull(){

	return false;
}
