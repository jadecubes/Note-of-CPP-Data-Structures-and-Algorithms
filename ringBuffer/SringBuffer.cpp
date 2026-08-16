// Author: jadecubes by MIT Licence

#include "SringBuffer.h"

// Distance from wi to the bottom of the buffer.
unsigned int RingWBDistance(SRingBuffer *RingBuffer) {
  return (RingBuffer->MaxLen - RingBuffer->wi);
}

// Available write space.
unsigned int RingAvailableSpace(SRingBuffer *RingBuffer) {
  return (RingBuffer->MaxLen - RingBuffer->TotalLen);
}

// Distance from ri to the bottom of the buffer.
unsigned int RingRBDistance(SRingBuffer *RingBuffer) {
  return (RingBuffer->MaxLen - RingBuffer->ri);
}

// Wrap wi back into range if it passed the boundary.
void RingCheckWi(SRingBuffer *RingBuffer) {
  if (RingBuffer->wi >= RingBuffer->MaxLen)
    RingBuffer->wi -= RingBuffer->MaxLen;
}

// Wrap ri back into range if it passed the boundary.
void RingCheckRi(SRingBuffer *RingBuffer) {
  if (RingBuffer->ri >= RingBuffer->MaxLen)
    RingBuffer->ri -= RingBuffer->MaxLen;
}

// Initialize the ring over caller-owned storage.
void RingInit(SRingBuffer *RingBuffer, char *buff, int max_len) {
  RingBuffer->ri = 0;
  RingBuffer->wi = 0;
  RingBuffer->TotalLen = 0;
  RingBuffer->buf = buff;
  RingBuffer->MaxLen = max_len;
}

// Advance ri by len (a read of len bytes).
void RingIncRi(SRingBuffer *RingBuffer, int len) {
  RingBuffer->ri += len;
  RingCheckRi(RingBuffer);
  RingBuffer->TotalLen -= len;
}

// Advance wi by len (a write of len bytes).
void RingIncWi(SRingBuffer *RingBuffer, int len) {
  RingBuffer->wi += len;
  RingCheckWi(RingBuffer);
  RingBuffer->TotalLen += len;
}
