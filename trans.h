#pragma once

enum
{
	DateSize = 4,
	ClusterSize = 4
};

inline void init_trans(void)
{
	trans_alloc(64);
	pawn_entry = malloc(0xC00000);
	pawn_mask = (0xC00000 / sizeof(struct pawn_info_t)) - 1;
	if (pawn_entry != 0)
		memset(pawn_entry, 0, 0xC00000);
}

inline void trans_alloc(int target)
{
	int size;
	target *= 1024 * 1024;
	for (size = 1; size != 0 && size <= target; size *= 2);
	size /= 2;
	size /= sizeof(struct entry_t);
	trans_size = size + (ClusterSize - 1);
	trans_mask = size - 2;
	trans_entry = (struct entry_t*)malloc(trans_size * sizeof(struct entry_t) + 64);
	trans_clear();
}

inline void trans_set_date(int date)
{
	trans_date = date;
	for (int i = 0; i < DateSize; i++)
	{
		trans_score[i] = (date + 1) * 256;
		date = trans_date - (i + 1);
		if (date < 0) date += DateSize;
	}
}

inline void trans_clear(void)
{
	struct entry_t* entry = trans_entry;
	trans_set_date(0);
	for (int i = 0; i < trans_size; i++, entry++)
	{
		entry->lock = 0;
		entry->move = 0;
		entry->depth = 0;
		entry->date = 0;
		entry->min_value = 0;
		entry->max_value = 0;
		entry->move_depth = 0;
		entry->flags = 0;
		entry->min_depth = 0;
		entry->max_depth = 0;
	}
}

inline void trans_store(const uint16 move, const char depth, const sint16 value)
{
	struct entry_t* best_entry = NULL;
	int best = 0;
	struct entry_t* entry = trans_entry + (KEY_INDEX & trans_mask);
	for (int i = 0; i < ClusterSize; i++, entry++)
	{
		if (entry->lock == KEY_LOCK)
		{
			entry->date = (unsigned char)trans_date;
			if (depth > entry->depth) entry->depth = depth;
			if (depth >= entry->move_depth)
			{
				entry->move_depth = depth;
				entry->move = move;
			}
			if (depth >= entry->min_depth)
			{
				entry->min_depth = depth;
				entry->min_value = value;
			}
			if (depth >= entry->max_depth)
			{
				entry->max_depth = depth;
				entry->max_value = value;
			}
			return;
		}
		const int score = trans_score[entry->date] - (entry->depth);
		if (score > best)
		{
			best_entry = entry;
			best = score;
		}
	}
	best_entry->lock = KEY_LOCK;
	best_entry->date = (unsigned char)trans_date;
	best_entry->depth = depth;
	best_entry->move_depth = depth;
	best_entry->move = move;
	best_entry->min_depth = depth;
	best_entry->min_value = value;
	best_entry->max_depth = depth;
	best_entry->max_value = value;
}

inline void trans_move_store(const uint16 move, char depth, const sint16 value)
{
	if (value >= 31500) depth = 64;
	struct entry_t* best_entry = NULL;
	int best = 0;
	struct entry_t* entry = trans_entry + (KEY_INDEX & trans_mask);
	for (int i = 0; i < ClusterSize; i++, entry++)
	{
		if (entry->lock == KEY_LOCK)
		{
			entry->date = (unsigned char)trans_date;
			if (depth > entry->depth) entry->depth = depth;
			if (depth >= entry->move_depth)
			{
				entry->move_depth = depth;
				entry->move = move;
			}
			if (depth >= entry->min_depth)
			{
				entry->min_depth = depth;
				entry->min_value = value;
			}
			return;
		}
		const int score = trans_score[entry->date] - (entry->depth);
		if (score > best)
		{
			best_entry = entry;
			best = score;
		}
	}
	best_entry->lock = KEY_LOCK;
	best_entry->date = (unsigned char)trans_date;
	best_entry->depth = depth;
	best_entry->move_depth = depth;
	best_entry->move = move;
	best_entry->min_depth = depth;
	best_entry->min_value = value;
	best_entry->max_depth = 0;
}

inline void trans_min_store(char depth, const sint16 value)
{
	if (value >= 31500) depth = 64;
	struct entry_t* best_entry = NULL;
	int best = 0;
	struct entry_t* entry = trans_entry + (KEY_INDEX & trans_mask);
	for (int i = 0; i < ClusterSize; i++, entry++)
	{
		if (entry->lock == KEY_LOCK)
		{
			entry->date = (unsigned char)trans_date;
			if (depth > entry->depth) entry->depth = depth;
			if (depth >= entry->min_depth)
			{
				entry->min_depth = depth;
				entry->min_value = value;
			}
			return;
		}
		const int score = trans_score[entry->date] - (entry->depth);
		if (score > best)
		{
			best_entry = entry;
			best = score;
		}
	}
	best_entry->lock = KEY_LOCK;
	best_entry->date = (unsigned char)trans_date;
	best_entry->depth = depth;
	best_entry->move_depth = 0;
	best_entry->move = 0;
	best_entry->min_depth = depth;
	best_entry->min_value = value;
	best_entry->max_depth = 0;
}

inline void trans_max_store(char depth, const sint16 value)
{
	if (value <= -31500) depth = 64;
	struct entry_t* best_entry = NULL;
	int best = 0;
	struct entry_t* entry = trans_entry + (KEY_INDEX & trans_mask);
	for (int i = 0; i < ClusterSize; i++, entry++)
	{
		if (entry->lock == KEY_LOCK)
		{
			entry->date = (unsigned char)trans_date;
			if (depth > entry->depth) entry->depth = depth;
			if (depth >= entry->max_depth)
			{
				entry->max_depth = depth;
				entry->max_value = value;
			}
			return;
		}
		const int score = trans_score[entry->date] - (entry->depth);
		if (score > best)
		{
			best_entry = entry;
			best = score;
		}
	}
	best_entry->lock = KEY_LOCK;
	best_entry->date = (unsigned char)trans_date;
	best_entry->depth = depth;
	best_entry->move_depth = 0;
	best_entry->move = 0;
	best_entry->min_depth = 0;
	best_entry->max_depth = depth;
	best_entry->max_value = value;
}
