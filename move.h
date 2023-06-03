#pragma once

inline int see_move(const int move)
{
	int slide_index[4];
	uint64 slide_pieces[4];

	int from = MOVE_FROM(move);
	const int to = MOVE_TO(move);
	int piece_value = ValuePiece[Board->square[from]];
	int capt_value = ValuePiece[Board->square[to]];
	if (capt_value >= piece_value) return 1;
	if (MOVE_IS_ENPASSANT(move)) return 1;
	const int me = Board->turn;
	const int opp = me ^ 1;
	uint64 mask = MaskPawnAttacks[me][to] & (Board->mp[WhitePawn + opp]);
	if (mask) return 0;
	uint64 atk_bm = ((Board->mp[WhiteKnight]) | (Board->mp[BlackKnight])) & MaskKnightMoves[to];
	const int delta = piece_value - capt_value;
	if (delta > 3 && ((Board->mp[WhiteKnight + opp]) & atk_bm)) return 0;
	slide_index[0] = (int)((Board->md3) >> LineShift[0][to]) & 0x3F;
	slide_index[1] = (int)((Board->md4) >> LineShift[1][to]) & 0x3F;
	mask = (Board->mp[WhiteQueen]) | (Board->mp[BlackQueen]) |
		(Board->mp[WhiteBishop]) | (Board->mp[BlackBishop]);
	slide_pieces[0] = mask;
	slide_pieces[1] = mask;
	atk_bm |= (LineMask[0][to][slide_index[0]] | LineMask[1][to][slide_index[1]]) & mask;
	if (delta > 3 && ((Board->mp[WhiteBishop + opp]) & atk_bm)) return 0;
	mask = MaskPawnAttacks[opp][to] & (Board->mp[WhitePawn + me]);
	if (mask) return 1;
	slide_index[2] = (int)((Board->md1) >> LineShift[2][to]) & 0x3F;
	slide_index[3] = (int)((Board->md2) >> LineShift[3][to]) & 0x3F;
	mask = (Board->mp[WhiteRook]) | (Board->mp[BlackRook]) |
		(Board->mp[WhiteQueen]) | (Board->mp[BlackQueen]);
	slide_pieces[2] = mask;
	slide_pieces[3] = mask;
	atk_bm |= (LineMask[2][to][slide_index[2]] | LineMask[3][to][slide_index[3]]) & mask;
	atk_bm |= ((Board->mp[WhiteKing]) | (Board->mp[BlackKing])) & MaskKingMoves[to];
	uint64 clear_bm = MaskClearSquare[from] & MaskClearSquare[to];
	atk_bm &= clear_bm;
	int dir = LineIndex[from][to];
	if (dir < 4) atk_bm |= LineMask[dir][from][slide_index[dir]] & slide_pieces[dir] & clear_bm;
	capt_value -= piece_value;
	do
	{
		clear_bm &= ~atk_bm;
		mask = (Board->mp[WhiteKnight + opp]) & atk_bm;
		if (mask)
		{
			atk_bm ^= (~(mask - 1)) & mask;
			piece_value = 3;
		}
		else
		{
			mask = (Board->mp[WhiteBishop + opp]) & atk_bm;
			if (mask)
			{
				piece_value = 3;
				from = lsb(mask);
				dir = LineIndex[from][to];
				mask = LineMask[dir][from][slide_index[dir]] & clear_bm & slide_pieces[0];
				atk_bm = mask | (MaskClearSquare[from] & atk_bm);
			}
			else
			{
				mask = (Board->mp[WhiteRook + opp]) & atk_bm;
				if (mask)
				{
					piece_value = 5;
					from = lsb(mask);
					dir = LineIndex[from][to];
					mask = LineMask[dir][from][slide_index[dir]] & clear_bm & slide_pieces[2];
					atk_bm = mask | (MaskClearSquare[from] & atk_bm);
				}
				else
				{
					mask = (Board->mp[WhiteQueen + opp]) & atk_bm;
					if (mask)
					{
						piece_value = 10;
						from = lsb(mask);
						dir = LineIndex[from][to];
						mask = LineMask[dir][from][slide_index[dir]] & clear_bm & slide_pieces[dir];
						atk_bm = mask | (MaskClearSquare[from] & atk_bm);
					}
					else
					{
						mask = (Board->mp[WhiteKing + opp]) & atk_bm;
						if (!mask) return 1;
						piece_value = 2001;
					}
				}
			}
		}
		capt_value += piece_value;
		if (capt_value < 0) return 0;
		mask = (Board->mp[WhiteKnight + me]) & atk_bm;
		if (mask)
		{
			atk_bm ^= (~(mask - 1)) & mask;
			piece_value = 3;
		}
		else
		{
			mask = (Board->mp[WhiteBishop + me]) & atk_bm;
			if (mask)
			{
				piece_value = 3;
				from = lsb(mask);
				dir = LineIndex[from][to];
				mask = LineMask[dir][from][slide_index[dir]] & clear_bm & slide_pieces[0];
				atk_bm = mask | (MaskClearSquare[from] & atk_bm);
			}
			else
			{
				mask = (Board->mp[WhiteRook + me]) & atk_bm;
				if (mask)
				{
					piece_value = 5;
					from = lsb(mask);
					dir = LineIndex[from][to];
					mask = LineMask[dir][from][slide_index[dir]] & clear_bm & slide_pieces[2];
					atk_bm = mask | (MaskClearSquare[from] & atk_bm);
				}
				else
				{
					mask = (Board->mp[WhiteQueen + me]) & atk_bm;
					if (mask)
					{
						piece_value = 10;
						from = lsb(mask);
						dir = LineIndex[from][to];
						mask = LineMask[dir][from][slide_index[dir]] & clear_bm & slide_pieces[dir];
						atk_bm = mask | (MaskClearSquare[from] & atk_bm);
					}
					else
					{
						mask = (Board->mp[WhiteKing + me]) & atk_bm;
						if (!mask) return 0;
						if (capt_value > 1000) return 1;
						piece_value = 2999;
					}
				}
			}
		}
		capt_value -= piece_value;
	} while (capt_value < 0);
	return 1;
}

