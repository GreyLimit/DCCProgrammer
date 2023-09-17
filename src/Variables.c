/*
 *	Variables.c
 *
 * 	Define all the CV configuration data the program uses
 *	to understand what the CVs actually represent.
 */

#include "Compare.h"
#include "Const.h"
#include "Variables.h"
#include "CVs.h"

/************************************************************************
 *									*
 *	Define all of the enumerated types the CV values require.	*
 *									*
 ************************************************************************/

/*
 *	Define Enumerated values.
 */
 
static ENUMERATIONS enum_decoder = {
	"state", TRUE,
	2, {{ "multifunction", 0 },{ "accessory", 1 }}
};
static ENUMERATIONS enum_enable_disable = {
	"state", TRUE,
	2, {{ "disable", 0 },{ "enable", 1 }}
};
static ENUMERATIONS enum_inverted_enable_disable = {
	"state", TRUE,
	2, {{ "enable", 0 },{ "disable", 1 }}
};
static ENUMERATIONS enum_direction = {
	"direction", TRUE,
	2, {{ "normal", 0 },{ "reversed", 1 }}
};
static ENUMERATIONS enum_sign = {
	"sign", TRUE,
	2, {{ "plus", 0 },{ "minus", 1 }}
};
static ENUMERATIONS enum_light_control = {
	"light_control", TRUE,
	2, {{ "direction", 0 },{ "function", 1 }}
};
static ENUMERATIONS enum_power_source = {
	"power_source", TRUE,
	2, {{ "NMEA", 0 },{ "alternative", 1 }}
};
static ENUMERATIONS enum_power_sources = {
	"power_sources", FALSE,
	6, {{ "Analogue", 1 },{ "Radio", 2 },{ "Zero_1", 4 },{ "TRIX", 8 },{ "CTC16_RailCommand", 16 },{ "FMZ", 32 }}
};
static ENUMERATIONS enum_manufacturers = {
	"manufacturer", TRUE,
	164, {
		{ "AdvanceICEngineering",		17	},
		{ "AMW",				19	},
		{ "ANEModelCoLtd",			45	},
		{ "Aristo-CraftTrains",			34	},
		{ "Arnold–Rivarossi",			173	},
		{ "AtlasModelRailroadProducts",		127	},
		{ "AuroTrains",				170	},
		{ "Auvidel",				76	},
		{ "AXJElectronics",			110	},
		{ "BachmannTrains",			101	},
		{ "BenezanElectronics",			114	},
		{ "Berros",				122	},
		{ "BLOCKsignalling",			148	},
		{ "Bluecher-Electronic",		60	},
		{ "BlueDigital",			225	},
		{ "Brelec",				31	},
		{ "BRAWAModellspielwarenGmbH&Co.",	186	},
		{ "BroadwayLimitedImportsLLC",		38	},
		{ "Capecom",				47	},
		{ "CMLElectronicsLimited",		1	},
		{ "cmOSEngineering",			130	},
		{ "ComputerDialysisFrance",		105	},
		{ "Con-ComGmbH",			204	},
		{ "csikos-muhely",			120	},
		{ "cTElektronik",			117	},
		{ "CVPProducts",			135	},
		{ "DapolLimited",			154	},
		{ "DCCconcepts",			36	},
		{ "DCC-Gaspar-Electronic",		124	},
		{ "DCCSuppliesLtd",			51	},
		{ "DCCTrainAutomation",			144	},
		{ "DesktopStation",			140	},
		{ "DietzModellbahntechnik",		115	},
		{ "Digi-CZ",				152	},
		{ "Digikeijs",				42	},
		{ "DigitalBahn",			64	},
		{ "DigitoolsElektronikaKft",		75	},
		{ "Digitrax",				129	},
		{ "Digsight",				30	},
		{ "Doehler&Haas",			97	},
		{ "drM",				164	},
		{ "EducationalComputerInc.",		39	},
		{ "Electronik&ModelProduktion",		35	},
		{ "ElectronicSolutionsUlmGmbH",		151	},
		{ "ElectroniscriptInc.",		94	},
		{ "E-Modell",				69	},
		{ "FrateschiModelTrains",		128	},
		{ "Fucik",				158	},
		{ "Gaugemaster",			65	},
		{ "Gebr.FleischmannGmbH&Co.",		155	},
		{ "Nucky",				156	},
		{ "GFBDesigns",				46	},
		{ "GooVerModels",			81	},
		{ "Haber&KoenigElectronicsGmbH(HKE)",	111	},
		{ "HAGModelleisenbahnAG",		82	},
		{ "HarmanDCC",				98	},
		{ "HattonsModelRailways",		79	},
		{ "HeljanA/S",				28	},
		{ "HellerModenlbahn",			67	},
		{ "HelvestSystemsGmbH",			167	},
		{ "HONSModel",				88	},
		{ "HornbyHobbiesLtd",			48	},
		{ "IntegratedSignalSystems",		102	},
		{ "IntelligentCommandControl",		133	},
		{ "JokaElectronic",			49	},
		{ "JMRI",				18	},
		{ "JSS-Elektronic",			83	},
		{ "KAMIndustries",			22	},
		{ "KATOPrecisionModels",		40	},
		{ "Kevtronicscc",			93	},
		{ "KreischerDatentechnik",		21	},
		{ "KRESGmbH",				58	},
		{ "Krois-Modell",			52	},
		{ "KuehnIng.",				157	},
		{ "LaisDCC",				134	},
		{ "LenzElektronikGmbH",			99	},
		{ "LDH",				56	},
		{ "LGB(ErnstPaulLehmannPatentwerk)",	159	},
		{ "LSdigital",				112	},
		{ "LSModelsSprl",			77	},
		{ "MaisondeDCC",			166	},
		{ "MassothElektronikGmbH",		123	},
		{ "MAWEElektronik",			68	},
		{ "MBTronik–PiNGITmBH",			26	},
		{ "MDElectronics",			160	},
		{ "MistralTrainModels",			29	},
		{ "MoBaTron.de",			24	},
		{ "ModelElectronicRailwayGroup",	165	},
		{ "ModelRectifierCorp.",		143	},
		{ "ModelTrainTechnology",		168	},
		{ "ModelleisenbahnGmbH(formerlyRoco)",	161	},
		{ "MöllehemGårdsproduktion",		126	},
		{ "MTBModel",				72	},
		{ "MTHElectricTrainsInc.",		27	},
		{ "MÜTGmbH",				118	},
		{ "MyLocoSound",			116	},
		{ "N&QElectronics",			50	},
		{ "NACServicesInc.",			37	},
		{ "NagasueSystemDesignOffice",		103	},
		{ "Nagoden",				108	},
		{ "NCECorporation(formerlyNorthCoastEngineering)",	11	},
		{ "NewYorkByanoLimited",		71	},
		{ "Ngineering",				43	},
		{ "NMRAReserved(forextendedID#’s)",	238	},
		{ "Noarail",				63	},
		{ "Nucky",				156	},
		{ "NYRS",				136	},
		{ "Opherline1",				106	},
		{ "Passmann",				41	},
		{ "PhoenixSoundSystemsInc.",		107	},
		{ "PIKO",				162	},
		{ "PpPDigital",				74	},
		{ "Pojezdy.EU",				89	},
		{ "Praecipuus",				33	},
		{ "PRICOMDesign",			96	},
		{ "ProfiLokModellbahntechnikGmbH",	125	},
		{ "PSI–Dynatrol",			14	},
		{ "Public Domain & DIY Decoders",	13	},
		{ "QElectronicsGmbH",			55	},
		{ "QSIndustries(QSI)",			113	},
		{ "RailflyerModelPrototypesInc.",	84	},
		{ "RailnetSolutionsLLC",		66	},
		{ "RailsEuropExpress",			146	},
		{ "RailstarsLimited",			91	},
		{ "RamfixxTechnologies(Wangrow)",	15	},
		{ "RampinoElektronik",			57	},
		{ "RautenhausDigitalVertrieb",		53	},
		{ "RealRailEffects",			139	},
		{ "RegalWayCo.Ltd",			32	},
		{ "RockJunctionControls",		149	},
		{ "Rocrail",				70	},
		{ "RR-Cirkits",				87	},
		{ "SHelperService",			23	},
		{ "SandaKanIndustrialLtd.",		95	},
		{ "ShourtLine",				90	},
		{ "SLOMORailroadModels",		142	},
		{ "SpectrumEngineering",		80	},
		{ "SPROG-DCC",				44	},
		{ "T4T–TechnologyforTrainsGmbH",	20	},
		{ "TamValleyDepot",			59	},
		{ "TamsElektronikGmbH",			62	},
		{ "Tawcrafts",				92	},
		{ "TCHTechnology",			54	},
		{ "TeamDigitalLLC",			25	},
		{ "Tehnologistic(train-O-matic)",	78	},
		{ "TheElectricRailroadCompany",		73	},
		{ "Throttle-Up(Soundtraxx)",		141	},
		{ "TrainControlSystems",		153	},
		{ "TrainIDSystems",			138	},
		{ "TrainModules",			61	},
		{ "TrainTechnology",			2	},
		{ "TrainTech",				104	},
		{ "TrenesDigitales",			100	},
		{ "TrixModelleisenbahn",		131	},
		{ "UhlenbrockGmbH",			85	},
		{ "UmelecIng.Buero",			147	},
		{ "ViessmannModellspielwarenGmbH",	109	},
		{ "Wm.K.WalthersInc.",			150	},
		{ "W.S.AtarasEngineering",		119	},
		{ "WangrowElectronics",			12	},
		{ "WekommEngineeringGmbH",		86	},
		{ "WPRailshops",			163	},
		{ "ZimoElektronik",			145	},
		{ "ZTC",				132	},
	}
};

