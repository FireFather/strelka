#pragma once
inline void board_from_fen(const char fen[])
{
	int i, j;

	memset(Board, 0, sizeof(struct board_t));
	int pos = 0;
	char c = fen[pos];
	for (i = 56; i >= 0; i -= 8)
	{
		for (j = 0; j <= 7;)
		{
			if (c <= '8') j += c - '0';
			else
			{
				Board->square[i + j] = PieceFromChar[c];
				j++;
			}
			c = fen[++pos];
		}
		c = fen[++pos];
	}
	if (c == 'b') Board->turn = 1;
	c = fen[++pos];
	c = fen[++pos];
	if (c == '-') c = fen[++pos];
	if (c == 'K')
	{
		Board->flags |= 1;
		c = fen[++pos];
	}
	if (c == 'Q')
	{
		Board->flags |= 2;
		c = fen[++pos];
	}
	if (c == 'k')
	{
		Board->flags |= 4;
		c = fen[++pos];
	}
	if (c == 'q')
	{
		Board->flags |= 8;
		c = fen[++pos];
	}
	c = fen[++pos];
	if (c != '-')
	{
		i = c + fen[++pos] * 8 - 489;
		j = i ^ 8;
		if (Board->square[i] != 0) i = 0;
		else if (Board->square[j] != (3 - Board->turn)) i = 0;
		else if (Board->square[j - 1] != (Board->turn + 2) && Board->square[j + 1] != (Board->turn + 2)) i = 0;
		Board->ep_square = i;
	}
	board_init(Board);
}

inline void board_init(struct board_t* board)
{
	int square, piece;

	board->opening = 0;
	board->endgame = 0;
	for (square = 0; square < 64; square++)
	{
		piece = board->square[square];
		if (piece != 0)
		{
			board->opening += PieceSquareValue[piece - 2][square][0];
			board->endgame += PieceSquareValue[piece - 2][square][1];
		}
	}
	for (int i = 0; i < 14; i++) board->mp[i] = 0;
	board->md1 = 0;
	board->md2 = 0;
	board->md3 = 0;
	board->md4 = 0;
	for (square = 0; square < 64; square++)
	{
		piece = board->square[square];
		if (piece != 0)
		{
			uint64 const key = (uint64)1 << square;
			board->mp[piece & 1] |= key;
			board->mp[piece] |= key;
			board->md1 |= key;
			board->md2 |= MaskSetMD2[square];
			board->md3 |= MaskSetMD3[square];
			board->md4 |= MaskSetMD4[square];
		}
	}
	board->key = 0;
	for (square = 0; square < 64; square++)
	{
		piece = board->square[square];
		if (piece != 0) board->key ^= Random[piece - 2][square];
	}
	board->key ^= RandomCastle[board->flags];
	if (board->ep_square != 0) board->key ^= RandomEP[board->ep_square & 7];
	if (board->turn) board->key ^= 0;
	else board->key ^= RandomTurn;
	board->pawn_key = Random[0][0];
	for (square = 0; square < 64; square++)
	{
		piece = board->square[square];
		if (PIECE_IS_PAWN(piece)) board->pawn_key ^= Random[piece - 2][square];
	}
	board->mat_summ =
		popcnt(board->mp[WhiteQueen]) +
		popcnt(board->mp[BlackQueen]) * 2 +
		popcnt(board->mp[WhiteRook]) * 2 * 2 +
		popcnt(board->mp[BlackRook]) * 2 * 2 * 3 +
		popcnt(board->mp[WhiteBishop]) * 2 * 2 * 3 * 3 +
		popcnt(board->mp[BlackBishop]) * 2 * 2 * 3 * 3 * 3 +
		popcnt(board->mp[WhiteKnight]) * 2 * 2 * 3 * 3 * 3 * 3 +
		popcnt(board->mp[BlackKnight]) * 2 * 2 * 3 * 3 * 3 * 3 * 3 +
		popcnt(board->mp[WhitePawn]) * 2 * 2 * 3 * 3 * 3 * 3 * 3 * 3 +
		popcnt(board->mp[BlackPawn]) * 2 * 2 * 3 * 3 * 3 * 3 * 3 * 3 * 9;
	board->mat_diff =
		(popcnt(board->mp[WhiteQueen]) - popcnt(board->mp[BlackQueen])) * 10 +
		(popcnt(board->mp[WhiteRook]) - popcnt(board->mp[BlackRook])) * 5 +
		(popcnt(board->mp[WhiteBishop]) - popcnt(board->mp[BlackBishop])) * 3 +
		(popcnt(board->mp[WhiteKnight]) - popcnt(board->mp[BlackKnight])) * 3 +
		(popcnt(board->mp[WhitePawn]) - popcnt(board->mp[BlackPawn]));
}