inline int move_is_legal(const int move, const struct pos_info_t* pos_info)
{
	const int from = MOVE_FROM(move);
	const int to = MOVE_TO(move);
	const uint64 mask_to = (uint64)1 << to;
	if ((Board->md1) & mask_to) return 0;
	const int piece = Board->square[from];
	if (piece == 0) return 0;
	if (Board->turn == White)
	{
		if ((piece & 1) != 0) return 0;
		if (piece == WhiteKnight)
		{
			if (MaskKnightMoves[from] & mask_to) return 1;
			return 0;
		}
		if (piece == WhiteBishop)
		{
			if ((LINE1(from) | LINE2(from)) & mask_to) return 1;
			return 0;
		}
		if (MOVE_IS_CASTLING(move))
		{
			if (mask_to & 0x40)
			{
				if (((Board->flags) & 1) == 0) return 0;
				if (Board->square[5] != 0) return 0;
				if ((pos_info->mob[1]) & 0x20) return 0;
			}
			else
			{
				if (((Board->flags) & 2) == 0) return 0;
				if (Board->square[3] != 0) return 0;
				if ((pos_info->mob[1]) & 0x08) return 0;
			}
			return 1;
		}
		if (piece == WhiteRook)
		{
			if ((LINE3(from) | LINE4(from)) & mask_to) return 1;
			return 0;
		}
		if (piece == WhiteQueen)
		{
			if ((LINE1(from) | LINE2(from) | LINE3(from) | LINE4(from)) & mask_to) return 1;
			return 0;
		}
		if (piece == WhitePawn)
		{
			if (WhitePawnMoves1[from] & mask_to & 0x00FFFFFFFFFFFFFF) return 1;
			if (!(WhitePawnMoves2[from] & mask_to)) return 0;
			if (WhitePawnMoves1[from] & (Board->md1)) return 0;
			return 1;
		}
		if (MaskKingMoves[from] & mask_to) return 1;
	}
	else
	{
		if ((piece & 1) == 0) return 0;
		if (piece == BlackKnight)
		{
			if (MaskKnightMoves[from] & mask_to) return 1;
			return 0;
		}
		if (piece == BlackBishop)
		{
			if ((LINE1(from) | LINE2(from)) & mask_to) return 1;
			return 0;
		}
		if (MOVE_IS_CASTLING(move))
		{
			if (mask_to & 0x4000000000000000)
			{
				if (((Board->flags) & 4) == 0) return 0;
				if (Board->square[61] != 0) return 0;
				if ((pos_info->mob[1]) & 0x2000000000000000) return 0;
			}
			else
			{
				if (((Board->flags) & 8) == 0) return 0;
				if (Board->square[59] != 0) return 0;
				if ((pos_info->mob[1]) & 0x0800000000000000) return 0;
			}
			return 1;
		}
		if (piece == BlackRook)
		{
			if ((LINE3(from) | LINE4(from)) & mask_to) return 1;
			return 0;
		}
		if (piece == BlackQueen)
		{
			if ((LINE1(from) | LINE2(from) | LINE3(from) | LINE4(from)) & mask_to) return 1;
			return 0;
		}
		if (piece == BlackPawn)
		{
			if (BlackPawnMoves1[from] & mask_to & 0xFFFFFFFFFFFFFF00) return 1;
			if (!(BlackPawnMoves2[from] & mask_to)) return 0;
			if (BlackPawnMoves1[from] & (Board->md1)) return 0;
			return 1;
		}
		if (MaskKingMoves[from] & mask_to) return 1;
	}
	return 0;
}