/************************************************************************
 *									*
 *	Define the way the various CVs are accessed, but not the	*
 *	specific meaning of each piece of data.				*
 *									*
 ************************************************************************/

/*
 *	CV 1 Component Values.
 */
static BINARY_VALUE cv1_06 = {
	"cv1/0-6", TRUE,
	1, {{ 1, 7, 0 }}
};
static BINARY_VALUE cv1_7 = {
	"cv1/7", TRUE,
	1, {{ 1, 1, 7 }}
};

/*
 *	CV 2.
 */
static BINARY_VALUE cv2_07 = {
	"cv2/0-7", TRUE,
	1, {{ 2, 8, 0 }}
};

/*
 *	CV 3.
 */
static BINARY_VALUE cv3_07 = {
	"cv3/0-7", TRUE,
	1, {{ 3, 8, 0 }}
};

/*
 *	CV 4.
 */
static BINARY_VALUE cv4_07 = {
	"cv4/0-7", TRUE,
	1, {{ 4, 8, 0 }}
};

/*
 *	CV 5.
 */
static BINARY_VALUE cv5_07 = {
	"cv5/0-7", TRUE,
	1, {{ 5, 8, 0 }}
};

/*
 *	CV 6.
 */
static BINARY_VALUE cv6_07 = {
	"cv6/0-7", TRUE,
	1, {{ 6, 8, 0 }}
};

/*
 *	CV 7.
 */
