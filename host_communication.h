#ifndef __HOST_COMM__
#define __HOST_COMM__

typedef uint8_t (*fn)(uint8_t *buff, uint8_t size);
typedef void (*fn1)(uint16_t buff);
typedef uint8_t (*fn2)(uint8_t *buff);

typedef struct {
	fn dwn_tx;
	fn dwn_rx;
}t_host_comm;

void host_RegisterTxRx(fn down_tx, fn down_rx);
uint8_t host_AnalyzeCommand(uint32_t cmd);
#endif
