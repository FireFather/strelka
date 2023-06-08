inline void start_search(void);
inline void disp_pv(void);
inline void pv_cat(int dst[], const int src[], const int move);
inline int full_root(const int depth);
inline int full_search(const int beta, const int depth, int search_parm, int* pv);
inline int full_check_search(const int beta, const int depth, int search_parm, int* pv);
inline int full_pv_search(int alpha, const int beta, const int depth, const int in_check, int* pv);
inline int qu_search(int alpha, const int beta, const int depth, int* pv);
inline int qu_check_search(int alpha, const int beta, const int depth, int* pv);
inline int next_move(struct moves_info_t* moves_info, const struct pos_info_t* pos_info);
inline void search_check(void);

