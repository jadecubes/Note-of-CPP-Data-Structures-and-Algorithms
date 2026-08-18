// Author: jadecubes by MIT Licence

#include "s_ring_buffer.h"

size_t RingWBDistance(SRingBuffer *RingBuffer) {
  return (RingBuffer->MaxLen - RingBuffer->wi);
}

size_t RingAvailableSpace(SRingBuffer *RingBuffer) {
  return (RingBuffer->MaxLen - RingBuffer->TotalLen);
}

size_t RingRBDistance(SRingBuffer *RingBuffer) {
  return (RingBuffer->MaxLen - RingBuffer->ri);
}

void RingCheckWi(SRingBuffer *RingBuffer) {
  if (RingBuffer->wi >= RingBuffer->MaxLen) {
    RingBuffer->wi -= RingBuffer->MaxLen;
  }
}

void RingCheckRi(SRingBuffer *RingBuffer) {
  if (RingBuffer->ri >= RingBuffer->MaxLen) {
    RingBuffer->ri -= RingBuffer->MaxLen;
  }
}

void RingInit(SRingBuffer *RingBuffer, char *buff, size_t max_len) {
  RingBuffer->ri = 0;
  RingBuffer->wi = 0;
  RingBuffer->TotalLen = 0;
  RingBuffer->buf = buff;
  RingBuffer->MaxLen = max_len;
}

void RingIncRi(SRingBuffer *RingBuffer, size_t len) {
  RingBuffer->ri += len;
  RingCheckRi(RingBuffer);
  RingBuffer->TotalLen -= len;
}

void RingIncWi(SRingBuffer *RingBuffer, size_t len) {
  RingBuffer->wi += len;
  RingCheckWi(RingBuffer);
  RingBuffer->TotalLen += len;
}
