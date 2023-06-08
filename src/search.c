#pragma once
#include "trans.h"

#pragma warning(disable: 4189) // local variable is initialized but not referenced

inline void start_search(void)
{
	int i, k;

	true_nodes = 0;
	pos_info_entry = Pos_info;
	memset(list_root, 0, 256 * sizeof(struct list_t));
	if (evaluate(pos_info_entry))
	{
		gen_evasions(list_root, ~(pos_info_entry->mob[1]));
	}
	else
	{
		gen_captures(list_root, Board->mp[White], Board->mp[Black]);
		for (i = 0; list_root[i].move != 0; i++);
		gen_quiet_moves(list_root + i, pos_info_entry->mob[1], -1, -1, -1);
		for (k = i; list_root[k].move != 0; k++) list_root[k].score = 0;
	}
	if (setjmp(jmp_buffer) != 0) return;
	int num_moves = 0;
	for (i = 0; list_root[i].move != 0; i++)
	{
		struct undo_t undo[1];
		move_do(list_root[i].move, undo);
		evaluate(pos_info_entry);
		const int legal = !ILLEGAL_POSITION;
		move_undo(list_root[i].move, undo);
		if (legal)
		{
			list_root[num_moves].move = list_root[i].move;
			num_moves++;
		}
	}
	list_root[num_moves].move = 0;

	trans_set_date((trans_date + 1) % DateSize);
	for (i = 0; i < 256; i++)
	{
		(Pos_info + i)->killer1 = 0;
		(Pos_info + i)->killer2 = 0;
	}
	memset(History, 0x100, 12 * 64 * sizeof(int));
	struct entry_t* entry = trans_entry + (KEY_INDEX & trans_mask);
	for (i = 0; i < ClusterSize; i++, entry++) if (entry->lock == KEY_LOCK) trans_move = entry->move;
	if (num_moves >= 2)
	{
		int score;
		for (i = num_moves - 1; i >= 0; i--)
		{
			const int move = list_root[i].move;
			if (move == trans_move) score = 0x7FFFFFFF;
			else
			{
				const int from = MOVE_FROM(move);
				const int to = MOVE_TO(move);
				const int piece = Board->square[from];
				const int capture = Board->square[to];
				if (capture != 0) score = (capture * 16) - piece + 0x7FFFFEFF;
				else score = move_order(move);
			}
			for (k = i; score < list_root[k + 1].score; k++)
			{
				list_root[k].move = list_root[k + 1].move;
				list_root[k].score = list_root[k + 1].score;
			}
			list_root[k].move = move;
			list_root[k].score = score;
		}
	}
	for (int depth = 1; depth < 72; depth++)
	{
		printf("info depth %d\n", depth);
		bad_1 = change = 0;
		int value = full_root(depth);
		if (best_score <= -32000 || best_score >= 32000) break;
		if (depth == 1 && num_moves >= 2 && list_root[0].score >= list_root[1].score + 150) easy = 1;
		if (depth > 1)
		{
			bad_2 = bad_1;
			bad_1 = 0;
		}
		if (depth >= 5) can_stop = 1;
		depth_score = best_score;
		if (depth_is_limited && depth >= depth_limit) break;
		int time = (int)GetTickCount64() - start_time;
		if (time < 0) time = 0;
			sint64 speed = 0;
			if (time > 0) speed = (true_nodes * 1000) / time;
			printf("info depth %d time %d nodes %lld nps %lld\n",
			        depth, time, true_nodes, speed);
		if (time_is_limited)
		{
			if (time >= time_limit_1 && !bad_2) flag = 1;
			else if (time >= (time_limit_1 / 6) && easy) flag = 1;
			else if (time >= (time_limit_1 / 2) && !bad_2 && !change) flag = 1;
			if (can_stop && flag) stop_search = 1;
		}
		if (stop_search) break;
	}
}

