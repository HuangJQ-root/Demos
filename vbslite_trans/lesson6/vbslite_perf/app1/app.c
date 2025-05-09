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

#define EVENT_CYCLE_MS 100     //domain_0_topic_0Topic send period 100ms

static inline int get_cpu_load(void) {return -1;}
static int gtx_ok_cnt;
static struct AgentHelloWorld sample1;
static Rte_Dds_TopicData data_w;
static Rte_Dds_Writer w;
static Rte_Dds_TopicId topic_w = DEF_RTE_DDS_TOPIC("domain_0_topic_0Topic", 0 );

// static int grx_ok_cnt;
static struct AgentHelloWorld sample2 ;
static Rte_Dds_TopicData data_r;
static Rte_Dds_Reader r;
static Rte_Dds_TopicId topic_r = DEF_RTE_DDS_TOPIC("domain_0_topic_1Topic", 0 );
// static struct sample_info Sample_info;
/* The following code lines are for reader topic. */


static uint64_t rx_ok_count = 0;
static uint64_t total_last_packet_count = 0;
static uint64_t total_loss_packet_count = 0;

static uint64_t convert_to_nanoseconds(int32_t seconds, uint32_t nanoseconds) {
	const uint64_t NANOSECONDS_PER_SECOND = 1000000000ULL;

	uint64_t total_nanoseconds = (uint64_t)(seconds * NANOSECONDS_PER_SECOND + nanoseconds);

	return total_nanoseconds;
}

static int64_t e2e_delay_array[5] = {0};

static void time_event(Rte_Dds_Reader r)
{
	int32_t		tmp_sec = 0;
	uint32_t	tmp_nsec = 0;
	uint64_t	e2e_delay = 0;
	static uint8_t  e2e_delay_count = 0;

	Rte_Dds_ReturnType ret;
	ret = Rte_Dds_RxData(r, true, &data_r, NULL);
	if (ret == RTE_DDS_RETCODE_OK) {
		rx_ok_count++;
		mvbs_get_time(&tmp_sec, &tmp_nsec);

		uint8_t delta_counter = sample2.sn - total_last_packet_count;
		if (delta_counter > 1) {
			total_loss_packet_count++;
			pr_warn("loss_packet_count:%d",delta_counter);
		}

		total_last_packet_count = sample2.sn;

		e2e_delay = convert_to_nanoseconds(tmp_sec, tmp_nsec) - sample2.index;
		if (e2e_delay_count < 5) {
			e2e_delay_count++;
			// pr_info("e2e_delay:%d",e2e_delay);
			// pr_warn("e2e_delay_count:%lu",e2e_delay_count);
			e2e_delay_array[e2e_delay_count - 1] = e2e_delay/2;
		} else {
			e2e_delay_count = 0;
			uint64_t e2e_avg_delay = 0;

			e2e_avg_delay = (e2e_delay_array[0] + e2e_delay_array[1] + e2e_delay_array[2] + e2e_delay_array[3]
				+ e2e_delay_array[4])/5;
			pr_info("---------------%d-------------------",rx_ok_count);
			pr_warn("total_recv_packet:%ld,total_loss_packet_count:%ld.",sample2.sn, total_loss_packet_count);
			pr_warn("cpu_load:%d.",get_cpu_load());
			pr_warn("dynamic_ram:%lu.",dynamic_mem_get_max_used());
			pr_warn("e2e_avg_delay:%lu.", e2e_avg_delay);
			pr_info("----------------------------------");
		}
	}
}


static int on_event0()
{
	int32_t		tmp_sec = 0;
	uint32_t	tmp_nsec = 0;
	Rte_Dds_ReturnType ret;

	Rte_Dds_TopicStats stats;
	memset(&stats, 0, sizeof(Rte_Dds_TopicStats));
	ret = Rte_Dds_GetWriterStats(w, &stats);
	if (ret == RTE_DDS_RETCODE_OK && stats.remotes_online > 0) {
		mvbs_get_time(&tmp_sec, &tmp_nsec);

		sample1.index = convert_to_nanoseconds(tmp_sec, tmp_nsec);
		sample1.sn = 0;

		Rte_Dds_ReturnType ret = Rte_Dds_TxData(w, &data_w, NULL);
		if (ret == RTE_DDS_RETCODE_OK) {
			gtx_ok_cnt++;
		} else {
			pr_info("Rte_Dds_TxData failed!\n");
		return MVBS_TEST_FAIL;
		}
	}

	return MVBS_TEST_CONTINUE;
}