static BINARY_VALUE cv7_07 = {
	"cv7/0-7", TRUE,
	1, {{ 7, 8, 0 }}
};

/*
 *	CV 8.
 */
static BINARY_VALUE cv8_07 = {
	"cv8/0-7", TRUE,
	1, {{ 8, 8, 0 }}
};

/*
 *	CV 9.
 */
static BINARY_VALUE cv9_07 = {
	"cv9/0-7", TRUE,
	1, {{ 9, 8, 0 }}
};

/*
 *	CV 10.
 */
static BINARY_VALUE cv10_07 = {
	"cv10/0-7", TRUE,
	1, {{ 10, 8, 0 }}
};

/*
 *	CV 11.
 */
static BINARY_VALUE cv11_07 = {
	"cv11/0-7", TRUE,
	1, {{ 11, 8, 0 }}
};

/*
 *	CV 12.
 */
static BINARY_VALUE cv12_07 = {
	"cv12/0-7", TRUE,
	1, {{ 12, 8, 0 }}
};

/*
 *	CV 17 + CV 18 Component Values.
 */
static BINARY_VALUE cv17_67 = {
	"cv17/6-7",  TRUE,
	1, {{ 17, 2, 6 }}
};
static BINARY_VALUE cv17_05_cv18_07 = {
	"cv17/0-5_cv18/0-7", TRUE,
	2, {{ 17, 6, 0 },{ 18, 8, 0 }}
};

/*
 *	CV 19 Component values.
 */
static BINARY_VALUE cv19_06 = {
	"cv19/0-6", TRUE,
	1, {{ 19, 7, 0 }}
};
static BINARY_VALUE cv19_7 = {
	"cv19/7", TRUE,
	1, {{ 19, 1, 7 }}
};

/*
 *	CV 23
 */
static BINARY_VALUE cv23_06 = {
	"cv23/0-6", TRUE,
	1, {{ 23, 7, 0 }}
};
static BINARY_VALUE cv23_7 = {
	"cv23/7", TRUE,
	1, {{ 23, 1, 7 }}
};

/*
 *	CV 24
 */
static BINARY_VALUE cv24_06 = {
	"cv24/0-6", TRUE,
	1, {{ 24, 7, 0 }}
};
static BINARY_VALUE cv24_7 = {
	"cv24/7", TRUE,
	1, {{ 24, 1, 7 }}
};

/*
 *	CV 25
 */
static BINARY_VALUE cv25_07 = {
	"cv25/0-7", TRUE,
	1, {{ 25, 8, 0 }}
};

/*
 *	CV 29 Component Values.
 */
static BINARY_VALUE cv29_0 = {
	"cv29/0", TRUE,
	1, {{ 29, 1, 0 }}
};
static BINARY_VALUE cv29_1 = {
	"cv29/1", TRUE,
	1, {{ 29, 1, 1 }}
};
static BINARY_VALUE cv29_2 = {
	"cv29/2", TRUE,
	1, {{ 29, 1, 2 }}
};
static BINARY_VALUE cv29_3 = {
	"cv29/3", TRUE,
	1, {{ 29, 1, 3 }}
};
static BINARY_VALUE cv29_4 = {
	"cv29/4", TRUE,
	1, {{ 29, 1, 4 }}
};
static BINARY_VALUE cv29_5 = {
	"cv29/5", TRUE,
	1, {{ 29, 1, 5 }}
};
static BINARY_VALUE cv29_7 = {
	"cv29/7", TRUE,
	1, {{ 29, 1, 7 }}
};

/*
 *	CV 65
 */
static BINARY_VALUE cv65_07 = {
	"cv65/0-7", TRUE,
	1, {{ 65, 8, 0 }}
};

/*
 *	CV 66
 */
static BINARY_VALUE cv66_07 = {
	"cv66/0-7", TRUE,
	1, {{ 66, 8, 0 }}
};

/*
 *	CV 67 through to CV 94
 *
 *	28 locations (inclusive)
 *	used as a use configurable
 *	speed table.
 *
 *	Each location has a value
 *	from 0 to 255.
 *
 *	This is enabled by setting
 *	CV29/4
 */
static BINARY_VALUE cv67_cv94 = {
	"cv67_cv94", FALSE,
	28, {
		{ 67, 8, 0 }, { 68, 8, 0 }, { 69, 8, 0 }, { 70, 8, 0 },
		{ 71, 8, 0 }, { 72, 8, 0 }, { 73, 8, 0 }, { 74, 8, 0 },
		{ 75, 8, 0 }, { 76, 8, 0 }, { 77, 8, 0 }, { 78, 8, 0 },
		{ 79, 8, 0 }, { 80, 8, 0 }, { 81, 8, 0 }, { 82, 8, 0 },
		{ 83, 8, 0 }, { 84, 8, 0 }, { 85, 8, 0 }, { 86, 8, 0 },
		{ 87, 8, 0 }, { 88, 8, 0 }, { 89, 8, 0 }, { 90, 8, 0 },
		{ 91, 8, 0 }, { 92, 8, 0 }, { 93, 8, 0 }, { 94, 8, 0 }
	}
};

/*
 *	CV 95
 */
static BINARY_VALUE cv95_07 = {
	"cv95/0-7", TRUE,
	1, {{ 95, 8, 0 }}
};


/************************************************************************
 *									*
 *	Define test cases for enable/disable specific logical		*
 *	functions.							*
 *									*
 ************************************************************************/
 
