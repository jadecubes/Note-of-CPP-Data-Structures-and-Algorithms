# Ring Buffer

A C-style circular buffer in the embedded-systems tradition: the struct holds
only *bookkeeping* (read index, write index, lengths). The caller owns the
backing storage and does the actual copying — the API tells it where and how
much.

## Design

- `RingInit` points the ring at caller-owned storage. No allocation happens
  anywhere in this module, which is what makes the pattern usable on
  bare-metal targets and with DMA buffers.
- A write is two steps: copy up to `RingAvailableSpace` bytes into `buf`
  starting at `wi` (splitting the copy at the physical end of the buffer if
  needed — `RingWBDistance` says how many bytes fit before the wrap), then
  call `RingIncWi(len)` to publish them.
- A read mirrors it with `RingRBDistance` / `RingIncRi`.
- `RingCheckWi` / `RingCheckRi` wrap an index back into range after it passes
  the boundary; `RingInc*` call them internally.

## Complexity

All operations are O(1): index arithmetic only, no data movement inside the
module.

## Caveats (deliberately not handled — caller's contract)

- No overflow/underflow checks: writing more than `RingAvailableSpace` or
  reading more than `TotalLen` corrupts the bookkeeping. Check first.
- Single wrap only: `RingCheck*` subtract `MaxLen` once, so a single advance
  must be at most `MaxLen` bytes.
- Not thread-safe. For one producer + one consumer, see the lock-free SPSC
  treatment in classic embedded literature — a good follow-up exercise.