inline void disp_pv(void)
{
	int i, j, score;
	char string[10] = "cp";
	char multi[100] = "";

	for (i = 0; i < MultiPV; i++)
		for (j = i + 1; j < MultiPV; j++)
		{
			if (multipv[j].score > multipv[i].score)
			{
				int pv[256];
				memcpy(pv, multipv[i].pv, 256 * sizeof(int));
				memcpy(multipv[i].pv, multipv[j].pv, 256 * sizeof(int));
				memcpy(multipv[j].pv, pv, 256 * sizeof(int));
				score = multipv[i].score;
				multipv[i].score = multipv[j].score;
				multipv[j].score = score;
				const sint64 nodes = multipv[i].nodes;
				multipv[i].nodes = multipv[j].nodes;
				multipv[j].nodes = nodes;
				const int time = multipv[i].time;
				multipv[i].time = multipv[j].time;
				multipv[j].time = time;
				const sint64 speed = multipv[i].speed;
				multipv[i].speed = multipv[j].speed;
				multipv[j].speed = speed;
			}
		}
	best_move = multipv[0].pv[0];
	memcpy(best_pv, multipv[0].pv, 256 * sizeof(int));
	for (i = 0; i < MultiPV; i++)
	{
		if (multipv[i].score < -32000) break;
		int pos = 0;
		pv_str[0] = 0;
		for (j = 0; multipv[i].pv[j] != 0; j++)
		{
			if (pos > 0)
			{
				pv_str[pos] = ' ';
				pos++;
			}
			const int move = multipv[i].pv[j];
			pv_str[pos++] = ((move >> 6) & 7) + 'a';
			pv_str[pos++] = ((move >> 9) & 7) + '1';
			pv_str[pos++] = (move & 7) + 'a';
			pv_str[pos++] = ((move >> 3) & 7) + '1';
			if (MOVE_IS_PROMOTION(move))
			{
				if ((move & 0x7000) == FlagPromoQueen) pv_str[pos++] = 'q';
				else if ((move & 0x7000) == FlagPromoRook) pv_str[pos++] = 'r';
				else if ((move & 0x7000) == FlagPromoBishop) pv_str[pos++] = 'b';
				else if ((move & 0x7000) == FlagPromoKnight) pv_str[pos++] = 'n';
			}
			pv_str[pos] = 0;
		}
		score = multipv[i].score;
		if (best_score < -30000 || best_score > 30000)
		{
			if (j & 1) score = j / 2 + 1;
			else score = -(j / 2);
			strcpy(string, "mate");
		}
		if (MultiPV > 1) sprintf(multi, "multipv %d", i + 1);
			printf("info depth %d %s score %s %d time %d nodes %lld nps %lld pv %s\n",
			        best_depth, multi, string, score,
			        multipv[i].time, multipv[i].nodes, multipv[i].speed, pv_str);
	}
}

inline void pv_cat(int dst[], const int src[], const int move)
{
	*dst++ = move;
	while ((*dst++ = *src++) != 0);
}

