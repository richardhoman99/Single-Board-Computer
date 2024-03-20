/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0xfbc00daa */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/home/ise/Single-Board-Computer/SBC-Address-Router/AddressDecoder.vhd";
extern char *IEEE_P_2592010699;

unsigned char ieee_p_2592010699_sub_3488768496604610246_503743352(char *, unsigned char , unsigned char );
unsigned char ieee_p_2592010699_sub_374109322130769762_503743352(char *, unsigned char );


static void work_a_2188137860_3212880686_p_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    int t5;
    char *t6;
    char *t7;
    int t8;
    char *t9;
    char *t10;
    int t11;
    char *t12;
    int t14;
    char *t15;
    int t17;
    char *t18;
    int t20;
    char *t21;
    int t23;
    char *t24;
    int t26;
    char *t27;
    char *t29;
    char *t30;
    char *t31;
    char *t32;
    char *t33;

LAB0:    t1 = (t0 + 5224U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(94, ng0);
    t2 = (t0 + 3752U);
    t3 = *((char **)t2);
    t2 = (t0 + 12010);
    t5 = xsi_mem_cmp(t2, t3, 5U);
    if (t5 == 1)
        goto LAB5;

LAB14:    t6 = (t0 + 12015);
    t8 = xsi_mem_cmp(t6, t3, 5U);
    if (t8 == 1)
        goto LAB6;

LAB15:    t9 = (t0 + 12020);
    t11 = xsi_mem_cmp(t9, t3, 5U);
    if (t11 == 1)
        goto LAB7;

LAB16:    t12 = (t0 + 12025);
    t14 = xsi_mem_cmp(t12, t3, 5U);
    if (t14 == 1)
        goto LAB8;

LAB17:    t15 = (t0 + 12030);
    t17 = xsi_mem_cmp(t15, t3, 5U);
    if (t17 == 1)
        goto LAB9;

LAB18:    t18 = (t0 + 12035);
    t20 = xsi_mem_cmp(t18, t3, 5U);
    if (t20 == 1)
        goto LAB10;

LAB19:    t21 = (t0 + 12040);
    t23 = xsi_mem_cmp(t21, t3, 5U);
    if (t23 == 1)
        goto LAB11;

LAB20:    t24 = (t0 + 12045);
    t26 = xsi_mem_cmp(t24, t3, 5U);
    if (t26 == 1)
        goto LAB12;

LAB21:
LAB13:    xsi_set_current_line(98, ng0);
    t2 = (t0 + 12098);
    t4 = (t0 + 7472);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t9 = (t7 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t2, 6U);
    xsi_driver_first_trans_fast(t4);

LAB4:    xsi_set_current_line(94, ng0);

LAB25:    t2 = (t0 + 7280);
    *((int *)t2) = 1;
    *((char **)t1) = &&LAB26;

LAB1:    return;
LAB5:    xsi_set_current_line(98, ng0);
    t27 = (t0 + 12050);
    t29 = (t0 + 7472);
    t30 = (t29 + 56U);
    t31 = *((char **)t30);
    t32 = (t31 + 56U);
    t33 = *((char **)t32);
    memcpy(t33, t27, 6U);
    xsi_driver_first_trans_fast(t29);
    goto LAB4;

LAB6:    xsi_set_current_line(98, ng0);
    t2 = (t0 + 12056);
    t4 = (t0 + 7472);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t9 = (t7 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t2, 6U);
    xsi_driver_first_trans_fast(t4);
    goto LAB4;

LAB7:    xsi_set_current_line(98, ng0);
    t2 = (t0 + 12062);
    t4 = (t0 + 7472);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t9 = (t7 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t2, 6U);
    xsi_driver_first_trans_fast(t4);
    goto LAB4;

LAB8:    xsi_set_current_line(98, ng0);
    t2 = (t0 + 12068);
    t4 = (t0 + 7472);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t9 = (t7 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t2, 6U);
    xsi_driver_first_trans_fast(t4);
    goto LAB4;

LAB9:    xsi_set_current_line(98, ng0);
    t2 = (t0 + 12074);
    t4 = (t0 + 7472);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t9 = (t7 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t2, 6U);
    xsi_driver_first_trans_fast(t4);
    goto LAB4;

LAB10:    xsi_set_current_line(98, ng0);
    t2 = (t0 + 12080);
    t4 = (t0 + 7472);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t9 = (t7 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t2, 6U);
    xsi_driver_first_trans_fast(t4);
    goto LAB4;

LAB11:    xsi_set_current_line(98, ng0);
    t2 = (t0 + 12086);
    t4 = (t0 + 7472);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t9 = (t7 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t2, 6U);
    xsi_driver_first_trans_fast(t4);
    goto LAB4;

LAB12:    xsi_set_current_line(98, ng0);
    t2 = (t0 + 12092);
    t4 = (t0 + 7472);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t9 = (t7 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t2, 6U);
    xsi_driver_first_trans_fast(t4);
    goto LAB4;

LAB22:;
LAB23:    t3 = (t0 + 7280);
    *((int *)t3) = 0;
    goto LAB2;

LAB24:    goto LAB23;

LAB26:    goto LAB24;

}

static void work_a_2188137860_3212880686_p_1(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    unsigned char t5;
    unsigned char t6;
    unsigned char t7;
    unsigned char t8;
    char *t9;
    int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned char t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;

LAB0:    xsi_set_current_line(113, ng0);
    t1 = (t0 + 3272U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 4072U);
    t4 = *((char **)t1);
    t5 = *((unsigned char *)t4);
    t6 = ieee_p_2592010699_sub_374109322130769762_503743352(IEEE_P_2592010699, t5);
    t7 = ieee_p_2592010699_sub_3488768496604610246_503743352(IEEE_P_2592010699, t3, t6);
    t8 = (t7 == (unsigned char)2);
    if (t8 != 0)
        goto LAB2;

LAB4:    xsi_set_current_line(125, ng0);
    t1 = (t0 + 7728);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(126, ng0);
    t1 = (t0 + 7664);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(127, ng0);
    t1 = (t0 + 7856);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(128, ng0);
    t1 = (t0 + 7792);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(129, ng0);
    t1 = (t0 + 7920);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(130, ng0);
    t1 = (t0 + 7536);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(131, ng0);
    t1 = (t0 + 7600);
    t2 = (t1 + 56U);
    t4 = *((char **)t2);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    *((unsigned char *)t15) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);

LAB3:    t1 = (t0 + 7296);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(116, ng0);
    t1 = (t0 + 3912U);
    t9 = *((char **)t1);
    t10 = (5 - 5);
    t11 = (t10 * -1);
    t12 = (1U * t11);
    t13 = (0 + t12);
    t1 = (t9 + t13);
    t14 = *((unsigned char *)t1);
    t15 = (t0 + 7536);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    t18 = (t17 + 56U);
    t19 = *((char **)t18);
    *((unsigned char *)t19) = t14;
    xsi_driver_first_trans_fast_port(t15);
    xsi_set_current_line(117, ng0);
    t1 = (t0 + 3912U);
    t2 = *((char **)t1);
    t10 = (5 - 5);
    t11 = (t10 * -1);
    t12 = (1U * t11);
    t13 = (0 + t12);
    t1 = (t2 + t13);
    t3 = *((unsigned char *)t1);
    t4 = (t0 + 7600);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    *((unsigned char *)t17) = t3;
    xsi_driver_first_trans_fast_port(t4);
    xsi_set_current_line(118, ng0);
    t1 = (t0 + 3912U);
    t2 = *((char **)t1);
    t10 = (4 - 5);
    t11 = (t10 * -1);
    t12 = (1U * t11);
    t13 = (0 + t12);
    t1 = (t2 + t13);
    t3 = *((unsigned char *)t1);
    t4 = (t0 + 7664);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    *((unsigned char *)t17) = t3;
    xsi_driver_first_trans_fast_port(t4);
    xsi_set_current_line(119, ng0);
    t1 = (t0 + 3912U);
    t2 = *((char **)t1);
    t10 = (3 - 5);
    t11 = (t10 * -1);
    t12 = (1U * t11);
    t13 = (0 + t12);
    t1 = (t2 + t13);
    t3 = *((unsigned char *)t1);
    t4 = (t0 + 7728);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    *((unsigned char *)t17) = t3;
    xsi_driver_first_trans_fast_port(t4);
    xsi_set_current_line(120, ng0);
    t1 = (t0 + 3912U);
    t2 = *((char **)t1);
    t10 = (2 - 5);
    t11 = (t10 * -1);
    t12 = (1U * t11);
    t13 = (0 + t12);
    t1 = (t2 + t13);
    t3 = *((unsigned char *)t1);
    t4 = (t0 + 7792);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    *((unsigned char *)t17) = t3;
    xsi_driver_first_trans_fast_port(t4);
    xsi_set_current_line(121, ng0);
    t1 = (t0 + 3912U);
    t2 = *((char **)t1);
    t10 = (1 - 5);
    t11 = (t10 * -1);
    t12 = (1U * t11);
    t13 = (0 + t12);
    t1 = (t2 + t13);
    t3 = *((unsigned char *)t1);
    t4 = (t0 + 7856);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    *((unsigned char *)t17) = t3;
    xsi_driver_first_trans_fast_port(t4);
    xsi_set_current_line(122, ng0);
    t1 = (t0 + 3912U);
    t2 = *((char **)t1);
    t10 = (0 - 5);
    t11 = (t10 * -1);
    t12 = (1U * t11);
    t13 = (0 + t12);
    t1 = (t2 + t13);
    t3 = *((unsigned char *)t1);
    t4 = (t0 + 7920);
    t9 = (t4 + 56U);
    t15 = *((char **)t9);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    *((unsigned char *)t17) = t3;
    xsi_driver_first_trans_fast_port(t4);
    goto LAB3;

}

