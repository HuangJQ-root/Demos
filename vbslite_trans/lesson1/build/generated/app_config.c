#include <mvbs/sections/start_sec_code.h>
#include <mvbs/sections/start_sec_bss.h>
#include <mvbs/sections/start_sec_const.h>
#include <mvbs/sections/start_sec_data.h>

#define __MVBS_CORE_SOURCE__

#include <mvbs/core.h>
#include <mvbs/mvbs.h>
#include <mvbs/rtps/message.h>
#include <mvbs/adapter/adapter.h>
#include <mvbs/rte/Rte_Dds_Adaptor.h>


static struct participant mvbs_ptcp;


#include "HelloWorldPlugin.h"

union union_of_all_topics {
	MVBS_HelloWorld __MVBS_HelloWorld;
};

extern const struct type_plugin MVBS_HelloWorld_typeplugin;



static uint8_t local_ringbuff[8192];

static const struct transport_info_local local_trans_info = {
	.buf_info		= {
		.buffer_size	= 8192,
		.buffer		= local_ringbuff,
	},
};
static const struct udp_info udp_info_list[] = {
	{
		.addr           = { 127, 0, 0, 1 },
		.mask           = { 255, 255, 255, 0 },
		.addr_uint32_le = 0x0100007F, /* 127.0.0.1 */
		.mask_uint32_le = 0x00FFFFFF, /* 255.255.255.0 */
	},
};

static uint8_t udp_ringbuff[32768];

static uint8_t udp_recv_buffer[MVBS_UDP_RXBUFSIZE];
static uint8_t udp_send_buffer[MVBS_UDP_TXBUFSIZE];

static const struct transport_info_udp udp_trans_info = {
	.buf_info		= {
		.buffer_size	= 32768,
		.buffer		= udp_ringbuff,
	},
	.rx_buf			= {
		.buffer_size	= MVBS_UDP_RXBUFSIZE,
		.buffer		= udp_recv_buffer,
	},
	.tx_buf			= {
		.buffer_size	= MVBS_UDP_TXBUFSIZE,
		.buffer		= udp_send_buffer,
	},
	.info_cnt		= 1,
	.info			= udp_info_list,
};

static const struct reader_attr mvbs_reader_attrs[] = {
	{
		.key	= "r1",
		.type	= &MVBS_HelloWorld_typeplugin,
		.ptcp	= &mvbs_ptcp,
		.ep_attr = {
			.topic_name		= "MVBS_topic1",
			.type			= &MVBS_HelloWorld_typeplugin,
			.agent_flag		= 0,
			.period_ms = 0,
			.qos = {
				.reliability_kind = BEST_EFFORT,
				.durability_kind = TRANSIENT_LOCAL,
				.ownership_kind = SHARED,
				.liveliness_kind = QOS_LIVE_AUTOMATIC,
				.history_kind = KEEP_LAST,
			},
			.history.depth = 5,
			.ownership_strength.value = 0,
			.liveliness = {
				.lease_duration = { 2147483647, 4294967295 },
				.announcement_period = { 1073741844, 974500000 },
			},
			.resource_limit = {
				.max_samples = 5,
				.max_instances = 1,
				.max_samples_per_instance = 5,
			},
			.lifespan.duration = { 2147483647, 4294967295 },
			.e2e = {
				.e2e_protection = false,
				
				.e2e_p04_min_data_length = 0,
				.e2e_p04_max_data_length = 4090,
				.e2e_p04_max_delta_counter = 10,
				.e2e_deadline_counter = 2,
                		.e2e_liveliness_lease_duration = { 0, 500000000 },
                		.e2e_liveliness_kind = QOS_LIVE_MANUAL_BY_TOPIC,
			},
			.deadline.duration	= { 2147483647, 4294967295 },
			.entity_id		= 1,
			.user_defined_id	= -1,
			.locator_selector	= 0,
			.backup_enabled		= false,
			.crc16_enabled		= false,
		},
		.listener	= {
			.on_data		= Rte_Dds_Reader_On_Data,
			.on_irq			= NULL,
			.on_matched		= Rte_Dds_Reader_On_Matched,
			.on_e2e_exception	= Rte_Dds_Reader_On_E2e_Exception,
		},
		.max_matched_writers = 2,
	},
};

