#include <mvbs/errno.h>
#include <mvbs/utils/cdefs.h>
#include <mvbs/rte/Rte_Dds_Adaptor.h>

#include <mvbs/utils/mm.h>
#include <mvbs/utils/mm_stat.h>
#include <mvbs/utils/log.h>
#include <mvbs/utils/time.h>

#if defined(TARGET_PRODUCT_LINUX) || defined(TARGET_PRODUCT_J6M_ACORE) || defined(TARGET_PRODUCT_MINGW)
#include <mvbs_aux/mvbs_aux.h>
#endif


#ifdef TARGET_PRODUCT_MINGW
#include <windows.h>
#endif

#include "vbslite_perfPlugin.h"

#ifndef UINT_MAX
#define UINT_MAX			(uint32_t)(-1)
#endif

#define MVBS_LOOP_CYCLE_MS		5

#define TOTAL_TIME_MS			72*60*60*1000		// 72h
#define READER_DUMP_PER_CNT		1000
#define WRITER_DUMP_PER_CNT		1000

#define MVBS_TEST_CONTINUE		1
#define MVBS_TEST_PASS			0
#define MVBS_TEST_AGAIN			1
#define MVBS_TEST_FAIL			-1

#define reader_topic_index(x)		x##_r_idx
#define writer_topic_index(x)		x##_w_idx

typedef void (*sample_init_t)(void *);


// static int gtx_ok_cnt;
static struct AgentHelloWorld sample1;
static Rte_Dds_TopicData data_w;
static Rte_Dds_Writer rte_w;
static Rte_Dds_TopicId topic_w = DEF_RTE_DDS_TOPIC("domain_0_topic_1Topic", 0 );

// static int grx_ok_cnt;
// static int32_t count = 0;
static struct AgentHelloWorld sample2 ;
static Rte_Dds_TopicData data_r;
static Rte_Dds_Reader rte_r;
static Rte_Dds_TopicId topic_r = DEF_RTE_DDS_TOPIC("domain_0_topic_0Topic", 0 );
/* The following code lines are for reader topic. */

static uint64_t total_send_package = 0;
static void time_event(Rte_Dds_Reader r)
{
	Rte_Dds_ReturnType ret;
	ret = Rte_Dds_RxData(r, true, &data_r, NULL);
	if (ret == RTE_DDS_RETCODE_OK) {
		memset(&sample1, 0, sizeof(struct AgentHelloWorld));
		memcpy(&sample1, data_r.data, sizeof(struct AgentHelloWorld));

		total_send_package++;

		sample1.sn = total_send_package;

		ret = Rte_Dds_TxData(rte_w, &data_w, NULL);
		if (ret != RTE_DDS_RETCODE_OK) {
			pr_warn("tx data failed!\n");
		}
	}
}


enum {
	reader_topic_index(HelloWorld1),
	reader_topic_index(HelloWorld2),
	reader_topic_index(HelloWorld3),
	reader_topic_index(HelloWorld4),
	reader_topic_index(HelloWorld5),
	reader_topic_index(HelloWorld6),
	reader_topic_index(HelloWorld7),
	reader_topic_index(HelloWorld8),
	reader_topic_index(HelloWorld9),
	reader_topic_index(HelloWorld10),
	reader_topic_index(HelloWorld11),
	reader_topic_index(HelloWorld12),
	reader_topic_index(HelloWorld13),
	reader_topic_index(HelloWorld14),
	reader_topic_index(HelloWorld15),
	reader_topic_index(HelloWorld16),
	reader_topic_index(HelloWorld17),
	reader_topic_index(HelloWorld18),
	reader_topic_index(HelloWorld19),
	reader_topic_index(HelloWorld20),
	reader_topic_index(HelloWorld21),
	reader_topic_index(HelloWorld22),
	reader_topic_index(HelloWorld23),
	reader_topic_index(HelloWorld24),
	reader_topic_index(HelloWorld25),
	reader_topic_index(HelloWorld26),
	reader_topic_index(HelloWorld27),
	reader_topic_index(HelloWorld28),
	reader_topic_index(HelloWorld29),
	reader_topic_index(HelloWorld30),
	reader_topic_index(HelloWorld31),
	reader_topic_index(HelloWorld32),
	reader_topic_index(HelloWorld33),
	reader_topic_index(HelloWorld34),
	reader_topic_index(HelloWorld35),
	reader_topic_index(HelloWorld36),
	reader_topic_index(HelloWorld37),
	reader_topic_index(HelloWorld38),
	reader_topic_index(HelloWorld39),
	reader_topic_index(HelloWorld40),
	reader_topic_index(HelloWorld41),
	reader_topic_index(HelloWorld42),
	reader_topic_index(HelloWorld43),
	reader_topic_index(HelloWorld44),
	reader_topic_index(HelloWorld45),
	reader_topic_index(HelloWorld46),
	reader_topic_index(HelloWorld47),
	reader_topic_index(HelloWorld48),
	reader_topic_index(HelloWorld49),
	reader_topic_index(HelloWorld50),
	reader_topic_index(HelloWorld51),
	reader_topic_index(HelloWorld52),
	reader_topic_index(HelloWorld53),
	reader_topic_index(HelloWorld54),
	reader_topic_index(HelloWorld55),
	reader_topic_index(HelloWorld56),
	reader_topic_index(HelloWorld57),
	reader_topic_index(HelloWorld58),
	reader_topic_index(HelloWorld59),
	reader_topic_index(HelloWorld60),
	reader_topic_index(HelloWorld61),
	reader_topic_index(HelloWorld62),
	reader_topic_index(HelloWorld63),
	reader_topic_index(HelloWorld64),
	reader_topic_index(HelloWorld65),
	reader_topic_index(HelloWorld66),
	reader_topic_index(HelloWorld67),
	reader_topic_index(HelloWorld68),
	reader_topic_index(HelloWorld69),
	reader_topic_index(HelloWorld70),
	reader_topic_index(HelloWorld71),
	reader_topic_index(HelloWorld72),
	reader_topic_index(HelloWorld73),
	reader_topic_index(HelloWorld74),
	reader_topic_index(HelloWorld75),
	reader_topic_index(HelloWorld76),
	reader_topic_index(HelloWorld77),
	reader_topic_index(HelloWorld78),
	reader_topic_index(HelloWorld79),
	reader_topic_index(HelloWorld80),
	reader_topic_index(HelloWorld81),
	reader_topic_index(HelloWorld82),
	reader_topic_index(HelloWorld83),
	reader_topic_index(HelloWorld84),
	reader_topic_index(HelloWorld85),
	reader_topic_index(HelloWorld86),
	reader_topic_index(HelloWorld87),
	reader_topic_index(HelloWorld88),
	reader_topic_index(HelloWorld89),
	reader_topic_index(HelloWorld90),
	reader_topic_index(HelloWorld91),
	reader_topic_index(HelloWorld92),
	reader_topic_index(HelloWorld93),
	reader_topic_index(HelloWorld94),
	reader_topic_index(HelloWorld95),
	reader_topic_index(HelloWorld96),
	reader_topic_index(HelloWorld97),
	reader_topic_index(HelloWorld98),
	reader_topic_index(HelloWorld99),
	reader_topic_index(HelloWorld100),
	reader_topic_index(HelloWorld101),
	reader_topic_index(HelloWorld102),
	reader_topic_index(HelloWorld103),
	reader_topic_index(HelloWorld104),
	reader_topic_index(HelloWorld105),
	reader_topic_index(HelloWorld106),
	reader_topic_index(HelloWorld107),
	reader_topic_index(HelloWorld108),
	reader_topic_index(HelloWorld109),
	reader_topic_index(HelloWorld110),
	reader_topic_index(HelloWorld111),
	reader_topic_index(HelloWorld112),
	reader_topic_index(HelloWorld113),
	reader_topic_index(HelloWorld114),
	reader_topic_index(HelloWorld115),
	reader_topic_index(HelloWorld116),
	reader_topic_index(HelloWorld117),
	reader_topic_index(HelloWorld118),
	reader_topic_index(HelloWorld119),
	reader_topic_index(HelloWorld120),
	reader_topic_index(HelloWorld121),
	reader_topic_index(HelloWorld122),
	reader_topic_index(HelloWorld123),
	reader_topic_index(HelloWorld124),
	reader_topic_index(HelloWorld125),
	reader_topic_index(HelloWorld126),
	reader_topic_index(HelloWorld127),
	reader_topic_index(HelloWorld128),
	reader_topic_index(HelloWorld129),
	reader_topic_index(HelloWorld130),
	reader_topic_index(HelloWorld131),
	reader_topic_index(HelloWorld132),
	reader_topic_index(HelloWorld133),
	reader_topic_index(HelloWorld134),
	reader_topic_index(HelloWorld135),
	reader_topic_index(HelloWorld136),
	reader_topic_index(HelloWorld137),
	reader_topic_index(HelloWorld138),
	reader_topic_index(HelloWorld139),
	reader_topic_index(HelloWorld140),
	reader_topic_index(HelloWorld141),
	reader_topic_index(HelloWorld142),
	reader_topic_index(HelloWorld143),
	reader_topic_index(HelloWorld144),
	reader_topic_index(HelloWorld145),
	reader_topic_index(HelloWorld146),
	reader_topic_index(HelloWorld147),
	reader_topic_index(HelloWorld148),
	reader_topic_index(HelloWorld149),
};

struct reader_meta_info {
	Rte_Dds_Reader	r;
	const char	*topic;
	void		*sample;
	uint16_t	period_ms;
	uint16_t	match_count;
	uint32_t	total_count;
	uint32_t	recv_count;
	uint32_t	fail_count;

	sample_init_t	init;

	void (*fn)(void *);

	uint32_t	print_per_cnt;
};

