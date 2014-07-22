//*******************************************************************************
//
//	File:		FpgaRegs.h
//	Author:		Kevin Moon, Peter Scott, Anton Kachatkou
//	Date:		16/3/04, last modified on 27/04/10
//
//	Fpfa register definitions
//
//
//*******************************************************************************

#ifndef FPGAREGS_H
#define FPGAREGS_H

// the following macro creates a full address of the FPGA register to access (read/write)
// the structure of the 16-bit address is 0xMMMR, where M is a module address (should be
// pre-selected by writing 0xMMM0 to the FPGA_ADDR), R is the register address.
// In total, 6 write and 8 read registers available to each FPGA module, their addresses
// are defined for each module separately below in this file.
// Two write registers, FPGA_ADDR and FPGA_RESET, are reserved for module selection and
// FPGA reset commands respectively.
#define		FPGA(module, reg)	(((module) & 0xFFF0) | ((reg) & 0x000F))

// host bus modules chip select addresses
// (write to FPGA_ADDR register to select a particular model)
#define		CS_HOST_CTRL		0x0010	// host control
#define		CS_IMAGER			0x0020	// imager (IBIS4) interface module
#define		CS_VID				0x0030	// video framestore
#define		CS_FRAME_DMA_READ	0x0050	// first DMA read channel (host frame DMA)
#define		CS_DMA_WRITE		0x0060	// DMA write channel
#define		CS_DARK_DMA_READ	0x0070	// second DMA read channel (dark image DMA)
#define		CS_PROFILER			0x0090	// profiler module


//general purpose registers
#define		FPGA_ADDR				0x0000	// (w) address reg
#define		FPGA_RESET				0x0002	// (w) device reset

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//Host control module
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//registers
#define		HOST_CTRL				FPGA(CS_HOST_CTRL, 0x0004)	// (rw) fpga global control/status register
#define		HOST_ID					FPGA(CS_HOST_CTRL, 0x0006)	// (r) FPGA ID register
#define		HOST_EN					FPGA(CS_HOST_CTRL, 0x0008)	// (rw) host enable register (rw),
																// currently used to
																// enable (low impedance) or disable
																// (high impedance) IBIS4 sensor
// id register bits

#define		FPGA_ID_CODE			0x2347	// device id

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//End of host control module definitions
//////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//Video framestore
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//register selects
#define		VID_STATUS				FPGA(CS_VID, 0x0000)		// (r) status register
																// (see VIDFS_STAT_XXX bits below)
#define		VID_READ_GP				FPGA(CS_VID, 0x0002)		// (r) read 16-bit data from the general purpose buffer
#define		VID_MULTIMG_COUNTER		FPGA(CS_VID, 0x0004)		// (r) counting frame ticker during
																// multiple image acquisition (summing or averaging)
#define		VID_CONTROL				FPGA(CS_VID, 0x0004)		// (w) set framestore parameters (see VID_CTRL_XXX bits)
#define		VID_READ32_MSW			FPGA(CS_VID, 0x0006)		// (r) read the most significant word of 32-bit data;
																// this is currently an accumulated image with or
																// without dark image subtracted
#define		VID_SET_MODE			FPGA(CS_VID, 0x0006)		// (w) framestore operating mode,
																// see VID_MODE_xxx for valid values
#define		VID_READ32_LSW			FPGA(CS_VID, 0x0008)		// (r) read the least significant word of 32-bit data;
																// also see comments on VID_READ32_MSW
#define		VID_WRITE				FPGA(CS_VID, 0x0008)		// (w) write data to FPGA RAM
#define		VID_FRAMENO				FPGA(CS_VID, 0x000A)		// (r) current frame number, currently contains
																// the same value as IMAGER_FRAMENO
#define		VID_SUM_FRAME_NUM		FPGA(CS_VID, 0x000A)		// (w) number of frames to sum
#define		VID_BITS_TO_SHIFT		FPGA(CS_VID, 0x000C)		// (w) number of bits to shift accumulated pixel values
																// to the right in order to produce the average value (31 max)

// framestore status register bits (read)
#define		VID_STAT_GP_BUSY		0x0001	// general purpose buffer's busy flag
#define		VID_STAT_DARK_BUSY		0x0002	// dark image buffer's busy flag
#define		VID_STAT_HOST			0x0004	// host request flag (set 1 when the host initiated
											// any task and reset only when the task is finished)
