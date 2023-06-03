#include <stdio.h>
#include <windows.h>
#include "defs.h"
#include "common.h"
#include "genmove.h"
#include "move.h"
#include "search.c"
#include "trans.h"

void move_to_string(const int move, char string[])
{
	int pos = 0;

	string[pos++] = ((move >> 6) & 7) + 'a';
	string[pos++] = ((move >> 9) & 7) + '1';
	string[pos++] = (move & 7) + 'a';
	string[pos++] = ((move >> 3) & 7) + '1';
	if (MOVE_IS_PROMOTION(move))
	{
		if ((move & 0x7000) == FlagPromoQueen) string[pos++] = 'q';
		else if ((move & 0x7000) == FlagPromoRook) string[pos++] = 'r';
		else if ((move & 0x7000) == FlagPromoBishop) string[pos++] = 'b';
		else if ((move & 0x7000) == FlagPromoKnight) string[pos++] = 'n';
	}
	string[pos] = 0;
}

int move_from_string(char cmove[])
{
	const int from = ((cmove[1] - '1') * 8) + (cmove[0] - 'a');
	const int to = ((cmove[3] - '1') * 8) + (cmove[2] - 'a');
	int move = (from << 6) | to;
	if (Board->square[from] == 12 && ((from - to) == 2 || (to - from) == 2)) move |= FlagCastle;
	if (Board->square[from] == 13 && ((from - to) == 2 || (to - from) == 2)) move |= FlagCastle;
	if (Board->ep_square != 0 && to == Board->ep_square) move |= FlagEnpassant;
	if (cmove[4] != 0)
	{
		if (cmove[4] == 'q') move |= FlagPromoQueen;
		else if (cmove[4] == 'r') move |= FlagPromoRook;
		else if (cmove[4] == 'b') move |= FlagPromoBishop;
		else if (cmove[4] == 'n') move |= FlagPromoKnight;
	}
	return move;
}

int input_available(void)
{
	static int init = 0, is_pipe;
	static HANDLE stdin_h;
	DWORD val = 0;

	if (!init)
	{
		init = 1;
		stdin_h = GetStdHandle(STD_INPUT_HANDLE);
		is_pipe = !GetConsoleMode(stdin_h, &val);
		if (!is_pipe)
		{
			SetConsoleMode(stdin_h, val & ~(ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT));
			FlushConsoleInputBuffer(stdin_h);
		}
	}
	if (is_pipe)
	{
		if (!PeekNamedPipe(stdin_h, NULL, 0, NULL, &val, NULL)) return 1;
		return val > 0;
	}
	GetNumberOfConsoleInputEvents(stdin_h, &val);
	return val > 1;
}

void send_best_move(void)
{
	char string[20];
	sint64 speed = 0;
	const int time = (int)GetTickCount64() - start_time;
	if (time > 0) speed = (true_nodes * 1000) / time;
	printf("info time %d nodes %lld nps %lld\n", time, true_nodes, speed);
	move_to_string(best_move, string);
	if (best_pv[0] == best_move && best_pv[1] != 0)
	{
		char ponder[20];
		move_to_string(best_pv[1], ponder);
		printf("bestmove %s ponder %s\n", string, ponder);
	}
	else printf("bestmove %s\n", string);
}

void parse_position(char string[])
{
	const char* fen = strstr(string, "fen ");
	char* moves = strstr(string, "moves ");
	if (fen != NULL)
	{
		if (moves != NULL) moves[-1] = 0;
		board_from_fen(fen + 4);
	}
	else board_from_fen(start_pos);
	if (moves != NULL)
	{
		char move_string[256];
		const char* ptr = moves + 6;
		while (*ptr != 0)
		{
			struct undo_t undo[1];
			move_string[0] = *ptr++;
			move_string[1] = *ptr++;
			move_string[2] = *ptr++;
			move_string[3] = *ptr++;
			if (*ptr == 0 || *ptr == ' ') move_string[4] = 0;
			else
			{
				move_string[4] = *ptr++;
				move_string[5] = 0;
			}
			const int move = move_from_string(move_string);
			move_do(move, undo);
			while (*ptr == ' ') ptr++;
		}
	}
}

void parse_setoption(char string[])
{
	int size;

	const char* name = strstr(string, "name ");
	char* value = strstr(string, "value ");
	if (name == NULL || value == NULL || name >= value) return;
	value[-1] = 0;
	name += 5;
	value += 6;
	if (!memcmp(name, "Hash", 4))
	{
		size = atoi(value);
		if (size >= 4 && size <= 1024)
		{
			free(trans_entry);
			trans_alloc(size);
		}
	}
	if (!memcmp(name, "MultiPV", 7))
	{
		size = atoi(value);
		if (size >= 1 && size <= 100)
		{
			MultiPV = size;
		}
	}
}

