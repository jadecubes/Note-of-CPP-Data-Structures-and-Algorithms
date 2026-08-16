// Author: jadecubes by MIT Licence

#include "SRingBuffer.h"

unsigned int RingWBDistance(SRingBuffer *RingBuffer) {
  return (RingBuffer->MaxLen - RingBuffer->wi);
}

unsigned int RingAvailableSpace(SRingBuffer *RingBuffer) {
  return (RingBuffer->MaxLen - RingBuffer->TotalLen);
}

unsigned int RingRBDistance(SRingBuffer *RingBuffer) {
  return (RingBuffer->MaxLen - RingBuffer->ri);
}

void RingCheckWi(SRingBuffer *RingBuffer) {
  if (RingBuffer->wi >= RingBuffer->MaxLen)
    RingBuffer->wi -= RingBuffer->MaxLen;
}

void RingCheckRi(SRingBuffer *RingBuffer) {
  if (RingBuffer->ri >= RingBuffer->MaxLen)
    RingBuffer->ri -= RingBuffer->MaxLen;
}

void RingInit(SRingBuffer *RingBuffer, char *buff, int max_len) {
  RingBuffer->ri = 0;
  RingBuffer->wi = 0;
  RingBuffer->TotalLen = 0;
  RingBuffer->buf = buff;
  RingBuffer->MaxLen = max_len;
}

void RingIncRi(SRingBuffer *RingBuffer, int len) {
  RingBuffer->ri += len;
  RingCheckRi(RingBuffer);
  RingBuffer->TotalLen -= len;
}

void RingIncWi(SRingBuffer *RingBuffer, int len) {
  RingBuffer->wi += len;
  RingCheckWi(RingBuffer);
  RingBuffer->TotalLen += len;
}
