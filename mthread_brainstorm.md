# Multithread Brainstorm

## Ring Buffer of AudioBuffer
So firstly we need a ring buffer to store the blocks ready to go get written to
disk.  I don't believe we will need any atomic functionality with it since the
writer pointer will not be able to access the next block until the read pointer
is done processing the next block.