void get_uci_command(void)
{
	char string[8192];

	(void)fgets(string, 8192, stdin);
	if (feof(stdin)) exit(0);
	char* ptr = strchr(string, '\n');
	if (ptr != NULL) *ptr = 0;

	if (!strcmp(string, "uci"))
	{
		printf("id name Strelka 2.0 B\n");
		printf("id author Jury Osipov\n");
		printf("option name Hash type spin default 64 min 4 max 512\n");
		printf("option name MultiPV type spin default 1 min 1 max 100\n");
		printf("uciok\n");
	}
	else if (!strcmp(string, "ucinewgame"))
	{
		if (!Searching && !Delay) trans_clear();
	}
	else if (!strcmp(string, "isready"))
	{
		printf("readyok\n");
	}
	else if (!strcmp(string, "ponderhit"))
	{
		if (Searching) Infinite = false;
		else if (Delay)
		{
			send_best_move();
			Delay = false;
		}
	}
	else if (!memcmp(string, "position", 8))
	{
		if (!Searching && !Delay) parse_position(string);
	}
	else if (!memcmp(string, "setoption", 9))
	{
		if (!Searching && !Delay) parse_setoption(string);
	}
	else if (!memcmp(string, "go", 2))
	{
		if (!Searching && !Delay) start_go(string);
	}
	else if (!strcmp(string, "stop"))
	{
		if (Searching)
		{
			stop_search = 1;
			Infinite = false;
		}
		else if (Delay)
		{
			send_best_move();
			Delay = false;
		}
	}
	else if (!strcmp(string, "quit")) exit(0);
}

void start_go(char string[])
{
	sint64 nodes;
	int time, inc;
	struct board_t BoardSave[1];

	int infinite = 0;
	int ponder = 0;
	int depth = -1;
	int mate = -1;
	int movestogo = -1;
	nodes = -1;
	int binc = -1;
	int btime = -1;
	int movetime = -1;
	int winc = -1;
	int wtime = -1;
	const char* ptr = strtok(string, " ");
	for (ptr = strtok(NULL, " "); ptr != NULL; ptr = strtok(NULL, " "))
	{
		if (!strcmp(ptr, "binc"))
		{
			ptr = strtok(NULL, " ");
			binc = atoi(ptr);
		}
		else if (!strcmp(ptr, "btime"))
		{
			ptr = strtok(NULL, " ");
			btime = atoi(ptr);
		}
		else if (!strcmp(ptr, "depth"))
		{
			ptr = strtok(NULL, " ");
			depth = atoi(ptr);
		}
		else if (!strcmp(ptr, "infinite")) { infinite = 1; }
		else if (!strcmp(ptr, "mate"))
		{
			ptr = strtok(NULL, " ");
			mate = atoi(ptr);
		}
		else if (!strcmp(ptr, "movestogo"))
		{
			ptr = strtok(NULL, " ");
			movestogo = atoi(ptr);
		}
		else if (!strcmp(ptr, "movetime"))
		{
			ptr = strtok(NULL, " ");
			movetime = atoi(ptr);
		}
		else if (!strcmp(ptr, "nodes"))
		{
			ptr = strtok(NULL, " ");
			int res = sscanf(ptr, "%lld", &nodes);
		}
		else if (!strcmp(ptr, "ponder")) { ponder = 1; }
		else if (!strcmp(ptr, "winc"))
		{
			ptr = strtok(NULL, " ");
			winc = atoi(ptr);
		}
		else if (!strcmp(ptr, "wtime"))
		{
			ptr = strtok(NULL, " ");
			wtime = atoi(ptr);
		}
	}
	best_move = 0;
	best_score = 0;
	depth_score = 0;
	check_nb = 1024;
	start_time = (int)GetTickCount64();
	can_stop = 0;
	bad_1 = bad_2 = change = easy = flag = 0;
	*pv_str = 0;
	stop_search = 0;
	depth_is_limited = time_is_limited = 0;
	if (depth >= 0)
	{
		depth_is_limited = 1;
		depth_limit = depth;
	}
	else if (mate >= 0)
	{
		depth_is_limited = 1;
		depth_limit = mate * 2 - 1;
	}
	if ((Board->turn) == 0)
	{
		time = wtime;
		inc = winc;
	}
	else
	{
		time = btime;
		inc = binc;
	}
	int zapas = 0;
	if (movestogo <= 0) movestogo = 30;
	if (movestogo > 30)
	{
		movestogo = 30;
		zapas = 1;
	}
	time_max = 100000;
	if (inc < 0) inc = 0;
	if (movetime >= 0)
	{
		time_is_limited = 1;
		time_max = movetime;
		time_limit_1 = movetime * 5;
		time_limit_2 = movetime;
	}
	else if (time >= 0)
	{
		time_is_limited = 1;
		if (zapas) time_max = ((time / 10) * 9) - 5000;
		else time_max = time - 2000;
		if (time_max < 0) time_max = 0;
		int alloc = (time_max + inc * (movestogo - 1)) / movestogo;
		if (alloc > time_max) alloc = time_max;
		time_limit_1 = alloc;
		alloc = (time_max + inc * (movestogo - 1)) / 2;
		if (alloc < time_limit_1) alloc = time_limit_1;
		if (alloc > time_max) alloc = time_max;
		time_limit_2 = alloc;
	}
	Infinite = false;
	if (infinite || ponder) Infinite = true;
	Searching = true;
	Delay = false;
	memcpy(BoardSave, Board, sizeof(struct board_t));
	start_search();
	memcpy(Board, BoardSave, sizeof(struct board_t));
	search_time = (int)GetTickCount64() - start_time;
	if (search_time < 0) search_time = 0;
	Searching = false;
	Delay = Infinite;
	if (!Delay) send_best_move();
}
