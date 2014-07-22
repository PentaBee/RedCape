//*******************************************************************************
//
//	File:		PWM_ARM.v
//	Author:		Octavio Rico
//	Data:		24/09/2013
//
//	TOP LEVEL MODULE
//
//	This module is the top level module
//  contains io pins and lower level module instances
//
//*******************************************************************************

`include	"timescale.v"

module pwm_ARM (

// omap bus:
				omap_gpmc_clk,			// omap gpmc clock
				omap_bus_clk,			// 25 MHz system clock
				omap_cs_l,				// chip select
				omap_oe_l,				// output enable
				omap_wr_l,				// write strobe
				omap_a,					// address bus.
				omap_d,					// bidirectional data bus.			
// CCD Imager Port
            	pwm,//connected to led 0
            	pwm2,//connected to led 1
            	pwm3//connected to led 2
            			
);

// omap bus:
input			omap_gpmc_clk;
input			omap_bus_clk;
input			omap_cs_l;
input			omap_oe_l;
input			omap_wr_l;
input	[3:0]	omap_a;
inout	[15:0]	omap_d;
//pwm
output		pwm;
output		pwm2;
output		pwm3;

// omap bus:
tri		[15:0]	omap_d;

// host syscon
wire			sys_rst_l;


//*******************************************************************************
// HOST BUS WIRING
//*******************************************************************************
// host bus
wire			host_rst_l;
wire			host_clk;
wire	[15:0]	host_addr;
wire	[15:0]	host_rd_data;
wire	[15:0]	host_wr_data;
wire			host_rd_en;
wire			host_wr_en;

// host_ctrl bus

wire	[15:0]	host_ctrl_addr;
wire	[15:0]	host_ctrl_rd_data;
wire	[15:0]	host_ctrl_wr_data;
wire			host_ctrl_cs;
wire			host_ctrl_rd_en;
wire			host_ctrl_wr_en;

// vid_imager bus

wire	[15:0]	vid_imager_addr;
wire	[15:0]	vid_imager_rd_data;
wire	[15:0]	vid_imager_wr_data;
wire			vid_imager_cs;
wire			vid_imager_rd_en;
wire			vid_imager_wr_en;

//*******************************************************************************
// SYSTEM MODULES
//*******************************************************************************

// instantiate host bus syscon

host_syscon iHOST_SYSCON (
// sys clock in:
				.sys_clk (omap_bus_clk),
				.sys_rst_l (sys_rst_l),

				
// host bus clock out:
				.host_clk (host_clk),
				.host_rst_l (host_rst_l),

);





//omap processor bus interface
omap_bus iomap_BUS (
// omap bus:
				.omap_cs_l (omap_cs_l),
				.omap_oe_l (omap_oe_l),
				.omap_wr_l (omap_wr_l),
				.omap_a (omap_a),
				.omap_d (omap_d),
				.omap_gpmc_clk (omap_gpmc_clk),
//  host bus:
				.host_rst_l (host_rst_l),
				.host_clk (host_clk),
				.host_addr (host_addr),
				.host_rd_data (host_rd_data),
				.host_wr_data (host_wr_data),
				.host_rd_en (host_rd_en),
				.host_wr_en (host_wr_en),
				.sys_rst_l(sys_rst_l)
				
);

//*******************************************************************************
// HOST BUS
//*******************************************************************************

host_bus iHOST_BUS (
// host bus
				.host_rst_l (host_rst_l),
				.host_clk (host_clk),
				.host_addr (host_addr),
				.host_rd_data (host_rd_data),
				.host_wr_data (host_wr_data),
				.host_rd_en (host_rd_en),
				.host_wr_en (host_wr_en),
// host_ctrl bus
				.host_ctrl_addr (host_ctrl_addr),
				.host_ctrl_rd_data (host_ctrl_rd_data),
				.host_ctrl_wr_data (host_ctrl_wr_data),
				.host_ctrl_cs (host_ctrl_cs),
				.host_ctrl_rd_en (host_ctrl_rd_en),
				.host_ctrl_wr_en (host_ctrl_wr_en),
// vid_imager bus
				.vid_imager_addr (vid_imager_addr),
				.vid_imager_rd_data (vid_imager_rd_data),
				.vid_imager_wr_data (vid_imager_wr_data),
				.vid_imager_cs (vid_imager_cs),
				.vid_imager_rd_en (vid_imager_rd_en),
				.vid_imager_wr_en (vid_imager_wr_en)		
);

//*******************************************************************************
// HOST BUS MODULES
//*******************************************************************************

host_ctrl iHOST_CTRL (
// host bus:
				.host_rst_l (host_rst_l),
				.host_clk (host_clk),
// host_ctrl bus
				.host_addr (host_ctrl_addr),
				.host_rd_data (host_ctrl_rd_data),
				.host_wr_data (host_ctrl_wr_data),
				.host_cs (host_ctrl_cs),
				.host_rd_en (host_ctrl_rd_en),
				.host_wr_en (host_ctrl_wr_en),

);

//*******************************************************************************
// PWM Driver
//*******************************************************************************

pwm_drv iPWM_drv (
// host bus:
				.host_rst_l(host_rst_l),
				.host_clk(host_clk),
				.host_addr (vid_imager_addr),
				.host_wr_data (vid_imager_wr_data),
				.host_cs (vid_imager_cs),
				.host_rd_en (vid_imager_rd_en),
				.host_wr_en (vid_imager_wr_en),
				
				.pwm (pwm),
				.pwm2 (pwm2),
				.pwm3 (pwm3)
			);

endmodule