#define Rank(x) ((x)>>3)
#define File(x) ((x)&7)

inline int line_attack(const int file, const int zapoln)
{
	int i, att = 0;

	if (file < 7)
		for (i = 1 << (file + 1); i < 256; i <<= 1)
		{
			att |= i;
			if (zapoln & i) break;
		}
	if (file > 0)
		for (i = 1 << (file - 1); i > 0; i >>= 1)
		{
			att |= i;
			if (zapoln & i) break;
		}
	return att;
}

const char setmd3[64] = {
	0, 2, 5, 9, 14, 20, 27, 35,
	1, 4, 8, 13, 19, 26, 34, 42,
	3, 7, 12, 18, 25, 33, 41, 48,
	6, 11, 17, 24, 32, 40, 47, 53,
	10, 16, 23, 31, 39, 46, 52, 57,
	15, 22, 30, 38, 45, 51, 56, 60,
	21, 29, 37, 44, 50, 55, 59, 62,
	28, 36, 43, 49, 54, 58, 61, 63
};
const char setmd4[64] = {
	28, 21, 15, 10, 6, 3, 1, 0,
	36, 29, 22, 16, 11, 7, 4, 2,
	43, 37, 30, 23, 17, 12, 8, 5,
	49, 44, 38, 31, 24, 18, 13, 9,
	54, 50, 45, 39, 32, 25, 19, 14,
	58, 55, 51, 46, 40, 33, 26, 20,
	61, 59, 56, 52, 47, 41, 34, 27,
	63, 62, 60, 57, 53, 48, 42, 35
};

