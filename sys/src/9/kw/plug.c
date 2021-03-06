/* 
 * This file is part of the UCB release of Plan 9. It is subject to the license
 * terms in the LICENSE file found in the top-level directory of this
 * distribution and at http://akaros.cs.berkeley.edu/files/Plan9License. No
 * part of the UCB release of Plan 9, including this file, may be copied,
 * modified, propagated, or distributed except according to the terms contained
 * in the LICENSE file.
 */

#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "io.h"
#include "../port/error.h"

extern Dev rootdevtab;
extern Dev consdevtab;
extern Dev envdevtab;
extern Dev pipedevtab;
extern Dev procdevtab;
extern Dev mntdevtab;
extern Dev srvdevtab;
extern Dev dupdevtab;
extern Dev rtcdevtab;
extern Dev archdevtab;
extern Dev ssldevtab;
extern Dev tlsdevtab;
extern Dev capdevtab;
extern Dev kprofdevtab;
extern Dev aoedevtab;
extern Dev sddevtab;
extern Dev fsdevtab;
extern Dev flashdevtab;
extern Dev twsidevtab;
extern Dev etherdevtab;
extern Dev ipdevtab;
extern Dev uartdevtab;
extern Dev usbdevtab;
Dev* devtab[]={
	&rootdevtab,
	&consdevtab,
	&envdevtab,
	&pipedevtab,
	&procdevtab,
	&mntdevtab,
	&srvdevtab,
	&dupdevtab,
	&rtcdevtab,
	&archdevtab,
	&ssldevtab,
	&tlsdevtab,
	&capdevtab,
	&kprofdevtab,
	&aoedevtab,
	&sddevtab,
	&fsdevtab,
	&flashdevtab,
	&twsidevtab,
	&etherdevtab,
	&ipdevtab,
	&uartdevtab,
	&usbdevtab,
	nil,
};

extern void ether1116link(void);
extern void archkwlink(void);
extern void ethermediumlink(void);
extern void flashkwlink(void);
extern void loopbackmediumlink(void);
extern void netdevmediumlink(void);
extern void usbehcilink(void);
void links(void){
	bootlinks();

	ether1116link();
	archkwlink();
	ethermediumlink();
	flashkwlink();
	loopbackmediumlink();
	netdevmediumlink();
	usbehcilink();
}

#include "../port/sd.h"
extern SDifc sdaoeifc;
SDifc* sdifc[] = {
	&sdaoeifc,
	nil,
};

extern PhysUart kwphysuart;
PhysUart* physuart[] = {
	&kwphysuart,
	nil,
};

#include "../ip/ip.h"
extern void tcpinit(Fs*);
extern void udpinit(Fs*);
extern void ipifcinit(Fs*);
extern void icmpinit(Fs*);
extern void icmp6init(Fs*);
extern void ipmuxinit(Fs*);
void (*ipprotoinit[])(Fs*) = {
	tcpinit,
	udpinit,
	ipifcinit,
	icmpinit,
	icmp6init,
	ipmuxinit,
	nil,
};

int cpuserver = 1;
int i8250freq = 3686000;