#define		VID_STAT_READY			0x0008	// ready flag (all buffers are ready to be read)
// framestore control register bits (write)
#define		VID_CTRL_ENABLE_SHIFT	0
#define		VID_CTRL_CONT_SHIFT		1
#define		VID_CTRL_WIDTH_SHIFT	2
#define		VID_CTRL_DARKSUB_SHIFT	4
#define		VID_CTRL_CONTPROF_SHIFT	5
#define		VID_CTRL_ENABLE			(1 << VID_CTRL_ENABLE_SHIFT)	// enable framestore
#define		VID_CTRL_ENABLE_MASK	(1 << VID_CTRL_ENABLE_SHIFT)
#define		VID_CTRL_CONT			(1 << VID_CTRL_CONT_SHIFT)		// continuous acquisition (single if zero)
#define		VID_CTRL_CONT_MASK		(1 << VID_CTRL_CONT_SHIFT)
#define		VID_CTRL_WIDTH_16		(0 << VID_CTRL_WIDTH_SHIFT)		// 16-bit data output
#define		VID_CTRL_WIDTH_32		(1 << VID_CTRL_WIDTH_SHIFT)		// 32-bit data output
#define		VID_CTRL_WIDTH_MASK		(3 << VID_CTRL_WIDTH_SHIFT)		// data width bit mask
#define		VID_CTRL_DARKSUB		(1 << VID_CTRL_DARKSUB_SHIFT)	// enable dark image subtraction (disable if zero)
#define		VID_CTRL_DARKSUB_MASK	(1 << VID_CTRL_DARKSUB_SHIFT)
#define		VID_CTRL_CONTPROF		(1 << VID_CTRL_CONTPROF_SHIFT)	// continuous profile acquisition
#define		VID_CTRL_CONTPROF_MASK	(1 << VID_CTRL_CONTPROF_SHIFT)
//framestore control register set macro
#define		VID_CTRL_SET(enable,cont,wdata,dark,pcont)	(uint16_t)(((enable << VID_CTRL_ENABLE_SHIFT) & VID_CTRL_ENABLE_MASK) |\
														((cont << VID_CTRL_CONT_SHIFT) & VID_CTRL_CONT_MASK) |\
														((wdata << VID_CTRL_WIDTH_SHIFT) & VID_CTRL_WIDTH_MASK) |\
														((dark << VID_CTRL_DARKSUB_SHIFT) & VID_CTRL_DARKSUB_MASK) |\
														((pcont << VID_CTRL_CONTPROF_SHIFT) & VID_CTRL_CONTPROF_MASK))
//framestore modes
#define		VID_MODE_READ			0x0001	// read data from FPGA RAM, supports 8 and 16-bit data, 8-bit data are packed
											// in words so that they are correctly ordered on a big-endian system:
											// for example, if there is a sequence of bytes 0x11, 0x22, 0x33, 0x44,
											// two subsequently read words on a big-endian system are 0x1122 and
											// 0x3344, whereas on a little-endian system the result is 0x2211 and
											// 0x4433
#define		VID_MODE_IMG16			0x0002	// capture 16-bit image into FPGA RAM
#define		VID_MODE_IMG8			0x0003	// capture 8-bit image into FPGA RAM
#define		VID_MODE_SUM			0x0004	// sum images into FPGA RAM (32 bit)
#define		VID_MODE_PROFILE		0x0005	// profiler mode, instruct framestore to create an access channel for
											// the profiler module and to stop any other tasks
#define		VID_MODE_AVER			0x0006	// calculate average image from the sum of images stored in FPGA RAM
											// (perform right shift of pixel values by a pre-configured number of
											// bits) and subtract dark image if pre-configured so
#define		VID_MODE_READ32			0x0007	// read 32-bit data from FPGA RAM (access through VID_READ32_MSW
											// and VID_READ32_LSW registers)
#define		VID_MODE_WRITE			0x0008	// write data into FPGA RAM

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//End of video framestore definitions
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// DMA read/write channels
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Common DMA registers
#define		DMA_REG_STAT			0x0000						// (r) DMA channel status, currently
																// contains current buffer number