inline void init_bitboards(void)
{
	int i, j, k, sq, shift, att, Rank1, File1, File2;
	int knightmoves[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };

	for (i = 0; i < 256; i++) PieceFromChar[i] = 0;
	PieceFromChar[66] = 6;
	PieceFromChar[75] = 12;
	PieceFromChar[78] = 4;
	PieceFromChar[80] = 2;
	PieceFromChar[81] = 10;
	PieceFromChar[82] = 8;
	PieceFromChar[98] = 7;
	PieceFromChar[107] = 13;
	PieceFromChar[110] = 5;
	PieceFromChar[112] = 3;
	PieceFromChar[113] = 11;
	PieceFromChar[114] = 9;
	BsfByte[0] = 0;
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (i & (1 << j))
			{
				BsfByte[i] = (unsigned char)j;
				break;
			}
		}
	}
	for (i = 0; i < 64; i++)
		for (j = 0; j < 64; j++)
		{
			Distance[i][j] = max((char)abs(File(i) - File(j)), (char)abs(Rank(i) - Rank(j)));
			if (i == j) LineIndex[i][j] = 9;
			else if (Rank(i) == Rank(j)) LineIndex[i][j] = 2;
			else if (File(i) == File(j)) LineIndex[i][j] = 3;
			else if (File(i) - File(j) == Rank(i) - Rank(j)) LineIndex[i][j] = 1;
			else if (File(i) - File(j) == Rank(j) - Rank(i)) LineIndex[i][j] = 0;
			else LineIndex[i][j] = 9;
		}
	for (i = 0; i < 64; i++)
	{
		for (j = 0; j < 64; j++)
		{
			LineMask[0][i][j] = 0;
			LineMask[1][i][j] = 0;
			LineMask[2][i][j] = 0;
			LineMask[3][i][j] = 0;
			att = line_attack(File(i), j << 1);
			for (k = 0, sq = Rank(i) * 8; k < 8; k++, sq++)
				if (att & (1 << k)) LineMask[2][i][j] |= (uint64)1 << sq;
			att = line_attack(7 - Rank(i), j << 1);
			for (k = 0, sq = File(i) + 56; k < 8; k++, sq -= 8)
				if (att & (1 << k)) LineMask[3][i][j] |= (uint64)1 << sq;
			if (Rank(i) + File(i) <= 7) sq = File(i);
			else sq = 7 - Rank(i);
			att = line_attack(sq, j << 1);
			if (Rank(i) + File(i) <= 7) sq = i + 7 * File(i);
			else sq = i + 7 * (7 - Rank(i));
			for (k = 0; k < 8; k++, sq -= 7)
			{
				if (att & (1 << k)) LineMask[0][i][j] |= (uint64)1 << sq;
				if (File(sq) == 7 || Rank(sq) == 0) break;
			}
			if (File(i) > Rank(i)) sq = Rank(i);
			else sq = File(i);
			att = line_attack(sq, j << 1);
			if (File(i) > Rank(i)) sq = i - 9 * Rank(i);
			else sq = i - 9 * File(i);
			for (k = 0; k < 8; k++, sq += 9)
			{
				if (att & (1 << k)) LineMask[1][i][j] |= (uint64)1 << sq;
				if (File(sq) == 7 || Rank(sq) == 7) break;
			}
		}
	}
	for (i = 0; i < 64; i++)
		for (j = 0; j < 64; j++)
		{
			MaskEvasionMoves[i][j][1] = 0xFFFFFFFFFFFFFFFF;
			MaskEvasionMoves[i][j][0] = (uint64)1 << j;
			if (LineIndex[i][j] < 9)
			{
				sq = i;
				if (File(j) > File(i) && File(i) > 0) sq -= 1;
				if (File(j) < File(i) && File(i) < 7) sq += 1;
				if (Rank(j) > Rank(i) && Rank(i) > 0) sq -= 8;
				if (Rank(j) < Rank(i) && Rank(i) < 7) sq += 8;
				if (LineIndex[i][j] == LineIndex[i][sq])
					MaskEvasionMoves[i][j][1] ^= (uint64)1 << sq;
				shift = 0;
				if (File(j) > File(i))
				{
					if (Rank(j) > Rank(i)) shift = 9;
					else if (Rank(j) == Rank(i)) shift = 1;
					else if (Rank(j) < Rank(i)) shift = -7;
				}
				else if (File(j) == File(i))
				{
					if (Rank(j) > Rank(i)) shift = 8;
					else shift = -8;
				}
				else
				{
					if (Rank(j) > Rank(i)) shift = 7;
					else if (Rank(j) == Rank(i)) shift = -1;
					else if (Rank(j) < Rank(i)) shift = -9;
				}
				for (sq = i + shift; sq != j; sq += shift)
					MaskEvasionMoves[i][j][0] |= (uint64)1 << sq;
			}
		}
	for (i = 0; i < 64; i++)
	{
		MaskPawnDoubled[i] = 0;
		for (sq = File(i); sq < 64; sq += 8)
			if (sq != i) MaskPawnDoubled[i] |= (uint64)1 << sq;
		MaskPawnIsolated[i] = 0;
		if (File(i) > 0)
			for (sq = File(i) - 1; sq < 64; sq += 8)
				MaskPawnIsolated[i] |= (uint64)1 << sq;
		if (File(i) < 7)
			for (sq = File(i) + 1; sq < 64; sq += 8)
				MaskPawnIsolated[i] |= (uint64)1 << sq;
		MaskPawnProtectedW[i] = 0;
		if (File(i) > 0)
			for (sq = File(i) - 1; sq < 64; sq += 8)
			{
				MaskPawnProtectedW[i] |= (uint64)1 << sq;
				if (Rank(sq) == Rank(i)) break;
			}
		if (File(i) < 7)
			for (sq = File(i) + 1; sq < 64; sq += 8)
			{
				MaskPawnProtectedW[i] |= (uint64)1 << sq;
				if (Rank(sq) == Rank(i)) break;
			}
		MaskPawnProtectedB[i] = 0;
		if (File(i) > 0)
			for (sq = Rank(i) * 8 + File(i) - 1; sq < 64; sq += 8)
				MaskPawnProtectedB[i] |= (uint64)1 << sq;
		if (File(i) < 7)
			for (sq = Rank(i) * 8 + File(i) + 1; sq < 64; sq += 8)
				MaskPawnProtectedB[i] |= (uint64)1 << sq;
		MaskPawnAttacksW1[i] = 0;
		if (Rank(i) < 6)
		{
			if (File(i) > 0) MaskPawnAttacksW1[i] |= (uint64)1 << (i + 15);
			if (File(i) < 7) MaskPawnAttacksW1[i] |= (uint64)1 << (i + 17);
		}
		MaskPawnAttacksB1[i] = 0;
		if (Rank(i) > 1)
		{
			if (File(i) > 0) MaskPawnAttacksB1[i] |= (uint64)1 << (i - 17);
			if (File(i) < 7) MaskPawnAttacksB1[i] |= (uint64)1 << (i - 15);
		}
		MaskPawnAttacksW2[i] = 0;
		if (Rank(i) < 5)
		{
			if (File(i) > 0) MaskPawnAttacksW2[i] |= (uint64)1 << (i + 23);
			if (File(i) < 7) MaskPawnAttacksW2[i] |= (uint64)1 << (i + 25);
		}
		MaskPawnAttacksB2[i] = 0;
		if (Rank(i) > 2)
		{
			if (File(i) > 0) MaskPawnAttacksB2[i] |= (uint64)1 << (i - 25);
			if (File(i) < 7) MaskPawnAttacksB2[i] |= (uint64)1 << (i - 23);
		}
		MaskPawnPassedW[i] = 0;
		for (sq = i + 8; sq < 64; sq += 8)
			MaskPawnPassedW[i] |= (uint64)1 << sq;
		if (File(i) > 0)
			for (sq = i + 7; sq < 64; sq += 8)
				MaskPawnPassedW[i] |= (uint64)1 << sq;
		if (File(i) < 7)
			for (sq = i + 9; sq < 64; sq += 8)
				MaskPawnPassedW[i] |= (uint64)1 << sq;
		MaskPawnPassedB[i] = 0;
		for (sq = i - 8; sq >= 0; sq -= 8)
			MaskPawnPassedB[i] |= (uint64)1 << sq;
		if (File(i) > 0)
			for (sq = i - 9; sq >= 0; sq -= 8)
				MaskPawnPassedB[i] |= (uint64)1 << sq;
		if (File(i) < 7)
			for (sq = i - 7; sq >= 0; sq -= 8)
				MaskPawnPassedB[i] |= (uint64)1 << sq;
		MaskPawnOpenFileW[i] = 0;
		for (sq = i + 8; sq < 64; sq += 8)
			MaskPawnOpenFileW[i] |= (uint64)1 << sq;
		MaskPawnOpenFileB[i] = 0;
		for (sq = i - 8; sq >= 0; sq -= 8)
			MaskPawnOpenFileB[i] |= (uint64)1 << sq;
		MaskPawnAttacks[0][i] = 0;
		if (Rank(i) < 7)
		{
			if (File(i) > 0) MaskPawnAttacks[0][i] |= (uint64)1 << (i + 7);
			if (File(i) < 7) MaskPawnAttacks[0][i] |= (uint64)1 << (i + 9);
		}
		MaskPawnAttacks[1][i] = 0;
		if (Rank(i) > 0)
		{
			if (File(i) > 0) MaskPawnAttacks[1][i] |= (uint64)1 << (i - 9);
			if (File(i) < 7) MaskPawnAttacks[1][i] |= (uint64)1 << (i - 7);
		}
		MaskClearSquare[i] = 0xFFFFFFFFFFFFFFFF ^ ((uint64)1 << i);
		MaskKnightMoves[i] = 0;
		for (j = 0; j < 8; j++)
		{
			sq = i + knightmoves[j];
			if (sq >= 0 && sq < 64 && abs(Rank(i) - Rank(sq)) <= 2 && abs(File(i) - File(sq)) <= 2)
				MaskKnightMoves[i] |= (uint64)1 << sq;
		}
		MaskKingMoves[i] = 0;
		for (j = 0; j < 64; j++)
			if (Distance[i][j] == 1)
				MaskKingMoves[i] |= (uint64)1 << j;
		sq = File(i) * 8 + (7 - Rank(i));
		MaskSetMD2[i] = (uint64)1 << sq;
		MaskClearMD2[i] = 0xFFFFFFFFFFFFFFFF ^ (uint64)1 << sq;
		sq = setmd3[i];
		MaskSetMD3[i] = (uint64)1 << sq;
		MaskClearMD3[i] = 0xFFFFFFFFFFFFFFFF ^ (uint64)1 << sq;
		sq = setmd4[i];
		MaskSetMD4[i] = (uint64)1 << sq;
		MaskClearMD4[i] = 0xFFFFFFFFFFFFFFFF ^ (uint64)1 << sq;
		WhitePawnMoves1[i] = 0;
		if (Rank(i) < 7) WhitePawnMoves1[i] |= (uint64)1 << (i + 8);
		BlackPawnMoves1[i] = 0;
		if (Rank(i) > 0) BlackPawnMoves1[i] |= (uint64)1 << (i - 8);
		WhitePawnMoves2[i] = 0;
		if (Rank(i) == 1) WhitePawnMoves2[i] |= (uint64)1 << (i + 16);
		BlackPawnMoves2[i] = 0;
		if (Rank(i) == 6) BlackPawnMoves2[i] |= (uint64)1 << (i - 16);
		WhitePawnCaptures1[i] = 0;
		if (Rank(i) > 0 && File(i) > 0) WhitePawnCaptures1[i] |= (uint64)1 << (i - 9);
		BlackPawnCaptures1[i] = 0;
		if (Rank(i) < 7 && File(i) > 0) BlackPawnCaptures1[i] |= (uint64)1 << (i + 7);
		WhitePawnCaptures2[i] = 0;
		if (Rank(i) > 0 && File(i) < 7) WhitePawnCaptures2[i] |= (uint64)1 << (i - 7);
		BlackPawnCaptures2[i] = 0;
		if (Rank(i) < 7 && File(i) < 7) BlackPawnCaptures2[i] |= (uint64)1 << (i + 9);
		MaskLines[i] = 0xFFFFFFFFFFFFFFFF ^ ((uint64)1 << i);
		if (File(i) > 0)
			for (sq = i - 1;; sq--)
			{
				MaskLines[i] ^= (uint64)1 << sq;
				if (File(sq) == 0) break;
			}
		if (File(i) < 7)
			for (sq = i + 1;; sq++)
			{
				MaskLines[i] ^= (uint64)1 << sq;
				if (File(sq) == 7) break;
			}
		if (Rank(i) > 0)
			for (sq = i - 8;; sq -= 8)
			{
				MaskLines[i] ^= (uint64)1 << sq;
				if (Rank(sq) == 0) break;
			}
		if (Rank(i) < 7)
			for (sq = i + 8;; sq += 8)
			{
				MaskLines[i] ^= (uint64)1 << sq;
				if (Rank(sq) == 7) break;
			}
		MaskDiags[i] = 0xFFFFFFFFFFFFFFFF ^ ((uint64)1 << i);
		if (File(i) > 0 && Rank(i) > 0)
			for (sq = i - 9;; sq -= 9)
			{
				MaskDiags[i] ^= (uint64)1 << sq;
				if (File(sq) == 0 || Rank(sq) == 0) break;
			}
		if (File(i) > 0 && Rank(i) < 7)
			for (sq = i + 7;; sq += 7)
			{
				MaskDiags[i] ^= (uint64)1 << sq;
				if (File(sq) == 0 || Rank(sq) == 7) break;
			}
		if (File(i) < 7 && Rank(i) > 0)
			for (sq = i - 7;; sq -= 7)
			{
				MaskDiags[i] ^= (uint64)1 << sq;
				if (File(sq) == 7 || Rank(sq) == 0) break;
			}
		if (File(i) < 7 && Rank(i) < 7)
			for (sq = i + 9;; sq += 9)
			{
				MaskDiags[i] ^= (uint64)1 << sq;
				if (File(sq) == 7 || Rank(sq) == 7) break;
			}
		WhiteKingOpp[i] = 0;
		if (Rank(i) > 3)
		{
			if (File(i) == 0)
			{
				WhiteKingOpp[i] |= (uint64)1 << 49;
				if (Rank(i) > 4) WhiteKingOpp[i] |= (uint64)1 << 57;
			}
			else if (File(i) == 7)
			{
				WhiteKingOpp[i] |= (uint64)1 << 54;
				if (Rank(i) > 4) WhiteKingOpp[i] |= (uint64)1 << 62;
			}
			else
			{
				WhiteKingOpp[i] |= (uint64)1 << (File(i) + 47);
				WhiteKingOpp[i] |= (uint64)1 << (File(i) + 48);
				WhiteKingOpp[i] |= (uint64)1 << (File(i) + 49);
				if (Rank(i) > 4)
				{
					WhiteKingOpp[i] |= (uint64)1 << (File(i) + 55);
					WhiteKingOpp[i] |= (uint64)1 << (File(i) + 56);
					WhiteKingOpp[i] |= (uint64)1 << (File(i) + 57);
				}
			}
		}
		BlackKingOpp[i] = 0;
		if (Rank(i) < 4)
		{
			if (File(i) == 0)
			{
				BlackKingOpp[i] |= (uint64)1 << 9;
				if (Rank(i) < 3) BlackKingOpp[i] |= (uint64)1 << 1;
			}
			else if (File(i) == 7)
			{
				BlackKingOpp[i] |= (uint64)1 << 14;
				if (Rank(i) < 3) BlackKingOpp[i] |= (uint64)1 << 6;
			}
			else
			{
				BlackKingOpp[i] |= (uint64)1 << (File(i) + 7);
				BlackKingOpp[i] |= (uint64)1 << (File(i) + 8);
				BlackKingOpp[i] |= (uint64)1 << (File(i) + 9);
				if (Rank(i) < 3)
				{
					BlackKingOpp[i] |= (uint64)1 << (File(i) - 1);
					BlackKingOpp[i] |= (uint64)1 << (File(i));
					BlackKingOpp[i] |= (uint64)1 << (File(i) + 1);
				}
			}
		}
		QuadBlackKing[i][0] = 0;
		QuadBlackKing[i][1] = 0;
		Rank1 = Rank(i);
		if (Rank1 != 0 && Rank1 != 7)
		{
			QuadBlackKing[i][0] = 0xFFFFFFFFFFFFFFFF;
			if (Rank1 == 1) Rank1++;
			File1 = File(i) - (7 - Rank1);
			if (File1 < 0) File1 = 0;
			File2 = File(i) + (7 - Rank1);
			if (File2 > 7) File2 = 7;
			for (; Rank1 < 8; Rank1++)
				for (j = File1; j <= File2; j++)
					QuadBlackKing[i][0] ^= (uint64)1 << (Rank1 * 8 + j);
			QuadBlackKing[i][1] = 0xFFFFFFFFFFFFFFFF;
			Rank1 = Rank(i) - 1;
			if (Rank1 == 0) Rank1++;
			File1 = File(i) - (7 - Rank1);
			if (File1 < 0) File1 = 0;
			File2 = File(i) + (7 - Rank1);
			if (File2 > 7) File2 = 7;
			for (; Rank1 < 8; Rank1++)
				for (j = File1; j <= File2; j++)
					QuadBlackKing[i][1] ^= (uint64)1 << (Rank1 * 8 + j);
		}
		QuadWhiteKing[i][0] = 0;
		QuadWhiteKing[i][1] = 0;
		Rank1 = Rank(i);
		if (Rank1 != 0 && Rank1 != 7)
		{
			QuadWhiteKing[i][0] = 0xFFFFFFFFFFFFFFFF;
			Rank1++;
			if (Rank1 == 7) Rank1--;
			File1 = File(i) - Rank1;
			if (File1 < 0) File1 = 0;
			File2 = File(i) + Rank1;
			if (File2 > 7) File2 = 7;
			for (; Rank1 >= 0; Rank1--)
				for (j = File1; j <= File2; j++)
					QuadWhiteKing[i][0] ^= (uint64)1 << (Rank1 * 8 + j);
			QuadWhiteKing[i][1] = 0xFFFFFFFFFFFFFFFF;
			Rank1 = Rank(i);
			if (Rank1 == 6) Rank1--;
			File1 = File(i) - Rank1;
			if (File1 < 0) File1 = 0;
			File2 = File(i) + Rank1;
			if (File2 > 7) File2 = 7;
			for (; Rank1 >= 0; Rank1--)
				for (j = File1; j <= File2; j++)
					QuadWhiteKing[i][1] ^= (uint64)1 << (Rank1 * 8 + j);
		}
	}
}