char* conffile = "/sys/src/9/kw/plug";
ulong kerndate = KERNDATE;
uchar configfile[]={
0x23,0x20,0x70,0x6c,0x75,0x67,0x20,0x2d,0x20,0x73,0x68,0x65,0x65,0x76,0x61,0x20,
0x70,0x6c,0x75,0x67,0x2c,0x20,0x6f,0x70,0x65,0x6e,0x72,0x64,0x2d,0x63,0x6c,0x69,
0x65,0x6e,0x74,0x2c,0x20,0x67,0x75,0x72,0x75,0x70,0x6c,0x75,0x67,0x2c,0x20,0x64,
0x72,0x65,0x61,0x6d,0x70,0x6c,0x75,0x67,0x20,0x61,0x6e,0x64,0x20,0x6f,0x74,0x68,
0x65,0x72,0x73,0x20,0x62,0x61,0x73,0x65,0x64,0x20,0x6f,0x6e,0x0a,0x23,0x09,0x6d,
0x61,0x72,0x76,0x65,0x6c,0x6c,0x27,0x73,0x20,0x6b,0x69,0x72,0x6b,0x77,0x6f,0x6f,
0x64,0x20,0x73,0x6f,0x63,0x0a,0x64,0x65,0x76,0x0a,0x09,0x72,0x6f,0x6f,0x74,0x0a,
0x09,0x63,0x6f,0x6e,0x73,0x0a,0x09,0x65,0x6e,0x76,0x0a,0x09,0x70,0x69,0x70,0x65,
0x0a,0x09,0x70,0x72,0x6f,0x63,0x0a,0x09,0x6d,0x6e,0x74,0x0a,0x09,0x73,0x72,0x76,
0x0a,0x09,0x64,0x75,0x70,0x0a,0x09,0x72,0x74,0x63,0x0a,0x09,0x61,0x72,0x63,0x68,
0x0a,0x09,0x73,0x73,0x6c,0x0a,0x09,0x74,0x6c,0x73,0x0a,0x09,0x63,0x61,0x70,0x0a,
0x09,0x6b,0x70,0x72,0x6f,0x66,0x0a,0x09,0x61,0x6f,0x65,0x0a,0x09,0x73,0x64,0x0a,
0x09,0x66,0x73,0x0a,0x09,0x66,0x6c,0x61,0x73,0x68,0x0a,0x09,0x74,0x77,0x73,0x69,
0x0a,0x23,0x09,0x70,0x6e,0x70,0x09,0x09,0x70,0x63,0x69,0x0a,0x0a,0x09,0x65,0x74,
0x68,0x65,0x72,0x09,0x09,0x6e,0x65,0x74,0x69,0x66,0x0a,0x09,0x69,0x70,0x09,0x09,
0x61,0x72,0x70,0x20,0x63,0x68,0x61,0x6e,0x64,0x69,0x61,0x6c,0x20,0x69,0x70,0x20,
0x69,0x70,0x76,0x36,0x20,0x69,0x70,0x61,0x75,0x78,0x20,0x69,0x70,0x72,0x6f,0x75,
0x74,0x65,0x20,0x6e,0x65,0x74,0x6c,0x6f,0x67,0x20,0x6e,0x75,0x6c,0x6c,0x6d,0x65,
0x64,0x69,0x75,0x6d,0x20,0x70,0x6b,0x74,0x6d,0x65,0x64,0x69,0x75,0x6d,0x20,0x70,
0x74,0x63,0x6c,0x62,0x73,0x75,0x6d,0x20,0x69,0x6e,0x66,0x65,0x72,0x6e,0x6f,0x0a,
0x0a,0x23,0x23,0x09,0x64,0x72,0x61,0x77,0x09,0x09,0x73,0x63,0x72,0x65,0x65,0x6e,
0x20,0x76,0x67,0x61,0x20,0x76,0x67,0x61,0x78,0x0a,0x23,0x23,0x09,0x6d,0x6f,0x75,
0x73,0x65,0x09,0x09,0x6d,0x6f,0x75,0x73,0x65,0x0a,0x23,0x23,0x09,0x76,0x67,0x61,
0x0a,0x23,0x09,0x6b,0x62,0x6d,0x61,0x70,0x0a,0x23,0x23,0x09,0x6b,0x62,0x69,0x6e,
0x0a,0x0a,0x09,0x75,0x61,0x72,0x74,0x0a,0x09,0x75,0x73,0x62,0x0a,0x0a,0x6c,0x69,
0x6e,0x6b,0x0a,0x09,0x65,0x74,0x68,0x65,0x72,0x31,0x31,0x31,0x36,0x09,0x65,0x74,
0x68,0x65,0x72,0x6d,0x69,0x69,0x0a,0x09,0x61,0x72,0x63,0x68,0x6b,0x77,0x0a,0x09,
0x65,0x74,0x68,0x65,0x72,0x6d,0x65,0x64,0x69,0x75,0x6d,0x0a,0x23,0x20,0x6e,0x6f,
0x20,0x66,0x6c,0x61,0x73,0x68,0x20,0x79,0x65,0x74,0x20,0x66,0x6f,0x72,0x20,0x67,
0x75,0x72,0x75,0x70,0x6c,0x75,0x67,0x20,0x6e,0x6f,0x72,0x20,0x64,0x72,0x65,0x61,
0x6d,0x70,0x6c,0x75,0x67,0x3b,0x20,0x69,0x74,0x20,0x6b,0x65,0x65,0x70,0x73,0x20,
0x63,0x68,0x61,0x6e,0x67,0x69,0x6e,0x67,0x2c,0x20,0x61,0x6e,0x64,0x0a,0x23,0x20,
0x6f,0x6e,0x20,0x74,0x68,0x65,0x20,0x64,0x72,0x65,0x61,0x6d,0x70,0x6c,0x75,0x67,
0x2c,0x20,0x66,0x6c,0x61,0x73,0x68,0x20,0x69,0x73,0x20,0x73,0x70,0x69,0x20,0x69,
0x6e,0x73,0x74,0x65,0x61,0x64,0x20,0x6f,0x66,0x20,0x6e,0x61,0x6e,0x64,0x2e,0x0a,
0x09,0x66,0x6c,0x61,0x73,0x68,0x6b,0x77,0x09,0x09,0x65,0x63,0x63,0x0a,0x09,0x6c,
0x6f,0x6f,0x70,0x62,0x61,0x63,0x6b,0x6d,0x65,0x64,0x69,0x75,0x6d,0x0a,0x09,0x6e,
0x65,0x74,0x64,0x65,0x76,0x6d,0x65,0x64,0x69,0x75,0x6d,0x0a,0x09,0x75,0x73,0x62,
0x65,0x68,0x63,0x69,0x09,0x09,0x75,0x73,0x62,0x65,0x68,0x63,0x69,0x6b,0x77,0x0a,
0x0a,0x69,0x70,0x0a,0x09,0x74,0x63,0x70,0x0a,0x09,0x75,0x64,0x70,0x0a,0x09,0x69,
0x70,0x69,0x66,0x63,0x0a,0x09,0x69,0x63,0x6d,0x70,0x0a,0x09,0x69,0x63,0x6d,0x70,
0x36,0x0a,0x09,0x69,0x70,0x6d,0x75,0x78,0x0a,0x0a,0x6d,0x69,0x73,0x63,0x0a,0x09,
0x72,0x64,0x62,0x0a,0x09,0x63,0x6f,0x70,0x72,0x6f,0x63,0x0a,0x09,0x73,0x64,0x61,
0x6f,0x65,0x09,0x09,0x73,0x64,0x73,0x63,0x73,0x69,0x0a,0x09,0x73,0x6f,0x66,0x74,
0x66,0x70,0x75,0x0a,0x09,0x73,0x79,0x73,0x63,0x61,0x6c,0x6c,0x0a,0x09,0x75,0x61,
0x72,0x74,0x6b,0x77,0x0a,0x09,0x75,0x63,0x61,0x6c,0x6c,0x6f,0x63,0x0a,0x23,0x23,
0x09,0x76,0x67,0x61,0x76,0x65,0x73,0x61,0x0a,0x0a,0x70,0x6f,0x72,0x74,0x0a,0x09,
0x69,0x6e,0x74,0x20,0x63,0x70,0x75,0x73,0x65,0x72,0x76,0x65,0x72,0x20,0x3d,0x20,
0x31,0x3b,0x0a,0x09,0x69,0x6e,0x74,0x20,0x69,0x38,0x32,0x35,0x30,0x66,0x72,0x65,
0x71,0x20,0x3d,0x20,0x33,0x36,0x38,0x36,0x30,0x30,0x30,0x3b,0x0a,0x0a,0x62,0x6f,
0x6f,0x74,0x20,0x63,0x70,0x75,0x0a,0x09,0x74,0x63,0x70,0x0a,0x23,0x09,0x70,0x61,
0x71,0x0a,0x0a,0x62,0x6f,0x6f,0x74,0x64,0x69,0x72,0x0a,0x09,0x62,0x6f,0x6f,0x74,
0x24,0x43,0x4f,0x4e,0x46,0x2e,0x6f,0x75,0x74,0x20,0x62,0x6f,0x6f,0x74,0x0a,0x09,
0x2f,0x61,0x72,0x6d,0x2f,0x62,0x69,0x6e,0x2f,0x69,0x70,0x2f,0x69,0x70,0x63,0x6f,
0x6e,0x66,0x69,0x67,0x0a,0x09,0x2f,0x61,0x72,0x6d,0x2f,0x62,0x69,0x6e,0x2f,0x61,
0x75,0x74,0x68,0x2f,0x66,0x61,0x63,0x74,0x6f,0x74,0x75,0x6d,0x0a,0x09,0x2f,0x61,
0x72,0x6d,0x2f,0x62,0x69,0x6e,0x2f,0x75,0x73,0x62,0x2f,0x75,0x73,0x62,0x64,0x0a,
0x09,0x2f,0x61,0x72,0x6d,0x2f,0x62,0x69,0x6e,0x2f,0x64,0x69,0x73,0x6b,0x2f,0x70,
0x61,0x72,0x74,0x66,0x73,0x0a,0x23,0x09,0x2f,0x61,0x72,0x6d,0x2f,0x62,0x69,0x6e,
0x2f,0x70,0x61,0x71,0x66,0x73,0x0a,

0,
};