#define		DMA_REG_ENABLE			0x0004						// (w) DMA channel enable(1)/disable(0)
#define		DMA_REG_PAGE			0x0006						// (w) start access memory page address
#define		DMA_REG_PARAMS			0x0008						// (w) channel access parameters, see DMA_PAR_xxx
																// macros for available values
#define		DMA_REG_BUFFER			0x000A						// (w) number of the current access buffer

// First DMA read channel (frame)
#define		RFRAME_ENABLE			FPGA(CS_FRAME_DMA_READ, DMA_REG_ENABLE)	// (w) enable (1) / disable (0) DMA channel
#define		RFRAME_START_PAGE		FPGA(CS_FRAME_DMA_READ, DMA_REG_PAGE)	// (w) start access memory page address
#define		RFRAME_PARAMS			FPGA(CS_FRAME_DMA_READ, DMA_REG_PARAMS)	// (w) access parameters,
#define		RFRAME_BUFFER			FPGA(CS_FRAME_DMA_READ, DMA_REG_BUFFER)	// (w) number of the current buffer to read from

// DMA write channel
#define		WRAM_ENABLE				FPGA(CS_DMA_WRITE, DMA_REG_ENABLE)	// (w) enable (1) / disable (0) DMA channel
#define		WRAM_START_PAGE			FPGA(CS_DMA_WRITE, DMA_REG_PAGE)	// (w) start access memory page address
#define		WRAM_PARAMS				FPGA(CS_DMA_WRITE, DMA_REG_PARAMS)	// (w) access parameters,
#define		WRAM_BUFFER				FPGA(CS_DMA_WRITE, DMA_REG_BUFFER)	// (w) number of the current buffer to read from

// Second DMA read channel (dark)
#define		RDARK_ENABLE			FPGA(CS_DARK_DMA_READ, DMA_REG_ENABLE)	// (w) enable (1) / disable (0) DMA channel
#define		RDARK_START_PAGE		FPGA(CS_DARK_DMA_READ, DMA_REG_PAGE)	// (w) start access memory page address
#define		RDARK_PARAMS			FPGA(CS_DARK_DMA_READ, DMA_REG_PARAMS)	// (w) access parameters,
#define		RDARK_BUFFER			FPGA(CS_DARK_DMA_READ, DMA_REG_BUFFER)	// (w) number of the current buffer to read from

// DMA parameter register bits
#define		DMA_PAR_BUF_NUM_MASK	0x00FF	// number of buffers mask
#define		DMA_PAR_BUF_NUM_SHIFT	0		// position of the least significant bit of the number of buffers value
#define		DMA_PAR_BUF_SIZE_MASK	0x0F00	// buffer size mask
#define		DMA_PAR_BUF_SIZE_SHIFT	8		// position of the least significant bit of the buffer size value
#define		DMA_PAR_AUTOINC_MASK	0x1000	// current buffer number auto increment value mask
#define		DMA_PAR_AUTOINC_SHIFT	12		// position of the current buffer number auto increment bit
#define		DMA_PAR_WRAP_MASK		0x2000	// wrap around buffer protection/round robin processing bit mask
#define		DMA_PAR_WRAP_SHIFT		13		// position of the wrap around buffer protection/round robin processing bit

//DMA parameter set macro
#define		DMA_PARAM_SET(bufsize,nbuf,autoinc,wrapbuf)	(uint16_t)(((nbuf << DMA_PAR_BUF_NUM_SHIFT) & DMA_PAR_BUF_NUM_MASK) |\
														((bufsize << DMA_PAR_BUF_SIZE_SHIFT) & DMA_PAR_BUF_SIZE_MASK) |\
														((autoinc << DMA_PAR_AUTOINC_SHIFT) & DMA_PAR_AUTOINC_MASK) |\
														((wrapbuf << DMA_PAR_WRAP_SHIFT) & DMA_PAR_WRAP_MASK))

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//End of DMA read/write channels definitions
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Profiler
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// register selects
#define		PROF_STATUS				FPGA(CS_PROFILER, 0x0000)	// (r) status register, see PROF_STAT_xxx for values
#define		PROF_RES_VAL			FPGA(CS_PROFILER, 0x0002)	// (r) result register, contains the value of the
																// profile calculation result requested by writing
																// to PROF_READ_ADDR