inline void move_do(const int move, struct undo_t undo[])
{
	pos_info_entry++;
	undo->flags = Board->flags;
	undo->ep_square = Board->ep_square;
	undo->ply_nb = Board->ply_nb;
	undo->sp = Board->sp;
	undo->opening = Board->opening;
	undo->endgame = Board->endgame;
	undo->key = Board->key;
	undo->pawn_key = Board->pawn_key;
	undo->mat_summ = Board->mat_summ;
	undo->mat_diff = Board->mat_diff;
	Board->stack[Board->sp++] = Board->key;
	Board->ply_nb++;
	const int from = MOVE_FROM(move);
	int to = MOVE_TO(move);
	int piece = Board->square[from];
	const int flags = CastleFlags[from] & CastleFlags[to] & (Board->flags);
	Board->key ^= RandomCastle[(Board->flags) ^ flags];
	Board->flags = flags;
	if (Board->ep_square)
	{
		Board->key ^= RandomEP[(Board->ep_square) & 7];
		Board->ep_square = 0;
	}
	Board->square[from] = 0;
	const int me = Board->turn;
	uint64 mask = MaskClearSquare[from];
	Board->mp[me] &= mask;
	Board->mp[piece] &= mask;
	Board->md1 &= mask;
	Board->md2 &= MaskClearMD2[from];
	Board->md3 &= MaskClearMD3[from];
	Board->md4 &= MaskClearMD4[from];
	Board->opening += PieceSquareValue[piece - 2][to][0] - PieceSquareValue[piece - 2][from][0];
	Board->endgame += PieceSquareValue[piece - 2][to][1] - PieceSquareValue[piece - 2][from][1];
	mask = Random[piece - 2][from] ^ Random[piece - 2][to];
	Board->key ^= mask;
	if (PIECE_IS_PAWN(piece)) Board->pawn_key ^= mask;
	const int capture = Board->square[to];
	undo->capture = capture;
	const uint64 mask_to = (uint64)1 << to;
	if (capture != 0)
	{
		Board->mp[me ^ 1] &= MaskClearSquare[to];
		Board->mp[capture] &= MaskClearSquare[to];
		Board->opening -= PieceSquareValue[capture - 2][to][0];
		Board->endgame -= PieceSquareValue[capture - 2][to][1];
		Board->key ^= Random[capture - 2][to];
		if (PIECE_IS_PAWN(capture)) Board->pawn_key ^= Random[capture - 2][to];
		Board->mat_summ -= MatSummValue[capture - 2];
		Board->mat_diff -= MatDiffValue[capture - 2];
		Board->ply_nb = 0;
	}
	else
	{
		Board->md1 |= mask_to;
		Board->md2 |= MaskSetMD2[to];
		Board->md3 |= MaskSetMD3[to];
		Board->md4 |= MaskSetMD4[to];
		if (MOVE_IS_CASTLING(move)) move_do_castle(to);
	}
	Board->square[to] = piece;
	Board->mp[me] |= mask_to;
	Board->mp[piece] |= mask_to;
	if (PIECE_IS_PAWN(piece))
	{
		Board->ply_nb = 0;
		if (MOVE_IS_ENPASSANT(move))
		{
			Board->square[to ^ 8] = 0;
			mask = MaskClearSquare[to ^ 8];
			Board->mp[((piece - 2) ^ 1) & 1] &= mask;
			Board->mp[((piece - 2) ^ 1) + 2] &= mask;
			Board->md1 &= mask;
			Board->md2 &= MaskClearMD2[to ^ 8];
			Board->md3 &= MaskClearMD3[to ^ 8];
			Board->md4 &= MaskClearMD4[to ^ 8];
			Board->opening -= PieceSquareValue[(piece - 2) ^ 1][to ^ 8][0];
			Board->endgame -= PieceSquareValue[(piece - 2) ^ 1][to ^ 8][1];
			Board->key ^= Random[(piece - 2) ^ 1][to ^ 8];
			Board->pawn_key ^= Random[(piece - 2) ^ 1][to ^ 8];
			Board->mat_summ -= MatSummValue[(piece - 2) ^ 1];
			Board->mat_diff -= MatDiffValue[(piece - 2) ^ 1];
		}
		if (MOVE_IS_PROMOTION(move))
		{
			piece = PIECE_PROMO(move, me);
			Board->square[to] = piece;
			Board->mp[2 + me] &= MaskClearSquare[to];
			Board->mp[piece] |= mask_to;
			Board->opening += PieceSquareValue[piece - 2][to][0] - PieceSquareValue[me][to][0];
			Board->endgame += PieceSquareValue[piece - 2][to][1] - PieceSquareValue[me][to][1];
			Board->key ^= Random[piece - 2][to] ^ Random[me][to];
			Board->pawn_key ^= Random[me][to];
			Board->mat_summ += MatSummValue[piece - 2] - MatSummValue[me];
			Board->mat_diff += MatDiffValue[piece - 2] - MatDiffValue[me];
		}
		if ((to ^ from) == 16)
		{
			if (MaskEnPassant[me][to & 7] & (Board->mp[3 - me]))
			{
				to = (from + to) / 2;
				Board->ep_square = to;
				Board->key ^= RandomEP[to & 7];
			}
		}
	}
	Board->turn ^= 1;
	Board->key ^= RandomTurn;
}

