#ifndef GIFANIM_H
#define GIFANIM_H

#include <stdlib.h>		// for malloc, calloc, free, memcpy, bzero, integer typedefs
#include <stdio.h>		// for FILE*

struct GifPalette
{
	int bitDepth;

	uint8_t r[256];
	uint8_t g[256];
	uint8_t b[256];

	// k-d tree over RGB space, organized in heap fashion
	// i.e. left child of node i is node i*2, right child is node i*2+1
	// nodes 256-511 are implicitly the leaves, containing a color
	// -----------------------------------------------------------------
	uint8_t treeSplitElt[255];
	uint8_t treeSplit[255];
};

// Simple structure to write out the LZW-compressed
// portion of the image one bit at a time
// ------------------------------------------------
struct GifBitStatus
{
	uint8_t bitIndex;  // how many bits in the partial byte written so far
	uint8_t byte;      // current partial byte

	uint32_t chunkIndex;
	uint8_t chunk[256];   // bytes are written in here until we have 256 of them, then written to the file
};

// The LZW dictionary is a 256-ary tree constructed
// as the file is encoded, this is one node
// ------------------------------------------------
struct GifLzwNode
{
	uint16_t m_next[256];
};

struct GifWriter
{
	FILE* f;
	uint8_t* oldImage;
	bool firstFrame;
};

class GifAnim
{
public:
	GifAnim();
	int GifIMax(int l, int r);
	int GifIMin(int l, int r);
	int GifIAbs(int i);
	void GifGetClosestPaletteColor(GifPalette* pPal, int r, int g, int b, int& bestInd, int& bestDiff, int treeRoot = 1);
	void GifSwapPixels(uint8_t* image, int pixA, int pixB);
	int GifPartition(uint8_t* image, const int left, const int right, const int elt, int pivotIndex);
	void GifPartitionByMedian(uint8_t* image, int left, int right, int com, int neededCenter);
	void GifSplitPalette(uint8_t* image, int numPixels, int firstElt, int lastElt, int splitElt, int splitDist, int treeNode, bool buildForDither, GifPalette* pal);
	int GifPickChangedPixels( const uint8_t* lastFrame, uint8_t* frame, int numPixels );
	void GifMakePalette( const uint8_t* lastFrame, const uint8_t* nextFrame, uint32_t width, uint32_t height, int bitDepth, bool buildForDither, GifPalette* pPal );
	void GifDitherImage( const uint8_t* lastFrame, const uint8_t* nextFrame, uint8_t* outFrame, uint32_t width, uint32_t height, GifPalette* pPal );
	void GifThresholdImage( const uint8_t* lastFrame, const uint8_t* nextFrame, uint8_t* outFrame, uint32_t width, uint32_t height, GifPalette* pPal );
	void GifWriteBit( GifBitStatus& stat, uint32_t bit );
	void GifWriteChunk( FILE* f, GifBitStatus& stat );
	void GifWriteCode( FILE* f, GifBitStatus& stat, uint32_t code, uint32_t length );
	void GifWritePalette( const GifPalette* pPal, FILE* f );
	void GifWriteLzwImage(FILE* f, uint8_t* image, uint32_t left, uint32_t top,  uint32_t width, uint32_t height, uint32_t delay, GifPalette* pPal);
	bool GifBegin( GifWriter* writer, const char* filename, uint32_t width, uint32_t height, uint32_t delay, int loopcount = 0, int32_t bitDepth = 8, bool dither = false);
	bool GifWriteFrame( GifWriter* writer, const uint8_t* image, uint32_t width, uint32_t height, uint32_t delay, int bitDepth = 8, bool dither = false, GifPalette *p = NULL);
	bool GifEnd( GifWriter* writer );

	const int kGifTransIndex = 0;
	bool havePalette;
	GifPalette *have;
};

#endif // GIFANIM_H