static BINARY_CASE case_conf_alt_power = {
	"conf_alt_power", 1, FALSE, 1, &cv29_2
};
static BINARY_CASE case_alt_power_adrs = {
	"alt_power_adrs", 0, FALSE, 0, &cv1_06
};
static BINARY_CASE case_nmea_power_adrs = {
	"nmea_power_adrs", 0, TRUE, 3, &cv1_06
};
static BINARY_CASE case_clear_cv1_7 = {
	"cv1_7_is_clear", 0, FALSE, 0, &cv1_7
};
static BINARY_CASE case_fill_cv17_67 = {
	"cv17_67_are_full", 3, FALSE, 3, &cv17_67
};
static BINARY_CASE case_long_address = {
	"use_long_address", 1, FALSE, 1, &cv29_5
};
static BINARY_CASE case_short_address = {
	"use_short_address", 0, FALSE, 0, &cv29_5
};
static BINARY_CASE has_user_speed_table = {
	"use_local_speed_table", 1, FALSE, 1, &cv29_4
};

/************************************************************************
 *									*
 *	DCC decoder logical functions.					*
 *									*
 ************************************************************************/

/*
 *	Set the (current) number of logical values defined.
 */
#define TOTAL_LOGICAL_VALUES	31
 
LOGICAL_VALUE functions[ TOTAL_LOGICAL_VALUES ] = {
	{
		"direction",				/* Set direction of decoder */
		0, { },
		&enum_direction,			/* Enumerated values for direction */
		TRUE,					/* Yes, Read/Write */
		0, 0,					/* Range not required */
		&cv29_0					/* CV29 bit 0 */
	},
	{
		"light_control",			/* Set control of lights */
		0, { },
		&enum_light_control,			/* Enumerated values for light control */
		TRUE,					/* Yes, Read/Write */
		0, 0,					/* Range not required */
		&cv29_1					/* CV29 bit 1 */
	},
	{
		"power_source",				/* Set power source */
		0, { },
		&enum_power_source,			/* Enumerated values for power source */
		TRUE,					/* Yes, Read/Write */
		0, 0,					/* Range not required */
		&cv29_2					/* CV29 bit 2 */
	},
	{
		"decoder_type",				/* What type of decoder? */
		0, { },
		&enum_decoder,
		FALSE,
		0, 0,
		&cv29_7					/* CV29 bit 7 */
	},
	{
		"alt_power_source",			/* Where does aternative power come from? */
		3, { &case_conf_alt_power, &case_clear_cv1_7, &case_alt_power_adrs },
		&enum_power_sources,			/* Where is the power from? */
		TRUE,					/* Yes, Read/Write */
		0, 0,					/* Range not required */
		&cv12_07				/* CV12 bits 0-7 */
	},
	{
		"bidirectional_comms",			/* Bidirectional communications enabled? */
		0, { },
		&enum_inverted_enable_disable,		/* Enabled or Disabled? */
		TRUE,					/* Yes, Read/Write */
		0, 0,					/* Range not required */
		&cv29_3					/* CV29 bit 3 */
	},
	{
		"accel_adjust",				/* Acceleration Adjustment value */
		0, { },
		NULL,					/* Numeric Value */
		TRUE,					/* Yes, Read/Write */
		0, 127,					/* All 7 bit values */
		&cv23_06				/* CV23 bits 0 to 6 */
	},
	{
		"accel_sign",				/* Acceleration Sign */
		0, { },
		&enum_sign,				/* Sign: plus/minus */
		TRUE,					/* Yes, Read/Write */
		0, 0,					/* Not Used */
		&cv23_7					/* CV23 bit 7 */
	},
	{
		"decel_adjust",				/* Deceleration Adjustment value */
		0, { },
		NULL,					/* Numeric Value */
		TRUE,					/* Yes, Read/Write */
		0, 127,					/* All 7 bit values */
		&cv24_06				/* CV24 bits 0 to 6 */
	},
	{
		"decel_sign",				/* Deceleration Sign */
		0, { },
		&enum_sign,				/* Sign: plus/minus */
		TRUE,					/* Yes, Read/Write */
		0, 0,					/* Not Used */
		&cv24_7					/* CV24 bit 7 */
	},
	{
		"alt_speed_table",			/* Select an alternative speed table */
		0, { },
		NULL,					/* Numeric Value */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* Full range */
		&cv25_07				/* CV25 all 8 bits */
	},
	{
		"kick_start",				/* Extra kick to move away from stationary */
		0, { },
		NULL,					/* Numeric Value */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* Full range */
		&cv65_07				/* CV65 all 8 bits */
	},
	{
		"forward_trim",				/* Adjustment to forwards speed */
		0, { },
		NULL,					/* Numeric Value */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* Full range */
		&cv66_07				/* CV66 all 8 bits */
	},
	{
		"reverse_trim",				/* Adjustment to reverse speeds */
		0, { },
		NULL,					/* Numeric Value */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* Full range */
		&cv95_07				/* CV95 all 8 bits */
	},
	{
		"user_speed_table",			/* Using a bespoke speed table? */
		0, { },
		&enum_enable_disable,			/* Enabled or Disabled? */
		TRUE,					/* Yes, Read/Write */
		0, 0,					/* Range not required */
		&cv29_4					/* CV29 bit 4 */
	},
	{
		"speed_table",				/* The local speed table */
		1, { &has_user_speed_table },		/* Only valid if cv29/4 is set */
		NULL,					/* Numeric Values */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* Full range on each element */
		&cv67_cv94				/* 28 CVs from cv67 to cv94 */
	},
	{
		"time_out",				/* Period decoder will continue without valid packet */
		0, { },
		NULL,					/* Numeric Value */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* All 8 bit values */
		&cv11_07				/* CV11 all bits */
	},
	{
		"v_start",				/* Start Voltage (ratio of available voltage) */
		0, { },
		NULL,					/* Numeric value */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* All 8 bit values */
		&cv2_07					/* CV2 bits 0 to 7 */
	},
	{
		"acceleration",				/* Acceleration Rate */
		0, { },
		NULL,					/* Numeric value */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* All 8 bit values */
		&cv3_07					/* CV3 bits 0 to 7 */
	},
	{
		"deceleration",				/* deceleration Rate */
		0, { },
		NULL,					/* Numeric value */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* All 8 bit values */
		&cv4_07					/* CV4 bits 0 to 7 */
	},
	{
		"v_high",				/* High Voltage (ratio of available voltage) */
		0, { },
		NULL,					/* Numeric value */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* All 8 bit values */
		&cv5_07					/* CV5 bits 0 to 7 */
	},
	{
		"v_mid",				/* Mid point Voltage (ratio of available voltage) */
		0, { },
		NULL,					/* Numeric value */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* All 8 bit values */
		&cv6_07					/* CV6 bits 0 to 7 */
	},
	{
		"extended_address",			/* Long addresses enabled? */
		3, { &case_clear_cv1_7, &case_nmea_power_adrs, &case_fill_cv17_67 },
		&enum_enable_disable,			/* Enabled or Disabled? */
		TRUE,					/* Yes, Read/Write */
		0, 0,					/* Range not required */
		&cv29_5					/* CV29 bit 5 */
	},
	{
		"long_address",				/* Long Address to use */
		4, { &case_clear_cv1_7, &case_nmea_power_adrs, &case_fill_cv17_67, &case_long_address },
		NULL,					/* Numeric value */
		TRUE,					/* Yes, Read/Write */
		1, 10239,				/* Range of long addresses */
		&cv17_05_cv18_07			/* 14 bits spread between CV17 and CV18 */
	},
	{
		"short_address",			/* Short Address to use */
		3, { &case_clear_cv1_7, &case_nmea_power_adrs, &case_short_address },
		NULL,					/* Numeric value */
		TRUE,					/* Yes, Read/Write */
		1, 127,					/* non-zero 7 bit value */
		&cv1_06					/* CV 1 bits 0 to 6 */
	},
	{
		"consist",				/* Consist address of this decoder */
		0, { },
		NULL,					/* Numeric value */
		TRUE,					/* Yes, Read/Write */
		0, 127,					/* Consist address to catch */
		&cv19_06				/* CV19 bits 0 to 6 */
	},
	{
		"consist_dir",				/* Set direction within consist */
		0, { },
		&enum_direction,			/* Enumerated values for direction */
		TRUE,					/* Yes, Read/Write */
		0, 0,					/* Range not required */
		&cv19_7					/* CV19 bit 7 */
	},
	{
		"Manufacturer_ID",			/* Who made the device */
		0, { },
		&enum_manufacturers,			/* List of manufacturers */
		FALSE,					/* READ-ONLY */
		0, 0,					/* Range not required */
		&cv8_07					/* CV8 bits 0 to 7 */
	},
	{
		"Manufacturer_Model",			/* Model Version */
		0, { },
		NULL,
		FALSE,					/* READ-ONLY */
		0, 0,					/* Range not required */
		&cv7_07					/* CV8 bits 0 to 7 */
	},
	{
		"PWM_period",				/* PWM total period? */
		0, { },
		NULL,					/* Numeric Value */
		TRUE,					/* Yes, Read/Write */
		0, 255,					/* Range not required */
		&cv9_07					/* CV9 bits 0 to 7 */
	},
	{
		"BEMF_cutoff",				/* When to cut the back EMF */
		0, { },
		NULL,					/* Numeric Value */
		TRUE,					/* Yes, Read/Write */
		1, 128,					/* 128 speeds */
		&cv10_07				/* CV10 bits 0 to 7 */
	}
};