enum
{
	PAWN_SCORE_SIZE = 125
};

struct
{
	uint16 mask;
	uint16 bits;
	sint16 score0;
	sint16 score1;

}

pawnscore[PAWN_SCORE_SIZE] = {
	{0xFFF, 0x000, 4484, 0}, {0x007, 0x007, 794, 0}, {0x00F, 0x00E, 214, 2334},
	{0x027, 0x023, 214, 2334}, {0x017, 0x015, 428, 2334}, {0x02F, 0x02A, 428, 4668},
	{0x01F, 0x01C, 642, 4668}, {0x037, 0x031, 642, 4668}, {0x04F, 0x046, 749, 653},
	{0x127, 0x103, 749, 653}, {0x03F, 0x038, 856, 7002}, {0x24F, 0x206, 915, 310},
	{0x927, 0x803, 915, 310}, {0x12F, 0x10A, 963, 2987}, {0x06F, 0x062, 963, 2987},
	{0x927, 0x003, 1121, 0}, {0x24F, 0x006, 1121, 0}, {0x26F, 0x222, 1129, 2644},
	{0x92F, 0x80A, 1129, 2644}, {0x05F, 0x054, 1177, 2987}, {0x137, 0x111, 1177, 2987},
	{0x26F, 0x022, 1335, 2334}, {0x92F, 0x00A, 1335, 2334}, {0x937, 0x811, 1343, 2644},
	{0x25F, 0x214, 1343, 2644}, {0x07F, 0x070, 1391, 5321}, {0x13F, 0x118, 1391, 5321},
	{0x097, 0x085, 1498, 653}, {0x16F, 0x142, 1498, 1306}, {0x25F, 0x014, 1549, 2334},
	{0x937, 0x011, 1549, 2334}, {0x27F, 0x230, 1557, 4978}, {0x93F, 0x818, 1557, 4978},
	{0x36F, 0x302, 1664, 963}, {0x96F, 0x842, 1664, 963}, {0x09F, 0x08C, 1712, 2987},
	{0x0B7, 0x0A1, 1712, 2987}, {0x27F, 0x030, 1763, 4668}, {0x93F, 0x018, 1763, 4668},
	{0x497, 0x405, 1830, 310}, {0xB6F, 0xA02, 1830, 620}, {0x36F, 0x102, 1870, 653},
	{0x96F, 0x042, 1870, 653}, {0x0BF, 0x0A8, 1926, 5321}, {0x17F, 0x150, 1926, 3640},
	{0xB6F, 0x802, 2036, 310}, {0xB6F, 0x202, 2036, 310}, {0x49F, 0x40C, 2044, 2644},
	{0x4B7, 0x421, 2044, 2644}, {0x37F, 0x310, 2092, 3297}, {0x97F, 0x850, 2092, 3297},
	{0x497, 0x005, 2242, 0}, {0xB6F, 0x002, 2242, 0}, {0x0DF, 0x0C4, 2247, 1306},
	{0x1B7, 0x181, 2247, 1306}, {0x4BF, 0x428, 2258, 4978}, {0xB7F, 0xA10, 2258, 2954},
	{0x37F, 0x110, 2298, 2987}, {0x97F, 0x050, 2298, 2987}, {0x9B7, 0x881, 2413, 963},
	{0x2DF, 0x284, 2413, 963}, {0x49F, 0x00C, 2456, 2334}, {0x4B7, 0x021, 2456, 2334},
	{0x0FF, 0x0E0, 2461, 3640}, {0x1BF, 0x188, 2461, 3640}, {0xB7F, 0x810, 2464, 2644},
	{0xB7F, 0x210, 2464, 2644}, {0x4DF, 0x444, 2579, 963}, {0x5B7, 0x501, 2579, 963},
	{0x2DF, 0x084, 2619, 653}, {0x9B7, 0x081, 2619, 653}, {0x2FF, 0x2A0, 2627, 3297},
	{0x9BF, 0x888, 2627, 3297}, {0x4BF, 0x028, 2670, 4668}, {0xB7F, 0x010, 2670, 2334},
	{0x6DF, 0x604, 2745, 620}, {0xDB7, 0xC01, 2745, 620}, {0x4FF, 0x460, 2793, 3297},
	{0x5BF, 0x508, 2793, 3297}, {0x2FF, 0x0A0, 2833, 2987}, {0x9BF, 0x088, 2833, 2987},
	{0x6DF, 0x404, 2951, 310}, {0xDB7, 0x401, 2951, 310}, {0x6FF, 0x620, 2959, 2954},
	{0xDBF, 0xC08, 2959, 2954}, {0x4DF, 0x044, 2991, 653}, {0x5B7, 0x101, 2991, 653},
	{0x1FF, 0x1C0, 2996, 1959}, {0x6DF, 0x204, 3157, 310}, {0xDB7, 0x801, 3157, 310},
	{0x3FF, 0x380, 3162, 1616}, {0x9FF, 0x8C0, 3162, 1616}, {0x6FF, 0x420, 3165, 2644},
	{0xDBF, 0x408, 3165, 2644}, {0x4FF, 0x060, 3205, 2987}, {0x5BF, 0x108, 3205, 2987},
	{0x5FF, 0x540, 3328, 1616}, {0xBFF, 0xA80, 3328, 1273}, {0x6DF, 0x004, 3363, 0},
	{0xDB7, 0x001, 3363, 0}, {0x3FF, 0x180, 3368, 1306}, {0x9FF, 0x0C0, 3368, 1306},
	{0x6FF, 0x220, 3371, 2644}, {0xDBF, 0x808, 3371, 2644}, {0x7FF, 0x700, 3494, 1273},
	{0xDFF, 0xC40, 3494, 1273}, {0xBFF, 0x880, 3534, 963}, {0xBFF, 0x280, 3534, 963},
	{0x6FF, 0x020, 3577, 2334}, {0xDBF, 0x008, 3577, 2334}, {0xFFF, 0xE00, 3660, 930},
	{0x7FF, 0x500, 3700, 963}, {0xDFF, 0x440, 3700, 963}, {0xBFF, 0x080, 3740, 653},
	{0x5FF, 0x140, 3740, 1306}, {0xFFF, 0xC00, 3866, 620}, {0xFFF, 0x600, 3866, 620},
	{0x7FF, 0x300, 3906, 963}, {0xDFF, 0x840, 3906, 963}, {0xFFF, 0x400, 4072, 310},
	{0xFFF, 0xA00, 4072, 620}, {0x7FF, 0x100, 4112, 653}, {0xDFF, 0x040, 4112, 653},
	{0xFFF, 0x800, 4278, 310}, {0xFFF, 0x200, 4278, 310}
};