inline int full_root(const int depth)
{
	int i, j, move;
	int value, num_moves, time;
	int pv_cnt = 0;
	sint64 speed;

	int alpha = -31500;
	int best_value = -32500;
	best_depth = depth;
	for (i = 0; i < MultiPV; i++)
	{
		multipv[i].score = -32500;
		multipv[i].time = 0;
		multipv[i].speed = 0;
		multipv[i].nodes = 0;
	}
	for (num_moves = 0; list_root[num_moves].move != 0; num_moves++) list_root[num_moves].score = 0;
	for (i = 0; (move = list_root[i].move) != 0; i++)
	{
		int new_pv[256];
		struct undo_t undo[1];
		if (depth > 10 && time_max > 10000)
		{
			char string[20];
			move_to_string(move, string);
			printf("info currmove %s currmovenumber %d\n", string, i + 1);
		}
		const int piece = Board->square[MOVE_FROM(move)];
		int flag_add_depth = 0;
		if (PIECE_IS_PAWN(piece))
			if (((move >> 3) & 7) == 6 || ((move >> 3) & 7) == 1)
				if (see_move(move)) flag_add_depth = 1;
		move_do(move, undo);
		const int in_check = evaluate(pos_info_entry);
		int new_depth = depth - 1;
		if (flag_add_depth || in_check) new_depth++;
		if (best_value != -32500 && new_depth > 0)
		{
			if (in_check) value = -full_check_search(-alpha, new_depth, 3, new_pv);
			else value = -full_search(-alpha, new_depth, 3, new_pv);
			if (value > alpha)
			{
				change = 1;
				easy = flag = 0;
				value = -full_pv_search(-31500, -alpha, new_depth, in_check, new_pv);
			}
		}
		else value = -full_pv_search(-31500, -alpha, new_depth, in_check, new_pv);
		move_undo(move, undo);
		if (value <= alpha) list_root[i].score = 0;
		else if (value >= 31500) list_root[i].score = 63000;
		else list_root[i].score = value + 31500;
		if (value > best_value)
		{
			if (pv_cnt < MultiPV)
			{
				pv_cat(multipv[pv_cnt].pv, new_pv, move);
				multipv[pv_cnt].score = value;
				multipv[pv_cnt].nodes = true_nodes;
				time = (int)GetTickCount64() - start_time;
				if (time < 0) time = 0;
				speed = 0;
				if (time > 0) speed = (true_nodes * 1000) / time;
				multipv[pv_cnt].time = time;
				multipv[pv_cnt].speed = speed;
				pv_cnt++;
			}
			if (pv_cnt == MultiPV)
			{
				int min_value = 32500;
				int min_index = 0;
				for (j = 0; j < MultiPV; j++)
					if (multipv[j].score < min_value)
					{
						min_value = multipv[j].score;
						min_index = j;
					}
				if (value > min_value)
				{
					pv_cat(multipv[min_index].pv, new_pv, move);
					multipv[min_index].score = value;
					multipv[min_index].nodes = true_nodes;
					time = (int)GetTickCount64() - start_time;
					if (time < 0) time = 0;
					speed = 0;
					if (time > 0) speed = (true_nodes * 1000) / time;
					multipv[min_index].time = time;
					multipv[min_index].speed = speed;
				}
				if (best_value == -32500 || value > alpha)
				{
					best_move = move;
					best_score = value;
					best_depth = depth;
					if (depth > 1 && value < depth_score - 50)
					{
						bad_1 = 1;
						easy = flag = 0;
					}
				}
				best_value = value;
				if (best_value > alpha)
				{
					alpha = best_value;
					if (alpha >= 31500) break;
				}
			}
		}
	}
	if (time_max > 10000 || depth > 5) disp_pv();
	list_root[num_moves].score = 0;
	for (i = num_moves - 2; i >= 0; i--)
	{
		move = list_root[i].move;
		value = list_root[i].score;
		for (j = i; value < list_root[j + 1].score; j++)
		{
			list_root[j].score = list_root[j + 1].score;
			list_root[j].move = list_root[j + 1].move;
		}
		list_root[j].move = move;
		list_root[j].score = value;
	}
	return best_value;
}

