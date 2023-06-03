#pragma once
inline struct list_t* gen_evasions(struct list_t* list, uint64 mask)
{
	uint64 atk_bm, mask_em;
	int king, square, piece, atk_square;

	if (Board->turn == White)
	{
		king = lsb(Board->mp[WhiteKing]);
		atk_bm = ((LINE3(king) | LINE4(king)) & ((Board->mp[BlackRook]) | (Board->mp[BlackQueen]))) |
			((LINE1(king) | LINE2(king)) & ((Board->mp[BlackBishop]) | (Board->mp[BlackQueen]))) |
			(MaskKnightMoves[king] & (Board->mp[BlackKnight])) |
			(MaskPawnAttacks[0][king] & (Board->mp[BlackPawn]));
		atk_square = lsb(atk_bm);
		piece = Board->square[atk_square];
		mask = mask & (MaskPieceIsPawn[piece] | MaskEvasionMoves[king][atk_square][1]) &
			MaskKingMoves[king] & (~(Board->mp[White]));
		atk_bm &= (atk_bm - 1);
		if (atk_bm != 0)
		{
			square = lsb(atk_bm);
			piece = Board->square[square];
			for (mask = mask & (MaskPieceIsPawn[piece] | MaskEvasionMoves[king][square][1]); mask != 0; mask &= (mask -
				1))
			{
				square = lsb(mask);
				(list++)->move = (king << 6) | square;
			}
			list->move = list->score = 0;
			return (list - 1);
		}
		for (; mask != 0; mask &= (mask - 1))
		{
			(list++)->move = (king << 6) | lsb(mask);
		}
		if (WhitePawnCaptures1[atk_square] & (Board->mp[WhitePawn]))
		{
			list->move = ((atk_square - 9) << 6) | atk_square;
			if (atk_square >= 56)
			{
				(list++)->move |= FlagPromoQueen;
				(list++)->move = ((atk_square - 9) << 6) | atk_square | FlagPromoRook;
				(list++)->move = ((atk_square - 9) << 6) | atk_square | FlagPromoBishop;
				list->move = ((atk_square - 9) << 6) | atk_square | FlagPromoKnight;
			}
			list++;
		}
		if (WhitePawnCaptures2[atk_square] & (Board->mp[WhitePawn]))
		{
			list->move = ((atk_square - 7) << 6) | atk_square;
			if (atk_square >= 56)
			{
				(list++)->move |= FlagPromoQueen;
				(list++)->move = ((atk_square - 7) << 6) | atk_square | FlagPromoRook;
				(list++)->move = ((atk_square - 7) << 6) | atk_square | FlagPromoBishop;
				list->move = ((atk_square - 7) << 6) | atk_square | FlagPromoKnight;
			}
			list++;
		}
		if (Board->ep_square != 0 && Board->ep_square == (atk_square + 8))
		{
			if (WhitePawnCaptures1[atk_square + 8] & (Board->mp[WhitePawn]))
			{
				(list++)->move = ((atk_square - 1) << 6) | (atk_square + 8) | FlagEnpassant;
			}
			if (WhitePawnCaptures2[atk_square + 8] & (Board->mp[WhitePawn]))
			{
				(list++)->move = ((atk_square + 1) << 6) | (atk_square + 8) | FlagEnpassant;
			}
		}
		mask_em = MaskEvasionMoves[king][atk_square][0];
		mask = (MaskClearSquare[atk_square] >> 8) & (mask_em >> 8) & (Board->mp[WhitePawn]);
		for (; mask != 0; mask &= (mask - 1))
		{
			square = lsb(mask);
			list->move = (square << 6) | (square + 8);
			if (square >= 48)
			{
				(list++)->move |= FlagPromoQueen;
				(list++)->move = (square << 6) | (square + 8) | FlagPromoRook;
				(list++)->move = (square << 6) | (square + 8) | FlagPromoBishop;
				list->move = (square << 6) | (square + 8) | FlagPromoKnight;
			}
			list++;
		}
		mask = (~((Board->md1) >> 8)) &
			(MaskClearSquare[atk_square] >> 16) &
			(mask_em >> 16) &
			(Board->mp[WhitePawn]);
		for (mask = mask & 0xFF00; mask != 0; mask &= (mask - 1))
		{
			square = lsb(mask);
			(list++)->move = (square << 6) | (square + 16);
		}
		for (atk_bm = Board->mp[WhiteKnight]; atk_bm != 0; atk_bm &= (atk_bm - 1))
		{
			square = lsb(atk_bm);
			for (mask = MaskKnightMoves[square] & mask_em; mask != 0; mask &= (mask - 1))
			{
				(list++)->move = (square << 6) | lsb(mask);
			}
		}
		for (atk_bm = (Board->mp[WhiteBishop]) | (Board->mp[WhiteQueen]); atk_bm != 0; atk_bm &= (atk_bm - 1))
		{
			square = lsb(atk_bm);
			for (mask = (LINE1(square) | LINE2(square)) & mask_em; mask != 0; mask &= (mask - 1))
			{
				(list++)->move = (square << 6) | lsb(mask);
			}
		}
		for (atk_bm = (Board->mp[WhiteRook]) | (Board->mp[WhiteQueen]); atk_bm != 0; atk_bm &= (atk_bm - 1))
		{
			square = lsb(atk_bm);
			for (mask = (LINE3(square) | LINE4(square)) & mask_em; mask != 0; mask &= (mask - 1))
			{
				(list++)->move = (square << 6) | lsb(mask);
			}
		}
	}
	else
	{
		king = lsb(Board->mp[BlackKing]);
		atk_bm = ((LINE3(king) | LINE4(king)) & ((Board->mp[WhiteRook]) | (Board->mp[WhiteQueen]))) |
			((LINE1(king) | LINE2(king)) & ((Board->mp[WhiteBishop]) | (Board->mp[WhiteQueen]))) |
			(MaskKnightMoves[king] & (Board->mp[WhiteKnight])) |
			(MaskPawnAttacks[1][king] & (Board->mp[WhitePawn]));
		atk_square = lsb(atk_bm);
		piece = Board->square[atk_square];
		mask = mask & (MaskPieceIsPawn[piece] | MaskEvasionMoves[king][atk_square][1]) &
			MaskKingMoves[king] & (~(Board->mp[Black]));
		atk_bm &= (atk_bm - 1);
		if (atk_bm != 0)
		{
			square = lsb(atk_bm);
			piece = Board->square[square];
			for (mask = mask & (MaskPieceIsPawn[piece] | MaskEvasionMoves[king][square][1]); mask != 0; mask &= (mask -
				1))
			{
				square = lsb(mask);
				(list++)->move = (king << 6) | square;
			}
			list->move = list->score = 0;
			return (list - 1);
		}
		for (; mask != 0; mask &= (mask - 1))
		{
			(list++)->move = (king << 6) | lsb(mask);
		}
		if (BlackPawnCaptures1[atk_square] & (Board->mp[BlackPawn]))
		{
			list->move = ((atk_square + 7) << 6) | atk_square;
			if (atk_square <= 7)
			{
				(list++)->move |= FlagPromoQueen;
				(list++)->move = ((atk_square + 7) << 6) | atk_square | FlagPromoRook;
				(list++)->move = ((atk_square + 7) << 6) | atk_square | FlagPromoBishop;
				list->move = ((atk_square + 7) << 6) | atk_square | FlagPromoKnight;
			}
			list++;
		}
		if (BlackPawnCaptures2[atk_square] & (Board->mp[BlackPawn]))
		{
			list->move = ((atk_square + 9) << 6) | atk_square;
			if (atk_square <= 7)
			{
				(list++)->move |= FlagPromoQueen;
				(list++)->move = ((atk_square + 9) << 6) | atk_square | FlagPromoRook;
				(list++)->move = ((atk_square + 9) << 6) | atk_square | FlagPromoBishop;
				list->move = ((atk_square + 9) << 6) | atk_square | FlagPromoKnight;
			}
			list++;
		}
		if (Board->ep_square != 0 && Board->ep_square == (atk_square - 8))
		{
			if (BlackPawnCaptures1[atk_square - 8] & (Board->mp[BlackPawn]))
			{
				(list++)->move = ((atk_square - 1) << 6) | (atk_square - 8) | FlagEnpassant;
			}
			if (BlackPawnCaptures2[atk_square - 8] & (Board->mp[BlackPawn]))
			{
				(list++)->move = ((atk_square + 1) << 6) | (atk_square - 8) | FlagEnpassant;
			}
		}
		mask_em = MaskEvasionMoves[king][atk_square][0];
		mask = (MaskClearSquare[atk_square] << 8) & (mask_em << 8) & (Board->mp[BlackPawn]);
		for (; mask != 0; mask &= (mask - 1))
		{
			square = lsb(mask);
			list->move = (square << 6) | (square - 8);
			if (square <= 15)
			{
				(list++)->move |= FlagPromoQueen;
				(list++)->move = (square << 6) | (square - 8) | FlagPromoRook;
				(list++)->move = (square << 6) | (square - 8) | FlagPromoBishop;
				list->move = (square << 6) | (square - 8) | FlagPromoKnight;
			}
			list++;
		}
		mask = (((MaskClearSquare[atk_square] & mask_em) & 0xFF00000000) << 16) &
			(~((Board->md1) << 8)) &
			(Board->mp[BlackPawn]);
		for (; mask != 0; mask &= (mask - 1))
		{
			square = lsb(mask);
			(list++)->move = (square << 6) | (square - 16);
		}
		for (atk_bm = Board->mp[BlackKnight]; atk_bm != 0; atk_bm &= (atk_bm - 1))
		{
			square = lsb(atk_bm);
			for (mask = MaskKnightMoves[square] & mask_em; mask != 0; mask &= (mask - 1))
			{
				(list++)->move = (square << 6) | lsb(mask);
			}
		}
		for (atk_bm = (Board->mp[BlackBishop]) | (Board->mp[BlackQueen]); atk_bm != 0; atk_bm &= (atk_bm - 1))
		{
			square = lsb(atk_bm);
			for (mask = (LINE1(square) | LINE2(square)) & mask_em; mask != 0; mask &= (mask - 1))
			{
				(list++)->move = (square << 6) | lsb(mask);
			}
		}
		for (atk_bm = (Board->mp[BlackRook]) | (Board->mp[BlackQueen]); atk_bm != 0; atk_bm &= (atk_bm - 1))
		{
			square = lsb(atk_bm);
			for (mask = (LINE3(square) | LINE4(square)) & mask_em; mask != 0; mask &= (mask - 1))
			{
				(list++)->move = (square << 6) | lsb(mask);
			}
		}
	}
	list->move = list->score = 0;
	return (list - 1);
}

