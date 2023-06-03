#pragma once
#include <setjmp.h>
#include <stdbool.h>

#include "windows.h"
#include "stdio.h"
#include "types.h"

enum
{
	White = 0,
	Black = 1,
	WhitePawn = 2,
	BlackPawn = 3,
	WhiteKnight = 4,
	BlackKnight = 5,
	WhiteBishop = 6,
	BlackBishop = 7,
	WhiteRook = 8,
	BlackRook = 9,
	WhiteQueen = 10,
	BlackQueen = 11,
	WhiteKing = 12,
	BlackKing = 13
};

enum
{
	FlagCastle = 0x2000,
	FlagEnpassant = 0x1000,
	FlagPromoQueen = 0x4000,
	FlagPromoRook = 0x5000,
	FlagPromoBishop = 0x6000,
	FlagPromoKnight = 0x7000
};

struct mat_info_t* Material;

char LineIndex[64][64];
extern const int ValuePiece[14];
uint64 MaskPawnDoubled[64];
uint64 MaskPawnIsolated[64];
uint64 MaskPawnProtectedW[64];
uint64 MaskPawnProtectedB[64];
uint64 MaskPawnAttacksW1[64];
uint64 MaskPawnAttacksB1[64];
uint64 MaskPawnAttacksW2[64];
uint64 MaskPawnAttacksB2[64];
uint64 MaskPawnPassedW[64];
uint64 MaskPawnPassedB[64];
uint64 MaskPawnOpenFileW[64];
uint64 MaskPawnOpenFileB[64];
uint64 MaskPawnAttacks[2][64];
uint64 MaskClearSquare[64];
uint64 MaskKnightMoves[64];
uint64 MaskKingMoves[64];
uint64 MaskSetMD2[64];
uint64 MaskClearMD2[64];
uint64 MaskSetMD3[64];
uint64 MaskClearMD3[64];
uint64 MaskSetMD4[64];
uint64 MaskClearMD4[64];
uint64 WhitePawnMoves1[64];
uint64 BlackPawnMoves1[64];
uint64 WhitePawnMoves2[64];
uint64 BlackPawnMoves2[64];
uint64 WhitePawnCaptures1[64];
uint64 BlackPawnCaptures1[64];
uint64 WhitePawnCaptures2[64];
uint64 BlackPawnCaptures2[64];
uint64 MaskLines[64];
uint64 MaskDiags[64];
uint64 WhiteKingOpp[64];
uint64 BlackKingOpp[64];
uint64 QuadBlackKing[64][2];
uint64 QuadWhiteKing[64][2];
sint16 PawnStruScore0[4096];
sint16 PawnStruScore1[4096];
sint16 PieceSquareValue[12][64][2];

extern const uint64 RandomTurn;
extern const uint64 RandomCastle[16];
extern const uint64 RandomEP[8];
extern const uint64 Random[12][64];

extern const unsigned char PawnPassedFile[8];
extern const sint16 PawnPassedScoreOpening[8];
extern const sint16 PawnPassedScoreEndgame[8];
extern const char LineShift[4][64];
uint64 LineMask[4][64][64];
extern const int MatDiffValue[12];
extern const int MatSummValue[12];
extern const uint64 MaskEnPassant[2][8];
extern const unsigned int CastleFlags[64];
extern const uint64 MaskPieceIsPawn[14];
uint64 MaskEvasionMoves[64][64][2];
int PieceFromChar[256];
extern const uint64 MaskFile[8];
extern const int FileWing[64];
int BsfByte[256];
extern const int PassedPawnValue1[8];
extern const int PassedPawnValue2[8];
extern const int PassedPawnValue3[8];
extern const int PassedPawnValue4[8];
extern const int PassedPawnValue5[8];
extern const int PassedPawnValue6[8];
extern const int PassedPawnValue7[8];
char Distance[64][64];
extern const int KingAttackWeight[16];

struct board_t Board[1];
struct entry_t* trans_entry;
int trans_mask;
int trans_date;
int trans_size;
int trans_score[16];
struct pawn_info_t* pawn_entry;
unsigned int pawn_mask;

static bool Searching = false;
static bool Infinite = false;
static bool Delay = false;
static int MultiPV = 1;

struct pv_t
{
	int pv[256];
	int score;
	int time;
	sint64 nodes;
	sint64 speed;
} multipv[100];

sint64 true_nodes;
int depth_is_limited, time_is_limited;
int depth_limit;
int time_limit_1, time_limit_2, time_max;
int can_stop;
int check_nb;
int best_score, best_move, best_depth, depth_score;
int best_pv[256];
int trans_move, best_trans_move;
int History[12][64];
struct pos_info_t Pos_info[256];
struct pos_info_t* pos_info_entry;
struct list_t list_root[256];
int start_time, search_time;
char pv_str[1000];
static jmp_buf jmp_buffer;
int stop_search;
int bad_1, bad_2, change, easy, flag;
static char start_pos[500] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ";
