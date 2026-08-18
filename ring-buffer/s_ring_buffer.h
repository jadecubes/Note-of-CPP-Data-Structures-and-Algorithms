// Author: jadecubes by MIT Licence

#ifndef S_RING_BUFFER_H
#define S_RING_BUFFER_H

#include <stddef.h>

// C-style ring buffer bookkeeping (indices and lengths only; the caller owns
// the backing storage and the actual copying). See Readme.md for the usage
// pattern.
//
// Every length and index is size_t: these are buffer offsets, so the type
// that measures objects is the right one. Mixing int and unsigned long here
// used to truncate on the accessors and sign-convert on the mutators.
// The C-style typedef is what this module is demonstrating; `using` would
// not compile as C.
// NOLINTNEXTLINE(modernize-use-using)
typedef struct SRingBuffer {
  char *buf;
  size_t TotalLen; // current data length
  size_t MaxLen;   // max available space
  size_t ri;       // read index
  size_t wi;       // write index
} SRingBuffer;

// Distance from wi to the bottom of the buffer.
size_t RingWBDistance(SRingBuffer *RingBuffer);
// Available write space.
size_t RingAvailableSpace(SRingBuffer *RingBuffer);
// Distance from ri to the bottom of the buffer.
size_t RingRBDistance(SRingBuffer *RingBuffer);
// Wrap wi back into range if it passed the boundary.
void RingCheckWi(SRingBuffer *RingBuffer);
// Wrap ri back into range if it passed the boundary.
void RingCheckRi(SRingBuffer *RingBuffer);
// Initialize the ring over caller-owned storage.
void RingInit(SRingBuffer *RingBuffer, char *buff, size_t max_len);
// Advance ri by len (a read of len bytes).
void RingIncRi(SRingBuffer *RingBuffer, size_t len);
// Advance wi by len (a write of len bytes).
void RingIncWi(SRingBuffer *RingBuffer, size_t len);

#endif // S_RING_BUFFER_H