/************************************************************************
 *									*
 *	Support routines for the					*
 *									*
 ************************************************************************/

/*
 *	Define a simple array which converts a bit count
 *	into a bit 0 based bit mask.
 */
#define MAXIMUM_BITS	8
static byte bit_mask[ MAXIMUM_BITS+1 ] = {
	0, 1, 3, 7, 15, 31, 63, 127, 255
};

/*
 *	Get a value from the variable array.
 *
 *	If combined is false then element is the array index number.
 */
static STATUS get_binary_value( BINARY_VALUE *ptr, int element, int *value ) {
	STATUS		ret;
	BINARY_DATA	*d;
	byte		m, v, b;

	assert( ptr != NULL );
	assert(( ptr->elements > 0 )&&( ptr->elements <= BINARY_DATA_LIMIT ));
	assert( value != NULL );

	if( ptr->combined ) {
		int	sum;
		
		sum = 0;
		/*
		 *	When reading a variable we count forwards through
		 * 	the elements that make up the variable dealing with
		 * 	the MSBs first.
		 */
		for( int i = 0; i < ptr->elements; i++ ) {
			/*
			 *	Set up short cut to binary data being handled.
			 */
			d = &( ptr->data[ i ]);

			/*
			 *	Execute integrity check on the static data being
			 * 	used.  This is a "belt and braces" check.
			 */
			assert(( d->cv > 0 )&&( d->cv <= MAXIMUM_CV_NUMBER ));
			assert(( d->bits > 0 )&&( d->bits <= 8 ));
			assert(( d->lsb >= 0 )&&( d->lsb < 8 ));
			assert(( d->bits + d->lsb ) <= 8 );

			/*
			 * 	Read out the indicated CV, shift the mask and
			 *	value obtained so that the required value starts
			 * 	at bit 0.  Verify that the mask is set for all
			 * 	the bits the should contain the value.  If mask
			 * 	OK then fold value bits into the sum.
			 */
			if(( ret = final_read_cv( d->cv, &m, &v ))) return( ret );
			b = bit_mask[ d->bits ];
			m = ( m >> d->lsb ) & b;
			v = ( v >> d->lsb ) & b;
			if( m != b ) return( LV_VALUE_INCOMPLETE );

			/*
			 *	Roll new data into the sum value.
			 */
			sum = ( sum << d->bits ) | v;
		}
		*value = sum;
		return( SUCCESS );
	}
	/*
	 * 	Accessing an "array" style CV value; make sure the index
	 * 	supplied is inside the valid range.
	 */
	if(( element < 0 )||( element >= ptr->elements )) return( LV_INDEX_INVALID );
	
	/*
	 *	Set up short cut to binary data being handled.
	 */
	d = &( ptr->data[ element ]);
	
	/*
	 *	Execute integrity check on the static data being
	 * 	used.  This is a "belt and braces" check.
	 */
	assert(( d->cv > 0 )&&( d->cv <= MAXIMUM_CV_NUMBER ));
	assert(( d->bits > 0 )&&( d->bits <= 8 ));
	assert(( d->lsb >= 0 )&&( d->lsb < 8 ));
	assert(( d->bits + d->lsb ) <= 8 );

	/*
	 * 	Extract CV value, process and check it (all as above).
	 */
	final_read_cv( d->cv, &m, &v );
	b = bit_mask[ d->bits ];
	m = ( m >> d->lsb ) & b;
	v = ( v >> d->lsb ) & b;
	if( m != b ) return( LV_VALUE_INCOMPLETE );
	*value = v;
	return( SUCCESS );
}


