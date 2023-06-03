#pragma once
const int ValuePiece[14] = { 0, 0, 1, 1, 3, 3, 3, 3, 5, 5, 10, 10, 9999, 9999 };
const unsigned char PawnPassedFile[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
const sint16 PawnPassedScoreOpening[8] = { 0, 0, 0, 382, 1131, 2263, 3763, 3763 };
const sint16 PawnPassedScoreEndgame[8] = { 18, 18, 18, 181, 501, 985, 1626, 1626 };
const char LineShift[4][64] = {
	{
		0, 0, 4, 7, 11, 16, 22, 29,
		0, 4, 7, 11, 16, 22, 29, 37,
		4, 7, 11, 16, 22, 29, 37, 44,
		7, 11, 16, 22, 29, 37, 44, 50,
		11, 16, 22, 29, 37, 44, 50, 55,
		16, 22, 29, 37, 44, 50, 55, 59,
		22, 29, 37, 44, 50, 55, 59, 0,
		29, 37, 44, 50, 55, 59, 0, 0
	},
	{
		29, 22, 16, 11, 7, 4, 0, 0,
		37, 29, 22, 16, 11, 7, 4, 0,
		44, 37, 29, 22, 16, 11, 7, 4,
		50, 44, 37, 29, 22, 16, 11, 7,
		55, 50, 44, 37, 29, 22, 16, 11,
		59, 55, 50, 44, 37, 29, 22, 16,
		0, 59, 55, 50, 44, 37, 29, 22,
		0, 0, 59, 55, 50, 44, 37, 29
	},
	{
		1, 1, 1, 1, 1, 1, 1, 1,
		9, 9, 9, 9, 9, 9, 9, 9,
		17, 17, 17, 17, 17, 17, 17, 17,
		25, 25, 25, 25, 25, 25, 25, 25,
		33, 33, 33, 33, 33, 33, 33, 33,
		41, 41, 41, 41, 41, 41, 41, 41,
		49, 49, 49, 49, 49, 49, 49, 49,
		57, 57, 57, 57, 57, 57, 57, 57
	},
	{
		1, 9, 17, 25, 33, 41, 49, 57,
		1, 9, 17, 25, 33, 41, 49, 57,
		1, 9, 17, 25, 33, 41, 49, 57,
		1, 9, 17, 25, 33, 41, 49, 57,
		1, 9, 17, 25, 33, 41, 49, 57,
		1, 9, 17, 25, 33, 41, 49, 57,
		1, 9, 17, 25, 33, 41, 49, 57,
		1, 9, 17, 25, 33, 41, 49, 57
	}
};

const int MatDiffValue[12] = { 1, -1, 3, -3, 3, -3, 5, -5, 10, -10, 0, 0 };
const int MatSummValue[12] = { 2916, 26244, 324, 972, 36, 108, 4, 12, 1, 2, 0, 0 };
const uint64 MaskEnPassant[2][8] = {
	{
		0x0000000002000000, 0x0000000005000000, 0x000000000A000000, 0x0000000014000000, 0x0000000028000000,
		0x0000000050000000, 0x00000000A0000000, 0x0000000040000000
	},
	{
		0x0000000200000000, 0x0000000500000000, 0x0000000A00000000, 0x0000001400000000, 0x0000002800000000,
		0x0000005000000000, 0x000000A000000000, 0x0000004000000000
	}
};
const unsigned int CastleFlags[64] = {
	0x0000000D, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000C, 0x0000000F, 0x0000000F, 0x0000000E,
	0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F,
	0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F,
	0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F,
	0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F,
	0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F,
	0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F,
	0x00000007, 0x0000000F, 0x0000000F, 0x0000000F, 0x00000003, 0x0000000F, 0x0000000F, 0x0000000B
};

const uint64 MaskPieceIsPawn[14] = {
	0x0000000000000000, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF,
	0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
	0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
	0x0000000000000000, 0x0000000000000000
};
const uint64 MaskFile[8] = {
	0x0101010101010101, 0x0202020202020202, 0x0404040404040404, 0x0808080808080808,
	0x1010101010101010, 0x2020202020202020, 0x4040404040404040, 0x8080808080808080
};
const int FileWing[64] = {
	0, 0, 0, 1, 1, 2, 2, 2,
	0, 0, 0, 1, 1, 2, 2, 2,
	0, 0, 0, 1, 1, 2, 2, 2,
	0, 0, 0, 1, 1, 2, 2, 2,
	0, 0, 0, 1, 1, 2, 2, 2,
	0, 0, 0, 1, 1, 2, 2, 2,
	0, 0, 0, 1, 1, 2, 2, 2,
	0, 0, 0, 1, 1, 2, 2, 2
};
const int PassedPawnValue1[8] = { 0, 0, 0, 489, 1450, 2900, 4821, 4821 };
const int PassedPawnValue2[8] = { 146, 146, 146, 336, 709, 1273, 2020, 2020 };
const int PassedPawnValue3[8] = { 0, 0, 0, 26, 78, 157, 262, 262 };
const int PassedPawnValue4[8] = { 0, 0, 0, 133, 394, 788, 1311, 1311 };
const int PassedPawnValue5[8] = { 0, 0, 0, 101, 300, 601, 1000, 1000 };
const int PassedPawnValue6[8] = { 0, 0, 0, 66, 195, 391, 650, 650 };
const int PassedPawnValue7[8] = { 0, 0, 0, 131, 389, 779, 1295, 1295 };
const int KingAttackWeight[16] = {
	0, -1, 37, 71, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
};
