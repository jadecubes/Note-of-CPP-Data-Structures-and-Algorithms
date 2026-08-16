// Author: jadecubes by MIT Licence

#ifndef SRING_BUFFER_H
#define SRING_BUFFER_H

// C-style ring buffer bookkeeping (indices and lengths only; the caller owns
// the backing storage and the actual copying). See Readme.md for the usage
// pattern.
typedef struct SRingBuffer {
  char *buf;
  unsigned long TotalLen; // current data length
  unsigned long MaxLen;   // max available space
  unsigned long ri;       // read index
  unsigned long wi;       // write index
} SRingBuffer;

// Distance from wi to the bottom of the buffer.
unsigned int RingWBDistance(SRingBuffer *RingBuffer);
// Available write space.
unsigned int RingAvailableSpace(SRingBuffer *RingBuffer);
// Distance from ri to the bottom of the buffer.
unsigned int RingRBDistance(SRingBuffer *RingBuffer);
// Wrap wi back into range if it passed the boundary.
void RingCheckWi(SRingBuffer *RingBuffer);
// Wrap ri back into range if it passed the boundary.
void RingCheckRi(SRingBuffer *RingBuffer);
// Initialize the ring over caller-owned storage.
void RingInit(SRingBuffer *RingBuffer, char *buff, int max_len);
// Advance ri by len (a read of len bytes).
void RingIncRi(SRingBuffer *RingBuffer, int len);
// Advance wi by len (a write of len bytes).
void RingIncWi(SRingBuffer *RingBuffer, int len);

#endif // SRING_BUFFER_H