/*
 *	Set a value into the variable array, return true on success.
 *	Return false if any of the writes into the CV fails.
 *
 *	If combined is false then element is the array index number.
 */
static STATUS set_binary_value( BINARY_VALUE *ptr, int element, int value ) {
	STATUS		ret;
	BINARY_DATA	*d;
	byte		m, v, b;

	assert( ptr != NULL );
	assert(( ptr->elements > 0 )&&( ptr->elements <= BINARY_DATA_LIMIT ));

	if( ptr->combined ) {
		/*
		 *	To set we count backwards through the elements
		 * 	of the variable so that we handle the LSBs first.
		 */
		for( int i = ptr->elements-1; i >= 0; i-- ) {
			/*
			 *	Set up short cut to binary data being handled.
			 */
			d = &( ptr->data[ i ]);

			/*
			 *	Execute integrity check on the static data being
			 * 	used.  This is a "belt and braces" check.
			 */
			assert(( d->cv > 0 )&&( d->cv <= MAXIMUM_CV_NUMBER ));
			assert(( d->bits > 0 )&&( d->bits <= 8 ));
			assert(( d->lsb >= 0 )&&( d->lsb < 8 ));
			assert(( d->bits + d->lsb ) <= 8 );

			/*
			 *	Construct the mask and value bits for this
			 * 	specific CV component of this variable.
			 */
			b = bit_mask[ d->bits ];
			v = ( value & b ) << d->lsb;
			m = b << d->lsb;

			/*
			 *	Remove the part of value we have extracted.
			 */
			value >>= d->bits;

			/*
			 * 	Write this partial value(v) and corresponding
			 * 	mask(m) into the target CV.
			 */
			if(( ret = final_write_cv( d->cv, m, v ))) return( ret );
		}
		return( SUCCESS );
	}
	/*
	 * 	Accessing an "array" style CV value; make sure the index
	 * 	supplied is inside the valid range.
	 */
	if(( element < 0 )||( element >= ptr->elements )) return( LV_INDEX_INVALID );
	
	/*
	 *	Set up short cut to binary data being handled.
	 */
	d = &( ptr->data[ element ]);

	/*
	 *	Execute integrity check on the static data being
	 * 	used.  This is a "belt and braces" check.
	 */
	assert(( d->cv > 0 )&&( d->cv <= MAXIMUM_CV_NUMBER ));
	assert(( d->bits > 0 )&&( d->bits <= 8 ));
	assert(( d->lsb >= 0 )&&( d->lsb < 8 ));
	assert(( d->bits + d->lsb ) <= 8 );

	/*
	 *	Construct the mask and value bits for this
	 * 	specific CV component of this variable.
	 */
	b = bit_mask[ d->bits ];
	v = ( value & b ) << d->lsb;
	m = b << d->lsb;

	/*
	 * 	Write this partial value(v) and corresponding
	 * 	mask(m) into the target CV.
	 */
	return( final_write_cv( d->cv, m, v ));
}


/*
 *	Check a case structure and return TRUE if valid, FALSE otherwise.
 */
static bool check_binary_case( BINARY_CASE *ptr ) {
	int	v;

	assert( ptr != NULL );

	if( get_binary_value( ptr->where, 0, &v ) == SUCCESS ) {
		if( ptr->negated ) return( ptr->value != v );
		return( ptr->value == v );
	}
	return( FALSE );

}
/*
 *	... as above but for an array of cases.
 */
static bool check_binary_cases( BINARY_CASE **ptr, int count ) {
	
	assert( ptr != NULL );
	assert(( count >= 0 )&&( count <= TEST_CASE_LIMIT ));

	for( int i = 0; i < count; i++ ) if( !check_binary_case( ptr[ i ])) return( FALSE );
	return( TRUE );

}

/*
 *	Set a binary check case into the CV values.
 */
static STATUS set_binary_case( BINARY_CASE *ptr ) {

	assert( ptr != NULL );

	/*
	 *	Check the case first as there's no need
	 * 	to try and force it if it is already
	 * 	applied.
	 */
	if( check_binary_case( ptr )) return( SUCCESS );
	return( set_binary_value( ptr->where, 0, ptr->reset ));
}
/*
 *	... as above but for an array of cases.
 */