static struct mvbs_reader_cache_change_eid_0 {
	struct mp_blk_hdr		hdr;
	struct reader_cache_change	cc;
	uint8_t				data[MVBS_HELLOWORLD_SIZE];
} mvbs_reader_history_eid_0[5];

static struct writer_proxy_pool_eid_0 {
	struct mp_blk_hdr	hdr;
	struct writer_proxy	proxy;
	ulong_t			bitmap[1]; /* depth = 5 */
} mvbs_writer_proxy_eid_0[2];

static struct reader mvbs_readers[] = {
	{
		.attr		= &mvbs_reader_attrs[0],
		.proxies	= {
			.mem_addr  = (void *)mvbs_writer_proxy_eid_0,
			.mem_size  = sizeof(mvbs_writer_proxy_eid_0),
			.blk_total = 2,
			.blk_free  = 2,
			.blk_size  = sizeof(mvbs_writer_proxy_eid_0[0]) - MP_BLK_HDR_SIZE,
		},
		.history	= {
			.cache_change	   = {
				.mem_addr  = (void *)mvbs_reader_history_eid_0,
				.mem_size  = sizeof(mvbs_reader_history_eid_0),
				.blk_total = 5,
				.blk_free  = 5,
				.blk_size  = sizeof(mvbs_reader_history_eid_0[0]) - MP_BLK_HDR_SIZE,
			},
		},
		.owner		= NULL,
		.lifespan_td	= TIMER_DESC_INVALID,
		.deadline_td	= TIMER_DESC_INVALID,
		.liveliness_td	= TIMER_DESC_INVALID,
		.listener	= NULL,
		.priv_data	= NULL,
	},
};



static const struct writer_attr mvbs_writer_attrs[] = {
	{
		.key	= "w1",
		.type	= &MVBS_HelloWorld_typeplugin,
		.ptcp	= &mvbs_ptcp,
		.ep_attr = {
			.topic_name		= "MVBS_topic1",
			.type			= &MVBS_HelloWorld_typeplugin,
			.agent_flag		= 0,
			.period_ms = 0,
			.qos = {
				.reliability_kind = BEST_EFFORT,
				.durability_kind = TRANSIENT_LOCAL,
				.ownership_kind = SHARED,
				.liveliness_kind = QOS_LIVE_AUTOMATIC,
				.history_kind = KEEP_LAST,
			},
			.history.depth = 5,
			.ownership_strength.value = 0,
			.liveliness = {
				.lease_duration = { 2147483647, 4294967295 },
				.announcement_period = { 1073741844, 974500000 },
			},
			.resource_limit = {
				.max_samples = 5,
				.max_instances = 1,
				.max_samples_per_instance = 5,
			},
			.lifespan.duration = { 2147483647, 4294967295 },
			.e2e = {
				.e2e_protection = false,
				
				.e2e_p04_min_data_length = 0,
				.e2e_p04_max_data_length = 4090,
				.e2e_p04_max_delta_counter = 10,
				.e2e_deadline_counter = 2,
                		.e2e_liveliness_lease_duration = { 0, 500000000 },
                		.e2e_liveliness_kind = QOS_LIVE_MANUAL_BY_TOPIC,
			},
			.deadline.duration	= { 2147483647, 4294967295 },
			.entity_id		= 1,
			.user_defined_id	= -1,
			.locator_selector	= 0,
			.backup_enabled		= false,
			.crc16_enabled		= false,
		},
		.listener	= {
			.on_matched		= Rte_Dds_Writer_On_Matched,
		},
		.max_matched_readers = 2,
		.enforce_unicast = false,
	},
};

