// MIT License
// 
// Copyright (c) 2024 Floréal Risso
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef FAT_ARENA_H
#define FAT_ARENA_H

typedef struct FatArena {
	uint8_t *addr;
	size_t remain;
	size_t size;
} FatArena;

typedef int Bool;

size_t getpgsz();
Bool ftnew(FatArena *a, size_t sz);
int ftalloc(FatArena *a, size_t sz);
Bool ftwrite(FatArena *a, int idx, const uint8_t *ptr, size_t sz);
Bool ftread(const FatArena *a, int idx, uint8_t *ptr, size_t sz);
uint8_t* ftptr(const FatArena *a, int idx);
int ftidx(const FatArena *a, const uint8_t *ptr);

#endif // FAT_ARENA_H