inline int full_search(const int beta, const int depth, int search_parm, int* pv)
{
	struct moves_info_t moves_info[1];
	struct undo_null_t undo_null[1];
	int i, new_value;
	int new_pv[256];

	true_nodes++;
	*pv = 0;
	for (i = 4; i <= Board->ply_nb; i += 2) if (Board->stack[Board->sp - i] == Board->key) return 0;
	struct entry_t* entry = trans_entry + (KEY_INDEX & trans_mask);
	moves_info->trans_move = 0;
	int trans_depth = 0;
	undo_null->ply_nb = 0;
	for (i = 0; i < ClusterSize; i++, entry++)
		if (entry->lock == KEY_LOCK)
		{
			entry->date = (unsigned char)trans_date;
			moves_info->trans_move = (int)entry->move;
			trans_depth = (int)entry->max_depth;
			if (entry->min_depth >= depth && entry->min_value >= beta)
			{
				best_trans_move = (int)entry->move;
				return entry->min_value;
			}
			if (entry->max_depth >= depth && entry->max_value < beta) return entry->max_value;
			break;
		}
	int value = pos_info_entry->value + 125;
	if (value < beta)
	{
		if (depth == 1)
		{
			new_value = qu_search(beta - 1, beta, 0, new_pv);
			if (new_value >= value) return new_value;
			return value;
		}
		value += 175;
		if (value < beta && depth <= 3)
		{
			new_value = qu_search(beta - 1, beta, depth * 8 - 8, new_pv);
			if (new_value < beta)
			{
				if (new_value >= value) return new_value;
				return value;
			}
		}
	}
	if (depth >= 2 && pos_info_entry->value >= beta)
	{
		const int turn = Board->turn;
		const uint64 mask = Board->mp[10 + turn] | Board->mp[8 + turn] |
				Board->mp[6 + turn] | Board->mp[4 + turn];
		if (mask != 0 && (search_parm & 1) && (search_parm & 2))
		{
			move_do_null(undo_null);
			(pos_info_entry + 1)->mob[0] = pos_info_entry->mob[1];
			(pos_info_entry + 1)->mob[1] = pos_info_entry->mob[0];
			(pos_info_entry + 1)->value = 6 - (pos_info_entry->value);
			pos_info_entry++;
			if (depth <= 4) new_value = -qu_search(-beta, 1 - beta, 0, new_pv);
			else new_value = -full_search(1 - beta, depth - 4, 7, new_pv);
			Board->turn ^= 1;
			Board->sp--;
			Board->ep_square = undo_null->ep_square;
			Board->ply_nb = undo_null->ply_nb;
			Board->key = undo_null->key;
			pos_info_entry--;

			if (depth > 5 && new_value >= beta) new_value = full_search(beta, depth - 5, 0, new_pv);

			if (new_value >= beta)
			{
				trans_min_store((char)depth, (sint16)new_value);
				best_trans_move = 0;
				return new_value;
			}
		}
	}
	search_parm |= 2;
	if (depth >= 4 && moves_info->trans_move == 0 && depth > trans_depth + 2 && (search_parm & 1))
	{
		if (pos_info_entry->value >= beta || depth >= 6)
		{
			if (full_search(beta, depth - 2, 3, new_pv) >= beta) moves_info->trans_move = best_trans_move;
		}
	}
	moves_info->entry = 0;
	moves_info->next = moves_info->list;
	int best_value = -32500;
	int moves_cnt = 0;
	int move = next_move(moves_info, pos_info_entry);
	if (move == 0) return 0;
	while (move != 0)
	{
		struct undo_t undo[1];
		move_do(move, undo);
		const int in_check = evaluate(pos_info_entry);
		if (ILLEGAL_POSITION) move_undo(move, undo);
		else
		{
			int new_depth = depth - 1;
			if (in_check) new_depth++;
			else if (depth >= 3 && moves_info->entry == 5 && moves_cnt >= 4) new_depth--;
			if (new_depth <= 0) new_value = -qu_search(-beta, 1 - beta, 0, new_pv);
			else if (in_check) new_value = -full_check_search(1 - beta, new_depth, search_parm ^ 1, new_pv);
			else new_value = -full_search(1 - beta, new_depth, search_parm ^ 1, new_pv);
			if (new_depth == depth - 2 && new_value >= beta)
				new_value = -full_search(1 - beta, new_depth + 1, 0, new_pv);
			move_undo(move, undo);
			moves_cnt++;
			if (new_value > best_value)
			{
				best_value = new_value;
				pv_cat(pv, new_pv, move);
				if (new_value >= beta)
				{
					if (!MOVE_IS_PROMOTION(move) && !MOVE_IS_ENPASSANT(move) && Board->square[MOVE_TO(move)] == 0)
						history_store(pos_info_entry, move, depth);
					best_trans_move = move;
					trans_move_store((uint16)move, (char)depth, (sint16)new_value);
					return new_value;
				}
			}
			search_parm &= 6;
		}
		move = next_move(moves_info, pos_info_entry);
	}
	if (best_value == -32500)
	{
		best_trans_move = 0;
		return 0;
	}
	trans_max_store((char)depth, (sint16)best_value);
	check_nb--;
	if (check_nb <= 0)
	{
		check_nb = 1024;
		search_check();
	}
	return best_value;
}

