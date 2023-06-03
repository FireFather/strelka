#pragma once
int pawn_knight[9][9][3] = {
	{{0, 0, 0}, {0, 22, 0}, {0, 22, 45}, {0, 45, 67}, {0, 22, 67}, {0, 22, 45}, {0, 45, 67}, {0, 22, 67}, {0, 0, 45}},
	{{0, 0, 0}, {0, 45, 0}, {0, 22, 67}, {0, 22, 45}, {0, 45, 67}, {0, 22, 67}, {0, 22, 45}, {0, 45, 67}, {0, 0, 67}},
	{{0, 0, 0}, {0, 22, 0}, {0, 45, 67}, {0, 22, 67}, {0, 22, 45}, {0, 45, 67}, {0, 22, 67}, {0, 22, 45}, {0, 0, 67}},
	{{0, 0, 0}, {0, 22, 0}, {0, 22, 45}, {0, 45, 67}, {0, 22, 67}, {0, 22, 45}, {0, 45, 67}, {0, 90, 135}, {0, 0, 180}},
	{
		{0, 0, 0}, {0, 45, 0}, {0, 22, 67}, {0, 22, 45}, {0, 45, 67}, {0, 90, 135}, {0, 90, 180}, {0, 90, 180},
		{0, 0, 180}
	},
	{
		{0, 0, 0}, {0, 22, 0}, {0, 45, 67}, {0, 90, 135}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180},
		{0, 0, 180}
	},
	{
		{0, 0, 0}, {0, 90, 0}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180},
		{0, 0, 180}
	},
	{
		{0, 0, 0}, {0, 90, 0}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180},
		{0, 0, 180}
	},
	{
		{0, 0, 0}, {0, 90, 0}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180}, {0, 90, 180},
		{0, 0, 180}
	}
};

int pawn_minors[9][7] = {
	{0, 67, 134, 181, 250, 319, 365},
	{0, 45, 114, 181, 229, 297, 365},
	{0, 67, 114, 181, 250, 297, 365},
	{0, 68, 134, 181, 250, 319, 365},
	{0, 46, 114, 181, 229, 229, 229},
	{0, 67, 114, 114, 114, 114, 114},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0}
};

int pawn_majors[3][3][3] = {
	{{2, 150, 274}, {137, 262, 385}, {251, 375, 518}},
	{{251, 375, 518}, {367, 510, 630}, {502, 623, 742}},
	{{502, 623, 742}, {617, 735, 741}, {730, 735, 740}}
};

int bp, wp, bn, wn, bb, wb, br, wr, bq, wq;
int majors, minors, minors1, minors2;

inline int recog_osob(const int w_q, const int b_q, const int w_r, const int b_r, const int w_b, const int b_b,
                      const int w_n, const int b_n, const int w_p, const int b_p)
{
	const int begin = hash_osob[w_q][b_q][w_r][b_r].begin;
	const int end = hash_osob[w_q][b_q][w_r][b_r].end;

	for (int i = begin; i < end; i++)
	{
		if (osob[i].wb == w_b && osob[i].bb == b_b &&
			osob[i].wn == w_n && osob[i].bn == b_n &&
			osob[i].wp == w_p && osob[i].bp == b_p)
			return osob[i].value;
	}
	return 0;
}

inline int recog_draw(void)
{
	int recog = 0;
	const int wt = wq + wr + wb + wn + wp;
	const int bt = bq + br + bb + bn + bp;
	if (wt == 1 && bt == 0)
	{
		if (wb == 1) recog = 1;
		if (wn == 1) recog = 1;
	}
	else if (wt == 0 && bt == 1)
	{
		if (bb == 1) recog = 1;
		if (bn == 1) recog = 1;
	}
	else if (wt == 1 && bt == 1)
	{
		if (wp == 1 && bn == 1) recog = 1;
		if (wn == 1 && bp == 1) recog = 1;
		if (wp == 1 && bb == 1) recog = 1;
		if (wb == 1 && bp == 1) recog = 1;
		if (wb == 1 && bn == 1) recog = 1;
		if (wn == 1 && bb == 1) recog = 1;
	}
	else if (wt == 0 && bt == 2)
	{
		if (bn == 2) recog = 1;
	}
	else if (wt == 2 && bt == 0)
	{
		if (wn == 2) recog = 1;
	}
	else if (wt == 2 && bt == 1)
	{
		if (wp == 2 && bn == 1) recog = 1;
		if (wn == 2 && bn == 1) recog = 1;
		if (wp == 2 && bb == 1) recog = 1;
		if (wn == 2 && bb == 1) recog = 1;
		if (wn == 2 && br == 1) recog = 1;
	}
	else if (wt == 1 && bt == 2)
	{
		if (wn == 1 && bp == 2) recog = 1;
		if (wn == 1 && bn == 2) recog = 1;
		if (wb == 1 && bp == 2) recog = 1;
		if (wb == 1 && bn == 2) recog = 1;
		if (wr == 1 && bn == 2) recog = 1;
	}
	else if (wt == 3 && bt == 1)
	{
		if (wp == 3 && bn == 1) recog = 1;
		if (wp == 3 && bb == 1) recog = 1;
	}
	else if (wt == 1 && bt == 3)
	{
		if (wn == 1 && bp == 3) recog = 1;
		if (wb == 1 && bp == 3) recog = 1;
	}
	else if (wt == 2 && bt == 2)
	{
		if (wn == 1 && wp == 1 && bn == 2) recog = 1;
		if (wn == 2 && bn == 1 && bp == 1) recog = 1;
		if (wn == 2 && bb == 1 && bp == 1) recog = 1;
		if (wb == 1 && wp == 1 && bn == 2) recog = 1;
	}
	else if (wt == 3 && bt == 2)
	{
		if (wn == 1 && wp == 2 && bn == 2) recog = 1;
		if (wb == 1 && wp == 2 && bn == 2) recog = 1;
	}
	else if (wt == 2 && bt == 3)
	{
		if (wn == 2 && bn == 1 && bp == 2) recog = 1;
		if (wn == 2 && bb == 1 && bp == 2) recog = 1;
	}
	else if (wt == 4 && bt == 2)
	{
		if (wn == 1 && wp == 3 && bn == 2) recog = 1;
	}
	else if (wt == 2 && bt == 4)
	{
		if (wn == 2 && bn == 1 && bp == 3) recog = 1;
	}
	return recog;
}

