#include "music/diatonic.h"

const u8 diatonic_fundemental[] = {
  0,2,4,5,7,9,11,
  12,14,16,17,19,21,23,
  24,26,28,29,31,33,35,
  36,38,40,41,43,45,47,
  48,50,52,53,55,57,59,
  60,62,64,65,67,69,71,
  72,74,76,77,79,81,83,
  84,86,88,89,91,93,95,
  96,98,100,101,103,105,107,
  108
};  // stopped there to make it 64, may be a mistake... seems to be enough for now

// Circuit scale modes....
const u8 scales[16][13] = {
    {6, 0, 3, 5, 6, 7, 10}, // Blues  [[1st ROW]]
	{5, 0, 3, 5, 7, 10}, // Minor Pentatonic
	{7, 0, 2, 3, 6, 7, 8, 11}, // Hungarian Minor
	{7, 0, 2, 3, 6, 7, 9, 10}, // Ukrainian Dorian
	{7, 0, 1, 4, 6, 7, 9, 11}, // Marva
	{7, 0, 1, 3, 5, 6, 7, 11}, // Todi
	{6, 0, 2, 4, 6, 8, 10}, // Whole Tone
	{12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, // Chromatic [special Piano Layout]
	{7, 0, 2, 3, 5, 7, 8, 10}, // Minor
	{7, 0, 2, 4, 5, 7, 9, 11}, // Major
	{7, 0, 2, 3, 5, 7, 9, 10}, // Dorian
	{7, 0, 1, 3, 5, 7, 8, 10}, // Phrygian
	{7, 0, 2, 4, 5, 7, 9, 10}, // Mixolydian
	{7, 0, 2, 3, 5, 7, 9, 11}, // Melodic Minor (ascending)
	{7, 0, 2, 3, 5, 7, 8, 11}, // Harmonic Minor
	{8, 0, 2, 3, 4, 5, 7, 9, 10}, // BeBop Dorian
};


// LPP scale modes....
// const u8 scales[32][13] = {
// 	{5, 0, 1, 5, 7, 10}, // In Sen
// 	{5, 0, 2, 5, 7, 9}, // Yo scale
// 	{5, 0, 1, 5, 6, 10}, // Iwato
// 	{8, 0, 2, 3, 5, 6, 8, 9, 11}, // Whole Half
// 	{8, 0, 2, 3, 5, 7, 8, 10, 11}, // BeBop Minor
// 	{6, 0, 2, 3, 4, 7, 9}, // Major blues
// 	{5, 0, 2, 3, 7, 9}, // Kumoi
// 	{8, 0, 2, 4, 5, 7, 8, 9, 11}, // BeBop Major
// 	{7, 0, 2, 4, 6, 7, 9, 11}, // Lydian
// 	{7, 0, 1, 3, 5, 6, 8, 10}, // Locrian
// 	{5, 0, 2, 4, 7, 9}, // Major Pentatonic
// 	{7, 0, 1, 4, 5, 7, 8, 10}, // Phyrigian Dominant
// 	{8, 0, 1, 3, 4, 6, 7, 9, 10}, // Half-Whole Diminished
// 	{8, 0, 2, 4, 5, 7, 9, 10, 11}, // Mixolydian BeBop
// 	{7, 0, 1, 3, 4, 6, 8, 10}, // Super Locrian
// 	{5, 0, 2, 3, 6, 7}, // Hirajoshi
// 	{6, 0, 3, 5, 6, 7, 10}, // Blues
// 	{5, 0, 3, 5, 7, 10}, // Minor Pentatonic
// 	{7, 0, 2, 3, 6, 7, 8, 11}, // Hungarian Minor
// 	{7, 0, 2, 3, 6, 7, 9, 10}, // Ukrainian Dorian
// 	{7, 0, 1, 4, 6, 7, 9, 11}, // Marva
// 	{7, 0, 1, 3, 5, 6, 7, 11}, // Todi
// 	{6, 0, 2, 4, 6, 8, 10}, // Whole Tone
// 	{12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, // Chromatic
// 	{7, 0, 2, 3, 5, 7, 8, 10}, // Minor
// 	{7, 0, 2, 4, 5, 7, 9, 11}, // Major
// 	{7, 0, 2, 3, 5, 7, 9, 10}, // Dorian
// 	{7, 0, 1, 3, 5, 7, 8, 10}, // Phrygian
// 	{7, 0, 2, 4, 5, 7, 9, 10}, // Mixolydian
// 	{7, 0, 2, 3, 5, 7, 9, 11}, // Melodic Minor (ascending)
// 	{7, 0, 2, 3, 5, 7, 8, 11}, // Harmonic Minor
// 	{8, 0, 2, 3, 4, 5, 7, 9, 10} // BeBop Dorian
// };