static STATUS set_binary_cases( BINARY_CASE **ptr, int count ) {
	STATUS	ret;
	
	assert( ptr != NULL );
	assert(( count >= 0 )&&( count <= TEST_CASE_LIMIT ));

	for( int i = 0; i < count; i++ ) if(( ret = set_binary_case( ptr[ i ]))) return( ret );
	return( SUCCESS );
}

/*
 *	Convert a number to an enumeration value.
 */
static STATUS number_to_enumeration( ENUMERATIONS *enums, int val, char *value, int size ) {
	bool	sep;
	int	len;

	assert( enums != NULL );
	assert( value != NULL );
	assert( size >= NUMBER_BUFFER );

	/*
	 *	Is this a single value or a bit mapped set of values?
	 */
	if( enums->exclusive ) {
		/*
		 *	The simple case:  The CV is a single value that
		 * 	maps 1:1 with a textual meaning.
		 */
		for( int i = 0; i < enums->values; i++ ) {
			if( enums->value[ i ].value == val ) {
				/*
				 *	Found!
				 */
				if( strlen( enums->value[ i ].name ) < size ) {
					strcpy( value, enums->value[ i ].name );
					return( SUCCESS );
				}
				return( BUFFER_OVERFLOW );
			}
		}
		/*
		 * 	Getting here is an issue as the numeric value provided
		 * 	did not match any enumerated value.  Just "print" the
		 * 	value into the buffer.
		 */
		snprintf( value, size, "%d", val );
		return( SUCCESS );
	}
	/*
	 *	This is a set of values that we will need to break down into
	 * 	a set of OR separated strings (with optional value).
	 */
	sep = FALSE;		/* Don't need a separator initially. */
	for( int i = 0; i < enums->values; i++ ) {
		if( val & enums->value[ i ].value ) {
			/*
			 *	Add text to value and remove bits from
			 *	val.
			 */
			len = strlen( enums->value[ i ].name );
			if( len + 1 > size ) return( BUFFER_OVERFLOW );
			if( sep ) {
				*value++ = OR;
				size--;
			}
			sep = TRUE;
			value = stpcpy( value, enums->value[ i ].name );
			size -= len;
			val |= ~enums->value[ i ].value;
		}
	}
	/*
	 *	At this point if val is non-zero we try to add its
	 * 	value to the end of the buffer.
	 */
	if( val ) {
		if( size < NUMBER_BUFFER ) return( BUFFER_OVERFLOW );
		if( sep ) {
			*value++ = OR;
			size--;
		}
		snprintf( value, size, "%d", val );
	}
	return( SUCCESS );
}

static STATUS find_enumeration( ENUMERATION *data, int size, char *text, int *value ) {

	assert( data != NULL );
	assert( size > 0 );
	assert( text != NULL );
	assert( value != NULL );

	for( int i = 0; i < size; i++ ) {
		if( compare( text, data[ i ].name ) == 0 ) {
			*value = data[ i ].value;
			return( SUCCESS );
		}
	}
	return( LV_VALUE_INVALID );
}

static STATUS enumeration_to_number( ENUMERATIONS *enums, char *value, int *val ) {
	char	*sep;
	int	v;
	STATUS	ret;

	assert( enums != NULL );
	assert( value != NULL );
	assert( val != NULL );

	/*
	 *	Is this a single value or a bit mapped set of values?
	 */
	if( enums->exclusive ) {
		/*
		 *	The simple case:  Lookup the text in the enumerations
		 * 	and return the number required.
		 */
		return( find_enumeration( enums->value, enums->values, value, val ));
	}
	/*
	 *	This is a set of OR separated strings which will need to
	 *	be parsed to determine its proper numeric value.
	 */
	*val = 0;
	while(( sep = strchr( value, OR ))) {
		*sep = EOS;
		if(( ret = find_enumeration( enums->value, enums->values, value, &v ))) return( ret );
		*val |= v;
		*sep++ = OR;
		value = sep;
	}
	if(( ret = find_enumeration( enums->value, enums->values, value, &v ))) return( ret );
	*val |= v;
	return( SUCCESS );
}

static STATUS read_binary_value( int dcc, BINARY_VALUE *value ) {
	STATUS	ret;

	assert( dcc != ERROR );
	assert( value != NULL );

	for( int e = 0; e < value->elements; e++ ) {
		
		BINARY_DATA *d = &( value->data[ e ]);
		
		if(( ret = read_cv( dcc, d->cv, ( bit_mask[ d->bits ] << d->lsb )))) return( ret );
	}
	return( SUCCESS );
}


/************************************************************************
 *									*
 *	The logical Variables API					*
 *									*
 ************************************************************************/


/*
 *	Locate a function by name or abstract number (0..N)
 */
LOGICAL_VALUE *find_variable_by_name( char *name ) {

	assert( name != NULL );

	for( int i = 0; i < TOTAL_LOGICAL_VALUES; i++ ) if( compare( name, functions[ i ].name ) == 0 ) return( &( functions[ i ]));
	return( NULL );
}
LOGICAL_VALUE *find_variable_by_number( int number ) {

	if(( number < 0 )||( number >= TOTAL_LOGICAL_VALUES )) return( NULL );
	return( &( functions[ number ]));
}


/*
 *	Read the content of a variable from the decoder
 * 	on the programming track.
 *
 * 	To do this we need to read not only the CVs that
 *	contain the data that is the variables meaning, but
 * 	also the CVs (or parts thereof) which contain the
 * 	controlling case information.
 */