inline void move_do_castle(const int to)
{
	Board->ply_nb = 0;
	if (to == 6)
	{
		Board->mp[0] ^= 0x00000000000000A0;
		Board->mp[8] ^= 0x00000000000000A0;
		Board->md1 ^= 0x00000000000000A0;
		Board->md2 ^= 0x8000800000000000;
		Board->md3 ^= 0x0000000800100000;
		Board->md4 ^= 0x0000000000000009;
		Board->opening += 208;
		Board->key ^= Random[WhiteRook - 2][5] ^ Random[WhiteRook - 2][7];
		Board->square[7] = 0;
		Board->square[5] = 8;
	}
	else if (to == 2)
	{
		Board->mp[0] ^= 0x0000000000000009;
		Board->mp[8] ^= 0x0000000000000009;
		Board->md1 ^= 0x0000000000000009;
		Board->md2 ^= 0x0000000080000080;
		Board->md3 ^= 0x0000000000000201;
		Board->md4 ^= 0x0000000010000400;
		Board->opening += 312;
		Board->key ^= Random[WhiteRook - 2][0] ^ Random[WhiteRook - 2][3];
		Board->square[0] = 0;
		Board->square[3] = 8;
	}
	else if (to == 62)
	{
		Board->mp[1] ^= 0xA000000000000000;
		Board->mp[9] ^= 0xA000000000000000;
		Board->md1 ^= 0xA000000000000000;
		Board->md2 ^= 0x0100010000000000;
		Board->md3 ^= 0x8400000000000000;
		Board->md4 ^= 0x0001000800000000;
		Board->opening -= 208;
		Board->key ^= Random[BlackRook - 2][63] ^ Random[BlackRook - 2][61];
		Board->square[63] = 0;
		Board->square[61] = 9;
	}
	else if (to == 58)
	{
		Board->mp[1] ^= 0x0900000000000000;
		Board->mp[9] ^= 0x0900000000000000;
		Board->md1 ^= 0x0900000000000000;
		Board->md2 ^= 0x0000000001000001;
		Board->md3 ^= 0x0002000010000000;
		Board->md4 ^= 0x8200000000000000;
		Board->opening -= 312;
		Board->key ^= Random[BlackRook - 2][56] ^ Random[BlackRook - 2][59];
		Board->square[56] = 0;
		Board->square[59] = 9;
	}
}

