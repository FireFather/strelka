#pragma once
const uint64 RandomTurn = 0x2B5F86B85A7D3E98;
const uint64 RandomCastle[16] = {
	0x0000000000000000, 0xC587778E1C593FA8, 0xF1A05AA56ECAA853, 0x34272D2B729397FB,
	0x3F7E0754A47719EC, 0xFAF970DAB82E2644, 0xCEDE5DF1CABDB1BF, 0x0B592A7FD6E48E17,
	0xA7A6AE9FFD6151F2, 0x6221D911E1386E5A, 0x5606F43A93ABF9A1, 0x938183B48FF2C609,
	0x98D8A9CB5916481E, 0x5D5FDE45454F77B6, 0x6978F36E37DCE04D, 0xACFF84E02B85DFE5
};
const uint64 RandomEP[8] = {
	0xB3A8B4499D874860, 0x61C8293117E8F324, 0x4EA6CB352B62CC46, 0xB77B8E69E2EFD2B1,
	0xCE69FDEB037CB305, 0x867783AF1000DBD6, 0x62F9B0ECFE6945D7, 0x790EAD68ACE76F30
};
const uint64 Random[12][64] = {
	{
		0x27C06528B11258B9, 0x7CF0F94115C5F328, 0x36FC1EEE0BFEA395, 0x4E768C794FD8160E,
		0x3860CBD0E035FF75, 0xF4BB6DD12DD219D8, 0x1F5EF298C63766FC, 0x7834100D52277DF9,
		0x01F25EC1630A5C37, 0xC611DB41D62B9E54, 0x39D9E2E106BE16BE, 0x1F574CEB79EFDF7A,
		0x5E6279985EF2206D, 0x2AE711874E578EAD, 0x2CF0C0C4706C4341, 0x516EFEF7D9E2232C,
		0xB303DAC5A6BAFBF0, 0x294AB0228A87F116, 0x131921A205BE04F4, 0xED0C154033F74AF0,
		0x1F06FEF1D340794C, 0x0DDFE986B1AAD88E, 0x2DE7BEB033DA5182, 0x3CDCA2E4AE501566,
		0x38BF3DE8917307C6, 0x95E52E4099E79F29, 0x88EF596E504DAED0, 0x0F49DFF6FE6D2CB5,
		0x4FECB3A3D3B75B2C, 0x4A4678DFDFF0DAF1, 0xBD3C6181CCE6BD34, 0x56A313E3823BCBD7,
		0xB97D0B52E4C662D9, 0xDF654DE3DC81F60F, 0x88407036690BA500, 0x5314E1296097583C,
		0x41AFD2BBAF6653E3, 0x27D561EA52F8FAAD, 0xD2437B8AF3A11893, 0x2C94CA0E71043865,
		0x47EF261502CA3C6A, 0x7EAA193A2679F31A, 0x71E5AAECD43D85D4, 0x5C9DF209F09F6FB9,
		0x1C7069580E6CEBBC, 0x0FE15BF6D234AF7F, 0x026DA0E9E37C82DB, 0x33FBA6FF7BA060F6,
		0x55714BD643A19EFC, 0x2D695FF999393A81, 0x266FBBDA5410962C, 0x27F4B81CF004A80C,
		0x29F9E6861EED0198, 0x6A357D15AD9D07AB, 0x0F9DC5141633A6D3, 0x0A341DB416CC8590,
		0x2C17D2E976F02D3E, 0x5282221B9C97A4C8, 0x5B6F86443BEFAE72, 0x92D667D435871659,
		0x420900D578F42B60, 0xF15F2C507D069519, 0x244EAE9DE1A1C68C, 0x7F5FA7D9505CD425
	},
	{
		0x311CF930B1A6365B, 0x6500832C8C041D1B, 0xCBBC7B879403FCD1, 0x714C53DB21A52758,
		0x0C9BE43D323EAE5E, 0xB038751ADBAB15F6, 0xC327658AE1894A9F, 0x5E167E5DFDCDEDFA,
		0x64B2251306E49415, 0x9F5C75BA36B83C56, 0x011545379BD5F5C8, 0xA4E7CA066094017E,
		0xA1E775EF3D518DC5, 0x5AB069699B3D6C1E, 0x3B92E67C48F83C8C, 0xFF037706C0042679,
		0x207437A61D7015A6, 0x77A634F5EF29FC91, 0x7A2116D344E0BC83, 0xEA0AAEB974049673,
		0xB0A83562C0A31783, 0xF8D8F1F7DC7587DE, 0xF35D2826CA639D7B, 0x35C378E23A28503C,
		0xE40EEB6F463324CF, 0x9E9CA855A99228EE, 0x273EE563FE49085B, 0xC887C43CEF48846A,
		0x65D6240EFC719A3F, 0x39317725C65D8AA2, 0x322E82F83ECD2B79, 0x825A276A4198C702,
		0x50405551E10FCBFD, 0x6DF0C11CCAAA8895, 0x8995A84C96C6184D, 0xAE33746DCAB9F711,
		0x53CA591E5F9F0627, 0x5E71AB21130C1619, 0xEA20B895B23ECF0E, 0xC6C3D79976272699,
		0xA35B5B406309D6DF, 0xCF943FF173FC99F6, 0xF3DC4D88B61D3B55, 0x60BF421FED901E10,
		0x67622C07D4C5CA60, 0xB8F16C40D39FE879, 0xD6578132F6E035ED, 0xA2254756D6FB1215,
		0x9408B2B5E188BF2C, 0x922B143CD1126F79, 0x5FFC187489891FAE, 0xE17D4060B744C583,
		0x51D41FC057D5701E, 0x033FDE4970364A20, 0xA3166D6DA24EF6C8, 0x6459BD7F6999F2C9,
		0x3C8834B0AB626EC6, 0xF94DF146AE163ADA, 0x5EF047B499DCC088, 0x7EA8F36D0C44BB2B,
		0xBA4066399FB4B67F, 0x4EF55805F582B73B, 0xCD2A9D40AF76033E, 0xB6149F61712663A5
	},
	{
		0x1A20F135B41ACC0A, 0xC208A6A203D88294, 0xB044914C2673668E, 0xEA8348147F592882,
		0x5315EC97EEC4AEE1, 0x7944AD1E033E0360, 0x8B643949E5BA535D, 0x4F6295A8241C10D6,
		0x071092E6919FFA7A, 0xB2A6FC14D94C1B0F, 0x90C853B1A431F912, 0x83E52672A7C06436,
		0x74E01E49B2BD6762, 0xC8CBB2B44C4C848F, 0x9CD9C6C377F006FC, 0x4272B1311B3ECA8F,
		0x96E2B5C941E990CA, 0xD594CF734104EC73, 0x5F2E5A0239F0F2B0, 0xAB9C150E1C56AF8D,
		0x5E182402B563BF48, 0xAE2ECAD320C705D2, 0xA31E0013CA1ADEEB, 0xDDD4E8175F3A1289,
		0x224CFFFD113EF2FF, 0x265E97718F90F1F6, 0x4A9E823048B4E349, 0xEAA6193E5385F249,
		0x152CDD911B2662E2, 0x70033C9F5319F73B, 0x2259B7F7079B7716, 0x9376C30B2C5540F0,
		0x9E4E6C2F7C2E51D9, 0x2FB7B9A5F2C11C58, 0xBD1E7ACFFDA41DF1, 0x8B65BBE580349E96,
		0xF762403B156DB0DC, 0x9FE6E698D2EB81A8, 0xEA5BAB358FF9D49E, 0xB6F4E56D7518D798,
		0x761AF8C5EEBA85A9, 0x7020CE4D7AEFE756, 0xF997F73AADD96180, 0xF6E1D16D7F81D849,
		0x2B83717D2C924BB5, 0x7EEE11CDCBA8EC19, 0x8C5FC9B0CC499596, 0xA8D8581FCF4A478B,
		0xAFDC3774C3DA1836, 0x35ECA40F45CA876F, 0xD3CE95E2D01B471F, 0x551CC79CED00DBB0,
		0xAB069EA6B453BE8C, 0xBA01CADBB9EA039B, 0x1B0CE08379D6DCEC, 0x9236289441EEB13F,
		0x146FE1614E6155BA, 0x05EA6F722191480C, 0x1BFDE4643B908883, 0xA896A33D3DFE35C5,
		0x9338CDD2749304AD, 0x5E4CA53DAD1930A3, 0x0D98D2EF7D73F8FF, 0x053084AD89026547
	},
	{
		0x8D4F7E1403ABA786, 0x9CFB0D0FB32D0B9E, 0xC80B228298BB44E1, 0x9EED843BAEDDD586,
		0x3CAB165F37EDD699, 0xA8A16192955C741B, 0xCA991B6F8315A924, 0xFF80A0A361DA4EA1,
		0x32197477DF33B6E3, 0x51809CF715EEBFEA, 0x97E84E5630D76783, 0x4A2188C5DD318A96,
		0x2D5A36FF3401F937, 0x12299115480172A3, 0x8889E42AD572A219, 0xE3074E59427697BD,
		0xF65311282302F817, 0xC0AADF0352213A65, 0x4343D528C4DE9AF5, 0xCBF21E0AC9A94706,
		0x1AA0D161D14DFA4F, 0x6EE18CDD73492ADA, 0xEA779000624D4E1D, 0x250CB9C3146E31C4,
		0x67939FD16B4FE27E, 0xA7160FBB9272CC09, 0xADC49264765454FD, 0xD86FCB234DD172D9,
		0xC66F8E391837B768, 0x84CDB82C33B87114, 0xD817A835A2469625, 0x86878EE6F48BC221,
		0xDBB660C5B01B0B1B, 0x67DCFFE8B67729D8, 0xB486C5A22A4BC192, 0x004BFC08DF18E0E5,
		0x198C330FB790972A, 0xAEC5B3F7F3538634, 0x29C2D16E1B03B322, 0x6072E4F537A4EA3D,
		0xC2BDA2A80BDDE76E, 0x00F0AE97EF6CED0C, 0x46C904DD265D184E, 0xB70CA3E803A66E15,
		0x0A9040EDA7E9A63E, 0x17C70053755AC17B, 0x0ED52894B1FFFC23, 0x89ED7D9FD625E509,
		0xD508CD1765304556, 0xA7BD133F394B3C6F, 0x5FD6013D321E08F9, 0xAF7C40AF6D2EEE76,
		0x425383841A61771A, 0x72139EF6DA64F6B6, 0x3B0DC6998AE00B8A, 0x42281BE79FC1C6D8,
		0x08E501737AEFA8BE, 0x6CF37A9CCEE0368E, 0x8F5C0196992F94AA, 0x8EF52951A07C741C,
		0xCAA797BA7918714F, 0x6AF193373B4B52A1, 0xB18FC97D5B03C639, 0x6937E0E5D83272B1
	},
	{
		0x7387B718BF141637, 0xA83978ED37CA6BBA, 0x5D87ADA916919FC4, 0x6B0DFDF70F99D8CE,
		0x4DC0C9BD37A3618F, 0x6D72EF87513F0806, 0xDB8A42AB9682E7B7, 0xBC78FA41C90D0562,
		0xB5087925985EB84A, 0x3985233BB5C9E963, 0x3C0F2AE3EF81002A, 0xB6A0922335B08DA1,
		0x3B0E4FFF5E6F5D0C, 0xC4F7613193250E74, 0xD5388BCF49A6CF8C, 0xD6B6A2D69D62F51E,
		0x406FA53DF1311C50, 0xABC681AA48EF9673, 0x18854D9590381468, 0xB207DFD1B378265C,
		0xA6F27E7E8C0B045F, 0x2524AE03BF33790E, 0x9FBDE57BB42E372D, 0x62C744664E0329F9,
		0x9C6F1FBE542C4CAA, 0x141D202C51B49072, 0x7E3C26A5A439DCC5, 0x1C149E9A48AB458F,
		0x6912D0D9D9C769D4, 0x5D1D5DA8FBE31EE4, 0xE24509418018432E, 0xC66581CCE1ED6374,
		0xD22FCBDBEACD4BD1, 0xB2AA2194436193B9, 0xD4D4CA2D6A606BDF, 0xEE82DF952FC7988D,
		0x503135E8C9661593, 0x50C643E3DB547D2A, 0x105A5941C2A1F684, 0xFAD7B0A93DE64872,
		0x5AC1326A6040226C, 0x2673885BCC6B7CD0, 0xB484FD321E2EB832, 0x1366C49088D331B6,
		0x9A0DCCB11ABFA082, 0x707C493B319AAC04, 0xD117DBAB7B14A6EA, 0x2DF96A38113AEA1F,
		0x384DB267CF55B9B7, 0x492871B184D3FD5C, 0x5EFB97FE0F75410A, 0x6DB01F108F5FDE21,
		0x2DB36FD745DBFE11, 0xF0D14ED2169B7134, 0x01BCB3D6C1ED1704, 0xA6F83C53B744F0BF,
		0x6260FACCCF39B3F5, 0x1BAF160A8C43D66B, 0x9C8F59038389A90D, 0x178B925BEA3F999C,
		0xA444D3066DFB5C04, 0xA31BBCC43C84A162, 0x3B6E2148C1968083, 0x89C658696FF5D0FC
	},
	{
		0x0EE7AB06F105D322, 0x71CE9744BCAF9492, 0xEDAB84A654282FD0, 0x2CC55735B243BD98,
		0x82C3A5B89C4B2F92, 0x77710596980EE43D, 0x14D5E1DD57B11275, 0x39174AB2DA9B6AFA,
		0xA896C96DCF3D2B1F, 0x9F5482F983733F39, 0x4D3974736138D6B7, 0xCE3FE583CF19B7DE,
		0x34B10BDCF4826A60, 0x3B14A588D5A5CA3D, 0x3CE0FC723395EB6F, 0x553506D3826EDAD2,
		0xEE5BC28B4B8E0976, 0xAC1EED8CAE9FE8D6, 0x8305AC0C06641951, 0x435CBF92B85C239A,
		0x7678AA75139D722E, 0x557A6ED91600CEBF, 0x0BA4BD268E5829B4, 0x5448C48146198701,
		0x6C4F43C21F3E5A65, 0xBBC0E569F7280C8D, 0xC3D91B605FBD06F6, 0x3312177922832998,
		0xC735CAB2B9167402, 0xF3768676905BD7F8, 0x5A7DC4A66D10DCB4, 0xD338251CE1E7F179,
		0x045B28A057C341E2, 0x7B0536CE5342749A, 0x6F016F81EEB42E34, 0x07312BE1AB00FAA0,
		0xCDEB97A18A1476DF, 0xCA097C50FD4C7B66, 0x9F7C8F9B504C98C8, 0x250ECA478AEC3281,
		0xD1D481F648273AA0, 0x20BFBE78131DF9E2, 0xE94399014FAC8247, 0x31B4F8D6177420D9,
		0x6764E39DBD75412E, 0x449657D157314A46, 0x244D6B935E96DB73, 0xA34748849751C3A7,
		0xB27834604A72246D, 0x63C10D4E5A0D2909, 0x2BBA4BA376E1CB9B, 0x8153A92F930C644B,
		0x750B5E4D5DE65776, 0xE36FDAC862E2A74E, 0x9B4CF6613D60F055, 0xEAF65D179A2AA78A,
		0xD667C4D6F5B90727, 0xE72108AA465DE314, 0xD3649BC97FDCB026, 0x4867E04B2C170B8E,
		0x65C1CCD7EA3FB566, 0xC18AFBF9D3783903, 0xEBA8C22250F16FAA, 0x3171BC37720263AC
	},
	{
		0x6E91249260AD19CA, 0x11189E3FD2C8CE35, 0x2772C4E4772B553B, 0xC43ED7E00763C719,
		0xBD4AE5E5ADF95D15, 0x33AFB1F2F756CD53, 0x922366BD034BF9BF, 0x3E2483751D02843A,
		0xAAE1B99A6A58C3A5, 0xE29D7A3271B90785, 0xC1D71085BBBE4C00, 0x6846FA71D4870E93,
		0xB5B28E93FDE47910, 0x2273641DFEEC8C1C, 0xCAE974D2F0E3AEBB, 0x38398CDE0C1C6C0B,
		0x5CC163CC86C0F3B6, 0xEB5CBCB82CFF4DC9, 0x1194714A034733C7, 0x2538251BF01AE6D1,
		0x86551912FE7708DA, 0xC4B8B207CDC38E6E, 0x16A2FC269726063A, 0x3FE47692AF48FCE7,
		0x87D3CE21D84B2EE0, 0x4C101A7C9DB070BA, 0x88D581EBA337412B, 0xBEA03BA152898DA2,
		0x6D94C20E4F99CBC7, 0x25F2A9CB0688F309, 0xB6A256879F14D4B8, 0x847EEE74A61630D9,
		0x0E86E2B431668CB4, 0x6B2AB47D9D4721F8, 0xEB37452ACD02E3FA, 0xB3B0371629324BD8,
		0xAD4D4ADA3D855B85, 0x28574CDA08FEED39, 0xD1A5B31AA82E2E80, 0x9B141B3763D94728,
		0x5C3BFC20FD6CB4C2, 0x2E809CA82D1B6FD4, 0x2607899956E49B1C, 0xAB86DA1ABE93C15E,
		0xF3545B1DA2D667FE, 0x83B6974441275B3C, 0x79C9E006BA5CE48B, 0x80202401E2D7EA2D,
		0x4E6B3674AA15B1CA, 0x2E6943DCDADA2D11, 0x965512311C5AA0DC, 0x6FEC66F926D37F64,
		0xA45269A70794CE14, 0x739A3FD827E208BC, 0xB57877B078696627, 0xB844445322DF4D15,
		0x1749743C097932E2, 0x8D247E748BAF881E, 0x3EE252772CB45EFA, 0xBDB8045200EE2EF6,
		0xE298ABB570195363, 0x89E777647FAF7930, 0xB4A7E843C2DA6A3C, 0x7DFDE1538E646329
	},
	{
		0x75EB637359ECD806, 0x4264E7CD4FB0B296, 0xDC074558DC83891F, 0x653944A400F5D56B,
		0xDCFB6215B9F87417, 0xB3333F1461BA7729, 0xC544AD0CEA549214, 0xD09629FAC9CCA36B,
		0xD50966DBD47A4B60, 0x03B20B218E679D7B, 0x9CAC59796950884C, 0x6947B47C9B5C3A57,
		0xA9314090830A7E35, 0x764C06D304582C4E, 0xC842E3D6B0401AD8, 0xBF529EF92288A2A4,
		0x00F090A774C1B289, 0xE5AFC7BD6F9B9A19, 0x0DD954AF5E62AED6, 0xF6B778DBA2670840,
		0x2060470F43C435D7, 0x4708A44780C8893C, 0xED3BBA30F08FCDA6, 0x65C4610D42DEAA91,
		0xC595EA239A26CA57, 0x0E9ACF2DB38C0AB5, 0xCDECFA5B5AE1BB4D, 0x78716E0BF8FAAFA9,
		0x5EDF926AED1E3764, 0x31C136167E98DB78, 0xA98A3349499ED07A, 0x6BF73B1EDA81B56A,
		0x6E1A4381EEEAFD54, 0x824BEC02B346B844, 0x2E5A651338757497, 0xD4AC975FD65B866C,
		0xBD72B5D741BF8283, 0x4BBE8A4B022EB074, 0xC116F51BB8616410, 0xE0CB592F25A28042,
		0xC0BED0978E631FC3, 0x841DC02CFFF1B578, 0xA303EA48101F011C, 0xFA1FAB5407BB1984,
		0x73AB27075E9DB23F, 0xFB26BB837DAC24AA, 0xFFE20A09F7C3649F, 0x4EF402082AEBBE2B,
		0xF8090E978448DF46, 0x82911F33D6A105C3, 0xA054BC5531B98192, 0x5C54323AE74817E5,
		0x21A50ED7FAFC0D0D, 0xA217BC20E583FE9B, 0xBDB55C1FD570D2DF, 0xD631C5F2C04AF5E8,
		0x953CC3BC9B540E16, 0xDB9EF45BB34AF924, 0xF2F1F219A4753F69, 0x7D57E3411B2EC156,
		0xC32EF2D5ADB5C588, 0xF9C35058E0631C14, 0x305225296C7FC827, 0xC1488CA9617E7A81
	},
	{
		0x7C91923EE6246BC6, 0x59C2632F9CFE238B, 0x5A25E23C333806A0, 0xB7B1E0C0C92FF369,
		0x4832F82CDEC7F22F, 0x2DB3BA1C02C3CD74, 0x8CA4CD14C9F94AFB, 0xDDEA611CC4088E21,
		0xDB32872A30D117CC, 0x288A59CC66B088F0, 0xE8DCBC8E99124A85, 0xFEF80659F633FE26,
		0x9BBA3E236D788BBF, 0x6902F3D344766952, 0x59913195648A2C08, 0x4297CBA1D68ACFEA,
		0xC29842590451D21C, 0x8B7F2EC0058E4204, 0x3462FDADCFA184FB, 0x54C82F8CD1404635,
		0x20A800E5CE1BC3A0, 0xD3557498C56285E5, 0x2465AF291E273CFE, 0x73FA58A0003A351A,
		0xF9D516C079F6CD71, 0x8630BCF343C1B3D9, 0x99B016BEB2A33EB7, 0x5AC722CDBF7146C9,
		0x01CE95F1DCCD34FD, 0x0CB9BCB2AAF8D5A4, 0x23DD859A6F048FB8, 0x84C056650A5A5664,
		0xCC3E66F089B27700, 0x7FDEA0EE35B7BA80, 0xD341E1F07AB51127, 0x7D8C8C8CDAE7AEA3,
		0x584CEF685462FB59, 0x22789E5556D26A49, 0x44D56A1C0A06BD43, 0x345C2FCB9916BE27,
		0xBD1622AF91FD5C3E, 0xFF46A047568E5880, 0x5AEFF0A616123BDF, 0xB4D05E16E970C907,
		0x02022883080DE278, 0x202E1A77FE181AF2, 0xB0790EFA4478EB5C, 0x7811C1B75C19CB9A,
		0x1CA57703AD944AE9, 0xA4CB250CCF75B838, 0x54361C6DF021B41A, 0xD3D359704366662B,
		0xB61A625DB54BABF0, 0x5E26196A2DC87092, 0x1407D1B902817786, 0xDFC533ACEFCD4793,
		0x1B7310057894545B, 0x1302FC984170726D, 0x2AD14DE883B8E300, 0xA7F6BA03C640E1AA,
		0x164E04893B27EB07, 0x1D21077F0B9DF9BC, 0xB5B7A51F18DC9429, 0xC44C5D371104FDBB
	},
	{
		0xED96FFDB3CA8BC74, 0x6A8061653DFC3360, 0xECD9D3194F5AB8B2, 0xB1467C7CEE98DFE0,
		0x0C6C290029C3487D, 0x48BDE6091D5DEB44, 0x59918749F2E47115, 0xD1FB154746E19C51,
		0xA5026E5C899C2681, 0xAD0B7495CC6CC664, 0xAA615D9C9A09D9C2, 0xA5913D401AA53883,
		0xD3F86D39F3D89C60, 0x9F17D90750CBE804, 0x407C7C81B71E569E, 0x71D1CE2E07D4B6B2,
		0x5644C658011D3A13, 0x7C11EAE2D779803B, 0x513B32A97BF4B52D, 0x567010393BA7BFC1,
		0xA878BD30E1B8B5A3, 0xD5B6E9F6414ED9A7, 0x0F464E63CF45B094, 0xD1EEF65834194FEA,
		0x3765704EEBCACBDA, 0xC4E62555E6FC544C, 0x6C0F1ECAF12708F6, 0x1AF6DF5687CC1E21,
		0xD4FA8AD82611A6E4, 0xF8C4982925B64AA3, 0xB0F6A5B0F0A21727, 0x81142C26DB9C8915,
		0xD3F6856060BB859C, 0xCEA70223D8D3CB59, 0xE8809F82F84ABC62, 0x28C7B7947DE62283,
		0x29D96861336DEFEE, 0xA624874A215EA940, 0x63AA203E778953A0, 0x2D593BD0745E414C,
		0xBD65E6739DB6C501, 0xCE104F9D0B5F026C, 0x52581897BC3123EE, 0x9940D641AFA98633,
		0x55A8C1077CE9390D, 0x643ED7D3024D733A, 0x53CF8055DF3CD971, 0x48048D5B9E79B895,
		0x84CC237F7229BC79, 0xE48F265AFA2F9773, 0xED0F05EB9A51E3D0, 0xA3F71FF134F108C7,
		0xC4622A9C86FEA148, 0xC2B4BA1EE628B357, 0x2330E3F48235C5E2, 0x8574157BFBCD8B09,
		0x140A95DFD0932ED5, 0x3EDE01CC51748C2A, 0xD8E971D8DC78568E, 0xA47F5B77EAC4FC61,
		0x3196B286DC5EBF4A, 0xD65194ACC8F873DC, 0x153EBEEA60CBB80A, 0xE8025986032A163B
	},
	{
		0x3834BE39807684D5, 0x4FD317CD0BE69F12, 0xD6DF6DD4EBBD8531, 0xDB1EC652E135744F,
		0xAEAB63E53F7426BE, 0x65DD1198E3E44947, 0x2B5E5C00BF8D3BE6, 0x536428A3EC8E928A,
		0x7BEA541389D582F1, 0xB363056D23432C8A, 0x881FAC6562B2C490, 0xD6D46201BDCD5B24,
		0xD6C6EE80E3CB9A78, 0xA0F19EBBAADB9F44, 0xDF85FC4D585C6EDE, 0x98A3BD49EC6EAFE6,
		0xEA7A53ED1A70C31A, 0x037BAE944A678D21, 0xE694EA1AB0813A07, 0x7E180AB88978377F,
		0xAEBE90E6852B5D8B, 0xD816B41F51DDFE0E, 0xD42D0D0CB322EB1A, 0xD822037D25E726F5,
		0x40B3C50513C1A569, 0x501149B3778769E0, 0xEEC39CBEEB053537, 0xE5656972B826C0C0,
		0x2ABB81F97E344DA3, 0x713C9A950E8A5B88, 0xD9FFFF5F7BD66650, 0x141FDC85DA663D5B,
		0x23BD412B11F7AD04, 0xE6041438CA05C473, 0x1308798740D53B78, 0x32F31756C55CB51E,
		0xA8C0868927A649AF, 0x96DE7C9AD8C2A3EE, 0xEE09DA6253C8792C, 0x5AD012B56FB37828,
		0xAEC841BE889E0E7F, 0x839E20F245B576FB, 0x1AB3EF429BF569FB, 0xA0F4BC1D878C9502,
		0x15B4904FCC6B6480, 0xD442703133C453DC, 0x70AAAA90AA4C955D, 0xCBC46DDC262FEFA2,
		0x2C8004891EB62E1F, 0x03FABBF8688D839D, 0x07F93EC402EB06B3, 0xF1A001DB61E6E97F,
		0xABBC8989396E97AA, 0xDABA06F3FD00DF64, 0xCCAF196A6D7C186D, 0x43CC93FCB0479B24,
		0x764CEC93237D2E19, 0xFBF31D578F9D8303, 0x50F10F008C541073, 0x3376EAC26838F500,
		0xB633D900B8F0A870, 0x311EEC60C21F9CA5, 0x1620141229CE17C2, 0x566C68D6EF484F22
	},
	{
		0xC602D9DFFAF76EEE, 0x080C6E9C8B8F7553, 0x530F9B498D961C17, 0xB035E5BAB602EDFF,
		0xE234243EE5F482BA, 0x6BF9A727DDC8D747, 0x59345E89BB75371C, 0x212AACD007367B8B,
		0xFA08E202B894237E, 0x1CE1BE2324C08E58, 0x0F0F9A1CD0F34A53, 0x61C0431E995126D6,
		0x692E936663DD4413, 0x91267F2486A1CB0A, 0xB9DE8EE56DE653D0, 0x14E08C8115672D06,
		0x356B2F907A1EE0C5, 0x5DFA21DCEBB2D3FF, 0x065497E0075D27D0, 0x9DCB4523981743AB,
		0x17AD1521FCC87856, 0x9CDD561F43A273D0, 0x2072A63750DC3970, 0x34EBEFDA044595DA,
		0xACB72E4A853C4471, 0x58618DC10DB369C0, 0xC3AC415D356B4200, 0xBBB94D7A78D0EEC0,
		0x303D4187F11928C2, 0x9D22A11074D30046, 0x8322FBFA92B323FE, 0x238BC81F016A457A,
		0xBE6FC1E262F51782, 0x6AA3340A986C69CC, 0x3E64D5ADBCBF6F07, 0xC0A0AE1C92730245,
		0xA4C1F7AFEA7E0361, 0xCF9E34A4BF9DC2BD, 0xD70D88B89128E42C, 0x409512E60A9E11B8,
		0x8BCBAC2A1DD26D4C, 0x905651EC8F0BB6ED, 0x4387C136D6E4BD0E, 0x918B9ADD62AB9F26,
		0x5AFC7FC13B5AE497, 0x57E560CD235E09BB, 0xD8A4DA42F2432E50, 0x646958EA5CFD0FB3,
		0xE472D1179517A9D8, 0x745509B22250E649, 0xEBD9E7B267589891, 0x81803078F11DFE67,
		0xD65DF276F72CF64B, 0x49EE36DAB7EA8ADD, 0xC4A95D7B5444BD05, 0x601180A27947B4C9,
		0x0A0E99AE5CCC7DF9, 0xC246AB42B66A9193, 0xA262C26A0B6B31A8, 0x3D32597E74F33BAC,
		0x1887E25958C1C1CB, 0xF1EED98C828D6A87, 0x9204276D87295E3D, 0x1F49BF8C4508C4D5
	}
};