inline int full_check_search(const int beta, const int depth, int search_parm, int* pv)
{
	struct list_t moves[32];
	int i, new_value;

	true_nodes++;
	*pv = 0;
	for (i = 4; i <= Board->ply_nb; i += 2) if (Board->stack[Board->sp - i] == Board->key) return 0;
	struct entry_t* entry = trans_entry + (KEY_INDEX & trans_mask);
	int move = 0;
	for (i = 0; i < ClusterSize; i++, entry++)
		if (entry->lock == KEY_LOCK)
		{
			entry->date = (unsigned char)trans_date;
			move = (int)entry->move;
			if (entry->min_depth >= depth && entry->min_value >= beta) return entry->min_value;
			if (entry->max_depth >= depth && entry->max_value < beta) return entry->max_value;
			break;
		}
	struct list_t* last = gen_evasions(moves, ~(pos_info_entry->mob[1]));
	if (last > moves) note_moves(last, moves, pos_info_entry, move);
	int best_value = -32000;
	for (const struct list_t* moveptr = moves; moveptr->move != 0; moveptr++)
	{
		struct undo_t undo[1];
		move = moveptr->move;
		move_do(move, undo);
		const int in_check = evaluate(pos_info_entry);
		if (ILLEGAL_POSITION) move_undo(move, undo);
		else
		{
			int new_pv[256];
			int new_depth = depth - 1;
			if (last == moves || in_check) new_depth++;
			if (new_depth <= 0) new_value = -qu_search(-beta, 1 - beta, 0, new_pv);
			else if (in_check) new_value = -full_check_search(1 - beta, new_depth, search_parm ^ 1, new_pv);
			else new_value = -full_search(1 - beta, new_depth, search_parm ^ 1, new_pv);
			move_undo(move, undo);
			if (new_value > best_value)
			{
				best_value = new_value;
				pv_cat(pv, new_pv, move);
				if (new_value >= beta)
				{
					trans_move_store((uint16)move, (char)depth, (sint16)new_value);
					return new_value;
				}
			}
			search_parm &= 6;
		}
	}
	trans_max_store((char)depth, (sint16)best_value);
	return best_value;
}