void HelloWorld1_cb(void *sample)
{
	HelloWorld1 *data = (HelloWorld1*)sample;
	(void)data;
}
void HelloWorld2_cb(void *sample)
{
	HelloWorld2 *data = (HelloWorld2*)sample;
	(void)data;
}
void HelloWorld3_cb(void *sample)
{
	HelloWorld3 *data = (HelloWorld3*)sample;
	(void)data;
}
void HelloWorld4_cb(void *sample)
{
	HelloWorld4 *data = (HelloWorld4*)sample;
	(void)data;
}
void HelloWorld5_cb(void *sample)
{
	HelloWorld5 *data = (HelloWorld5*)sample;
	(void)data;
}
void HelloWorld6_cb(void *sample)
{
	HelloWorld6 *data = (HelloWorld6*)sample;
	(void)data;
}
void HelloWorld7_cb(void *sample)
{
	HelloWorld7 *data = (HelloWorld7*)sample;
	(void)data;
}
void HelloWorld8_cb(void *sample)
{
	HelloWorld8 *data = (HelloWorld8*)sample;
	(void)data;
}
void HelloWorld9_cb(void *sample)
{
	HelloWorld9 *data = (HelloWorld9*)sample;
	(void)data;
}
void HelloWorld10_cb(void *sample)
{
	HelloWorld10 *data = (HelloWorld10*)sample;
	(void)data;
}
void HelloWorld11_cb(void *sample)
{
	HelloWorld11 *data = (HelloWorld11*)sample;
	(void)data;
}
void HelloWorld12_cb(void *sample)
{
	HelloWorld12 *data = (HelloWorld12*)sample;
	(void)data;
}
void HelloWorld13_cb(void *sample)
{
	HelloWorld13 *data = (HelloWorld13*)sample;
	(void)data;
}
void HelloWorld14_cb(void *sample)
{
	HelloWorld14 *data = (HelloWorld14*)sample;
	(void)data;
}
void HelloWorld15_cb(void *sample)
{
	HelloWorld15 *data = (HelloWorld15*)sample;
	(void)data;
}
void HelloWorld16_cb(void *sample)
{
	HelloWorld16 *data = (HelloWorld16*)sample;
	(void)data;
}
void HelloWorld17_cb(void *sample)
{
	HelloWorld17 *data = (HelloWorld17*)sample;
	(void)data;
}
void HelloWorld18_cb(void *sample)
{
	HelloWorld18 *data = (HelloWorld18*)sample;
	(void)data;
}
void HelloWorld19_cb(void *sample)
{
	HelloWorld19 *data = (HelloWorld19*)sample;
	(void)data;
}
void HelloWorld20_cb(void *sample)
{
	HelloWorld20 *data = (HelloWorld20*)sample;
	(void)data;
}
void HelloWorld21_cb(void *sample)
{
	HelloWorld21 *data = (HelloWorld21*)sample;
	(void)data;
}
void HelloWorld22_cb(void *sample)
{
	HelloWorld22 *data = (HelloWorld22*)sample;
	(void)data;
}
void HelloWorld23_cb(void *sample)
{
	HelloWorld23 *data = (HelloWorld23*)sample;
	(void)data;
}
void HelloWorld24_cb(void *sample)
{
	HelloWorld24 *data = (HelloWorld24*)sample;
	(void)data;
}
void HelloWorld25_cb(void *sample)
{
	HelloWorld25 *data = (HelloWorld25*)sample;
	(void)data;
}
void HelloWorld26_cb(void *sample)
{
	HelloWorld26 *data = (HelloWorld26*)sample;
	(void)data;
}
void HelloWorld27_cb(void *sample)
{
	HelloWorld27 *data = (HelloWorld27*)sample;
	(void)data;
}
void HelloWorld28_cb(void *sample)
{
	HelloWorld28 *data = (HelloWorld28*)sample;
	(void)data;
}
void HelloWorld29_cb(void *sample)
{
	HelloWorld29 *data = (HelloWorld29*)sample;
	(void)data;
}
void HelloWorld30_cb(void *sample)
{
	HelloWorld30 *data = (HelloWorld30*)sample;
	(void)data;
}
void HelloWorld31_cb(void *sample)
{
	HelloWorld31 *data = (HelloWorld31*)sample;
	(void)data;
}
void HelloWorld32_cb(void *sample)
{
	HelloWorld32 *data = (HelloWorld32*)sample;
	(void)data;
}
void HelloWorld33_cb(void *sample)
{
	HelloWorld33 *data = (HelloWorld33*)sample;
	(void)data;
}
void HelloWorld34_cb(void *sample)
{
	HelloWorld34 *data = (HelloWorld34*)sample;
	(void)data;
}
void HelloWorld35_cb(void *sample)
{
	HelloWorld35 *data = (HelloWorld35*)sample;
	(void)data;
}
void HelloWorld36_cb(void *sample)
{
	HelloWorld36 *data = (HelloWorld36*)sample;
	(void)data;
}
void HelloWorld37_cb(void *sample)
{
	HelloWorld37 *data = (HelloWorld37*)sample;
	(void)data;
}
void HelloWorld38_cb(void *sample)
{
	HelloWorld38 *data = (HelloWorld38*)sample;
	(void)data;
}
void HelloWorld39_cb(void *sample)
{
	HelloWorld39 *data = (HelloWorld39*)sample;
	(void)data;
}
void HelloWorld40_cb(void *sample)
{
	HelloWorld40 *data = (HelloWorld40*)sample;
	(void)data;
}
void HelloWorld41_cb(void *sample)
{
	HelloWorld41 *data = (HelloWorld41*)sample;
	(void)data;
}
void HelloWorld42_cb(void *sample)
{
	HelloWorld42 *data = (HelloWorld42*)sample;
	(void)data;
}
void HelloWorld43_cb(void *sample)
{
	HelloWorld43 *data = (HelloWorld43*)sample;
	(void)data;
}
void HelloWorld44_cb(void *sample)
{
	HelloWorld44 *data = (HelloWorld44*)sample;
	(void)data;
}
void HelloWorld45_cb(void *sample)
{
	HelloWorld45 *data = (HelloWorld45*)sample;
	(void)data;
}
void HelloWorld46_cb(void *sample)
{
	HelloWorld46 *data = (HelloWorld46*)sample;
	(void)data;
}
void HelloWorld47_cb(void *sample)
{
	HelloWorld47 *data = (HelloWorld47*)sample;
	(void)data;
}
void HelloWorld48_cb(void *sample)
{
	HelloWorld48 *data = (HelloWorld48*)sample;
	(void)data;
}
void HelloWorld49_cb(void *sample)
{
	HelloWorld49 *data = (HelloWorld49*)sample;
	(void)data;
}
void HelloWorld50_cb(void *sample)
{
	HelloWorld50 *data = (HelloWorld50*)sample;
	(void)data;
}
void HelloWorld51_cb(void *sample)
{
	HelloWorld51 *data = (HelloWorld51*)sample;
	(void)data;
}
void HelloWorld52_cb(void *sample)
{
	HelloWorld52 *data = (HelloWorld52*)sample;
	(void)data;
}
void HelloWorld53_cb(void *sample)
{
	HelloWorld53 *data = (HelloWorld53*)sample;
	(void)data;
}
void HelloWorld54_cb(void *sample)
{
	HelloWorld54 *data = (HelloWorld54*)sample;
	(void)data;
}
void HelloWorld55_cb(void *sample)
{
	HelloWorld55 *data = (HelloWorld55*)sample;
	(void)data;
}
void HelloWorld56_cb(void *sample)
{
	HelloWorld56 *data = (HelloWorld56*)sample;
	(void)data;
}
void HelloWorld57_cb(void *sample)
{
	HelloWorld57 *data = (HelloWorld57*)sample;
	(void)data;
}
void HelloWorld58_cb(void *sample)
{
	HelloWorld58 *data = (HelloWorld58*)sample;
	(void)data;
}
void HelloWorld59_cb(void *sample)
{
	HelloWorld59 *data = (HelloWorld59*)sample;
	(void)data;
}
void HelloWorld60_cb(void *sample)
{
	HelloWorld60 *data = (HelloWorld60*)sample;
	(void)data;
}
void HelloWorld61_cb(void *sample)
{
	HelloWorld61 *data = (HelloWorld61*)sample;
	(void)data;
}
void HelloWorld62_cb(void *sample)
{
	HelloWorld62 *data = (HelloWorld62*)sample;
	(void)data;
}
void HelloWorld63_cb(void *sample)
{
	HelloWorld63 *data = (HelloWorld63*)sample;
	(void)data;
}
void HelloWorld64_cb(void *sample)
{
	HelloWorld64 *data = (HelloWorld64*)sample;
	(void)data;
}
void HelloWorld65_cb(void *sample)
{
	HelloWorld65 *data = (HelloWorld65*)sample;
	(void)data;
}
void HelloWorld66_cb(void *sample)
{
	HelloWorld66 *data = (HelloWorld66*)sample;
	(void)data;
}
void HelloWorld67_cb(void *sample)
{
	HelloWorld67 *data = (HelloWorld67*)sample;
	(void)data;
}
void HelloWorld68_cb(void *sample)
{
	HelloWorld68 *data = (HelloWorld68*)sample;
	(void)data;
}
void HelloWorld69_cb(void *sample)
{
	HelloWorld69 *data = (HelloWorld69*)sample;
	(void)data;
}
void HelloWorld70_cb(void *sample)
{
	HelloWorld70 *data = (HelloWorld70*)sample;
	(void)data;
}
void HelloWorld71_cb(void *sample)
{
	HelloWorld71 *data = (HelloWorld71*)sample;
	(void)data;
}
void HelloWorld72_cb(void *sample)
{
	HelloWorld72 *data = (HelloWorld72*)sample;
	(void)data;
}
void HelloWorld73_cb(void *sample)
{
	HelloWorld73 *data = (HelloWorld73*)sample;
	(void)data;
}
void HelloWorld74_cb(void *sample)
{
	HelloWorld74 *data = (HelloWorld74*)sample;
	(void)data;
}
void HelloWorld75_cb(void *sample)
{
	HelloWorld75 *data = (HelloWorld75*)sample;
	(void)data;
}
void HelloWorld76_cb(void *sample)
{
	HelloWorld76 *data = (HelloWorld76*)sample;
	(void)data;
}
void HelloWorld77_cb(void *sample)
{
	HelloWorld77 *data = (HelloWorld77*)sample;
	(void)data;
}
void HelloWorld78_cb(void *sample)
{
	HelloWorld78 *data = (HelloWorld78*)sample;
	(void)data;
}
void HelloWorld79_cb(void *sample)
{
	HelloWorld79 *data = (HelloWorld79*)sample;
	(void)data;
}
void HelloWorld80_cb(void *sample)
{
	HelloWorld80 *data = (HelloWorld80*)sample;
	(void)data;
}
void HelloWorld81_cb(void *sample)
{
	HelloWorld81 *data = (HelloWorld81*)sample;
	(void)data;
}
void HelloWorld82_cb(void *sample)
{
	HelloWorld82 *data = (HelloWorld82*)sample;
	(void)data;
}
void HelloWorld83_cb(void *sample)
{
	HelloWorld83 *data = (HelloWorld83*)sample;
	(void)data;
}
void HelloWorld84_cb(void *sample)
{
	HelloWorld84 *data = (HelloWorld84*)sample;
	(void)data;
}
void HelloWorld85_cb(void *sample)
{
	HelloWorld85 *data = (HelloWorld85*)sample;
	(void)data;
}
void HelloWorld86_cb(void *sample)
{
	HelloWorld86 *data = (HelloWorld86*)sample;
	(void)data;
}
void HelloWorld87_cb(void *sample)
{
	HelloWorld87 *data = (HelloWorld87*)sample;
	(void)data;
}
void HelloWorld88_cb(void *sample)
{
	HelloWorld88 *data = (HelloWorld88*)sample;
	(void)data;
}
void HelloWorld89_cb(void *sample)
{
	HelloWorld89 *data = (HelloWorld89*)sample;
	(void)data;
}
void HelloWorld90_cb(void *sample)
{
	HelloWorld90 *data = (HelloWorld90*)sample;
	(void)data;
}
void HelloWorld91_cb(void *sample)
{
	HelloWorld91 *data = (HelloWorld91*)sample;
	(void)data;
}
void HelloWorld92_cb(void *sample)
{
	HelloWorld92 *data = (HelloWorld92*)sample;
	(void)data;
}
void HelloWorld93_cb(void *sample)
{
	HelloWorld93 *data = (HelloWorld93*)sample;
	(void)data;
}
void HelloWorld94_cb(void *sample)
{
	HelloWorld94 *data = (HelloWorld94*)sample;
	(void)data;
}
void HelloWorld95_cb(void *sample)
{
	HelloWorld95 *data = (HelloWorld95*)sample;
	(void)data;
}
void HelloWorld96_cb(void *sample)
{
	HelloWorld96 *data = (HelloWorld96*)sample;
	(void)data;
}
void HelloWorld97_cb(void *sample)
{
	HelloWorld97 *data = (HelloWorld97*)sample;
	(void)data;
}
void HelloWorld98_cb(void *sample)
{
	HelloWorld98 *data = (HelloWorld98*)sample;
	(void)data;
}
void HelloWorld99_cb(void *sample)
{
	HelloWorld99 *data = (HelloWorld99*)sample;
	(void)data;
}
void HelloWorld100_cb(void *sample)
{
	HelloWorld100 *data = (HelloWorld100*)sample;
	(void)data;
}
void HelloWorld101_cb(void *sample)
{
	HelloWorld101 *data = (HelloWorld101*)sample;
	(void)data;
}
void HelloWorld102_cb(void *sample)
{
	HelloWorld102 *data = (HelloWorld102*)sample;
	(void)data;
}
void HelloWorld103_cb(void *sample)
{
	HelloWorld103 *data = (HelloWorld103*)sample;
	(void)data;
}
void HelloWorld104_cb(void *sample)
{
	HelloWorld104 *data = (HelloWorld104*)sample;
	(void)data;
}
void HelloWorld105_cb(void *sample)
{
	HelloWorld105 *data = (HelloWorld105*)sample;
	(void)data;
}
void HelloWorld106_cb(void *sample)
{
	HelloWorld106 *data = (HelloWorld106*)sample;
	(void)data;
}
void HelloWorld107_cb(void *sample)
{
	HelloWorld107 *data = (HelloWorld107*)sample;
	(void)data;
}
void HelloWorld108_cb(void *sample)
{
	HelloWorld108 *data = (HelloWorld108*)sample;
	(void)data;
}
void HelloWorld109_cb(void *sample)
{
	HelloWorld109 *data = (HelloWorld109*)sample;
	(void)data;
}
void HelloWorld110_cb(void *sample)
{
	HelloWorld110 *data = (HelloWorld110*)sample;
	(void)data;
}
void HelloWorld111_cb(void *sample)
{
	HelloWorld111 *data = (HelloWorld111*)sample;
	(void)data;
}
void HelloWorld112_cb(void *sample)
{
	HelloWorld112 *data = (HelloWorld112*)sample;
	(void)data;
}
void HelloWorld113_cb(void *sample)
{
	HelloWorld113 *data = (HelloWorld113*)sample;
	(void)data;
}
void HelloWorld114_cb(void *sample)
{
	HelloWorld114 *data = (HelloWorld114*)sample;
	(void)data;
}
void HelloWorld115_cb(void *sample)
{
	HelloWorld115 *data = (HelloWorld115*)sample;
	(void)data;
}
void HelloWorld116_cb(void *sample)
{
	HelloWorld116 *data = (HelloWorld116*)sample;
	(void)data;
}
void HelloWorld117_cb(void *sample)
{
	HelloWorld117 *data = (HelloWorld117*)sample;
	(void)data;
}
void HelloWorld118_cb(void *sample)
{
	HelloWorld118 *data = (HelloWorld118*)sample;
	(void)data;
}
void HelloWorld119_cb(void *sample)
{
	HelloWorld119 *data = (HelloWorld119*)sample;
	(void)data;
}
void HelloWorld120_cb(void *sample)
{
	HelloWorld120 *data = (HelloWorld120*)sample;
	(void)data;
}
void HelloWorld121_cb(void *sample)
{
	HelloWorld121 *data = (HelloWorld121*)sample;
	(void)data;
}
void HelloWorld122_cb(void *sample)
{
	HelloWorld122 *data = (HelloWorld122*)sample;
	(void)data;
}
void HelloWorld123_cb(void *sample)
{
	HelloWorld123 *data = (HelloWorld123*)sample;
	(void)data;
}
void HelloWorld124_cb(void *sample)
{
	HelloWorld124 *data = (HelloWorld124*)sample;
	(void)data;
}
void HelloWorld125_cb(void *sample)
{
	HelloWorld125 *data = (HelloWorld125*)sample;
	(void)data;
}
void HelloWorld126_cb(void *sample)
{
	HelloWorld126 *data = (HelloWorld126*)sample;
	(void)data;
}
void HelloWorld127_cb(void *sample)
{
	HelloWorld127 *data = (HelloWorld127*)sample;
	(void)data;
}
void HelloWorld128_cb(void *sample)
{
	HelloWorld128 *data = (HelloWorld128*)sample;
	(void)data;
}
void HelloWorld129_cb(void *sample)
{
	HelloWorld129 *data = (HelloWorld129*)sample;
	(void)data;
}
void HelloWorld130_cb(void *sample)
{
	HelloWorld130 *data = (HelloWorld130*)sample;
	(void)data;
}
void HelloWorld131_cb(void *sample)
{
	HelloWorld131 *data = (HelloWorld131*)sample;
	(void)data;
}
void HelloWorld132_cb(void *sample)
{
	HelloWorld132 *data = (HelloWorld132*)sample;
	(void)data;
}
void HelloWorld133_cb(void *sample)
{
	HelloWorld133 *data = (HelloWorld133*)sample;
	(void)data;
}
void HelloWorld134_cb(void *sample)
{
	HelloWorld134 *data = (HelloWorld134*)sample;
	(void)data;
}
void HelloWorld135_cb(void *sample)
{
	HelloWorld135 *data = (HelloWorld135*)sample;
	(void)data;
}
void HelloWorld136_cb(void *sample)
{
	HelloWorld136 *data = (HelloWorld136*)sample;
	(void)data;
}
void HelloWorld137_cb(void *sample)
{
	HelloWorld137 *data = (HelloWorld137*)sample;
	(void)data;
}
void HelloWorld138_cb(void *sample)
{
	HelloWorld138 *data = (HelloWorld138*)sample;
	(void)data;
}
void HelloWorld139_cb(void *sample)
{
	HelloWorld139 *data = (HelloWorld139*)sample;
	(void)data;
}
void HelloWorld140_cb(void *sample)
{
	HelloWorld140 *data = (HelloWorld140*)sample;
	(void)data;
}
void HelloWorld141_cb(void *sample)
{
	HelloWorld141 *data = (HelloWorld141*)sample;
	(void)data;
}
void HelloWorld142_cb(void *sample)
{
	HelloWorld142 *data = (HelloWorld142*)sample;
	(void)data;
}
void HelloWorld143_cb(void *sample)
{
	HelloWorld143 *data = (HelloWorld143*)sample;
	(void)data;
}
void HelloWorld144_cb(void *sample)
{
	HelloWorld144 *data = (HelloWorld144*)sample;
	(void)data;
}
void HelloWorld145_cb(void *sample)
{
	HelloWorld145 *data = (HelloWorld145*)sample;
	(void)data;
}
void HelloWorld146_cb(void *sample)
{
	HelloWorld146 *data = (HelloWorld146*)sample;
	(void)data;
}
void HelloWorld147_cb(void *sample)
{
	HelloWorld147 *data = (HelloWorld147*)sample;
	(void)data;
}
void HelloWorld148_cb(void *sample)
{
	HelloWorld148 *data = (HelloWorld148*)sample;
	(void)data;
}
void HelloWorld149_cb(void *sample)
{
	HelloWorld149 *data = (HelloWorld149*)sample;
	(void)data;
}

