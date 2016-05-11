/*
 * Clock Initialization for board based on EXYNOS4210
 *
 * Copyright (C) 2013 Samsung Electronics
 * Rajeshwari Shinde <rajeshwari.s@samsung.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <config.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/clk.h>
#include <asm/arch/clock.h>
#include "common_setup.h"

#define APLL_CON1_VAL (0x00803800)
#define APLL_CON0_VAL (0x807D0300)
#define MPLL_CON1_VAL (0x00803800)
#define MPLL_CON0_VAL (0x80640300)
#define EPLL_CON2_VAL (0x00000080)
#define EPLL_CON1_VAL (0x66010000)
#define EPLL_CON0_VAL (0x80640301)
#define VPLL_CON2_VAL (0x00000080)
#define VPLL_CON1_VAL (0x66010000)
#define VPLL_CON0_VAL (0x80640303)

#define CLK_SRC_CPU_VAL (0x01000001)
#define CLK_SRC_DMC_VAL (0x00011000)
#define CLK_SRC_TOP0_VAL (0x00000110)
#define CLK_SRC_TOP1_VAL (0x00011000)

#define CLK_SRC_LEFTBUS_VAL (0x00000010)
#define CLK_SRC_RIGHTBUS_VAL (0x00000010)

#define CLK_DIV_LEFTBUS_VAL (0x00000013)
#define CLK_DIV_RIGHTBUS_VAL (0x00000013)

#define CLK_DIV_DMC0_VAL (0x00111113)
#define CLK_DIV_DMC1_VAL (0x01011113)

#define CLK_DIV_CPU0_VAL (0x01143730)
#define CLK_DIV_CPU1_VAL (0x00000004)

#define CLK_DIV_TOP_VAL (0x01205473)

#define PLL_LOCKTIME (0xFFF)
/*
 * system_clock_init: Initialize core clock and bus clock.
 * void system_clock_init(void)
 */
void system_clock_init(void)
{
	struct exynos4x12_clock *clk =
			(struct exynos4x12_clock*)samsung_get_base_clock();

	writel(CLK_SRC_CPU_VAL, &clk->src_cpu);

	sdelay(0x10000);

	writel(CLK_SRC_TOP0_VAL, &clk->src_top0);
	writel(CLK_SRC_TOP1_VAL, &clk->src_top1);
	writel(CLK_SRC_DMC_VAL, &clk->src_dmc);
	writel(CLK_SRC_LEFTBUS_VAL, &clk->src_leftbus);
	writel(CLK_SRC_RIGHTBUS_VAL, &clk->src_rightbus);

	sdelay(0x10000);

	writel(CLK_DIV_CPU0_VAL, &clk->div_cpu0);
	writel(CLK_DIV_CPU1_VAL, &clk->div_cpu1);
	writel(CLK_DIV_DMC0_VAL, &clk->div_dmc0);
	writel(CLK_DIV_DMC1_VAL, &clk->div_dmc1);
	writel(CLK_DIV_LEFTBUS_VAL, &clk->div_leftbus);
	writel(CLK_DIV_RIGHTBUS_VAL, &clk->div_rightbus);
	writel(CLK_DIV_TOP_VAL, &clk->div_top);

	/* Set PLL locktime */
	writel(PLL_LOCKTIME, &clk->apll_lock);
	writel(PLL_LOCKTIME, &clk->mpll_lock);
	writel(PLL_LOCKTIME, &clk->epll_lock);
	writel(PLL_LOCKTIME, &clk->vpll_lock);

	writel(APLL_CON1_VAL, &clk->apll_con1);
	writel(APLL_CON0_VAL, &clk->apll_con0);
	writel(MPLL_CON1_VAL, &clk->mpll_con1);
	writel(MPLL_CON0_VAL, &clk->mpll_con0);
	writel(EPLL_CON2_VAL, &clk->epll_con2);
	writel(EPLL_CON1_VAL, &clk->epll_con1);
	writel(EPLL_CON0_VAL, &clk->epll_con0);
	writel(VPLL_CON2_VAL, &clk->vpll_con2);
	writel(VPLL_CON1_VAL, &clk->vpll_con1);
	writel(VPLL_CON0_VAL, &clk->vpll_con0);

	sdelay(0x30000);
}