inline int full_pv_search(int alpha, const int beta, const int depth, const int in_check, int* pv)
{
	struct moves_info_t moves_info[1];
	int i, move, new_value;
	int new_pv[256];

	if (depth <= 0) return qu_search(alpha, beta, 0, pv);
	true_nodes++;
	*pv = 0;
	if (Board->ply_nb > 100) return 0;
	for (i = 4; i <= Board->ply_nb; i += 2) if (Board->stack[Board->sp - i] == Board->key) return 0;
	struct entry_t* entry = trans_entry + (KEY_INDEX & trans_mask);
	moves_info->trans_move = 0;
	for (i = 0; i < ClusterSize; i++, entry++)
		if (entry->lock == KEY_LOCK)
		{
			moves_info->trans_move = entry->move;
			break;
		}
	if (depth >= 2 && moves_info->trans_move == 0)
	{
		full_pv_search(alpha, beta, depth - 1, in_check, new_pv);
		moves_info->trans_move = best_trans_move;
	}
	int flag_one_move = 0;
	moves_info->entry = 0;
	if (in_check)
	{
		struct list_t* last = gen_evasions(moves_info->list, ~(pos_info_entry->mob[1]));
		flag_one_move = 1;
		if (last > moves_info->list)
		{
			note_moves(last, moves_info->list, pos_info_entry, moves_info->trans_move);
			flag_one_move = 0;
		}
		moves_info->entry = 7;
	}
	moves_info->next = moves_info->list;
	int best_value = -32500;
	int best = 0;
	while ((move = next_move(moves_info, pos_info_entry)) != 0)
	{
		struct undo_t undo[1];
		int flag_add_depth = 0;
		if (flag_one_move) flag_add_depth = 1;
		else
		{
			if (pos_info_entry != Pos_info && ((((pos_info_entry - 1)->move) ^ move) & 0x3F) == 0 &&
				(pos_info_entry->value + 50 < -(pos_info_entry - 1)->value) && see_move(move) != 0)
				flag_add_depth = 1;
			if (PIECE_IS_PAWN(Board->square[MOVE_FROM(move)]) &&
				((((uint64)1) << (MOVE_TO(move))) & 0x00FF00000000FF00) != 0 &&
				see_move(move) != 0)
				flag_add_depth = 1;
		}
		move_do(move, undo);
		const int flag_in_check = evaluate(pos_info_entry);
		if (ILLEGAL_POSITION) move_undo(move, undo);
		else
		{
			int new_depth = depth - 1;
			if (flag_add_depth || flag_in_check) new_depth++;
			(pos_info_entry - 1)->move = move;
			if (best_value == -32500) new_value = -full_pv_search(-beta, -alpha, new_depth, flag_in_check, new_pv);
			else
			{
				if (new_depth <= 0) new_value = -qu_search(-alpha - 1, -alpha, 0, new_pv);
				else
				{
					if (flag_in_check) new_value = -full_check_search(-alpha, new_depth, 3, new_pv);
					else new_value = -full_search(-alpha, new_depth, 3, new_pv);
				}
				if (new_value > alpha) new_value = -full_pv_search(-beta, -alpha, new_depth, flag_in_check, new_pv);
			}
			move_undo(move, undo);
			if (new_value > best_value)
			{
				best_value = new_value;
				pv_cat(pv, new_pv, move);
				if (new_value > alpha)
				{
					alpha = new_value;
					best = move;
					if (new_value >= beta)
					{
						best_trans_move = move;
						if (!MOVE_IS_PROMOTION(move) && !MOVE_IS_ENPASSANT(move) && Board->square[MOVE_TO(move)] == 0)
							history_store(pos_info_entry, move, depth);
						trans_move_store((uint16)move, (char)depth, (sint16)new_value);
						return new_value;
					}
				}
			}
		}
	}
	best_trans_move = best;
	if (best_value == -32500) best_value = (-in_check) & 0xFFFF8300;
	else
	{
		if (best != 0)
		{
			if (!MOVE_IS_PROMOTION(best) && !MOVE_IS_ENPASSANT(best) && Board->square[MOVE_TO(best)] ==
				0)
				history_store(pos_info_entry, best, depth);
			trans_store((uint16)best, (char)depth, (sint16)best_value);
		}
		else trans_max_store((char)depth, (sint16)best_value);
	}
	return best_value;
}

