/*
 * def_68681.c
 * Richard Homan
 * 02/11/2024
 * Defintions of the 68681 DUART as connected on Commodork Enemigo -64
 */

/*
 * Important info:
 * DUART RS1-4 lines are connected to M68K A1-A4 respectively. DUART D0-D7 lines
 * are connected to M68K D0-D7 respectively. This means that we need to have
 * each register address spaced in multiples of two and have each on odd
 * addresses.
 */

#ifndef DEF_68681_H
#define DEF_68681_H

#define DUART_PTR 0x20000 // location of DUART

// offsets
#define MR1A_OFF (0x0 * 2) + 1
#define MR2A_OFF MR1A_OFF
#define  SRA_OFF (0x1 * 2) + 1
#define CSRA_OFF SRA_OFF
#define  CRA_OFF (0x2 * 2) + 1
#define  RBA_OFF (0x3 * 2) + 1
#define  TBA_OFF RBA_OFF
#define IPCR_OFF (0x4 * 2) + 1
#define  ACR_OFF IPCR_OFF
#define  ISR_OFF (0x5 * 2) + 1
#define  IMR_OFF ISR_OFF
#define  CUR_OFF (0x6 * 2) + 1
#define CTUR_OFF CUR_OFF
#define  CLR_OFF (0x7 * 2) + 1
#define CTLR_OFF CLR_OFF
#define MR1B_OFF (0x8 * 2) + 1
#define MR2B_OFF MR1B_OFF
#define  SRB_OFF (0x9 * 2) + 1
#define CSRB_OFF SRB_OFF
#define  CRB_OFF (0xa * 2) + 1
#define  RBB_OFF (0xb * 2) + 1
#define  TBB_OFF RBB_OFF
#define  IVR_OFF (0xc * 2) + 1
#define  IPR_OFF (0xd * 2) + 1
#define OPCR_OFF IPR_OFF
#define OPRS_OFF (0xe * 2) + 1
#define OPRC_OFF (0xf * 2) + 1

// pointer definitions
#define MR1A_PTR (ubyte * const)(DUART_PTR + MR1A_OFF)
#define MR2A_PTR (ubyte * const)(DUART_PTR + MR2A_OFF)
#define SRA_PTR  (ubyte * const)(DUART_PTR +  SRA_OFF)
#define CSRA_PTR (ubyte * const)(DUART_PTR + CSRA_OFF)
#define CRA_PTR  (ubyte * const)(DUART_PTR +  CRA_OFF)
#define RBA_PTR  (ubyte * const)(DUART_PTR +  RBA_OFF)
#define TBA_PTR  (ubyte * const)(DUART_PTR +  TBA_OFF)
#define IPCR_PTR (ubyte * const)(DUART_PTR + IPCR_OFF)
#define ACR_PTR  (ubyte * const)(DUART_PTR +  ACR_OFF)
#define ISR_PTR  (ubyte * const)(DUART_PTR +  ISR_OFF)
#define IMR_PTR  (ubyte * const)(DUART_PTR +  IMR_OFF)
#define CUR_PTR  (ubyte * const)(DUART_PTR +  CUR_OFF)
#define CTUR_PTR (ubyte * const)(DUART_PTR + CTUR_OFF)
#define CLR_PTR  (ubyte * const)(DUART_PTR +  CLR_OFF)
#define CTLR_PTR (ubyte * const)(DUART_PTR + CTLR_OFF)
#define MR1B_PTR (ubyte * const)(DUART_PTR + MR1B_OFF)
#define MR2B_PTR (ubyte * const)(DUART_PTR + MR1B_OFF)
#define SRB_PTR  (ubyte * const)(DUART_PTR +  SRB_OFF)
#define CSRB_PTR (ubyte * const)(DUART_PTR + CSRB_OFF)
#define CRB_PTR  (ubyte * const)(DUART_PTR +  CRB_OFF)
#define RBB_PTR  (ubyte * const)(DUART_PTR +  RBB_OFF)
#define TBB_PTR  (ubyte * const)(DUART_PTR +  TBB_OFF)
#define IVR_PTR  (ubyte * const)(DUART_PTR +  IVR_OFF)
#define IPR_PTR  (ubyte * const)(DUART_PTR +  IPR_OFF)
#define OPCR_PTR (ubyte * const)(DUART_PTR + OPCR_OFF)
#define OPRS_PTR (ubyte * const)(DUART_PTR + OPRS_OFF)
#define OPRC_PTR (ubyte * const)(DUART_PTR + OPRC_OFF)

#endif