static void work_a_2188137860_3212880686_p_2(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;

LAB0:    xsi_set_current_line(136, ng0);

LAB3:    t1 = (t0 + 3272U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 7984);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t8 = (t0 + 7312);
    *((int *)t8) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_2188137860_3212880686_p_3(char *t0)
{
    char *t1;
    char *t2;
    int t3;
    unsigned int t4;
    unsigned int t5;
    unsigned int t6;
    unsigned char t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;

LAB0:    xsi_set_current_line(139, ng0);

LAB3:    t1 = (t0 + 3432U);
    t2 = *((char **)t1);
    t3 = (1 - 7);
    t4 = (t3 * -1);
    t5 = (1U * t4);
    t6 = (0 + t5);
    t1 = (t2 + t6);
    t7 = *((unsigned char *)t1);
    t8 = (t0 + 8048);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = t7;
    xsi_driver_first_trans_delta(t8, 1U, 1, 0LL);

LAB2:    t13 = (t0 + 7328);
    *((int *)t13) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_2188137860_3212880686_p_4(char *t0)
{
    char *t1;
    char *t2;
    int t3;
    unsigned int t4;
    unsigned int t5;
    unsigned int t6;
    unsigned char t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;

LAB0:    xsi_set_current_line(140, ng0);

LAB3:    t1 = (t0 + 3432U);
    t2 = *((char **)t1);
    t3 = (0 - 7);
    t4 = (t3 * -1);
    t5 = (1U * t4);
    t6 = (0 + t5);
    t1 = (t2 + t6);
    t7 = *((unsigned char *)t1);
    t8 = (t0 + 8112);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = t7;
    xsi_driver_first_trans_delta(t8, 2U, 1, 0LL);

LAB2:    t13 = (t0 + 7344);
    *((int *)t13) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_2188137860_3212880686_p_5(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;

LAB0:    xsi_set_current_line(141, ng0);

LAB3:    t1 = (t0 + 3112U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 8176);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_delta(t1, 3U, 1, 0LL);

LAB2:    t8 = (t0 + 7360);
    *((int *)t8) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_2188137860_3212880686_p_6(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;

LAB0:    xsi_set_current_line(142, ng0);

LAB3:    t1 = (t0 + 2952U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 8240);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_delta(t1, 4U, 1, 0LL);

LAB2:    t8 = (t0 + 7376);
    *((int *)t8) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_2188137860_3212880686_p_7(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;

LAB0:    xsi_set_current_line(145, ng0);

LAB3:    t1 = (t0 + 4072U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 8304);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t8 = (t0 + 7392);
    *((int *)t8) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}


extern void work_a_2188137860_3212880686_init()
{
	static char *pe[] = {(void *)work_a_2188137860_3212880686_p_0,(void *)work_a_2188137860_3212880686_p_1,(void *)work_a_2188137860_3212880686_p_2,(void *)work_a_2188137860_3212880686_p_3,(void *)work_a_2188137860_3212880686_p_4,(void *)work_a_2188137860_3212880686_p_5,(void *)work_a_2188137860_3212880686_p_6,(void *)work_a_2188137860_3212880686_p_7};
	xsi_register_didat("work_a_2188137860_3212880686", "isim/AddressDecoder_Bench_isim_beh.exe.sim/work/a_2188137860_3212880686.didat");
	xsi_register_executes(pe);
}