inline void gen_captures(struct list_t* list, uint64 mask_w, uint64 mask_b)
{
	uint64 mask_from, mask_to;
	int from, to;

	if (Board->turn == White)
	{
		for (mask_from = Board->mp[WhiteKnight]; mask_from != 0; mask_from &= (mask_from - 1))
		{
			from = lsb(mask_from);
			for (mask_to = MaskKnightMoves[from] & mask_b; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = (Board->square[to]) * 3 + 12;
			}
		}
		for (mask_from = Board->mp[WhiteBishop]; mask_from != 0; mask_from &= (mask_from - 1))
		{
			from = lsb(mask_from);
			for (mask_to = (LINE1(from) | LINE2(from)) & mask_b; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = (Board->square[to]) * 3 + 11;
			}
		}
		for (mask_from = Board->mp[WhiteRook]; mask_from != 0; mask_from &= (mask_from - 1))
		{
			from = lsb(mask_from);
			for (mask_to = (LINE3(from) | LINE4(from)) & mask_b; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = (Board->square[to]) * 3 + 10;
			}
		}
		for (mask_from = Board->mp[WhiteQueen]; mask_from != 0; mask_from &= (mask_from - 1))
		{
			from = lsb(mask_from);
			for (mask_to = (LINE1(from) | LINE2(from) | LINE3(from) | LINE4(from)) & mask_b; mask_to != 0; mask_to &= (
				mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = (Board->square[to]) * 3 + 9;
			}
		}
		from = lsb(Board->mp[WhiteKing]);
		for (mask_to = MaskKingMoves[from] & mask_b; mask_to != 0; mask_to &= (mask_to - 1))
		{
			to = lsb(mask_to);
			list->move = (from << 6) | to;
			(list++)->score = (Board->square[to]) * 3 + 8;
		}
		for (mask_from = (Board->mp[WhitePawn]) & 0x00FF000000000000; mask_from != 0; mask_from &= (mask_from - 1))
		{
			from = lsb(mask_from);
			to = from + 8;
			if ((Board->square[to]) == 0)
			{
				list->move = (from << 6) | to | FlagPromoQueen;
				(list++)->score = 15;
				list->move = (from << 6) | to | FlagPromoRook;
				(list++)->score = 14;
				list->move = (from << 6) | to | FlagPromoBishop;
				(list++)->score = 13;
				list->move = (from << 6) | to | FlagPromoKnight;
				(list++)->score = 12;
			}
			to = from + 7;
			if (from != 48 && (((uint64)1 << to) & Board->mp[Black]) != 0)
			{
				list->move = (from << 6) | to | FlagPromoQueen;
				(list++)->score = (Board->square[to]) * 3 + 13;
				list->move = (from << 6) | to | FlagPromoRook;
				(list++)->score = (Board->square[to]) * 3 + 12;
				list->move = (from << 6) | to | FlagPromoBishop;
				(list++)->score = (Board->square[to]) * 3 + 11;
				list->move = (from << 6) | to | FlagPromoKnight;
				(list++)->score = (Board->square[to]) * 3 + 10;
			}
			to = from + 9;
			if (from != 55 && (((uint64)1 << to) & Board->mp[Black]) != 0)
			{
				list->move = (from << 6) | to | FlagPromoQueen;
				(list++)->score = (Board->square[to]) * 3 + 13;
				list->move = (from << 6) | to | FlagPromoRook;
				(list++)->score = (Board->square[to]) * 3 + 12;
				list->move = (from << 6) | to | FlagPromoBishop;
				(list++)->score = (Board->square[to]) * 3 + 11;
				list->move = (from << 6) | to | FlagPromoKnight;
				(list++)->score = (Board->square[to]) * 3 + 10;
			}
		}
		for (mask_to = (((Board->mp[WhitePawn]) & 0x0000FEFEFEFEFE00) << 7) & mask_b; mask_to != 0; mask_to &= (mask_to
			- 1))
		{
			to = lsb(mask_to);
			from = to - 7;
			list->move = (from << 6) | to;
			(list++)->score = (Board->square[to]) * 3 + 13;
		}
		for (mask_to = (((Board->mp[WhitePawn]) & 0x00007F7F7F7F7F00) << 9) & mask_b; mask_to != 0; mask_to &= (mask_to
			- 1))
		{
			to = lsb(mask_to);
			from = to - 9;
			list->move = (from << 6) | to;
			(list++)->score = (Board->square[to]) * 3 + 13;
		}
		if ((to = Board->ep_square) != 0)
		{
			mask_to = (((Board->mp[WhitePawn]) & 0x00FEFEFEFEFEFEFE) << 7) & ((uint64)1 << to);
			if (mask_to != 0)
			{
				from = to - 7;
				list->move = (from << 6) | to | FlagEnpassant;
				(list++)->score = 22;
			}
			mask_to = (((Board->mp[WhitePawn]) & 0xFFFF7F7F7F7F7F7F) << 9) & ((uint64)1 << to);
			if (mask_to != 0)
			{
				from = to - 9;
				list->move = (from << 6) | to | FlagEnpassant;
				(list++)->score = 22;
			}
		}
	}
	else
	{
		for (mask_from = Board->mp[BlackKnight]; mask_from != 0; mask_from &= (mask_from - 1))
		{
			from = lsb(mask_from);
			for (mask_to = MaskKnightMoves[from] & mask_w; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = (Board->square[to]) * 3 + 15;
			}
		}
		for (mask_from = Board->mp[BlackBishop]; mask_from != 0; mask_from &= (mask_from - 1))
		{
			from = lsb(mask_from);
			for (mask_to = (LINE1(from) | LINE2(from)) & mask_w; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = (Board->square[to]) * 3 + 14;
			}
		}
		for (mask_from = Board->mp[BlackRook]; mask_from != 0; mask_from &= (mask_from - 1))
		{
			from = lsb(mask_from);
			for (mask_to = (LINE3(from) | LINE4(from)) & mask_w; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = (Board->square[to]) * 3 + 13;
			}
		}
		for (mask_from = Board->mp[BlackQueen]; mask_from != 0; mask_from &= (mask_from - 1))
		{
			from = lsb(mask_from);
			for (mask_to = (LINE1(from) | LINE2(from) | LINE3(from) | LINE4(from)) & mask_w; mask_to != 0; mask_to &= (
				mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = (Board->square[to]) * 3 + 12;
			}
		}
		from = lsb(Board->mp[BlackKing]);
		for (mask_to = MaskKingMoves[from] & mask_w; mask_to != 0; mask_to &= (mask_to - 1))
		{
			to = lsb(mask_to);
			list->move = (from << 6) | to;
			(list++)->score = (Board->square[to]) * 3 + 11;
		}
		for (mask_from = (Board->mp[BlackPawn]) & 0x000000000000FF00; mask_from != 0; mask_from &= (mask_from - 1))
		{
			from = lsb(mask_from);
			to = from - 8;
			if ((Board->square[to]) == 0)
			{
				list->move = (from << 6) | to | FlagPromoQueen;
				(list++)->score = 15;
				list->move = (from << 6) | to | FlagPromoRook;
				(list++)->score = 14;
				list->move = (from << 6) | to | FlagPromoBishop;
				(list++)->score = 13;
				list->move = (from << 6) | to | FlagPromoKnight;
				(list++)->score = 12;
			}
			to = from - 9;
			if (from != 8 && (((uint64)1 << to) & Board->mp[White]) != 0)
			{
				list->move = (from << 6) | to | FlagPromoQueen;
				(list++)->score = (Board->square[to]) * 3 + 16;
				list->move = (from << 6) | to | FlagPromoRook;
				(list++)->score = (Board->square[to]) * 3 + 15;
				list->move = (from << 6) | to | FlagPromoBishop;
				(list++)->score = (Board->square[to]) * 3 + 14;
				list->move = (from << 6) | to | FlagPromoKnight;
				(list++)->score = (Board->square[to]) * 3 + 13;
			}
			to = from - 7;
			if (from != 15 && (((uint64)1 << to) & Board->mp[White]) != 0)
			{
				list->move = (from << 6) | to | FlagPromoQueen;
				(list++)->score = (Board->square[to]) * 3 + 16;
				list->move = (from << 6) | to | FlagPromoRook;
				(list++)->score = (Board->square[to]) * 3 + 15;
				list->move = (from << 6) | to | FlagPromoBishop;
				(list++)->score = (Board->square[to]) * 3 + 14;
				list->move = (from << 6) | to | FlagPromoKnight;
				(list++)->score = (Board->square[to]) * 3 + 13;
			}
		}
		for (mask_to = (((Board->mp[BlackPawn]) >> 9) & mask_w) & 0x00007F7F7F7F7F00; mask_to != 0; mask_to &= (mask_to
			- 1))
		{
			to = lsb(mask_to);
			from = to + 9;
			list->move = (from << 6) | to;
			(list++)->score = (Board->square[to]) * 3 + 16;
		}
		for (mask_to = (((Board->mp[BlackPawn]) >> 7) & mask_w) & 0x0000FEFEFEFEFE00; mask_to != 0; mask_to &= (mask_to
			- 1))
		{
			to = lsb(mask_to);
			from = to + 7;
			list->move = (from << 6) | to;
			(list++)->score = (Board->square[to]) * 3 + 16;
		}
		if ((to = Board->ep_square) != 0)
		{
			mask_to = (((Board->mp[BlackPawn]) >> 9) & 0x007F7F7F7F7F7F7F) & ((uint64)1 << to);
			if (mask_to != 0)
			{
				from = to + 9;
				list->move = (from << 6) | to | FlagEnpassant;
				(list++)->score = 22;
			}
			mask_to = (((Board->mp[BlackPawn]) >> 7) & 0x00FEFEFEFEFEFEFE) & ((uint64)1 << to);
			if (mask_to != 0)
			{
				from = to + 7;
				list->move = (from << 6) | to | FlagEnpassant;
				(list++)->score = 22;
			}
		}
	}
	list->move = 0;
}

inline void gen_quiet_moves(struct list_t* list, uint64 mask, int tt_move, int killer1, int killer2)
{
	int move, score, from, to;
	uint64 bme, mask_to;
	struct list_t* list_head, * pi, * pj;

	list_head = list;
	bme = ~(Board->md1);
	if (Board->turn == White)
	{
		if (((Board->flags) & 1) && (((Board->md1) | mask) & 0x60) == 0)
		{
			list->move = 0x106 | FlagCastle;
			(list++)->score = History[WhiteKing - 2][6];
		}
		if (((Board->flags) & 2) && ((Board->md1) & 0x0E) == 0 && (mask & 0x0C) == 0)
		{
			list->move = 0x102 | FlagCastle;
			(list++)->score = History[WhiteKing - 2][2];
		}
		for (mask = (((Board->mp[WhitePawn]) & 0x0000FFFFFFFFFF00) << 8) & bme; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			if (((from & 0xFFFFFFF8) == 16) && Board->square[from + 8] == 0)
			{
				list->move = ((from - 8) << 6) | (from + 8);
				(list++)->score = History[WhitePawn - 2][from + 8];
			}
			list->move = ((from - 8) << 6) | from;
			(list++)->score = History[WhitePawn - 2][from];
		}
		for (mask = Board->mp[WhiteKnight]; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			for (mask_to = MaskKnightMoves[from] & bme; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = History[WhiteKnight - 2][to];
			}
		}
		for (mask = Board->mp[WhiteQueen]; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			for (mask_to = (LINE1(from) | LINE2(from) | LINE3(from) | LINE4(from)) & bme; mask_to != 0; mask_to &= (
				mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = History[WhiteQueen - 2][to];
			}
		}
		for (mask = Board->mp[WhiteBishop]; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			for (mask_to = (LINE1(from) | LINE2(from)) & bme; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = History[WhiteBishop - 2][to];
			}
		}
		for (mask = Board->mp[WhiteRook]; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			for (mask_to = (LINE3(from) | LINE4(from)) & bme; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = History[WhiteRook - 2][to];
			}
		}
		from = lsb(Board->mp[WhiteKing]);
		for (mask_to = MaskKingMoves[from] & bme; mask_to != 0; mask_to &= (mask_to - 1))
		{
			to = lsb(mask_to);
			list->move = (from << 6) | to;
			(list++)->score = History[WhiteKing - 2][to];
		}
	}
	else
	{
		if (((Board->flags) & 4) && (((Board->md1) | mask) & 0x6000000000000000) == 0)
		{
			list->move = 0xF3E | FlagCastle;
			(list++)->score = History[BlackKing - 2][62];
		}
		if (((Board->flags) & 8) && ((Board->md1) & 0x0E00000000000000) == 0 && (mask & 0x0C00000000000000) == 0)
		{
			list->move = 0xF3A | FlagCastle;
			(list++)->score = History[BlackKing - 2][58];
		}
		for (mask = (((Board->mp[BlackPawn]) >> 8) & 0x0000FFFFFFFFFF00) & bme; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			if (((from & 0xFFFFFFF8) == 40) && Board->square[from - 8] == 0)
			{
				list->move = ((from + 8) << 6) | (from - 8);
				(list++)->score = History[BlackPawn - 2][from - 8];
			}
			list->move = ((from + 8) << 6) | from;
			(list++)->score = History[BlackPawn - 2][from];
		}
		for (mask = Board->mp[BlackKnight]; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			for (mask_to = MaskKnightMoves[from] & bme; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = History[BlackKnight - 2][to];
			}
		}
		for (mask = Board->mp[BlackQueen]; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			for (mask_to = (LINE1(from) | LINE2(from) | LINE3(from) | LINE4(from)) & bme; mask_to != 0; mask_to &= (
				mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = History[BlackQueen - 2][to];
			}
		}
		for (mask = Board->mp[BlackBishop]; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			for (mask_to = (LINE1(from) | LINE2(from)) & bme; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = History[BlackBishop - 2][to];
			}
		}
		for (mask = Board->mp[BlackRook]; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			for (mask_to = (LINE3(from) | LINE4(from)) & bme; mask_to != 0; mask_to &= (mask_to - 1))
			{
				to = lsb(mask_to);
				list->move = (from << 6) | to;
				(list++)->score = History[BlackRook - 2][to];
			}
		}
		from = lsb(Board->mp[BlackKing]);
		for (mask_to = MaskKingMoves[from] & bme; mask_to != 0; mask_to &= (mask_to - 1))
		{
			to = lsb(mask_to);
			list->move = (from << 6) | to;
			(list++)->score = History[BlackKing - 2][to];
		}
	}
	list->move = 0;
	list->score = 0;
	if (list == list_head) return;
	for (pi = list - 1; pi >= list_head; pi--)
	{
		if (pi->move != tt_move && pi->move != killer1 && pi->move != killer2) break;
		pi->move = 0;
		pi->score = 0;
	}
	while (pi > list_head)
	{
		pi--;
		move = pi->move;
		if (move != tt_move && move != killer1 && move != killer2)
		{
			score = pi->score;
			for (pj = pi; score < (pj + 1)->score; pj++)
			{
				pj->move = (pj + 1)->move;
				pj->score = (pj + 1)->score;
			}
			pj->move = move;
			pj->score = score;
		}
		else
		{
			list--;
			if (pi < list) memcpy(pi, pi + 1, (list - pi) * sizeof(struct list_t));
			list->move = 0;
			list->score = 0;
		}
	}
}

inline void gen_checks(struct list_t* list, uint64 mask_w, uint64 mask_b)
{
	uint64 mask, mask_to;
	int from, to, piece;

	if (Board->turn == White)
	{
		int bking;
		bking = lsb(Board->mp[BlackKing]);
		for (mask = Board->mp[WhiteKnight]; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			mask_to = MaskKnightMoves[from] & MaskKnightMoves[bking] & ((Board->mp[White]) ^ mask_b);
			for (; mask_to != 0; mask_to &= (mask_to - 1))
				(list++)->move = (from << 6) | lsb(mask_to);
		}
		for (mask = (Board->mp[WhiteBishop]) | (Board->mp[WhiteQueen]); mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			mask_to = (LINE1(from) & LINE1(bking) & mask_b) |
				(LINE2(from) & LINE2(bking) & mask_b);
			if (mask_to != 0)
			{
				to = lsb(mask_to);
				piece = Board->square[to];
				if (piece == BlackPawn) (list++)->move = (from << 6) | to;
				else if (piece == WhitePawn)
				{
					if (to <= 47 && Board->square[to + 8] == 0)
					{
						(list++)->move = (to << 6) | (to + 8);
						if ((to & 0xFFFFFFF8) == 8 && Board->square[to + 16] == 0)
							(list++)->move = (to << 6) | (to + 16);
					}
					if (((mask_to & 0xFFFF7F7F7F7F7F7F) << 9) & (Board->mp[Black]) & mask_b)
						(list++)->move = (to << 6) | (to + 9);
					if (((mask_to & 0x00FEFEFEFEFEFEFE) << 7) & (Board->mp[Black]) & mask_b)
						(list++)->move = (to << 6) | (to + 7);
				}
				else if (piece == WhiteKnight)
				{
					mask_to = MaskKnightMoves[to] & ((Board->mp[White]) ^ mask_b);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
				else if (piece == WhiteRook)
				{
					mask_to = (LINE3(to) | LINE4(to)) & ((Board->mp[White]) ^ mask_b);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
				else if (piece == WhiteKing)
				{
					mask_to = MaskKingMoves[to] & MaskDiags[bking] & ((Board->mp[White]) ^ mask_b);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
			}
			else
			{
				mask_to = (LINE1(from) & LINE2(bking) & mask_b) |
					(LINE2(from) & LINE1(bking) & mask_b);
				if (Board->square[from] == WhiteQueen)
				{
					mask_to |= ((LINE3(from) | LINE4(from)) &
						((LINE2(bking) & mask_b) | (LINE1(bking) & mask_b))) |
						((LINE1(from) | LINE2(from)) &
							((LINE3(bking) & mask_b) | (LINE4(bking) & mask_b)));
				}
				mask_to &= (Board->mp[White]) ^ mask_b;
				for (; mask_to != 0; mask_to &= (mask_to - 1))
					(list++)->move = (from << 6) | lsb(mask_to);
			}
		}
		for (mask = (Board->mp[WhiteRook]) | (Board->mp[WhiteQueen]); mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			mask_to = (LINE3(from) & LINE3(bking) & mask_b) |
				(LINE4(from) & LINE4(bking) & mask_b);
			if (mask_to != 0)
			{
				to = lsb(mask_to);
				piece = Board->square[to];
				if (piece == BlackPawn) (list++)->move = (from << 6) | to;
				else if (piece == WhitePawn)
				{
					if ((mask_to & LINE3(from)) && to <= 47 && Board->square[to + 8] == 0)
					{
						(list++)->move = (to << 6) | (to + 8);
						if ((to & 0xFFFFFFF8) == 8 && Board->square[to + 16] == 0)
							(list++)->move = (to << 6) | (to + 16);
					}
					if (((mask_to & 0xFFFF7F7F7F7F7F7F) << 9) & (Board->mp[Black]) & mask_b)
						(list++)->move = (to << 6) | (to + 9);
					if (((mask_to & 0x00FEFEFEFEFEFEFE) << 7) & (Board->mp[Black]) & mask_b)
						(list++)->move = (to << 6) | (to + 7);
				}
				else if (piece == WhiteKnight)
				{
					mask_to = MaskKnightMoves[to] & ((Board->mp[White]) ^ mask_b);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
				else if (piece == WhiteBishop)
				{
					mask_to = (LINE1(to) | LINE2(to)) & ((Board->mp[White]) ^ mask_b);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
				else if (piece == WhiteKing)
				{
					mask_to = MaskKingMoves[to] & MaskLines[bking] & ((Board->mp[White]) ^ mask_b);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
			}
			else
			{
				mask_to = ((LINE3(from) & LINE4(bking) & mask_b) |
					(LINE4(from) & LINE3(bking) & mask_b)) &
					((Board->mp[White]) ^ mask_b);
				for (; mask_to != 0; mask_to &= (mask_to - 1))
					(list++)->move = (from << 6) | lsb(mask_to);
			}
		}
		mask = (((Board->mp[WhitePawn]) & 0x0000FEFEFEFEFEFE) << 15) & (Board->mp[BlackKing]);
		if (mask && Board->square[bking - 7] == 0) (list++)->move = ((bking - 15) << 6) | (bking - 7);
		mask = (((Board->mp[WhitePawn]) & 0xFFFFFF7F7F7F7F7F) << 17) & (Board->mp[BlackKing]);
		if (mask && Board->square[bking - 9] == 0) (list++)->move = ((bking - 17) << 6) | (bking - 9);
		mask = ((Board->mp[BlackKing]) >> 7) &
			(((Board->mp[WhitePawn]) & 0x00FCFCFCFCFCFCFC) << 7) &
			(Board->mp[Black]) & mask_b;
		if (mask) (list++)->move = ((bking - 14) << 6) | (bking - 7);
		mask = ((Board->mp[BlackKing]) >> 9) &
			(((Board->mp[WhitePawn]) & 0x00FEFEFEFEFEFEFE) << 7) &
			(Board->mp[Black]) & mask_b;
		if (mask) (list++)->move = ((bking - 16) << 6) | (bking - 9);
		mask = ((Board->mp[BlackKing]) >> 7) &
			(((Board->mp[WhitePawn]) & 0xFFFF7F7F7F7F7F7F) << 9) &
			(Board->mp[Black]) & mask_b;
		if (mask) (list++)->move = ((bking - 16) << 6) | (bking - 7);
		mask = ((Board->mp[BlackKing]) >> 9) &
			(((Board->mp[WhitePawn]) & 0x003F3F3F3F3F3F3F) << 9) &
			(Board->mp[Black]) & mask_b;
		if (mask) (list++)->move = ((bking - 18) << 6) | (bking - 9);
		mask = (((Board->mp[WhitePawn]) & 0x000000000000FE00) << 23) & (Board->mp[BlackKing]);
		if (mask && Board->square[bking - 7] == 0 && Board->square[bking - 15] == 0)
			(list++)->move = ((bking - 23) << 6) | (bking - 7);
		mask = (((Board->mp[WhitePawn]) & 0x0000000000007F00) << 25) & (Board->mp[BlackKing]);
		if (mask && Board->square[bking - 9] == 0 && Board->square[bking - 17] == 0)
			(list++)->move = ((bking - 25) << 6) | (bking - 9);
	}
	else
	{
		int wking;
		wking = lsb(Board->mp[WhiteKing]);
		for (mask = Board->mp[BlackKnight]; mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			mask_to = MaskKnightMoves[from] & MaskKnightMoves[wking] & ((Board->mp[Black]) ^ mask_w);
			for (; mask_to != 0; mask_to &= (mask_to - 1))
				(list++)->move = (from << 6) | lsb(mask_to);
		}
		for (mask = (Board->mp[BlackBishop]) | (Board->mp[BlackQueen]); mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			mask_to = (LINE1(from) & LINE1(wking) & mask_w) |
				(LINE2(from) & LINE2(wking) & mask_w);
			if (mask_to != 0)
			{
				to = lsb(mask_to);
				piece = Board->square[to];
				if (piece == WhitePawn) (list++)->move = (from << 6) | to;
				else if (piece == BlackPawn)
				{
					if (to >= 16 && Board->square[to - 8] == 0)
					{
						(list++)->move = (to << 6) | (to - 8);
						if ((to & 0xFFFFFFF8) == 48 && Board->square[to - 16] == 0)
							(list++)->move = (to << 6) | (to - 16);
					}
					if (((mask_to >> 7) & (Board->mp[White]) & mask_w) & 0x00FEFEFEFEFEFEFE)
						(list++)->move = (to << 6) | (to - 7);
					if (((mask_to >> 9) & (Board->mp[White]) & mask_w) & 0x007F7F7F7F7F7F7F)
						(list++)->move = (to << 6) | (to - 9);
				}
				else if (piece == BlackKnight)
				{
					mask_to = MaskKnightMoves[to] & ((Board->mp[Black]) ^ mask_w);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
				else if (piece == BlackRook)
				{
					mask_to = (LINE3(to) | LINE4(to)) & ((Board->mp[Black]) ^ mask_w);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
				else if (piece == BlackKing)
				{
					mask_to = MaskKingMoves[to] & MaskDiags[wking] & ((Board->mp[Black]) ^ mask_w);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
			}
			else
			{
				mask_to = (LINE1(from) & LINE2(wking) & mask_w) |
					(LINE2(from) & LINE1(wking) & mask_w);
				if (Board->square[from] == BlackQueen)
				{
					mask_to |= ((LINE3(from) | LINE4(from)) &
						((LINE2(wking) & mask_w) | (LINE1(wking) & mask_w))) |
						((LINE1(from) | LINE2(from)) &
							((LINE3(wking) & mask_w) | (LINE4(wking) & mask_w)));
				}
				mask_to &= (Board->mp[Black]) ^ mask_w;
				for (; mask_to != 0; mask_to &= (mask_to - 1))
					(list++)->move = (from << 6) | lsb(mask_to);
			}
		}
		for (mask = (Board->mp[BlackRook]) | (Board->mp[BlackQueen]); mask != 0; mask &= (mask - 1))
		{
			from = lsb(mask);
			mask_to = (LINE3(from) & (LINE3(wking) & mask_w)) |
				(LINE4(from) & (LINE4(wking) & mask_w));
			if (mask_to != 0)
			{
				to = lsb(mask_to);
				piece = Board->square[to];
				if (piece == WhitePawn) (list++)->move = (from << 6) | to;
				else if (piece == BlackPawn)
				{
					if ((mask_to & LINE3(from)) && to >= 16 && Board->square[to - 8] == 0)
					{
						(list++)->move = (to << 6) | (to - 8);
						if ((to & 0xFFFFFFF8) == 48 && Board->square[to - 16] == 0)
							(list++)->move = (to << 6) | (to - 16);
					}
					if (((mask_to >> 7) & (Board->mp[White]) & mask_w) & 0x00FEFEFEFEFEFEFE)
						(list++)->move = (to << 6) | (to - 7);
					if (((mask_to >> 9) & (Board->mp[White]) & mask_w) & 0x007F7F7F7F7F7F7F)
						(list++)->move = (to << 6) | (to - 9);
				}
				else if (piece == BlackKnight)
				{
					mask_to = MaskKnightMoves[to] & ((Board->mp[Black]) ^ mask_w);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
				else if (piece == BlackBishop)
				{
					mask_to = (LINE1(to) | LINE2(to)) & ((Board->mp[Black]) ^ mask_w);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
				else if (piece == BlackKing)
				{
					mask_to = MaskKingMoves[to] & MaskLines[wking] & ((Board->mp[Black]) ^ mask_w);
					for (; mask_to != 0; mask_to &= (mask_to - 1))
						(list++)->move = (to << 6) | lsb(mask_to);
				}
			}
			else
			{
				mask_to = ((LINE3(from) & LINE4(wking) & mask_w) |
					(LINE4(from) & LINE3(wking) & mask_w)) &
					((Board->mp[Black]) ^ mask_w);
				for (; mask_to != 0; mask_to &= (mask_to - 1))
					(list++)->move = (from << 6) | lsb(mask_to);
			}
		}
		mask = ((Board->mp[BlackPawn]) >> 17) & (Board->mp[WhiteKing]) & 0x00007F7F7F7F7F7F;
		if (mask && Board->square[wking + 9] == 0) (list++)->move = ((wking + 17) << 6) | (wking + 9);
		mask = ((Board->mp[BlackPawn]) >> 15) & (Board->mp[WhiteKing]) & 0x0000FEFEFEFEFEFE;
		if (mask && Board->square[wking + 7] == 0) (list++)->move = ((wking + 15) << 6) | (wking + 7);
		mask = (((Board->mp[WhiteKing]) & 0x00003F3F3F3F3F3F) << 9) &
			((Board->mp[BlackPawn]) >> 9) &
			(Board->mp[White]) & mask_w;
		if (mask) (list++)->move = ((wking + 18) << 6) | (wking + 9);
		mask = (((Board->mp[WhiteKing]) & 0x0000FEFEFEFEFEFE) << 7) &
			((Board->mp[BlackPawn]) >> 9) &
			(Board->mp[White]) & mask_w;
		if (mask) (list++)->move = ((wking + 16) << 6) | (wking + 7);
		mask = (((Board->mp[WhiteKing]) & 0x00007F7F7F7F7F7F) << 9) &
			((Board->mp[BlackPawn]) >> 7) &
			(Board->mp[White]) & mask_w;
		if (mask) (list++)->move = ((wking + 16) << 6) | (wking + 9);
		mask = (((Board->mp[WhiteKing]) & 0x0000FCFCFCFCFCFC) << 7) &
			((Board->mp[BlackPawn]) >> 7) &
			(Board->mp[White]) & mask_w;
		if (mask) (list++)->move = ((wking + 14) << 6) | (wking + 7);
		mask = (((Board->mp[BlackPawn]) >> 25) & 0x000000007F000000) & (Board->mp[WhiteKing]);
		if (mask && Board->square[wking + 9] == 0 && Board->square[wking + 17] == 0)
			(list++)->move = ((wking + 25) << 6) | (wking + 9);
		mask = (((Board->mp[BlackPawn]) >> 23) & 0x00000000FE000000) & (Board->mp[WhiteKing]);
		if (mask && Board->square[wking + 7] == 0 && Board->square[wking + 15] == 0)
			(list++)->move = ((wking + 23) << 6) | (wking + 7);
	}
	list->move = 0;
}