STATUS read_variable( int dcc, LOGICAL_VALUE *func ) {
	STATUS	ret;

	assert( dcc != ERROR );
	assert( func != NULL );
	assert( func->value != NULL );

	/*
	 *	Start with the main value components
	 */
	if(( ret = read_binary_value( dcc, func->value ))) return( ret );
	/*
	 *	Now we read all the conditional case values.
	 */
	for( int a = 0; a < func->asserts; a++ ) {
		if(( ret = read_binary_value( dcc, func->test[ a ]->where ))) return( ret );
	}
	return( SUCCESS );
}



/*
 *	Return the name of the variable.
 */
char *get_variable_name( LOGICAL_VALUE *func ) {

	assert( func != NULL );

	return( func->name );
}

/*
 *	Can the variable be updated?  Is it read/write?
 */
bool is_variable_updatable( LOGICAL_VALUE *func ) {

	assert( func != NULL );

	return( func->read_write );
}



/*
 *	Is the variable an enumerated type?  This has an impact
 * 	on which variable read/write routines should be used
 * 	when reading or modifying its content.
 */
bool is_variable_enumerated( LOGICAL_VALUE *func ) {

	assert( func != NULL );

	return( func->values != NULL );
}

/*
 *	Return the number of elements a logical value contains
 * 	(ie, "Is this an array?")  All non-array values return 1
 * 	and are accessed as element 0.  Arrays return a value N
 * 	(where N greater than 1) and are accessed with element
 * 	numbers 0 to N-1.
 */
int get_variable_elements( LOGICAL_VALUE *func ) {

	assert( func != NULL );
	assert( func->value != NULL );

	if( func->value->combined ) return( 1 );

	assert( func->value->elements >= 1 );
	
	return( func->value->elements );
}

/*
 *	Read and write routines provide access to the raw CV values
 * 	through the logical values defined.
 */
STATUS read_int_variable( LOGICAL_VALUE *func, int element, int *value ) {

	assert( func != NULL );
	assert( func->value != NULL );
	assert( func->values == NULL );
	assert( value != NULL );
	
	/*
	 *	Before accessing the value execute the checks.
	 */
	if( !check_binary_cases( func->test, func->asserts )) return( LV_CASES_INVALID );
	/*
	 *	Cases checked out, access the requested value.
	 */
	return( get_binary_value( func->value, element, value ));
}

STATUS read_enum_variable( LOGICAL_VALUE *func, int element, char *value, int size ) {
	STATUS	ret;
	int	val;

	assert( func != NULL );
	assert( func->value != NULL );
	assert( func->values != NULL );
	assert( value != NULL );
	
	/*
	 *	Before accessing the value execute the checks.
	 */
	if( !check_binary_cases( func->test, func->asserts )) return( LV_CASES_INVALID );
	/*
	 *	Cases checked out, access the requested value.
	 */
	if(( ret = get_binary_value( func->value, element, &val ))) return( ret );
	/*
	 *	Convert back to enumerated value.
	 */
	 return( number_to_enumeration( func->values, val, value, size ));
}

STATUS write_int_variable( LOGICAL_VALUE *func, int element, int value ) {
	STATUS	ret;

	assert( func != NULL );
	assert( func->value != NULL );
	assert( func->values == NULL );

	/*
	 *	Validate the range of the value before we go wading in with it.
	 */
	if(( value < func->minimum )||( value > func->maximum )) return( LV_VALUE_INVALID );
	/*
	 *	We try to set the value CV before setting the cases.
	 */
	if(( ret = set_binary_value( func->value, element, value ))) return( ret );
	/*
	 *	Having set the logical value, we then back fill all
	 * 	the case information to support it.
	 */
	return( set_binary_cases( func->test, func->asserts ));
}

STATUS write_enum_variable( LOGICAL_VALUE *func, int element, char *value ) {
	STATUS	ret;
	int	val;

	assert( func != NULL );
	assert( func->value != NULL );
	assert( func->values == NULL );
	assert( value != NULL );

	/*
	 *	First we convert the text into a numeric value.
	 */
	if(( ret = enumeration_to_number( func->values, value, &val ))) return( ret );
	/*
	 *	We try to set the value CV before setting the cases.
	 */
	if(( ret = set_binary_value( func->value, element, val ))) return( ret );
	/*
	 *	Having set the logical value, we then back fill all
	 * 	the case information to support it.
	 */
	return( set_binary_cases( func->test, func->asserts ));
}

/************************************************************************
 *									*
 *	Database and data dumping API					*
 *									*
 ************************************************************************/

/*
 *	Dump the Variable database to the provided stream.
 */
void dump_variables_database( FILE *stream ) {
	LOGICAL_VALUE	*lv;
	ENUMERATIONS	*ep;
	int		l;
	
	fprintf( stream, "Logical Variables:-\n" );
	for( int i = 0; i < TOTAL_LOGICAL_VALUES; i++ ) {
		lv = &( functions[ i ]);
		l = strlen( lv->name );
		fprintf( stream, "\t%s", lv->name );
		if( !lv->value->combined ) {
			fprintf( stream, "[%3d]", lv->value->elements );
			l += 5;
		}
		if(( l = 20 - l ) < 0 ) l = 1;
		while( l-- ) fprintf( stream, " " );
		fprintf( stream, "(%s) ",( lv->read_write? "RW": "RO" ));
		if(( ep = lv->values )) {
			fprintf( stream, "%s:", ep->name );
			for( int i = 0; i < ep->values; i++ ) fprintf( stream, " %s", ep->value[ i ].name );
		}
		else {
			fprintf( stream, "Range: %d-%d", lv->minimum, lv->maximum );
		}
		fprintf( stream, "\n" );
	}
}

/*
 * 	EOF
 */