inline int calc(void)
{
	int value = recog_osob(wq, bq, wr, br, wb, bb, wn, bn, wp, bp);
	if (value == 0) value = -recog_osob(bq, wq, br, wr, bb, wb, bn, wn, bp, wp);
	if (value != 0) return value;
	value += bp * (247 - pawn_knight[majors][minors][bn] +
		pawn_minors[majors][minors1] +
		pawn_majors[wq + bq][wr][br]);
	value -= wp * (247 - pawn_knight[majors][minors][wn] +
		pawn_minors[majors][minors2] +
		pawn_majors[wq + bq][br][wr]);
	value += piece_bonus[wq][bq][wr][br][wb][bb][wn][bn];
	return value;
}

inline void init_material(void)
{
	int calc_value;
	Material = malloc(MAX_MATERIAL * sizeof(struct mat_info_t));

	for (wq = 0; wq < 2; wq++)
		for (bq = 0; bq < 2; bq++)
			for (wr = 0; wr < 3; wr++)
				for (br = 0; br < 3; br++)
				{
					hash_osob[wq][bq][wr][br].begin = 0;
					hash_osob[wq][bq][wr][br].end = 0;
				}
	wq = bq = wr = br = 0;
	for (int i = 0; i < 1175; i++)
	{
		if (osob[i].wq != wq || osob[i].bq != bq || osob[i].wr != wr || osob[i].br != br)
		{
			hash_osob[wq][bq][wr][br].end = i;
			wq = osob[i].wq;
			bq = osob[i].bq;
			wr = osob[i].wr;
			br = osob[i].br;
			hash_osob[wq][bq][wr][br].begin = i;
		}
	}
	hash_osob[wq][bq][wr][br].end = 1175;

	for (wq = 0; wq < 2; wq++)
		for (bq = 0; bq < 2; bq++)
			for (wr = 0; wr < 3; wr++)
				for (br = 0; br < 3; br++)
					for (wb = 0; wb < 3; wb++)
						for (bb = 0; bb < 3; bb++)
							for (wn = 0; wn < 3; wn++)
								for (bn = 0; bn < 3; bn++)
									for (wp = 0; wp < 9; wp++)
										for (bp = 0; bp < 9; bp++)
										{
											int summ = wq +
												bq * 2 +
												wr * 2 * 2 +
												br * 2 * 2 * 3 +
												wb * 2 * 2 * 3 * 3 +
												bb * 2 * 2 * 3 * 3 * 3 +
												wn * 2 * 2 * 3 * 3 * 3 * 3 +
												bn * 2 * 2 * 3 * 3 * 3 * 3 * 3 +
												wp * 2 * 2 * 3 * 3 * 3 * 3 * 3 * 3 +
												bp * 2 * 2 * 3 * 3 * 3 * 3 * 3 * 3 * 9;
											summ &= 0x3FFFF;
											int diff = (wq - bq) * 10 + (wr - br) * 5 + (wb - bb) * 3 + (wn - bn) * 3 + (wp
												- bp);
											diff = diff * 3399;
											majors = wq * 2 + bq * 2 + wr + br;
											minors = wb + bb + wn + bn;
											minors1 = wb + bb + wn;
											minors2 = wb + bb + bn;

											if (recog_draw()) calc_value = -diff;
											else calc_value = calc();

											if (abs(calc_value) < 2000)
											{
												calc_value = calc_value / 8;

												if (wb >= 2) calc_value += 600;
												if (bb >= 2) calc_value -= 600;
											}

											if (wq + bq + wr + br + minors == 0) calc_value = 2000 * (wp - bp);

											Material[summ].value = (short)calc_value;

											int phase = 24 - minors - majors * 2;
											if (phase < 0) phase = 0;
											uint16 flags = (uint16)(phase << 4);
											if (majors == 0 && wb == 1 && bb == 1 && (wn + bn) == 0 && abs(wp - bp) < 3)
												flags |= 1;
											if (bq != 0 && (br + bb + bn) > 0) flags |= 2;
											if (wq != 0 && (wr + wb + wn) > 0) flags |= 4;
											Material[summ].flags = flags;
										}
}