inline void move_undo_castle(const int to)
{
	if (to == 6)
	{
		Board->mp[0] ^= 0x00000000000000A0;
		Board->mp[8] ^= 0x00000000000000A0;
		Board->md1 ^= 0x00000000000000A0;
		Board->md2 ^= 0x8000800000000000;
		Board->md3 ^= 0x0000000800100000;
		Board->md4 ^= 0x0000000000000009;
		Board->square[5] = 0;
		Board->square[7] = 8;
	}
	else if (to == 2)
	{
		Board->mp[0] ^= 0x0000000000000009;
		Board->mp[8] ^= 0x0000000000000009;
		Board->md1 ^= 0x0000000000000009;
		Board->md2 ^= 0x0000000080000080;
		Board->md3 ^= 0x0000000000000201;
		Board->md4 ^= 0x0000000010000400;
		Board->square[3] = 0;
		Board->square[0] = 8;
	}
	else if (to == 62)
	{
		Board->mp[1] ^= 0xA000000000000000;
		Board->mp[9] ^= 0xA000000000000000;
		Board->md1 ^= 0xA000000000000000;
		Board->md2 ^= 0x0100010000000000;
		Board->md3 ^= 0x8400000000000000;
		Board->md4 ^= 0x0001000800000000;
		Board->square[61] = 0;
		Board->square[63] = 9;
	}
	else if (to == 58)
	{
		Board->mp[1] ^= 0x0900000000000000;
		Board->mp[9] ^= 0x0900000000000000;
		Board->md1 ^= 0x0900000000000000;
		Board->md2 ^= 0x0000000001000001;
		Board->md3 ^= 0x0002000010000000;
		Board->md4 ^= 0x8200000000000000;
		Board->square[59] = 0;
		Board->square[56] = 9;
	}
}