static struct mvbs_writer_cache_change_eid_0 {
	struct mp_blk_hdr		hdr;
	struct writer_cache_change	cc;
	uint8_t				data[MVBS_HELLOWORLD_SIZE];
} mvbs_writer_history_eid_0[5];

static struct reader_proxy_pool_eid_0 {
	struct mp_blk_hdr	hdr;
	struct reader_proxy	proxy;
	ulong_t			bitmap[1]; /* depth = 5 */
} mvbs_reader_proxy_eid_0[2];

static struct writer mvbs_writers[] = {
	{
		.attr		= &mvbs_writer_attrs[0],
		.proxies	= {
			.mem_addr  = (void *)mvbs_reader_proxy_eid_0,
			.mem_size  = sizeof(mvbs_reader_proxy_eid_0),
			.blk_total = 2,
			.blk_free  = 2,
			.blk_size  = sizeof(mvbs_reader_proxy_eid_0[0]) - MP_BLK_HDR_SIZE,
		},
		.history	= {
			.cache_change	   = {
				.mem_addr  = (void *)mvbs_writer_history_eid_0,
				.mem_size  = sizeof(mvbs_writer_history_eid_0),
				.blk_total = 5,
				.blk_free  = 5,
				.blk_size  = sizeof(mvbs_writer_history_eid_0[0]) - MP_BLK_HDR_SIZE,
			},
		},
		.lifespan_td	= TIMER_DESC_INVALID,
		.deadline_td	= TIMER_DESC_INVALID,
		.liveliness_td	= TIMER_DESC_INVALID,
		.writer_status	= {
			.heartbeat_td	= TIMER_DESC_INVALID,
		},
		.listener	= NULL,
		.priv_data	= NULL,
	},
};



static const struct participant_attr mvbs_ptcp_attr = {
	.name		= "node_1_127.0.0.1",
	.domain_id	= 0,

	/* 1. Maximum number of each resource */
	.max_readers	= 1,
	.max_writers	= 1,
	.max_timers	= 13,
	.max_proxies	= 9,

	.max_topic_size = sizeof(union union_of_all_topics),

	/* 2. Configuration of Transport */
	.trans_info 	= {
		.local_comm	= &local_trans_info,
		.udp		= &udp_trans_info,
		.ipc_j6m 	= NULL,
	},

	/* 3. Configuration for Discovery */
	.discovery	= {
		.edp_type				= DYNAMIC_EDP,
		.lease_duration				= { 10, 0 },
		.lease_duration_announce_period		= { 5, 0 },
		.initial_announce_count			= 50,
		.initial_announce_period		= { 3, 0 },
		.hb_policy = {
			.heartbeats_per_max_samples	= 5,
			.period_sec			= 5,
			.period_msec			= 0,
		},
	},

	/* 4. Configuration of Endpoints */
	.static_reader_num	= 0,
	.static_reader_attrs	= NULL,
	.static_writer_num	= 0,
	.static_writer_attrs	= NULL,

	.reader_num		= 1,
	.reader_attrs		= mvbs_reader_attrs,
	.writer_num		= 1,
	.writer_attrs		= mvbs_writer_attrs,

	/* 5. Entities list */
	.readers		= mvbs_readers,
	.writers		= mvbs_writers,

	/* 6. Configuration of preferred remote participant list */
	.preferred_list_num	= 0,
	.preferred_list		= NULL,
};

static struct udp_transport	mvbs_transport;

static struct discovery_pdp pdp_template = {
	/* encapsulation options */
	/* const uint8_t SCHEME_PL_CDR_LE[2] = { 0x00, 0x03 }; */
	.encapsulation_kind		= {0x00, 0x03},
	.encapsulation_options		= 0,