#define		PROF_CTRL				FPGA(CS_PROFILER, 0x0004)	// (w) control register, see PROF_CTRL_xxx for values
#define		PROF_READ_ADDR			FPGA(CS_PROFILER, 0x0006)	// (w) profiler's internal address to read calculation
																// results from PROF_RES_VAL, see PROF_ADDR_xxx for
																// available values (multiplexed read); alternatively,
																// used to set block RAM address to read x-, y-profile
																// or histogram data via dedicated registers
#define		PROF_QUAD_CONF			FPGA(CS_PROFILER, 0x0008)	// (w) quad configuration register, four most
																// significant bits of the data written determines
																// which parameter is set (see PROF_QUAD_xxx macros
																// for the values)
#define		PROF_Y_LOW				FPGA(CS_PROFILER, 0x0004)	// (r) y-profile lower word
#define		PROF_Y_HIGH				FPGA(CS_PROFILER, 0x0006)	// (r) y-profile upper word
#define		PROF_X_LOW				FPGA(CS_PROFILER, 0x0008)	// (r) x-profile lower word
#define		PROF_X_HIGH				FPGA(CS_PROFILER, 0x000A)	// (r) x-profile upper word
#define		PROF_HIST_LOW			FPGA(CS_PROFILER, 0x000C)	// (r) histogram lower word
#define		PROF_HIST_HIGH			FPGA(CS_PROFILER, 0x000E)	// (r) histogram upper word

// Profiler status register bits
#define		PROF_STAT_DONE_MASK		0x0003	// profiler-finished-processing bits mask
#define		PROF_STAT_DONE			0x0003	// profiler finished processing, data ready for reading out
// Profiler control register bits
#define		PROF_CTRL_ENABLE		0x0001	// enable profiler
#define		PROF_CTRL_TRIGGER		0x0002	// make profiler trigger after the current frame (what does this mean????)
#define		PROF_CTRL_ADDR_AUTO_INC	0x0004	// auto increment profiler's block RAM address after each read (used when
											// reading x-, y-profile and histogram data; read lower word last to make
											// this work correctly)
// Profiler internal address register values
#define		PROF_ADDR_XACC0			1		// first (LS) word of the x-accumulated data
#define		PROF_ADDR_XACC1			2		// second word of the x-accumulated data
#define		PROF_ADDR_XACC2			3		// third word of the x-accumulated data (fourth or MSW is always zero)
#define		PROF_ADDR_YACC0			4		// first (LS) word of the y-accumulated data
#define		PROF_ADDR_YACC1			5		// second word of the y-accumulated data
#define		PROF_ADDR_YACC2			6		// third word of the y-accumulated data (fourth or MSW is always zero)
#define		PROF_ADDR_IMGSUM0		7		// first (LS) word of the image total sum data
#define		PROF_ADDR_IMGSUM1		8		// second word of the image total sum data
#define		PROF_ADDR_IMGSUM2		9		// third word of the image total sum data (fourth or MSW is always zero)
#define		PROF_ADDR_QUADBEGIN		12		// LSW of Quad0, the order is Quad0[LSW], Quad0[MSW], Quad1[LSW],... Quad3[MSW]
#define		PROF_ADDR_QUADEND		19		// MSW of Quad3
#define		PROF_ADDR_QUADPARBEGIN	20		// first quad parameter; order: x_centre, y_centre, x_start, x_end, y_start, y_end
#define 	PROF_ADDR_QUADPAREND	25		// last quad parameter
// Profiler quad configuration register data indicators
#define		PROF_QUAD_XCENTRE		0x0000	// x-coordinate of the quad configuration centre
#define		PROF_QUAD_YCENTRE		0x1000	// y-coordinate of the quad configuration centre
#define		PROF_QUAD_XSTART		0x2000	// x-coordinate of the quad window bottom left (top left?) point
#define		PROF_QUAD_XEND			0x3000	// x-coordinate of the quad window top right (bottom right?) point
#define		PROF_QUAD_YSTART		0x4000	// y-coordinate of the quad window bottom left (top left?) point
#define		PROF_QUAD_YEND			0x5000	// y-coordinate of the quad window top right (bottom right?) point

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of profiler definitions
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif


