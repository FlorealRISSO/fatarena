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

#define _DEFAULT_SOURCE
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

#include "fatarena.h"

size_t
getpgsz()
{
	static size_t pgsz = 0;
	if (!pgsz) {
		pgsz = sysconf(_SC_PAGESIZE);
	}
	return pgsz;
}

Bool
ftnew(FatArena *a, size_t sz)
{
	size_t pgsz = getpgsz();
	size_t fatsz = pgsz;
	while (fatsz < sz) {
		fatsz += pgsz;
	}

	uint8_t *pg = mmap(NULL, fatsz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (pg == MAP_FAILED) {
		return 0;
	}

	a->addr = pg;
	a->remain = fatsz;
	a->size = fatsz;
	return 1;
}

int
ftalloc(FatArena *a, size_t sz)
{
	if ((sz > a->remain)) {
		return -1;
	}

	int idx = a->size - a->remain;
	a->remain -= sz;
	return idx;
}

Bool
ftwrite(FatArena *a, int idx, const uint8_t *ptr, size_t sz)
{
	uint8_t *addr = a->addr + idx;
	if (addr + sz > addr + a->size) {
		return 0;
	}
	memcpy(addr, ptr, sz);
	return 1;
}

Bool
ftread(const FatArena *a, int idx, uint8_t *ptr, size_t sz)
{
	uint8_t *addr = a->addr + idx;
	if (addr + sz > addr + a->size) {
		return 0;
	}
	memcpy(ptr, addr, sz);
	return 1;
}

uint8_t*
ftptr(const FatArena *a, int idx)
{
	if (idx < 0 || a->size < (unsigned int) idx) {
		return NULL;
	}
	return a->addr + idx;
}

int
ftidx(const FatArena *a, const uint8_t *ptr)
{
	if (ptr > a->addr + a->size) {
		return -1;
	}
	return ptr - a->addr;
}
