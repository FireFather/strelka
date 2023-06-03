#include "defs.h"

#include "bitops.h"
#include "common.h"
#include "board.h"
#include "consts.h"
#include "eval.h"
#include "genmove.h"
#include "io.h"
#include "move.h"
#include "osob.h"
#include "piece.h"
#include "material.h"
#include "random.h"
#include "trans.h"

int main(void)
{
	init_io();
	init_bitboards();
	init_evals();
	init_material();
	init_trans();
	board_from_fen(start_pos);
	while (1) get_uci_command();
}