inline int qu_search(int alpha, const int beta, const int depth, int* pv)
{
	struct undo_t undo[1];
	struct list_t list[64];
	struct list_t *pi;
	int move, new_value;
	int new_pv[256];

	true_nodes++;
	*pv = 0;
	for (int i = 4; i <= Board->ply_nb; i += 2) if (Board->stack[Board->sp - i] == Board->key) return 0;
	uint64 mask_w = Board->mp[White];
	uint64 mask_b = Board->mp[Black];
	int best_value = pos_info_entry->value;
	if (pos_info_entry->value > alpha)
	{
		alpha = pos_info_entry->value;
		if (alpha >= beta) return alpha;
	}
	else if (pos_info_entry->value < (alpha - 250))
	{
		best_value = pos_info_entry->value + 250;
		mask_w ^= Board->mp[WhitePawn];
		mask_b ^= Board->mp[BlackPawn];
		if (pos_info_entry->value < (alpha - 450))
		{
			best_value = pos_info_entry->value + 450;
			mask_w ^= Board->mp[WhiteKnight];
			mask_b ^= Board->mp[BlackKnight];
			mask_w ^= Board->mp[WhiteBishop];
			mask_b ^= Board->mp[BlackBishop];
			if (pos_info_entry->value < (alpha - 650))
			{
				best_value = pos_info_entry->value + 650;
				mask_w ^= Board->mp[WhiteRook];
				mask_b ^= Board->mp[BlackRook];
				if (pos_info_entry->value < (alpha - 1050))
				{
					best_value = pos_info_entry->value + 1050;
					mask_w ^= Board->mp[WhiteQueen];
					mask_b ^= Board->mp[BlackQueen];
				}
			}
		}
	}
	gen_captures(list, mask_w, mask_b);
	for (pi = list; pi->move != 0; pi++)
	{
		int next_move = pi->move;
		int next_score = pi->score;
		for (struct list_t* pj = pi + 1; pj->move != 0; pj++)
		{
			move = pj->move;
			const int score = pj->score;
			if (score > next_score)
			{
				pj->score = next_score;
				pj->move = next_move;
				next_score = score;
				next_move = move;
			}
		}
		if (depth > 0 || see_move(next_move) != 0)
		{
			move_do(next_move, undo);
			const int in_check = evaluate(pos_info_entry);
			if (ILLEGAL_POSITION) move_undo(next_move, undo);
			else
			{
				if (in_check) new_value = -qu_check_search(-beta, -alpha, depth - 1, new_pv);
				else new_value = -qu_search(-beta, -alpha, depth - 8, new_pv);
				move_undo(next_move, undo);
				if (new_value > best_value)
				{
					best_value = new_value;
					pv_cat(pv, new_pv, next_move);
					if (new_value > alpha)
					{
						alpha = new_value;
						if (new_value >= beta) return new_value;
					}
				}
			}
		}
	}
	if (depth <= -6) return best_value;
	gen_checks(list, ~mask_w, ~mask_b);
	for (pi = list; pi->move != 0; pi++)
	{
		move = pi->move;
		const int piece = Board->square[MOVE_FROM(move)];
		const int to = MOVE_TO(move);
		if (PIECE_IS_PAWN(piece) && (to > 55 || to < 8) && !MOVE_IS_PROMOTION(move))
			move |= FlagPromoQueen;
		if (depth > 0 || see_move(move) != 0)
		{
			move_do(move, undo);
			eval_mob(pos_info_entry);
			if (ILLEGAL_POSITION) move_undo(move, undo);
			else
			{
				new_value = -qu_check_search(-beta, -alpha, depth - 1, new_pv);
				move_undo(move, undo);
				if (new_value > best_value)
				{
					best_value = new_value;
					pv_cat(pv, new_pv, move);
					if (new_value > alpha)
					{
						alpha = new_value;
						if (new_value >= beta) return new_value;
					}
				}
			}
		}
	}
	return best_value;
}

inline int qu_check_search(int alpha, const int beta, const int depth, int* pv)
{
	struct list_t moves[32];
	struct list_t*pi;
	int move, new_value;

	true_nodes++;
	*pv = 0;
	for (int i = 4; i <= Board->ply_nb; i += 2) if (Board->stack[Board->sp - i] == Board->key) return 0;
	struct list_t* last = gen_evasions(moves, ~(pos_info_entry->mob[1]));
	int sub_depth = 1;
	if (last > moves)
	{
		(last + 1)->score = -30000;
		int from = MOVE_FROM(last->move);
		int to = MOVE_TO(last->move);
		int piece = Board->square[from];
		int capture = Board->square[to];
		last->score = (capture * 16 - piece) * capture;
		sub_depth = 8;
		for (last = last - 1; last >= moves; last--)
		{
			from = MOVE_FROM(last->move);
			to = MOVE_TO(last->move);
			piece = Board->square[from];
			capture = Board->square[to];
			const int score = (capture * 16 - piece) * capture;
			move = last->move;
			for (pi = last; (pi + 1)->score > score; pi++)
			{
				pi->move = (pi + 1)->move;
				pi->score = (pi + 1)->score;
			}
			pi->move = move;
			pi->score = score;
		}
	}
	int best_value = -32000;
	for (pi = moves; pi->move != 0; pi++)
	{
		struct undo_t undo[1];
		move = pi->move;
		move_do(move, undo);
		const int in_check = evaluate(pos_info_entry);
		if (ILLEGAL_POSITION) move_undo(move, undo);
		else
		{
			int new_pv[256];
			if (in_check) new_value = -qu_check_search(-beta, -alpha, depth - 1, new_pv);
			else new_value = -qu_search(-beta, -alpha, depth - sub_depth, new_pv);
			move_undo(move, undo);
			if (new_value > best_value)
			{
				best_value = new_value;
				pv_cat(pv, new_pv, move);
				if (new_value > alpha)
				{
					alpha = new_value;
					if (new_value >= beta) return new_value;
				}
			}
		}
	}
	return best_value;
}