const sint16 PawnFileOpening = 181;
const sint16 PawnFileEndgame = -97;
const sint16 KnightCentrOpening = 347;
const sint16 KnightCentrEndgame = 56;
const sint16 KnightRankOpening = 358;
const sint16 KnightTrapped = 3200;
const sint16 BishopCentrOpening = 147;
const sint16 BishopCentrEndgame = 49;
const sint16 BishopBackRankOpening = 251;
const sint16 BishopDiagonalOpening = 378;
const sint16 RookFileOpening = 104;
const sint16 QueenCentrOpening = 98;
const sint16 QueenCentrEndgame = 108;
const sint16 QueenBackRankOpening = 201;
const sint16 KingFileOpening = 469;
const sint16 KingCentrEndgame = 401;

const sint16 PawnFile[8] = { -3, -1, 0, 1, 1, 0, -1, -3 };
const sint16 KnightLine[8] = { -4, -2, 0, 1, 1, 0, -2, -4 };
const sint16 KnightRank[8] = { -2, -1, 0, 1, 2, 3, 2, 1 };
const sint16 BishopLine[8] = { -3, -1, 0, 1, 1, 0, -1, -3 };
const sint16 RookFile[8] = { -2, -1, 0, 1, 1, 0, -1, -2 };
const sint16 QueenLine[8] = { -3, -1, 0, 1, 1, 0, -1, -3 };
const sint16 KingLine[8] = { -3, -1, 0, 1, 1, 0, -1, -3 };
const sint16 KingFile[8] = { 3, 4, 2, 0, 0, 2, 4, 3 };