#define READER_META_INFO(name, type, cb, period)		\
	[reader_topic_index(name)] = {				\
		.topic		= #name,			\
		.sample		= (type [1]) {},		\
		.period_ms	= period,			\
		.match_count	= 0,				\
		.recv_count	= 0,				\
		.fail_count	= 0,				\
		.init		= (sample_init_t)(type##_init),	\
		.fn		= cb,				\
	}

static struct reader_meta_info subscriber_list[] = {
    	READER_META_INFO(HelloWorld1, HelloWorld1, HelloWorld1_cb, 100),
    	READER_META_INFO(HelloWorld2, HelloWorld2, HelloWorld2_cb, 100),
    	READER_META_INFO(HelloWorld3, HelloWorld3, HelloWorld3_cb, 100),
    	READER_META_INFO(HelloWorld4, HelloWorld4, HelloWorld4_cb, 100),
    	READER_META_INFO(HelloWorld5, HelloWorld5, HelloWorld5_cb, 100),
    	READER_META_INFO(HelloWorld6, HelloWorld6, HelloWorld6_cb, 100),
    	READER_META_INFO(HelloWorld7, HelloWorld7, HelloWorld7_cb, 100),
    	READER_META_INFO(HelloWorld8, HelloWorld8, HelloWorld8_cb, 100),
    	READER_META_INFO(HelloWorld9, HelloWorld9, HelloWorld9_cb, 100),
    	READER_META_INFO(HelloWorld10, HelloWorld10, HelloWorld10_cb, 100),
    	READER_META_INFO(HelloWorld11, HelloWorld11, HelloWorld11_cb, 100),
    	READER_META_INFO(HelloWorld12, HelloWorld12, HelloWorld12_cb, 100),
    	READER_META_INFO(HelloWorld13, HelloWorld13, HelloWorld13_cb, 100),
    	READER_META_INFO(HelloWorld14, HelloWorld14, HelloWorld14_cb, 100),
    	READER_META_INFO(HelloWorld15, HelloWorld15, HelloWorld15_cb, 100),
    	READER_META_INFO(HelloWorld16, HelloWorld16, HelloWorld16_cb, 100),
    	READER_META_INFO(HelloWorld17, HelloWorld17, HelloWorld17_cb, 100),
    	READER_META_INFO(HelloWorld18, HelloWorld18, HelloWorld18_cb, 100),
    	READER_META_INFO(HelloWorld19, HelloWorld19, HelloWorld19_cb, 100),
    	READER_META_INFO(HelloWorld20, HelloWorld20, HelloWorld20_cb, 100),
    	READER_META_INFO(HelloWorld21, HelloWorld21, HelloWorld21_cb, 100),
    	READER_META_INFO(HelloWorld22, HelloWorld22, HelloWorld22_cb, 100),
    	READER_META_INFO(HelloWorld23, HelloWorld23, HelloWorld23_cb, 100),
    	READER_META_INFO(HelloWorld24, HelloWorld24, HelloWorld24_cb, 100),
    	READER_META_INFO(HelloWorld25, HelloWorld25, HelloWorld25_cb, 100),
    	READER_META_INFO(HelloWorld26, HelloWorld26, HelloWorld26_cb, 100),
    	READER_META_INFO(HelloWorld27, HelloWorld27, HelloWorld27_cb, 100),
    	READER_META_INFO(HelloWorld28, HelloWorld28, HelloWorld28_cb, 100),
    	READER_META_INFO(HelloWorld29, HelloWorld29, HelloWorld29_cb, 100),
    	READER_META_INFO(HelloWorld30, HelloWorld30, HelloWorld30_cb, 100),
    	READER_META_INFO(HelloWorld31, HelloWorld31, HelloWorld31_cb, 100),
    	READER_META_INFO(HelloWorld32, HelloWorld32, HelloWorld32_cb, 100),
    	READER_META_INFO(HelloWorld33, HelloWorld33, HelloWorld33_cb, 100),
    	READER_META_INFO(HelloWorld34, HelloWorld34, HelloWorld34_cb, 100),
    	READER_META_INFO(HelloWorld35, HelloWorld35, HelloWorld35_cb, 100),
    	READER_META_INFO(HelloWorld36, HelloWorld36, HelloWorld36_cb, 100),
    	READER_META_INFO(HelloWorld37, HelloWorld37, HelloWorld37_cb, 100),
    	READER_META_INFO(HelloWorld38, HelloWorld38, HelloWorld38_cb, 100),
    	READER_META_INFO(HelloWorld39, HelloWorld39, HelloWorld39_cb, 100),
    	READER_META_INFO(HelloWorld40, HelloWorld40, HelloWorld40_cb, 100),
    	READER_META_INFO(HelloWorld41, HelloWorld41, HelloWorld41_cb, 100),
    	READER_META_INFO(HelloWorld42, HelloWorld42, HelloWorld42_cb, 100),
    	READER_META_INFO(HelloWorld43, HelloWorld43, HelloWorld43_cb, 100),
    	READER_META_INFO(HelloWorld44, HelloWorld44, HelloWorld44_cb, 100),
    	READER_META_INFO(HelloWorld45, HelloWorld45, HelloWorld45_cb, 100),
    	READER_META_INFO(HelloWorld46, HelloWorld46, HelloWorld46_cb, 100),
    	READER_META_INFO(HelloWorld47, HelloWorld47, HelloWorld47_cb, 100),
    	READER_META_INFO(HelloWorld48, HelloWorld48, HelloWorld48_cb, 100),
    	READER_META_INFO(HelloWorld49, HelloWorld49, HelloWorld49_cb, 100),
    	READER_META_INFO(HelloWorld50, HelloWorld50, HelloWorld50_cb, 100),
    	READER_META_INFO(HelloWorld51, HelloWorld51, HelloWorld51_cb, 100),
    	READER_META_INFO(HelloWorld52, HelloWorld52, HelloWorld52_cb, 100),
    	READER_META_INFO(HelloWorld53, HelloWorld53, HelloWorld53_cb, 100),
    	READER_META_INFO(HelloWorld54, HelloWorld54, HelloWorld54_cb, 100),
    	READER_META_INFO(HelloWorld55, HelloWorld55, HelloWorld55_cb, 100),
    	READER_META_INFO(HelloWorld56, HelloWorld56, HelloWorld56_cb, 100),
    	READER_META_INFO(HelloWorld57, HelloWorld57, HelloWorld57_cb, 100),
    	READER_META_INFO(HelloWorld58, HelloWorld58, HelloWorld58_cb, 100),
    	READER_META_INFO(HelloWorld59, HelloWorld59, HelloWorld59_cb, 100),
    	READER_META_INFO(HelloWorld60, HelloWorld60, HelloWorld60_cb, 100),
    	READER_META_INFO(HelloWorld61, HelloWorld61, HelloWorld61_cb, 100),
    	READER_META_INFO(HelloWorld62, HelloWorld62, HelloWorld62_cb, 100),
    	READER_META_INFO(HelloWorld63, HelloWorld63, HelloWorld63_cb, 100),
    	READER_META_INFO(HelloWorld64, HelloWorld64, HelloWorld64_cb, 100),
    	READER_META_INFO(HelloWorld65, HelloWorld65, HelloWorld65_cb, 100),
    	READER_META_INFO(HelloWorld66, HelloWorld66, HelloWorld66_cb, 100),
    	READER_META_INFO(HelloWorld67, HelloWorld67, HelloWorld67_cb, 100),
    	READER_META_INFO(HelloWorld68, HelloWorld68, HelloWorld68_cb, 100),
    	READER_META_INFO(HelloWorld69, HelloWorld69, HelloWorld69_cb, 100),
    	READER_META_INFO(HelloWorld70, HelloWorld70, HelloWorld70_cb, 100),
    	READER_META_INFO(HelloWorld71, HelloWorld71, HelloWorld71_cb, 100),
    	READER_META_INFO(HelloWorld72, HelloWorld72, HelloWorld72_cb, 100),
    	READER_META_INFO(HelloWorld73, HelloWorld73, HelloWorld73_cb, 100),
    	READER_META_INFO(HelloWorld74, HelloWorld74, HelloWorld74_cb, 100),
    	READER_META_INFO(HelloWorld75, HelloWorld75, HelloWorld75_cb, 100),
    	READER_META_INFO(HelloWorld76, HelloWorld76, HelloWorld76_cb, 100),
    	READER_META_INFO(HelloWorld77, HelloWorld77, HelloWorld77_cb, 100),
    	READER_META_INFO(HelloWorld78, HelloWorld78, HelloWorld78_cb, 100),
    	READER_META_INFO(HelloWorld79, HelloWorld79, HelloWorld79_cb, 100),
    	READER_META_INFO(HelloWorld80, HelloWorld80, HelloWorld80_cb, 100),
    	READER_META_INFO(HelloWorld81, HelloWorld81, HelloWorld81_cb, 100),
    	READER_META_INFO(HelloWorld82, HelloWorld82, HelloWorld82_cb, 100),
    	READER_META_INFO(HelloWorld83, HelloWorld83, HelloWorld83_cb, 100),
    	READER_META_INFO(HelloWorld84, HelloWorld84, HelloWorld84_cb, 100),
    	READER_META_INFO(HelloWorld85, HelloWorld85, HelloWorld85_cb, 100),
    	READER_META_INFO(HelloWorld86, HelloWorld86, HelloWorld86_cb, 100),
    	READER_META_INFO(HelloWorld87, HelloWorld87, HelloWorld87_cb, 100),
    	READER_META_INFO(HelloWorld88, HelloWorld88, HelloWorld88_cb, 100),
    	READER_META_INFO(HelloWorld89, HelloWorld89, HelloWorld89_cb, 100),
    	READER_META_INFO(HelloWorld90, HelloWorld90, HelloWorld90_cb, 100),
    	READER_META_INFO(HelloWorld91, HelloWorld91, HelloWorld91_cb, 100),
    	READER_META_INFO(HelloWorld92, HelloWorld92, HelloWorld92_cb, 100),
    	READER_META_INFO(HelloWorld93, HelloWorld93, HelloWorld93_cb, 100),
    	READER_META_INFO(HelloWorld94, HelloWorld94, HelloWorld94_cb, 100),
    	READER_META_INFO(HelloWorld95, HelloWorld95, HelloWorld95_cb, 100),
    	READER_META_INFO(HelloWorld96, HelloWorld96, HelloWorld96_cb, 100),
    	READER_META_INFO(HelloWorld97, HelloWorld97, HelloWorld97_cb, 100),
    	READER_META_INFO(HelloWorld98, HelloWorld98, HelloWorld98_cb, 100),
    	READER_META_INFO(HelloWorld99, HelloWorld99, HelloWorld99_cb, 100),
    	READER_META_INFO(HelloWorld100, HelloWorld100, HelloWorld100_cb, 100),
    	READER_META_INFO(HelloWorld101, HelloWorld101, HelloWorld101_cb, 100),
    	READER_META_INFO(HelloWorld102, HelloWorld102, HelloWorld102_cb, 100),
    	READER_META_INFO(HelloWorld103, HelloWorld103, HelloWorld103_cb, 100),
    	READER_META_INFO(HelloWorld104, HelloWorld104, HelloWorld104_cb, 100),
    	READER_META_INFO(HelloWorld105, HelloWorld105, HelloWorld105_cb, 100),
    	READER_META_INFO(HelloWorld106, HelloWorld106, HelloWorld106_cb, 100),
    	READER_META_INFO(HelloWorld107, HelloWorld107, HelloWorld107_cb, 100),
    	READER_META_INFO(HelloWorld108, HelloWorld108, HelloWorld108_cb, 100),
    	READER_META_INFO(HelloWorld109, HelloWorld109, HelloWorld109_cb, 100),
    	READER_META_INFO(HelloWorld110, HelloWorld110, HelloWorld110_cb, 100),
    	READER_META_INFO(HelloWorld111, HelloWorld111, HelloWorld111_cb, 100),
    	READER_META_INFO(HelloWorld112, HelloWorld112, HelloWorld112_cb, 100),
    	READER_META_INFO(HelloWorld113, HelloWorld113, HelloWorld113_cb, 100),
    	READER_META_INFO(HelloWorld114, HelloWorld114, HelloWorld114_cb, 100),
    	READER_META_INFO(HelloWorld115, HelloWorld115, HelloWorld115_cb, 100),
    	READER_META_INFO(HelloWorld116, HelloWorld116, HelloWorld116_cb, 100),
    	READER_META_INFO(HelloWorld117, HelloWorld117, HelloWorld117_cb, 100),
    	READER_META_INFO(HelloWorld118, HelloWorld118, HelloWorld118_cb, 100),
    	READER_META_INFO(HelloWorld119, HelloWorld119, HelloWorld119_cb, 100),
    	READER_META_INFO(HelloWorld120, HelloWorld120, HelloWorld120_cb, 100),
    	READER_META_INFO(HelloWorld121, HelloWorld121, HelloWorld121_cb, 100),
    	READER_META_INFO(HelloWorld122, HelloWorld122, HelloWorld122_cb, 100),
    	READER_META_INFO(HelloWorld123, HelloWorld123, HelloWorld123_cb, 100),
    	READER_META_INFO(HelloWorld124, HelloWorld124, HelloWorld124_cb, 100),
    	READER_META_INFO(HelloWorld125, HelloWorld125, HelloWorld125_cb, 100),
    	READER_META_INFO(HelloWorld126, HelloWorld126, HelloWorld126_cb, 100),
    	READER_META_INFO(HelloWorld127, HelloWorld127, HelloWorld127_cb, 100),
    	READER_META_INFO(HelloWorld128, HelloWorld128, HelloWorld128_cb, 100),
    	READER_META_INFO(HelloWorld129, HelloWorld129, HelloWorld129_cb, 100),
    	READER_META_INFO(HelloWorld130, HelloWorld130, HelloWorld130_cb, 100),
    	READER_META_INFO(HelloWorld131, HelloWorld131, HelloWorld131_cb, 100),
    	READER_META_INFO(HelloWorld132, HelloWorld132, HelloWorld132_cb, 100),
    	READER_META_INFO(HelloWorld133, HelloWorld133, HelloWorld133_cb, 100),
    	READER_META_INFO(HelloWorld134, HelloWorld134, HelloWorld134_cb, 100),
    	READER_META_INFO(HelloWorld135, HelloWorld135, HelloWorld135_cb, 100),
    	READER_META_INFO(HelloWorld136, HelloWorld136, HelloWorld136_cb, 100),
    	READER_META_INFO(HelloWorld137, HelloWorld137, HelloWorld137_cb, 100),
    	READER_META_INFO(HelloWorld138, HelloWorld138, HelloWorld138_cb, 100),
    	READER_META_INFO(HelloWorld139, HelloWorld139, HelloWorld139_cb, 100),
    	READER_META_INFO(HelloWorld140, HelloWorld140, HelloWorld140_cb, 100),
    	READER_META_INFO(HelloWorld141, HelloWorld141, HelloWorld141_cb, 100),
    	READER_META_INFO(HelloWorld142, HelloWorld142, HelloWorld142_cb, 100),
    	READER_META_INFO(HelloWorld143, HelloWorld143, HelloWorld143_cb, 100),
    	READER_META_INFO(HelloWorld144, HelloWorld144, HelloWorld144_cb, 100),
    	READER_META_INFO(HelloWorld145, HelloWorld145, HelloWorld145_cb, 100),
    	READER_META_INFO(HelloWorld146, HelloWorld146, HelloWorld146_cb, 100),
    	READER_META_INFO(HelloWorld147, HelloWorld147, HelloWorld147_cb, 100),
    	READER_META_INFO(HelloWorld148, HelloWorld148, HelloWorld148_cb, 100),
    	READER_META_INFO(HelloWorld149, HelloWorld149, HelloWorld149_cb, 100),
};

static void subscriber_init(Rte_Dds_Participant ptcp)
{
	struct reader_meta_info *info;

	for (uint8_t i = 0; i < ARRAY_SIZE(subscriber_list); i++) {
		info = &subscriber_list[i];

		info->r = Rte_Dds_GetReader(ptcp, info->topic);
		info->init(info->sample);

		info->recv_count	= 0;
		info->fail_count	= 0;

		if (info->period_ms != 0) {
			info->print_per_cnt = 100000 / info->period_ms;	/* print per 1s */
		} else {
			info->print_per_cnt = 10;
		}

		Rte_Dds_Reader_Set_Private(info->r, info);
	}
}

void Rte_Dds_RxIndication(Rte_Dds_Reader r, Rte_Dds_Instance inst)
{
	(void)inst;

	struct reader_meta_info 	*info;
	Rte_Dds_TopicData        	data;
	static struct sample_info 	Sample_info;
	const char * topic_name;

	topic_name = reader_get_topicname(r);
	if (!strcmp(topic_name,"domain_0_topic_0Topic")) {
		// pr_info("topic_name: %s",topic_name);
		time_event(r);
		return;
	}

	info = Rte_Dds_Reader_Get_Private(r);

	Rte_Dds_PackData(&data, info->sample);

	if (RTE_DDS_RETCODE_OK == Rte_Dds_RxData(r, true, &data, &Sample_info)) {
		info->recv_count++;

		if (info->fn != NULL) {
			info->fn(info->sample);
		}

		if ((info->recv_count % info->print_per_cnt) == 0) {
			pr_info(" Get a sample from: [%s], sample count: %ld," "transport_type:%d",
						info->topic, info->recv_count,Sample_info.locator_kind);
		}
	} else {
		info->fail_count++;

		pr_info("Failed to read sample from [%s], fail count:%ld",
						info->topic, info->recv_count);
	}
}

void Rte_Dds_Reader_OnMatch(Rte_Dds_Reader r,
			    const Rte_Dds_Reader_MatchStatus *status)
{
	(void)status;

	struct reader_meta_info *info;

	for (uint8_t i = 0; i < ARRAY_SIZE(subscriber_list); i++) {
		info = &subscriber_list[i];


		if (!mvbs_strcmp(info->topic, reader_get_topicname(r))) {
			info->match_count++;
			pr_warn("topic:%s, match_count:%d",info->topic, info->match_count);
		}
	}
}

static bool get_all_reader_match_status(void)
{
	struct reader_meta_info *info;

	for (uint8_t i = 0; i < ARRAY_SIZE(subscriber_list); i++) {
		info = &subscriber_list[i];

		if (info->match_count == 0) {
			return false;
		}
	}

	return true;
}
/* The following code lines are for writer topic. */

enum {
	writer_topic_index(HelloWorld151),
	writer_topic_index(HelloWorld152),
	writer_topic_index(HelloWorld153),
	writer_topic_index(HelloWorld154),
	writer_topic_index(HelloWorld155),
	writer_topic_index(HelloWorld156),
	writer_topic_index(HelloWorld157),
	writer_topic_index(HelloWorld158),
	writer_topic_index(HelloWorld159),
	writer_topic_index(HelloWorld160),
	writer_topic_index(HelloWorld161),
	writer_topic_index(HelloWorld162),
	writer_topic_index(HelloWorld163),
	writer_topic_index(HelloWorld164),
	writer_topic_index(HelloWorld165),
	writer_topic_index(HelloWorld166),
	writer_topic_index(HelloWorld167),
	writer_topic_index(HelloWorld168),
	writer_topic_index(HelloWorld169),
	writer_topic_index(HelloWorld170),
	writer_topic_index(HelloWorld171),
	writer_topic_index(HelloWorld172),
	writer_topic_index(HelloWorld173),
	writer_topic_index(HelloWorld174),
	writer_topic_index(HelloWorld175),
	writer_topic_index(HelloWorld176),
	writer_topic_index(HelloWorld177),
	writer_topic_index(HelloWorld178),
	writer_topic_index(HelloWorld179),
	writer_topic_index(HelloWorld180),
	writer_topic_index(HelloWorld181),
	writer_topic_index(HelloWorld182),
	writer_topic_index(HelloWorld183),
	writer_topic_index(HelloWorld184),
	writer_topic_index(HelloWorld185),
	writer_topic_index(HelloWorld186),
	writer_topic_index(HelloWorld187),
	writer_topic_index(HelloWorld188),
	writer_topic_index(HelloWorld189),
	writer_topic_index(HelloWorld190),
	writer_topic_index(HelloWorld191),
	writer_topic_index(HelloWorld192),
	writer_topic_index(HelloWorld193),
	writer_topic_index(HelloWorld194),
	writer_topic_index(HelloWorld195),
	writer_topic_index(HelloWorld196),
	writer_topic_index(HelloWorld197),
	writer_topic_index(HelloWorld198),
	writer_topic_index(HelloWorld199),
	writer_topic_index(HelloWorld200),
	writer_topic_index(HelloWorld201),
	writer_topic_index(HelloWorld202),
	writer_topic_index(HelloWorld203),
	writer_topic_index(HelloWorld204),
	writer_topic_index(HelloWorld205),
	writer_topic_index(HelloWorld206),
	writer_topic_index(HelloWorld207),
	writer_topic_index(HelloWorld208),
	writer_topic_index(HelloWorld209),
	writer_topic_index(HelloWorld210),
	writer_topic_index(HelloWorld211),
	writer_topic_index(HelloWorld212),
	writer_topic_index(HelloWorld213),
	writer_topic_index(HelloWorld214),
	writer_topic_index(HelloWorld215),
	writer_topic_index(HelloWorld216),
	writer_topic_index(HelloWorld217),
	writer_topic_index(HelloWorld218),
	writer_topic_index(HelloWorld219),
	writer_topic_index(HelloWorld220),
	writer_topic_index(HelloWorld221),
	writer_topic_index(HelloWorld222),
	writer_topic_index(HelloWorld223),
	writer_topic_index(HelloWorld224),
	writer_topic_index(HelloWorld225),
	writer_topic_index(HelloWorld226),
	writer_topic_index(HelloWorld227),
	writer_topic_index(HelloWorld228),
	writer_topic_index(HelloWorld229),
	writer_topic_index(HelloWorld230),
	writer_topic_index(HelloWorld231),
	writer_topic_index(HelloWorld232),
	writer_topic_index(HelloWorld233),
	writer_topic_index(HelloWorld234),
	writer_topic_index(HelloWorld235),
	writer_topic_index(HelloWorld236),
	writer_topic_index(HelloWorld237),
	writer_topic_index(HelloWorld238),
	writer_topic_index(HelloWorld239),
	writer_topic_index(HelloWorld240),
	writer_topic_index(HelloWorld241),
	writer_topic_index(HelloWorld242),
	writer_topic_index(HelloWorld243),
	writer_topic_index(HelloWorld244),
	writer_topic_index(HelloWorld245),
	writer_topic_index(HelloWorld246),
	writer_topic_index(HelloWorld247),
	writer_topic_index(HelloWorld248),
	writer_topic_index(HelloWorld249),
	writer_topic_index(HelloWorld250),
	writer_topic_index(HelloWorld251),
	writer_topic_index(HelloWorld252),
	writer_topic_index(HelloWorld253),
	writer_topic_index(HelloWorld254),
	writer_topic_index(HelloWorld255),
	writer_topic_index(HelloWorld256),
	writer_topic_index(HelloWorld257),
	writer_topic_index(HelloWorld258),
	writer_topic_index(HelloWorld259),
	writer_topic_index(HelloWorld260),
	writer_topic_index(HelloWorld261),
	writer_topic_index(HelloWorld262),
	writer_topic_index(HelloWorld263),
	writer_topic_index(HelloWorld264),
	writer_topic_index(HelloWorld265),
	writer_topic_index(HelloWorld266),
	writer_topic_index(HelloWorld267),
	writer_topic_index(HelloWorld268),
	writer_topic_index(HelloWorld269),
	writer_topic_index(HelloWorld270),
	writer_topic_index(HelloWorld271),
	writer_topic_index(HelloWorld272),
	writer_topic_index(HelloWorld273),
	writer_topic_index(HelloWorld274),
	writer_topic_index(HelloWorld275),
	writer_topic_index(HelloWorld276),
	writer_topic_index(HelloWorld277),
	writer_topic_index(HelloWorld278),
	writer_topic_index(HelloWorld279),
	writer_topic_index(HelloWorld280),
	writer_topic_index(HelloWorld281),
	writer_topic_index(HelloWorld282),
	writer_topic_index(HelloWorld283),
	writer_topic_index(HelloWorld284),
	writer_topic_index(HelloWorld285),
	writer_topic_index(HelloWorld286),
	writer_topic_index(HelloWorld287),
	writer_topic_index(HelloWorld288),
	writer_topic_index(HelloWorld289),
	writer_topic_index(HelloWorld290),
	writer_topic_index(HelloWorld291),
	writer_topic_index(HelloWorld292),
	writer_topic_index(HelloWorld293),
	writer_topic_index(HelloWorld294),
	writer_topic_index(HelloWorld295),
	writer_topic_index(HelloWorld296),
	writer_topic_index(HelloWorld297),
	writer_topic_index(HelloWorld298),
	writer_topic_index(HelloWorld299),
};

struct writer_meta_info {
	Rte_Dds_Writer	w;
	const char	*topic;
	uint8_t		match_count;
	void		*sample;

	unsigned long	period_next;	/* FIXME: Init value maybe shouldn't be zero. */
	uint32_t	period_ms;
	uint32_t	phase_ms;

	uint32_t	public_count;	/* Only for test */
	uint32_t	send_count;

	sample_init_t	init;
};

#define WRITER_META_INFO(name, type, period)			\
	[writer_topic_index(name)] = {				\
		.topic		= #name,			\
		.match_count	= 0,				\
		.sample		= (type [1]) {},		\
		.init		= (sample_init_t)(type##_init),	\
		.period_ms	= period,			\
		.period_next	= 0,				\
	}

static struct writer_meta_info publisher_list[] = {
	WRITER_META_INFO(HelloWorld151, HelloWorld151, 402),
	WRITER_META_INFO(HelloWorld152, HelloWorld152, 409),
	WRITER_META_INFO(HelloWorld153, HelloWorld153, 416),
	WRITER_META_INFO(HelloWorld154, HelloWorld154, 423),
	WRITER_META_INFO(HelloWorld155, HelloWorld155, 430),
	WRITER_META_INFO(HelloWorld156, HelloWorld156, 437),
	WRITER_META_INFO(HelloWorld157, HelloWorld157, 444),
	WRITER_META_INFO(HelloWorld158, HelloWorld158, 451),
	WRITER_META_INFO(HelloWorld159, HelloWorld159, 458),
	WRITER_META_INFO(HelloWorld160, HelloWorld160, 465),
	WRITER_META_INFO(HelloWorld161, HelloWorld161, 472),
	WRITER_META_INFO(HelloWorld162, HelloWorld162, 479),
	WRITER_META_INFO(HelloWorld163, HelloWorld163, 486),
	WRITER_META_INFO(HelloWorld164, HelloWorld164, 493),
	WRITER_META_INFO(HelloWorld165, HelloWorld165, 500),
	WRITER_META_INFO(HelloWorld166, HelloWorld166, 507),
	WRITER_META_INFO(HelloWorld167, HelloWorld167, 514),
	WRITER_META_INFO(HelloWorld168, HelloWorld168, 521),
	WRITER_META_INFO(HelloWorld169, HelloWorld169, 528),
	WRITER_META_INFO(HelloWorld170, HelloWorld170, 535),
	WRITER_META_INFO(HelloWorld171, HelloWorld171, 542),
	WRITER_META_INFO(HelloWorld172, HelloWorld172, 549),
	WRITER_META_INFO(HelloWorld173, HelloWorld173, 556),
	WRITER_META_INFO(HelloWorld174, HelloWorld174, 563),
	WRITER_META_INFO(HelloWorld175, HelloWorld175, 570),
	WRITER_META_INFO(HelloWorld176, HelloWorld176, 577),
	WRITER_META_INFO(HelloWorld177, HelloWorld177, 584),
	WRITER_META_INFO(HelloWorld178, HelloWorld178, 591),
	WRITER_META_INFO(HelloWorld179, HelloWorld179, 598),
	WRITER_META_INFO(HelloWorld180, HelloWorld180, 605),
	WRITER_META_INFO(HelloWorld181, HelloWorld181, 612),
	WRITER_META_INFO(HelloWorld182, HelloWorld182, 619),
	WRITER_META_INFO(HelloWorld183, HelloWorld183, 626),
	WRITER_META_INFO(HelloWorld184, HelloWorld184, 633),
	WRITER_META_INFO(HelloWorld185, HelloWorld185, 640),
	WRITER_META_INFO(HelloWorld186, HelloWorld186, 647),
	WRITER_META_INFO(HelloWorld187, HelloWorld187, 654),
	WRITER_META_INFO(HelloWorld188, HelloWorld188, 661),
	WRITER_META_INFO(HelloWorld189, HelloWorld189, 668),
	WRITER_META_INFO(HelloWorld190, HelloWorld190, 675),
	WRITER_META_INFO(HelloWorld191, HelloWorld191, 682),
	WRITER_META_INFO(HelloWorld192, HelloWorld192, 689),
	WRITER_META_INFO(HelloWorld193, HelloWorld193, 696),
	WRITER_META_INFO(HelloWorld194, HelloWorld194, 703),
	WRITER_META_INFO(HelloWorld195, HelloWorld195, 710),
	WRITER_META_INFO(HelloWorld196, HelloWorld196, 717),
	WRITER_META_INFO(HelloWorld197, HelloWorld197, 724),
	WRITER_META_INFO(HelloWorld198, HelloWorld198, 731),
	WRITER_META_INFO(HelloWorld199, HelloWorld199, 738),
	WRITER_META_INFO(HelloWorld200, HelloWorld200, 745),
	WRITER_META_INFO(HelloWorld201, HelloWorld201, 752),
	WRITER_META_INFO(HelloWorld202, HelloWorld202, 759),
	WRITER_META_INFO(HelloWorld203, HelloWorld203, 766),
	WRITER_META_INFO(HelloWorld204, HelloWorld204, 773),
	WRITER_META_INFO(HelloWorld205, HelloWorld205, 780),
	WRITER_META_INFO(HelloWorld206, HelloWorld206, 787),
	WRITER_META_INFO(HelloWorld207, HelloWorld207, 794),
	WRITER_META_INFO(HelloWorld208, HelloWorld208, 801),
	WRITER_META_INFO(HelloWorld209, HelloWorld209, 808),
	WRITER_META_INFO(HelloWorld210, HelloWorld210, 815),
	WRITER_META_INFO(HelloWorld211, HelloWorld211, 822),
	WRITER_META_INFO(HelloWorld212, HelloWorld212, 829),
	WRITER_META_INFO(HelloWorld213, HelloWorld213, 836),
	WRITER_META_INFO(HelloWorld214, HelloWorld214, 843),
	WRITER_META_INFO(HelloWorld215, HelloWorld215, 850),
	WRITER_META_INFO(HelloWorld216, HelloWorld216, 857),
	WRITER_META_INFO(HelloWorld217, HelloWorld217, 864),
	WRITER_META_INFO(HelloWorld218, HelloWorld218, 871),
	WRITER_META_INFO(HelloWorld219, HelloWorld219, 878),
	WRITER_META_INFO(HelloWorld220, HelloWorld220, 885),
	WRITER_META_INFO(HelloWorld221, HelloWorld221, 892),
	WRITER_META_INFO(HelloWorld222, HelloWorld222, 899),
	WRITER_META_INFO(HelloWorld223, HelloWorld223, 906),
	WRITER_META_INFO(HelloWorld224, HelloWorld224, 913),
	WRITER_META_INFO(HelloWorld225, HelloWorld225, 920),
	WRITER_META_INFO(HelloWorld226, HelloWorld226, 927),
	WRITER_META_INFO(HelloWorld227, HelloWorld227, 934),
	WRITER_META_INFO(HelloWorld228, HelloWorld228, 941),
	WRITER_META_INFO(HelloWorld229, HelloWorld229, 948),
	WRITER_META_INFO(HelloWorld230, HelloWorld230, 955),
	WRITER_META_INFO(HelloWorld231, HelloWorld231, 962),
	WRITER_META_INFO(HelloWorld232, HelloWorld232, 969),
	WRITER_META_INFO(HelloWorld233, HelloWorld233, 976),
	WRITER_META_INFO(HelloWorld234, HelloWorld234, 983),
	WRITER_META_INFO(HelloWorld235, HelloWorld235, 990),
	WRITER_META_INFO(HelloWorld236, HelloWorld236, 997),
	WRITER_META_INFO(HelloWorld237, HelloWorld237, 1004),
	WRITER_META_INFO(HelloWorld238, HelloWorld238, 1011),
	WRITER_META_INFO(HelloWorld239, HelloWorld239, 1018),
	WRITER_META_INFO(HelloWorld240, HelloWorld240, 1025),
	WRITER_META_INFO(HelloWorld241, HelloWorld241, 1032),
	WRITER_META_INFO(HelloWorld242, HelloWorld242, 1039),
	WRITER_META_INFO(HelloWorld243, HelloWorld243, 1046),
	WRITER_META_INFO(HelloWorld244, HelloWorld244, 1053),
	WRITER_META_INFO(HelloWorld245, HelloWorld245, 1060),
	WRITER_META_INFO(HelloWorld246, HelloWorld246, 1067),
	WRITER_META_INFO(HelloWorld247, HelloWorld247, 1074),
	WRITER_META_INFO(HelloWorld248, HelloWorld248, 1081),
	WRITER_META_INFO(HelloWorld249, HelloWorld249, 1088),
	WRITER_META_INFO(HelloWorld250, HelloWorld250, 1095),
	WRITER_META_INFO(HelloWorld251, HelloWorld251, 1102),
	WRITER_META_INFO(HelloWorld252, HelloWorld252, 1109),
	WRITER_META_INFO(HelloWorld253, HelloWorld253, 1116),
	WRITER_META_INFO(HelloWorld254, HelloWorld254, 1123),
	WRITER_META_INFO(HelloWorld255, HelloWorld255, 1130),
	WRITER_META_INFO(HelloWorld256, HelloWorld256, 1137),
	WRITER_META_INFO(HelloWorld257, HelloWorld257, 1144),
	WRITER_META_INFO(HelloWorld258, HelloWorld258, 1151),
	WRITER_META_INFO(HelloWorld259, HelloWorld259, 1158),
	WRITER_META_INFO(HelloWorld260, HelloWorld260, 1165),
	WRITER_META_INFO(HelloWorld261, HelloWorld261, 1172),
	WRITER_META_INFO(HelloWorld262, HelloWorld262, 1179),
	WRITER_META_INFO(HelloWorld263, HelloWorld263, 1186),
	WRITER_META_INFO(HelloWorld264, HelloWorld264, 1193),
	WRITER_META_INFO(HelloWorld265, HelloWorld265, 1200),
	WRITER_META_INFO(HelloWorld266, HelloWorld266, 1207),
	WRITER_META_INFO(HelloWorld267, HelloWorld267, 1214),
	WRITER_META_INFO(HelloWorld268, HelloWorld268, 1221),
	WRITER_META_INFO(HelloWorld269, HelloWorld269, 1228),
	WRITER_META_INFO(HelloWorld270, HelloWorld270, 1235),
	WRITER_META_INFO(HelloWorld271, HelloWorld271, 1242),
	WRITER_META_INFO(HelloWorld272, HelloWorld272, 1249),
	WRITER_META_INFO(HelloWorld273, HelloWorld273, 1256),
	WRITER_META_INFO(HelloWorld274, HelloWorld274, 1263),
	WRITER_META_INFO(HelloWorld275, HelloWorld275, 1270),
	WRITER_META_INFO(HelloWorld276, HelloWorld276, 1277),
	WRITER_META_INFO(HelloWorld277, HelloWorld277, 1284),
	WRITER_META_INFO(HelloWorld278, HelloWorld278, 1291),
	WRITER_META_INFO(HelloWorld279, HelloWorld279, 1298),
	WRITER_META_INFO(HelloWorld280, HelloWorld280, 1305),
	WRITER_META_INFO(HelloWorld281, HelloWorld281, 1312),
	WRITER_META_INFO(HelloWorld282, HelloWorld282, 1319),
	WRITER_META_INFO(HelloWorld283, HelloWorld283, 1326),
	WRITER_META_INFO(HelloWorld284, HelloWorld284, 1333),
	WRITER_META_INFO(HelloWorld285, HelloWorld285, 1340),
	WRITER_META_INFO(HelloWorld286, HelloWorld286, 1347),
	WRITER_META_INFO(HelloWorld287, HelloWorld287, 1354),
	WRITER_META_INFO(HelloWorld288, HelloWorld288, 1361),
	WRITER_META_INFO(HelloWorld289, HelloWorld289, 1368),
	WRITER_META_INFO(HelloWorld290, HelloWorld290, 1375),
	WRITER_META_INFO(HelloWorld291, HelloWorld291, 1382),
	WRITER_META_INFO(HelloWorld292, HelloWorld292, 1389),
	WRITER_META_INFO(HelloWorld293, HelloWorld293, 1396),
	WRITER_META_INFO(HelloWorld294, HelloWorld294, 1403),
	WRITER_META_INFO(HelloWorld295, HelloWorld295, 1410),
	WRITER_META_INFO(HelloWorld296, HelloWorld296, 1417),
	WRITER_META_INFO(HelloWorld297, HelloWorld297, 1424),
	WRITER_META_INFO(HelloWorld298, HelloWorld298, 1431),
	WRITER_META_INFO(HelloWorld299, HelloWorld299, 1438),
};

/* Greatest Common Divisor */
static uint32_t gcd(uint32_t a, uint32_t b)
{
	uint32_t temp;

	while (b != 0) {
		temp = b;

		b = a % b;
		a = temp;
	}

	return a;
}

/* Update the phase */
static void writer_meta_info_update_phase(struct writer_meta_info *info_list,
								int info_cnt)
{
	uint32_t min_conflicts;
	uint32_t best_phase;

	for (int i = 0; i < info_cnt; ++i) {
		info_list[i].period_ms = info_list[i].period_ms / MVBS_LOOP_CYCLE_MS;
	}


	for (int i = 0; i < info_cnt; ++i) {
		min_conflicts	= UINT_MAX;
		best_phase	= 0;

		// for each available phase (0 <= d < k)
		for (uint32_t d = 0; d < info_list[i].period_ms; ++d) {
			uint32_t conflicts = 0;

			// check the all available phase
			for (int j = 0; j < i; ++j) {
				uint32_t tmp_gcd;

				tmp_gcd = gcd(info_list[i].period_ms,
					      info_list[j].period_ms);

				if ((d - info_list[j].phase_ms) % tmp_gcd == 0) {
					// increase the count of conflicts.
					conflicts++;
				}
			}

			// select the best phase
			if (conflicts < min_conflicts ||
			   (conflicts == min_conflicts && d < best_phase)) {
				min_conflicts = conflicts;
				best_phase    = d;
			}
		}

		info_list[i].phase_ms = best_phase; // store the result
	}

	for (int i = 0; i < info_cnt; ++i) {
		info_list[i].period_ms = info_list[i].period_ms * 5;
		info_list[i].phase_ms  = info_list[i].phase_ms * 5;

		info_list[i].period_next  = info_list[i].phase_ms;
	}
}

static void publisher_init(Rte_Dds_Participant ptcp, uint32_t ms)
{
	struct writer_meta_info *info;

	for (uint8_t i = 0; i < ARRAY_SIZE(publisher_list); i++) {
		info = &publisher_list[i];

		info->w = Rte_Dds_GetWriter(ptcp, info->topic);
		info->init(info->sample);

		if (info->period_ms != 0) {
			info->public_count = ms / info->period_ms;
		} else {
			info->public_count = 0;
		}

		Rte_Dds_Writer_Set_Private(info->w, info);
	}

	writer_meta_info_update_phase(publisher_list,
					ARRAY_SIZE(publisher_list));
}

void Rte_Dds_Writer_OnMatch(Rte_Dds_Writer w,
			    const Rte_Dds_Writer_MatchStatus *status)
{
	(void)status;
	struct writer_meta_info *info;

	for (uint8_t i = 0; i < ARRAY_SIZE(publisher_list); i++) {
		info = &publisher_list[i];

		if (!mvbs_strcmp(info->topic, writer_get_topicname(w))) {
			info->match_count++;
			pr_warn("topic:%s, match_count:%d",info->topic, info->match_count);
		}
	}
}

static bool get_all_writer_match_status(void)
{
	struct writer_meta_info *info;

	for (uint8_t i = 0; i < ARRAY_SIZE(publisher_list); i++) {
		info = &publisher_list[i];

		if (info->match_count == 0) {
			return false;
		}
	}

	return true;
}

static int writer_topic_public(struct writer_meta_info *info)
{
	(void)info;
	Rte_Dds_TopicData        data;

	Rte_Dds_PackData(&data, info->sample);

	if (RTE_DDS_RETCODE_OK == Rte_Dds_TxData(info->w, &data, NULL)) {
		info->send_count++;

		if (info->send_count % WRITER_DUMP_PER_CNT == 0) {
			pr_info("Success to send sample of Topic [%s]: [%d].",
						info->topic, info->send_count);
		}
	} else {
		pr_info("Fail to send sample of Topic [%s].", info->topic);
	}

	return MVBS_TEST_CONTINUE;
}

static int writers_topic_loop(void)
{
	static unsigned long timer_ms;
	struct writer_meta_info *info;
	uint16_t topic_done_cnt = 0;

	for(uint8_t i = 0; i < ARRAY_SIZE(publisher_list); i++) {
		info = &publisher_list[i];

		if (info->public_count == 0) {
			topic_done_cnt++;

			continue ;
		}

		if (time_after_eq(timer_ms, info->period_next)) {
			(void)writer_topic_public(info);

			/* FIXME:
			 * Should the period_next be changed only public success?
			 */
			info->period_next = timer_ms + info->period_ms;

			info->public_count--;
		}
	}

	timer_ms += MVBS_LOOP_CYCLE_MS;

	if (topic_done_cnt < ARRAY_SIZE(publisher_list)) {
		return MVBS_TEST_CONTINUE;
	} else {
		pr_info("Writer test finished.");
		return MVBS_TEST_PASS;
	}
}

static int app_loop(unsigned long timer_ms)
{
	static uint16_t	stage = 0;

	int32_t		tmp_sec = 0;
	uint32_t	tmp_nsec = 0;

	bool		reader_all_match;
	bool		writer_all_match;

	int ret = MVBS_TEST_CONTINUE;

	(void)timer_ms;

	switch (stage) {
	case 0:
		reader_all_match = get_all_reader_match_status();
		writer_all_match = get_all_writer_match_status();

		if (reader_all_match && writer_all_match) {
			mvbs_get_time(&tmp_sec, &tmp_nsec);

			pr_info("All topic are match, current tmp_sec:%d.tmp_nsec:%d",
								   tmp_sec, tmp_nsec);
		}
		stage = 1;

		break ;

	case 1:
		ret = writers_topic_loop();
		break ;

	default:
		break;
	}

	return ret;
}

static Rte_Dds_Participant app_init(int argc, char *argv[])
{
	int32_t		tmp_sec  = 0;
	uint32_t	tmp_nsec = 0;

	(void)argc;
	(void)argv;


	extern Rte_Dds_Participant Rte_Dds_GetParticipant();
	Rte_Dds_Participant ptcp = Rte_Dds_GetParticipant();
	if (Rte_Dds_Init(ptcp) != RTE_DDS_RETCODE_OK) {
		pr_err(ERR_INVALID,"Rte_Dds_Init fail !");
		return NULL;
	} else {
		pr_info("Rte_Dds_Init OK !");
	}

	mvbs_get_time(&tmp_sec, &tmp_nsec);

	pr_info("MVBS init success, current tmp_sec:%d.tmp_nsec:%d",
							tmp_sec, tmp_nsec);
	subscriber_init(ptcp);
	publisher_init(ptcp, TOTAL_TIME_MS);

	AgentHelloWorld_init(&sample1);
	Rte_Dds_PackData(&data_w, &sample1);
	pr_warn("topic_w.name:%s",topic_w.name);
	rte_w = Rte_Dds_GetWriter(ptcp, topic_w.name);

	AgentHelloWorld_init(&sample2);
	Rte_Dds_PackData(&data_r, &sample2);
	pr_warn("topic_r.name:%s",topic_r.name);
	rte_r = Rte_Dds_GetReader(ptcp, topic_r.name);

	pr_info("Allocated %ld bytes in heap.", dynamic_mem_get_max_used());

	return ptcp;
}

#if defined(TARGET_PRODUCT_LINUX) || defined(TARGET_PRODUCT_J6M_ACORE) || defined(TARGET_PRODUCT_MINGW)

#define MVBS_APP_LOOP_PERIOD_MS			5

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int ret;
	struct mvbs_event_loop		*loop		= NULL;
	Rte_Dds_Participant		ptcp		= NULL;

	unsigned long			mvbs_app_loop_cnt = 0;
	uint32_t			recv_max_pkg	  = 0;
	uint32_t			event		  = 0;

	#ifdef TARGET_PRODUCT_MINGW
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	#endif

	loop = mvbs_event_loop_create(MVBS_APP_LOOP_PERIOD_MS);

	do {
		ptcp = app_init(0, NULL);
		if (ptcp != NULL) {
			break;
		}
	} while (true);

	while (true) {
		event = mvbs_event_loop_wait(loop);

		if (event & MVBS_EV_RECV) {
			if (ptcp != NULL) {
				Rte_Dds_Ptcp_Recv_Handler(ptcp, recv_max_pkg);
			}
		}

		if (event & MVBS_EV_TIMER) {
			if (ptcp != NULL) {
				Rte_Dds_Ptcp_Timer_Handler(ptcp);
			}

			mvbs_app_loop_cnt++;

			ret = app_loop(mvbs_app_loop_cnt * MVBS_APP_LOOP_PERIOD_MS);
			if (ret != MVBS_TEST_CONTINUE) {
				break ;
			}
		}
	}
	if (ret == MVBS_TEST_PASS) {
		pr_info("~~~ Run successfully ~~~");
	} else {
		pr_info("~~~ Run failure ~~~");
	}

#ifdef TARGET_PRODUCT_MINGW
	WSACleanup();
#endif
	return ret;
}

#else

void dds_5ms()
{
	#define MVBS_STAGE_INIT         0
	#define MVBS_STAGE_LOOP         1

	static unsigned long	timer_ms;
	static int mvbs_status = MVBS_STAGE_INIT;
	static Rte_Dds_Participant ptcp;

	uint32_t recv_max_pkg = 0;

	timer_ms += MVBS_LOOP_CYCLE_MS;

	switch (mvbs_status) {
	case MVBS_STAGE_INIT:
		ptcp = app_init(0, NULL);
		if (ptcp != NULL)
			mvbs_status = MVBS_STAGE_LOOP;

		break;

	case MVBS_STAGE_LOOP:
		Rte_Dds_Ptcp_Timer_Handler(ptcp);
		Rte_Dds_Ptcp_Recv_Handler(ptcp, recv_max_pkg);

		app_loop(timer_ms);
		break;
	}
}
#endif