inline void move_undo(const int move, struct undo_t undo[])
{
	uint64 mask_to;

	const int from = MOVE_FROM(move);
	int to = MOVE_TO(move);
	int piece = Board->square[to];
	Board->turn ^= 1;
	const int me = Board->turn;
	if (MOVE_IS_PROMOTION(move))
	{
		Board->mp[PIECE_PROMO(move, me)] &= MaskClearSquare[to];
		piece = me | 2;
	}
	Board->square[from] = piece;
	Board->square[to] = undo->capture;
	const uint64 mask_from = (uint64)1 << from;
	Board->mp[me] |= mask_from;
	Board->mp[piece] |= mask_from;
	Board->mp[me] &= MaskClearSquare[to];
	Board->mp[piece] &= MaskClearSquare[to];
	Board->md1 |= mask_from;
	Board->md2 |= MaskSetMD2[from];
	Board->md3 |= MaskSetMD3[from];
	Board->md4 |= MaskSetMD4[from];
	piece = undo->capture;
	if (piece != 0)
	{
		mask_to = (uint64)1 << to;
		Board->mp[me ^ 1] |= mask_to;
		Board->mp[piece] |= mask_to;
	}
	else
	{
		Board->md1 &= MaskClearSquare[to];
		Board->md2 &= MaskClearMD2[to];
		Board->md3 &= MaskClearMD3[to];
		Board->md4 &= MaskClearMD4[to];
		if (MOVE_IS_CASTLING(move)) move_undo_castle(to);
		if (MOVE_IS_ENPASSANT(move))
		{
			to = to ^ 8;
			piece = (me ^ 1) | 2;
			Board->square[to] = piece;
			mask_to = (uint64)1 << to;
			Board->mp[me ^ 1] |= mask_to;
			Board->mp[2 + (me ^ 1)] |= mask_to;
			Board->md1 |= mask_to;
			Board->md2 |= MaskSetMD2[to];
			Board->md3 |= MaskSetMD3[to];
			Board->md4 |= MaskSetMD4[to];
		}
	}
	Board->flags = undo->flags;
	Board->ep_square = undo->ep_square;
	Board->ply_nb = undo->ply_nb;
	Board->sp = undo->sp;
	Board->opening = undo->opening;
	Board->endgame = undo->endgame;
	Board->key = undo->key;
	Board->pawn_key = undo->pawn_key;
	Board->mat_summ = undo->mat_summ;
	Board->mat_diff = undo->mat_diff;
	pos_info_entry--;
}

inline void move_do_null(struct undo_null_t* undo)
{
	undo->ep_square = Board->ep_square;
	undo->ply_nb = Board->ply_nb;
	undo->key = Board->key;
	Board->stack[Board->sp++] = Board->key;
	Board->key ^= RandomTurn;
	Board->turn ^= 1;
	Board->ply_nb = 0;
	if (Board->ep_square != 0)
	{
		Board->key ^= RandomEP[(Board->ep_square) & 7];
		Board->ep_square = 0;
	}
}

inline void history_store(struct pos_info_t* pos_info, const int move, const int depth)
{
	if (pos_info->killer1 != move)
	{
		pos_info->killer2 = pos_info->killer1;
		pos_info->killer1 = move;
	}
	const int from = MOVE_FROM(move);
	const int to = MOVE_TO(move);
	const int piece = Board->square[from];
	History[piece - 2][to] += depth * depth;
}

inline void note_moves(struct list_t* last, const struct list_t* moves, const struct pos_info_t* pos_info, const int best_m)
{
	struct list_t* pj;
	int score;

	for (struct list_t* pi = last; pi >= moves; pi--)
	{
		const int move = pi->move;
		const int from = MOVE_FROM(move);
		const int to = MOVE_TO(move);
		const int piece = Board->square[from];
		const int capture = Board->square[to];
		if (move == best_m) score = 0x7FFFFFFF;
		else if (capture != 0) score = 0x7FFFFEFF + (capture * 16) - piece;
		else if (move == pos_info->killer1) score = 0x7FFFFEFF;
		else if (move == pos_info->killer2) score = 0x7FFFFEFE;
		else score = History[piece - 2][to];
		for (pj = pi; (pj + 1)->score > score; pj++)
		{
			pj->move = (pj + 1)->move;
			pj->score = (pj + 1)->score;
		}
		pj->move = move;
		pj->score = score;
	}
}

inline int move_order(const int move)
{
	return move;
}
