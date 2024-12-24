/* ***************************************************************************
MIT License

Copyright (c) 2024 k-off pacovali@student.42berlin.de

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*************************************************************************** */

#pragma once

#include <cstdint>

// Synchronization signals differ for different vga modes, choose Lo or Hi
enum class Sync : bool {Lo, Hi};

struct Timing {
	uint8_t fporch; // front porch, in pixels (lines) for horisontal (vertical) resolution
	uint8_t spulse; // synch pulse, in pixels (lines) for horisontal (vertical) resolution
	uint8_t bporch; // back  porch, in pixels (lines) for horisontal (vertical) resolution
};

struct VGAMode {
	uint8_t		frequency;	// display refresh rate, Hz
	uint32_t	linefreq;	// line refresh rate, Hz
	Timing		htim;		// horisontal timings
	uint16_t	hres;		// number of visible pixels in a line
	Timing		vtim;		// vertical   timings
	uint16_t	vres;		// number of visible pixels (lines) in a column
	Sync		hsync;		// horisontal synching signal: Lo or Hi
	Sync		vsync;		// vertical synching signal: Lo or Hi

	// returns total vertical pixels (lines)
	inline uint16_t vtotal() const {
		return vres + vtim.bporch + vtim.fporch + vtim.spulse;
	}
	// returns total horisontal pixels (columns)
	inline uint16_t htotal() const {
		return hres + htim.bporch + htim.fporch + htim.spulse;
	}
};

/// @brief 320x240 @60Hz
/// 320	240	60 Hz	31.5 kHz	ModeLine "320x240" 12.60 320 328 376 400 240 245 246 262 -HSync -VSync DoubleScan
constexpr const VGAMode m320x240_60Hz = {
	.frequency=60u,
	.linefreq=31500u,
	.htim={
		.fporch=8u,
		.spulse=48u,
		.bporch=24u
	},
	.hres=320u,
	.vtim={
		.fporch=5u,
		.spulse=2u,
		.bporch=15u
	},
	.vres=240u,
	.hsync=Sync::Lo,
	.vsync=Sync::Lo
};

/// @brief 512x384 @60Hz
/// 512 384 60 Hz 48.3631 kHz ModeLine "512x384" 32.50 512 524 592 672 384 385 388 403 -HSync -VSync DoubleScan
constexpr const VGAMode m512x384_60Hz = {
	.frequency=60u,
	.linefreq=48363u,
	.htim={
		.fporch=12u,
		.spulse=68u,
		.bporch=24u
	},
	.hres=512u,
	.vtim={
		.fporch=1u,
		.spulse=3u,
		.bporch=15u
	},
	.vres=384u,
	.hsync=Sync::Lo,
	.vsync=Sync::Lo
};

/// @brief 640x480 @60Hz
/// 640	480	60 Hz	31.5 kHz	ModeLine "640x480" 25.20 640 656 752 800 480 490 492 525 -HSync -VSync
constexpr const VGAMode m640x480_60Hz = {
	.frequency=60u,
	.linefreq=31500u,
	.htim={
		.fporch=16u,
		.spulse=96u,
		.bporch=48u
	},
	.hres=640u,
	.vtim={
		.fporch=10u,
		.spulse=2u,
		.bporch=33u
	},
	.vres=480u,
	.hsync=Sync::Lo,
	.vsync=Sync::Lo
};

/// @brief 800x600 @56Hz
/// 800	600	56 Hz	35.1562 kHz	ModeLine "800x600" 36.00 800 824 896 1024 600 601 603 625 +HSync +VSync
constexpr const VGAMode m800x600_56Hz = {
	.frequency=56u,
	.linefreq=35156u,
	.htim={
		.fporch=24u,
		.spulse=72u,
		.bporch=128u
	},
	.hres=800u,
	.vtim={
		.fporch=1u,
		.spulse=2u,
		.bporch=22u
	},
	.vres=600u,
	.hsync=Sync::Hi,
	.vsync=Sync::Hi
};

/// @brief 1024x768 @60Hz
/// 1024	768	60 Hz	48.3631 kHz	ModeLine "1024x768" 65.00 1024 1048 1184 1344 768 771 777 806 -HSync -VSync
constexpr const VGAMode m1024x768_60Hz = {
	.frequency=60u,
	.linefreq=48363u,
	.htim={
		.fporch=24u,
		.spulse=136u,
		.bporch=160u
	},
	.hres=1024u,
	.vtim={
		.fporch=3u,
		.spulse=6u,
		.bporch=29u
	},
	.vres=768u,
	.hsync=Sync::Lo,
	.vsync=Sync::Lo
};