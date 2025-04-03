//Author: jadecubes by MIT Licence

#ifndef SringBufferH
#define SringBufferH

#include <string>
typedef struct _SRingBuffer
{
	char* buf;
	unsigned long TotalLen;//current data length
	unsigned long MaxLen;//max avalible space
	unsigned long ri;//Read Index
	unsigned long wi;//Write Index
	
}SRingBuffer;

//distant between wi to button
unsigned int RingWBDistance(SRingBuffer *RingBuffer);
//Avallible write space
unsigned int RingAvailableSpace(SRingBuffer *RingBuffer);
//distant between ri to button
unsigned int RingRBDistance(SRingBuffer *RingBuffer);
//check wi is over boundery or not
void RingCheckWi(SRingBuffer *RingBuffer);
//check ri is over boundery or not
void RingCheckRi(SRingBuffer *RingBuffer);
//Ring initial function
void RingInit(SRingBuffer *RingBuffer,char* buff,int max_len);
//Increase ri
void RingIncRi(SRingBuffer *RingBuffer,int len);
//Increase wi
void RingIncWi(SRingBuffer *RingBuffer,int len); 

#endif
