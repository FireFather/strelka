#pragma once
sint16 piece_bonus[2][2][3][3][3][3][3][3] = {
	{
		{
			{
				{
					{
						{{0, 880, 1714}, {-880, 0, 841}, {-1714, -841, 0}},
						{{269, 1104, 1938}, {-566, 269, 1089}, {-1400, -551, 269}},
						{{-1114, -268, 524}, {-1924, -1069, -269}, {-2663, -1816, -1025}}
					},
					{
						{{-269, 566, 1400}, {-1104, -269, 551}, {-1938, -1089, -269}},
						{{0, 828, 1594}, {-828, 0, 774}, {-1594, -774, 0}},
						{{-1365, -564, 191}, {-2112, -1311, -558}, {-2815, -2029, -1267}}
					},
					{
						{{1114, 1924, 2663}, {268, 1069, 1816}, {-524, 269, 1025}},
						{{1365, 2112, 2815}, {564, 1311, 2029}, {-191, 558, 1267}},
						{{0, 729, 1434}, {-729, 0, 691}, {-1434, -691, 0}}
					}
				},
				{
					{
						{{-48, 910, 1895}, {-713, 317, 1310}, {-1261, -237, 682}},
						{{367, 1361, 2292}, {-188, 805, 1671}, {-681, 232, 1170}},
						{{-752, 206, 1091}, {-1219, -343, 609}, {-1777, -803, 149}}
					},
					{
						{{-171, 823, 1754}, {-727, 267, 1133}, {-1220, -307, 632}},
						{{317, 1249, 2116}, {-176, 682, 1608}, {-752, 195, 1120}},
						{{-775, 103, 985}, {-1326, -366, 525}, {-1717, -764, 44}}
					},
					{
						{{1386, 2292, 3141}, {866, 1707, 2606}, {273, 1193, 2091}},
						{{1848, 2691, 3520}, {1261, 2169, 3005}, {817, 1715, 2489}},
						{{682, 1547, 2365}, {256, 1120, 1873}, {-125, 660, 1485}}
					}
				},
				{
					{
						{{2120, 3075, 3950}, {1649, 2524, 3465}, {1098, 2068, 3009}},
						{{2631, 3499, 4371}, {2086, 3036, 3915}, {1700, 2641, 3440}},
						{{1499, 2405, 3282}, {1131, 2038, 2831}, {794, 1603, 2487}}
					},
					{
						{{2093, 2961, 3833}, {1548, 2498, 3377}, {1162, 2103, 2902}},
						{{2524, 3404, 4253}, {2129, 3009, 3785}, {1765, 2556, 3413}},
						{{1499, 2376, 3148}, {1161, 1948, 2794}, {749, 1641, 2487}}
					},
					{
						{{3549, 4402, 5225}, {3127, 3980, 4738}, {2735, 3509, 4340}},
						{{4034, 4857, 5593}, {3642, 4393, 5186}, {3193, 4032, 4825}},
						{{3009, 3756, 4514}, {2585, 3413, 4179}, {2313, 3132, 3817}}
					}
				}
			},
			{
				{
					{
						{{48, 713, 1261}, {-910, -317, 237}, {-1895, -1310, -682}},
						{{171, 727, 1220}, {-823, -267, 307}, {-1754, -1133, -632}},
						{{-1386, -866, -273}, {-2292, -1707, -1193}, {-3141, -2606, -2091}}
					},
					{
						{{-367, 188, 681}, {-1361, -805, -232}, {-2292, -1671, -1170}},
						{{-317, 176, 752}, {-1249, -682, -195}, {-2116, -1608, -1120}},
						{{-1848, -1261, -817}, {-2691, -2169, -1715}, {-3520, -3005, -2489}}
					},
					{
						{{752, 1219, 1777}, {-206, 343, 803}, {-1091, -609, -149}},
						{{775, 1326, 1717}, {-103, 366, 764}, {-985, -525, -44}},
						{{-682, -256, 125}, {-1547, -1120, -660}, {-2365, -1873, -1485}}
					}
				},
				{
					{
						{{0, 713, 1426}, {-713, 0, 699}, {-1426, -699, 0}},
						{{269, 976, 1605}, {-438, 269, 906}, {-1067, -368, 269}},
						{{-1025, -361, 273}, {-1635, -971, -339}, {-2215, -1567, -926}}
					},
					{
						{{-269, 438, 1067}, {-976, -269, 368}, {-1605, -906, -269}},
						{{0, 638, 1245}, {-638, 0, 615}, {-1245, -615, 0}},
						{{-1267, -632, -23}, {-1847, -1222, -618}, {-2422, -1772, -1168}}
					},
					{
						{{1025, 1635, 2215}, {361, 971, 1567}, {-273, 339, 926}},
						{{1267, 1847, 2422}, {632, 1222, 1772}, {23, 618, 1168}},
						{{0, 586, 1101}, {-586, 0, 524}, {-1101, -524, 0}}
					}
				},
				{
					{
						{{1842, 2511, 3117}, {1220, 1889, 2495}, {660, 1314, 1928}},
						{{2135, 2742, 3349}, {1574, 2174, 2774}, {998, 1620, 2221}},
						{{918, 1536, 2110}, {366, 1002, 1583}, {-107, 521, 1085}}
					},
					{
						{{1597, 2204, 2811}, {1036, 1636, 2236}, {459, 1082, 1683}},
						{{1889, 2490, 3037}, {1319, 1928, 2483}, {819, 1420, 1967}},
						{{682, 1264, 1801}, {201, 783, 1309}, {-235, 323, 714}}
					},
					{
						{{2859, 3443, 3964}, {2272, 2854, 3383}, {1745, 2319, 2849}},
						{{3127, 3656, 4138}, {2591, 3121, 3611}, {2102, 2625, 3242}},
						{{1928, 2438, 2916}, {1465, 1967, 2347}, {1018, 1610, 1989}}
					}
				}
			},
			{
				{
					{
						{{-2120, -1649, -1098}, {-3075, -2524, -2068}, {-3950, -3465, -3009}},
						{{-2093, -1548, -1162}, {-2961, -2498, -2103}, {-3833, -3377, -2902}},
						{{-3549, -3127, -2735}, {-4402, -3980, -3509}, {-5225, -4738, -4340}}
					},
					{
						{{-2631, -2086, -1700}, {-3499, -3036, -2641}, {-4371, -3915, -3440}},
						{{-2524, -2129, -1765}, {-3404, -3009, -2556}, {-4253, -3785, -3413}},
						{{-4034, -3642, -3193}, {-4857, -4393, -4032}, {-5593, -5186, -4825}}
					},
					{
						{{-1499, -1131, -794}, {-2405, -2038, -1603}, {-3282, -2831, -2487}},
						{{-1499, -1161, -749}, {-2376, -1948, -1641}, {-3148, -2794, -2487}},
						{{-3009, -2585, -2313}, {-3756, -3413, -3132}, {-4514, -4179, -3817}}
					}
				},
				{
					{
						{{-1842, -1220, -660}, {-2511, -1889, -1314}, {-3117, -2495, -1928}},
						{{-1597, -1036, -459}, {-2204, -1636, -1082}, {-2811, -2236, -1683}},
						{{-2859, -2272, -1745}, {-3443, -2854, -2319}, {-3964, -3383, -2849}}
					},
					{
						{{-2135, -1574, -998}, {-2742, -2174, -1620}, {-3349, -2774, -2221}},
						{{-1889, -1319, -819}, {-2490, -1928, -1420}, {-3037, -2483, -1967}},
						{{-3127, -2591, -2102}, {-3656, -3121, -2625}, {-4138, -3611, -3242}}
					},
					{
						{{-918, -366, 107}, {-1536, -1002, -521}, {-2110, -1583, -1085}},
						{{-682, -201, 235}, {-1264, -783, -323}, {-1801, -1309, -714}},
						{{-1928, -1465, -1018}, {-2438, -1967, -1610}, {-2916, -2347, -1989}}
					}
				},
				{
					{
						{{0, 578, 1093}, {-578, 0, 524}, {-1093, -524, 0}},
						{{269, 793, 1263}, {-255, 269, 746}, {-725, -208, 141}},
						{{-926, -429, 67}, {-1370, -882, -739}, {-1831, -1508, -1366}}
					},
					{
						{{-269, 255, 725}, {-793, -269, 208}, {-1263, -746, -141}},
						{{0, 471, 949}, {-471, 0, 385}, {-949, -385, 0}},
						{{-1168, -679, -569}, {-1623, -1264, -1141}, {-1960, -1613, -1453}}
					},
					{
						{{926, 1370, 1831}, {429, 882, 1508}, {-67, 739, 1366}},
						{{1168, 1623, 1960}, {679, 1264, 1613}, {569, 1141, 1453}},
						{{0, 311, 410}, {-311, 0, 153}, {-410, -153, 0}}
					}
				}
			}
		},
		{
			{
				{
					{
						{{1482, 2606, 3592}, {1180, 2166, 3275}, {740, 1879, 2987}},
						{{2162, 3142, 4181}, {1729, 2846, 3893}, {1511, 2620, 3530}},
						{{1141, 2216, 3260}, {942, 2016, 2922}, {772, 1693, 2745}}
					},
					{
						{{1624, 2604, 3643}, {1191, 2308, 3355}, {973, 2082, 2992}},
						{{2166, 3214, 4231}, {1940, 2987, 3875}, {1743, 2647, 3671}},
						{{1310, 2355, 3238}, {1139, 2038, 3053}, {839, 1899, 2913}}
					},
					{
						{{3191, 4212, 5203}, {2937, 3959, 4829}, {2714, 3599, 4598}},
						{{3844, 4835, 5683}, {3620, 4483, 5444}, {3283, 4290, 5251}},
						{{2987, 3846, 4772}, {2676, 3671, 4605}, {2571, 3559, 4355}}
					}
				},
				{
					{
						{{2888, 4163, 5375}, {2873, 4147, 5157}, {2919, 3977, 5196}},
						{{3787, 5000, 6011}, {3833, 4836, 6042}, {3660, 4889, 6095}},
						{{3176, 4199, 5378}, {3028, 4270, 5457}, {3161, 4395, 5363}}
					},
					{
						{{3249, 4462, 5473}, {3295, 4298, 5504}, {3122, 4351, 5557}},
						{{4147, 5152, 6305}, {3982, 5196, 6357}, {4088, 5295, 6245}},
						{{3344, 4533, 5675}, {3469, 4657, 5587}, {3639, 4601, 5122}}
					},
					{
						{{5119, 6106, 7232}, {4935, 6123, 7257}, {5015, 6194, 7127}},
						{{5789, 6924, 8012}, {5860, 6995, 7889}, {5977, 6903, 7650}},
						{{5196, 6312, 7194}, {5340, 6245, 6755}, {5296, 6018, 6527}}
					}
				},
				{
					{
						{{6052, 7064, 8233}, {5910, 7140, 8316}, {6048, 7270, 8228}},
						{{6756, 7933, 9056}, {6885, 8062, 8974}, {7069, 8020, 8520}},
						{{6214, 7364, 8295}, {6423, 7346, 7640}, {6397, 6871, 7165}}
					},
					{
						{{6218, 7395, 8518}, {6347, 7524, 8436}, {6531, 7482, 8239}},
						{{7140, 8263, 9177}, {7323, 8228, 8764}, {7279, 7995, 8531}},
						{{6624, 7549, 7810}, {6605, 7115, 7389}, {6420, 6917, 7178}}
					},
					{
						{{8067, 9163, 10059}, {8223, 9110, 9888}, {8161, 9119, 9897}},
						{{8962, 9851, 10339}, {8907, 9644, 10144}, {8949, 9672, 10085}},
						{{8228, 8690, 8940}, {8069, 8531, 8784}, {8121, 8478, 8783}}
					}
				}
			},
			{
				{
					{
						{{1444, 2281, 3055}, {991, 1827, 2545}, {598, 1365, 2146}},
						{{1905, 2680, 3399}, {1513, 2224, 2992}, {1048, 1839, 2607}},
						{{856, 1587, 2328}, {416, 1220, 1969}, {111, 907, 1583}}
					},
					{
						{{1367, 2142, 2861}, {974, 1686, 2454}, {510, 1300, 2069}},
						{{1827, 2540, 3255}, {1370, 2146, 2869}, {1037, 1807, 2465}},
						{{732, 1483, 2187}, {419, 1169, 1807}, {151, 821, 1320}}
					},
					{
						{{2798, 3494, 4182}, {2322, 3072, 3769}, {1964, 2705, 3347}},
						{{3177, 3874, 4524}, {2809, 3507, 4109}, {2488, 3123, 3849}},
						{{2146, 2824, 3414}, {1852, 2465, 2953}, {1516, 2216, 2704}}
					}
				},
				{
					{
						{{2987, 3838, 4764}, {2684, 3671, 4605}, {2579, 3559, 4355}},
						{{3530, 4464, 5344}, {3417, 4351, 5101}, {3357, 4147, 4626}},
						{{2745, 3652, 4422}, {2712, 3473, 3746}, {2524, 2977, 3249}}
					},
					{
						{{2992, 3926, 4806}, {2879, 3813, 4563}, {2818, 3609, 4345}},
						{{3671, 4552, 5304}, {3612, 4355, 4870}, {3406, 4101, 4615}},
						{{2913, 3676, 3916}, {2732, 3221, 3474}, {2526, 3002, 3249}}
					},
					{
						{{4598, 5452, 6186}, {4510, 5237, 5994}, {4288, 5224, 5981}},
						{{5251, 5978, 6445}, {5034, 5750, 6229}, {5054, 5757, 6155}},
						{{4355, 4796, 5025}, {4175, 4615, 4855}, {4206, 4549, 4832}}
					}
				},
				{
					{
						{{5623, 6527, 7287}, {5587, 6346, 6864}, {5405, 6111, 6628}},
						{{6326, 7079, 7314}, {6151, 6627, 6875}, {5940, 6403, 6647}},
						{{5464, 5674, 5671}, {5052, 5261, 5347}, {4852, 5041, 5092}}
					},
					{
						{{5788, 6541, 7034}, {5613, 6347, 6852}, {5660, 6380, 6795}},
						{{6346, 6798, 7037}, {6176, 6628, 6874}, {6218, 6568, 6862}},
						{{5223, 5423, 5503}, {5077, 5268, 5324}, {5033, 5267, 5322}}
					},
					{
						{{7228, 7922, 8403}, {7300, 7994, 8402}, {7584, 8096, 8631}},
						{{7751, 8179, 8409}, {7832, 8174, 8457}, {7940, 8400, 8682}},
						{{6628, 6803, 6835}, {6639, 6862, 6906}, {6889, 7098, 7096}}
					}
				}
			},
			{
				{
					{
						{{-77, 612, 1295}, {-543, 202, 894}, {-891, -154, 482}},
						{{304, 995, 1633}, {-53, 640, 1228}, {-355, 274, 732}},
						{{-724, -59, 549}, {-1000, -400, -148}, {-1349, -917, -666}}
					},
					{
						{{-235, 457, 1095}, {-591, 101, 690}, {-893, -264, 450}},
						{{202, 841, 1431}, {-101, 482, 976}, {-467, 206, 699}},
						{{-798, -197, 22}, {-1141, -673, -442}, {-1369, -914, -681}}
					},
					{
						{{1128, 1740, 2313}, {799, 1364, 2099}, {415, 1330, 2065}},
						{{1538, 2105, 2551}, {1161, 1855, 2313}, {1159, 1841, 2225}},
						{{482, 902, 1109}, {280, 699, 925}, {290, 619, 880}}
					}
				},
				{
					{
						{{1720, 2577, 3305}, {1636, 2364, 2860}, {1423, 2107, 2603}},
						{{2376, 3097, 3311}, {2169, 2624, 2851}, {1937, 2379, 2608}},
						{{1482, 1670, 1646}, {1049, 1237, 1308}, {828, 1002, 1033}}
					},
					{
						{{1838, 2559, 3031}, {1631, 2344, 2828}, {1655, 2355, 2757}},
						{{2364, 2794, 3012}, {2173, 2603, 2836}, {2193, 2530, 2802}},
						{{1219, 1399, 1464}, {1052, 1229, 1264}, {995, 1207, 1241}}
					},
					{
						{{3246, 3919, 4379}, {3296, 3968, 4363}, {3559, 4056, 4571}},
						{{3748, 4154, 4371}, {3807, 4136, 4397}, {3900, 4339, 4601}},
						{{2603, 2764, 2775}, {2601, 2802, 2825}, {2828, 3017, 3001}}
					}
				},
				{
					{
						{{4355, 4796, 5025}, {4175, 4615, 4855}, {4206, 4549, 4832}},
						{{4626, 4800, 4862}, {4454, 4628, 4657}, {4393, 4600, 4630}},
						{{3249, 3256, 3035}, {3093, 3062, 2854}, {3089, 3046, 2875}}
					},
					{
						{{4345, 4777, 5011}, {4430, 4776, 5063}, {4541, 5006, 5294}},
						{{4615, 4784, 4805}, {4620, 4832, 4866}, {4859, 5058, 5048}},
						{{3249, 3210, 2993}, {3321, 3282, 3114}, {3571, 3472, 3310}}
					},
					{
						{{5981, 6311, 6574}, {6147, 6601, 6877}, {6628, 7069, 7221}},
						{{6155, 6343, 6353}, {6454, 6642, 6625}, {6930, 6983, 7047}},
						{{4832, 4769, 4585}, {5155, 5048, 4875}, {5512, 5482, 5308}}
					}
				}
			}
		}
	},
	{
		{
			{
				{
					{
						{{-1482, -1180, -740}, {-2606, -2166, -1879}, {-3592, -3275, -2987}},
						{{-1624, -1191, -973}, {-2604, -2308, -2082}, {-3643, -3355, -2992}},
						{{-3191, -2937, -2714}, {-4212, -3959, -3599}, {-5203, -4829, -4598}}
					},
					{
						{{-2162, -1729, -1511}, {-3142, -2846, -2620}, {-4181, -3893, -3530}},
						{{-2166, -1940, -1743}, {-3214, -2987, -2647}, {-4231, -3875, -3671}},
						{{-3844, -3620, -3283}, {-4835, -4483, -4290}, {-5683, -5444, -5251}}
					},
					{
						{{-1141, -942, -772}, {-2216, -2016, -1693}, {-3260, -2922, -2745}},
						{{-1310, -1139, -839}, {-2355, -2038, -1899}, {-3238, -3053, -2913}},
						{{-2987, -2676, -2571}, {-3846, -3671, -3559}, {-4772, -4605, -4355}}
					}
				},
				{
					{
						{{-1444, -991, -598}, {-2281, -1827, -1365}, {-3055, -2545, -2146}},
						{{-1367, -974, -510}, {-2142, -1686, -1300}, {-2861, -2454, -2069}},
						{{-2798, -2322, -1964}, {-3494, -3072, -2705}, {-4182, -3769, -3347}}
					},
					{
						{{-1905, -1513, -1048}, {-2680, -2224, -1839}, {-3399, -2992, -2607}},
						{{-1827, -1370, -1037}, {-2540, -2146, -1807}, {-3255, -2869, -2465}},
						{{-3177, -2809, -2488}, {-3874, -3507, -3123}, {-4524, -4109, -3849}}
					},
					{
						{{-856, -416, -111}, {-1587, -1220, -907}, {-2328, -1969, -1583}},
						{{-732, -419, -151}, {-1483, -1169, -821}, {-2187, -1807, -1320}},
						{{-2146, -1852, -1516}, {-2824, -2465, -2216}, {-3414, -2953, -2704}}
					}
				},
				{
					{
						{{77, 543, 891}, {-612, -202, 154}, {-1295, -894, -482}},
						{{235, 591, 893}, {-457, -101, 264}, {-1095, -690, -450}},
						{{-1128, -799, -415}, {-1740, -1364, -1330}, {-2313, -2099, -2065}}
					},
					{
						{{-304, 53, 355}, {-995, -640, -274}, {-1633, -1228, -732}},
						{{-202, 101, 467}, {-841, -482, -206}, {-1431, -976, -699}},
						{{-1538, -1161, -1159}, {-2105, -1855, -1841}, {-2551, -2313, -2225}}
					},
					{
						{{724, 1000, 1349}, {59, 400, 917}, {-549, 148, 666}},
						{{798, 1141, 1369}, {197, 673, 914}, {-22, 442, 681}},
						{{-482, -280, -290}, {-902, -699, -619}, {-1109, -925, -880}}
					}
				}
			},
			{
				{
					{
						{{-2888, -2873, -2919}, {-4163, -4147, -3977}, {-5375, -5157, -5196}},
						{{-3249, -3295, -3122}, {-4462, -4298, -4351}, {-5473, -5504, -5557}},
						{{-5119, -4935, -5015}, {-6106, -6123, -6194}, {-7232, -7257, -7127}}
					},
					{
						{{-3787, -3833, -3660}, {-5000, -4836, -4889}, {-6011, -6042, -6095}},
						{{-4147, -3982, -4088}, {-5152, -5196, -5295}, {-6305, -6357, -6245}},
						{{-5789, -5860, -5977}, {-6924, -6995, -6903}, {-8012, -7889, -7650}}
					},
					{
						{{-3176, -3028, -3161}, {-4199, -4270, -4395}, {-5378, -5457, -5363}},
						{{-3344, -3469, -3639}, {-4533, -4657, -4601}, {-5675, -5587, -5122}},
						{{-5196, -5340, -5296}, {-6312, -6245, -6018}, {-7194, -6755, -6527}}
					}
				},
				{
					{
						{{-2987, -2684, -2579}, {-3838, -3671, -3559}, {-4764, -4605, -4355}},
						{{-2992, -2879, -2818}, {-3926, -3813, -3609}, {-4806, -4563, -4345}},
						{{-4598, -4510, -4288}, {-5452, -5237, -5224}, {-6186, -5994, -5981}}
					},
					{
						{{-3530, -3417, -3357}, {-4464, -4351, -4147}, {-5344, -5101, -4626}},
						{{-3671, -3612, -3406}, {-4552, -4355, -4101}, {-5304, -4870, -4615}},
						{{-5251, -5034, -5054}, {-5978, -5750, -5757}, {-6445, -6229, -6155}}
					},
					{
						{{-2745, -2712, -2524}, {-3652, -3473, -2977}, {-4422, -3746, -3249}},
						{{-2913, -2732, -2526}, {-3676, -3221, -3002}, {-3916, -3474, -3249}},
						{{-4355, -4175, -4206}, {-4796, -4615, -4549}, {-5025, -4855, -4832}}
					}
				},
				{
					{
						{{-1720, -1636, -1423}, {-2577, -2364, -2107}, {-3305, -2860, -2603}},
						{{-1838, -1631, -1655}, {-2559, -2344, -2355}, {-3031, -2828, -2757}},
						{{-3246, -3296, -3559}, {-3919, -3968, -4056}, {-4379, -4363, -4571}}
					},
					{
						{{-2376, -2169, -1937}, {-3097, -2624, -2379}, {-3311, -2851, -2608}},
						{{-2364, -2173, -2193}, {-2794, -2603, -2530}, {-3012, -2836, -2802}},
						{{-3748, -3807, -3900}, {-4154, -4136, -4339}, {-4371, -4397, -4601}}
					},
					{
						{{-1482, -1049, -828}, {-1670, -1237, -1002}, {-1646, -1308, -1033}},
						{{-1219, -1052, -995}, {-1399, -1229, -1207}, {-1464, -1264, -1241}},
						{{-2603, -2601, -2828}, {-2764, -2802, -3017}, {-2775, -2825, -3001}}
					}
				}
			},
			{
				{
					{
						{{-6052, -5910, -6048}, {-7064, -7140, -7270}, {-8233, -8316, -8228}},
						{{-6218, -6347, -6531}, {-7395, -7524, -7482}, {-8518, -8436, -8239}},
						{{-8067, -8223, -8161}, {-9163, -9110, -9119}, {-10059, -9888, -9897}}
					},
					{
						{{-6756, -6885, -7069}, {-7933, -8062, -8020}, {-9056, -8974, -8520}},
						{{-7140, -7323, -7279}, {-8263, -8228, -7995}, {-9177, -8764, -8531}},
						{{-8962, -8907, -8949}, {-9851, -9644, -9672}, {-10339, -10144, -10085}}
					},
					{
						{{-6214, -6423, -6397}, {-7364, -7346, -6871}, {-8295, -7640, -7165}},
						{{-6624, -6605, -6420}, {-7549, -7115, -6917}, {-7810, -7389, -7178}},
						{{-8228, -8069, -8121}, {-8690, -8531, -8478}, {-8940, -8784, -8783}}
					}
				},
				{
					{
						{{-5623, -5587, -5405}, {-6527, -6346, -6111}, {-7287, -6864, -6628}},
						{{-5788, -5613, -5660}, {-6541, -6347, -6380}, {-7034, -6852, -6795}},
						{{-7228, -7300, -7584}, {-7922, -7994, -8096}, {-8403, -8402, -8631}}
					},
					{
						{{-6326, -6151, -5940}, {-7079, -6627, -6403}, {-7314, -6875, -6647}},
						{{-6346, -6176, -6218}, {-6798, -6628, -6568}, {-7037, -6874, -6862}},
						{{-7751, -7832, -7940}, {-8179, -8174, -8400}, {-8409, -8457, -8682}}
					},
					{
						{{-5464, -5052, -4852}, {-5674, -5261, -5041}, {-5671, -5347, -5092}},
						{{-5223, -5077, -5033}, {-5423, -5268, -5267}, {-5503, -5324, -5322}},
						{{-6628, -6639, -6889}, {-6803, -6862, -7098}, {-6835, -6906, -7096}}
					}
				},
				{
					{
						{{-4355, -4175, -4206}, {-4796, -4615, -4549}, {-5025, -4855, -4832}},
						{{-4345, -4430, -4541}, {-4777, -4776, -5006}, {-5011, -5063, -5294}},
						{{-5981, -6147, -6628}, {-6311, -6601, -7069}, {-6574, -6877, -7221}}
					},
					{
						{{-4626, -4454, -4393}, {-4800, -4628, -4600}, {-4862, -4657, -4630}},
						{{-4615, -4620, -4859}, {-4784, -4832, -5058}, {-4805, -4866, -5048}},
						{{-6155, -6454, -6930}, {-6343, -6642, -6983}, {-6353, -6625, -7047}}
					},
					{
						{{-3249, -3093, -3089}, {-3256, -3062, -3046}, {-3035, -2854, -2875}},
						{{-3249, -3321, -3571}, {-3210, -3282, -3472}, {-2993, -3114, -3310}},
						{{-4832, -5155, -5512}, {-4769, -5048, -5482}, {-4585, -4875, -5308}}
					}
				}
			}
		},
		{
			{
				{
					{
						{{0, 578, 1093}, {-578, 0, 524}, {-1093, -524, 0}},
						{{269, 793, 1263}, {-255, 269, 746}, {-725, -208, 141}},
						{{-926, -429, 67}, {-1370, -882, -739}, {-1831, -1508, -1366}}
					},
					{
						{{-269, 255, 725}, {-793, -269, 208}, {-1263, -746, -141}},
						{{0, 471, 949}, {-471, 0, 385}, {-949, -385, 0}},
						{{-1168, -679, -569}, {-1623, -1264, -1141}, {-1960, -1613, -1453}}
					},
					{
						{{926, 1370, 1831}, {429, 882, 1508}, {-67, 739, 1366}},
						{{1168, 1623, 1960}, {679, 1264, 1613}, {569, 1141, 1453}},
						{{0, 311, 410}, {-311, 0, 153}, {-410, -153, 0}}
					}
				},
				{
					{
						{{1541, 2231, 2847}, {1290, 1906, 2294}, {965, 1541, 1928}},
						{{2029, 2639, 2745}, {1711, 2057, 2175}, {1370, 1703, 1860}},
						{{1024, 1104, 971}, {482, 562, 560}, {152, 254, 176}}
					},
					{
						{{1491, 2101, 2464}, {1173, 1777, 2152}, {1089, 1679, 2009}},
						{{1906, 2228, 2337}, {1606, 1928, 2088}, {1517, 1782, 1945}},
						{{653, 723, 716}, {377, 481, 407}, {247, 350, 276}}
					},
					{
						{{2788, 3352, 3703}, {2730, 3293, 3615}, {2884, 3308, 3714}},
						{{3181, 3479, 3623}, {3131, 3388, 3540}, {3152, 3482, 3636}},
						{{1928, 2016, 1918}, {1853, 1945, 1860}, {1971, 2052, 1963}}
					}
				},
				{
					{
						{{3905, 4237, 4357}, {3616, 3948, 4115}, {3539, 3809, 3983}},
						{{4067, 4133, 4122}, {3786, 3888, 3809}, {3653, 3752, 3673}},
						{{2582, 2516, 2187}, {2353, 2214, 1897}, {2241, 2089, 1845}}
					},
					{
						{{3786, 4110, 4271}, {3763, 4036, 4215}, {3801, 4158, 4336}},
						{{3948, 4044, 3956}, {3880, 3983, 3908}, {4010, 4100, 4018}},
						{{2509, 2361, 2035}, {2472, 2324, 2084}, {2613, 2442, 2171}}
					},
					{
						{{5314, 5571, 5726}, {5407, 5753, 5920}, {5779, 6111, 6191}},
						{{5415, 5494, 5395}, {5605, 5684, 5595}, {5972, 5953, 5909}},
						{{3983, 3811, 3555}, {4197, 4018, 3736}, {4482, 4343, 4061}}
					}
				}
			},
			{
				{
					{
						{{-1541, -1290, -965}, {-2231, -1906, -1541}, {-2847, -2294, -1928}},
						{{-1491, -1173, -1089}, {-2101, -1777, -1679}, {-2464, -2152, -2009}},
						{{-2788, -2730, -2884}, {-3352, -3293, -3308}, {-3703, -3615, -3714}}
					},
					{
						{{-2029, -1711, -1370}, {-2639, -2057, -1703}, {-2745, -2175, -1860}},
						{{-1906, -1606, -1517}, {-2228, -1928, -1782}, {-2337, -2088, -1945}},
						{{-3181, -3131, -3152}, {-3479, -3388, -3482}, {-3623, -3540, -3636}}
					},
					{
						{{-1024, -482, -152}, {-1104, -562, -254}, {-971, -560, -176}},
						{{-653, -377, -247}, {-723, -481, -350}, {-716, -407, -276}},
						{{-1928, -1853, -1971}, {-2016, -1945, -2052}, {-1918, -1860, -1963}}
					}
				},
				{
					{
						{{0, 311, 410}, {-311, 0, 153}, {-410, -153, 0}},
						{{141, 185, 161}, {-162, -74, -174}, {-309, -232, -331}},
						{{-1366, -1445, -1796}, {-1609, -1769, -2107}, {-1742, -1915, -2173}}
					},
					{
						{{-141, 162, 309}, {-185, 74, 232}, {-161, 174, 331}},
						{{0, 82, -27}, {-82, 0, -96}, {27, 96, 0}},
						{{-1453, -1622, -1968}, {-1511, -1679, -1934}, {-1391, -1576, -1868}}
					},
					{
						{{1366, 1609, 1742}, {1445, 1769, 1915}, {1796, 2107, 2173}},
						{{1453, 1511, 1391}, {1622, 1679, 1576}, {1968, 1934, 1868}},
						{{0, -192, -463}, {192, 0, -303}, {463, 303, 0}}
					}
				},
				{
					{
						{{2021, 2109, 2011}, {1946, 2038, 1953}, {2064, 2145, 2056}},
						{{1953, 1780, 1428}, {1891, 1717, 1459}, {2006, 1817, 1520}},
						{{269, -156, -581}, {230, -117, -652}, {346, -45, -580}}
					},
					{
						{{2102, 2186, 2092}, {2296, 2381, 2294}, {2669, 2652, 2613}},
						{{2038, 1856, 1592}, {2242, 2056, 1763}, {2519, 2370, 2077}},
						{{369, 16, -528}, {585, 198, -333}, {923, 523, 26}}
					},
					{
						{{3807, 3868, 3765}, {4253, 4228, 4178}, {4692, 4784, 4733}},
						{{3729, 3527, 3210}, {4095, 3935, 3631}, {4660, 4486, 4142}},
						{{2056, 1645, 1090}, {2488, 2077, 1573}, {3063, 2595, 2095}}
					}
				}
			},
			{
				{
					{
						{{-3905, -3616, -3539}, {-4237, -3948, -3809}, {-4357, -4115, -3983}},
						{{-3786, -3763, -3801}, {-4110, -4036, -4158}, {-4271, -4215, -4336}},
						{{-5314, -5407, -5779}, {-5571, -5753, -6111}, {-5726, -5920, -6191}}
					},
					{
						{{-4067, -3786, -3653}, {-4133, -3888, -3752}, {-4122, -3809, -3673}},
						{{-3948, -3880, -4010}, {-4044, -3983, -4100}, {-3956, -3908, -4018}},
						{{-5415, -5605, -5972}, {-5494, -5684, -5953}, {-5395, -5595, -5909}}
					},
					{
						{{-2582, -2353, -2241}, {-2516, -2214, -2089}, {-2187, -1897, -1845}},
						{{-2509, -2472, -2613}, {-2361, -2324, -2442}, {-2035, -2084, -2171}},
						{{-3983, -4197, -4482}, {-3811, -4018, -4343}, {-3555, -3736, -4061}}
					}
				},
				{
					{
						{{-2021, -1946, -2064}, {-2109, -2038, -2145}, {-2011, -1953, -2056}},
						{{-2102, -2296, -2669}, {-2186, -2381, -2652}, {-2092, -2294, -2613}},
						{{-3807, -4253, -4692}, {-3868, -4228, -4784}, {-3765, -4178, -4733}}
					},
					{
						{{-1953, -1891, -2006}, {-1780, -1717, -1817}, {-1428, -1459, -1520}},
						{{-2038, -2242, -2519}, {-1856, -2056, -2370}, {-1592, -1763, -2077}},
						{{-3729, -4095, -4660}, {-3527, -3935, -4486}, {-3210, -3631, -4142}}
					},
					{
						{{-269, -230, -346}, {156, 117, 45}, {581, 652, 580}},
						{{-369, -585, -923}, {-16, -198, -523}, {528, 333, -26}},
						{{-2056, -2488, -3063}, {-1645, -2077, -2595}, {-1090, -1573, -2095}}
					}
				},
				{
					{
						{{0, -192, -463}, {192, 0, -303}, {463, 303, 0}},
						{{-331, -702, -1271}, {-133, -546, -1102}, {179, -247, -760}},
						{{-2173, -2836, -3644}, {-1993, -2657, -3329}, {-1669, -2307, -3060}}
					},
					{
						{{331, 133, -179}, {702, 546, 247}, {1271, 1102, 760}},
						{{0, -421, -987}, {421, 0, -511}, {987, 511, 0}},
						{{-1868, -2541, -3219}, {-1423, -2057, -2806}, {-896, -1535, -2284}}
					},
					{
						{{2173, 1993, 1669}, {2836, 2657, 2307}, {3644, 3329, 3060}},
						{{1868, 1423, 896}, {2541, 2057, 1535}, {3219, 2806, 2284}},
						{{0, -650, -1423}, {650, 0, -760}, {1423, 760, 0}}
					}
				}
			}
		}
	}
};