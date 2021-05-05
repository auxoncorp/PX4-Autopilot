/* Modality probe configurations and helpers for running the SITL target on Linux */

#ifndef MODALITY_HELPERS_H
#define MODALITY_HELPERS_H

/* Keep asserts around in release mode */
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <inttypes.h>

#include <drivers/drv_hrt.h>

#include <modality/probe.h>
#include <modality/mutator.h>
#include <modality/mutation_interface.h>
#include <modality/control_message_transport.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_PROBE_INIT(p) PX4_INFO("Probe " #p " (ID %lu) initialized", p)
#define LOG_PROBE_INIT_W_RECVR(p, r) PX4_INFO("Probe " #p " (ID %lu) initialized, control receiver %s", p, r)

/* Microseconds to nanoseconds */
#define US_TO_NS(us) (us * 1000UL)

/* Probe log storage size in bytes */
#define PROBE_SIZE (1300)

/* 1,400 byte report buffers, for sending over UDP socket */
#define REPORT_SIZE (1400)

/* Reserve a portion of the report buffer for mutator announcements */
#define ANNOUNCEMENT_RESERVATION_SIZE (64)

/* Instrumentation uses the single high-resolution timer (hrt_abstime, microseconds) time domain */
#define PX4_WALL_CLOCK_ID (1)
#define PX4_WALL_CLOCK_RESOLUTION_NS (1000)

/* Modalityd's UDP collector address that receives probe reports, see Modality.toml */
#define COLLECTOR_ADDRESS "127.0.0.1"
#define COLLECTOR_PORT (2718)

/* Probes will send reports every ~25 ms by default, some probes will use their own reporting cadence */
#define REPORT_INTERVAL_US (25UL * 1000UL)
#define REPORT_INTERVAL_US_GYROSCOPE (20UL * 1000UL)

/* Control message receivers, see Modality.toml */
#define UDP_CONTROL_RECVR_BATTERY "127.0.0.1:34000"
#define UDP_CONTROL_RECVR_GYROSCOPE "127.0.0.1:34001"

/* Helper and utility functions */
uint64_t hrt_time_ns(void);
int update_last_report_time(
        const hrt_abstime report_interval,
        hrt_abstime * const last_report_time);
void probe_report_socket_init(
        int * const report_socket);
void probe_report_socket_deinit(
        int * const report_socket);
size_t next_persistent_sequence_id(
        const uint32_t probe_id,
        void * const user_state,
        uint16_t * const out_sequence_id);
void control_msg_callback(
        const uint8_t * const bytes,
        const size_t length,
        void * const opaque_probe);
void send_probe_report(
        modality_probe * const probe,
        const int socket_fd,
        uint8_t * const buffer,
        const size_t buffer_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_HELPERS_H */