enum {
	reader_topic_index(HelloWorld151),
	reader_topic_index(HelloWorld152),
	reader_topic_index(HelloWorld153),
	reader_topic_index(HelloWorld154),
	reader_topic_index(HelloWorld155),
	reader_topic_index(HelloWorld156),
	reader_topic_index(HelloWorld157),
	reader_topic_index(HelloWorld158),
	reader_topic_index(HelloWorld159),
	reader_topic_index(HelloWorld160),
	reader_topic_index(HelloWorld161),
	reader_topic_index(HelloWorld162),
	reader_topic_index(HelloWorld163),
	reader_topic_index(HelloWorld164),
	reader_topic_index(HelloWorld165),
	reader_topic_index(HelloWorld166),
	reader_topic_index(HelloWorld167),
	reader_topic_index(HelloWorld168),
	reader_topic_index(HelloWorld169),
	reader_topic_index(HelloWorld170),
	reader_topic_index(HelloWorld171),
	reader_topic_index(HelloWorld172),
	reader_topic_index(HelloWorld173),
	reader_topic_index(HelloWorld174),
	reader_topic_index(HelloWorld175),
	reader_topic_index(HelloWorld176),
	reader_topic_index(HelloWorld177),
	reader_topic_index(HelloWorld178),
	reader_topic_index(HelloWorld179),
	reader_topic_index(HelloWorld180),
	reader_topic_index(HelloWorld181),
	reader_topic_index(HelloWorld182),
	reader_topic_index(HelloWorld183),
	reader_topic_index(HelloWorld184),
	reader_topic_index(HelloWorld185),
	reader_topic_index(HelloWorld186),
	reader_topic_index(HelloWorld187),
	reader_topic_index(HelloWorld188),
	reader_topic_index(HelloWorld189),
	reader_topic_index(HelloWorld190),
	reader_topic_index(HelloWorld191),
	reader_topic_index(HelloWorld192),
	reader_topic_index(HelloWorld193),
	reader_topic_index(HelloWorld194),
	reader_topic_index(HelloWorld195),
	reader_topic_index(HelloWorld196),
	reader_topic_index(HelloWorld197),
	reader_topic_index(HelloWorld198),
	reader_topic_index(HelloWorld199),
	reader_topic_index(HelloWorld200),
	reader_topic_index(HelloWorld201),
	reader_topic_index(HelloWorld202),
	reader_topic_index(HelloWorld203),
	reader_topic_index(HelloWorld204),
	reader_topic_index(HelloWorld205),
	reader_topic_index(HelloWorld206),
	reader_topic_index(HelloWorld207),
	reader_topic_index(HelloWorld208),
	reader_topic_index(HelloWorld209),
	reader_topic_index(HelloWorld210),
	reader_topic_index(HelloWorld211),
	reader_topic_index(HelloWorld212),
	reader_topic_index(HelloWorld213),
	reader_topic_index(HelloWorld214),
	reader_topic_index(HelloWorld215),
	reader_topic_index(HelloWorld216),
	reader_topic_index(HelloWorld217),
	reader_topic_index(HelloWorld218),
	reader_topic_index(HelloWorld219),
	reader_topic_index(HelloWorld220),
	reader_topic_index(HelloWorld221),
	reader_topic_index(HelloWorld222),
	reader_topic_index(HelloWorld223),
	reader_topic_index(HelloWorld224),
	reader_topic_index(HelloWorld225),
	reader_topic_index(HelloWorld226),
	reader_topic_index(HelloWorld227),
	reader_topic_index(HelloWorld228),
	reader_topic_index(HelloWorld229),
	reader_topic_index(HelloWorld230),
	reader_topic_index(HelloWorld231),
	reader_topic_index(HelloWorld232),
	reader_topic_index(HelloWorld233),
	reader_topic_index(HelloWorld234),
	reader_topic_index(HelloWorld235),
	reader_topic_index(HelloWorld236),
	reader_topic_index(HelloWorld237),
	reader_topic_index(HelloWorld238),
	reader_topic_index(HelloWorld239),
	reader_topic_index(HelloWorld240),
	reader_topic_index(HelloWorld241),
	reader_topic_index(HelloWorld242),
	reader_topic_index(HelloWorld243),
	reader_topic_index(HelloWorld244),
	reader_topic_index(HelloWorld245),
	reader_topic_index(HelloWorld246),
	reader_topic_index(HelloWorld247),
	reader_topic_index(HelloWorld248),
	reader_topic_index(HelloWorld249),
	reader_topic_index(HelloWorld250),
	reader_topic_index(HelloWorld251),
	reader_topic_index(HelloWorld252),
	reader_topic_index(HelloWorld253),
	reader_topic_index(HelloWorld254),
	reader_topic_index(HelloWorld255),
	reader_topic_index(HelloWorld256),
	reader_topic_index(HelloWorld257),
	reader_topic_index(HelloWorld258),
	reader_topic_index(HelloWorld259),
	reader_topic_index(HelloWorld260),
	reader_topic_index(HelloWorld261),
	reader_topic_index(HelloWorld262),
	reader_topic_index(HelloWorld263),
	reader_topic_index(HelloWorld264),
	reader_topic_index(HelloWorld265),
	reader_topic_index(HelloWorld266),
	reader_topic_index(HelloWorld267),
	reader_topic_index(HelloWorld268),
	reader_topic_index(HelloWorld269),
	reader_topic_index(HelloWorld270),
	reader_topic_index(HelloWorld271),
	reader_topic_index(HelloWorld272),
	reader_topic_index(HelloWorld273),
	reader_topic_index(HelloWorld274),
	reader_topic_index(HelloWorld275),
	reader_topic_index(HelloWorld276),
	reader_topic_index(HelloWorld277),
	reader_topic_index(HelloWorld278),
	reader_topic_index(HelloWorld279),
	reader_topic_index(HelloWorld280),
	reader_topic_index(HelloWorld281),
	reader_topic_index(HelloWorld282),
	reader_topic_index(HelloWorld283),
	reader_topic_index(HelloWorld284),
	reader_topic_index(HelloWorld285),
	reader_topic_index(HelloWorld286),
	reader_topic_index(HelloWorld287),
	reader_topic_index(HelloWorld288),
	reader_topic_index(HelloWorld289),
	reader_topic_index(HelloWorld290),
	reader_topic_index(HelloWorld291),
	reader_topic_index(HelloWorld292),
	reader_topic_index(HelloWorld293),
	reader_topic_index(HelloWorld294),
	reader_topic_index(HelloWorld295),
	reader_topic_index(HelloWorld296),
	reader_topic_index(HelloWorld297),
	reader_topic_index(HelloWorld298),
	reader_topic_index(HelloWorld299),
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

void HelloWorld151_cb(void *sample)
{
	HelloWorld151 *data = (HelloWorld151*)sample;
	(void)data;
}
void HelloWorld152_cb(void *sample)
{
	HelloWorld152 *data = (HelloWorld152*)sample;
	(void)data;
}
void HelloWorld153_cb(void *sample)
{
	HelloWorld153 *data = (HelloWorld153*)sample;
	(void)data;
}
void HelloWorld154_cb(void *sample)
{
	HelloWorld154 *data = (HelloWorld154*)sample;
	(void)data;
}
void HelloWorld155_cb(void *sample)
{
	HelloWorld155 *data = (HelloWorld155*)sample;
	(void)data;
}
void HelloWorld156_cb(void *sample)
{
	HelloWorld156 *data = (HelloWorld156*)sample;
	(void)data;
}
void HelloWorld157_cb(void *sample)
{
	HelloWorld157 *data = (HelloWorld157*)sample;
	(void)data;
}
void HelloWorld158_cb(void *sample)
{
	HelloWorld158 *data = (HelloWorld158*)sample;
	(void)data;
}
void HelloWorld159_cb(void *sample)
{
	HelloWorld159 *data = (HelloWorld159*)sample;
	(void)data;
}
void HelloWorld160_cb(void *sample)
{
	HelloWorld160 *data = (HelloWorld160*)sample;
	(void)data;
}
void HelloWorld161_cb(void *sample)
{
	HelloWorld161 *data = (HelloWorld161*)sample;
	(void)data;
}
void HelloWorld162_cb(void *sample)
{
	HelloWorld162 *data = (HelloWorld162*)sample;
	(void)data;
}
void HelloWorld163_cb(void *sample)
{
	HelloWorld163 *data = (HelloWorld163*)sample;
	(void)data;
}
void HelloWorld164_cb(void *sample)
{
	HelloWorld164 *data = (HelloWorld164*)sample;
	(void)data;
}
void HelloWorld165_cb(void *sample)
{
	HelloWorld165 *data = (HelloWorld165*)sample;
	(void)data;
}
void HelloWorld166_cb(void *sample)
{
	HelloWorld166 *data = (HelloWorld166*)sample;
	(void)data;
}
void HelloWorld167_cb(void *sample)
{
	HelloWorld167 *data = (HelloWorld167*)sample;
	(void)data;
}
void HelloWorld168_cb(void *sample)
{
	HelloWorld168 *data = (HelloWorld168*)sample;
	(void)data;
}
void HelloWorld169_cb(void *sample)
{
	HelloWorld169 *data = (HelloWorld169*)sample;
	(void)data;
}
void HelloWorld170_cb(void *sample)
{
	HelloWorld170 *data = (HelloWorld170*)sample;
	(void)data;
}
void HelloWorld171_cb(void *sample)
{
	HelloWorld171 *data = (HelloWorld171*)sample;
	(void)data;
}
void HelloWorld172_cb(void *sample)
{
	HelloWorld172 *data = (HelloWorld172*)sample;
	(void)data;
}
void HelloWorld173_cb(void *sample)
{
	HelloWorld173 *data = (HelloWorld173*)sample;
	(void)data;
}
void HelloWorld174_cb(void *sample)
{
	HelloWorld174 *data = (HelloWorld174*)sample;
	(void)data;
}
void HelloWorld175_cb(void *sample)
{
	HelloWorld175 *data = (HelloWorld175*)sample;
	(void)data;
}
void HelloWorld176_cb(void *sample)
{
	HelloWorld176 *data = (HelloWorld176*)sample;
	(void)data;
}
void HelloWorld177_cb(void *sample)
{
	HelloWorld177 *data = (HelloWorld177*)sample;
	(void)data;
}
void HelloWorld178_cb(void *sample)
{
	HelloWorld178 *data = (HelloWorld178*)sample;
	(void)data;
}
void HelloWorld179_cb(void *sample)
{
	HelloWorld179 *data = (HelloWorld179*)sample;
	(void)data;
}
void HelloWorld180_cb(void *sample)
{
	HelloWorld180 *data = (HelloWorld180*)sample;
	(void)data;
}
void HelloWorld181_cb(void *sample)
{
	HelloWorld181 *data = (HelloWorld181*)sample;
	(void)data;
}
void HelloWorld182_cb(void *sample)
{
	HelloWorld182 *data = (HelloWorld182*)sample;
	(void)data;
}
void HelloWorld183_cb(void *sample)
{
	HelloWorld183 *data = (HelloWorld183*)sample;
	(void)data;
}
void HelloWorld184_cb(void *sample)
{
	HelloWorld184 *data = (HelloWorld184*)sample;
	(void)data;
}
void HelloWorld185_cb(void *sample)
{
	HelloWorld185 *data = (HelloWorld185*)sample;
	(void)data;
}
void HelloWorld186_cb(void *sample)
{
	HelloWorld186 *data = (HelloWorld186*)sample;
	(void)data;
}
void HelloWorld187_cb(void *sample)
{
	HelloWorld187 *data = (HelloWorld187*)sample;
	(void)data;
}
void HelloWorld188_cb(void *sample)
{
	HelloWorld188 *data = (HelloWorld188*)sample;
	(void)data;
}
void HelloWorld189_cb(void *sample)
{
	HelloWorld189 *data = (HelloWorld189*)sample;
	(void)data;
}
void HelloWorld190_cb(void *sample)
{
	HelloWorld190 *data = (HelloWorld190*)sample;
	(void)data;
}
void HelloWorld191_cb(void *sample)
{
	HelloWorld191 *data = (HelloWorld191*)sample;
	(void)data;
}
void HelloWorld192_cb(void *sample)
{
	HelloWorld192 *data = (HelloWorld192*)sample;
	(void)data;
}
void HelloWorld193_cb(void *sample)
{
	HelloWorld193 *data = (HelloWorld193*)sample;
	(void)data;
}
void HelloWorld194_cb(void *sample)
{
	HelloWorld194 *data = (HelloWorld194*)sample;
	(void)data;
}
void HelloWorld195_cb(void *sample)
{
	HelloWorld195 *data = (HelloWorld195*)sample;
	(void)data;
}
void HelloWorld196_cb(void *sample)
{
	HelloWorld196 *data = (HelloWorld196*)sample;
	(void)data;
}
void HelloWorld197_cb(void *sample)
{
	HelloWorld197 *data = (HelloWorld197*)sample;
	(void)data;
}
void HelloWorld198_cb(void *sample)
{
	HelloWorld198 *data = (HelloWorld198*)sample;
	(void)data;
}
void HelloWorld199_cb(void *sample)
{
	HelloWorld199 *data = (HelloWorld199*)sample;
	(void)data;
}
void HelloWorld200_cb(void *sample)
{
	HelloWorld200 *data = (HelloWorld200*)sample;
	(void)data;
}
void HelloWorld201_cb(void *sample)
{
	HelloWorld201 *data = (HelloWorld201*)sample;
	(void)data;
}
void HelloWorld202_cb(void *sample)
{
	HelloWorld202 *data = (HelloWorld202*)sample;
	(void)data;
}
void HelloWorld203_cb(void *sample)
{
	HelloWorld203 *data = (HelloWorld203*)sample;
	(void)data;
}
void HelloWorld204_cb(void *sample)
{
	HelloWorld204 *data = (HelloWorld204*)sample;
	(void)data;
}
void HelloWorld205_cb(void *sample)
{
	HelloWorld205 *data = (HelloWorld205*)sample;
	(void)data;
}
void HelloWorld206_cb(void *sample)
{
	HelloWorld206 *data = (HelloWorld206*)sample;
	(void)data;
}
void HelloWorld207_cb(void *sample)
{
	HelloWorld207 *data = (HelloWorld207*)sample;
	(void)data;
}
void HelloWorld208_cb(void *sample)
{
	HelloWorld208 *data = (HelloWorld208*)sample;
	(void)data;
}
void HelloWorld209_cb(void *sample)
{
	HelloWorld209 *data = (HelloWorld209*)sample;
	(void)data;
}
void HelloWorld210_cb(void *sample)
{
	HelloWorld210 *data = (HelloWorld210*)sample;
	(void)data;
}
void HelloWorld211_cb(void *sample)
{
	HelloWorld211 *data = (HelloWorld211*)sample;
	(void)data;
}
void HelloWorld212_cb(void *sample)
{
	HelloWorld212 *data = (HelloWorld212*)sample;
	(void)data;
}
void HelloWorld213_cb(void *sample)
{
	HelloWorld213 *data = (HelloWorld213*)sample;
	(void)data;
}
void HelloWorld214_cb(void *sample)
{
	HelloWorld214 *data = (HelloWorld214*)sample;
	(void)data;
}
void HelloWorld215_cb(void *sample)
{
	HelloWorld215 *data = (HelloWorld215*)sample;
	(void)data;
}
void HelloWorld216_cb(void *sample)
{
	HelloWorld216 *data = (HelloWorld216*)sample;
	(void)data;
}
void HelloWorld217_cb(void *sample)
{
	HelloWorld217 *data = (HelloWorld217*)sample;
	(void)data;
}
void HelloWorld218_cb(void *sample)
{
	HelloWorld218 *data = (HelloWorld218*)sample;
	(void)data;
}
void HelloWorld219_cb(void *sample)
{
	HelloWorld219 *data = (HelloWorld219*)sample;
	(void)data;
}
void HelloWorld220_cb(void *sample)
{
	HelloWorld220 *data = (HelloWorld220*)sample;
	(void)data;
}
void HelloWorld221_cb(void *sample)
{
	HelloWorld221 *data = (HelloWorld221*)sample;
	(void)data;
}
void HelloWorld222_cb(void *sample)
{
	HelloWorld222 *data = (HelloWorld222*)sample;
	(void)data;
}
void HelloWorld223_cb(void *sample)
{
	HelloWorld223 *data = (HelloWorld223*)sample;
	(void)data;
}
void HelloWorld224_cb(void *sample)
{
	HelloWorld224 *data = (HelloWorld224*)sample;
	(void)data;
}
void HelloWorld225_cb(void *sample)
{
	HelloWorld225 *data = (HelloWorld225*)sample;
	(void)data;
}
void HelloWorld226_cb(void *sample)
{
	HelloWorld226 *data = (HelloWorld226*)sample;
	(void)data;
}
void HelloWorld227_cb(void *sample)
{
	HelloWorld227 *data = (HelloWorld227*)sample;
	(void)data;
}
void HelloWorld228_cb(void *sample)
{
	HelloWorld228 *data = (HelloWorld228*)sample;
	(void)data;
}
void HelloWorld229_cb(void *sample)
{
	HelloWorld229 *data = (HelloWorld229*)sample;
	(void)data;
}
void HelloWorld230_cb(void *sample)
{
	HelloWorld230 *data = (HelloWorld230*)sample;
	(void)data;
}
void HelloWorld231_cb(void *sample)
{
	HelloWorld231 *data = (HelloWorld231*)sample;
	(void)data;
}
void HelloWorld232_cb(void *sample)
{
	HelloWorld232 *data = (HelloWorld232*)sample;
	(void)data;
}
void HelloWorld233_cb(void *sample)
{
	HelloWorld233 *data = (HelloWorld233*)sample;
	(void)data;
}
void HelloWorld234_cb(void *sample)
{
	HelloWorld234 *data = (HelloWorld234*)sample;
	(void)data;
}
void HelloWorld235_cb(void *sample)
{
	HelloWorld235 *data = (HelloWorld235*)sample;
	(void)data;
}
void HelloWorld236_cb(void *sample)
{
	HelloWorld236 *data = (HelloWorld236*)sample;
	(void)data;
}
void HelloWorld237_cb(void *sample)
{
	HelloWorld237 *data = (HelloWorld237*)sample;
	(void)data;
}
void HelloWorld238_cb(void *sample)
{
	HelloWorld238 *data = (HelloWorld238*)sample;
	(void)data;
}
void HelloWorld239_cb(void *sample)
{
	HelloWorld239 *data = (HelloWorld239*)sample;
	(void)data;
}
void HelloWorld240_cb(void *sample)
{
	HelloWorld240 *data = (HelloWorld240*)sample;
	(void)data;
}
void HelloWorld241_cb(void *sample)
{
	HelloWorld241 *data = (HelloWorld241*)sample;
	(void)data;
}
void HelloWorld242_cb(void *sample)
{
	HelloWorld242 *data = (HelloWorld242*)sample;
	(void)data;
}
void HelloWorld243_cb(void *sample)
{
	HelloWorld243 *data = (HelloWorld243*)sample;
	(void)data;
}
void HelloWorld244_cb(void *sample)
{
	HelloWorld244 *data = (HelloWorld244*)sample;
	(void)data;
}
void HelloWorld245_cb(void *sample)
{
	HelloWorld245 *data = (HelloWorld245*)sample;
	(void)data;
}
void HelloWorld246_cb(void *sample)
{
	HelloWorld246 *data = (HelloWorld246*)sample;
	(void)data;
}
void HelloWorld247_cb(void *sample)
{
	HelloWorld247 *data = (HelloWorld247*)sample;
	(void)data;
}
void HelloWorld248_cb(void *sample)
{
	HelloWorld248 *data = (HelloWorld248*)sample;
	(void)data;
}
void HelloWorld249_cb(void *sample)
{
	HelloWorld249 *data = (HelloWorld249*)sample;
	(void)data;
}
void HelloWorld250_cb(void *sample)
{
	HelloWorld250 *data = (HelloWorld250*)sample;
	(void)data;
}
void HelloWorld251_cb(void *sample)
{
	HelloWorld251 *data = (HelloWorld251*)sample;
	(void)data;
}
void HelloWorld252_cb(void *sample)
{
	HelloWorld252 *data = (HelloWorld252*)sample;
	(void)data;
}
void HelloWorld253_cb(void *sample)
{
	HelloWorld253 *data = (HelloWorld253*)sample;
	(void)data;
}
void HelloWorld254_cb(void *sample)
{
	HelloWorld254 *data = (HelloWorld254*)sample;
	(void)data;
}
void HelloWorld255_cb(void *sample)
{
	HelloWorld255 *data = (HelloWorld255*)sample;
	(void)data;
}
void HelloWorld256_cb(void *sample)
{
	HelloWorld256 *data = (HelloWorld256*)sample;
	(void)data;
}
void HelloWorld257_cb(void *sample)
{
	HelloWorld257 *data = (HelloWorld257*)sample;
	(void)data;
}
void HelloWorld258_cb(void *sample)
{
	HelloWorld258 *data = (HelloWorld258*)sample;
	(void)data;
}
void HelloWorld259_cb(void *sample)
{
	HelloWorld259 *data = (HelloWorld259*)sample;
	(void)data;
}
void HelloWorld260_cb(void *sample)
{
	HelloWorld260 *data = (HelloWorld260*)sample;
	(void)data;
}
void HelloWorld261_cb(void *sample)
{
	HelloWorld261 *data = (HelloWorld261*)sample;
	(void)data;
}
void HelloWorld262_cb(void *sample)
{
	HelloWorld262 *data = (HelloWorld262*)sample;
	(void)data;
}
void HelloWorld263_cb(void *sample)
{
	HelloWorld263 *data = (HelloWorld263*)sample;
	(void)data;
}
void HelloWorld264_cb(void *sample)
{
	HelloWorld264 *data = (HelloWorld264*)sample;
	(void)data;
}
void HelloWorld265_cb(void *sample)
{
	HelloWorld265 *data = (HelloWorld265*)sample;
	(void)data;
}
void HelloWorld266_cb(void *sample)
{
	HelloWorld266 *data = (HelloWorld266*)sample;
	(void)data;
}
void HelloWorld267_cb(void *sample)
{
	HelloWorld267 *data = (HelloWorld267*)sample;
	(void)data;
}
void HelloWorld268_cb(void *sample)
{
	HelloWorld268 *data = (HelloWorld268*)sample;
	(void)data;
}
void HelloWorld269_cb(void *sample)
{
	HelloWorld269 *data = (HelloWorld269*)sample;
	(void)data;
}
void HelloWorld270_cb(void *sample)
{
	HelloWorld270 *data = (HelloWorld270*)sample;
	(void)data;
}
void HelloWorld271_cb(void *sample)
{
	HelloWorld271 *data = (HelloWorld271*)sample;
	(void)data;
}
void HelloWorld272_cb(void *sample)
{
	HelloWorld272 *data = (HelloWorld272*)sample;
	(void)data;
}
void HelloWorld273_cb(void *sample)
{
	HelloWorld273 *data = (HelloWorld273*)sample;
	(void)data;
}
void HelloWorld274_cb(void *sample)
{
	HelloWorld274 *data = (HelloWorld274*)sample;
	(void)data;
}
void HelloWorld275_cb(void *sample)
{
	HelloWorld275 *data = (HelloWorld275*)sample;
	(void)data;
}
void HelloWorld276_cb(void *sample)
{
	HelloWorld276 *data = (HelloWorld276*)sample;
	(void)data;
}
void HelloWorld277_cb(void *sample)
{
	HelloWorld277 *data = (HelloWorld277*)sample;
	(void)data;
}
void HelloWorld278_cb(void *sample)
{
	HelloWorld278 *data = (HelloWorld278*)sample;
	(void)data;
}
void HelloWorld279_cb(void *sample)
{
	HelloWorld279 *data = (HelloWorld279*)sample;
	(void)data;
}
void HelloWorld280_cb(void *sample)
{
	HelloWorld280 *data = (HelloWorld280*)sample;
	(void)data;
}
void HelloWorld281_cb(void *sample)
{
	HelloWorld281 *data = (HelloWorld281*)sample;
	(void)data;
}
void HelloWorld282_cb(void *sample)
{
	HelloWorld282 *data = (HelloWorld282*)sample;
	(void)data;
}
void HelloWorld283_cb(void *sample)
{
	HelloWorld283 *data = (HelloWorld283*)sample;
	(void)data;
}
void HelloWorld284_cb(void *sample)
{
	HelloWorld284 *data = (HelloWorld284*)sample;
	(void)data;
}
void HelloWorld285_cb(void *sample)
{
	HelloWorld285 *data = (HelloWorld285*)sample;
	(void)data;
}
void HelloWorld286_cb(void *sample)
{
	HelloWorld286 *data = (HelloWorld286*)sample;
	(void)data;
}
void HelloWorld287_cb(void *sample)
{
	HelloWorld287 *data = (HelloWorld287*)sample;
	(void)data;
}
void HelloWorld288_cb(void *sample)
{
	HelloWorld288 *data = (HelloWorld288*)sample;
	(void)data;
}
void HelloWorld289_cb(void *sample)
{
	HelloWorld289 *data = (HelloWorld289*)sample;
	(void)data;
}
void HelloWorld290_cb(void *sample)
{
	HelloWorld290 *data = (HelloWorld290*)sample;
	(void)data;
}
void HelloWorld291_cb(void *sample)
{
	HelloWorld291 *data = (HelloWorld291*)sample;
	(void)data;
}
void HelloWorld292_cb(void *sample)
{
	HelloWorld292 *data = (HelloWorld292*)sample;
	(void)data;
}
void HelloWorld293_cb(void *sample)
{
	HelloWorld293 *data = (HelloWorld293*)sample;
	(void)data;
}
void HelloWorld294_cb(void *sample)
{
	HelloWorld294 *data = (HelloWorld294*)sample;
	(void)data;
}
void HelloWorld295_cb(void *sample)
{
	HelloWorld295 *data = (HelloWorld295*)sample;
	(void)data;
}
void HelloWorld296_cb(void *sample)
{
	HelloWorld296 *data = (HelloWorld296*)sample;
	(void)data;
}
void HelloWorld297_cb(void *sample)
{
	HelloWorld297 *data = (HelloWorld297*)sample;
	(void)data;
}
void HelloWorld298_cb(void *sample)
{
	HelloWorld298 *data = (HelloWorld298*)sample;
	(void)data;
}
void HelloWorld299_cb(void *sample)
{
	HelloWorld299 *data = (HelloWorld299*)sample;
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
		READER_META_INFO(HelloWorld151, HelloWorld151, HelloWorld151_cb, 100),
		READER_META_INFO(HelloWorld152, HelloWorld152, HelloWorld152_cb, 100),
		READER_META_INFO(HelloWorld153, HelloWorld153, HelloWorld153_cb, 100),
		READER_META_INFO(HelloWorld154, HelloWorld154, HelloWorld154_cb, 100),
		READER_META_INFO(HelloWorld155, HelloWorld155, HelloWorld155_cb, 100),
		READER_META_INFO(HelloWorld156, HelloWorld156, HelloWorld156_cb, 100),
		READER_META_INFO(HelloWorld157, HelloWorld157, HelloWorld157_cb, 100),
		READER_META_INFO(HelloWorld158, HelloWorld158, HelloWorld158_cb, 100),
		READER_META_INFO(HelloWorld159, HelloWorld159, HelloWorld159_cb, 100),
		READER_META_INFO(HelloWorld160, HelloWorld160, HelloWorld160_cb, 100),
		READER_META_INFO(HelloWorld161, HelloWorld161, HelloWorld161_cb, 100),
		READER_META_INFO(HelloWorld162, HelloWorld162, HelloWorld162_cb, 100),
		READER_META_INFO(HelloWorld163, HelloWorld163, HelloWorld163_cb, 100),
		READER_META_INFO(HelloWorld164, HelloWorld164, HelloWorld164_cb, 100),
		READER_META_INFO(HelloWorld165, HelloWorld165, HelloWorld165_cb, 100),
		READER_META_INFO(HelloWorld166, HelloWorld166, HelloWorld166_cb, 100),
		READER_META_INFO(HelloWorld167, HelloWorld167, HelloWorld167_cb, 100),
		READER_META_INFO(HelloWorld168, HelloWorld168, HelloWorld168_cb, 100),
		READER_META_INFO(HelloWorld169, HelloWorld169, HelloWorld169_cb, 100),
		READER_META_INFO(HelloWorld170, HelloWorld170, HelloWorld170_cb, 100),
		READER_META_INFO(HelloWorld171, HelloWorld171, HelloWorld171_cb, 100),
		READER_META_INFO(HelloWorld172, HelloWorld172, HelloWorld172_cb, 100),
		READER_META_INFO(HelloWorld173, HelloWorld173, HelloWorld173_cb, 100),
		READER_META_INFO(HelloWorld174, HelloWorld174, HelloWorld174_cb, 100),
		READER_META_INFO(HelloWorld175, HelloWorld175, HelloWorld175_cb, 100),
		READER_META_INFO(HelloWorld176, HelloWorld176, HelloWorld176_cb, 100),
		READER_META_INFO(HelloWorld177, HelloWorld177, HelloWorld177_cb, 100),
		READER_META_INFO(HelloWorld178, HelloWorld178, HelloWorld178_cb, 100),
		READER_META_INFO(HelloWorld179, HelloWorld179, HelloWorld179_cb, 100),
		READER_META_INFO(HelloWorld180, HelloWorld180, HelloWorld180_cb, 100),
		READER_META_INFO(HelloWorld181, HelloWorld181, HelloWorld181_cb, 100),
		READER_META_INFO(HelloWorld182, HelloWorld182, HelloWorld182_cb, 100),
		READER_META_INFO(HelloWorld183, HelloWorld183, HelloWorld183_cb, 100),
		READER_META_INFO(HelloWorld184, HelloWorld184, HelloWorld184_cb, 100),
		READER_META_INFO(HelloWorld185, HelloWorld185, HelloWorld185_cb, 100),
		READER_META_INFO(HelloWorld186, HelloWorld186, HelloWorld186_cb, 100),
		READER_META_INFO(HelloWorld187, HelloWorld187, HelloWorld187_cb, 100),
		READER_META_INFO(HelloWorld188, HelloWorld188, HelloWorld188_cb, 100),
		READER_META_INFO(HelloWorld189, HelloWorld189, HelloWorld189_cb, 100),
		READER_META_INFO(HelloWorld190, HelloWorld190, HelloWorld190_cb, 100),
		READER_META_INFO(HelloWorld191, HelloWorld191, HelloWorld191_cb, 100),
		READER_META_INFO(HelloWorld192, HelloWorld192, HelloWorld192_cb, 100),
		READER_META_INFO(HelloWorld193, HelloWorld193, HelloWorld193_cb, 100),
		READER_META_INFO(HelloWorld194, HelloWorld194, HelloWorld194_cb, 100),
		READER_META_INFO(HelloWorld195, HelloWorld195, HelloWorld195_cb, 100),
		READER_META_INFO(HelloWorld196, HelloWorld196, HelloWorld196_cb, 100),
		READER_META_INFO(HelloWorld197, HelloWorld197, HelloWorld197_cb, 100),
		READER_META_INFO(HelloWorld198, HelloWorld198, HelloWorld198_cb, 100),
		READER_META_INFO(HelloWorld199, HelloWorld199, HelloWorld199_cb, 100),
		READER_META_INFO(HelloWorld200, HelloWorld200, HelloWorld200_cb, 100),
		READER_META_INFO(HelloWorld201, HelloWorld201, HelloWorld201_cb, 100),
		READER_META_INFO(HelloWorld202, HelloWorld202, HelloWorld202_cb, 100),
		READER_META_INFO(HelloWorld203, HelloWorld203, HelloWorld203_cb, 100),
		READER_META_INFO(HelloWorld204, HelloWorld204, HelloWorld204_cb, 100),
		READER_META_INFO(HelloWorld205, HelloWorld205, HelloWorld205_cb, 100),
		READER_META_INFO(HelloWorld206, HelloWorld206, HelloWorld206_cb, 100),
		READER_META_INFO(HelloWorld207, HelloWorld207, HelloWorld207_cb, 100),
		READER_META_INFO(HelloWorld208, HelloWorld208, HelloWorld208_cb, 100),
		READER_META_INFO(HelloWorld209, HelloWorld209, HelloWorld209_cb, 100),
		READER_META_INFO(HelloWorld210, HelloWorld210, HelloWorld210_cb, 100),
		READER_META_INFO(HelloWorld211, HelloWorld211, HelloWorld211_cb, 100),
		READER_META_INFO(HelloWorld212, HelloWorld212, HelloWorld212_cb, 100),
		READER_META_INFO(HelloWorld213, HelloWorld213, HelloWorld213_cb, 100),
		READER_META_INFO(HelloWorld214, HelloWorld214, HelloWorld214_cb, 100),
		READER_META_INFO(HelloWorld215, HelloWorld215, HelloWorld215_cb, 100),
		READER_META_INFO(HelloWorld216, HelloWorld216, HelloWorld216_cb, 100),
		READER_META_INFO(HelloWorld217, HelloWorld217, HelloWorld217_cb, 100),
		READER_META_INFO(HelloWorld218, HelloWorld218, HelloWorld218_cb, 100),
		READER_META_INFO(HelloWorld219, HelloWorld219, HelloWorld219_cb, 100),
		READER_META_INFO(HelloWorld220, HelloWorld220, HelloWorld220_cb, 100),
		READER_META_INFO(HelloWorld221, HelloWorld221, HelloWorld221_cb, 100),
		READER_META_INFO(HelloWorld222, HelloWorld222, HelloWorld222_cb, 100),
		READER_META_INFO(HelloWorld223, HelloWorld223, HelloWorld223_cb, 100),
		READER_META_INFO(HelloWorld224, HelloWorld224, HelloWorld224_cb, 100),
		READER_META_INFO(HelloWorld225, HelloWorld225, HelloWorld225_cb, 100),
		READER_META_INFO(HelloWorld226, HelloWorld226, HelloWorld226_cb, 100),
		READER_META_INFO(HelloWorld227, HelloWorld227, HelloWorld227_cb, 100),
		READER_META_INFO(HelloWorld228, HelloWorld228, HelloWorld228_cb, 100),
		READER_META_INFO(HelloWorld229, HelloWorld229, HelloWorld229_cb, 100),
		READER_META_INFO(HelloWorld230, HelloWorld230, HelloWorld230_cb, 100),
		READER_META_INFO(HelloWorld231, HelloWorld231, HelloWorld231_cb, 100),
		READER_META_INFO(HelloWorld232, HelloWorld232, HelloWorld232_cb, 100),
		READER_META_INFO(HelloWorld233, HelloWorld233, HelloWorld233_cb, 100),
		READER_META_INFO(HelloWorld234, HelloWorld234, HelloWorld234_cb, 100),
		READER_META_INFO(HelloWorld235, HelloWorld235, HelloWorld235_cb, 100),
		READER_META_INFO(HelloWorld236, HelloWorld236, HelloWorld236_cb, 100),
		READER_META_INFO(HelloWorld237, HelloWorld237, HelloWorld237_cb, 100),
		READER_META_INFO(HelloWorld238, HelloWorld238, HelloWorld238_cb, 100),
		READER_META_INFO(HelloWorld239, HelloWorld239, HelloWorld239_cb, 100),
		READER_META_INFO(HelloWorld240, HelloWorld240, HelloWorld240_cb, 100),
		READER_META_INFO(HelloWorld241, HelloWorld241, HelloWorld241_cb, 100),
		READER_META_INFO(HelloWorld242, HelloWorld242, HelloWorld242_cb, 100),
		READER_META_INFO(HelloWorld243, HelloWorld243, HelloWorld243_cb, 100),
		READER_META_INFO(HelloWorld244, HelloWorld244, HelloWorld244_cb, 100),
		READER_META_INFO(HelloWorld245, HelloWorld245, HelloWorld245_cb, 100),
		READER_META_INFO(HelloWorld246, HelloWorld246, HelloWorld246_cb, 100),
		READER_META_INFO(HelloWorld247, HelloWorld247, HelloWorld247_cb, 100),
		READER_META_INFO(HelloWorld248, HelloWorld248, HelloWorld248_cb, 100),
		READER_META_INFO(HelloWorld249, HelloWorld249, HelloWorld249_cb, 100),
		READER_META_INFO(HelloWorld250, HelloWorld250, HelloWorld250_cb, 100),
		READER_META_INFO(HelloWorld251, HelloWorld251, HelloWorld251_cb, 100),
		READER_META_INFO(HelloWorld252, HelloWorld252, HelloWorld252_cb, 100),
		READER_META_INFO(HelloWorld253, HelloWorld253, HelloWorld253_cb, 100),
		READER_META_INFO(HelloWorld254, HelloWorld254, HelloWorld254_cb, 100),
		READER_META_INFO(HelloWorld255, HelloWorld255, HelloWorld255_cb, 100),
		READER_META_INFO(HelloWorld256, HelloWorld256, HelloWorld256_cb, 100),
		READER_META_INFO(HelloWorld257, HelloWorld257, HelloWorld257_cb, 100),
		READER_META_INFO(HelloWorld258, HelloWorld258, HelloWorld258_cb, 100),
		READER_META_INFO(HelloWorld259, HelloWorld259, HelloWorld259_cb, 100),
		READER_META_INFO(HelloWorld260, HelloWorld260, HelloWorld260_cb, 100),
		READER_META_INFO(HelloWorld261, HelloWorld261, HelloWorld261_cb, 100),
		READER_META_INFO(HelloWorld262, HelloWorld262, HelloWorld262_cb, 100),
		READER_META_INFO(HelloWorld263, HelloWorld263, HelloWorld263_cb, 100),
		READER_META_INFO(HelloWorld264, HelloWorld264, HelloWorld264_cb, 100),
		READER_META_INFO(HelloWorld265, HelloWorld265, HelloWorld265_cb, 100),
		READER_META_INFO(HelloWorld266, HelloWorld266, HelloWorld266_cb, 100),
		READER_META_INFO(HelloWorld267, HelloWorld267, HelloWorld267_cb, 100),
		READER_META_INFO(HelloWorld268, HelloWorld268, HelloWorld268_cb, 100),
		READER_META_INFO(HelloWorld269, HelloWorld269, HelloWorld269_cb, 100),
		READER_META_INFO(HelloWorld270, HelloWorld270, HelloWorld270_cb, 100),
		READER_META_INFO(HelloWorld271, HelloWorld271, HelloWorld271_cb, 100),
		READER_META_INFO(HelloWorld272, HelloWorld272, HelloWorld272_cb, 100),
		READER_META_INFO(HelloWorld273, HelloWorld273, HelloWorld273_cb, 100),
		READER_META_INFO(HelloWorld274, HelloWorld274, HelloWorld274_cb, 100),
		READER_META_INFO(HelloWorld275, HelloWorld275, HelloWorld275_cb, 100),
		READER_META_INFO(HelloWorld276, HelloWorld276, HelloWorld276_cb, 100),
		READER_META_INFO(HelloWorld277, HelloWorld277, HelloWorld277_cb, 100),
		READER_META_INFO(HelloWorld278, HelloWorld278, HelloWorld278_cb, 100),
		READER_META_INFO(HelloWorld279, HelloWorld279, HelloWorld279_cb, 100),
		READER_META_INFO(HelloWorld280, HelloWorld280, HelloWorld280_cb, 100),
		READER_META_INFO(HelloWorld281, HelloWorld281, HelloWorld281_cb, 100),
		READER_META_INFO(HelloWorld282, HelloWorld282, HelloWorld282_cb, 100),
		READER_META_INFO(HelloWorld283, HelloWorld283, HelloWorld283_cb, 100),
		READER_META_INFO(HelloWorld284, HelloWorld284, HelloWorld284_cb, 100),
		READER_META_INFO(HelloWorld285, HelloWorld285, HelloWorld285_cb, 100),
		READER_META_INFO(HelloWorld286, HelloWorld286, HelloWorld286_cb, 100),
		READER_META_INFO(HelloWorld287, HelloWorld287, HelloWorld287_cb, 100),
		READER_META_INFO(HelloWorld288, HelloWorld288, HelloWorld288_cb, 100),
		READER_META_INFO(HelloWorld289, HelloWorld289, HelloWorld289_cb, 100),
		READER_META_INFO(HelloWorld290, HelloWorld290, HelloWorld290_cb, 100),
		READER_META_INFO(HelloWorld291, HelloWorld291, HelloWorld291_cb, 100),
		READER_META_INFO(HelloWorld292, HelloWorld292, HelloWorld292_cb, 100),
		READER_META_INFO(HelloWorld293, HelloWorld293, HelloWorld293_cb, 100),
		READER_META_INFO(HelloWorld294, HelloWorld294, HelloWorld294_cb, 100),
		READER_META_INFO(HelloWorld295, HelloWorld295, HelloWorld295_cb, 100),
		READER_META_INFO(HelloWorld296, HelloWorld296, HelloWorld296_cb, 100),
		READER_META_INFO(HelloWorld297, HelloWorld297, HelloWorld297_cb, 100),
		READER_META_INFO(HelloWorld298, HelloWorld298, HelloWorld298_cb, 100),
		READER_META_INFO(HelloWorld299, HelloWorld299, HelloWorld299_cb, 100),
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

static void time_event(Rte_Dds_Reader r);

void Rte_Dds_RxIndication(Rte_Dds_Reader r, Rte_Dds_Instance inst)
{
	(void)inst;

	struct reader_meta_info 	*info;
	Rte_Dds_TopicData			data;
	static struct sample_info 	Sample_info;
	const char * topic_name;

	topic_name = reader_get_topicname(r);
	if (!strcmp(topic_name,"domain_0_topic_1Topic")) {
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
	writer_topic_index(HelloWorld1),
	writer_topic_index(HelloWorld2),
	writer_topic_index(HelloWorld3),
	writer_topic_index(HelloWorld4),
	writer_topic_index(HelloWorld5),
	writer_topic_index(HelloWorld6),
	writer_topic_index(HelloWorld7),
	writer_topic_index(HelloWorld8),
	writer_topic_index(HelloWorld9),
	writer_topic_index(HelloWorld10),
	writer_topic_index(HelloWorld11),
	writer_topic_index(HelloWorld12),
	writer_topic_index(HelloWorld13),
	writer_topic_index(HelloWorld14),
	writer_topic_index(HelloWorld15),
	writer_topic_index(HelloWorld16),
	writer_topic_index(HelloWorld17),
	writer_topic_index(HelloWorld18),
	writer_topic_index(HelloWorld19),
	writer_topic_index(HelloWorld20),
	writer_topic_index(HelloWorld21),
	writer_topic_index(HelloWorld22),
	writer_topic_index(HelloWorld23),
	writer_topic_index(HelloWorld24),
	writer_topic_index(HelloWorld25),
	writer_topic_index(HelloWorld26),
	writer_topic_index(HelloWorld27),
	writer_topic_index(HelloWorld28),
	writer_topic_index(HelloWorld29),
	writer_topic_index(HelloWorld30),
	writer_topic_index(HelloWorld31),
	writer_topic_index(HelloWorld32),
	writer_topic_index(HelloWorld33),
	writer_topic_index(HelloWorld34),
	writer_topic_index(HelloWorld35),
	writer_topic_index(HelloWorld36),
	writer_topic_index(HelloWorld37),
	writer_topic_index(HelloWorld38),
	writer_topic_index(HelloWorld39),
	writer_topic_index(HelloWorld40),
	writer_topic_index(HelloWorld41),
	writer_topic_index(HelloWorld42),
	writer_topic_index(HelloWorld43),
	writer_topic_index(HelloWorld44),
	writer_topic_index(HelloWorld45),
	writer_topic_index(HelloWorld46),
	writer_topic_index(HelloWorld47),
	writer_topic_index(HelloWorld48),
	writer_topic_index(HelloWorld49),
	writer_topic_index(HelloWorld50),
	writer_topic_index(HelloWorld51),
	writer_topic_index(HelloWorld52),
	writer_topic_index(HelloWorld53),
	writer_topic_index(HelloWorld54),
	writer_topic_index(HelloWorld55),
	writer_topic_index(HelloWorld56),
	writer_topic_index(HelloWorld57),
	writer_topic_index(HelloWorld58),
	writer_topic_index(HelloWorld59),
	writer_topic_index(HelloWorld60),
	writer_topic_index(HelloWorld61),
	writer_topic_index(HelloWorld62),
	writer_topic_index(HelloWorld63),
	writer_topic_index(HelloWorld64),
	writer_topic_index(HelloWorld65),
	writer_topic_index(HelloWorld66),
	writer_topic_index(HelloWorld67),
	writer_topic_index(HelloWorld68),
	writer_topic_index(HelloWorld69),
	writer_topic_index(HelloWorld70),
	writer_topic_index(HelloWorld71),
	writer_topic_index(HelloWorld72),
	writer_topic_index(HelloWorld73),
	writer_topic_index(HelloWorld74),
	writer_topic_index(HelloWorld75),
	writer_topic_index(HelloWorld76),
	writer_topic_index(HelloWorld77),
	writer_topic_index(HelloWorld78),
	writer_topic_index(HelloWorld79),
	writer_topic_index(HelloWorld80),
	writer_topic_index(HelloWorld81),
	writer_topic_index(HelloWorld82),
	writer_topic_index(HelloWorld83),
	writer_topic_index(HelloWorld84),
	writer_topic_index(HelloWorld85),
	writer_topic_index(HelloWorld86),
	writer_topic_index(HelloWorld87),
	writer_topic_index(HelloWorld88),
	writer_topic_index(HelloWorld89),
	writer_topic_index(HelloWorld90),
	writer_topic_index(HelloWorld91),
	writer_topic_index(HelloWorld92),
	writer_topic_index(HelloWorld93),
	writer_topic_index(HelloWorld94),
	writer_topic_index(HelloWorld95),
	writer_topic_index(HelloWorld96),
	writer_topic_index(HelloWorld97),
	writer_topic_index(HelloWorld98),
	writer_topic_index(HelloWorld99),
	writer_topic_index(HelloWorld100),
	writer_topic_index(HelloWorld101),
	writer_topic_index(HelloWorld102),
	writer_topic_index(HelloWorld103),
	writer_topic_index(HelloWorld104),
	writer_topic_index(HelloWorld105),
	writer_topic_index(HelloWorld106),
	writer_topic_index(HelloWorld107),
	writer_topic_index(HelloWorld108),
	writer_topic_index(HelloWorld109),
	writer_topic_index(HelloWorld110),
	writer_topic_index(HelloWorld111),
	writer_topic_index(HelloWorld112),
	writer_topic_index(HelloWorld113),
	writer_topic_index(HelloWorld114),
	writer_topic_index(HelloWorld115),
	writer_topic_index(HelloWorld116),
	writer_topic_index(HelloWorld117),
	writer_topic_index(HelloWorld118),
	writer_topic_index(HelloWorld119),
	writer_topic_index(HelloWorld120),
	writer_topic_index(HelloWorld121),
	writer_topic_index(HelloWorld122),
	writer_topic_index(HelloWorld123),
	writer_topic_index(HelloWorld124),
	writer_topic_index(HelloWorld125),
	writer_topic_index(HelloWorld126),
	writer_topic_index(HelloWorld127),
	writer_topic_index(HelloWorld128),
	writer_topic_index(HelloWorld129),
	writer_topic_index(HelloWorld130),
	writer_topic_index(HelloWorld131),
	writer_topic_index(HelloWorld132),
	writer_topic_index(HelloWorld133),
	writer_topic_index(HelloWorld134),
	writer_topic_index(HelloWorld135),
	writer_topic_index(HelloWorld136),
	writer_topic_index(HelloWorld137),
	writer_topic_index(HelloWorld138),
	writer_topic_index(HelloWorld139),
	writer_topic_index(HelloWorld140),
	writer_topic_index(HelloWorld141),
	writer_topic_index(HelloWorld142),
	writer_topic_index(HelloWorld143),
	writer_topic_index(HelloWorld144),
	writer_topic_index(HelloWorld145),
	writer_topic_index(HelloWorld146),
	writer_topic_index(HelloWorld147),
	writer_topic_index(HelloWorld148),
	writer_topic_index(HelloWorld149),
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
	WRITER_META_INFO(HelloWorld1, HelloWorld1, 402),
	WRITER_META_INFO(HelloWorld2, HelloWorld2, 409),
	WRITER_META_INFO(HelloWorld3, HelloWorld3, 416),
	WRITER_META_INFO(HelloWorld4, HelloWorld4, 423),
	WRITER_META_INFO(HelloWorld5, HelloWorld5, 430),
	WRITER_META_INFO(HelloWorld6, HelloWorld6, 437),
	WRITER_META_INFO(HelloWorld7, HelloWorld7, 444),
	WRITER_META_INFO(HelloWorld8, HelloWorld8, 451),
	WRITER_META_INFO(HelloWorld9, HelloWorld9, 458),
	WRITER_META_INFO(HelloWorld10, HelloWorld10, 465),
	WRITER_META_INFO(HelloWorld11, HelloWorld11, 472),
	WRITER_META_INFO(HelloWorld12, HelloWorld12, 479),
	WRITER_META_INFO(HelloWorld13, HelloWorld13, 486),
	WRITER_META_INFO(HelloWorld14, HelloWorld14, 493),
	WRITER_META_INFO(HelloWorld15, HelloWorld15, 500),
	WRITER_META_INFO(HelloWorld16, HelloWorld16, 507),
	WRITER_META_INFO(HelloWorld17, HelloWorld17, 514),
	WRITER_META_INFO(HelloWorld18, HelloWorld18, 521),
	WRITER_META_INFO(HelloWorld19, HelloWorld19, 528),
	WRITER_META_INFO(HelloWorld20, HelloWorld20, 535),
	WRITER_META_INFO(HelloWorld21, HelloWorld21, 542),
	WRITER_META_INFO(HelloWorld22, HelloWorld22, 549),
	WRITER_META_INFO(HelloWorld23, HelloWorld23, 556),
	WRITER_META_INFO(HelloWorld24, HelloWorld24, 563),
	WRITER_META_INFO(HelloWorld25, HelloWorld25, 570),
	WRITER_META_INFO(HelloWorld26, HelloWorld26, 577),
	WRITER_META_INFO(HelloWorld27, HelloWorld27, 584),
	WRITER_META_INFO(HelloWorld28, HelloWorld28, 591),
	WRITER_META_INFO(HelloWorld29, HelloWorld29, 598),
	WRITER_META_INFO(HelloWorld30, HelloWorld30, 605),
	WRITER_META_INFO(HelloWorld31, HelloWorld31, 612),
	WRITER_META_INFO(HelloWorld32, HelloWorld32, 619),
	WRITER_META_INFO(HelloWorld33, HelloWorld33, 626),
	WRITER_META_INFO(HelloWorld34, HelloWorld34, 633),
	WRITER_META_INFO(HelloWorld35, HelloWorld35, 640),
	WRITER_META_INFO(HelloWorld36, HelloWorld36, 647),
	WRITER_META_INFO(HelloWorld37, HelloWorld37, 654),
	WRITER_META_INFO(HelloWorld38, HelloWorld38, 661),
	WRITER_META_INFO(HelloWorld39, HelloWorld39, 668),
	WRITER_META_INFO(HelloWorld40, HelloWorld40, 675),
	WRITER_META_INFO(HelloWorld41, HelloWorld41, 682),
	WRITER_META_INFO(HelloWorld42, HelloWorld42, 689),
	WRITER_META_INFO(HelloWorld43, HelloWorld43, 696),
	WRITER_META_INFO(HelloWorld44, HelloWorld44, 703),
	WRITER_META_INFO(HelloWorld45, HelloWorld45, 710),
	WRITER_META_INFO(HelloWorld46, HelloWorld46, 717),
	WRITER_META_INFO(HelloWorld47, HelloWorld47, 724),
	WRITER_META_INFO(HelloWorld48, HelloWorld48, 731),
	WRITER_META_INFO(HelloWorld49, HelloWorld49, 738),
	WRITER_META_INFO(HelloWorld50, HelloWorld50, 745),
	WRITER_META_INFO(HelloWorld51, HelloWorld51, 752),
	WRITER_META_INFO(HelloWorld52, HelloWorld52, 759),
	WRITER_META_INFO(HelloWorld53, HelloWorld53, 766),
	WRITER_META_INFO(HelloWorld54, HelloWorld54, 773),
	WRITER_META_INFO(HelloWorld55, HelloWorld55, 780),
	WRITER_META_INFO(HelloWorld56, HelloWorld56, 787),
	WRITER_META_INFO(HelloWorld57, HelloWorld57, 794),
	WRITER_META_INFO(HelloWorld58, HelloWorld58, 801),
	WRITER_META_INFO(HelloWorld59, HelloWorld59, 808),
	WRITER_META_INFO(HelloWorld60, HelloWorld60, 815),
	WRITER_META_INFO(HelloWorld61, HelloWorld61, 822),
	WRITER_META_INFO(HelloWorld62, HelloWorld62, 829),
	WRITER_META_INFO(HelloWorld63, HelloWorld63, 836),
	WRITER_META_INFO(HelloWorld64, HelloWorld64, 843),
	WRITER_META_INFO(HelloWorld65, HelloWorld65, 850),
	WRITER_META_INFO(HelloWorld66, HelloWorld66, 857),
	WRITER_META_INFO(HelloWorld67, HelloWorld67, 864),
	WRITER_META_INFO(HelloWorld68, HelloWorld68, 871),
	WRITER_META_INFO(HelloWorld69, HelloWorld69, 878),
	WRITER_META_INFO(HelloWorld70, HelloWorld70, 885),
	WRITER_META_INFO(HelloWorld71, HelloWorld71, 892),
	WRITER_META_INFO(HelloWorld72, HelloWorld72, 899),
	WRITER_META_INFO(HelloWorld73, HelloWorld73, 906),
	WRITER_META_INFO(HelloWorld74, HelloWorld74, 913),
	WRITER_META_INFO(HelloWorld75, HelloWorld75, 920),
	WRITER_META_INFO(HelloWorld76, HelloWorld76, 927),
	WRITER_META_INFO(HelloWorld77, HelloWorld77, 934),
	WRITER_META_INFO(HelloWorld78, HelloWorld78, 941),
	WRITER_META_INFO(HelloWorld79, HelloWorld79, 948),
	WRITER_META_INFO(HelloWorld80, HelloWorld80, 955),
	WRITER_META_INFO(HelloWorld81, HelloWorld81, 962),
	WRITER_META_INFO(HelloWorld82, HelloWorld82, 969),
	WRITER_META_INFO(HelloWorld83, HelloWorld83, 976),
	WRITER_META_INFO(HelloWorld84, HelloWorld84, 983),
	WRITER_META_INFO(HelloWorld85, HelloWorld85, 990),
	WRITER_META_INFO(HelloWorld86, HelloWorld86, 997),
	WRITER_META_INFO(HelloWorld87, HelloWorld87, 1004),
	WRITER_META_INFO(HelloWorld88, HelloWorld88, 1011),
	WRITER_META_INFO(HelloWorld89, HelloWorld89, 1018),
	WRITER_META_INFO(HelloWorld90, HelloWorld90, 1025),
	WRITER_META_INFO(HelloWorld91, HelloWorld91, 1032),
	WRITER_META_INFO(HelloWorld92, HelloWorld92, 1039),
	WRITER_META_INFO(HelloWorld93, HelloWorld93, 1046),
	WRITER_META_INFO(HelloWorld94, HelloWorld94, 1053),
	WRITER_META_INFO(HelloWorld95, HelloWorld95, 1060),
	WRITER_META_INFO(HelloWorld96, HelloWorld96, 1067),
	WRITER_META_INFO(HelloWorld97, HelloWorld97, 1074),
	WRITER_META_INFO(HelloWorld98, HelloWorld98, 1081),
	WRITER_META_INFO(HelloWorld99, HelloWorld99, 1088),
	WRITER_META_INFO(HelloWorld100, HelloWorld100, 1095),
	WRITER_META_INFO(HelloWorld101, HelloWorld101, 1102),
	WRITER_META_INFO(HelloWorld102, HelloWorld102, 1109),
	WRITER_META_INFO(HelloWorld103, HelloWorld103, 1116),
	WRITER_META_INFO(HelloWorld104, HelloWorld104, 1123),
	WRITER_META_INFO(HelloWorld105, HelloWorld105, 1130),
	WRITER_META_INFO(HelloWorld106, HelloWorld106, 1137),
	WRITER_META_INFO(HelloWorld107, HelloWorld107, 1144),
	WRITER_META_INFO(HelloWorld108, HelloWorld108, 1151),
	WRITER_META_INFO(HelloWorld109, HelloWorld109, 1158),
	WRITER_META_INFO(HelloWorld110, HelloWorld110, 1165),
	WRITER_META_INFO(HelloWorld111, HelloWorld111, 1172),
	WRITER_META_INFO(HelloWorld112, HelloWorld112, 1179),
	WRITER_META_INFO(HelloWorld113, HelloWorld113, 1186),
	WRITER_META_INFO(HelloWorld114, HelloWorld114, 1193),
	WRITER_META_INFO(HelloWorld115, HelloWorld115, 1200),
	WRITER_META_INFO(HelloWorld116, HelloWorld116, 1207),
	WRITER_META_INFO(HelloWorld117, HelloWorld117, 1214),
	WRITER_META_INFO(HelloWorld118, HelloWorld118, 1221),
	WRITER_META_INFO(HelloWorld119, HelloWorld119, 1228),
	WRITER_META_INFO(HelloWorld120, HelloWorld120, 1235),
	WRITER_META_INFO(HelloWorld121, HelloWorld121, 1242),
	WRITER_META_INFO(HelloWorld122, HelloWorld122, 1249),
	WRITER_META_INFO(HelloWorld123, HelloWorld123, 1256),
	WRITER_META_INFO(HelloWorld124, HelloWorld124, 1263),
	WRITER_META_INFO(HelloWorld125, HelloWorld125, 1270),
	WRITER_META_INFO(HelloWorld126, HelloWorld126, 1277),
	WRITER_META_INFO(HelloWorld127, HelloWorld127, 1284),
	WRITER_META_INFO(HelloWorld128, HelloWorld128, 1291),
	WRITER_META_INFO(HelloWorld129, HelloWorld129, 1298),
	WRITER_META_INFO(HelloWorld130, HelloWorld130, 1305),
	WRITER_META_INFO(HelloWorld131, HelloWorld131, 1312),
	WRITER_META_INFO(HelloWorld132, HelloWorld132, 1319),
	WRITER_META_INFO(HelloWorld133, HelloWorld133, 1326),
	WRITER_META_INFO(HelloWorld134, HelloWorld134, 1333),
	WRITER_META_INFO(HelloWorld135, HelloWorld135, 1340),
	WRITER_META_INFO(HelloWorld136, HelloWorld136, 1347),
	WRITER_META_INFO(HelloWorld137, HelloWorld137, 1354),
	WRITER_META_INFO(HelloWorld138, HelloWorld138, 1361),
	WRITER_META_INFO(HelloWorld139, HelloWorld139, 1368),
	WRITER_META_INFO(HelloWorld140, HelloWorld140, 1375),
	WRITER_META_INFO(HelloWorld141, HelloWorld141, 1382),
	WRITER_META_INFO(HelloWorld142, HelloWorld142, 1389),
	WRITER_META_INFO(HelloWorld143, HelloWorld143, 1396),
	WRITER_META_INFO(HelloWorld144, HelloWorld144, 1403),
	WRITER_META_INFO(HelloWorld145, HelloWorld145, 1410),
	WRITER_META_INFO(HelloWorld146, HelloWorld146, 1417),
	WRITER_META_INFO(HelloWorld147, HelloWorld147, 1424),
	WRITER_META_INFO(HelloWorld148, HelloWorld148, 1431),
	WRITER_META_INFO(HelloWorld149, HelloWorld149, 1438),
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
				best_phase	= d;
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
	Rte_Dds_TopicData		data;

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

	static int loop_cnt;

	if (++loop_cnt >= EVENT_CYCLE_MS / MVBS_LOOP_CYCLE_MS) {
		loop_cnt = 0;
		ret = on_event0();
	} else {
		ret = MVBS_TEST_CONTINUE;
	}

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
	}else {
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
	w = Rte_Dds_GetWriter(ptcp, topic_w.name);


	AgentHelloWorld_init(&sample2);
	Rte_Dds_PackData(&data_r, &sample2);
	pr_warn("topic_r.name:%s",topic_r.name);
	r = Rte_Dds_GetReader(ptcp, topic_r.name);
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