inline int next_move(struct moves_info_t* moves_info, const struct pos_info_t* pos_info)
{
	int move = 0;

	switch (moves_info->entry)
	{
	case 0:
		move = moves_info->trans_move;
		moves_info->entry = 1;
		if (move != 0)
		{
			if (Board->square[MOVE_FROM(move)] != 0)
			{
				if ((Board->square[MOVE_TO(move)] & 0x0E) != 12)
				{
					if (!(move & 0x7000)) return move;
					if (Board->square[MOVE_FROM(move)] == (Board->turn ^ 2)) return move;
					if (move_is_legal(move, pos_info) != 0) return move;
					if (MOVE_TO(move) == Board->ep_square) return move;
				}
			}
		}
	case 1:
		moves_info->entry = 2;
		gen_captures(moves_info->list, Board->mp[White], Board->mp[Black]);
		moves_info->bad_cnt = 0;
	case 2:
		for (move = moves_info->next->move; move != 0; move = moves_info->next->move)
		{
			int score = moves_info->next->score;
			moves_info->next++;
			struct list_t* next = moves_info->next;
			for (int move1 = next->move; move1 != 0; next++, move1 = next->move)
			{
				const int score1 = next->score;
				if (score1 > score)
				{
					next->move = move;
					next->score = score;
					move = move1;
					score = score1;
				}
			}
			if (move != moves_info->trans_move)
			{
				if (see_move(move) != 0) return move;
				moves_info->bad_captures[moves_info->bad_cnt] = move;
				moves_info->bad_cnt++;
			}
		}
		move = pos_info->killer1;
		moves_info->bad_captures[moves_info->bad_cnt] = 0;
		moves_info->entry = 3;
		if (move != moves_info->trans_move)
		{
			if (move_is_legal(move, pos_info) != 0) return move;
		}
	case 3:
		move = pos_info->killer2;
		moves_info->entry = 4;
		if (move != moves_info->trans_move)
		{
			if (move_is_legal(move, pos_info) != 0) return move;
		}
	case 4:
		moves_info->entry = 5;
		moves_info->next = moves_info->list;
		gen_quiet_moves(moves_info->list, pos_info->mob[1], moves_info->trans_move, pos_info->killer1,
		                pos_info->killer2);
	case 5:
		move = moves_info->next->move;
		moves_info->next++;
		if (move != 0) return move;
		moves_info->entry = 6;
		moves_info->bad_index = 0;
	case 6:
		move = moves_info->bad_captures[moves_info->bad_index];
		moves_info->bad_index++;
		break;
	case 7:
		move = moves_info->next->move;
		moves_info->next++;
		break;
	default: ;
	}
	return move;
}

inline void search_check(void)
{
	while (!stop_search && input_available()) get_uci_command();
	int time = (int)GetTickCount64() - start_time;
	if (time < 0) time = 0;
	if (stop_search || (time_is_limited && can_stop && time > time_limit_2))
	{
		stop_search = 1;
		longjmp(jmp_buffer, 1);
	}
}