inline void init_evals(void)
{
	int i, j;

	for (i = 0; i < 4096; i++)
	{
		for (j = 0; j < PAWN_SCORE_SIZE; j++)
		{
			if ((i & pawnscore[j].mask) == pawnscore[j].bits)
			{
				PawnStruScore0[i] = pawnscore[j].score0;
				PawnStruScore1[i] = pawnscore[j].score1;
				break;
			}
		}
	}
	for (i = 0; i < 64; i++)
	{
		PieceSquareValue[WhitePawn - 2][i][0] = PawnFile[i & 7] * PawnFileOpening;
		PieceSquareValue[WhitePawn - 2][i][1] = PawnFile[i & 7] * PawnFileEndgame;
		PieceSquareValue[WhiteKnight - 2][i][0] = KnightLine[i & 7] * KnightCentrOpening +
			KnightLine[i >> 3] * KnightCentrOpening +
			KnightRank[i >> 3] * KnightRankOpening;
		PieceSquareValue[WhiteKnight - 2][i][1] = KnightLine[i & 7] * KnightCentrEndgame +
			KnightLine[i >> 3] * KnightCentrEndgame;
		PieceSquareValue[WhiteBishop - 2][i][0] = BishopLine[i & 7] * BishopCentrOpening +
			BishopLine[i >> 3] * BishopCentrOpening;
		PieceSquareValue[WhiteBishop - 2][i][1] = BishopLine[i & 7] * BishopCentrEndgame +
			BishopLine[i >> 3] * BishopCentrEndgame;
		PieceSquareValue[WhiteRook - 2][i][0] = RookFile[i & 7] * RookFileOpening;
		PieceSquareValue[WhiteRook - 2][i][1] = 0;
		PieceSquareValue[WhiteQueen - 2][i][0] = QueenLine[i & 7] * QueenCentrOpening +
			QueenLine[i >> 3] * QueenCentrOpening;
		PieceSquareValue[WhiteQueen - 2][i][1] = QueenLine[i & 7] * QueenCentrEndgame +
			QueenLine[i >> 3] * QueenCentrEndgame;
		PieceSquareValue[WhiteKing - 2][i][0] = KingFile[i & 7] * KingFileOpening;
		PieceSquareValue[WhiteKing - 2][i][1] = KingLine[i & 7] * KingCentrEndgame +
			KingLine[i >> 3] * KingCentrEndgame;
	}
	PieceSquareValue[WhitePawn - 2][35][0] += 74;
	PieceSquareValue[WhitePawn - 2][36][0] += 74;
	PieceSquareValue[WhiteKnight - 2][56][0] -= KnightTrapped;
	PieceSquareValue[WhiteKnight - 2][63][0] -= KnightTrapped;
	for (i = 0; i < 8; i++)
	{
		PieceSquareValue[WhiteBishop - 2][i][0] -= BishopBackRankOpening;
		PieceSquareValue[WhiteBishop - 2][(i << 3) | i][0] += BishopDiagonalOpening;
		PieceSquareValue[WhiteBishop - 2][((i << 3) | i) ^ 070][0] += BishopDiagonalOpening;
		PieceSquareValue[WhiteQueen - 2][i][0] -= QueenBackRankOpening;
	}
	for (i = 0; i < 12; i += 2)
		for (j = 0; j < 64; j++)
		{
			PieceSquareValue[i + 1][j][0] = -PieceSquareValue[i][j ^ 070][0];
			PieceSquareValue[i + 1][j][1] = -PieceSquareValue[i][j ^ 070][1];
		}
}