	/* PID_PROTOCOL_VERSION */
	.protocol_version_pid		= PID_PROTOCOL_VERSION,
	.protocol_version_length	= 4,
	.protocol_version_major		= 2,
	.protocol_version_minor		= 3,
	.padding1			= 0,

	/* PID_VENDORID */
	.vendorid_pid			= PID_VENDORID,
	.vendorid_length		= 4,
	.vendorid_value		        = {MVBS_VENDOR_ID_HIGH, MVBS_VENDOR_ID_LOW},

	/* PID_BUILTIN_ENDPOINT_SET */
	.builtin_endpoint_set_pid	= PID_BUILTIN_ENDPOINT_SET,
	.builtin_endpoint_set_length	= 4,
	.builtin_endpoint_set_value	= DISC_BIE_PARTICIPANT_ANNOUNCER
					| DISC_BIE_PARTICIPANT_DETECTOR
					| DISC_BIE_PUBLICATION_ANNOUNCER
					| DISC_BIE_PUBLICATION_DETECTOR
					| DISC_BIE_SUBSCRIPTION_ANNOUNCER
					| DISC_BIE_SUBSCRIPTION_DETECTOR
					| BIE_PARTICIPANT_MESSAGE_DATA_READER
					| BIE_PARTICIPANT_MESSAGE_DATA_WRITER
					| DISC_BIE_DIAG_REQUEST_READER

#ifdef MVBS_DIAG_REQUEST_WRITER_ENABLE
					| DISC_BIE_DIAG_REQUEST_WRITER
#endif

#ifdef MVBS_DIAG_REPLY_READER_ENABLE
					| DISC_BIE_DIAG_REPLY_READER
#endif
					| DISC_BIE_DIAG_REPLY_WRITER

					,

	/* PID_MVBS_VERTION */
	.mvbs_version_pid		= PID_VBS_VERTION,
	.mvbs_version_length		= 4,
	.mvbs_version_value		= {MVBS_VERSION_MAJOR,
					   MVBS_VERSION_MINOR,
					   MVBS_VERSION_EXTRA,
					   MVBS_VERSION_PATCH},

	/* PID_PARTICIPANT_LEASE_DURATION */
	.ptcp_lease_duration_pid	= PID_PARTICIPANT_LEASE_DURATION,
	.ptcp_lease_duration_length	= 8,
	/* .ptcp_lease_duration_value	= ptcp->attr->discovery.lease_duration, */

	/* PID_PARTICIPANT_GUID */
	.ptcp_guid_pid			= PID_PARTICIPANT_GUID,
	.ptcp_guid_length		= 16,
	.ptcp_guid_value.eid		= {
		.entity_key		= {0, 0, 1},
		.entity_kind		= BUILD_IN_PARTICIPANT,
	},
	/* .participant_guid_value	= ptcp->guid_prefix, */

	/* PID_SESSION_ID */
	.session_id_pid			= PID_SESSION_ID,
	.session_id_length		= 8,
	/* .session_id_value_hi		= ptcp->session_id_high, */
	/* .session_id_value_lo		= ptcp->session_id_low, */
};

static struct discovery_edp edp_template = {
	/* encapsulation options */
	/* const uint8_t SCHEME_PL_CDR_LE[2] = { 0x00, 0x03 }; */
	.encapsulation_kind	= {0x00, 0x03},
	.encapsulation_options	= 0,

	/* PID_KEY_HASH */
	.key_hash_pid		= PID_KEY_HASH,
	.key_hash_pid_length	= 16,
	/* .key_hash_value	= Endpoint GUID */

	/* PID_ENDPOINT_GUID */
	.guid_pid		= PID_ENDPOINT_GUID,
	.guid_pid_length	= 16,
	/* .guid_kind		= Endpoint GUID */

	/* PID_RELIABILITY */
	.reliability_pid	= PID_RELIABILITY,
	.reliability_pid_length	= 12,
	/* .reliability_kind	= ep_attr->qos.reliability_kind, */
	.reliability_reserve1	= 0,
	.reliability_reserve2	= 0,

	/* PID_DURABILITY */
	.durability_pid		= PID_DURABILITY,
	.durability_pid_length	= 4,
	/* .durability_kind	=  ep_attr->qos.durability_kind, */

	/* PID_DEADLINE */
	.deadline_pid		= PID_DEADLINE,
	.deadline_pid_length	= 8,
	/* .deadline_kind	= ep_attr->deadline.duration, */

	/* PID_LIVELINESS */
	.liveliness_pid		= PID_LIVELINESS,
	.liveliness_pid_length	= 12,
	/* .liveliness_kind	= ep_attr->qos.liveliness_kind, */
	/* .lease_duration	= ep_attr->liveliness.lease_duration, */

	/* PID_OWNERSHIP */
	.ownership_pid		= PID_OWNERSHIP,
	.ownership_pid_length	= 4,
	/* .ownership_kind	= ep_attr->qos.ownership_kind, */

	/* PID_OWNERSHIP_STRENGTH */
	.ownership_strength_pid		= PID_OWNERSHIP_STRENGTH,
	.ownership_strength_pid_length	= 4,
	/* .ownership_strength_value	= ep_attr->ownership_strength.value, */

	/* PID_E2E_PROTECTION */
	.e2e_pid		= PID_E2E_PROTECTION,
	.e2e_pid_length		= 4,
	/* .e2e_kind		= ep_attr->e2e.e2e_protection ? 1U : 0U, */

	/* PID_MVBS_VERTION */
	.agent_pid		= PID_AGENT_ENDPOINT,
	.agent_length		= 4,
	// .agent_value		= ep_attr->agent_flag ? 1U : 0U,
	/* PID_CRC16_IDL  */
	/* PID_TOPIC_NAME */
	/* PID_TYPE_NAME  */
};

static struct participant_timer_pool {
	struct mp_blk_hdr	hdr;
	struct timer_handler	timer;
} participant_timer_list [13];

struct participant_proxy_elem {
	struct participant_proxy	proxy;
	struct locator			meta_uc_loc[1];
	struct locator			dfl_uc_loc[1];
};

static struct participant_proxy_pool {
	struct mp_blk_hdr		hdr;
	struct participant_proxy_elem	elem;
} participant_proxy_list [9];

static struct participant_proxy_elem	pdp_received;
static struct rtps_property             property_list[PROPERTY_LIST_MAX_COUNT];

static struct participant mvbs_ptcp = {
	.attr		= &mvbs_ptcp_attr,
	.proxies	= {
		.mem_addr  = (void *)&participant_proxy_list,
		.mem_size  = sizeof(participant_proxy_list),
		.blk_total = 9,
		.blk_free  = 9,
		.blk_size  = sizeof(participant_proxy_list[0]) - MP_BLK_HDR_SIZE,
	},
	.timers		= {
		.mem_addr  = (void *)&participant_timer_list,
		.mem_size  = sizeof(participant_timer_list),
		.blk_total = 13,
		.blk_free  = 13,
		.blk_size  = sizeof(participant_timer_list[0]) - MP_BLK_HDR_SIZE,
	},
	.ptransport	= (struct transport *)&mvbs_transport,
	.pdp_received	= (struct participant_proxy *)&pdp_received,

	.pdp_template   = &pdp_template,
	.edp_template   = &edp_template,

	.property	= {
		.max_count      = PROPERTY_LIST_MAX_COUNT,
		.valid_count    = 0,
		.property_list  = property_list,
	},

	.inited		= false,
	.started	= false,
};

Rte_Dds_Participant Rte_Dds_GetParticipant(void)
{
	return &mvbs_ptcp;
}
#include <mvbs/sections/stop_sec_data.h>
#include <mvbs/sections/stop_sec_const.h>
#include <mvbs/sections/stop_sec_bss.h>
#include <mvbs/sections/stop_sec_code.h>